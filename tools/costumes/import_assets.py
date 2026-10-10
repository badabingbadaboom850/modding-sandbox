#!/usr/bin/env python3
"""Deterministically crop generated costume sheets into indexed GBA assets.
Usage: import_assets.py NAME SHEET. Palette zero is transparent; side frames face left.
Only format conversion is performed; all costume art comes from generated sheets.
"""
from pathlib import Path
from PIL import Image
import sys
R=Path(__file__).resolve().parents[2]
name,source=sys.argv[1:]
ycuts={'riko_balloon':[0,380,705,1014,1280], 'bijuu_box':[0,350,660,975,1280], 'penny_hotdog':[0,345,660,970,1280]}[name]
sheet=Image.open(source).convert('RGBA');assert sheet.width==sheet.height
# Crop coordinates are expressed against the inspected 1280px preview.
factor=sheet.width/1280
boxes=[(x0,ycuts[row],x1,ycuts[row+1]) for row in range(3) for x0,x1 in [(0,430),(430,855),(855,1280)]]
boxes.append((430,ycuts[3],855,1280))
boxes=[tuple(round(v*factor) for v in b) for b in boxes]
subjects=[]
for box in boxes:
 im=sheet.crop(box);mask=im.getchannel('A').point(lambda a:255 if a>=180 else 0);bounds=mask.getbbox();assert bounds
 im=im.crop(bounds);subjects.append(im)
# Learn one shared palette from opaque pixels; reserve index0 solely for transparency.
pixels=[rgb[:3] for im in subjects for rgb in im.getdata() if rgb[3]>=180]
sample=Image.new('RGB',(len(pixels),1));sample.putdata(pixels)
pal=sample.quantize(colors=15,dither=Image.Dither.NONE).getpalette()[:45]
if name=='bijuu_box':
 pal[39:45]=[70,177,245,20,95,157] # Preserve the Siamese's small blue eyes.
colors=[(0,0,0)]+[tuple(pal[i:i+3]) for i in range(0,45,3)]
quant=Image.new('P',(1,1));quant.putpalette(pal+[0]*(768-45))
def convert(im,size,limit,scale=None):
 scale=scale or min(limit[0]/im.width,limit[1]/im.height)
 im=im.resize((max(1,round(im.width*scale)),max(1,round(im.height*scale))),Image.Resampling.NEAREST)
 indexed=im.convert('RGB').quantize(palette=quant,dither=Image.Dither.NONE)
 indexed.putdata([min(i,14)+1 if a>=180 else 0 for i,a in zip(indexed.tobytes(),im.getchannel('A').tobytes())])
 indexed.putpalette([v for c in colors for v in c]+[0]*720)
 out=Image.new('P',size,0);out.putpalette(indexed.getpalette());out.paste(indexed,((size[0]-im.width)//2,size[1]-im.height-1));return out
p=R/'graphics/pokemon'/name;p.mkdir(parents=True,exist_ok=True)
for n,i in [('front',0),('back',1)]:convert(subjects[i],(64,64),(60,60)).save(p/(n+'.png'),bits=4,transparency=0)
icon=convert(subjects[2],(32,32),(29,29));out=Image.new('P',(32,64),0);out.putpalette(icon.getpalette());out.paste(icon,(0,0));out.paste(icon,(0,32));out.save(p/'icon.png',bits=4,transparency=0)
walk=subjects[3:9];scale=min(29/max(im.width for im in walk),29/max(im.height for im in walk));out=Image.new('P',(192,32),0);out.putpalette(icon.getpalette())
for n,i in enumerate([0,1,4,5,2,3]):out.paste(convert(walk[i],(32,32),(29,29),scale),(n*32,0))
out.save(p/'overworld.png',bits=4,transparency=0)
text='JASC-PAL\n0100\n16\n'+'\n'.join(' '.join(map(str,c)) for c in colors)+'\n'
for n in ['normal','shiny','icon_normal','icon_shiny','overworld_normal','overworld_shiny']:(p/(n+'.pal')).write_text(text)
convert(subjects[9],(24,24),(22,22)).save(R/'graphics/items/icons'/(name+'.png'),bits=4,transparency=0)
(R/'graphics/items/icon_palettes'/(name+'.pal')).write_text(text)
print(name,'battle/icon/follower/item sprites imported')
