#!/usr/bin/env python3
"""Execute garden assembly with engine stubs; inspect actual geometry/assets.
Source simulation and decoded art are not an emulator playthrough.
"""
from pathlib import Path
import collections,json,re,struct,subprocess,unittest
from PIL import Image
ROOT=Path(__file__).resolve().parents[2]
S=(ROOT/'data/maps/TrioGarden/scripts.inc').read_text()
LABELS={};CODE=[]
for line in S.splitlines():
 line=line.strip()
 if not line or line.startswith('@'):continue
 if re.fullmatch(r'\w+::?',line):LABELS[line.rstrip(':')]=len(CODE)
 else:CODE.append(line)
STATE='VAR_TRIO_GARDEN_STATE';GIFT='FLAG_TRIO_GARDEN_BLOOM_RECEIVED'
BASE=list(struct.unpack('<432H',(ROOT/'data/layouts/TrioGarden/map.bin').read_bytes()))
MAP=json.loads((ROOT/'data/maps/TrioGarden/map.json').read_text())
class Run:
 def __init__(self,state=0,flags=(),girls=True,answers=(),room=True):
  self.vars={STATE:state};self.flags=set(flags);self.girls=girls;self.answers=iter(answers);self.room=room;self.blocks=BASE.copy();self.gifts=0;self.warps=[];self.locked=False;self.text=[];self.visible=set()
 def value(self,v):
  if v.startswith('VAR_'):return self.vars.get(v,0)
  return {'TRUE':1,'FALSE':0,'YES':1,'NO':0}.get(v,int(v,0) if re.fullmatch(r'(\d+|0x[\da-fA-F]+)',v) else v)
 def run(self,name):
  pc=LABELS['TrioGarden_'+name];stack=[]
  for _ in range(2000):
   op,_,args=CODE[pc].partition(' ');pc+=1;a=[v.strip() for v in args.split(',')]
   if op=='end':return self
   if op=='return':
    if not stack:return self
    pc=stack.pop();continue
   if op in ('lockall','lock'):self.locked=True;continue
   if op in ('releaseall','release'):self.locked=False;continue
   if op in ('faceplayer','closemessage','waitstate'):continue
   if op=='msgbox':
    self.text.append(a[0])
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=next(self.answers,1)
    continue
   if op=='setvar':self.vars[a[0]]=self.value(a[1]);continue
   if op=='setflag':self.flags.add(a[0]);continue
   if op=='clearflag':self.flags.discard(a[0]);continue
   if op=='removeobject':self.visible.discard(int(a[0]));continue
   if op=='addobject':self.visible.add(int(a[0]));continue
   if op=='warp':self.warps.append(tuple(a));continue
   if op=='giveitem':self.vars['VAR_RESULT']=int(self.room);self.gifts+=int(self.room);continue
   if op=='setmetatile':
    x,y=int(a[0]),int(a[1]);self.blocks[y*24+x]=(self.blocks[y*24+x]&0xf000)|int(a[2],0)|(0x800 if self.value(a[3]) else 0);continue
   if op=='special':assert a[0] in ('DrawWholeMapView','HealPlayerParty');continue
   target=a[-1];jump=False
   if op in ('goto','call'):jump=True
   elif op.startswith(('goto_if_','call_if_')):
    suffix=op.split('_if_')[1]
    if suffix in ('set','unset'):jump=(a[0] in self.flags)==(suffix=='set')
    else:
     x,y=self.value(a[0]),self.value(a[1]);jump={'eq':x==y,'ne':x!=y,'ge':x>=y,'lt':x<y}[suffix]
   else:raise AssertionError(CODE[pc-1])
   if jump:
    if target=='TrioSisters_CheckAll':self.vars['VAR_RESULT']=int(self.girls);continue
    if op.startswith('call'):stack.append(pc)
    pc=LABELS[target]
  raise AssertionError('loop')
 def reachable(self):
  occupied={(o['x'],o['y']) for o in MAP['object_events'] if o['flag']=='0' or o['flag'] not in self.flags};seen={(12,15)};q=collections.deque(seen)
  while q:
   x,y=q.popleft()
   for nx,ny in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
    if not(0<=nx<24 and 0<=ny<18):continue
    if (nx,ny) not in occupied and (nx,ny) not in seen and not(self.blocks[ny*24+nx]&0x800):seen.add((nx,ny));q.append((nx,ny))
  return seen
