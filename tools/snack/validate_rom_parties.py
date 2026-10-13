#!/usr/bin/env python3
"""Decode real production parties; the headless runner mocks gTrainers.

Compile party_layout.c with the engine ARM ABI (apcs-gnu, no short-enums),
then pass production ELF, GBA and that object. No third-party dependencies.
"""
import argparse,re,struct
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
def elf(path):
 b=Path(path).read_bytes();assert b[:5]==b'\x7fELF\x01'
 off=struct.unpack_from('<I',b,32)[0];step,count=struct.unpack_from('<HH',b,46)
 sections=[struct.unpack_from('<10I',b,off+i*step) for i in range(count)]
 symbols={}
 for sec in sections:
  if sec[1]!=2:continue
  strings=sections[sec[6]];names=b[strings[4]:strings[4]+strings[5]]
  for pos in range(sec[4],sec[4]+sec[5],sec[9]):
   name,value,size,info,other,index=struct.unpack_from('<IIIBBH',b,pos)
   end=names.find(b'\0',name);key=names[name:end].decode();symbols[key]=(value,size,index)
 return b,sections,symbols
p=argparse.ArgumentParser();p.add_argument('elf');p.add_argument('rom');p.add_argument('layout');a=p.parse_args()
b,secs,syms=elf(a.layout);value,size,index=syms['sGangLayout'];sec=secs[index]
layout=struct.unpack_from('<9I',b,sec[4]+value-sec[3]);trainer_size,party_off,count_off,mon_size,ev_off,iv_off,species_off,level_off,item_off=layout
_,_,syms=elf(a.elf);table,table_size,_=syms['gTrainers'];rom=Path(a.rom).read_bytes()
assert table_size==3*1164*trainer_size,(table_size,trainer_size)
def read(addr,size):
 off=addr-0x08000000;assert 0<=off and off+size<=len(rom),(hex(addr),size)
 return rom[off:off+size]
def u32(addr):return struct.unpack('<I',read(addr,4))[0]
def u16(addr):return struct.unpack('<H',read(addr,2))[0]
species=int(re.search(r'^#define SPECIES_GREEDENT\s+(\d+)',(ROOT/'include/constants/species.h').read_text(),re.M).group(1))
for wave,(trainer,level) in enumerate(zip([1162,1154,1155,1156,1157,1158],[22,35,48,62,78,100]),1):
 row=table+(1164+trainer)*trainer_size # DIFFICULTY_NORMAL = 1
 count=read(row+count_off,1)[0];party=u32(row+party_off);assert count==wave,(wave,count)
 for i in range(count):
  mon=party+i*mon_size;assert u16(mon+species_off)==species
  assert read(mon+level_off,1)[0]==level
  if wave==6:
   assert u32(mon+iv_off)==0x3FFFFFFF
   assert read(u32(mon+ev_off),3)==bytes([252,252,4])
   assert u16(mon+item_off)!=0
 print(f'Wave {wave}: {count} actual level-{level} Greedent'+(' with perfect IVs, HP/Attack EVs and held items' if wave==6 else ''))
print('Production-ROM party check passed; ARM layout:',layout)
