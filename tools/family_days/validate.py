#!/usr/bin/env python3
"""Actual event-script execution and native-map geometry; not a rendered playtest."""
from pathlib import Path
import collections,itertools,json,re,struct,subprocess,sys,unittest
ROOT=Path(__file__).resolve().parents[2]
BASE='c8cf449076faca7b2531fa8338b882682a525706'
S=(ROOT/'data/scripts/trio_family_days.inc').read_text()+'\n'+(ROOT/'data/maps/TrioHomecoming/scripts.inc').read_text()
LABELS={};CODE=[]
for line in S.splitlines():
 line=line.strip()
 if not line or line.startswith(('@','.string','.byte','map_script ')):continue
 if re.fullmatch(r'\w+::?',line):
  key=line.rstrip(':');assert key not in LABELS;LABELS[key]=len(CODE)
 else:CODE.append(line)
D='VAR_TRIO_DINNER_STATE';A='VAR_TRIO_RADIO_STATE';H='VAR_TRIO_HOMECOMING_STATE';G='VAR_TRIO_HOME_GIFTS';DR='VAR_TRIO_DINNER_REWARD';HR='VAR_TRIO_HOME_REWARD'
class Run:
 def __init__(self,vars=None,flags=(),answers=(),room=True,locked=False):
  self.vars=dict(vars or {});self.flags=set(flags);self.answers=iter(answers);self.room=room;self.lock=locked;self.text=[];self.warps=[];self.gifts=0;self.pictures=0;self.heals=0
 def v(self,x):
  if x.startswith('VAR_'):return self.vars.get(x,0)
  return {'TRUE':1,'FALSE':0,'NO':0,'YES':1}.get(x,int(x) if x.isdigit() else x)
 def run(self,name):
  pc=LABELS[name];stack=[]
  for _ in range(1000):
   line=CODE[pc];pc+=1;op,_,rest=line.partition(' ');a=[x.strip() for x in rest.split(',')]
   if op=='end':return self
   if op=='return':
    if not stack:return self
    pc=stack.pop();continue
   if op in ('lockall','lock'):self.lock=True;continue
   if op in ('releaseall','release'):self.lock=False;continue
   if op in ('faceplayer','closemessage','waitstate','waitbuttonpress'):continue
   if op=='msgbox':
    self.text.append(a[0])
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=next(self.answers,1)
    continue
   if op=='dynmultichoice':self.vars['VAR_RESULT']=next(self.answers,127);continue
   if op=='setvar':self.vars[a[0]]=self.v(a[1]);continue
   if op=='copyvar':self.vars[a[0]]=self.v(a[1]);continue
   if op=='setflag':self.flags.add(a[0]);continue
   if op=='clearflag':self.flags.discard(a[0]);continue
   if op=='showmonpic':self.pictures+=1;continue
   if op=='hidemonpic':self.pictures-=1;continue
   if op=='warp':self.warps.append(tuple(a));continue
   if op=='giveitem':self.vars['VAR_RESULT']=int(self.room);self.gifts+=int(self.room);continue
   if op=='special':assert a[0]=='BufferTrioFamilyRadio';continue
   target=a[-1];jump=False
   if op in ('goto','call'):jump=True
   elif op.startswith(('goto_if_','call_if_')):
    suffix=op.split('_if_')[1]
    if suffix in ('set','unset'):jump=(a[0] in self.flags)==(suffix=='set')
    else:
     x,y=self.v(a[0]),self.v(a[1]);jump={'eq':x==y,'ne':x!=y,'ge':x>=y,'lt':x<y}[suffix]
   else:raise AssertionError(line)
   if jump:
    if target=='TrioOutfit_Scott':continue
    if target=='Common_EventScript_OutOfCenterPartyHeal':self.heals+=1;continue
    if op.startswith('call'):stack.append(pc)
    pc=LABELS[target]
  raise AssertionError('script loop')
