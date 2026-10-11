"""Inspect the linked production map, script and music registrations."""
from pathlib import Path
import json, re, struct

R=Path(__file__).resolve().parents[2]
b=(R/'Soulgold.elf').read_bytes()
offset=struct.unpack_from('<I',b,32)[0]; step,count=struct.unpack_from('<HH',b,46)
sections=[struct.unpack_from('<10I',b,offset+i*step) for i in range(count)]
syms={}
for section in sections:
    if section[1]!=2: continue
    table=sections[section[6]]; names=b[table[4]:table[4]+table[5]]
    for position in range(section[4],section[4]+section[5],section[9]):
        name,value,size,info,other,index=struct.unpack_from('<IIIBBH',b,position)
        syms[names[name:names.find(b'\0',name)].decode()]=(value,size)
rom=(R/'Soulgold.gba').read_bytes()
def read(address,fmt):return struct.unpack_from(fmt,rom,address-0x08000000)[0]
def address(name):return syms[name][0]
events=address('TrioPomParade_ObjectEvents')
actors=json.loads((R/'data/maps/TrioPomParade/map.json').read_text())['object_events']
for i,actor in enumerate(actors):
    obj=events+i*24
    assert read(obj,'<B')==i+1
    assert [read(obj+4,'<h'),read(obj+6,'<h')]==[actor['x'],actor['y']]
    assert read(obj+12,'<H')==0 and read(obj+16,'<I')==0 and read(obj+20,'<H')==0
    if i<9: assert read(obj+2,'<H')==read(events+2,'<H')
script=address('TrioPomParade_MapScripts')
assert read(script,'<B')==3 and read(script+1,'<I')==address('TrioParade_Transition')
assert read(script+5,'<B')==2 and read(script+6,'<I')==address('TrioParade_Frame')
frame=address('TrioParade_Frame')
assert read(frame+4,'<I')==address('TrioParade_Run')
woman=address('GoldenrodCity_EventScript_Woman')
assert bytes([4])+struct.pack('<I',address('TrioParade_Offer')) in rom[woman-0x08000000:woman-0x08000000+32]
for name in ['TrioParade_March','TrioParade_Spin','TrioParade_Sniff','TrioParade_LatePom','TrioParade_Return','TrioParade_ReadMemory','TrioParade_MemoryText','PrepareTrioParadeActors','mus_hg_wifi_parade']:
    assert 0x08000000<=address(name)<0x0A000000,name
header=address('TrioPomParade')
assert read(header+16,'<H')==923
assert read(header+8,'<I')==script
assert read(header,'<I')==address('GoldenrodCity_Layout')
assert len(rom)==32*1024*1024
print('PASS fourteen native actors, active city organizer, map-frame scene, movement/memory pointers, native Goldenrod layout and enabled parade song in the production ROM')
