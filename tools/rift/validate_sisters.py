#!/usr/bin/env python3
"""Actual-script simulation and map/asset contracts, not emulator rendering."""
import unittest,json,struct,collections,subprocess,re
from pathlib import Path
from PIL import Image
from validate_rift import Run,ROOT,S,LABELS
B='VAR_TRIO_RIFT_BIJUU_STATE';P='VAR_TRIO_RIFT_PENNY_STATE'
C='FLAG_TRIO_RIFT_COURAGE_RECEIVED';F='FLAG_TRIO_RIFT_FIRE_RECEIVED';V='FLAG_TRIO_RIFT_BRAVERY_RECEIVED'
def run_at(key,state=0,**kwargs):
 r=Run(**kwargs);r.vars[key]=state;return r
class Sisters(unittest.TestCase):
 def test_hub_and_natural_gates(self):
  for flags,dest in [([],'MAP_TRIO_ECHO_WOODS'),([C],'MAP_TRIO_MIRROR_HOUSE'),([C,F],'MAP_TRIO_LANTERN_TRAIL')]:
   r=Run(flags=['FLAG_TRIO_FESTIVAL_PICNIC',*flags]).run('Entrance');self.assertEqual(r.warps[0][0],dest);self.assertFalse(r.locked)
   r=Run(flags=['FLAG_TRIO_FESTIVAL_PICNIC',*flags]).run('TownOffer');self.assertEqual(r.warps[0][0],dest)
  r=Run(flags=[C,F,V,'FLAG_TRIO_FESTIVAL_PICNIC'],answers=[0,0,1]).run('Entrance');self.assertEqual(r.warps[0][0],'MAP_TRIO_LANTERN_TRAIL')
  for prefix,flag in [('TrioMirror',C),('TrioLantern',F)]:
   self.assertFalse(Run().run(prefix+'_Entrance').warps)
   self.assertFalse(Run(flags=[flag],girls=False).run(prefix+'_Entrance').warps)
   self.assertFalse(Run(flags=[flag],answers=[0]).run(prefix+'_Entrance').warps)
   self.assertTrue(Run(flags=[flag]).run(prefix+'_Entrance').warps)
 def test_town_offer_is_optional_and_picnic_gated(self):
  for flags,girls,answers in [([],True,[1]),(['FLAG_TRIO_FESTIVAL_PICNIC'],False,[1]),(['FLAG_TRIO_FESTIVAL_PICNIC'],True,[0])]:
   r=Run(flags=flags,girls=girls,answers=answers).run('TownOffer')
   self.assertFalse(r.warps)
   self.assertEqual(r.flags,set(flags))
  for ext in ('inc','pory'):
   source=(ROOT/('data/maps/GoldenrodCity/scripts.'+ext)).read_text()
   self.assertIn('call_if_set FLAG_TRIO_FESTIVAL_PICNIC, TrioRift_TownOffer',source)
   self.assertIn('GoldenrodCity_EventScript_ScrapbookNeighbor',source)
 def test_penny_frames_have_no_detached_import_fragments(self):
  for name in ('front','back','overworld'):
   image=Image.open(ROOT/('graphics/pokemon/penny_brave/'+name+'.png'))
   for k in range(6 if name=='overworld' else 1):
    frame=image.crop((k*32,0,k*32+32,32)) if name=='overworld' else image
    pixels={(x,y) for y in range(frame.height) for x in range(frame.width) if frame.getpixel((x,y))!=0}
    self.assertTrue(pixels)
    queue=[pixels.pop()]
    while queue:
     x,y=queue.pop()
     for dx in (-1,0,1):
      for dy in (-1,0,1):
       neighbor=(x+dx,y+dy)
       if neighbor in pixels:pixels.remove(neighbor);queue.append(neighbor)
    self.assertFalse(pixels,(name,k,'detached sprite fragment'))
 def test_mirror_clues_copies_and_real_cat(self):
  r=run_at(B).run('TrioMirror_Penny');self.assertEqual(r.vars[B],0)
  for name in ['CopyA','CopyB','Real']:r.run('TrioMirror_'+name);self.assertEqual(r.vars[B],0)
  r.run('TrioMirror_Riko');self.assertEqual(r.vars[B],1)
  # Reconstructed saved state accepts the remaining clue without losing the first.
  r=run_at(B,1).run('TrioMirror_Penny');self.assertEqual(r.vars[B],2)
  for name in ['CopyA','CopyB']:r.run('TrioMirror_'+name);self.assertEqual(r.vars[B],2)
  r.answers=iter([0]);r.run('TrioMirror_Real');self.assertEqual(r.vars[B],2)
  r.answers=iter([1]);r.run('TrioMirror_Real');self.assertEqual(r.vars[B],3)
  r.run('TrioMirror_Penny').run('TrioMirror_Riko');self.assertEqual(r.vars[B],3)
 def test_guardian_loss_escape_decline_full_bag_and_repeat(self):
  for prefix,key,flag in [('TrioMirror',B,F),('TrioLantern',P,V)]:
   for outcome in [2,3,4,5]:
    r=run_at(key,3,outcomes=[outcome,1]).run(prefix+'_Guardian');self.assertEqual(r.vars[key],3);self.assertFalse(r.locked)
    r.run(prefix+'_Guardian');self.assertEqual(r.vars[key],5);self.assertIn(flag,r.flags)
    r.run(prefix+'_Guardian');self.assertEqual(r.gifts,1);self.assertEqual(r.battles,2)
   r=run_at(key,3,answers=[0]).run(prefix+'_Guardian');self.assertEqual(r.battles,0)
   r=run_at(key,3,room=False).run(prefix+'_Guardian');self.assertEqual(r.vars[key],4);self.assertNotIn(flag,r.flags)
   r.girls=False;r.room=True;r.run(prefix+'_Guardian');self.assertEqual(r.vars[key],5);self.assertEqual(r.battles,1);self.assertEqual(r.gifts,1)
   r.run(prefix+'_Guardian');self.assertEqual(r.gifts,1)
   r=run_at(key,2).run(prefix+'_Guardian');self.assertEqual(r.battles,0)
 def test_lantern_light_reconstruction_and_order(self):
  for state,radius in [(0,4),(1,3),(2,2),(3,0),(4,0),(5,0)]:
   r=run_at(P,state).run('TrioLantern_Load').run('TrioLantern_Lights');self.assertEqual(r.flash,radius)
   loaded=r.blocks.copy();r=run_at(P)
   for n in range(1,min(state,3)+1):r.run('TrioLantern_Light'+str(n))
   self.assertEqual(r.blocks,loaded)
  for kwargs in [{'girls':False},{'answers':[0]}]:
   r=run_at(P,**kwargs).run('TrioLantern_Light1');self.assertEqual(r.vars[P],0)
  r=run_at(P).run('TrioLantern_Light3');self.assertEqual(r.vars[P],0)
  r=run_at(P,2).run('TrioLantern_Exit');self.assertEqual(r.vars[P],2);self.assertEqual(r.flash,0)
 def test_support_forms_and_scrapbook(self):
  for label,form in [('TrioMirror_Riko','SPECIES_RIKO_ECHO'),('TrioMirror_Penny','SPECIES_PENNY_GUARDIAN'),('TrioLantern_Bijuu','SPECIES_BIJUU_EMBER'),('TrioLantern_Penny','SPECIES_PENNY_BRAVE')]:
   a=run_at(B,1).run(label);b=run_at(B,1,forms=[form]).run(label);self.assertNotEqual(a.text,b.text)
  for label in ['TrioMirror_ReadMemory','TrioLantern_ReadMemory']:
   r=Run();r.locked=True;r.run(label);self.assertTrue(r.locked);self.assertEqual(r.gifts,0)
 def test_map_reachability_and_stable_original_ids(self):
  layouts=json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts'];groups=json.loads((ROOT/'data/maps/map_groups.json').read_text())
  old=json.loads(subprocess.check_output(['git','show','3dd224e0:data/layouts/layouts.json'],cwd=ROOT,text=True));self.assertEqual(layouts[:len(old['layouts'])],old['layouts'])
  old=json.loads(subprocess.check_output(['git','show','3dd224e0:data/maps/map_groups.json'],cwd=ROOT,text=True));old['gMapGroup_IndoorGoldenrod']+=['TrioMirrorHouse','TrioLanternTrail'];old['gMapGroup_IndoorOlivine'].append('TrioGarden');old['gMapGroup_IndoorNewBark'].append('RikoSpiritCavern');self.assertEqual(groups,old)
  for name,entry,width,stage in [('TrioMirrorHouse',(4,7),13,0),('TrioLanternTrail',(12,27),24,3)]:
   m=json.loads((ROOT/f'data/maps/{name}/map.json').read_text());l=next(v for v in layouts if v['id']==m['layout']);blocks=list(struct.unpack('<%dH'%(l['width']*l['height']),(ROOT/l['blockdata_filepath']).read_bytes()))
   if name=='TrioLanternTrail':blocks=run_at(P,stage).run('TrioLantern_Load').blocks
   occupied={(o['x'],o['y']) for o in m['object_events']};self.assertEqual(len(occupied),len(m['object_events']));self.assertLessEqual(len(occupied)+2,16)
   seen={entry};q=collections.deque(seen)
   while q:
    x,y=q.popleft()
    for a,b in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
     if 0<=a<l['width'] and 0<=b<l['height'] and (a,b) not in seen|occupied and not(blocks[b*width+a]&0x800):seen.add((a,b));q.append((a,b))
   for o in m['object_events']:self.assertTrue(any((o['x']+dx,o['y']+dy) in seen for dx,dy in [(1,0),(-1,0),(0,1),(0,-1)]),o)
   for w in m['warp_events']:self.assertIn((w['x'],w['y']),seen);self.assertEqual(w['dest_map'],'MAP_GOLDENROD_CITY_POKEMON_CENTER')
   self.assertFalse(blocks[entry[1]*width+entry[0]]&0x800)
   if name=='TrioMirrorHouse':
    attrs=(ROOT/'data/tilesets/primary/johto_building/metatile_attributes.bin').read_bytes();self.assertEqual(struct.unpack_from('<H',attrs,0xe7*2)[0]&255,0x65)
  for name in ['EcruteakCity_PokemonCenter','OlivineCity_PokemonCenter']:
   m=json.loads((ROOT/f'data/maps/{name}/map.json').read_text());old=json.loads(subprocess.check_output(['git','show','3dd224e0:data/maps/'+name+'/map.json'],cwd=ROOT,text=True));self.assertEqual(m['object_events'][:-1],old['object_events']);self.assertEqual(m['warp_events'],old['warp_events'])
 def test_authoring_and_registered_scripts(self):
  for name in ['TrioMirrorHouse','TrioLanternTrail']:
   s=(ROOT/f'data/maps/{name}/scripts.inc').read_text();self.assertEqual((ROOT/f'data/maps/{name}/scripts.pory').read_text().split('`',1)[1].rsplit('`',1)[0].strip(),s.strip())
   for label in re.findall(r'\bTrio(?:Rift|Mirror|Lantern)_\w+\b',s):self.assertIn(label,LABELS)
   self.assertNotIn('MAP_SCRIPT_ON_FRAME',s);self.assertIn(f'data/maps/{name}/scripts.inc',(ROOT/'data/event_scripts.s').read_text())
 def test_indexed_assets(self):
  for folder in ['bijuu_ember','penny_brave']:
   p=ROOT/'graphics/pokemon'/folder
   for name,size in [('front',(64,64)),('back',(64,64)),('icon',(32,64)),('overworld',(192,32))]:
    with Image.open(p/(name+'.png')) as im:
     self.assertEqual(im.mode,'P');self.assertEqual(im.size,size);self.assertEqual(im.info['transparency'],0);self.assertLessEqual(max(im.tobytes()),15)
   for file in p.glob('*.pal'):self.assertEqual(len(file.read_text().splitlines()[3:]),16)
if __name__=='__main__':unittest.main()
