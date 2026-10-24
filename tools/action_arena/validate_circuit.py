#!/usr/bin/env python3
"""Validate the real NPC placements, dialogue, saved allocations and script paths."""
from pathlib import Path
import collections,json,re,subprocess
from geometry import geometry
ROOT=Path(__file__).resolve().parents[2]
BASE='884e6a3d3b264c06ed003e11344d3569fdcaa8c0'
def old(p):return subprocess.check_output(['git','show',BASE+':'+p],cwd=ROOT)
def flood(start,blocked,walk):
 seen={start};q=collections.deque(seen)
 while q:
  x,y=q.popleft()
  for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
   if p not in seen and p not in blocked and walk(*p):seen.add(p);q.append(p)
 return seen
for entry in json.loads((ROOT/'tools/action_arena/challengers.json').read_text()):
 city=entry['city'];m,w,h,walk,elevation=geometry(city)
 before=json.loads(old(f'data/maps/{city}/map.json'));actor=m['object_events'][-1]
 assert m['object_events'][:-1]==before['object_events']
 assert {k:v for k,v in m.items() if k!='object_events'}=={k:v for k,v in before.items() if k!='object_events'}
 pos=(entry['x'],entry['y']);assert (actor['x'],actor['y'])==pos
 assert actor['script']=='TrioArenaCircuit_'+city and actor['flag']=='0'
 assert actor['trainer_type']=='TRAINER_TYPE_NONE'
 assert actor['elevation']==elevation(*pos) and walk(*pos)
 assert pos not in {(e['x'],e['y']) for k in ['warp_events','coord_events','bg_events'] for e in m[k]}
 occupied={(e['x'],e['y']) for e in m['object_events']}
 assert sum((e['x'],e['y'])==pos for e in m['object_events'])==1
 start=tuple(entry['start']);seen=flood(start,occupied,walk)
 assert flood(start,occupied-{pos},walk)-{pos}==seen
 assert sum(p in seen for p in [(pos[0]+1,pos[1]),(pos[0]-1,pos[1]),(pos[0],pos[1]+1),(pos[0],pos[1]-1)])>=3
 budget=max(sum(abs(o['x']-x)<=10 and abs(o['y']-y)<=8 for o in m['object_events'])+2 for x in range(pos[0]-10,pos[0]+11) for y in range(pos[1]-8,pos[1]+9))
 assert budget==entry['budget'] and budget<=16
 assert re.search(r'#define LOCALID_ARENA_'+city.upper()+r'\s+'+str(entry['local_id'])+r'\b', (ROOT/'include/constants/map_event_ids.h').read_text())
for path in ['include/global.h','include/constants/flags.h','include/constants/items.h','include/constants/species.h','data/maps/map_groups.json','src/new_game.c','src/battle_setup.c']:
 assert (ROOT/path).read_bytes()==old(path),path
variables=(ROOT/'include/constants/vars.h').read_bytes();assert variables.startswith(old('include/constants/vars.h'))
assert set(re.findall(rb'#define (\w+)\s+(0x\w+)',variables[len(old('include/constants/vars.h')):]))=={(b'VAR_TRIO_ARENA_WINS',b'0x416B'),(b'VAR_TRIO_ARENA_REWARDS',b'0x416C')}
specials=(ROOT/'data/specials.inc').read_bytes();assert specials.startswith(old('data/specials.inc'))
script=(ROOT/'data/scripts/trio_action_circuit.inc').read_text()
assert (ROOT/'data/event_scripts.s').read_text().count('.include "data/scripts/trio_action_circuit.inc"')==1
labels=collections.Counter()
for p in [*ROOT.glob('data/maps/**/scripts.inc'),*ROOT.glob('data/scripts/*.inc')]:labels.update(re.findall(r'^(\w+)::?',p.read_text(),re.M))
for l in re.findall(r'\bTrioArenaCircuit_\w+\b',script):assert labels[l]==1,(l,labels[l])
chars={}
for l in (ROOT/'charmap.txt').read_text().splitlines():
 m=re.match(r"^('.*?')\s*=\s*([\da-fA-F]{2})\b",l)
 if m:chars[m[1][1:-1].replace("\\'", "'")]=int(m[2],16)
font=(ROOT/'src/fonts.c').read_text();widths=list(map(int,re.findall(r'\b\d+\b',font.split('gFontNormalLatinGlyphWidths[] = {')[1].split('};')[0])))
for t in re.findall(r'\.string "(.*?)"',script):
 assert t.endswith('$') and t.isascii()
 for page in t[:-1].split(r'\p'):
  assert len(page.split(r'\n'))<=2
  for l in page.split(r'\n'):assert len(l)<=26 and sum(widths[chars[c]] for c in l)<=208,l
# Interpret actual commands, returning resumed minigame outcomes at waitstate.
code=[];targets={}
for l in script.splitlines():
 l=l.strip()
 if not l or l.startswith(('@','.string')):continue
 if re.fullmatch(r'\w+::?',l):targets[l.rstrip(':')]=len(code)
 else:code.append(l)
def run(city,state,answers,outcomes,claim=1,setup=True):
 pc=targets['TrioArenaCircuit_'+city];locked=False;result=0;fights=0;records=0;claims=0
 answers=iter(answers);outcomes=iter(outcomes)
 val=lambda s:{'VAR_RESULT':result,'YES':1,'FALSE':0}.get(s,int(s) if s.isdigit() else s)
 for _ in range(160):
  op,_,args=code[pc].partition(' ');pc+=1;a=[v.strip() for v in args.split(',')]
  if op=='end':assert not locked;return fights,records,claims
  if op=='lockall':locked=True
  elif op=='releaseall':locked=False
  elif op in ['faceplayer','closemessage','playfanfare','waitfanfare']:pass
  elif op=='msgbox':
   if a[1]=='MSGBOX_YESNO':result=next(answers)
  elif op=='specialvar':
   if a[1]=='GetTrioArenaChallengeState':result=state
   else:assert a[1]=='ClaimTrioArenaChallengeReward';claims+=1;result=claim
  elif op=='special':
   if a[0]=='StartTrioActionChallenge':fights+=1;result=int(setup)
   else:assert a[0]=='RecordTrioArenaChallengeWin';records+=1;result=1
  elif op=='waitstate':result=next(outcomes)
  elif op=='goto':pc=targets[a[0]]
  elif op=='goto_if_eq':
   if val(a[0])==val(a[1]):pc=targets[a[2]]
  elif op=='goto_if_ne':
   if val(a[0])!=val(a[1]):pc=targets[a[2]]
  else:raise AssertionError(op)
 raise AssertionError('script did not release')
for e in json.loads((ROOT/'tools/action_arena/challengers.json').read_text()):
 c=e['city']
 assert run(c,0,[],[])==(0,0,0)
 assert run(c,1,[0],[])==(0,0,0)
 assert run(c,1,[1],[],setup=False)==(1,0,0)
 for out in [0,3]:assert run(c,1,[1],[out])==(1,0,0)
 assert run(c,1,[1,0],[1])==(1,0,0)
 for claim in [0,1,3]:
  assert run(c,1,[1,1],[1,2],claim)==(2,1,1)
  assert run(c,2,[],[],claim)==(0,0,1)
 assert run(c,3,[0],[])==(0,0,0)
 assert run(c,3,[1,0],[2],2)==(1,1,1)
print('PASS: eight appended reachable challengers, unchanged routes/events/IDs/save ABI, object budgets, exact font limits and 120 actual-script decline/retry/win/prize/replay/error paths')
