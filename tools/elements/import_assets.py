"""Image formats only; native C owns cropping, scaling and quantization."""
from pathlib import Path
from PIL import Image
import subprocess,tempfile,json,sys
R=Path(__file__).resolve().parents[2]
name=sys.argv[1]
p=R/'graphics/pokemon'/name;p.mkdir(parents=True,exist_ok=True)
accent={
 'riko_dragon':[(178,123,215),(119,80,164),(225,180,245)],
 'riko_bug':[(255,200,32),(191,132,20),(247,233,188)],
 'bijuu_dark':[(75,51,91),(43,34,62),(117,89,139)],
 'bijuu_rock':[(147,143,214),(194,223,250),(95,76,190)],
 'penny_ground':[(255,196,88),(156,97,45),(99,66,42)],
 'penny_steel':[(255,219,54),(127,137,156),(201,68,52)]}[name]
colors=[(0,0,0),(25,22,30),(50,46,55),(80,46,32),(140,88,49),(214,153,80),(255,220,177),(248,248,248),(188,195,210),(64,42,80)]+accent+[(239,139,161),(55,137,225),(20,67,142)]
pal=[v for c in colors for v in c]
with tempfile.TemporaryDirectory() as td:
    td=Path(td);exe=td/'convert'
    subprocess.run(['cc','-O2',str(R/'tools/elements/render.c'),'-o',str(exe)],check=True)
    atlas=Image.open(p/'source.png').convert('RGBA');raw=td/'source.raw';raw.write_bytes(atlas.tobytes())
    rgb=td/'palette.rgb';rgb.write_text(' '.join(map(str,pal)))
    def convert(cell,size):
        out=td/'out.raw';subprocess.run([str(exe),str(raw),*map(str,atlas.size),str(cell),str(size),str(out),str(rgb)],check=True)
        im=Image.frombytes('P',(size,size),out.read_bytes());im.putpalette(pal+[0]*720);return im
    for asset_name,cell in [('front',0),('back',1)]:convert(cell,64).save(p/(asset_name+'.png'),bits=4,transparency=0)
    icon=convert(2,32);out=Image.frombytes('P',(32,64),icon.tobytes()*2);out.putpalette(pal+[0]*720);out.save(p/'icon.png',bits=4,transparency=0)
    # Concatenate native row bytes, not raster resizing/compositing in Python.
    frames=[convert(cell,32).tobytes() for cell in [3,4,7,8,5,6]]
    data=b''.join(b''.join(frame[y*32:(y+1)*32] for frame in frames) for y in range(32))
    out=Image.frombytes('P',(192,32),data);out.putpalette(pal+[0]*720);out.save(p/'overworld.png',bits=4,transparency=0)
    convert(10,24).save(R/'graphics/items/icons'/f'{name}_keepsake.png',bits=4,transparency=0)
text='JASC-PAL\n0100\n16\n'+'\n'.join(' '.join(map(str,c)) for c in colors)+'\n'
for palette_name in ['normal','shiny','icon_normal','icon_shiny','overworld_normal','overworld_shiny']:(p/(palette_name+'.pal')).write_text(text)
(R/'graphics/items/icon_palettes'/f'{name}_keepsake.pal').write_text(text)
