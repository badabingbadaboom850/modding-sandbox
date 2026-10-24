#!/usr/bin/env python3
"""Convert the generated amulet icon into native 24x24, sixteen-color assets."""
from pathlib import Path
from PIL import Image
import sys
R=Path(__file__).resolve().parents[2]
colors=[(0,0,0),(28,22,27),(48,39,43),(78,62,61),(138,82,38),(193,124,41),(242,176,52),(255,224,116),(255,246,207),(190,147,103),(230,197,152),(90,41,148),(165,87,223),(224,175,255),(33,139,178),(143,236,255)]
s=Image.open(sys.argv[1]).convert('RGBA');mask=s.getchannel('A').point(lambda a:255 if a>=180 else 0);s=s.crop(mask.getbbox());scale=min(22/s.width,22/s.height);s=s.resize((round(s.width*scale),round(s.height*scale)),Image.Resampling.NEAREST)
pal=Image.new('P',(1,1));pal.putpalette([c for rgb in colors for c in rgb]+[0]*720)
a=s.getchannel('A');q=s.convert('RGB').quantize(palette=pal,dither=Image.Dither.NONE);q.putdata([max(i,1) if alpha>=180 else 0 for i,alpha in zip(q.getdata(),a.getdata())]);out=Image.new('P',(24,24));out.putpalette(pal.getpalette());out.paste(q,((24-q.width)//2,(24-q.height)//2));out.save(R/'graphics/items/icons/rikos_amulet.png',bits=4,transparency=0)
(R/'graphics/items/icon_palettes/rikos_amulet.pal').write_text('JASC-PAL\n0100\n16\n'+'\n'.join(' '.join(map(str,c)) for c in colors)+'\n')
