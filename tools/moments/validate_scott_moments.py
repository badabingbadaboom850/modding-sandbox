#!/usr/bin/env python3
"""Interpret the actual optional scripts and decode NPC approach geometry.

Source checks only: interactive rendering and save/reload need an emulator.
"""
from pathlib import Path
import collections
import itertools
import json
import re
import struct
import subprocess
import unittest

ROOT = Path(__file__).resolve().parents[2]
BASE = '471af8a86c95440d4e2d25c665ca4c33888143ec'
SOURCE = (ROOT / 'data/scripts/trio_scott_moments.inc').read_text()
STOPS = [
    ('Azalea', 'AzaleaTown', '02', 'johto_general', 'azalea_town'),
    ('Ecruteak', 'EcruteakCity', '04', 'johto_general', 'ecruteak_city'),
    ('Olivine', 'OlivineCity', '06', 'johto_general', 'olivine_city'),
    ('Blackthorn', 'BlackthornCity', '08', 'johto_north_west', 'blackthorn'),
]
LABELS, CODE = {}, []
for line in SOURCE.splitlines():
    line = line.strip()
    if not line or line.startswith('@'):
        continue
    if re.fullmatch(r'\w+::?', line):
        label = line.rstrip(':')
        assert label not in LABELS, label
        LABELS[label] = len(CODE)
    elif not line.startswith('.string'):
        CODE.append(line)


class Run:
    def __init__(self, flags=(), answer=1, locked=False):
        self.flags = set(flags)
        self.answer = answer
        self.result = None
        self.locked = locked
        self.text = []
        self.writes = []
        self.ended = False
        self.menu = False

    def run(self, label):
        pc, stack = LABELS[label], []
        for _ in range(300):
            line = CODE[pc]
            pc += 1
            op, _, rest = line.partition(' ')
            a = [v.strip() for v in rest.split(',')]
            if op == 'lockall':
                self.locked = True
            elif op == 'releaseall':
                self.locked = False
            elif op in ('closemessage', 'faceplayer'):
                pass
            elif op == 'msgbox':
                self.text.append(a[0])
                if a[1] == 'MSGBOX_YESNO':
                    self.result = self.answer
            elif op == 'setflag':
                self.flags.add(a[0])
                self.writes.append(a[0])
            elif op == 'return':
                if not stack:
                    return self
                pc = stack.pop()
            elif op == 'end':
                self.ended = True
                return self
            elif op == 'call':
                stack.append(pc)
                pc = LABELS[a[0]]
            elif op == 'goto':
                if a[0] == 'TrioScrapbook_Menu':
                    self.menu = True
                    return self
                pc = LABELS[a[0]]
            elif op in ('goto_if_set', 'goto_if_unset'):
                if (a[0] in self.flags) == (op == 'goto_if_set'):
                    pc = LABELS[a[1]]
            elif op == 'goto_if_eq':
                assert a[:2] == ['VAR_RESULT', 'NO'], line
                if self.result == 0:
                    pc = LABELS[a[2]]
            else:
                raise AssertionError(line)
        raise AssertionError('script failed to terminate')


