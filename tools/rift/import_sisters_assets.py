#!/usr/bin/env python3
"""Import approved portrait sprite sources: Bijuu sheet, Penny sheet.
Cells: battle front/back/icon; down/down step/right; right step/up/up step;
centered charm. Follower output is engine-ordered down/up/right.
"""
from pathlib import Path
from PIL import Image
import sys
ROOT=Path(__file__).resolve().parents[2]
COLORS=[(0,0,0),(20,13,16),(55,31,27),(93,57,42),(137,86,50),(182,119,54),(223,161,76),(250,197,108),(255,225,158),(255,246,214),(255,88,12),(202,44,7),(255,210,26),(54,142,206),(18,67,114),(244,156,135)]
PAL=Image.new('P',(1,1));PAL.putpalette([c for rgb in COLORS for c in rgb]+[0]*720)
def convert(source,size,limit):
 source=source.convert('RGBA');mask=source.getchannel('A').point(lambda a:255 if a>=180 else 0);box=mask.getbbox();assert box
 source=source.crop(box);scale=min(limit[0]/source.width,limit[1]/source.height);source=source.resize((max(1,round(source.width*scale)),max(1,round(source.height*scale))),Image.Resampling.NEAREST)
 rgb=source.convert('RGB').quantize(palette=PAL,dither=Image.Dither.NONE);rgb.putdata([max(idx,1) if alpha>=180 else 0 for idx,alpha in zip(rgb.tobytes(),source.getchannel('A').tobytes())])
 out=Image.new('P',size,0);out.putpalette(PAL.getpalette());out.paste(rgb,((size[0]-rgb.width)//2,size[1]-rgb.height-1));return out
for file,folder,item in zip(sys.argv[1:],['bijuu_ember','penny_brave'],['bijuus_fire','pennys_bravery']):
 sheet=Image.open(file);assert sheet.size==(1024,1536)
 boxes=[(0,0,380,510),(380,0,700,510),(700,0,1024,510),(0,510,380,880),(380,510,700,880),(700,510,1024,880),(0,880,380,1220),(380,880,700,1220),(700,880,1024,1220)]
 p=ROOT/'graphics/pokemon'/folder;p.mkdir(exist_ok=True)
 for name,box in zip(['front','back'],boxes[:2]):convert(sheet.crop(box),(64,64),(58,58)).save(p/(name+'.png'),bits=4,transparency=0)
 icon=convert(sheet.crop(boxes[2]),(32,32),(28,28));out=Image.new('P',(32,64),0);out.putpalette(PAL.getpalette());out.paste(icon,(0,0));out.paste(icon,(0,32));out.save(p/'icon.png',bits=4,transparency=0)
 out=Image.new('P',(192,32),0);out.putpalette(PAL.getpalette());walk=[convert(sheet.crop(b),(32,32),(29,29)) for b in boxes[3:]]
 for n,i in enumerate([0,1,4,5,2,3]):out.paste(walk[i],(n*32,0))
 out.save(p/'overworld.png',bits=4,transparency=0)
 text='JASC-PAL\n0100\n16\n'+'\n'.join(' '.join(map(str,c)) for c in COLORS)+'\n'
 for name in ['normal','shiny','icon_normal','icon_shiny','overworld_normal','overworld_shiny']:(p/(name+'.pal')).write_text(text)
 convert(sheet.crop((350,1220,700,1536)),(24,24),(21,21)).save(ROOT/'graphics/items/icons'/(item+'.png'),bits=4,transparency=0);(ROOT/'graphics/items/icon_palettes'/(item+'.pal')).write_text(text)
