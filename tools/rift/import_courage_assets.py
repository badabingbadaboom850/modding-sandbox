#!/usr/bin/env python3
"""Convert approved generated sprite sources into indexed GBA assets.
Usage: import_courage_assets.py SPRITE_SHEET ITEM_ICON
All output palettes share transparent index0; follower frames are down/up/right.
"""
from pathlib import Path
import sys
from PIL import Image
ROOT=Path(__file__).resolve().parents[2]
COLORS=[(0,0,0),(17,16,28),(41,37,48),(62,56,67),(102,87,80),(172,130,78),(218,168,104),(248,204,140),(255,232,180),(255,251,226),(60,138,145),(26,66,81),(220,90,118),(212,151,37),(255,210,60),(139,124,116)]
PAL=Image.new('P',(1,1));PAL.putpalette([c for rgb in COLORS for c in rgb]+[0]*720)
def convert(source,size,limit):
 source=source.convert('RGBA');mask=source.getchannel('A').point(lambda a:255 if a>=180 else 0)
 box=mask.getbbox();assert box,'No opaque subject';source=source.crop(box)
 scale=min(limit[0]/source.width,limit[1]/source.height)
 source=source.resize((max(1,round(source.width*scale)),max(1,round(source.height*scale))),Image.Resampling.NEAREST)
 rgb=source.convert('RGB').quantize(palette=PAL,dither=Image.Dither.NONE);a=source.getchannel('A');rgb.putdata([max(idx,1) if alpha>=180 else 0 for idx,alpha in zip(rgb.getdata(),a.getdata())])
 out=Image.new('P',size,0);out.putpalette(PAL.getpalette());out.paste(rgb,((size[0]-rgb.width)//2,size[1]-rgb.height-1));out.info['transparency']=0;return out
sheet=Image.open(sys.argv[1]);assert sheet.size==(1536,1024),sheet.size
boxes=[(70,25,545,425),(555,25,1000,425),(1060,90,1480,425),(130,440,430,720),(650,440,955,720),(1060,440,1480,735),(95,735,515,1024),(600,735,970,1024),(1100,735,1490,1024)]
p=ROOT/'graphics/pokemon/riko_echo';p.mkdir(parents=True,exist_ok=True)
frames=[convert(sheet.crop(box),(64,64),(58,58)) for box in boxes[:2]]
for name,im in zip(['front','back'],frames):im.save(p/(name+'.png'),bits=4,transparency=0)
icon=convert(sheet.crop(boxes[2]),(32,32),(28,28));icons=Image.new('P',(32,64),0);icons.putpalette(PAL.getpalette());icons.paste(icon,(0,0));icons.paste(icon,(0,32));icons.save(p/'icon.png',bits=4,transparency=0)
walk=[convert(sheet.crop(box),(32,32),(29,29)) for box in boxes[3:]]
# Existing engine ordering is down stand, down step, up stand, up step, right stand, right step.
strip=Image.new('P',(192,32),0);strip.putpalette(PAL.getpalette())
for n,i in enumerate([0,1,4,5,2,3]):strip.paste(walk[i],(32*n,0))
strip.save(p/'overworld.png',bits=4,transparency=0)
text='JASC-PAL\n0100\n16\n'+'\n'.join(' '.join(map(str,c)) for c in COLORS)+'\n'
for name in ['normal','shiny','icon_normal','icon_shiny','overworld_normal','overworld_shiny']:(p/(name+'.pal')).write_text(text)
item=convert(Image.open(sys.argv[2]),(24,24),(21,21));itempath=ROOT/'graphics/items/icons/rikos_courage.png';item.save(itempath,bits=4,transparency=0);(ROOT/'graphics/items/icon_palettes/rikos_courage.pal').write_text(text)
