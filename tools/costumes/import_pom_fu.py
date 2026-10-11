"""Image formats only; native C owns cropping, scaling and quantization."""
from pathlib import Path
from PIL import Image
import subprocess,tempfile
R=Path(__file__).resolve().parents[2]
colors=[(0,0,0),(25,22,30),(50,46,55),(83,77,89),(68,40,28),(112,69,40),(170,114,67),(223,173,113),(248,248,248),(198,199,208),(138,141,154),(239,139,161),(167,75,106),(255,216,176),(222,225,235),(108,98,100)]
p=R/'graphics/pokemon/riko_fighting';p.mkdir(parents=True,exist_ok=True)
pal=[v for c in colors for v in c]
with tempfile.TemporaryDirectory() as td:
    td=Path(td);exe=td/'convert'
    subprocess.run(['cc','-O2',str(R/'tools/costumes/pom_fu_render.c'),'-o',str(exe)],check=True)
    atlas=Image.open(p/'source.png').convert('RGBA');raw=td/'source.raw';raw.write_bytes(atlas.tobytes())
    def convert(cell,size):
        out=td/'out.raw';subprocess.run([str(exe),str(raw),*map(str,atlas.size),str(cell),str(size),str(out)],check=True)
        im=Image.frombytes('P',(size,size),out.read_bytes());im.putpalette(pal+[0]*720);return im
    for name,cell in [('front',0),('back',1)]:convert(cell,64).save(p/(name+'.png'),bits=4,transparency=0)
    icon=convert(2,32);out=Image.frombytes('P',(32,64),icon.tobytes()*2);out.putpalette(pal+[0]*720);out.save(p/'icon.png',bits=4,transparency=0)
    # Concatenate native row bytes, not raster resizing/compositing in Python.
    frames=[convert(cell,32).tobytes() for cell in [3,4,7,8,5,6]]
    data=b''.join(b''.join(frame[y*32:(y+1)*32] for frame in frames) for y in range(32))
    out=Image.frombytes('P',(192,32),data);out.putpalette(pal+[0]*720);out.save(p/'overworld.png',bits=4,transparency=0)
    convert(10,24).save(R/'graphics/items/icons/riko_black_belt.png',bits=4,transparency=0)
text='JASC-PAL\n0100\n16\n'+'\n'.join(' '.join(map(str,c)) for c in colors)+'\n'
for name in ['normal','shiny','icon_normal','icon_shiny','overworld_normal','overworld_shiny']:(p/(name+'.pal')).write_text(text)
(R/'graphics/items/icon_palettes/riko_black_belt.pal').write_text(text)
