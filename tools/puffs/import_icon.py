#!/usr/bin/env python3
"""Convert the generated kibble source to the engine's 24px/16-color format."""
from pathlib import Path
from PIL import Image
import sys
R=Path(__file__).resolve().parents[2]
colors=[(0,0,0),(35,15,5),(60,25,5),(83,35,9),(110,47,12),(134,61,18),(156,76,23),(180,95,32),(204,116,43),(221,135,53),(236,158,67),(249,181,89),(255,205,120),(255,226,150),(255,239,180),(255,251,215)]
s=Image.open(sys.argv[1]).convert('RGBA');mask=s.getchannel('A').point(lambda a:255 if a>=180 else 0);s=s.crop(mask.getbbox());scale=min(22/s.width,22/s.height);s=s.resize((round(s.width*scale),round(s.height*scale)),Image.Resampling.NEAREST)
pal=Image.new('P',(1,1));pal.putpalette([c for rgb in colors for c in rgb]+[0]*720)
a=s.getchannel('A');q=s.convert('RGB').quantize(palette=pal,dither=Image.Dither.NONE);q.putdata([max(i,1) if alpha>=180 else 0 for i,alpha in zip(q.getdata(),a.getdata())]);out=Image.new('P',(24,24));out.putpalette(pal.getpalette());out.paste(q,((24-q.width)//2,(24-q.height)//2));out.save(R/'graphics/items/icons/riko_puffs.png',bits=4,transparency=0)
(R/'graphics/items/icon_palettes/riko_puffs.pal').write_text('JASC-PAL\n0100\n16\n'+'\n'.join(' '.join(map(str,c)) for c in colors)+'\n')
