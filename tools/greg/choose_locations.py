"""Choose walkable Greg sidelines with bypasses and conservative object budgets."""
import sys,collections,json
from pathlib import Path
R=Path(__file__).resolve().parents[2];from geometry import geometry
seeds={'GoldenrodCity':(49,29),'Route38':(30,14),'EcruteakCity':(49,40),'CianwoodCity':(26,46),'Route42':(60,15),'BlackthornCity':(34,43),'PewterCity':(29,23),'CeruleanCity':(32,21),'VermilionCity':(35,23),'CeladonCity':(33,23),'FuchsiaCity':(21,32),'SaffronCity':(28,31)}
rows=[]
for n,seed in seeds.items():
 m,w,h,walk=geometry(n);m['object_events']=[o for o in m['object_events'] if not o['script'].startswith('GregRoam_')];occ={(o['x'],o['y']) for o in m['object_events']};events={(o['x'],o['y']) for t in ['warp_events','coord_events','bg_events'] for o in m[t]};tiles={(x,y) for y in range(h) for x in range(w) if walk(x,y)}-occ
 def component(start,blocked):
  seen={start};q=collections.deque(seen)
  while q:
   x,y=q.popleft()
   for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
    if p in tiles and p not in seen|blocked:seen.add(p);q.append(p)
  return seen
 viable=[]
 for x,y in sorted(tiles,key=lambda p:abs(p[0]-seed[0])+abs(p[1]-seed[1])):
  if not(3<=x<w-3 and 3<=y<h-3):continue
  blocked={(x,y),(x,y+1),(x,y+2)}
  if any(abs(x-ex)+abs(y-ey)<3 for ex,ey in events):continue
  if not all((x+dx,y+dy) in tiles for dx in [-1,0,1] for dy in [-1,0,1,2,3]):continue
  # All possible template visibility, plus Greg/player/follower, stays <=16.
  budget=max(sum(abs(o['x']-cx)<=10 and abs(o['y']-cy)<=8 for o in m['object_events'])+3 for cx in range(x-10,x+11) for cy in range(y-8,y+9))
  if budget>16:continue
  start=(x-1,y);before=component(start,set());after=component(start,blocked)
  if before-blocked!=after:continue
  if not any((v['x'],v['y']+1) in before for v in m['warp_events']):continue
  viable.append((x,y,budget));break
 if not viable:raise ValueError(n)
 x,y,b=viable[0];rows.append({'map':n,'xy':[x,y],'trainer':1080+len(rows),'sight':2,'budget':b});print(n,x,y,'peak',b)
path=R/'tools/greg/locations.json'
if path.exists():
 prior=json.loads(path.read_text())
 for r,p in zip(rows,prior):p.update(r)
 rows=prior
path.write_text(json.dumps(rows,indent=2)+'\n')
for row in rows:
 p=R/'data/maps'/row['map']/'map.json';m=json.loads(p.read_text())
 for o in m['object_events']:
  if o['script'].startswith('GregRoam_'):o['x'],o['y']=row['xy']
 p.write_text(json.dumps(m,indent=2)+'\n')
