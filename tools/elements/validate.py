"""Validate actual optional gift paths, historical IDs, and compiled sprite packing."""
from pathlib import Path
from PIL import Image
import subprocess,re,itertools,json
R=Path(__file__).resolve().parents[2]
BASE='dfd6fee8461daa67ff769b0063cf61d7c4ed393c'
def old(path):return subprocess.check_output(['git','show',BASE+':'+path],cwd=R)
forms=json.loads((R/'tools/elements/forms.json').read_text())
s=(R/'data/scripts/trio_complete_elements.inc').read_text();labels={};code=[]
for line in s.splitlines():
    line=line.strip()
    if not line or line.startswith('@'):continue
    if re.fullmatch(r'\w+::?',line):labels[line.rstrip(':')]=len(code)
    else:code.append(line)
assert not any(op in s for op in ['setflag','setvar','trainerbattle','lock','release'])
for f in forms:
    for owned,present,yes,room in itertools.product([0,1],repeat=4):
        pc=labels['TrioElement_'+f['camel']];result=0;gifts=0
        for step in range(80):
            op,_,args=code[pc].partition(' ');pc+=1;a=[p.strip() for p in args.split(',')]
            if op=='return':break
            elif op=='checkitem':assert a[0]=='ITEM_'+f['item'];result=owned
            elif op=='call':assert a[0]=='TrioParty_Check'+('Riko' if f['symbol'].startswith('RIKO') else 'Bijuu' if f['symbol'].startswith('BIJUU') else 'Penny');result=present
            elif op in ['goto_if_eq','goto_if_ne']:
                eq=result=={'TRUE':1,'FALSE':0,'NO':0}[a[1]]
                if eq==(op=='goto_if_eq'):pc=labels[a[2]]
            elif op=='msgbox':
                if a[1]=='MSGBOX_YESNO':result=yes
            elif op=='giveitem':assert a[0]=='ITEM_'+f['item'];gifts+=room;result=room
            else:raise AssertionError(op)
        else:raise AssertionError('nonterminating gift')
        assert gifts==int(not owned and present and yes and room)
    city=R/'data/maps'/f['city'];mapping=json.loads((city/'map.json').read_text())
    npc=[obj for obj in mapping['object_events'] if obj['script']==f['npc']];assert len(npc)==1
    assert [int(npc[0]['x']),int(npc[0]['y'])]==f['xy'];assert npc[0]['flag']=='0'
    assert (city/'map.json').read_bytes()==old('data/maps/'+f['city']+'/map.json')
    for ext in ['inc','pory']:
        path='data/maps/'+f['city']+'/scripts.'+ext
        if not (R/path).exists():continue
        current=(R/path).read_text();hook='TrioElement_'+f['camel']
        if ext=='inc':
            addition='\tcall '+hook+'\n'
            if f['symbol']=='RIKO_DRAGON':addition='\tlock\n\tfaceplayer\n'+addition+'\trelease\n'
        else:addition='\tcall '+hook+'\n'
        assert current.count(addition)==1,(path,addition)
        assert current.replace(addition,'',1)==old(path).decode(),path
for text in re.findall(r'\.string "(.*?)"',s):
    assert text.endswith('$')
    for page in text[:-1].split(r'\p'):
        lines=page.split(r'\n');assert len(lines)<=2 and all(len(l)<=26 for l in lines),lines
for path in ['include/global.h','include/global.fieldmap.h','src/new_game.c','include/constants/vars.h','include/constants/flags.h']:
    assert (R/path).read_bytes()==old(path),path
for path,prefix in [('include/constants/species.h','SPECIES_'),('include/constants/items.h','ITEM_')]:
    for name,value in re.findall(r'(?:#define\s+|\b)('+prefix+r'\w+)\s*(?:=|\s)\s*(\d+)\b',old(path).decode()):
        assert re.search(r'\b'+name+r'\s*(?:=|\s)\s*'+value+r'\b',(R/path).read_text()),name
for table in ['sRikoFormSpeciesIdTable','sBijuuFormSpeciesIdTable','sPennySpiritFormSpeciesIdTable']:
    path='src/data/pokemon/form_species_tables.h';pattern=table+r'\[\]\s*=\s*\{(.*?)\}'
    before=re.findall(r'\bSPECIES_\w+',re.search(pattern,old(path).decode(),re.S)[1]);after=re.findall(r'\bSPECIES_\w+',re.search(pattern,(R/path).read_text(),re.S)[1]);assert after[:len(before)]==before
print('PASS96 actual gift paths, six original NPC/map dispatches, dialogue, save ABI and historical IDs/form indices')
frames=0
for f in forms:
    p=R/'graphics/pokemon'/f['folder'];palette=[int(v) for line in (p/'normal.pal').read_text().splitlines()[3:] for v in line.split()]
    for name,size,fw,fh in [('front',(64,64),64,64),('back',(64,64),64,64),('icon',(32,64),32,32),('overworld',(192,32),32,32)]:
        im=Image.open(p/(name+'.png'));assert im.size==size and im.mode=='P' and im.info['transparency']==0
        assert im.getpalette()[:48]==palette and max(im.tobytes())<16
        expected=bytearray()
        for fy in range(0,im.height,fh):
            for fx in range(0,im.width,fw):
                frames+=1
                assert any(im.getpixel((x,y)) for y in range(fy,fy+fh) for x in range(fx,fx+fw))
                for ty in range(0,fh,8):
                    for tx in range(0,fw,8):
                        for y in range(8):
                            for x in range(0,8,2):expected.append(im.getpixel((fx+tx+x,fy+ty+y)) | im.getpixel((fx+tx+x+1,fy+ty+y))<<4)
        assert (p/(name+'.4bpp')).read_bytes()==expected,(f['folder'],name)
    im=Image.open(R/'graphics/items/icons'/(f['folder']+'_keepsake.png'));assert im.size==(24,24) and max(im.tobytes())<16
    assert (R/'graphics/items/icon_palettes'/(f['folder']+'_keepsake.pal')).read_text()==(p/'normal.pal').read_text()
print('PASS'+str(frames)+' native battle/menu/follower frames and six transparent16-color item icons')
