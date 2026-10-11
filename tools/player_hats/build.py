"""Convert PNG palettes to native indexed inputs; compile accessories in C.

The design is imagegen art. This script only handles file-format conversion;
render.c owns native frame assembly, leaving the historical body art intact.
"""
from pathlib import Path
from PIL import Image
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
subprocess.run(['cc', '-O2', str(ROOT/'tools/player_hats/render.c'), '-o', '/tmp/soulgold-hat-render'], check=True)
atlas = Image.open(ROOT/'graphics/player_hats/accessory-reference.png').convert('RGBA')
assert atlas.size == (1536, 1024)
raw = ROOT/'graphics/player_hats/accessory-reference.rgba'
raw.write_bytes(atlas.tobytes())
try:
    sources = list((ROOT/'graphics/object_events/pics/people/may').glob('*.png'))
    sources += [ROOT/'graphics/trainers/front_pics/may.png', ROOT/'graphics/trainers/back_pics/may.png']
    for source in sources:
        im = Image.open(source)
        kind = 1 if 'front_pics' in str(source) else 2 if 'back_pics' in str(source) else 3 if source.stem == 'underwater' else 0
        fw, fh = (64, 64) if kind in (1,2) else (16 if source.stem in ('walking', 'running', 'decorating') else 32, 32)
        for style, name in [(1, 'bow'), (2, 'sunhat')]:
            dest = ROOT/'graphics/player_hats'/name/('front' if kind==1 else 'back' if kind==2 else source.stem+'.png')
            if kind in (1,2): dest = dest.with_suffix('.png')
            dest.parent.mkdir(parents=True, exist_ok=True)
            with tempfile.TemporaryDirectory() as td:
                inp, out = Path(td)/'in.raw', Path(td)/'out.raw'
                inp.write_bytes(im.tobytes())
                subprocess.run(['/tmp/soulgold-hat-render', str(inp), str(out), *map(str, [*im.size, fw, fh, kind, style])], cwd=ROOT, check=True)
                result = Image.frombytes('P', im.size, out.read_bytes())
                result.putpalette(im.getpalette()); result.save(dest, transparency=0)
finally:
    raw.unlink()