class Checks(unittest.TestCase):
 def test_entry_gate_and_decline(self):
  self.assertFalse(Run().run('Offer').warps)
  self.assertFalse(Run(flags=['FLAG_BADGE05_GET'],answers=[0]).run('Offer').warps)
  for state in range(7):
   r=Run(state,flags=['FLAG_BADGE05_GET'],girls=False).run('Offer');self.assertEqual(r.warps,[('MAP_TRIO_GARDEN','12','15')]);self.assertEqual(r.vars[STATE],state);self.assertFalse(r.locked)
 def test_three_visits_save_reload_and_no_skip(self):
  r=Run().run('Riko');self.assertEqual(r.vars[STATE],1)
  r.run('Bijuu').run('Penny').run('Load');self.assertEqual(r.vars[STATE],1)
  r=Run(1).run('Load');self.assertEqual(r.vars[STATE],1)
  r.run('OnReturn').run('Bijuu');self.assertEqual(r.vars[STATE],3)
  r.run('Penny').run('Load');self.assertEqual(r.vars[STATE],3)
  r=Run(3).run('OnReturn').run('Penny');self.assertEqual(r.vars[STATE],5);self.assertEqual(r.gifts,0)
  r.run('TryBloom');self.assertEqual(r.vars[STATE],6);self.assertIn(GIFT,r.flags);self.assertEqual(r.gifts,1)
  r.run('Riko').run('Bijuu').run('Penny').run('OnReturn').run('TryBloom');self.assertEqual(r.gifts,1)
 def test_missing_party_and_decline_preserve_progress(self):
  for state,npc in [(0,'Riko'),(2,'Bijuu'),(4,'Penny')]:
   for args in [dict(girls=False),dict(answers=[0])]:
    r=Run(state,**args).run(npc);self.assertEqual(r.vars[STATE],state);self.assertFalse(r.locked);self.assertEqual(r.gifts,0)
 def test_full_bag_recovery_no_party_no_repeat(self):
  r=Run(5,room=False,girls=False).run('TryBloom');self.assertEqual(r.vars[STATE],5);self.assertNotIn(GIFT,r.flags);self.assertEqual(r.vars['VAR_RESULT'],0)
  r=Run(5,girls=False).run('TryBloom');self.assertEqual(r.gifts,1);self.assertEqual(r.vars[STATE],6)
  r=Run(6,flags=[GIFT],girls=False).run('TryBloom');self.assertEqual(r.gifts,0)
  mom=(ROOT/'data/scripts/trio_memories.inc').read_text();self.assertIn('call TrioGarden_TryBloom\n\tgoto_if_eq VAR_RESULT, FALSE, TrioMemories_Return',mom)
 def test_all_stages_have_exit_and_adjacent_interaction_tiles(self):
  for state in range(7):
   r=Run(state).run('Load');seen=r.reachable()
   for x in (11,12):self.assertIn((x,17),seen)
   for o in MAP['object_events']:
    if o['flag'] in r.flags:continue
    x,y=o['x'],o['y'];self.assertTrue(any(p in seen for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]),o)
   self.assertEqual('FLAG_TEMP_1' in r.flags,state>=5);self.assertEqual('FLAG_TEMP_2' in r.flags,state<5)
   self.assertEqual(r.blocks[4*24+4]&0x7ff,0x45c if state==0 else 9 if state<3 else 0x417 if state<5 else 0x410)
   r.run('Caretaker');self.assertEqual(r.warps[-1],('MAP_OLIVINE_CITY','33','57'));self.assertFalse(r.locked)
  city=json.loads((ROOT/'data/maps/OlivineCity/map.json').read_text());self.assertEqual(city['warp_events'][0]['dest_map'],'MAP_OLIVINE_CITY_LIGHTHOUSE')
 def test_appended_map_ids_and_authoring_parity(self):
  for path in ['data/maps/map_groups.json','data/layouts/layouts.json']:
   base=json.loads(subprocess.check_output(['git','show','aa7efd8:'+path],cwd=ROOT));now=json.loads((ROOT/path).read_text())
   if 'layouts' in base:self.assertEqual(now['layouts'][:-1],base['layouts'])
   else:
    for k,v in base.items():self.assertEqual(now[k][:-1] if k=='gMapGroup_IndoorOlivine' else now[k],v)
  self.assertEqual((ROOT/'data/maps/TrioGarden/scripts.pory').read_text().removeprefix('raw `\n').removesuffix('`\n').strip(),S.strip())
  for ext in ['pory','inc']:self.assertIn('call TrioGarden_OnReturn',(ROOT/f'data/maps/OlivineCity/scripts.{ext}').read_text())
 def test_assets_and_no_detached_crop_fragments(self):
  p=ROOT/'graphics/pokemon/riko_flower'
  for name,size in [('front',(64,64)),('back',(64,64)),('icon',(32,64)),('overworld',(192,32))]:
   im=Image.open(p/(name+'.png'));self.assertEqual(im.size,size);self.assertEqual(im.mode,'P');self.assertLessEqual(len(im.getcolors()),16)
   frames=[im.crop((x,0,x+32,32)) for x in range(0,192,32)] if name=='overworld' else [im.crop((0,0,32,32))] if name=='icon' else [im]
   for frame in frames:
    pixels={(x,y) for y in range(frame.height) for x in range(frame.width) if frame.getpixel((x,y))!=0};self.assertTrue(pixels)
    seen={next(iter(pixels))};q=collections.deque(seen)
    while q:
     x,y=q.popleft()
     for dx in (-1,0,1):
      for dy in (-1,0,1):
       n=(x+dx,y+dy)
       if n in pixels and n not in seen:seen.add(n);q.append(n)
    self.assertEqual(seen,pixels,(name,len(pixels-seen)))
  with Image.open(ROOT/'graphics/items/icons/rikos_bloom.png') as im:self.assertEqual(im.size,(24,24))
 def test_no_forced_battles_and_completion_memory(self):
  for text in re.findall(r'\.string "(.*)"',S):
   for page in text.rstrip('$').split(r'\p'):
    rows=page.split(r'\n');self.assertLessEqual(len(rows),2)
    for row in rows:self.assertLessEqual(len(row),26)
  self.assertNotIn('trainerbattle',S);self.assertNotIn('wildbattle',S);self.assertNotIn('PrepareTrioSpiritTrial',S)
  self.assertIn('call_if_ge VAR_TRIO_GARDEN_STATE, 5, TrioGarden_ReadMemory',(ROOT/'data/scripts/trio_memories.inc').read_text())
  self.assertIn('call_if_ge VAR_TRIO_GARDEN_STATE, 5, TrioGarden_DecorateCamp',(ROOT/'data/scripts/trio_camp_keepsakes.inc').read_text())
if __name__=='__main__':unittest.main()
