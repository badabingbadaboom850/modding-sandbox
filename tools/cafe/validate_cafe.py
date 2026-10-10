#!/usr/bin/env python3
"""Execute actual cafe assembly with stubs and check native geometry, not rendered playtesting."""
import collections,json,re,struct,subprocess,sys,unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
BASE='d7894d87f7e4d2309d7a7bcb52baf2ae814a1d70'
SOURCE=(ROOT/'data/maps/TrioGreedentCafe/scripts.inc').read_text()
LABELS={};CODE=[]
for line in SOURCE.splitlines():
 line=line.strip()
 if not line or line.startswith('@'):continue
 if re.fullmatch(r'\w+::?',line):
  assert line.rstrip(':') not in LABELS;LABELS[line.rstrip(':')]=len(CODE)
 else:CODE.append(line)
class Run:
 def __init__(self,state=0,answer=1,full=False):
  self.vars={'VAR_TRIO_CAFE_DELIVERY_STATE':state,'VAR_TRIO_GANG_WINS':0,'VAR_TRIO_GANG_PHASE':1,'VAR_TRIO_GANG_ACTIVE_WAVE':6};self.flags=set();self.answer=answer;self.full=full;self.gifts=[];self.warps=[];self.text=[];self.lock=False;self.shops=[]
 def val(self,x):return int(x) if x.isdigit() else self.vars.get(x,{'YES':1,'NO':0,'TRUE':1,'FALSE':0}.get(x,x))
 def run(self,label):
  pc=LABELS[label];stack=[]
  for _ in range(300):
   op,_,rest=CODE[pc].partition(' ');pc+=1;a=[x.strip() for x in rest.split(',')]
   if op in ['end','return']:
    if stack:pc=stack.pop()
    else:return self
   elif op=='lockall':self.lock=True
   elif op=='releaseall':self.lock=False
   elif op in ['faceplayer','closemessage','waitstate']:pass
   elif op=='call':stack.append(pc);pc=LABELS[a[0]]
   elif op=='msgbox':
    self.text.append(a[0])
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=self.answer
   elif op=='giveitem':
    self.vars['VAR_RESULT']=int(not self.full)
    if not self.full:self.gifts.append((a[0],int(a[1])))
   elif op=='pokemart':self.shops.append(a[0])
   elif op=='warp':self.warps.append(a)
   elif op=='setvar':self.vars[a[0]]=self.val(a[1])
   elif op=='setflag':self.flags.add(a[0])
   elif op=='goto':pc=LABELS[a[0]]
   elif op=='goto_if_eq':
    if self.val(a[0])==self.val(a[1]):pc=LABELS[a[2]]
   elif op=='goto_if_set':
    if a[0] in self.flags:pc=LABELS[a[1]]
   else:raise AssertionError(op)
  raise AssertionError('loop')
