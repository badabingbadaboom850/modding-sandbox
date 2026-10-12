"""Image formats only; native C owns cropping, scaling and quantization."""
from pathlib import Path
from PIL import Image
import subprocess,tempfile,json,sys
R=Path(__file__).resolve().parents[2]
name=sys.argv[1]
p=R/'graphics/pokemon'/name;p.mkdir(parents=True,exist_ok=True)
colors=[(0,0,0),(24,20,28),(54,45,53),(84,52,36),(151,98,49),(218,157,78),(255,218,154),(255,239,210),(245,247,255),(178,188,220),(110,123,170),(255,163,204),(221,101,170),(172,117,212),(60,171,244),(21,75,146)]
pal=[v for c in colors for v in c]
with tempfile.TemporaryDirectory() as td:
    td=Path(td);exe=td/'convert'
    subprocess.run(['cc','-O2',str(R/'tools/costumes/new_render.c'),'-o',str(exe)],check=True)
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
    convert(10,24).save(R/'graphics/items/icons'/f'{name}.png',bits=4,transparency=0)
text='JASC-PAL\n0100\n16\n'+'\n'.join(' '.join(map(str,c)) for c in colors)+'\n'
for palette_name in ['normal','shiny','icon_normal','icon_shiny','overworld_normal','overworld_shiny']:(p/(palette_name+'.pal')).write_text(text)
(R/'graphics/items/icon_palettes'/f'{name}.pal').write_text(text)
