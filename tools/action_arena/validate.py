#!/usr/bin/env python3
"""Actual event/geometry/font validation; not a rendered emulator playthrough."""
from pathlib import Path
import collections
import json
import re
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
BASE = '51e82674bf22a5ce2fadccd6d6414a43b964aebb'
sys.path.insert(0, str(ROOT / 'tools/snack'))
from gang_geometry import geometry

def old(path):
    return subprocess.check_output(['git', 'show', BASE + ':' + path], cwd=ROOT)

script = (ROOT / 'data/maps/TrioActionArena/scripts.inc').read_text()
labels = collections.Counter()
for path in [*ROOT.glob('data/maps/**/scripts.inc'), *ROOT.glob('data/scripts/*.inc')]:
    labels.update(re.findall(r'^(\w+)::?', path.read_text(), re.M))
for label in re.findall(r'\bTrioActionArena_\w+\b', script):
    assert labels[label] == 1, (label, labels[label])
assert (ROOT / 'data/event_scripts.s').read_text().count('.include "data/maps/TrioActionArena/scripts.inc"') == 1
specials = (ROOT / 'data/specials.inc').read_text()
assert specials.startswith(old('data/specials.inc').decode())
assert specials.count('def_special StartTrioActionArena') == 1
assert not re.search(r'^\s*(giveitem|removeitem|setflag|clearflag|trainerbattle\w*)\b', script, re.M)
assert re.findall(r'^\s*setvar (\w+)', script, re.M) == ['VAR_TEMP_A']
assert 'special StartTrioActionArena\n\tgoto_if_eq VAR_RESULT, FALSE, TrioActionArena_Unavailable\n\twaitstate' in script

for path in ['include/global.h', 'include/constants/flags.h',
             'include/constants/items.h', 'include/constants/species.h', 'include/constants/opponents.h',
             'data/layouts/layouts.json', 'src/new_game.c', 'src/battle_setup.c',
             'data/maps/NewBarkTown/scripts.inc', 'data/maps/NewBarkTown/scripts.pory']:
    assert (ROOT / path).read_bytes() == old(path), path
assert (ROOT / 'include/constants/vars.h').read_text().startswith(old('include/constants/vars.h').decode())
groups = json.loads((ROOT / 'data/maps/map_groups.json').read_text())
before = json.loads(old('data/maps/map_groups.json'))
assert groups['group_order'] == before['group_order']
for group in before['group_order']:
    assert groups[group] == before[group] + (['TrioActionArena'] if group == 'gMapGroup_IndoorNewBark' else []), group

newbark = json.loads((ROOT / 'data/maps/NewBarkTown/map.json').read_text())
baseline = json.loads(old('data/maps/NewBarkTown/map.json'))
assert newbark['object_events'][:-1] == baseline['object_events']
assert {k:v for k,v in newbark.items() if k != 'object_events'} == {k:v for k,v in baseline.items() if k != 'object_events'}
guide = newbark['object_events'][-1]
assert (guide['x'], guide['y'], guide['script'], guide['flag']) == (18, 14, 'TrioActionArena_Offer', '0')
assert guide['trainer_type'] == 'TRAINER_TYPE_NONE'

def flood(start, blocked, walk):
    assert walk(*start), start
    seen = {start}
    queue = collections.deque(seen)
    while queue:
        x,y = queue.popleft()
        for p in [(x+1,y), (x-1,y), (x,y+1), (x,y-1)]:
            if p not in seen and p not in blocked and walk(*p):
                seen.add(p); queue.append(p)
    return seen

for name, start in [('NewBarkTown', (18,12)), ('TrioActionArena', (12,15))]:
    m,w,h,walk = geometry(name)
    positions = [(o['x'], o['y']) for o in m['object_events']]
    assert len(positions) == len(set(positions)), name
    occupied = set(positions)
    seen = flood(start, occupied, walk)
    actors = m['object_events'][-1:] if name == 'NewBarkTown' else m['object_events']
    events = {(o['x'],o['y']) for key in ['warp_events','bg_events','coord_events'] for o in m[key]}
    for actor in actors:
        x,y = actor['x'], actor['y']
        assert walk(x,y) and (x,y) not in events, actor
        assert any(p in seen for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]), actor
        for xx in range(x-10,x+11):
            for yy in range(y-8,y+9):
                assert sum(abs(o['x']-xx)<=10 and abs(o['y']-yy)<=8 for o in m['object_events'])+2 <= 16, (name,xx,yy)
    if name == 'NewBarkTown':
        assert flood(start, occupied - {(18,14)}, walk) - {(18,14)} == seen
    else:
        assert (11,16) in seen and (12,16) in seen
        assert len(m['object_events']) == 5
        assert all(o['dest_map'] == 'MAP_NEW_BARK_TOWN' and o['dest_warp_id'] == '1' for o in m['warp_events'])

