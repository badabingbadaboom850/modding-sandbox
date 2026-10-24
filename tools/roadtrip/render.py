"""Decode actual map assets for visual QA; this is not an emulator."""
from pathlib import Path
import json,struct,sys
from PIL import Image,ImageDraw
ROOT=Path(__file__).resolve().parents[2]
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
def loadpair(secondary):
 tiles=[];pals={};mts=[];attrs=[]
 for si,s in enumerate(['primary/johto_general','secondary/'+secondary]):
  p=ROOT/'data/tilesets'/s;im=Image.open(p/'tiles.png')
  for y in range(0,im.height,8):
   for x in range(0,im.width,8):tiles.append(im.crop((x,y,x+8,y+8)))
  if si==0:
   while len(tiles)<640:tiles.append(Image.new('P',(8,8)))
  for f in (p/'palettes').glob('*.pal'):
   i=int(f.stem)
   if (si==0 and i<7) or (si==1 and i>=7):pals[i]=[tuple(map(int,l.split())) for l in f.read_text().splitlines()[3:]]
  mts.append(list(struct.iter_unpack('<12H',(p/'metatiles.bin').read_bytes())))
  attrs.append([a[0] for a in struct.iter_unpack('<H',(p/'metatile_attributes.bin').read_bytes())])
 return tiles,pals,mts,attrs
if __name__=='__main__':
 data=loadpair('cianwood_city')
 ids=[0,1,4,0xa,0xb,0xc,0xd,0x69,0x71,0x72,0x75,0x100,0x101,0x102,0x103,0x104,0x105,0x106,0x107,0x108,0x10b,0x10c,0x10d,0x115,0x12b,0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8]
 out=Image.new('RGB',(8*90,5*80),(20,20,20));d=ImageDraw.Draw(out)
 for n,id in enumerate(ids):
  x=n%8*90;y=n//8*80;out.paste(cell(id,data).resize((48,48)),(x,y));d.text((x,y+52),f'{id:03x}:{data[3][id>=1024][id%1024]&255:02x}',fill='white')
 out.save(ROOT.parent/'road_tiles.png')
