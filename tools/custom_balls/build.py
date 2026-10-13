"""Format conversion for the imagegen battle sheets and native palette compiler."""
from pathlib import Path
from PIL import Image
import subprocess,tempfile
R=Path(__file__).resolve().parents[2]
subprocess.run(['cc','-O2',str(R/'tools/custom_balls/index.c'),'-o','/tmp/soulgold-ball-index'],check=True)
for ball in ['great','ultra','moon','love']:
    source=Image.open(R/f'graphics/balls/custom_sources/{ball}.png').convert('RGBA')
    colors=[int(v) for line in (R/f'graphics/items/icon_palettes/{ball}_ball.pal').read_text().splitlines()[3:] for v in line.split()]
    assert len(colors)==48
    with tempfile.TemporaryDirectory() as td:
        inp,out,pal=Path(td)/'in.rgba',Path(td)/'out.idx',Path(td)/'palette.txt'
        inp.write_bytes(source.tobytes());pal.write_text(' '.join(map(str,colors)))
        subprocess.run(['/tmp/soulgold-ball-index',str(inp),str(out),*map(str,source.size),str(pal)],check=True)
        indexed=Image.frombytes('P',(16,48),out.read_bytes());indexed.putpalette(colors)
        indexed.save(R/f'graphics/balls/{ball}.png',transparency=0)
