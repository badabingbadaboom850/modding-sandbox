"""Read-only accessory, registration and historical-save checks."""
from pathlib import Path
from PIL import Image
import json, re, subprocess

R = Path(__file__).resolve().parents[2]
BASE = 'f5d7a32d88b5d05f9946b3345399c26fcba78dfa'
def old(path):
    return subprocess.check_output(['git', 'show', BASE+':'+path], cwd=R)

for path in ['include/global.h', 'include/global.fieldmap.h',
             'include/constants/flags.h',
             'include/constants/event_objects.h']:
    assert (R/path).read_bytes().replace(b'\r\n',b'\n') == old(path).replace(b'\r\n',b'\n'), path

# More-pink wardrobe edits are palette-only; protect skin, brown hair, outlines,
# transparency and white highlights against the original accessory baseline.
palette_changes = {'graphics/object_events/palettes/may.pal': {7: (238, 172, 205), 9: (255, 210, 237), 12: (255, 164, 214), 13: (222, 89, 164)}, 'graphics/object_events/palettes/may_reflection.pal': {7: (247, 222, 239), 9: (255, 238, 249), 12: (255, 222, 242), 13: (248, 194, 226)}, 'graphics/trainers/palettes/may.pal': {1: (222, 89, 164), 2: (205, 123, 164), 6: (255, 164, 214), 14: (255, 210, 237)}, 'graphics/trainers/palettes/may_back.pal': {1: (222, 89, 164), 2: (255, 164, 214), 3: (255, 210, 237)}}
for path, replacements in palette_changes.items():
    prior = old(path).decode().splitlines()
    current = (R/path).read_text().splitlines()
    expected = prior.copy()
    for index, rgb in replacements.items():
        expected[index+3] = " ".join(map(str, rgb))
    assert current == expected, path

prior_species = dict(re.findall(r'^#define (SPECIES_\w+)\s+(.+)$', old('include/constants/species.h').decode(), re.M))
current_species = dict(re.findall(r'^#define (SPECIES_\w+)\s+(.+)$', (R/'include/constants/species.h').read_text(), re.M))
for name, value in prior_species.items():
    if name != 'SPECIES_EGG': assert current_species[name] == value, name
assert '0x4144' not in old('include/constants/vars.h').decode()
assert '0x4144' in (R/'include/constants/vars.h').read_text()

sources = list((R/'graphics/object_events/pics/people/may').glob('*.png'))
sources += [R/'graphics/trainers/front_pics/may.png', R/'graphics/trainers/back_pics/may.png']
frames = changed = 0
for source in sources:
    assert source.read_bytes() == old(str(source.relative_to(R)))
    original = Image.open(source)
    kind = 1 if 'front_pics' in str(source) else 2 if 'back_pics' in str(source) else 0
    fw, fh = (64,64) if kind else (16 if source.stem in ('walking','running','decorating') else 32,32)
    for style in ['bow','sunhat']:
        path = R/'graphics/player_hats'/style/('front.png' if kind==1 else 'back.png' if kind==2 else source.name)
        result = Image.open(path)
        assert result.size == original.size and result.mode == 'P', path
        assert result.getpalette() == original.getpalette(), path
        assert max(result.tobytes()) < 16, path
        # Decode the actual frame-sized tile blocks used by the engine. Whole-
        # sheet tile order is valid 4bpp but tears a horizontal sprite atlas.
        binary = path.with_suffix('.4bpp').read_bytes()
        expected = bytearray()
        for fy in range(0,result.height,fh):
            for fx in range(0,result.width,fw):
                for ty in range(0,fh,8):
                    for tx in range(0,fw,8):
                        for y in range(8):
                            for x in range(0,8,2):
                                expected.append(result.getpixel((fx+tx+x,fy+ty+y)) | result.getpixel((fx+tx+x+1,fy+ty+y)) << 4)
        assert binary == expected, ('Compiled frame packing mismatch',path)
        a,b=original.load(),result.load()
        for fy in range(0,original.height,fh):
            for fx in range(0,original.width,fw):
                frames += 1
                gold = (14,9) if source.stem == 'underwater' else (12,13) if not kind else (6,1) if kind==1 else (2,1)
                points=[(x,y) for y in range(fh) for x in range(fw) if a[fx+x,fy+y] in gold]
                assert points, (path,fx,fy)
                top=min(y for x,y in points)
                head=[(x,y) for x,y in points if y <= top+(18 if kind else 7)]
                bottom=max(y for x,y in head)
                diff=[(x,y) for y in range(fh) for x in range(fw) if a[fx+x,fy+y]!=b[fx+x,fy+y]]
                assert diff, (path,fx,fy)
                assert all(top-1<=y<=bottom+(2 if kind else 1) for x,y in diff), (path,fx,fy,diff)
                changed += len(diff)