class Checks(unittest.TestCase):
    def test_badge_gates_and_declining(self):
        for name, _, badge, *_ in STOPS:
            flag = 'FLAG_TRIO_SCOTT_' + name.upper()
            gate = 'FLAG_BADGE' + badge + '_GET'
            # Later badges alone never invent the specific local victory.
            other = {'FLAG_BADGE' + b + '_GET' for b in ['01','02','03','04','05','06','07','08']} - {gate}
            for flags in [set(), other, {flag}]:
                r = Run(flags).run('TrioScott_' + name)
                self.assertEqual(r.text, ['TrioScott_' + name + '_WaitText'])
                self.assertEqual(r.flags, flags)
                self.assertFalse(r.locked)
                self.assertTrue(r.ended)
            r = Run({gate}, answer=0).run('TrioScott_' + name)
            self.assertEqual(r.flags, {gate})
            self.assertEqual(r.writes, [])
            self.assertNotIn('TrioScott_' + name + '_Memory', r.text)
            self.assertFalse(r.locked)

    def test_accept_and_repeat_are_independent(self):
        for order in itertools.permutations(STOPS):
            flags = {'FLAG_BADGE' + row[2] + '_GET' for row in STOPS}
            for name, *_ in order:
                flag = 'FLAG_TRIO_SCOTT_' + name.upper()
                first = Run(flags).run('TrioScott_' + name)
                self.assertEqual(first.writes, [flag])
                self.assertEqual(first.flags, flags | {flag})
                self.assertEqual(first.text[-1], 'TrioSisters_Recorded')
                self.assertFalse(first.locked)
                flags = first.flags
                for answer in [0, 1]:
                    again = Run(flags, answer).run('TrioScott_' + name)
                    self.assertEqual(again.flags, flags)
                    self.assertEqual(again.writes, [])
                    self.assertEqual(again.text[0], 'TrioScott_ReplayOffer')
                    self.assertFalse(again.locked)
                    self.assertEqual('TrioScott_' + name + '_Memory' in again.text, answer == 1)

    def test_book_and_checklist_do_not_create_memories(self):
        names = [row[0] for row in STOPS]
        for bits in itertools.product([False, True], repeat=4):
            # No party or badges are required to read an already saved page.
            flags = {'FLAG_TRIO_SCOTT_' + name.upper() for name, bit in zip(names, bits) if bit}
            r = Run(flags, locked=True).run('TrioScott_Scrapbook')
            self.assertTrue(r.menu)
            self.assertTrue(r.locked)
            self.assertEqual(r.flags, flags)
            self.assertEqual(r.writes, [])
            self.assertEqual(r.text[1:], ['TrioScott_' + name + ('_Memory' if bit else '_Hint') for name, bit in zip(names, bits)])
            r = Run(flags, locked=True).run('TrioScott_Checklist')
            self.assertEqual(r.text, ['TrioScott_' + name + ('_SavedText' if bit else '_Hint') for name, bit in zip(names, bits)])
            self.assertEqual(r.flags, flags)
            self.assertTrue(r.locked)

    def test_original_map_events_and_reachable_placements(self):
        layouts = json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts']
        for name, city, _, primary, secondary in STOPS:
            path = 'data/maps/' + city + '/map.json'
            old = json.loads(subprocess.check_output(['git', 'show', BASE + ':' + path], cwd=ROOT, text=True))
            new = json.loads((ROOT/path).read_text())
            self.assertEqual(new['object_events'][:-1], old['object_events'])
            self.assertEqual({k:v for k,v in new.items() if k != 'object_events'}, {k:v for k,v in old.items() if k != 'object_events'})
            o = new['object_events'][-1]
            self.assertEqual(o['script'], 'TrioScott_' + name)
            self.assertEqual(o['flag'], '0')
            self.assertEqual(o['graphics_id'], 'OBJ_EVENT_GFX_SILVER')
            layout = next(l for l in layouts if l['id'] == new['layout'])
            w, h = layout['width'], layout['height']
            blocks = struct.unpack('<' + str(w*h) + 'H', (ROOT/layout['blockdata_filepath']).read_bytes())
            attrs = [(ROOT/('data/tilesets/'+kind+'/'+folder+'/metatile_attributes.bin')).read_bytes() for kind,folder in [('primary',primary),('secondary',secondary)]]
            def walk(x,y):
                if not (0 <= x < w and 0 <= y < h):
                    return False
                v = blocks[y*w+x]
                i = v & 2047
                behavior = struct.unpack_from('<H', attrs[i >= 1024], (i % 1024)*2)[0] & 255
                return not (v & 0x800) and behavior in (0,2,3,7)
            pos = (o['x'], o['y'])
            occupied = {(a['x'],a['y']) for a in old['object_events']}
            for a in old['object_events']:
                if 'WANDER' in a['movement_type']:
                    for dx in range(-a['movement_range_x'], a['movement_range_x']+1):
                        for dy in range(-a['movement_range_y'], a['movement_range_y']+1):
                            occupied.add((a['x']+dx,a['y']+dy))
            self.assertNotIn(pos, occupied)
            self.assertTrue(walk(*pos))
            self.assertNotIn(pos, {(a['x'],a['y']) for a in new['coord_events']+new['warp_events']+new['bg_events']})
            occupied.add(pos)
            # Start from a real outdoor warp exit, not an arbitrary nearby tile.
            seed = (new['warp_events'][0]['x'], new['warp_events'][0]['y']+1)
            seen, q = {seed}, collections.deque([seed])
            while q:
                x,y = q.popleft()
                for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
                    if p not in seen and p not in occupied and walk(*p):
                        seen.add(p)
                        q.append(p)
            approaches = [(pos[0]+1,pos[1]),(pos[0]-1,pos[1]),(pos[0],pos[1]+1),(pos[0],pos[1]-1)]
            self.assertTrue(any(p in seen for p in approaches), city)
            # Check every camera position near Scott, even unwalkable ones:
            # adding him must not overfill the visible object pool while passing.
            for x in range(pos[0]-10, pos[0]+11):
                for y in range(pos[1]-8, pos[1]+9):
                    budget = sum(abs(a['x']-x) <= 10 and abs(a['y']-y) <= 8 for a in new['object_events']) + 2
                    self.assertLessEqual(budget, 16, (city,x,y,budget))
            for x,y in [p for p in approaches if p in seen]:
                # All templates, even hidden/night pairs, plus player/follower.
                budget = sum(abs(a['x']-x) <= 10 and abs(a['y']-y) <= 8 for a in new['object_events']) + 2
                self.assertLessEqual(budget, 16, (city,x,y,budget))
                # Original temporary Silver must not share Scott's viewport.
                for a in old['object_events']:
                    if a['graphics_id'] == 'OBJ_EVENT_GFX_SILVER':
                        self.assertFalse(abs(a['x']-x) <= 10 and abs(a['y']-y) <= 8, city)

    def test_registration_labels_text_and_menu(self):
        self.assertIn('.include "data/scripts/trio_scott_moments.inc"', (ROOT/'data/event_scripts.s').read_text())
        memories = (ROOT/'data/scripts/trio_memories.inc').read_text()
        self.assertIn('goto_if_eq VAR_RESULT, 4, TrioScott_Scrapbook', memories)
        self.assertIn('call TrioScott_Checklist', memories)
        menu = (ROOT/'src/data/script_menu.h').read_text().split('MultichoiceList_TrioScrapbook[]',1)[1].split('};',1)[0]
        self.assertEqual(re.findall(r'COMPOUND_STRING\("([^"]+)"\)', menu), ['Our journey','Sister moments','Spirit letters','Memory checklist','Scott moments'])
        self.assertEqual(menu.count('gText_Exit'), 1)
        all_labels = collections.Counter()
        for p in itertools.chain((ROOT/'data/maps').rglob('scripts.inc'), (ROOT/'data/scripts').glob('*.inc')):
            all_labels.update(re.findall(r'^(\w+)::?', p.read_text(), re.M))
        for label in LABELS:
            self.assertEqual(all_labels[label], 1, label)
        for target in re.findall(r'^\s*(?:call|goto|goto_if_set|goto_if_unset|goto_if_eq|msgbox)\s+([^\n]+)', SOURCE,re.M):
            args = [a.strip() for a in target.split(',')]
            ref = args[0] if len(args) < 3 and args[0] not in ('VAR_RESULT',) and not args[0].startswith('FLAG_') else args[-1]
            if args[0].startswith('FLAG_'):
                ref = args[1]
            if args[-1].startswith('MSGBOX_'):
                ref = args[0]
            self.assertEqual(all_labels[ref], 1, ref)
        for label,text in re.findall(r'^(\w+):\n\s*\.string "([^\n]+)"', SOURCE, re.M):
            self.assertTrue(text.endswith('$'),label)
            self.assertTrue(text.isascii(),label)
            for page in text[:-1].split(r'\p'):
                lines = page.split(r'\n')
                self.assertLessEqual(len(lines),2,label)
                self.assertTrue(all(len(line) <= 26 for line in lines),(label,lines))

    def test_flags_fit_existing_save_and_are_unique(self):
        src = (ROOT/'include/constants/flags.h').read_text()
        rows = re.findall(r'^#define (FLAG_TRIO_SCOTT_\w+)\s+(0x\w+)',src,re.M)
        self.assertEqual(len(rows),4)
        values = [int(v,16) for _,v in rows]
        self.assertEqual(values, list(range(0x1081,0x1085)))
        for name,value in rows:
            same = re.findall(r'^#define (\w+)\s+'+value+r'\b',src,re.M)
            self.assertEqual(same,[name])
            self.assertLess(int(value,16),0x1500)
        end_name = re.search(r'^#define CUSTOM_FLAGS_END\s+(\w+)',src,re.M).group(1)
        end_value = int(re.search(r'^#define '+end_name+r'\s+(0x\w+)',src,re.M).group(1),16)
        self.assertGreaterEqual(end_value, max(values))
        self.assertLess(end_value, 0x1500)
        writes = re.findall(r'^\s*setflag (\w+)',SOURCE,re.M)
        self.assertCountEqual(writes,[name for name,_ in rows])
        self.assertNotRegex(SOURCE, r'\b(giveitem|setvar|special|trainerbattle|applymovement|warp|clearflag)\b')


if __name__ == '__main__':
    unittest.main(verbosity=2)