# Both inherited boundary arrows have actual south-arrow behavior, not plain grass.
layouts = json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts']
layout = next(v for v in layouts if v['id'] == 'LAYOUT_TRIO_GARDEN')
tiles = struct.unpack('<' + str(layout['width']*layout['height']) + 'H', (ROOT/layout['blockdata_filepath']).read_bytes())
attrs = (ROOT/'data/tilesets/primary/johto_general/metatile_attributes.bin').read_bytes()
for x in [11,12]:
    tile = tiles[17*layout['width']+x]
    assert tile & 0x7FF < 1024
    assert struct.unpack_from('<H', attrs, (tile & 0x7FF)*2)[0] & 255 == 0x65

# Actual production font widths and conservative dialogue page limits.
chars = {}
for line in (ROOT/'charmap.txt').read_text().splitlines():
    match = re.match(r"^('.*?')\s*=\s*([\da-fA-F]{2})\b", line)
    if match: chars[match[1][1:-1].replace("\\'", "'")] = int(match[2],16)
font = (ROOT/'src/fonts.c').read_text()
widths = list(map(int,re.findall(r'\b\d+\b',font.split('gFontNormalLatinGlyphWidths[] = {')[1].split('};')[0])))
for text in re.findall(r'\.string "(.*?)"',script):
    assert text.endswith('$') and text.isascii(), text
    for page in text[:-1].split(r'\p'):
        assert len(page.split(r'\n')) <= 2, page
        for line in page.split(r'\n'):
            assert len(line) <= 26 and sum(widths[chars[c]] for c in line) <= 208, line
print('PASS: reachable guide, preserved paths/story/IDs/save ABI, five reachable lobby actors, sixteen-object budget, both native exits, exact script/special registration and dialogue widths')

# Execute the actual travel/referee instructions with minimal engine stubs.
code=[]; target={}
for line in script.splitlines():
    line=line.strip()
    if not line or line.startswith('.string'): continue
    if re.fullmatch(r'\w+::?',line): target[line.rstrip(':')]=len(code)
    else: code.append(line)
def run(label, answer, ready=True):
    pc=target[label]; locked=False; warps=[]; waits=0; result=0; started=0
    for _ in range(100):
        op,_,rest=code[pc].partition(' ');pc+=1
        args=[v.strip() for v in rest.split(',')]
        value=lambda v: {'VAR_RESULT':result,'YES':1,'FALSE':0}.get(v,v)
        if op=='end':
            assert not locked
            return warps,waits,started
        if op=='lockall': locked=True
        elif op=='releaseall': locked=False
        elif op in ['faceplayer','closemessage']: pass
        elif op=='msgbox':
            if args[1]=='MSGBOX_YESNO': result=answer
        elif op=='special': started+=1;result=int(ready)
        elif op=='waitstate': waits+=1
        elif op=='warp': warps.append(args)
        elif op=='goto': pc=target[args[0]]
        elif op=='goto_if_ne':
            if value(args[0])!=value(args[1]): pc=target[args[2]]
        elif op=='goto_if_eq':
            if value(args[0])==value(args[1]): pc=target[args[2]]
        else: raise AssertionError(op)
    raise AssertionError('script loop')
for yes in [0,1]:
    assert run('TrioActionArena_Offer',yes)==([['MAP_TRIO_ACTION_ARENA','12','15']] if yes else [],yes,0)
    assert run('TrioActionArena_Exit',yes)==([['MAP_NEW_BARK_TOWN','18','12']] if yes else [],yes,0)
    for ready in [False,True]:
        assert run('TrioActionArena_Referee',yes,ready)==([],int(yes and ready),yes)
assert run('TrioActionArena_WalkExit',0)==([['MAP_NEW_BARK_TOWN','18','12']],1,0)
for girl in ['Riko','Bijuu','Penny']: assert run('TrioActionArena_'+girl,0)==([],0,0)
print('PASS: actual travel decline/accept, referee decline/setup-failure/resume, all interactions and walk-out release locks correctly')
