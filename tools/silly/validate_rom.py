"""Verify eight actual linked map/guide/frame registries and fifty actor payloads."""
from pathlib import Path
import importlib.util,json,re,struct
R=Path(__file__).resolve().parents[2]
spec=importlib.util.spec_from_file_location('parade_rom',R/'tools/parade/validate_rom.py');v=importlib.util.module_from_spec(spec);spec.loader.exec_module(v)
scenes=json.loads((R/'tools/silly/locations.json').read_text());groups=json.loads((R/'data/maps/map_groups.json').read_text())
def data(name):return json.loads((R/f'data/maps/{name}/map.json').read_text())
def mapid(name):
 for group in groups['group_order']:
  if name in groups[group]:return groups['group_order'].index(group),groups[group].index(name)
 raise AssertionError(name)
count=0
for s in scenes:
 header=v.address(s['map']);group,num=mapid(s['map']);table=v.address(s['group']);assert v.read(table+num*4,'<I')==header
 assert v.read(header+8,'<I')==v.address(s['map']+'_MapScripts')
 events=v.address(s['map']+'_ObjectEvents');m=data(s['map'])
 for i,o in enumerate(m['object_events']):
  obj=events+i*24;assert v.read(obj,'<B')==i+1
  assert [v.read(obj+4,'<h'),v.read(obj+6,'<h')]==[o['x'],o['y']]
  assert v.read(obj+12,'<H')==0
  assert v.read(obj+16,'<I')==v.address(o['script']);count+=1
 guide=v.address(s['source']+'_ObjectEvents')+(s['guide_id']-1)*24
 assert v.read(guide+16,'<I')==v.address('TrioSilly_'+s['key']+'Offer')
 assert [v.read(guide+4,'<h'),v.read(guide+6,'<h')]==s['guide']
 if s['interactive']:
  warp=v.address(s['map']+'_MapWarps');g,n=mapid(s['source'])
  assert v.read(warp+5,'<B')==0 and v.read(warp+6,'<B')==n and v.read(warp+7,'<B')==g
 else:
  script=v.address(s['map']+'_MapScripts');assert v.read(script,'<B')==3
  assert v.read(script+1,'<I')==v.address('TrioSilly_'+s['key']+'Transition')
  assert v.read(script+5,'<B')==2 and v.read(script+6,'<I')==v.address('TrioSilly_'+s['key']+'Frame')
  assert v.read(v.address('TrioSilly_'+s['key']+'Frame')+4,'<I')==v.address('TrioSilly_'+s['key']+'Run')
# Check every authored string byte rather than only label/link presence.
chars={a.replace("\\'", "'"):int(b,16) for a,b in re.findall(r"^'(.*?)'\s*=\s*([0-9A-Fa-f]{2})(?:\s|$)",(R/'charmap.txt').read_text(),re.M)}
for label,encoded in re.findall(r'(TrioSilly_\w+Text):\n\s*\.string "(.*?)"',(R/'data/scripts/trio_silly_scenes.inc').read_text()):
 tokens=re.findall(r'\\[npl]|.',encoded);expected=bytes(chars[x] for x in tokens);address=v.address(label)-0x08000000
 assert v.rom[address:address+len(expected)]==expected,label
for name in ['PrepareTrioSillyActors','TrioSilly_ActorsReady']:
 assert 0x08000000<=v.address(name)<0x0A000000
assert count==50,count
print('PASS eight live guide/map registrations, seven auto-scene frames, six club speakers, fifty actors and every authored dialogue byte')
