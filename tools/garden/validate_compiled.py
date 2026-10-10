#!/usr/bin/env python3
"""Check built follower frame packing/palette against indexed authoring PNGs."""
from pathlib import Path
from PIL import Image
import struct
R=Path(__file__).resolve().parents[2];p=R/'graphics/pokemon/riko_flower'
raw=(p/'overworld.4bpp').read_bytes();assert len(raw)==3072
with Image.open(p/'overworld.png') as source:
 for frame in range(6):
  chunk=raw[frame*512:(frame+1)*512]
  for y in range(32):
   for x in range(32):
    tile=(y//8)*4+x//8;v=chunk[tile*32+(y%8)*4+(x%8)//2];color=(v>>4 if x%2 else v)&15
    assert color==source.getpixel((frame*32+x,y)),(frame,x,y)
colors=[tuple(map(int,line.split())) for line in (p/'overworld_normal.pal').read_text().splitlines()[3:]]
expected=[(r>>3)|((g>>3)<<5)|((b>>3)<<10) for r,g,b in colors]
assert list(struct.unpack('<16H',(p/'overworld_normal.gbapal').read_bytes()))==expected
print('Compiled Flower Riko: all six frames and palette match source pixels.')
