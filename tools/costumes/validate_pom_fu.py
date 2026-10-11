"""Actual gift-script flows, native frame packing and save-history checks."""
from pathlib import Path
from PIL import Image
import subprocess,re,itertools
R=Path(__file__).resolve().parents[2]
BASE='0fdc8cb5e8031ed2fbb8a7821dcc287429d8843e'
def old(path):return subprocess.check_output(['git','show',BASE+':'+path],cwd=R)
path='data/maps/CianwoodCity/scripts.inc'
s=(R/path).read_text();prior=old(path).decode()
restored=s.replace('\tcall PomFu_Offer\n','',1)
assert restored.startswith(prior)
assert (R/'data/maps/CianwoodCity/map.json').read_bytes()==old('data/maps/CianwoodCity/map.json')
for path in ['include/global.h','include/global.fieldmap.h','src/new_game.c','include/constants/vars.h','include/constants/flags.h']:
    assert (R/path).read_bytes()==old(path),path
for path,prefix in [('include/constants/species.h','SPECIES_'),('include/constants/items.h','ITEM_')]:
    for name,value in re.findall(r'(?:#define\s+|\b)('+prefix+r'\w+)\s*(?:=|\s)\s*(\d+)\b',old(path).decode()):
        assert re.search(r'\b'+name+r'\s*(?:=|\s)\s*'+value+r'\b',(R/path).read_text()),name
labels={};code=[]
for line in s[s.index('PomFu_Offer::'):].splitlines():
    line=line.strip()
    if not line or line.startswith('@'):continue
    if re.fullmatch(r'\w+::?',line):labels[line.rstrip(':')]=len(code)
    else:code.append(line)
for owned,present,yes,room in itertools.product([0,1],repeat=4):
    pc=labels['PomFu_Offer'];result=0;gifts=0
    for step in range(80):
        op,_,args=code[pc].partition(' ');pc+=1;a=[p.strip() for p in args.split(',')]
        if op=='return':break
        elif op=='checkitem':result=owned
        elif op=='call':assert a[0]=='TrioParty_CheckRiko';result=present
        elif op=='checkspecies':result=0
        elif op in ['goto_if_eq','goto_if_ne']:
            eq=result=={'TRUE':1,'FALSE':0,'NO':0}[a[1]]
            if eq==(op=='goto_if_eq'):pc=labels[a[2]]
        elif op=='msgbox':
            if a[1]=='MSGBOX_YESNO':result=yes
        elif op=='giveitem':gifts+=room;result=room
        else:raise AssertionError(op)
    else:raise AssertionError('nonterminating gift')
    assert gifts==int(not owned and present and yes and room)
assert 'setflag' not in s[s.index('PomFu_Offer::'):]
for text in re.findall(r'\.string "(.*?)"',s[s.index('PomFu_Offer::'):]):
    assert text.endswith('$')
    for page in text[:-1].split(r'\p'):
        lines=page.split(r'\n');assert len(lines)<=2 and all(len(l)<=26 for l in lines),lines
print('PASS16 actual gift/decline/missing/owned/full-Bag paths; original NPC/map/history retained')
p=R/'graphics/pokemon/riko_fighting'
palette=[int(v) for line in (p/'normal.pal').read_text().splitlines()[3:] for v in line.split()]
for name,size,fw,fh in [('front',(64,64),64,64),('back',(64,64),64,64),('icon',(32,64),32,32),('overworld',(192,32),32,32)]:
    im=Image.open(p/(name+'.png'))
    assert im.size==size and im.mode=='P' and im.info['transparency']==0
    assert im.getpalette()[:48]==palette and max(im.tobytes())<16
    expected=bytearray()
    for fy in range(0,im.height,fh):
        for fx in range(0,im.width,fw):
            for ty in range(0,fh,8):
                for tx in range(0,fw,8):
                    for y in range(8):
                        for x in range(0,8,2):
                            expected.append(im.getpixel((fx+tx+x,fy+ty+y)) | im.getpixel((fx+tx+x+1,fy+ty+y))<<4)
    assert (p/(name+'.4bpp')).read_bytes()==expected,name
im=Image.open(R/'graphics/items/icons/riko_black_belt.png');assert im.size==(24,24) and max(im.tobytes())<16
assert len(set(Image.open(p/'overworld.png').tobytes()))>8
assert 'sRikoFightingTrioLevelUpLearnset' in (R/'src/data/pokemon/species_info.h').read_text()
print('PASS native battle/menu/six follower frames and transparent16-color item palette')