# Walking-only family accessories: body and historical compiled atlas order.
family_frames = 0
for style in ['riko', 'penny', 'bijuu']:
    for sheet in ['walking', 'running']:
        source = Image.open(R/'graphics/object_events/pics/people/may'/f'{sheet}.png')
        path = R/'graphics/player_hats'/style/f'{sheet}.png'
        result = Image.open(path)
        assert result.size == source.size and result.mode == 'P'
        assert result.getpalette() == source.getpalette()
        assert max(result.tobytes()) < 16
        binary = bytearray()
        for fx in range(0,result.width,16):
            gold = [(x,y) for y in range(32) for x in range(16) if source.getpixel((fx+x,y)) in (12,13)]
            top = min(y for x,y in gold)
            bottom = max(y for x,y in gold if y <= top+7)
            diff = [(x,y) for y in range(32) for x in range(16) if source.getpixel((fx+x,y)) != result.getpixel((fx+x,y))]
            assert diff and all(top-3 <= y <= bottom for x,y in diff), (style,sheet,fx)
            assert all(result.getpixel((fx+x,y)) == source.getpixel((fx+x,y)) for y in range(bottom+1,32) for x in range(16))
            for ty in range(0,32,8):
                for tx in range(0,16,8):
                    for y in range(8):
                        for x in range(0,8,2):
                            binary.append(result.getpixel((fx+tx+x,ty+y)) | result.getpixel((fx+tx+x+1,ty+y)) << 4)
            family_frames += 1
        assert path.with_suffix('.4bpp').read_bytes() == binary, path
        assert len(set(result.tobytes())) > 5
assert family_frames == 54

j=json.loads((R/'data/maps/NewBarkTown_PlayersHouse_2F/map.json').read_text())
prior=json.loads(old('data/maps/NewBarkTown_PlayersHouse_2F/map.json'))
assert j['warp_events']==prior['warp_events'] and j['coord_events']==prior['coord_events']
assert j['object_events']==prior['object_events']
assert j['bg_events'][-1]['script']=='TrioPlayerHat_Wardrobe'
assert (j['bg_events'][-1]['x'],j['bg_events'][-1]['y'])==(6,1)
assert all(j['bg_events'][i]==prior['bg_events'][i] for i in range(len(j['bg_events'])-1))
s=(R/'data/scripts/trio_player_hats.inc').read_text()
assert s.index('goto_if_ge TrioPlayerHat_Exit') < s.index('special ApplyTrioPlayerHat')
for text in re.findall(r'\.string "(.*?)"',s):
    for page in text.rstrip('$').split('\\p'):
        lines=page.split('\\n');assert len(lines)<=2
        assert all(len(line)<=26 for line in lines), lines
assert 'gObjectEventGraphicsInfo_MayNormal' in (R/'src/data/object_events/object_event_graphics_info_pointers.h').read_text()
assert 'TRIO_PLAYER_HAT_GFX_BASE' in (R/'src/event_object_movement.c').read_text()
assert 'GetRivalAvatarGraphicsIdByStateIdAndGender(u8 state, enum Gender gender)\n{\n    return sRivalAvatarGfxIds[state][gender];' in (R/'src/field_player_avatar.c').read_text()
print(f'PASS: {frames} original plus {family_frames} family native accessory frames, {changed} head pixels; body/ABI source unchanged; authorized pink palettes verified; wardrobe cancellation and historical events intact')

menu = (R/'src/data/script_menu.h').read_text().split('MultichoiceList_PlayerHats[]')[1].split('};')[0]
assert menu.index('Riko Hat') < menu.index('Penny Hat') < menu.index('Bijuu Hat')
assert 'hot dog' not in menu.lower()
assert 'compare VAR_RESULT, 6' in s
print('PASS: hidden Penny surprise, six saved choices, menu cancel/Exit guard')
