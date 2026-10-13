"""Check actual production ROM trainer teams and active NPC/script registrations."""
from pathlib import Path
import json,re,struct,sys
R=Path(__file__).resolve().parents[2]
def elf(path):
 b=Path(path).read_bytes();assert b[:5]==b'\x7fELF\x01';off=struct.unpack_from('<I',b,32)[0];step,count=struct.unpack_from('<HH',b,46);secs=[struct.unpack_from('<10I',b,off+i*step) for i in range(count)];syms={}
 for s in secs:
  if s[1]!=2:continue
  t=secs[s[6]];names=b[t[4]:t[4]+t[5]]
  for pos in range(s[4],s[4]+s[5],s[9]):
   n,v,z,info,other,idx=struct.unpack_from('<IIIBBH',b,pos);syms[names[n:names.find(b'\0',n)].decode()]=(v,z,idx)
 return b,secs,syms
b,secs,syms=elf(sys.argv[1]);v,z,idx=syms['sRoadLayout'];section=secs[idx];ts,po,co,ms,so,lo,mo,movesize=struct.unpack_from('<8I',b,section[4]+v-section[3])
_,_,syms=elf(R/'Soulgold.elf');table,z,_=syms['gTrainers'];assert z==ts*1164*3
rom=(R/'Soulgold.gba').read_bytes()
def read(addr,fmt):return struct.unpack_from(fmt,rom,addr-0x08000000)[0]
base=table+(1164+1077)*ts;baseparty=read(base+po,'<I')
for row in json.loads((R/'tools/greg/locations.json').read_text()):
 trainer=table+(1164+row['trainer'])*ts;assert read(trainer+co,'<B')==6;assert read(trainer+co-1,'<B')&3==0
 party=read(trainer+po,'<I')
 for i in range(6):
  mon=party+i*ms;prior=baseparty+i*ms;assert read(mon+lo,'<B')==99
  assert read(mon+so,'<H')==read(prior+so,'<H')
  for slot in range(4):
   fmt='<H' if movesize==2 else '<I';assert read(mon+mo+slot*movesize,fmt)==read(prior+mo+slot*movesize,fmt)
 label='GregRoam_'+row['map'];script=syms[label][0];assert read(script+3,'<H')==row['trainer']
 # Native object_event macro emits24-byte rows with script at16 and flag at20.
 objs=syms[row['map']+'_ObjectEvents'][0];obj=objs+(row['local_id']-1)*24
 assert read(obj,'<B')==row['local_id'];assert [read(obj+4,'<h'),read(obj+6,'<h')]==row['xy']
 assert read(obj+12,'<H')==1 and read(obj+14,'<H')==2
 assert read(obj+16,'<I')==script and read(obj+20,'<H')==0
 assert read(script+5,'<I')==syms[label+'_Seen'][0];assert read(script+9,'<I')==syms[label+'_Beaten'][0]
print('PASS12 linked single-battle teams (72 level99 Pokemon) and12 native NPC/script/text registrations')
