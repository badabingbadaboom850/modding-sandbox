"""Format conversion only; family_render.c owns native sprite assembly."""
from pathlib import Path
from PIL import Image
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
with tempfile.TemporaryDirectory() as td:
    td = Path(td)
    exe = td/'render'
    subprocess.run(['cc', '-O2', str(ROOT/'tools/player_hats/family_render.c'), '-o', str(exe)], check=True)
    for style in ['riko', 'penny', 'bijuu']:
        atlas = Image.open(ROOT/'graphics/player_hats/family_sources'/f'{style}.png').convert('RGBA')
        rgba = td/'atlas.rgba'; rgba.write_bytes(atlas.tobytes())
        for sheet in ['walking', 'running']:
            source = Image.open(ROOT/'graphics/object_events/pics/people/may'/f'{sheet}.png')
            inp, out = td/'in.raw', td/'out.raw'; inp.write_bytes(source.tobytes())
            subprocess.run([str(exe), str(inp), str(out), str(source.width), str(rgba), *map(str,atlas.size)], check=True)
            result = Image.frombytes('P', source.size, out.read_bytes())
            result.putpalette(source.getpalette())
            dest = ROOT/'graphics/player_hats'/style/f'{sheet}.png'
            dest.parent.mkdir(parents=True, exist_ok=True)
            result.save(dest, transparency=0)
