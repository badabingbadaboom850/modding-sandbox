#!/usr/bin/env python3
"""Execute the real guide/selector scripts and validate current map geometry."""
import collections
import itertools
import json
import re
import subprocess
import sys
from pathlib import Path
import validate_rift as v

ROOT = Path(__file__).resolve().parents[2]
BASE = 'c231a90d32c67c678ab980da7090631b50ae2b4b'
source = (ROOT / 'data/scripts/trio_echo_catchup.inc').read_text()
for line in source.splitlines():
    line = line.strip()
    if not line or line.startswith('@'):
        continue
    if re.fullmatch(r'\w+::?', line):
        label = line.rstrip(':')
        assert label not in v.LABELS
        v.LABELS[label] = len(v.CODE)
    else:
        v.CODE.append(line)

flags = ['FLAG_TRIO_RIFT_COURAGE_RECEIVED', 'FLAG_TRIO_RIFT_FIRE_RECEIVED',
         'FLAG_TRIO_RIFT_BRAVERY_RECEIVED']
states = ['VAR_TRIO_RIFT_RIKO_STATE', 'VAR_TRIO_RIFT_BIJUU_STATE',
          'VAR_TRIO_RIFT_PENNY_STATE']
destinations = ['MAP_TRIO_ECHO_WOODS', 'MAP_TRIO_MIRROR_HOUSE', 'MAP_TRIO_LANTERN_TRAIL']
cases = 0
for bits, picnic, girls, answer in itertools.product(range(8), (False, True), (False, True), (0, 1)):
    earned = [flag for i, flag in enumerate(flags) if bits & (1 << i)]
    for progress in itertools.product(range(6), repeat=3):
        run = v.Run(flags=earned + (['FLAG_TRIO_FESTIVAL_PICNIC'] if picnic else []),
                    girls=girls, answers=[answer] * 3)
        run.vars.update(zip(states, progress))
        before = dict(run.vars)
        run.run('TrioEchoCatchup_Guide')
        assert not run.locked and run.battles == 0 and run.gifts == 0
        assert run.flags == set(earned + (['FLAG_TRIO_FESTIVAL_PICNIC'] if picnic else []))
        assert all(run.vars[k] == before[k] for k in states)
        if picnic and girls and answer:
            first = next((i for i, f in enumerate(flags) if f not in earned), 0)
            assert len(run.warps) == 1 and run.warps[0][0] == destinations[first]
        else:
            assert not run.warps
        cases += 1

sys.path.insert(0, str(ROOT / 'tools/snack'))
from gang_geometry import geometry
for city, position in [('CianwoodPokecenter', (5, 6)),
                       ('MahoganyTown_PokemonCenter', (10, 6)),
                       ('OlivineCity_PokemonCenter', (10, 6))]:
    path = f'data/maps/{city}/map.json'
    old = json.loads(subprocess.check_output(['git', 'show', BASE + ':' + path], cwd=ROOT))
    now, w, h, walk = geometry(city)
    actors = now['object_events']
    if city == 'OlivineCity_PokemonCenter':
        expected = json.loads(json.dumps(old['object_events']))
        matches = [o for o in expected if o['script'] == 'TrioLantern_Entrance']
        assert len(matches) == 1
        matches[0]['script'] = 'TrioEchoCatchup_Guide'
        assert actors == expected
    else:
        assert actors[:-1] == old['object_events']
        assert actors[-1]['script'] == 'TrioEchoCatchup_Guide'
    assert {k: x for k, x in now.items() if k != 'object_events'} == {
        k: x for k, x in old.items() if k != 'object_events'}
    assert len(actors) + 2 <= 16
    assert walk(*position)
    guide = [o for o in actors if o['script'] == 'TrioEchoCatchup_Guide']
    assert len(guide) == 1 and (guide[0]['x'], guide[0]['y']) == position
    assert guide[0]['flag'] == '0' and guide[0]['trainer_type'] == 'TRAINER_TYPE_NONE'
    assert position not in {(e['x'], e['y']) for k in ('warp_events', 'coord_events', 'bg_events') for e in now[k]}
    blocked = {(o['x'], o['y']) for o in actors}
    start = (7, 7)
    seen = {start}
    q = collections.deque(seen)
    while q:
        x, y = q.popleft()
        for p in ((x+1, y), (x-1, y), (x, y+1), (x, y-1)):
            if p not in seen and p not in blocked and walk(*p):
                seen.add(p)
                q.append(p)
    for actor in actors:
        x, y = actor['x'], actor['y']
        if y > 2:  # Chansey/nurse stand behind their service counter.
            assert any(p in seen for p in ((x+1,y), (x-1,y), (x,y+1), (x,y-1))), actor

assert (ROOT / 'data/event_scripts.s').read_text().count('.include "data/scripts/trio_echo_catchup.inc"') == 1
for text in re.findall(r'\.string "(.*)"', source):
    assert text.endswith('$') and text.isascii()
    for page in text[:-1].split(r'\p'):
        lines = page.split(r'\n')
        assert len(lines) <= 2 and all(len(line) <= 26 for line in lines), lines
print(f'{cases} guide paths passed; three Centers preserve actors/services, reachable guides and saved progress.')
