#!/usr/bin/env python3
"""Actual mugging/optional-battle event-flow and registration checks; not an emulator."""
from pathlib import Path
import collections,json,re,subprocess,unittest
ROOT=Path(__file__).resolve().parents[2]
BASE='e744835926e8f1bb76c66f0286b48ae387475ed9'
SOURCE=(ROOT/'data/scripts/trio_greedent_gang.inc').read_text()
STOPS=['Route37','Route38','Route42','Route44','Route26','Route6']
LABELS={};CODE=[]
for line in SOURCE.splitlines():
 line=line.strip()
 if not line or line.startswith('@') or line.startswith('.string'):continue
 if re.fullmatch(r'\w+::?',line):
  key=line.rstrip(':');assert key not in LABELS;LABELS[key]=len(CODE)
 else:CODE.append(line)
class Run:
 def __init__(self,wave,won=True,full=False,retry=False,answer=1):
  self.vars={'VAR_TEMP_B':wave,'VAR_TRIO_GANG_WINS':wave-1,'VAR_TRIO_GANG_PHASE':1 if retry else 0,'VAR_TRIO_SNACK_CHASE_STATE':0 if wave==1 else 4};self.answer=answer;self.wave=wave;self.won=won;self.full=full;self.retry=retry;self.text=[];self.battle=[];self.locked=False;self.blackout=False
 def run(self,label):
  pc=LABELS[label];stack=[]
  def v(x):return int(x) if x.isdigit() else self.vars.get(x,{'FALSE':0,'TRUE':1,'B_OUTCOME_WON':1,'NO':0}.get(x,x))
  for _ in range(400):
   line=CODE[pc];pc+=1;op,_,rest=line.partition(' ');a=[x.strip() for x in rest.split(',')]
   if op=='lockall':self.locked=True
   elif op=='return':
    if not stack:return self
    pc=stack.pop()
   elif op=='call':stack.append(pc);pc=LABELS[a[0]]
   elif op=='goto_if_unset':
    pass
   elif op=='setvar':self.vars[a[0]]=v(a[1])
   elif op=='copyvar':self.vars[a[0]]=v(a[1])
   elif op=='msgbox':
    self.text.append(a[0])
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=self.answer
   elif op=='special':
    if a[0]=='TrioGang_BeginAmbush':
     self.vars['VAR_0x8004']=self.wave;self.vars['VAR_RESULT']=1;self.vars['VAR_0x8005']=int(not self.retry);self.vars['VAR_TRIO_GANG_PHASE']=1
     if self.vars.get('VAR_0x8004',self.wave)==1:self.vars['VAR_TRIO_SNACK_CHASE_STATE']=1
    elif a[0]=='TrioGang_RecordVictory':
     assert self.won;self.vars['VAR_TRIO_GANG_PHASE']=2
     if self.vars['VAR_0x8004']==1:self.vars['VAR_TRIO_SNACK_CHASE_STATE']=3
    elif a[0]=='TrioSnack_ReturnItem':
     self.vars['VAR_RESULT']=int(not self.full)
     if not self.full:
      self.vars['VAR_TRIO_GANG_PHASE']=0;self.vars['VAR_TRIO_GANG_WINS']=self.vars.get('VAR_0x8004',self.vars['VAR_TEMP_B']);self.vars['VAR_TRIO_SNACK_CHASE_STATE']=4
    elif a[0]=='TrioGang_PrepareAmbush':self.vars['VAR_TEMP_B']=0
    else:assert a[0] in ['TrioSnack_BufferItem','TrioSnack_UpdateObjects']
   elif op=='specialvar':self.vars['VAR_RESULT']=1 if self.won else 2
   elif op=='trainerbattle_no_intro':
    self.battle.append(a[0]);assert self.vars['VAR_TRIO_GANG_PHASE']==1
    if not self.won:self.blackout=True;self.locked=False;return self # CB2_WhiteOut skips the event tail.
   elif op=='goto':
    if a[0]=='TrioSnack_Close':self.locked=False;return self
    pc=LABELS[a[0]]
   elif op in ['goto_if_eq','goto_if_ne']:
    if (v(a[0])==v(a[1]))==(op=='goto_if_eq'):
     if a[2]=='TrioSnack_Close':self.locked=False;return self
     pc=LABELS[a[2]]
   elif op in ['playmoncry','waitmoncry','setflag','removeobject','addobject','faceplayer']:pass
   else:raise AssertionError(line)
  raise AssertionError('loop')
