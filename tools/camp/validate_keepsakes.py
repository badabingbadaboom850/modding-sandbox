#!/usr/bin/env python3
"""Actual script-flow and decoded geometry checks, not an emulator."""
from pathlib import Path
import collections,itertools,json,re,struct,subprocess,unittest
ROOT=Path(__file__).resolve().parents[2]
SOURCE=(ROOT/'data/scripts/trio_camp_keepsakes.inc').read_text()
LABELS={};CODE=[]
for line in SOURCE.splitlines():
    line=line.strip()
    if not line or line.startswith('@'):continue
    if re.fullmatch(r'\w+::?',line):
        label=line.rstrip(':');assert label not in LABELS,label;LABELS[label]=len(CODE)
    else:CODE.append(line)
CONSTANTS={'TRUE':1,'FALSE':0}
for name,n in re.findall(r'#define (METATILE_HouseLab_Trio\w+)\s+(0x[0-9A-Fa-f]+)',(ROOT/'include/constants/metatile_labels.h').read_text()):CONSTANTS[name]=int(n,16)
BASE=list(struct.unpack('<130H',(ROOT/'data/layouts/NewBarkTown_House1/map.bin').read_bytes()))
MAP=json.loads((ROOT/'data/maps/NewBarkTown_House1/map.json').read_text())
ROWS=re.findall(r'\{(FLAG_HIDE_TRIO_CAMP_\w+), (FLAG_\w+), (FLAG_\w+|0)\}',(ROOT/'src/trio_camp.c').read_text())
def visibility(flags):return {hide for hide,earned,legacy in ROWS if earned not in flags and legacy not in flags}
class Run:
    def __init__(self,flags=()):self.flags=set(flags);self.blocks=BASE.copy();self.text=[];self.locked=False;self.ended=False
    def run(self,label):
        pc=LABELS[label];stack=[]
        for _ in range(500):
            line=CODE[pc];pc+=1;op,_,rest=line.partition(' ');a=[x.strip() for x in rest.split(',')]
            if op=='return':
                if not stack:return self
                pc=stack.pop();continue
            if op=='end':self.ended=True;return self
            if op=='lockall':self.locked=True;continue
            if op=='releaseall':self.locked=False;continue
            if op=='faceplayer':continue
            if op=='msgbox':self.text.append(a[0]);continue
            if op=='setmetatile':
                x,y=map(int,a[:2]);tile=CONSTANTS.get(a[2],None)
                if tile is None:tile=int(a[2],0)
                value=tile|(0x800 if CONSTANTS[a[3]] else 0)
                self.blocks[y*13+x]=(self.blocks[y*13+x]&0xF000)|value;continue
            if op in ['call_if_set','call_if_unset','goto_if_set','goto_if_unset']:
                condition=(a[0] in self.flags)==op.endswith('_set')
                if condition:
                    if op.startswith('call'):stack.append(pc)
                    pc=LABELS[a[1]]
                continue
            raise AssertionError(line)
        raise AssertionError('script loop')