class Checks(unittest.TestCase):
 def test_dinner_gate_decline_takeover_and_progress_retention(self):
  for badge,takeover,answer in itertools.product([False,True],[False,True],[0,1]):
   flags=(['FLAG_BADGE04_GET'] if badge else [])+(['FLAG_HIDE_GOLDENROD_NPCS'] if takeover else [])
   x=Run({D:3},flags,[answer]).run('FamilyDinner_Entrance')
   self.assertEqual(bool(x.warps),badge and not takeover and bool(answer));self.assertEqual(x.vars[D],3);self.assertFalse(x.lock)
  x=Run(flags=['FLAG_BADGE04_GET']).run('FamilyDinner_Entrance');self.assertEqual(x.vars[D],1)
 def test_dinner_clues_cancel_wrong_answers_and_resume(self):
  for state in range(1,5):
   for who in ['Riko','Bijuu','Penny']:
    x=Run({D:state},answers=[127 if who=='Riko' else 0]).run('FamilyDinner_'+who);self.assertEqual(x.vars[D],state);self.assertFalse(x.lock)
  x=Run({D:1},answers=[0]).run('FamilyDinner_Riko');self.assertEqual(x.vars[D],1)
  x=Run({D:1},answers=[1]).run('FamilyDinner_Riko');self.assertEqual(x.vars[D],2)
  for state,who in [(2,'Bijuu'),(3,'Penny')]:self.assertEqual(Run({D:state}).run('FamilyDinner_'+who).vars[D],state+1)
  self.assertEqual(Run({D:2}).run('FamilyDinner_Penny').vars[D],2)
  self.assertEqual(Run({D:3}).run('FamilyDinner_Scott').vars[D],3)
 def test_dinner_completion_full_bag_and_repeat_without_duplicate_reward(self):
  x=Run({D:4},room=False).run('FamilyDinner_Scott');self.assertEqual(x.vars[D],5);self.assertEqual(x.vars.get(DR,0),0);self.assertEqual(x.heals,1)
  x.room=True;x.answers=iter([0,1]);x.run('FamilyDinner_Scott');self.assertEqual(x.vars[DR],1);self.assertEqual(x.gifts,1)
  x.answers=iter([1]);x.run('FamilyDinner_Scott');self.assertEqual(x.gifts,1);self.assertFalse(x.lock)
  x=Run({D:4},answers=[0]).run('FamilyDinner_Scott');self.assertEqual(x.vars[D],4)
 def test_radio_offer_respects_quiz_badge_takeover_and_parent_lock(self):
  for quiz,badge,takeover,answer in itertools.product([False,True],repeat=4):
   flags=(['FLAG_ENABLE_RADIO'] if quiz else [])+(['FLAG_BADGE03_GET'] if badge else [])+(['FLAG_HIDE_GOLDENROD_NPCS'] if takeover else [])
   x=Run(flags=flags,answers=[int(answer)],locked=True).run('FamilyRadio_Offer');travel=quiz and badge and not takeover and answer
   self.assertEqual(bool(x.warps),travel);self.assertEqual(x.lock,not travel);self.assertNotIn(A,x.vars)
 def test_radio_preparation_recording_cancel_and_all_listening_options(self):
  for state in range(4):
   for who in ['Riko','Bijuu','Penny']:
    x=Run({A:state},answers=[0]).run('FamilyRadio_'+who);self.assertEqual(x.vars[A],state);self.assertFalse(x.lock)
  for state,who in enumerate(['Riko','Bijuu','Penny']):self.assertEqual(Run({A:state}).run('FamilyRadio_'+who).vars[A],state+1)
  self.assertEqual(Run({A:3},answers=[0]).run('FamilyRadio_Host').vars[A],3)
  for selection in [0,1,2,3,4,127]:
   x=Run({A:3},answers=[1,selection]).run('FamilyRadio_Host');self.assertEqual(x.vars[A],4);self.assertFalse(x.lock)
   if selection<4:self.assertEqual(x.vars['VAR_0x8004'],selection)
  self.assertEqual(Run({A:4},answers=[127]).run('FamilyRadio_Host').vars[A],4)
 def test_home_gate_clue_order_choices_reload_and_full_bag(self):
  for badge,answer in itertools.product([False,True],[0,1]):
   x=Run({G:2},flags=['FLAG_BADGE07_GET'] if badge else [],answers=[answer],locked=True).run('FamilyHome_Offer');travel=badge and answer
   self.assertEqual(bool(x.warps),bool(travel));self.assertEqual(x.vars[G],2);self.assertEqual(x.lock,not bool(travel))
  for stage,who in enumerate(['Riko','Bijuu','Penny']):
   self.assertEqual(Run({G:stage},answers=[0]).run('FamilyHome_Gift'+who).vars[G],stage)
   self.assertEqual(Run({G:stage}).run('FamilyHome_Gift'+who).vars[G],stage+1)
  self.assertEqual(Run({G:0}).run('FamilyHome_GiftPenny').vars[G],0)
  x=Run({G:3},room=False).run('FamilyHome_Mom');self.assertEqual(x.vars[H],1);self.assertEqual(x.vars.get(HR,0),0)
  x.room=True;x.answers=iter([0,1]);x.run('FamilyHome_Mom');self.assertEqual(x.vars[HR],1);x.answers=iter([1]);x.run('FamilyHome_Mom');self.assertEqual(x.gifts,1)
 def test_earned_decorations_callbacks_and_read_only_memories(self):
  for garden,festival,road in itertools.product([False,True],repeat=3):
   vars={'VAR_TRIO_GARDEN_STATE':5 if garden else 0,'VAR_TRIO_ROAD_COMPLETE':int(road)};flags=['FLAG_TRIO_FESTIVAL_PICNIC'] if festival else []
   x=Run(vars,flags).run('FamilyHome_Decor');self.assertEqual(x.vars,vars)
   for flag,shown in zip(['FLAG_TEMP_1','FLAG_TEMP_2','FLAG_TEMP_3'],[garden,festival,road]):self.assertEqual(flag not in x.flags,shown)
   x.run('FamilyHome_Callbacks');self.assertEqual('FamilyHome_GardenText' in x.text,garden);self.assertEqual('FamilyHome_RoadText' in x.text,road)
  for dinner,radio,home in itertools.product([False,True],repeat=3):
   vars={D:5 if dinner else 0,A:4 if radio else 0,H:int(home)};x=Run(vars,locked=True).run('FamilyDays_ReadMemories');self.assertTrue(x.lock);self.assertEqual(x.vars,vars)
   x.run('FamilyDays_Checklist');self.assertTrue(x.lock);self.assertEqual(x.vars,vars)
   self.assertEqual('FamilyDinner_ChecklistSaved' in x.text,dinner);self.assertEqual('FamilyRadio_ChecklistSaved' in x.text,radio);self.assertEqual('FamilyHome_ChecklistSaved' in x.text,home)
   self.assertEqual('FamilyDinner_ReadMemoryText' in x.text,dinner);self.assertEqual('FamilyRadio_ReadMemoryText' in x.text,radio);self.assertEqual('FamilyHome_ReadMemoryText' in x.text,home)
  for photo in ['GardenPhoto','RoadPhoto']:self.assertEqual(Run().run('FamilyHome_'+photo).pictures,0)
 def test_real_geometry_native_exits_and_viewport_limits(self):
  sys.path.insert(0,str(ROOT/'tools/snack'));from gang_geometry import geometry
  for name,entry in [('TrioDinnerDate',(3,7)),('TrioRadioStudio',(4,7)),('TrioHomecoming',(9,7)),('GoldenrodCity',(16,24))]:
   m,w,h,walk=geometry(name);occ={(o['x'],o['y']) for o in m['object_events']};seen={entry};q=collections.deque(seen);self.assertTrue(walk(*entry));self.assertNotIn(entry,occ)
   while q:
    x,y=q.popleft()
    for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
     if p not in seen|occ and walk(*p):seen.add(p);q.append(p)
   for o in m['object_events'] if name.startswith('Trio') else m['object_events'][-1:]:
    x,y=o['x'],o['y'];self.assertTrue(walk(x,y),(name,o));self.assertTrue(any(p in seen for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]),(name,o))
    for cx in range(x-10,x+11):
     for cy in range(y-8,y+9):self.assertLessEqual(sum(abs(v['x']-cx)<=10 and abs(v['y']-cy)<=8 for v in m['object_events'])+2,16,name)
   if name.startswith('Trio'):
    self.assertEqual(len(occ),len(m['object_events']));warp=m['warp_events'][0];original={'TrioDinnerDate':'OlivineCity_Cafe','TrioRadioStudio':'TrioMirrorHouse','TrioHomecoming':'NewBarkTown_PlayersHouse_1F'}[name];native=json.loads((ROOT/f'data/maps/{original}/map.json').read_text());self.assertEqual(m['layout'],native['layout']);self.assertEqual((warp['x'],warp['y']),(native['warp_events'][0]['x'],native['warp_events'][0]['y']));self.assertTrue(any(p in seen for p in [(warp['x']+1,warp['y']),(warp['x']-1,warp['y']),(warp['x'],warp['y']-1)]))
 def test_historical_ids_original_events_hook_parity_and_text(self):
  old=json.loads(subprocess.check_output(['git','show',BASE+':data/maps/map_groups.json'],cwd=ROOT));new=json.loads((ROOT/'data/maps/map_groups.json').read_text())
  for group in old['group_order']:self.assertEqual(new[group][:len(old[group])],old[group])
  for path in ['data/layouts/layouts.json','include/global.h','include/constants/items.h','include/constants/species.h','include/constants/flags.h','src/new_game.c']:
   prior=subprocess.check_output(['git','show',BASE+':'+path],cwd=ROOT)
   if path in ['include/constants/species.h','include/constants/items.h']:
    # Later authorized forms/items append IDs; preserve every historical real ID.
    prefix='SPECIES_' if 'species.h' in path else 'ITEM_';current=(ROOT/path).read_text()
    for name,value in re.findall(r'(?:#define\s+|\b)('+prefix+r'\w+)\s*(?:=|\s)\s*(\d+)\b',prior.decode()):
     self.assertRegex(current,r'\b'+name+r'\s*(?:=|\s)\s*'+value+r'\b',name)
   else:self.assertEqual((ROOT/path).read_bytes(),prior)
  for name in ['GoldenrodCity','GoldenrodCity_RadioTower_1F','NewBarkTown_PlayersHouse_1F']:
   m=json.loads((ROOT/f'data/maps/{name}/map.json').read_text());o=json.loads(subprocess.check_output(['git','show',BASE+f':data/maps/{name}/map.json'],cwd=ROOT))
   if name=='GoldenrodCity':m['object_events']=m['object_events'][:-1]
   self.assertEqual(m,o)
  for ext in ['inc','pory']:self.assertIn('msgbox RadioTower1F_Text_Lass, MSGBOX_DEFAULT\n\tcall FamilyRadio_Offer',(ROOT/f'data/maps/GoldenrodCity_RadioTower_1F/scripts.{ext}').read_text())
  alltext='\n'.join(p.read_text() for p in list((ROOT/'data/scripts').glob('*.inc'))+list((ROOT/'data/maps').rglob('scripts.inc')));labels=collections.Counter(re.findall(r'^(\w+)::?',alltext,re.M))
  for label in LABELS:self.assertEqual(labels[label],1,label)
  for txt in re.findall(r'\.string "([^\n]*)"',S):
   self.assertTrue(txt.endswith('$'));self.assertTrue(txt.isascii())
   for page in txt[:-1].split(r'\p'):
    rows=page.split(r'\n');self.assertLessEqual(len(rows),2);self.assertTrue(all(len(l)<=26 for l in rows),rows)
  self.assertNotRegex(S,r'\b(trainerbattle|removeitem|setrespawn|setflag FLAG_BADGE)\b')
  radio=(ROOT/'src/pokegear_radio.c').read_text();self.assertIn('{ 52, RADIO_STATION_TRIO',radio);self.assertIn('AddRadioTopic(TrioFamilyRadio_GetTopic(Random() % 4))',radio)
if __name__=='__main__':unittest.main(verbosity=2)
