#!/usr/bin/env python3
"""Run actual assembly with engine stubs; validate geometry and saved phase flow.
These checks do not claim rendered emulator playtesting.
"""
from pathlib import Path
import json,re,struct,collections,subprocess,unittest
ROOT=Path(__file__).resolve().parents[2];STATE='VAR_RIKO_CAVERN_STATE'
S=(ROOT/'data/maps/RikoSpiritCavern/scripts.inc').read_text()
MEM=(ROOT/'data/scripts/trio_memories.inc').read_text()
CODE=[];LABELS={}
for line in (S+'\n'+MEM).splitlines():
 line=line.strip()
 if not line or line.startswith('@'):continue
 if re.fullmatch(r'\w+::?',line):LABELS[line.rstrip(':')]=len(CODE)
 else:CODE.append(line)
MAP=json.loads((ROOT/'data/maps/RikoSpiritCavern/map.json').read_text());BASE=struct.unpack('<960H',(ROOT/'data/layouts/RikoSpiritCavern/map.bin').read_bytes())
class Run:
 def __init__(self,state=0,answers=(),outcome=1,room=True,party=True,flags=()):
  self.vars={STATE:state};self.answers=iter(answers);self.outcome=outcome;self.room=room;self.party=party;self.flags=set(flags);self.xy={i+1:(o['x'],o['y']) for i,o in enumerate(MAP['object_events'])};self.visible=set(range(1,9));self.battles=[];self.gifts=0;self.warps=[];self.lock=False;self.camera=False
 def val(self,s):
  if s.startswith('VAR_'):return self.vars.get(s,0)
  if re.fullmatch(r'\d+|0x[\da-fA-F]+',s):return int(s,0)
  return {'TRUE':1,'FALSE':0,'YES':1,'NO':0,'B_OUTCOME_WON':1}.get(s,s)
 def run(self,name):
  pc=LABELS[name];stack=[]
  for _ in range(1000):
   op,_,args=CODE[pc].partition(' ');pc+=1;a=[v.strip() for v in args.split(',')]
   if op=='end':return self
   if op=='return':
    if not stack:return self
    pc=stack.pop();continue
   if op=='lockall':self.lock=True;continue
   if op=='releaseall':self.lock=False;continue
   if op in ['faceplayer','closemessage','waitstate','playmoncry','waitmoncry','delay','applymovement','waitmovement','fadescreen']:continue
   if op=='msgbox':
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=next(self.answers,1)
    continue
   if op=='setvar':self.vars[a[0]]=self.val(a[1]);continue
   if op=='setflag':self.flags.add(a[0]);continue
   if op=='clearflag':self.flags.discard(a[0]);continue
   if op=='setobjectxyperm':self.xy[int(a[0])]=(int(a[1]),int(a[2]));continue
   if op=='removeobject':
    i=int(a[0]);self.visible.discard(i)
    if 1<=i<=4:self.flags.add('FLAG_TEMP_'+str(i))
    continue
   if op=='addobject':
    i=int(a[0]);assert 'FLAG_TEMP_'+str(i) not in self.flags;self.visible.add(i);continue
   if op=='warp':self.warps.append(tuple(a));continue
   if op=='giveitem':self.gifts+=self.room;self.vars['VAR_RESULT']=int(self.room);continue
   if op=='specialvar':
    assert a[1] in ['PrepareRikoCavernBattle','GetBattleOutcome'];self.vars[a[0]]=int(self.party) if a[1]=='PrepareRikoCavernBattle' else self.outcome;continue
   if op=='special':
    if a[0]=='BattleSetup_StartTrioSpiritTrial':self.battles.append(self.vars['VAR_0x8004'])
    elif a[0]=='SpawnCameraObject':self.camera=True
    elif a[0]=='RemoveCameraObject':self.camera=False
    else:assert a[0]=='HealPlayerParty'
    continue
   jump=False;target=a[-1]
   if op in ['call','goto']:jump=True
   elif '_if_' in op:
    cond=op.split('_if_')[1]
    if cond in ['set','unset']:jump=(a[0] in self.flags)==(cond=='set')
    else:
     x,y=self.val(a[0]),self.val(a[1]);jump={'eq':x==y,'ne':x!=y,'ge':x>=y,'lt':x<y}[cond]
   else:raise AssertionError(CODE[pc-1])
   if jump:
    if op.startswith('call'):stack.append(pc)
    pc=LABELS[target]
  raise AssertionError('loop')
