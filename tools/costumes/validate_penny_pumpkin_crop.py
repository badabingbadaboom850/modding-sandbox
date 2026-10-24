"""Reproduce the neighboring-tail crop and verify native conversion changes only up-idle."""
from pathlib import Path
from PIL import Image
import collections,subprocess,tempfile
R=Path(__file__).resolve().parents[2];P=R/'graphics/pokemon/penny_pumpkin'
def components(data):
 remaining={(i%32,i//32) for i,v in enumerate(data) if v};sizes=[]
 while remaining:
  start=remaining.pop();q=collections.deque([start]);count=1
  while q:
   x,y=q.popleft()
   for dx in [-1,0,1]:
    for dy in [-1,0,1]:
     p=x+dx,y+dy
     if p in remaining:remaining.remove(p);q.append(p);count+=1
  sizes.append(count)
 return sorted(sizes,reverse=True)
atlas=Image.open(P/'source.png').convert('RGBA');im=Image.open(P/'overworld.png')
frames=[bytes(im.getpixel((f*32+x,y)) for y in range(32) for x in range(32)) for f in range(6)]
palette=[int(v) for line in (P/'overworld_normal.pal').read_text().splitlines()[3:] for v in line.split()]
with tempfile.TemporaryDirectory() as directory:
 d=Path(directory);exe=d/'convert';raw=d/'atlas.raw';pal=d/'colors';out=d/'frame.raw'
 raw.write_bytes(atlas.tobytes());pal.write_text(' '.join(map(str,palette)))
 subprocess.run(['cc','-O2',str(R/'tools/costumes/new_render.c'),'-o',str(exe)],check=True)
 def convert(cell,isolate=False):
  subprocess.run([str(exe),str(raw),*map(str,atlas.size),str(cell),'32',str(out),str(pal),*(['1'] if isolate else [])],check=True)
  return out.read_bytes()
 for i,cell in enumerate([3,4,7,8,5,6]):
  default=convert(cell);fixed=convert(cell,True) if cell in [7,8] else default
  assert frames[i]==fixed,(i,'native conversion/PNG mismatch')
  if i==2:
   assert components(default)==[277,24],components(default) # actual prior crop reproduction
   assert len(components(fixed))==1 and fixed!=default
   xs=[j%32 for j,v in enumerate(fixed) if v];assert abs((min(xs)+max(xs))/2-15.5)<=2
  else:assert fixed==default,(i,'unrequested direction changed')
 assert len(components(frames[3]))==1
# Normal/shiny palette values and transparent index remain consistent.
assert im.mode=='P' and im.size==(192,32) and im.info['transparency']==0
assert im.getpalette()[:48]==palette and max(im.tobytes())<16
assert (P/'overworld_normal.pal').read_bytes()==(P/'overworld_shiny.pal').read_bytes()
print('PASS reproduced24-pixel neighboring tail; only up-idle repaired, other five frames byte-exact, both up poses connected/centered and palettes unchanged')
