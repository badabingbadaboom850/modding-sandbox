"""Check actual native battle frames, palette bindings and historical ball data."""
from pathlib import Path
from PIL import Image
import subprocess
R=Path(__file__).resolve().parents[2]
BASE='a4ddf82d8345934986be723cbadd2e7ebee92845'
for p in ['include/constants/items.h','include/constants/pokeball.h','src/data/items.h','src/battle_script_commands.c','src/new_game.c']:
    assert (R/p).read_bytes()==subprocess.check_output(['git','show',BASE+':'+p],cwd=R),p
registrations=(R/'src/data/graphics/pokeballs.h').read_text()
for ball in ['great','ultra','moon','love']:
    for path in [f'graphics/items/icons/{ball}_ball.png',f'graphics/items/icon_palettes/{ball}_ball.pal']:
        assert (R/path).read_bytes().replace(b'\r\n',b'\n')==subprocess.check_output(['git','show',BASE+':'+path],cwd=R).replace(b'\r\n',b'\n'),path
    p=R/f'graphics/balls/{ball}.png';im=Image.open(p)
    assert im.size==(16,48) and im.mode=='P' and im.info['transparency']==0
    pal=[int(x) for line in (R/f'graphics/items/icon_palettes/{ball}_ball.pal').read_text().splitlines()[3:] for x in line.split()]
    assert im.getpalette()[:48]==pal and max(im.tobytes())<16
    encoded=bytearray()
    for fy in range(0,48,16):
        for ty in range(0,16,8):
            for tx in range(0,16,8):
                for y in range(8):
                    for x in range(0,8,2):
                        encoded.append(im.getpixel((tx+x,fy+ty+y))|im.getpixel((tx+x+1,fy+ty+y))<<4)
    assert encoded==p.with_suffix('.4bpp').read_bytes()
    pixels=im.tobytes();assert pixels[:256]!=pixels[256:512] and pixels[256:512]!=pixels[512:]
    assert f'gBallPal_{ball.capitalize()}[] = INCBIN_U16("graphics/items/icon_palettes/{ball}_ball.gbapal")' in registrations
print('PASS: 12 complete compiled custom-ball frames; Bag palettes, item/capture IDs, catch-rate code and saved data unchanged')