class Checks(unittest.TestCase):
 def test_order_decline_failure_and_no_party(self):
  for stage,npc in enumerate(['Mind','Body','Soul','Spirit']):
   for kw in [dict(answers=[0]),dict(outcome=2),dict(outcome=4),dict(party=False)]:
    r=Run(stage,**kw).run('RikoCavern_'+npc);self.assertEqual(r.vars[STATE],stage);self.assertFalse(r.lock);self.assertFalse(r.camera);self.assertEqual(r.gifts,0)
  for state,npc in [(0,'Body'),(0,'Soul'),(1,'Soul'),(2,'Spirit')]:self.assertFalse(Run(state).run('RikoCavern_'+npc).battles)
 def test_four_fights_reunion_and_retry_pending(self):
  r=Run(room=False)
  for stage,npc in enumerate(['Mind','Body','Soul','Spirit']):
   r.run('RikoCavern_'+npc);self.assertEqual(r.vars[STATE],stage+1);self.assertFalse(r.lock);self.assertFalse(r.camera)
  self.assertEqual(r.battles,[0,1,2,3]);self.assertEqual(r.xy[1],(15,13));self.assertEqual(r.xy[2],(17,13));self.assertEqual(r.visible&{1,2,3,4},{4});self.assertEqual(r.gifts,0)
  r.party=False;r.room=True;r.run('TrioKeepsakes_TryRiko');self.assertEqual(r.gifts,1)
  r.run('RikoCavern_Spirit').run('TrioKeepsakes_TryRiko');self.assertEqual(r.gifts,1);self.assertEqual(r.battles,[0,1,2,3])
  self.assertNotIn('FLAG_DEFEATED_SUICUNE',r.flags)
 def test_reconstruction_and_geometry_all_saved_states(self):
  attrs=[[v[0] for v in struct.iter_unpack('<H',(ROOT/'data/tilesets'/p/'metatile_attributes.bin').read_bytes())] for p in ['primary/johto_general','secondary/cave_default']]
  for i,b in enumerate(BASE):
   tile=b&0x7ff;self.assertLess(tile%1024,len(attrs[tile>=1024]))
   if not b&0x800:self.assertIn(attrs[tile>=1024][tile%1024]&255,(8,0x65))
  for state in range(5):
   r=Run(state).run('RikoCavern_Transition');occupied={r.xy[i+1] for i,o in enumerate(MAP['object_events']) if o['flag']=='0' or o['flag'] not in r.flags};seen={(16,26)};q=collections.deque(seen)
   while q:
    x,y=q.popleft()
    for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
     nx,ny=p
     if 0<=nx<32 and 0<=ny<30 and p not in occupied and p not in seen and not BASE[ny*32+nx]&0x800:seen.add(p);q.append(p)
   for x,y in occupied:self.assertTrue(any(p in seen for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]),(state,x,y))
   for w in MAP['warp_events']:self.assertIn((w['x'],w['y']),seen);self.assertEqual(attrs[1][BASE[w['y']*32+w['x']]%1024]&255,0x65)
   # Shrine forces the camera scene's guaranteed south interaction position.
   self.assertIn((16,7),seen);self.assertTrue(all(BASE[y*32+x]&0x800 for x,y in [(15,6),(17,6),(16,5)]))
  self.assertLessEqual(len(MAP['object_events'])+3,16)
 def test_test_warp_reset_and_historical_reward(self):
  for state in range(5):
   r=Run(state,answers=[0]).run('RikoCavern_TestOffer');self.assertFalse(r.warps)
   r=Run(state).run('RikoCavern_TestOffer');self.assertEqual(r.warps,[('MAP_RIKO_SPIRIT_CAVERN','16','26')]);self.assertEqual(r.vars[STATE],state)
   r=Run(state,answers=[0,1],flags=['FLAG_TRIO_RIKO_KEEPSAKE','FLAG_RIKO_CAVERN_COMPLETE']).run('RikoCavern_Guide');self.assertEqual(r.vars[STATE],0);self.assertIn('FLAG_TRIO_RIKO_KEEPSAKE',r.flags);self.assertIn('FLAG_RIKO_CAVERN_COMPLETE',r.flags);self.assertFalse(r.lock)
  r=Run(flags=['FLAG_DEFEATED_SUICUNE']).run('TrioKeepsakes_TryRiko');self.assertEqual(r.gifts,1);self.assertEqual(r.vars[STATE],0)
 def test_authoring_refs_and_original_ids(self):
  self.assertEqual((ROOT/'data/maps/RikoSpiritCavern/scripts.pory').read_text().split('`')[1].strip(),S.strip())
  for text in re.findall(r'\.string "(.*)"',S):
   self.assertTrue(text.endswith('$'))
   for page in text[:-1].split(r'\p'):
    lines=page.split(r'\n');self.assertLessEqual(len(lines),2)
    for line in lines:self.assertLessEqual(len(line),26)
  for ref in re.findall(r'\bRikoCavern_\w+\b',S+MEM):self.assertIn(ref,LABELS)
  for path,key in [('data/layouts/layouts.json','layouts'),('data/maps/map_groups.json','gMapGroup_IndoorNewBark')]:
   old=json.loads(subprocess.check_output(['git','show','5eaa4ea0:'+path],cwd=ROOT));new=json.loads((ROOT/path).read_text());self.assertEqual(new[key][:-1],old[key])
  old=json.loads(subprocess.check_output(['git','show','5eaa4ea0:data/maps/NewBarkTown/map.json'],cwd=ROOT));self.assertEqual(json.loads((ROOT/'data/maps/NewBarkTown/map.json').read_text()),old)
if __name__=='__main__':unittest.main()
