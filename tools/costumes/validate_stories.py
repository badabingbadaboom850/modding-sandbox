#!/usr/bin/env python3
"""Execute real optional story assembly, album cancel flows and map/source checks."""
from pathlib import Path
import re,json,subprocess,itertools,sys
R=Path(__file__).resolve().parents[2]
s=(R/'data/scripts/trio_outfit_stories.inc').read_text();labels={};code=[]
for line in s.splitlines():
 line=line.strip()
 if not line or line.startswith('@'):continue
 if re.fullmatch(r'\w+::?',line):
  label=line.rstrip(':');assert label not in labels,label;labels[label]=len(code)
 else:code.append(line)
for label in re.findall(r'\b(?:TrioOutfit|TrioHunt|TrioBread|TrioStories)_\w+',s):assert label in labels,label
for line in s.splitlines():
 if line.strip().startswith('.string'):assert re.fullmatch(r'\s*\.string ".*\$"',line),line
for text in re.findall(r'\.string "(.*)"',s):
 for page in text[:-1].split(r'\p'):
  lines=page.split(r'\n');assert len(lines)<=2
  assert all(len(line)<=26 for line in lines),(text,lines)
class Run:
 def __init__(self,vars=None,party=True,yes=True,room=True,choices=(),photo=True,reactions=(0,0,0)):
  self.vars=dict(vars or {});self.party=party;self.yes=yes;self.room=room;self.choices=iter(choices);self.photo=photo;self.reactions=reactions;self.gifts=0;self.lock=False;self.image=False;self.images=0;self.messages=[]
 def val(self,a):return {'TRUE':1,'FALSE':0,'NO':0}.get(a,self.vars.get(a,int(a) if a.isdigit() else a))
 def run(self,start):
  pc=labels[start];stack=[]
  for _ in range(1000):
   op,_,arg=code[pc].partition(' ');pc+=1;a=[x.strip() for x in arg.split(',')]
   if op in ['lock','lockall']:self.lock=True
   elif op=='release':self.lock=False
   elif op=='end':assert not self.lock and not self.image;return self
   elif op=='return':
    if stack:pc=stack.pop()
    else:assert not self.image;return self
   elif op=='goto':pc=labels[a[0]]
   elif op in ['goto_if_eq','goto_if_ge','goto_if_lt']:
    x=self.val(a[0]);y=self.val(a[1]);condition=x==y if op=='goto_if_eq' else x>=y if op=='goto_if_ge' else x<y
    if condition:pc=labels[a[2]]
   elif op=='setvar':self.vars[a[0]]=self.val(a[1])
   elif op=='call':
    if a[0].startswith('TrioParty_Check'):self.vars['VAR_RESULT']=int(self.party)
    else:stack.append(pc);pc=labels[a[0]]
   elif op=='call_if_eq' or op=='call_if_ge':
    x=self.val(a[0]);y=self.val(a[1]);condition=x==y if op=='call_if_eq' else x>=y
    if condition:stack.append(pc);pc=labels[a[2]]
   elif op=='msgbox':
    self.messages.append(a[0])
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=int(self.yes)
   elif op=='giveitem':self.gifts+=int(self.room);self.vars['VAR_RESULT']=int(self.room)
   elif op=='specialvar':
    if a[1]=='HasTrioOutfitPhoto':self.vars[a[0]]=int(self.photo)
    elif a[1]=='GetTrioOutfitReaction':
     family=self.vars['VAR_0x8004'];self.vars[a[0]]=next((v for v in self.reactions if v),0) if family==3 else self.reactions[family]
    else:raise AssertionError(a)
   elif op=='special':assert a[0] in ['TrioOutfits_RecordPartyPhotos','BufferTrioOutfitPhotoCount']
   elif op=='dynmultichoice':self.vars['VAR_RESULT']=next(self.choices)
   elif op=='showmonpic':assert not self.image;self.image=True;self.images+=1
   elif op=='hidemonpic':assert self.image;self.image=False
   elif op in ['closemessage','faceplayer']:pass
   else:raise AssertionError(op)
  raise AssertionError('Nonterminating story '+start)
count=0
for girl in ['Riko','Bijuu','Penny']:
 var='VAR_TRIO_HUNT_'+girl.upper()
 for stage,party,yes,room in itertools.product(range(4),[False,True],[False,True],[False,True]):
  state={var:stage};r=Run(state,party,yes,room).run('TrioHunt_'+girl+'Host');expected=3 if stage==2 and room else 1 if stage==0 and party and yes else stage
  assert r.vars.get(var,0)==expected
  assert r.gifts==int(stage==2 and room)
  search=Run(state,party,yes,room).run('TrioHunt_'+girl+'Search');assert search.vars.get(var,0)==(2 if stage==1 and party else stage)
  if stage==2 and room:
   again=Run(r.vars,False,True,True).run('TrioHunt_'+girl+'Host');assert again.gifts==0
  count+=2
