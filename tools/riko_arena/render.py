#!/usr/bin/env python3
"""Decode existing engine tiles/metatiles for map QA (not emulator rendering)."""
from PIL import Image,ImageDraw
from pathlib import Path
import struct,collections
ROOT=Path(__file__).resolve().parents[2]
def load():
 tiles=[];pals={};mts=[];attrs=[]
 for si,s in enumerate(['primary/johto_general','secondary/cave_default']):
  p=ROOT/'data/tilesets'/s;im=Image.open(p/'tiles.png')
  for y in range(0,im.height,8):
   for x in range(0,im.width,8):tiles.append(im.crop((x,y,x+8,y+8)))
  if si==0:
   while len(tiles)<640:tiles.append(Image.new('P',(8,8)))
  for f in (p/'palettes').glob('*.pal'):pals[int(f.stem)]=[tuple(map(int,l.split())) for l in f.read_text().splitlines()[3:]]
  mts.append(list(struct.iter_unpack('<12H',(p/'metatiles.bin').read_bytes())))
  attrs.append([a[0] for a in struct.iter_unpack('<H',(p/'metatile_attributes.bin').read_bytes())])
 return tiles,pals,mts,attrs
def cell(id,data):
 tiles,pals,mts,attrs=data;si=int(id>=1024);idx=id-1024*si;out=Image.new('RGB',(16,16),(0,0,0))
 for layer in range(3):
  for q in range(4):
   t=mts[si][idx][layer*4+q];src=tiles[t&1023];pal=pals[(t>>12)&15]
   if t&1024:src=src.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
   if t&2048:src=src.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
   for y in range(8):
    for x in range(8):
     c=src.getpixel((x,y))
     if c:out.putpixel(((q%2)*8+x,(q//2)*8+y),pal[c])
 return out
if __name__=='__main__':
 import sys
 data=load()
 if len(sys.argv)==2 and sys.argv[1]=='atlas':
  blocks=struct.unpack('<2880H',(ROOT/'data/layouts/UnionCave_1F/map.bin').read_bytes());ids=sorted({b&0x7ff for b in blocks})
  print(collections.Counter(hex(b&0x7ff) for b in blocks).most_common(25))
  out=Image.new('RGB',(16*70,((len(ids)+15)//16)*60),(30,30,30));d=ImageDraw.Draw(out)
  for n,id in enumerate(ids):
   x=n%16*70;y=n//16*60;out.paste(cell(id,data).resize((32,32)),(x,y));d.text((x,y+34),f'{id:03x}:{data[3][id>=1024][id%1024]&255:02x}',fill='white')
  out.save(ROOT.parent/'cave_atlas.png')
 else:
  blocks=struct.unpack('<%dH'%(32*30),(ROOT/'data/layouts/RikoSpiritCavern/map.bin').read_bytes());out=Image.new('RGB',(32*16,30*16))
  for i,b in enumerate(blocks):out.paste(cell(b&0x7ff,data),(i%32*16,i//32*16))
  out.save(ROOT.parent/'riko_cavern.png')
