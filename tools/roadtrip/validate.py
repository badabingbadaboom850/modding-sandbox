#!/usr/bin/env python3
"""Execute actual island scripts and decode actual collision/behavior; not emulator QA."""
from pathlib import Path
import collections,itertools,json,re,struct,subprocess,sys,unittest
ROOT=Path(__file__).resolve().parents[2];BASE='24e87c19cbedc0cfec7b437c3e57ff2799b7a394'
S=(ROOT/'data/scripts/trio_roadtrip.inc').read_text();LABELS={};CODE=[]
for line in S.splitlines():
 line=line.strip()
 if not line or line.startswith(('@','.string')):continue
 if re.fullmatch(r'\w+::?',line):
  key=line.rstrip(':');assert key not in LABELS;LABELS[key]=len(CODE)
 else:CODE.append(line)
R='VAR_TRIO_ROAD_RIKO';B='VAR_TRIO_ROAD_BIJUU';P='VAR_TRIO_ROAD_PENNY';C='VAR_TRIO_ROAD_COMPLETE';G='VAR_TRIO_ROAD_SOUVENIR'
class Run:
 def __init__(self,r=0,b=0,p=0,c=0,answers=(),outcome=1,room=True,badges=True,members=3,port=0):
  self.vars={R:r,B:b,P:p,C:c,G:0,'VAR_TRIO_ROAD_RETURN':port};self.answers=iter(answers);self.outcome=outcome;self.room=room;self.badges=badges;self.members=members;self.port=port;self.lock=False;self.text=[];self.warps=[];self.battles=0;self.gifts=0;self.pictures=0;self.movements=[];self.heals=0;self.weather='WEATHER_NONE'
 def v(self,x):
  if x.startswith('VAR_'):return self.vars.get(x,0)
  return {'TRUE':1,'FALSE':0,'NO':0,'YES':1,'B_OUTCOME_WON':1}.get(x,int(x) if x.isdigit() else x)
 def run(self,name):
  pc=LABELS['TrioRoad_'+name];stack=[]
  for _ in range(1000):
   line=CODE[pc];pc+=1;op,_,rest=line.partition(' ');a=[x.strip() for x in rest.split(',')]
   if op=='end':return self
   if op=='return':
    if not stack:return self
    pc=stack.pop();continue
   if op=='lockall':self.lock=True;continue
   if op=='releaseall':self.lock=False;continue
   if op in ('faceplayer','closemessage','waitstate','waitmovement','doweather'):continue
   if op=='msgbox':
    self.text.append(a[0])
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=next(self.answers,1)
    continue
   if op=='dynmultichoice':self.vars['VAR_RESULT']=next(self.answers,127);continue
   if op=='setvar':self.vars[a[0]]=self.v(a[1]);continue
   if op=='applymovement':self.movements.append(tuple(a));continue
   if op=='showmonpic':self.pictures+=1;continue
   if op=='hidemonpic':self.pictures-=1;continue
   if op=='setweather':self.weather=a[0];continue
   if op=='warp':self.warps.append(tuple(a));continue
   if op=='giveitem':self.vars['VAR_RESULT']=int(self.room);self.gifts+=int(self.room);continue
   if op=='trainerbattle_no_intro':self.battles+=1;continue
   if op=='specialvar':self.vars[a[0]]=self.outcome if a[1]=='GetBattleOutcome' else self.members;continue
   if op=='special':
    if a[0]=='TrioRoad_RecordDeparture':self.vars['VAR_TRIO_ROAD_RETURN']=self.port;self.vars['VAR_TRIO_ROAD_VISITS']=min(3,self.vars.get('VAR_TRIO_ROAD_VISITS',0)+1)
    elif a[0]=='TrioRoad_RecordBattleWin':self.vars['VAR_TRIO_ROAD_BATTLES']=self.vars.get('VAR_TRIO_ROAD_BATTLES',0)|{'TRAINER_ROAD_BEACH':1,'TRAINER_ROAD_FOREST':2,'TRAINER_ROAD_SCOTT':4}[self.vars['VAR_0x8004']]
    else:raise AssertionError(line)
    continue
   target=a[-1];jump=False
   if op in ('goto','call'):jump=True
   elif op.startswith(('goto_if_','call_if_')):
    suffix=op.split('_if_')[1]
    if suffix in ('set','unset'):jump=self.badges==(suffix=='set')
    else:
     x,y=self.v(a[0]),self.v(a[1]);jump={'eq':x==y,'ne':x!=y,'ge':x>=y,'lt':x<y}[suffix]
   else:raise AssertionError(line)
   if jump:
    if target in ('TrioOutfit_Scott','TrioOutfit_ReactTown','TrioOutfit_Album'):continue
    if target=='Common_EventScript_OutOfCenterPartyHeal':self.heals+=1;continue
    if op.startswith('call'):stack.append(pc)
    pc=LABELS[target]
  raise AssertionError('script loop')