print(count,'hunt accept/decline/missing-party/reclaim/full-Bag/repeat paths pass')
var='VAR_TRIO_BREAD_MYSTERY'
for stage,yes,room in itertools.product(range(5),[False,True],[False,True]):
 state={var:stage};r=Run(state,yes=yes,room=room).run('TrioBread_Rumor');assert r.vars[var]==(4 if stage==3 and room else 1 if stage==0 and yes else stage);assert r.gifts==int(stage==3 and room)
 c=Run(state).run('TrioBread_Clue');assert c.vars[var]==(2 if stage in [1,2] else stage)
 reveal=Run(state).run('TrioBread_Reveal');assert reveal.vars[var]==(3 if stage==2 else stage)
print('60 bread mystery rumor/clue/reveal/reward/replay paths pass')
for family,ids in enumerate([[0,1,2],[3,4,5],[6,7,8],[9]]):
 for page in range(len(ids)):
  for unlocked in [False,True]:
   r=Run(choices=[family,page,127],photo=unlocked).run('TrioOutfit_Album');assert r.images==int(unlocked) and not r.image
 r=Run(choices=[family,127,127]).run('TrioOutfit_Album');assert r.images==0
Run(choices=[127]).run('TrioOutfit_Album')
for i in range(1,11):
 r=Run(reactions=(i,0,0)).run('TrioOutfit_React');assert len(r.messages)==1
 r=Run(reactions=(i,0,0)).run('TrioOutfit_ReactTown');assert len(r.messages)==1
r=Run(reactions=(2,6,9)).run('TrioOutfit_Scott');assert len(r.messages)==3
r=Run().run('TrioOutfit_Scott');assert not r.messages
print('All10 portrait unlock/locked/Back/B flows close images; all outfit/Scott dispatches pass')
sys.path.insert(0,str(R/'tools/snack'));from gang_geometry import geometry
placements=json.loads((R/'tools/costumes/story_placements.json').read_text());base='06af87a3d90b9a875024b7805f36acd4dcc285b8'
for city in {p['city'] for p in placements}:
 m,w,h,walk=geometry(city);old=json.loads(subprocess.check_output(['git','show',base+':data/maps/'+city+'/map.json'],cwd=R,text=True));assert m['object_events'][:len(old['object_events'])]==old['object_events']
 for k in old:
  if k!='object_events':assert old[k]==m[k]
 for p in [p for p in placements if p['city']==city]:
  x,y=p['x'],p['y'];assert all(walk(a,b) for a,b in [(x,y),(x-1,y),(x+1,y),(x,y-1),(x,y+1)])
  assert len([e for e in m['object_events'] if (e['x'],e['y'])==(x,y)])==1
  assert p['script'] in labels
print('Six optional story props/actors have walkable approaches and preserve all original map events')
for hook in json.loads((R/'tools/costumes/story_hooks.json').read_text()):
 for ext in ['inc','pory']:
  p=R/f'data/maps/{hook["city"]}/scripts.{ext}'
  if not p.exists():continue
  old=subprocess.check_output(['git','show',base+':'+str(p.relative_to(R))],cwd=R,text=True);new=p.read_text();assert new.count('TrioOutfit_ReactTown')==1
  assert new.replace('\tcall TrioOutfit_ReactTown\n','').replace('    call(TrioOutfit_ReactTown)\n','')==old
for p in ['include/global.h','include/pokemon.h','src/save.c','include/config/save.h','include/constants/species.h','include/constants/items.h']:
 assert (R/p).read_bytes()==subprocess.check_output(['git','show',base+':'+p],cwd=R)
old=subprocess.check_output(['git','show',base+':include/constants/vars.h'],cwd=R,text=True);new=(R/'include/constants/vars.h').read_text()
for n,v in re.findall(r'^#define (VAR\w+)\s+(0x[0-9A-F]+)',old,re.M):assert re.search(r'^#define '+n+r'\s+'+v+r'\b',new,re.M)
for id in range(0x4131,0x4136):assert not re.search(r'\b'+hex(id)+r'\b',old,re.I)
assert (R/'data/specials.inc').read_text().startswith(subprocess.check_output(['git','show',base+':data/specials.inc'],cwd=R,text=True))
print('Old save layouts/species/items/var IDs/special indices and civilian Pory/assembly preserved')