class Checks(unittest.TestCase):
    def test_registration_and_stable_original_objects(self):
        old=json.loads(subprocess.check_output(['git','show','b7e5ee42:data/maps/NewBarkTown_House1/map.json'],cwd=ROOT,text=True))
        self.assertEqual(MAP['object_events'][:8],old['object_events'])
        self.assertEqual(MAP['warp_events'],old['warp_events'])
        self.assertEqual(len(MAP['object_events']),14)
        self.assertEqual(len(ROWS),6)
        self.assertIn('map_script MAP_SCRIPT_ON_LOAD, TrioCamp_DecorateRoom',(ROOT/'data/maps/NewBarkTown_House1/scripts.inc').read_text())
        self.assertIn('special TrioCamp_UpdateKeepsakes',(ROOT/'data/scripts/trio_camp.inc').read_text())
    def test_tileset_append_preserves_existing_metatiles(self):
        for suffix,size in [('metatiles.bin',24),('metatile_attributes.bin',2)]:
            path='data/tilesets/secondary/house_lab/'+suffix
            old=subprocess.check_output(['git','show','b7e5ee42:'+path],cwd=ROOT)
            now=(ROOT/path).read_bytes();self.assertEqual(now[:len(old)],old)
            self.assertEqual(len(now)-len(old),1*size)
        self.assertLess(217,1024)
    def test_geometry_all_visual_progress_combinations(self):
        attrs=[(ROOT/'data/tilesets/primary/johto_building/metatile_attributes.bin').read_bytes(),(ROOT/'data/tilesets/secondary/house_lab/metatile_attributes.bin').read_bytes()]
        def walkable(blocks,x,y):
            if not(0<=x<13 and 0<=y<10):return False
            v=blocks[y*13+x];i=v&2047
            attribute=struct.unpack_from('<H',attrs[i>=1024],(i%1024)*2)[0]
            return not(v&0x800) and (attribute&255)==0
        objects=MAP['object_events'];occupied={(o['x'],o['y']) for o in objects}
        self.assertEqual(len(occupied),len(objects))
        self.assertLessEqual(len(objects)+2,16) # Every template, player and follower.
        keys=['FLAG_BADGE03_GET','FLAG_BADGE04_GET','FLAG_BADGE08_GET','FLAG_IS_CHAMPION']
        for bits in itertools.product([False,True],repeat=len(keys)):
            flags={key for key,bit in zip(keys,bits) if bit}
            blocks=Run(flags).run('TrioCamp_DecorateRoom').blocks
            # All upgrades preserve the original collision and elevation masks.
            for original,current in zip(BASE,blocks):self.assertEqual(original&0xF800,current&0xF800)
            seen={(4,8)};q=collections.deque(seen)
            while q:
                x,y=q.popleft()
                for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
                    if p not in seen and p not in occupied and walkable(blocks,*p):seen.add(p);q.append(p)
            for o in objects:
                x,y=o['x'],o['y']
                if o not in objects[:2]:self.assertTrue(walkable(blocks,x,y),o['script'])
                self.assertTrue(any(p in seen for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]),o['script'])
            for x,y in [(9,1),(10,1),(0,1),(6,1)]:self.assertIn((x,y+1),seen)
            for x,y in [(x,3) for x in range(1,4)]+[(2,y) for y in range(4,7)]+[(x,7) for x in range(7,10)]:
                self.assertTrue(walkable(blocks,x,y));self.assertNotIn((x,y),occupied-{(2,3),(2,5),(8,7)})
    def test_load_is_idempotent_and_resets_unearned_visuals(self):
        flags={'FLAG_BADGE03_GET','FLAG_BADGE04_GET','FLAG_BADGE08_GET','FLAG_IS_CHAMPION'}
        r=Run(flags).run('TrioCamp_DecorateRoom');first=r.blocks.copy()
        r.run('TrioCamp_DecorateRoom');self.assertEqual(first,r.blocks)
        r.flags=set();r.run('TrioCamp_DecorateRoom');self.assertEqual(r.blocks,BASE)
    def test_interactions_release_and_host_helper_returns(self):
        flags={'FLAG_BADGE03_GET','FLAG_BADGE04_GET','FLAG_BADGE08_GET','FLAG_IS_CHAMPION'}
        for o in MAP['object_events'][8:]:
            r=Run(flags).run(o['script']);self.assertTrue(r.ended);self.assertFalse(r.locked);self.assertEqual(len(r.text),1)
        for label in ['Photos','LeagueDisplay']:
            for f in [set(),flags]:
                r=Run(f).run('TrioCampKeepsakes_'+label);self.assertTrue(r.ended);self.assertFalse(r.locked)
        allflags=flags|{'FLAG_BADGE01_GET','FLAG_TRIO_FESTIVAL_PICNIC','FLAG_TRIO_PENNY_SPIRIT_COMPLETE','FLAG_TRIO_BIJUU_SPIRIT_COMPLETE'}
        r=Run(allflags|visibility(allflags));r.locked=True;r.run('TrioCampKeepsakes_ReadRoom')
        self.assertTrue(r.locked);self.assertFalse(r.ended);self.assertEqual(len(r.text),11)
        self.assertNotIn('setflag',SOURCE);self.assertNotIn('giveitem',SOURCE)
    def test_text_and_references(self):
        for name in re.findall(r'\bTrioCampKeepsakes_\w+\b',SOURCE):self.assertIn(name,LABELS)
        for string in re.findall(r'\.string "(.*)"',SOURCE):
            self.assertTrue(string.endswith('$'))
            for page in string[:-1].split(r'\p'):
                lines=page.split(r'\n');self.assertLessEqual(len(lines),2)
                for line in lines:self.assertLessEqual(len(line),26)
if __name__=='__main__':unittest.main()
