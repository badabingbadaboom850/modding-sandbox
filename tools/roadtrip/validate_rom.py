#!/usr/bin/env python3
"""Check production ARM tables rather than the headless runner's mocked trainers."""
from pathlib import Path
import re,struct,sys
ROOT=Path(__file__).resolve().parents[2]
def elf(path):
 b=Path(path).read_bytes();assert b[:5]==b'\x7fELF\x01';off=struct.unpack_from('<I',b,32)[0];step,count=struct.unpack_from('<HH',b,46);secs=[struct.unpack_from('<10I',b,off+i*step) for i in range(count)];syms={}
 for s in secs:
  if s[1]!=2:continue
  t=secs[s[6]];names=b[t[4]:t[4]+t[5]]
  for pos in range(s[4],s[4]+s[5],s[9]):
   n,v,z,info,other,idx=struct.unpack_from('<IIIBBH',b,pos);syms[names[n:names.find(b'\0',n)].decode()]=(v,z,idx)
 return b,secs,syms
b,secs,syms=elf(sys.argv[1]);v,z,idx=syms['sRoadLayout'];s=secs[idx];layout=struct.unpack_from('<8I',b,s[4]+v-s[3]);ts,po,co,ms,so,lo,mo,movesize=layout
_,_,syms=elf(ROOT/'Soulgold.elf');table,z,_=syms['gTrainers'];assert z==ts*1164*3;rom=(ROOT/'Soulgold.gba').read_bytes()
def read(addr,fmt):return struct.unpack_from(fmt,rom,addr-0x08000000)[0]
constants=(ROOT/'include/constants/species.h').read_text();moves=(ROOT/'include/constants/moves.h').read_text()
for trainer,level,names in [(1151,34,['AZUMARILL','PELIPPER','LANTURN']),(1152,36,['LEAFEON','BUTTERFREE','PACHIRISU']),(1153,38,['DACHSBUN','TOGETIC','LAPRAS','FIDOUGH'])]:
 row=table+(1164+trainer)*ts;count=read(row+co,'<B');party=read(row+po,'<I');assert count==len(names);assert read(row+co-1,'<B')&3==1,'not doubles'
 for i,name in enumerate(names):
  mon=party+i*ms;species=int(re.search(r'^#define SPECIES_'+name+r'\s+(\d+)',constants,re.M).group(1));assert read(mon+so,'<H')==species;assert read(mon+lo,'<B')==level
  for k in range(4):assert read(mon+mo+k*movesize,'<H' if movesize==2 else '<I')!=0,'missing authored move'
 print(f'Trainer {trainer}: actual doubles, {count} level-{level} Pokemon; all species and four authored moves confirmed.')
print('Production party ABI:',layout)