class Checks(unittest.TestCase):
 def test_parcels_once_per_visit_decline_full_bag_and_retry(self):
  for state,item,count in [(0,'ITEM_POTION',3),(2,'ITEM_RIKO_PUFFS',3),(4,'ITEM_LEFTOVERS',1)]:
   for answer,full in [(0,False),(1,True),(1,False)]:
    r=Run(state,answer,full).run('TrioCafe_Courier');success=answer and not full
    self.assertEqual(r.gifts,[(item,count)] if success else []);self.assertEqual(r.vars['VAR_TRIO_CAFE_DELIVERY_STATE'],state+1 if success else state);self.assertFalse(r.lock)
    before=len(r.gifts);r.run('TrioCafe_Courier');self.assertEqual(len(r.gifts),before)
   r=Run(state,full=True).run('TrioCafe_Courier');r.full=False;r.run('TrioCafe_Courier');self.assertEqual(r.gifts,[(item,count)])
 def test_return_visits_advance_but_cafe_reload_does_not(self):
  for state in range(6):
   r=Run(state).run('TrioCafe_OnTransition');self.assertEqual(r.vars['VAR_TRIO_CAFE_DELIVERY_STATE'],state)
   r.run('TrioCafe_AfterExit');expected={1:2,3:4}.get(state,state);self.assertEqual(r.vars['VAR_TRIO_CAFE_DELIVERY_STATE'],expected)
   r.run('TrioCafe_AfterExit');self.assertEqual(r.vars['VAR_TRIO_CAFE_DELIVERY_STATE'],expected)
  for town,label in [('VermilionCity','VermilionCity_MapScript_OnTransition::')]:
   s=(ROOT/f'data/maps/{town}/scripts.inc').read_text();self.assertIn(label+'\n\tcall TrioCafe_AfterExit',s)
 def test_release_host_and_retired_test_paths(self):
  for mode in [0,1]:
   for answer in [0,1]:
    r=Run(answer=answer);r.vars['VAR_TRIO_CAFE_TEST_RETURN']=mode
    before={k:v for k,v in r.vars.items() if 'GANG' in k};r.run('TrioCafe_Host');self.assertFalse(r.lock)
    self.assertEqual(r.warps,[['MAP_VERMILION_CITY','38','23']] if answer else [])
    self.assertEqual({k:v for k,v in r.vars.items() if 'GANG' in k},before)
  for file in ['scripts.inc','scripts.pory']:
   s=(ROOT/f'data/maps/NewBarkTown/{file}').read_text()
   self.assertIn('msgbox NewBarkTown_Text_PlayersHouse, MSGBOX_SIGN',s)
   self.assertNotIn('TrioCafe_TestOffer',s);self.assertNotIn('TrioCafe_AfterExit',s)
  for bad in ['TrioCafe_TestOffer','TrioCafe_TestText','TrioCafe_ReturnNewBark','VAR_TRIO_CAFE_TEST_RETURN']:
   self.assertNotIn(bad,SOURCE)
  self.assertNotIn('VAR_TRIO_CAFE_TEST_RETURN',(ROOT/'src/overworld.c').read_text())
  home=(ROOT/'data/maps/NewBarkTown_PlayersHouse_1F/scripts.inc').read_text()
  self.assertNotIn('TestSupplies',home)
  friend=home.split('NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend::')[1].split('NewBarkTown_PlayersHouse_1F_MomEventScript_GoodLuck::')[0]
  self.assertNotIn('giveitem',friend)
  fresh=(ROOT/'src/new_game.c').read_text()
  self.assertNotIn('AddBagItem(ITEM_MEGA_RING',fresh);self.assertNotIn('AddBagItem(ITEM_BONDSTONE',fresh)
  debug=(ROOT/'include/config/debug.h').read_text()
  for setting in ['DEBUG_OVERWORLD_MENU','DEBUG_BATTLE_MENU','DEBUG_POKEMON_SPRITE_VISUALIZER']:
   self.assertRegex(debug,rf'#define {setting}\s+FALSE')
 def test_intro_memory_and_shop_do_not_change_cartel_or_party(self):
  r=Run().run('TrioCafe_OnTransition').run('TrioCafe_Introduction');self.assertIn('FLAG_TRIO_CAFE_VISITED',r.flags);self.assertFalse(r.lock)
  r.run('TrioCafe_OnTransition');self.assertEqual(r.vars['VAR_TEMP_A'],0)
  self.assertIn('call_if_set FLAG_TRIO_CAFE_VISITED, TrioCafe_ReadMemory',(ROOT/'data/scripts/trio_memories.inc').read_text())
  for bad in ['trainerbattle','addpokemon','setrespawn','FLAG_BADGE','setvar VAR_TRIO_GANG','setvar VAR_TRIO_SNACK']:self.assertNotIn(bad,SOURCE)
  r.run('TrioCafe_Shop');self.assertEqual(r.shops,['TrioCafe_Stock']);self.assertFalse(r.lock)
 def test_geometry_all_actors_and_native_exit_reachable(self):
  sys.path.insert(0,str(ROOT/'tools/snack'));from gang_geometry import geometry
  m,w,h,walk=geometry('TrioGreedentCafe');self.assertEqual((w,h),(8,10));self.assertEqual(len(m['object_events']),9)
  self.assertTrue(all(a['graphics_id']=='OBJ_EVENT_GFX_SPECIES(GREEDENT)' for a in m['object_events'][:6]))
  actors={(a['x'],a['y']) for a in m['object_events']};self.assertEqual(len(actors),9);self.assertNotIn((3,7),actors);self.assertTrue(walk(3,7))
  reachable={(3,7)};q=collections.deque(reachable)
  while q:
   x,y=q.popleft()
   for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
    if p not in reachable and p not in actors and walk(*p):reachable.add(p);q.append(p)
  for a in m['object_events']:
   x,y=a['x'],a['y'];self.assertEqual(a['trainer_type'],'TRAINER_TYPE_NONE')
   self.assertTrue(any(p in reachable for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]) or (a['script']=='TrioCafe_Shop' and (x-2,y) in reachable),a['script'])
  layout=next(l for l in json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts'] if l['id']==m['layout'])
  headers=(ROOT/'src/data/tilesets/headers.h').read_text();metatiles=(ROOT/'src/data/tilesets/metatiles.h').read_text()
  body=headers.split('const struct Tileset '+layout['secondary_tileset']+' =')[1].split('};')[0]
  name=re.search(r'\.metatileAttributes = (\w+)',body).group(1);path=re.search(name+r'\[\] = INCBIN_U16\("([^"]+)',metatiles).group(1)
  attributes=(ROOT/path).read_bytes();self.assertEqual(struct.unpack_from('<H',attributes,0x67*2)[0]&255,0x80);self.assertEqual(struct.unpack_from('<H',attributes,0x56*2)[0]&255,0x65)
  original=json.loads((ROOT/'data/maps/OlivineCity_Cafe/map.json').read_text());self.assertEqual([(x['x'],x['y']) for x in m['warp_events']],[(x['x'],x['y']) for x in original['warp_events']]);self.assertIn((3,7),reachable)
  city=json.loads((ROOT/'data/maps/VermilionCity/map.json').read_text());self.assertEqual(city['warp_events'][7]['dest_map'],'MAP_VERMILION_CITY_HOUSE3')
  self.assertEqual(m['warp_events'][0]['dest_warp_id'],'7')
 def test_registration_ids_parity_text_and_allocations(self):
  self.assertEqual((ROOT/'data/maps/TrioGreedentCafe/scripts.pory').read_text().split('`')[1].strip(),SOURCE.strip())
  self.assertIn('data/maps/TrioGreedentCafe/scripts.inc',(ROOT/'data/event_scripts.s').read_text())
  old=json.loads(subprocess.check_output(['git','show',BASE+':data/maps/map_groups.json'],cwd=ROOT));new=json.loads((ROOT/'data/maps/map_groups.json').read_text());self.assertEqual(new['gMapGroup_IndoorVermilion'][:-1],old['gMapGroup_IndoorVermilion'])
  self.assertEqual({k:v for k,v in new.items() if k!='gMapGroup_IndoorVermilion'},{k:v for k,v in old.items() if k!='gMapGroup_IndoorVermilion'})
  for text in re.findall(r'\.string "(.*)"',SOURCE):
   self.assertTrue(text.endswith('$'))
   for page in text[:-1].split(r'\p'):
    lines=page.split(r'\n');self.assertLessEqual(len(lines),2)
    for line in lines:self.assertLessEqual(len(line),26,line)
  for ref in re.findall(r'\bTrioCafe_\w+\b',SOURCE):self.assertIn(ref,LABELS)
  for name,value in [('VAR_TRIO_CAFE_TEST_RETURN','0x412F'),('VAR_TRIO_CAFE_DELIVERY_STATE','0x4130'),('FLAG_TRIO_CAFE_VISITED','0x108F')]:
   header=ROOT/('include/constants/vars.h' if name.startswith('VAR') else 'include/constants/flags.h');self.assertRegex(header.read_text(),rf'#define {name}\s+{value}')
if __name__=='__main__':unittest.main()
