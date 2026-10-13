#!/usr/bin/env python3
"""Check actual linked photographer templates and special registration; no rendering."""
from pathlib import Path
import json,struct
R=Path(__file__).resolve().parents[2]
b=(R/'Soulgold.elf').read_bytes();off=struct.unpack_from('<I',b,32)[0];step,count=struct.unpack_from('<HH',b,46);secs=[struct.unpack_from('<10I',b,off+i*step) for i in range(count)];symbols={}
for sec in secs:
 if sec[1]!=2:continue
 st=secs[sec[6]];names=b[st[4]:st[4]+st[5]]
 for pos in range(sec[4],sec[4]+sec[5],sec[9]):
  name,value,size,info,other,index=struct.unpack_from('<IIIBBH',b,pos);end=names.find(b'\0',name);symbols[names[name:end].decode()]=(value,size,index)
rom=(R/'Soulgold.gba').read_bytes()
def at(address,n):return rom[address-0x08000000:address-0x08000000+n]
for name,label in [('OlivineCity_LighthouseTop','Lighthouse'),('LakeOfRage','Lake'),('IcePath_1F','Ice')]:
 m=json.loads((R/f'data/maps/{name}/map.json').read_text());actor=m['object_events'][-1];count=len(m['object_events']);base=symbols[name+'_ObjectEvents'][0];obj=at(base+(count-1)*24,24)
 assert len(obj)==24 and obj[0]==count and struct.unpack_from('<H',obj,1)[0]==48
 assert struct.unpack_from('<hh',obj,4)==(actor['x'],actor['y']) and obj[8]==actor['elevation']
 assert struct.unpack_from('<H',obj,12)[0]==0 and struct.unpack_from('<H',obj,20)[0]==0
 assert struct.unpack_from('<I',obj,16)[0]==symbols['TrioScenic_'+label][0]
 assert symbols['TrioScenic_'+label][1]>0
# Appended special callbacks have real Thumb pointers in the production table.
for name in ['TakeTrioScenicPhoto','ReadTrioScenicPhoto']:
 address,size,_=symbols[name];assert size>0
 table=symbols['gSpecials'][0];n=symbols['gSpecials'][1]
 assert struct.pack('<I',address|1) in at(table,n or 4096),name
assert symbols['TrioWeatherReaction'][1]>0 and symbols['TrioScenic_Album'][1]>0
print('PASS: actual production ROM photographer positions/scripts, appended special Thumb pointers, weather helper and album linked')
