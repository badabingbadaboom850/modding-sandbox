#!/usr/bin/env python3
"""Import the approved Flower Riko sheet and Bloom charm into GBA assets.
Usage: import_assets.py SHEET CHARM. Output side frames face LEFT.
"""
from pathlib import Path
import sys
from PIL import Image
ROOT=Path(__file__).resolve().parents[2]
COLORS=[(0,0,0),(23,18,28),(40,35,44),(70,60,76),(171,140,106),(236,197,148),(255,233,194),(255,247,225),(205,91,128),(245,143,177),(255,199,208),(145,88,38),(235,175,65),(255,219,96),(72,98,39),(138,173,85)]
PAL=Image.new('P',(1,1));PAL.putpalette([c for rgb in COLORS for c in rgb]+[0]*720)
def convert(source,size,limit):
 source=source.convert('RGBA');mask=source.getchannel('A').point(lambda a:255 if a>=180 else 0);box=mask.getbbox();assert box
 source=source.crop(box);scale=min(limit[0]/source.width,limit[1]/source.height)
 source=source.resize((max(1,round(source.width*scale)),max(1,round(source.height*scale))),Image.Resampling.NEAREST)
 rgb=source.convert('RGB').quantize(palette=PAL,dither=Image.Dither.NONE);rgb.putdata([max(i,1) if a>=180 else 0 for i,a in zip(rgb.getdata(),source.getchannel('A').getdata())])
 out=Image.new('P',size,0);out.putpalette(PAL.getpalette());out.paste(rgb,((size[0]-rgb.width)//2,size[1]-rgb.height-1));out.info['transparency']=0;return out
sheet=Image.open(sys.argv[1]);assert sheet.width==sheet.height,sheet.size
boxes=[(0,0,440,470),(440,0,850,470),(850,0,1280,470),(0,470,440,835),(440,470,850,835),(850,470,1280,835),(0,835,440,1280),(440,835,850,1280),(850,835,1280,1280)]
boxes=[tuple(round(v*sheet.width/1280) for v in b) for b in boxes]
p=ROOT/'graphics/pokemon/riko_flower';p.mkdir(parents=True,exist_ok=True)
for name,box in zip(['front','back'],boxes[:2]):convert(sheet.crop(box),(64,64),(58,58)).save(p/(name+'.png'),bits=4,transparency=0)
icon=convert(sheet.crop(boxes[2]),(32,32),(28,28));out=Image.new('P',(32,64),0);out.putpalette(PAL.getpalette());out.paste(icon,(0,0));out.paste(icon,(0,32));out.save(p/'icon.png',bits=4,transparency=0)
walk=[convert(sheet.crop(box),(32,32),(29,29)) for box in boxes[3:]];out=Image.new('P',(192,32),0);out.putpalette(PAL.getpalette())
for n,i in enumerate([0,1,4,5,2,3]):out.paste(walk[i],(n*32,0))
out.save(p/'overworld.png',bits=4,transparency=0)
text='JASC-PAL\n0100\n16\n'+'\n'.join(' '.join(map(str,c)) for c in COLORS)+'\n'
for name in ['normal','shiny','icon_normal','icon_shiny','overworld_normal','overworld_shiny']:(p/(name+'.pal')).write_text(text)
convert(Image.open(sys.argv[2]),(24,24),(21,21)).save(ROOT/'graphics/items/icons/rikos_bloom.png',bits=4,transparency=0)
(ROOT/'graphics/items/icon_palettes/rikos_bloom.pal').write_text(text)
