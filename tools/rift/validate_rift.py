#!/usr/bin/env python3
"""Execute actual Rift scripts with engine stubs, and decode collision geometry.
This is source simulation, not rendered emulator confirmation.
"""
from pathlib import Path
import collections,json,re,struct,subprocess,unittest
ROOT=Path(__file__).resolve().parents[2]
S=(ROOT/'data/maps/TrioEchoWoods/scripts.inc').read_text()
LABELS={};CODE=[]
for line in S.splitlines():
 line=line.strip()
 if not line or line.startswith('@'):continue
 if re.fullmatch(r'\w+::?',line):
  name=line.rstrip(':');assert name not in LABELS,name;LABELS[name]=len(CODE)
 else:CODE.append(line)
STATE='VAR_TRIO_RIFT_RIKO_STATE'
BASE=list(struct.unpack('<720H',(ROOT/'data/layouts/TrioEchoWoods/map.bin').read_bytes()))
MAP=json.loads((ROOT/'data/maps/TrioEchoWoods/map.json').read_text())
class Run:
 def __init__(self,state=0,flags=(),girls=True,answers=(),outcomes=(),room=True,forms=()):
  self.vars={STATE:state};self.flags=set(flags);self.girls=girls;self.answers=iter(answers);self.outcomes=iter(outcomes);self.room=room;self.forms=set(forms);self.blocks=BASE.copy();self.battles=0;self.gifts=0;self.warps=[];self.locked=False;self.text=[];self.last_outcome=1
 def value(self,v):
  if v.startswith('VAR_'):return self.vars.get(v,0)
  return {'TRUE':1,'FALSE':0,'YES':1,'NO':0,'B_OUTCOME_WON':1}.get(v,int(v,0) if re.fullmatch(r'(\d+|0x[\da-fA-F]+)',v) else v)
 def run(self,name):
  pc=LABELS['TrioRift_'+name];stack=[]
  for _ in range(1000):
   op,_,args=CODE[pc].partition(' ');pc+=1;a=[v.strip() for v in args.split(',')]
   if op=='end':return self
   if op=='return':
    if not stack:return self
    pc=stack.pop();continue
   if op=='lockall':self.locked=True;continue
   if op=='releaseall':self.locked=False;continue
   if op in ('faceplayer','closemessage','waitstate','playmoncry','waitmoncry'):continue
   if op=='msgbox':
    self.text.append(a[0])
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=next(self.answers,1)
    continue
   if op=='setvar':self.vars[a[0]]=self.value(a[1]);continue
   if op=='checkspecies':self.vars['VAR_RESULT']=int(a[0] in self.forms);continue
   if op=='warp':self.warps.append(tuple(a));continue
   if op=='giveitem':
    self.vars['VAR_RESULT']=int(self.room);self.gifts+=int(self.room);continue
   if op=='setmetatile':
    x,y=int(a[0]),int(a[1]);self.blocks[y*24+x]=(self.blocks[y*24+x]&0xf000)|int(a[2],0)|(0x800 if self.value(a[3]) else 0);continue
   if op=='special':
    if a[0]=='BattleSetup_StartTrioSpiritTrial':self.battles+=1;self.last_outcome=next(self.outcomes,1)
    else:assert a[0]=='DrawWholeMapView',a
    continue
   if op=='specialvar':self.vars[a[0]]=int(self.girls) if a[1]=='PrepareTrioSpiritTrial' else self.last_outcome;continue
   target=a[-1];jump=False
   if op in ('goto','call'):jump=True
   elif op.startswith(('goto_if_','call_if_')):
    suffix=op.split('_if_')[1]
    if suffix in ('set','unset'):jump=(a[0] in self.flags)==(suffix=='set')
    else:
     x,y=self.value(a[0]),self.value(a[1]);jump={'eq':x==y,'ne':x!=y,'ge':x>=y}[suffix]
   else:raise AssertionError(CODE[pc-1])
   if jump:
    if target=='TrioSisters_CheckAll':self.vars['VAR_RESULT']=int(self.girls);continue
    if op.startswith('call'):stack.append(pc)
    pc=LABELS[target]
  raise AssertionError('loop')
 def reachable(self):
  occupied={(o['x'],o['y']) for o in MAP['object_events']};seen={(12,27)};q=collections.deque(seen)
  while q:
   x,y=q.popleft()
   for nx,ny in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
    if not(0<=nx<24 and 0<=ny<30):continue
    if (nx,ny) not in occupied and (nx,ny) not in seen and not(self.blocks[ny*24+nx]&0x800):seen.add((nx,ny));q.append((nx,ny))
  return seen
