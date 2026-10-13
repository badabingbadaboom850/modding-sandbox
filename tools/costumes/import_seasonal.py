"""Formats-only bridge for seasonal atlases; native C isolates each pose before import."""
from pathlib import Path
from PIL import Image
import subprocess,tempfile,json
R=Path(__file__).resolve().parents[2]
rows=json.loads((R/'tools/costumes/seasons.json').read_text())
base=[(0,0,0),(20,17,22),(52,41,39),(91,58,34),(147,95,48),(207,147,73),(248,197,116),(255,232,187),(250,249,246)]
accents=[[(122,41,23),(191,73,25),(240,120,24),(249,179,35),(61,94,27),(110,134,42),(158,117,45)],[(49,74,49),(90,123,77),(146,169,124),(100,28,51),(167,59,79),(36,108,182),(77,186,250)],[(122,43,74),(178,78,109),(225,131,157),(252,188,200),(248,214,218),(196,171,156),(255,248,231)],[(95,31,18),(146,46,25),(205,71,44),(248,119,59),(123,82,53),(182,133,76),(228,182,118)],[(104,9,27),(181,26,39),(239,73,65),(160,161,164),(219,221,222),(32,104,183),(70,186,253)],[(116,26,20),(171,42,25),(216,75,30),(245,115,43),(255,160,58),(251,207,53),(255,230,110)],[(89,8,24),(156,12,31),(210,32,47),(251,71,76),(153,143,137),(204,199,194),(255,255,255)],[(13,60,29),(25,103,46),(52,159,62),(97,192,86),(159,17,28),(240,49,46),(58,173,245)],[(94,10,22),(167,18,29),(234,49,38),(255,96,77),(112,68,41),(182,127,74),(231,184,115)],[(134,96,11),(210,160,24),(255,211,43),(255,240,114),(149,33,83),(235,89,143),(255,172,199)],[(88,91,106),(136,144,161),(185,195,209),(231,237,245),(255,255,255),(31,105,184),(70,187,251)],[(112,28,67),(179,48,103),(226,94,143),(250,152,185),(255,192,213),(222,172,39),(255,232,86)]]
with tempfile.TemporaryDirectory() as td:
 td=Path(td);exe=td/'convert';subprocess.run(['cc','-O2',str(R/'tools/costumes/new_render.c'),'-o',str(exe)],check=True)
 for idx,row in enumerate(rows):
  name=row[2];p=R/'graphics/pokemon'/name;colors=base+accents[idx];pal=[v for c in colors for v in c]
  atlas=Image.open(p/'source.png').convert('RGBA');raw=td/'atlas.raw';raw.write_bytes(atlas.tobytes());rgb=td/'palette.rgb';rgb.write_text(' '.join(map(str,pal)))
  def convert(cell,size):
   out=td/'out.raw';subprocess.run([str(exe),str(raw),*map(str,atlas.size),str(cell),str(size),str(out),str(rgb),'1'],check=True)
   im=Image.frombytes('P',(size,size),out.read_bytes());im.putpalette(pal+[0]*720);return im
  for asset,cell in [('front',0),('back',1)]:convert(cell,64).save(p/(asset+'.png'),bits=4,transparency=0)
  icon=convert(2,32);out=Image.frombytes('P',(32,64),icon.tobytes()*2);out.putpalette(pal+[0]*720);out.save(p/'icon.png',bits=4,transparency=0)
  frames=[convert(cell,32).tobytes() for cell in [3,4,7,8,5,6]]
  out=Image.frombytes('P',(192,32),b''.join(b''.join(f[y*32:(y+1)*32] for f in frames) for y in range(32)));out.putpalette(pal+[0]*720);out.save(p/'overworld.png',bits=4,transparency=0)
  convert(10,24).save(R/'graphics/items/icons'/(name+'.png'),bits=4,transparency=0)
  text='JASC-PAL\n0100\n16\n'+'\n'.join(' '.join(map(str,c)) for c in colors)+'\n'
  for kind in ['normal','shiny','icon_normal','icon_shiny','overworld_normal','overworld_shiny']:(p/(kind+'.pal')).write_text(text)
  (R/'graphics/items/icon_palettes'/(name+'.pal')).write_text(text)
  print(name)