class Checks(unittest.TestCase):
 def test_fifth_badge_optional_departure_and_saved_ports(self):
  for badges,answer,port in itertools.product([False,True],[0,1],[0,1]):
   x=Run(r=3,b=2,p=2,answers=[answer],badges=badges,port=port).run('Entrance')
   self.assertEqual(bool(x.warps),badges and answer==1);self.assertFalse(x.lock);self.assertEqual((x.vars[R],x.vars[B],x.vars[P]),(3,2,2))
  for port in [0,1]:
   x=Run(port=port).run('Return');self.assertEqual(x.warps[0][0],'MAP_OLIVINE_CITY_PORT_OUTSIDE' if port else 'MAP_CIANWOOD_CITY');self.assertFalse(x.lock)
  self.assertFalse(Run(answers=[0]).run('Return').warps)
 def test_riko_wrong_turns_cancellation_reload_and_portrait(self):
  for state in range(5):
   for name in ['TrailOne','TrailTwo','Lookout']:
    x=Run(r=state,answers=[0 if name=='Lookout' else 127]).run(name);self.assertEqual(x.vars[R],state);self.assertFalse(x.lock)
  x=Run(answers=[1]).run('Tour');self.assertEqual(x.vars[R],1)
  self.assertEqual(Run(r=1,answers=[0]).run('TrailOne').vars[R],1)
  self.assertEqual(Run(r=1,answers=[1]).run('TrailOne').vars[R],2)
  self.assertEqual(Run(r=2,answers=[0]).run('TrailTwo').vars[R],2)
  self.assertEqual(Run(r=2,answers=[1]).run('TrailTwo').vars[R],3)
  x=Run(r=3).run('Lookout');self.assertEqual(x.vars[R],4);x.run('Lookout');self.assertEqual(x.vars[R],4)
  x.run('Photos');self.assertEqual(x.pictures,0);self.assertIn('TrioRoad_PhotoWoodlandText',x.text)
 def test_bijuu_sequential_clues_retries_and_reveal(self):
  steps=['GuardianRumor','FisherClue','Pawprints','Windchime']
  for state in range(4):
   for nextstep in steps[state+1:]:self.assertEqual(Run(b=state).run(nextstep).vars[B],state)
   self.assertEqual(Run(b=state).run(steps[state]).vars[B],state+1)
  for state in [0,3]:self.assertEqual(Run(b=state,answers=[0]).run(steps[state]).vars[B],state)
  for n in steps:self.assertEqual(Run(b=4).run(n).vars[B],4)
 def test_penny_weather_support_cabin_rest_and_reload(self):
  self.assertEqual(Run(answers=[0]).run('Picnic').vars[P],0)
  x=Run().run('Picnic');self.assertEqual(x.vars[P],1);self.assertEqual(x.weather,'WEATHER_RAIN');self.assertFalse(x.lock)
  for answer in [0,1,2]:self.assertEqual(Run(p=1,answers=[answer]).run('Penny').vars[P],2)
  for answer in [3,127]:self.assertEqual(Run(p=1,answers=[answer]).run('Penny').vars[P],1)
  self.assertEqual(Run(p=2,answers=[0]).run('Shelter').vars[P],2)
  self.assertEqual(Run(p=2).run('Shelter').vars[P],3)
  x=Run(p=3).run('Rest');self.assertEqual(x.vars[P],4);self.assertEqual(x.heals,1);self.assertFalse(x.lock)
  for state in range(5):
   x=Run(p=state).run('Weather');self.assertEqual(x.weather,'WEATHER_RAIN' if state in [1,2] else 'WEATHER_NONE');self.assertEqual(x.vars[P],state)
 def test_every_adventure_order_finishes_without_battles_and_replays(self):
  for order in itertools.permutations([R,B,P]):
   x=Run()
   for key in order:x.vars[key]=4
   x.run('Picnic');self.assertEqual(x.vars[C],1);self.assertEqual(x.battles,0);self.assertFalse(x.lock)
   before=dict(x.vars);x.run('Picnic');self.assertEqual(x.vars,before)
  for r,b,p in itertools.product(range(5),repeat=3):
   x=Run(r,b,p,answers=[0]).run('Picnic');self.assertEqual(x.vars[C],0)
  x=Run(4,4,4,answers=[0]).run('Picnic');self.assertEqual(x.vars[C],0)
 def test_exhibitions_optional_lost_replay_empty_egg_party_and_won_bits(self):
  for name,bit in [('BattleBeach',1),('BattleForest',2),('Scott',4)]:
   x=Run(answers=[0]).run(name);self.assertEqual(x.battles,0);self.assertFalse(x.lock)
   for members in [0,1]:self.assertEqual(Run(members=members).run(name).battles,0)
   for outcome in [1,2,3,4,5]:
    x=Run(outcome=outcome).run(name);self.assertEqual(x.battles,1);self.assertFalse(x.lock);self.assertEqual(x.vars.get('VAR_TRIO_ROAD_BATTLES',0),bit if outcome==1 else 0);self.assertEqual(x.vars[C],0)
    x.run(name);self.assertEqual(x.battles,2);self.assertEqual(x.vars.get('VAR_TRIO_ROAD_BATTLES',0),bit if outcome==1 else 0)
 def test_full_bag_souvenir_retry_and_inherited_menu_lock(self):
  x=Run(c=1,room=False).run('CabinScott');self.assertEqual(x.vars[G],0);self.assertEqual(x.gifts,0);self.assertFalse(x.lock)
  x.room=True;x.run('CabinScott');self.assertEqual(x.gifts,1);self.assertEqual(x.vars[G],1);x.run('CabinScott');self.assertEqual(x.gifts,1)
  x=Run(c=1,answers=[0]).run('CabinScott');self.assertEqual(x.gifts,0)
  for name in ['ReadMemory','ReadLetter','Checklist','PhotoPages']:
   for done in [0,1]:
    x=Run(4,4,4,done);x.lock=True;before=dict(x.vars);x.run(name);self.assertTrue(x.lock);self.assertEqual(x.vars,before);self.assertEqual(x.pictures,0)
 def test_geometry_approaches_warps_budget_and_existing_events(self):
  sys.path.insert(0,str(ROOT/'tools/snack'));from gang_geometry import geometry
  for name,entry in [('TrioRoadIsland',(18,24)),('TrioRoadWoods',(14,24)),('TrioRoadCove',(12,16)),('TrioRoadCabin',(4,7)),('CianwoodCity',(23,48)),('OlivineCity_PortOutside',(17,6))]:
   m,w,h,walk=geometry(name);occupied={(o['x'],o['y']) for o in m['object_events']};self.assertTrue(walk(*entry));self.assertNotIn(entry,occupied);seen={entry};q=collections.deque(seen)
   while q:
    x,y=q.popleft()
    for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
     if p not in seen|occupied and walk(*p):seen.add(p);q.append(p)
   objects=m['object_events'] if name.startswith('Trio') else m['object_events'][-1:]
   for o in objects:
    self.assertTrue(walk(o['x'],o['y']));self.assertTrue(any(p in seen for p in [(o['x']+1,o['y']),(o['x']-1,o['y']),(o['x'],o['y']+1),(o['x'],o['y']-1)]),o)
    # All potential visible templates, plus player/follower, fit 16 slots.
    for x in range(o['x']-10,o['x']+11):
     for y in range(o['y']-8,o['y']+9):self.assertLessEqual(sum(abs(v['x']-x)<=10 and abs(v['y']-y)<=8 for v in m['object_events'])+2,16,name)
   if name.startswith('Trio'):self.assertEqual(len(occupied),len(m['object_events']))
   else:
    old=json.loads(subprocess.check_output(['git','show',BASE+f':data/maps/{name}/map.json'],cwd=ROOT));self.assertEqual(m['object_events'][:-1],old['object_events']);self.assertEqual({k:v for k,v in m.items() if k!='object_events'},{k:v for k,v in old.items() if k!='object_events'})
  # Exact native building door and arrow behavior; adjacent arrival tiles are land.
  for name in ['TrioRoadIsland','TrioRoadWoods','TrioRoadCove','TrioRoadCabin']:self.assertIn('.include \"data/maps/'+name+'/scripts.inc\"',(ROOT/'data/event_scripts.s').read_text())
  layouts=json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts'];attrs=(ROOT/'data/tilesets/secondary/cianwood_city/metatile_attributes.bin').read_bytes()
  for name,x,y,behavior in [('TrioRoadIsland',28,9,0x69)]:
   m=json.loads((ROOT/f'data/maps/{name}/map.json').read_text());l=next(v for v in layouts if v['id']==m['layout']);b=struct.unpack('<%dH'%(l['width']*l['height']),(ROOT/l['blockdata_filepath']).read_bytes());id=b[y*l['width']+x]&2047;self.assertEqual(struct.unpack_from('<H',attrs,(id%1024)*2)[0]&255,behavior)
 def test_stable_saved_ids_references_text_and_callback_scope(self):
  for path,key in [('data/maps/map_groups.json','gMapGroup_IndoorCianwood'),('data/layouts/layouts.json','layouts')]:
   old=json.loads(subprocess.check_output(['git','show',BASE+':'+path],cwd=ROOT));new=json.loads((ROOT/path).read_text());self.assertEqual(new[key][:len(old[key])],old[key])
  for path in ['include/constants/species.h','include/constants/items.h','include/constants/flags.h','include/global.h','include/constants/game_stat.h']:
   self.assertEqual((ROOT/path).read_bytes(),subprocess.check_output(['git','show',BASE+':'+path],cwd=ROOT))
  labels=collections.Counter()
  for p in list((ROOT/'data/maps').rglob('scripts.inc'))+list((ROOT/'data/scripts').glob('*.inc')):labels.update(re.findall(r'^(\w+)::?',p.read_text(),re.M))
  for key in LABELS:self.assertEqual(labels[key],1,key)
  for ref in re.findall(r'\bTrioRoad_\w+\b',S):
   if ref in ['TrioRoad_RecordDeparture','TrioRoad_RecordBattleWin']:self.assertIn('def_special '+ref,(ROOT/'data/specials.inc').read_text())
   else:self.assertIn(ref,LABELS)
  for text in re.findall(r'\.string "([^\n]*)"',S):
   self.assertTrue(text.isascii());self.assertTrue(text.endswith('$'))
   for page in text[:-1].split(r'\p'):
    lines=page.split(r'\n');self.assertLessEqual(len(lines),2);self.assertTrue(all(len(x)<=26 for x in lines),lines)
  setup=(ROOT/'src/battle_setup.c').read_text();tail=setup.split('static void CB2_EndTrainerBattle(void)\n{')[1].split('static void CB2_EndRematchBattle')[0]
  self.assertLess(tail.index('TrioRoad_IsFriendlyBattle'),tail.index('CB2_WhiteOut'));self.assertIn('HealPlayerParty();',tail.split('TrioRoad_IsFriendlyBattle')[1].split('// Festival')[0]);self.assertNotRegex(S,r'\b(FLAG_SYS_NO_CATCHING|FLAG_SYS_NO_WHITEOUT|setrespawn|setflag)\b')
if __name__=='__main__':unittest.main(verbosity=2)