class Checks(unittest.TestCase):
 def test_entry_only_mugs_and_releases_without_a_battle(self):
  for wave in range(1,7):
   r=Run(wave).run('TrioGang_FirstTheft' if wave==1 else 'TrioGang_Ambush')
   self.assertEqual(r.battle,[]);self.assertFalse(r.locked);self.assertEqual(r.vars['VAR_TRIO_GANG_WINS'],wave-1);self.assertEqual(r.vars['VAR_TRIO_GANG_PHASE'],1);self.assertEqual(r.vars['VAR_TEMP_B'],0)
  self.assertNotIn('TrioGang_FirstGate',SOURCE)
 def test_optional_battles_all_waves_decline_loss_retry_and_win(self):
  for wave in range(1,7):
   r=Run(wave,retry=True,answer=0).run('TrioGang_Hideout');self.assertEqual(r.battle,[]);self.assertFalse(r.locked);self.assertEqual(r.vars['VAR_TRIO_GANG_PHASE'],1)
   expected='TRAINER_ROUTE37_SNACK_THIEF' if wave==1 else f'TRAINER_GREEDENT_GANG_{wave}'
   for won in [False,True]:
    r=Run(wave,won=won,retry=True).run('TrioGang_Hideout');self.assertEqual(r.battle,[expected]);self.assertFalse(r.locked)
    self.assertNotIn('TrioGang_StolenText',r.text)
    self.assertEqual(r.vars['VAR_TRIO_GANG_WINS'],wave if won else wave-1)
    self.assertEqual(r.vars['VAR_TRIO_GANG_PHASE'],0 if won else 1)
    self.assertEqual(r.blackout,not won)
    self.assertEqual('TrioGang_MemoryText' in r.text,won and wave==6)
 def test_full_bag_does_not_advance_or_force_another_battle(self):
  for wave in range(1,7):
   r=Run(wave,full=True,retry=True).run('TrioGang_Hideout');self.assertEqual(r.vars['VAR_TRIO_GANG_WINS'],wave-1);self.assertEqual(r.vars['VAR_TRIO_GANG_PHASE'],2);self.assertIn('TrioGang_FullBagText',r.text)
   r=Run(7);r.vars.update({'VAR_TRIO_GANG_PHASE':2,'VAR_TRIO_GANG_WINS':wave-1,'VAR_0x8004':wave,'VAR_TRIO_SNACK_CHASE_STATE':3 if wave==1 else 4});r.run('TrioGang_ReclaimOnEntry');self.assertEqual(r.battle,[]);self.assertEqual(r.vars['VAR_TRIO_GANG_WINS'],wave);self.assertFalse(r.locked)
 def test_map_callbacks_preserve_events_and_authoring(self):
  for city in STOPS:
   prefix='data/maps/'+city+'/';old=subprocess.check_output(['git','show',BASE+':'+prefix+'scripts.inc'],cwd=ROOT,text=True);now=(ROOT/(prefix+'scripts.inc')).read_text()
   self.assertNotIn('VAR_TEMP_B',old)
   stripped=now.replace('\tmap_script MAP_SCRIPT_ON_FRAME_TABLE, TrioGang_OnFrame\n','').replace('\tspecial TrioGang_PrepareAmbush\n','');self.assertEqual(stripped,old)
   self.assertIn('map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters',now)
   oldmap=json.loads(subprocess.check_output(['git','show',BASE+':'+prefix+'map.json'],cwd=ROOT));newmap=json.loads((ROOT/(prefix+'map.json')).read_text())
   self.assertEqual(newmap['coord_events'],oldmap['coord_events'])
   if city=='Route37':self.assertEqual(newmap,oldmap)
   else:
    self.assertEqual(newmap['object_events'][:-1],oldmap['object_events'])
    self.assertEqual(newmap['object_events'][-1]['script'],'TrioGang_Hideout')
    helper=(ROOT/'src/trio_snack_chase.c').read_text()
    mapname=newmap['id'];self.assertRegex(helper,rf'MAP_NUM\({mapname}\), \w+, {len(newmap["object_events"])}'+r'\}')
    self.assertEqual(newmap['object_events'][-1]['flag'],'FLAG_HIDE_TRIO_GANG_HIDEOUT')
    self.assertEqual(newmap['object_events'][-1]['trainer_type'],'TRAINER_TYPE_NONE')
    self.assertEqual({k:v for k,v in newmap.items() if k!='object_events'},{k:v for k,v in oldmap.items() if k!='object_events'})
   p=ROOT/(prefix+'scripts.pory')
   if p.exists():
    raw=p.read_text().split('raw `',1)[1].split('`',1)[0].strip();self.assertTrue(now.strip().startswith(raw))
  for wave in range(1,8):self.assertIn(f'map_script_2 VAR_TEMP_B, {wave}, TrioGang_',SOURCE)
 def test_hideouts_do_not_disconnect_paths_or_block_events(self):
  from gang_geometry import geometry
  cases=[]
  for city in STOPS:
   m,w,h,walk=geometry(city)
   old=m['object_events'][:12] if city=='Route37' else m['object_events'][:-1]
   for npc in (m['object_events'][12:] if city=='Route37' else m['object_events'][-1:]):cases.append((city,m,walk,old,npc))
  for city,m,walk,old,npc in cases:
   pos=(npc['x'],npc['y'])
   occupied={(o['x'],o['y']) for o in old}
   events={(o['x'],o['y']) for k in ['warp_events','coord_events','bg_events'] for o in m[k]}
   self.assertTrue(walk(*pos));self.assertNotIn(pos,occupied|events)
   if city!='Route37':self.assertTrue(all(abs(pos[0]-x)+abs(pos[1]-y)>1 for x,y in events))
   def connected(start,blocked):
    seen={start};q=collections.deque(seen)
    while q:
     x,y=q.popleft()
     for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
      if p not in seen and p not in blocked and walk(*p):seen.add(p);q.append(p)
    return seen
   neighbors=[p for p in [(pos[0]+1,pos[1]),(pos[0]-1,pos[1]),(pos[0],pos[1]+1),(pos[0],pos[1]-1)] if p not in occupied and walk(*p)]
   self.assertGreaterEqual(len(neighbors),3)
   before=connected(neighbors[0],occupied);after=connected(neighbors[0],occupied|{pos})
   self.assertEqual(after,before-{pos},city)
   for x in range(pos[0]-10,pos[0]+11):
    for y in range(pos[1]-8,pos[1]+9):
     self.assertLessEqual(sum(abs(o['x']-x)<=10 and abs(o['y']-y)<=8 for o in old+[npc])+2,16,city)
 def test_blackout_and_puzzle_flag_protection(self):
  source=(ROOT/'src/battle_setup.c').read_text();body=source.split('static void CB2_EndTrainerBattle(void)\n{',1)[1].split('static void CB2_EndRematchBattle',1)[0]
  self.assertNotIn('TrioSnack_IsFriendlyBattle',source);self.assertNotIn('TrioGang_',body);self.assertIn('SetMainCallback2(CB2_WhiteOut)',body)
  self.assertIn('if (TrioGang_WaveForTrainer(TRAINER_BATTLE_PARAM.opponentA))\n        return;',source)
  for fn in ['SetTrainerFlag','ClearTrainerFlag']:
   self.assertIn(f'void {fn}(u16 trainerId)\n{{\n    if (TrioGang_WaveForTrainer(trainerId))\n        return;',source)
  self.assertNotRegex(SOURCE,r'\b(HealPlayerParty|FLAG_SYS_NO_CATCHING|FLAG_SYS_NO_WHITEOUT)\b')
 def test_parties_levels_labels_and_wrapped_text(self):
  party=(ROOT/'src/data/trainers.party').read_text();levels=[22,35,48,62,78,100]
  for wave in range(1,7):
   label='TRAINER_ROUTE37_SNACK_THIEF' if wave==1 else f'TRAINER_GREEDENT_GANG_{wave}';block=party.split('=== '+label+' ===',1)[1].split('===',1)[0];self.assertEqual(len(re.findall(r'^Greedent\b',block,re.M)),wave);self.assertEqual(re.findall(r'^Level: (\d+)',block,re.M),[str(levels[wave-1])]*wave)
  labels=collections.Counter()
  for p in list((ROOT/'data/maps').rglob('scripts.inc'))+list((ROOT/'data/scripts').glob('*.inc')):labels.update(re.findall(r'^(\w+)::?',p.read_text(),re.M))
  for key in LABELS:self.assertEqual(labels[key],1,key)
  for label,text in re.findall(r'^(\w+):\n\s*\.string "([^\n]+)"',SOURCE,re.M):
   self.assertTrue(text.endswith('$'));self.assertTrue(text.isascii())
   for page in text[:-1].split(r'\p'):
    lines=page.split(r'\n');self.assertLessEqual(len(lines),2);self.assertTrue(all(len(line)<=26 for line in lines),(label,lines))
if __name__=='__main__':unittest.main(verbosity=2)
