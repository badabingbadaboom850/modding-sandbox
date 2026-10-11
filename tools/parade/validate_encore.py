"""Check cloned room, preserved IDs, approaches, exit and linked registrations."""
from pathlib import Path
import collections, importlib.util, json, re, subprocess, sys, struct
R = Path(__file__).resolve().parents[2]
BASE = '09db8070c19b599bc99d04077bcf7e0c4578185b'
def old(path): return subprocess.check_output(['git','show',BASE+':'+path],cwd=R)
def data(name): return json.loads((R/f'data/maps/{name}/map.json').read_text())
sys.path.insert(0,str(R/'tools/greg'))
from geometry import geometry
room = data('OlivinePomParty'); original = data('GoldenrodCity_House2')
assert room['layout'] == original['layout']
assert room['object_events'][2:] == original['object_events'][2:]
assert len(room['object_events']) + 2 <= 16
for path in ['data/maps/GoldenrodCity_House2/map.json','data/maps/GoldenrodCity_House2/scripts.inc',
             'include/global.h','include/constants/vars.h','include/constants/flags.h']:
    assert (R/path).read_bytes() == old(path), path
groups = json.loads((R/'data/maps/map_groups.json').read_text())
prior = json.loads(old('data/maps/map_groups.json'))
assert groups['gMapGroup_IndoorOlivine'] == prior['gMapGroup_IndoorOlivine'] + ['OlivinePomParty']
groups['gMapGroup_IndoorOlivine'].pop(); assert groups == prior
house = data('OlivineCity_House2'); priorhouse = json.loads(old('data/maps/OlivineCity_House2/map.json'))
assert house['object_events'][:-1] == priorhouse['object_events']
assert {k:v for k,v in house.items() if k!='object_events'} == {k:v for k,v in priorhouse.items() if k!='object_events'}
for name in ['OlivineCity_House2','OlivinePomParty']:
    m,w,h,walk = geometry(name); occupied = {(o['x'],o['y']) for o in m['object_events']}
    assert walk(4,7) and (4,7) not in occupied
    seen={(4,7)}; queue=collections.deque(seen)
    while queue:
        x,y=queue.popleft()
        for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
            if p not in seen|occupied and walk(*p): seen.add(p); queue.append(p)
    for o in m['object_events']:
        # Host is beside furniture: unchanged original hosts need not stand on land.
        assert any(p in seen for p in [(o['x']+1,o['y']),(o['x']-1,o['y']),(o['x'],o['y']+1),(o['x'],o['y']-1)])
    assert (4,7) in seen
assert room['warp_events'] == [dict(x=4,y=8,elevation=0,dest_map='MAP_OLIVINE_CITY_HOUSE2',dest_warp_id='0')]
assert house['warp_events'][0]['x']==4 and house['warp_events'][0]['y']==8
script = (R/'data/maps/OlivinePomParty/scripts.inc').read_text()
assert "'Cause a pom party" in script and "don't stop!" in script
assert not re.search(r'\b(?:setvar|setflag|clearflag|giveitem|takeitem)\b',script)
invite = (R/'data/maps/OlivineCity_House2/scripts.inc').read_text()
assert invite.startswith(old('data/maps/OlivineCity_House2/scripts.inc').decode())
assert 'goto_if_ne VAR_RESULT, YES, OlivinePomParty_Decline' in invite
assert 'warp MAP_OLIVINE_POM_PARTY, 4, 7\n\twaitstate\n\treleaseall\n\tend' in invite
for body in [script,invite.split('OlivinePomParty_Invite::',1)[1]]:
    for line in re.findall(r'\.string "(.*?)"',body):
        assert line.isascii()
        assert all(len(s)<=26 for s in re.split(r'\\[npl]',line))
spec=importlib.util.spec_from_file_location('parade_rom',R/'tools/parade/validate_rom.py')
romcheck=importlib.util.module_from_spec(spec);spec.loader.exec_module(romcheck)
assert romcheck.read(romcheck.address('OlivinePomParty'),'<I') == romcheck.address('GoldenrodCity_House2_Layout')
events=romcheck.address('OlivinePomParty_ObjectEvents')
for i,o in enumerate(room['object_events']):
    assert romcheck.read(events+i*24+16,'<I') == romcheck.address(o['script'])
    assert [romcheck.read(events+i*24+4,'<h'),romcheck.read(events+i*24+6,'<h')] == [o['x'],o['y']]
assert romcheck.read(romcheck.address('OlivineCity_House2_ObjectEvents')+2*24+16,'<I') == romcheck.address('OlivinePomParty_Invite')
print('PASS cloned ring, historical IDs/events, host approaches, exit, wrapped callback and seven live script registrations')
warp = romcheck.address('OlivinePomParty_MapWarps')
assert [romcheck.read(warp,'<h'),romcheck.read(warp+2,'<h')] == [4,8]
assert romcheck.read(warp+5,'<B') == 0
assert romcheck.read(warp+6,'<B') == prior['gMapGroup_IndoorOlivine'].index('OlivineCity_House2')
assert romcheck.read(warp+7,'<B') == prior['group_order'].index('gMapGroup_IndoorOlivine')
print('PASS compiled native door destination back to Olivine brothers house')