class Checks(unittest.TestCase):
 def test_entry_and_decline_existing_save(self):
  for flags,girls in [((),True),(('FLAG_TRIO_FESTIVAL_PICNIC',),False)]:
   r=Run(flags=flags,girls=girls).run('Entrance');self.assertFalse(r.warps);self.assertFalse(r.locked)
  r=Run(flags=['FLAG_TRIO_FESTIVAL_PICNIC'],answers=[0]).run('Entrance');self.assertFalse(r.warps)
  r=Run(flags=['FLAG_TRIO_FESTIVAL_PICNIC'],state=3).run('Entrance');self.assertEqual(r.warps,[('MAP_TRIO_ECHO_WOODS','12','27')]);self.assertEqual(r.vars[STATE],3)
 def test_physical_puzzles_and_persistent_reload(self):
  for state in range(6):
   r=Run(state).run('Load');seen=r.reachable()
   for n,y in [(1,26),(2,21),(3,13)]:self.assertEqual((11,y) in seen,state>=n-1)
   self.assertEqual((12,5) in seen,state>=3)
   self.assertIn((11,28),seen)
   for n in range(1,4):
    before=r.vars[STATE];r.run('Echo'+str(n));self.assertFalse(r.locked)
    if before==n-1:self.assertEqual(r.vars[STATE],n)
    else:self.assertEqual(r.vars[STATE],before)
  r=Run()
  for n in range(1,4):
   r.run('Echo'+str(n));self.assertEqual(r.vars[STATE],n)
   loaded=Run(n).run('Load');self.assertEqual(r.blocks,loaded.blocks)
   r.run('Exit');self.assertEqual(r.vars[STATE],n)
 def test_missing_and_declined_pad_dont_advance(self):
  for n in range(1,4):
   for kwargs in [{'girls':False},{'answers':[0]}]:
    r=Run(n-1,**kwargs).run('Echo'+str(n));self.assertEqual(r.vars[STATE],n-1);self.assertFalse(r.locked)
 def test_guardian_loss_escape_decline_and_full_bag(self):
  for outcome in [2,3,4,5]:
   r=Run(3,outcomes=[outcome,1]).run('Guardian');self.assertEqual(r.vars[STATE],3);self.assertEqual(r.gifts,0);self.assertFalse(r.locked)
   r.run('Guardian');self.assertEqual(r.vars[STATE],5)
  r=Run(3,answers=[0]).run('Guardian');self.assertEqual(r.battles,0)
  r=Run(3,room=False).run('Guardian');self.assertEqual(r.vars[STATE],4);self.assertEqual(r.battles,1)
  r.girls=False;r.room=True;r.run('Guardian');self.assertEqual(r.gifts,1);self.assertEqual(r.vars[STATE],5);self.assertEqual(r.battles,1)
  r.run('Guardian');self.assertEqual(r.gifts,1);self.assertEqual(r.battles,1)
 def test_forms_and_scrapbook_return(self):
  for npc,form in [('Riko','SPECIES_RIKO_WING'),('Bijuu','SPECIES_BIJUU_PSYCHIC'),('Penny','SPECIES_PENNY_GUARDIAN')]:
   a=Run().run(npc);b=Run(forms=[form]).run(npc);self.assertNotEqual(a.text,b.text);self.assertEqual(b.vars[STATE],0);self.assertFalse(b.locked)
  r=Run(4);r.locked=True;r.run('ReadMemory').run('Checklist');self.assertTrue(r.locked);self.assertEqual(r.vars[STATE],4)
 def test_geometry_assets_and_original_ids(self):
  layouts=json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts'];groups=json.loads((ROOT/'data/maps/map_groups.json').read_text())
  for path,current in [('data/layouts/layouts.json',layouts),('data/maps/map_groups.json',groups)]:
   old=json.loads(subprocess.check_output(['git','show','0a22e000:'+path],cwd=ROOT,text=True))
   if isinstance(current,list):self.assertEqual(current[:-1],old['layouts'])
   else:
    expected={k:list(v) if isinstance(v,list) else v for k,v in old.items()};expected['gMapGroup_IndoorGoldenrod'].append('TrioEchoWoods');self.assertEqual(current,expected)
  self.assertLessEqual(len(MAP['object_events'])+2,16)
  # Actual south-arrow warp behavior is required for automatic step exits.
  for warp in MAP['warp_events']:
   v=BASE[warp['y']*24+warp['x']];self.assertEqual(v&0x7ff,0x1de)
   self.assertEqual(warp['dest_map'],'MAP_GOLDENROD_CITY_POKEMON_CENTER')
  attrs=[(ROOT/f'data/tilesets/{p}/metatile_attributes.bin').read_bytes() for p in ['primary/johto_general','secondary/national_park']]
  for state in range(6):
   r=Run(state).run('Load')
   for index,v in enumerate(r.blocks):
    tile=v&0x7ff;self.assertLess((tile%1024)*2+1,len(attrs[tile>=1024]))
    if not(v&0x800) and index not in (28*24+11,28*24+12):self.assertIn(struct.unpack_from('<H',attrs[tile>=1024],(tile%1024)*2)[0]&255,(0,3))
  center=json.loads((ROOT/'data/maps/GoldenrodCity_PokemonCenter/map.json').read_text());layout=next(l for l in layouts if l['id']==center['layout']);blocks=struct.unpack('<%dH'%(layout['width']*layout['height']),(ROOT/layout['blockdata_filepath']).read_bytes());self.assertFalse(blocks[6*layout['width']+10]&0x800)
  old=json.loads(subprocess.check_output(['git','show','0a22e000:data/maps/GoldenrodCity_PokemonCenter/map.json'],cwd=ROOT,text=True));self.assertEqual(center['object_events'][:-1],old['object_events']);self.assertEqual(center['warp_events'],old['warp_events'])
 def test_source_authoring_and_safe_lifecycle(self):
  self.assertEqual((ROOT/'data/maps/TrioEchoWoods/scripts.pory').read_text().split('`',1)[1].rsplit('`',1)[0].strip(),S.strip())
  for name in re.findall(r'\bTrioRift_\w+\b',S):self.assertIn(name,LABELS)
  for text in re.findall(r'\.string "(.*)"',S):
   self.assertTrue(text.endswith('$'))
   for page in text[:-1].split(r'\p'):
    lines=page.split(r'\n');self.assertLessEqual(len(lines),2)
    for line in lines:self.assertLessEqual(len(line),26)
  self.assertNotIn('MAP_SCRIPT_ON_FRAME',S);self.assertNotIn('FLAG_SYS_NO_CATCHING',S)
  c=(ROOT/'src/battle_setup.c').read_text();callback=c.split('static void CB2_EndTrioSpiritTrial(void)\n{')[1].split('\n}')[0]
  self.assertIn('FlagClear(B_FLAG_NO_CATCHING)',callback);self.assertIn('HealTrioTrialParty()',callback);self.assertIn('CB2_ReturnToFieldContinueScriptPlayMapMusic',callback)
if __name__=='__main__':unittest.main()
