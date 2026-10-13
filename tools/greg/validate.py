"""Check new Greg geometry, source history, dialogue, reward and trainer teams."""
from pathlib import Path
import collections,json,re,subprocess,sys,itertools
R=Path(__file__).resolve().parents[2];BASE='e5a239bd4040ac0eb13aa81f89933470d150c01c'
from geometry import geometry
rows=json.loads((R/'tools/greg/locations.json').read_text());s=(R/'data/scripts/trio_greg_roaming.inc').read_text()
def old(p):return subprocess.check_output(['git','show',BASE+':'+p],cwd=R)
party=(R/'src/data/trainers.party').read_text();oldparty=old('src/data/trainers.party').decode();assert party.startswith(oldparty)
base=re.search(r'^=== TRAINER_GREG_ROUTE_29 ===\n(.*?)(?=^=== |\Z)',party,re.M|re.S)[1].strip()
for i,row in enumerate(rows):
    name=row['map'];m,w,h,walk=geometry(name);prior=json.loads(old('data/maps/'+name+'/map.json'))
    assert m['object_events'][:-1]==prior['object_events'];assert {k:v for k,v in m.items() if k!='object_events'}=={k:v for k,v in prior.items() if k!='object_events'}
    greg=m['object_events'][-1];assert [greg['x'],greg['y']]==row['xy'] and greg['flag']=='0'
    assert greg['script']=='GregRoam_'+name and greg['trainer_type']=='TRAINER_TYPE_NORMAL'
    assert greg['movement_type']=='MOVEMENT_TYPE_FACE_DOWN' and greg['trainer_sight_or_berry_tree_id']=='2'
    assert greg['local_id']==row['local_symbol'] and row['local_id']==len(m['object_events'])
    x,y=row['xy'];occ={(o['x'],o['y']) for o in prior['object_events']};tiles={(xx,yy) for yy in range(h) for xx in range(w) if walk(xx,yy)}-occ
    blocked={(x,y),(x,y+1),(x,y+2)};assert blocked<=tiles
    def flood(blocked):
        seen={(x-1,y)};q=collections.deque(seen)
        while q:
            xx,yy=q.popleft()
            for p in [(xx+1,yy),(xx-1,yy),(xx,yy+1),(xx,yy-1)]:
                if p in tiles and p not in seen|blocked:seen.add(p);q.append(p)
        return seen
    before=flood(set());after=flood(blocked);assert before-blocked==after,name
    # At least one building is accessible from the same outdoor component.
    assert any((v['x'],v['y']+1) in before for v in m['warp_events']),name
    for cx in range(x-10,x+11):
        for cy in range(y-8,y+9):assert sum(abs(o['x']-cx)<=10 and abs(o['y']-cy)<=8 for o in m['object_events'])+2<=16,name
    assert all(abs(x-v['x'])+abs(y-v['y'])>=3 for key in ['warp_events','coord_events','bg_events'] for v in m[key])
    body=re.search(r'^=== '+row['symbol']+r' ===\n(.*?)(?=^=== |\Z)',party,re.M|re.S)[1].strip();assert body==base
    assert re.findall(r'Level: (\d+)',body)==['99']*6
    assert '\ttrainerbattle_single '+row['symbol']+', GregRoam_'+name+'_Seen, GregRoam_'+name+'_Beaten' in s
    assert '\tcall GregRoam_Reward\n\tmsgbox GregRoam_'+name+'_After, MSGBOX_DEFAULT\n\tend' in s
print('PASS12 reachable sidelines with complete sight-line bypasses, native object budgets, preserved old events and six level99 teams')
for text in re.findall(r'\.string "(.*?)"',s):
    assert text.isascii() and text.endswith('$')
    for page in text[:-1].split(r'\p'):
        lines=page.split(r'\n');assert len(lines)<=2 and all(len(v)<=26 for v in lines),lines
for p in ['include/global.h','include/global.fieldmap.h','src/new_game.c','include/constants/flags.h','include/constants/items.h','include/constants/species.h']:
    assert (R/p).read_bytes()==old(p),p
for p in ['data/maps/Route29/map.json','data/maps/Route30/map.json','data/maps/CherrygroveCity/map.json','data/maps/Route29/scripts.inc','data/maps/Route30/scripts.inc','data/maps/CherrygroveCity/scripts.inc']:
    assert (R/p).read_bytes()==old(p),p
var='VAR_TRIO_GREG_WINS';assert not re.search(r'0x4145\b',old('include/constants/vars.h').decode())
assert 'TRAINERS_COUNT                      1164' in (R/'include/constants/opponents.h').read_text()
for i,row in enumerate(rows):
    alias='TRAINER_UNUSED_'+str(216+i)
    assert not re.search(r'^=== '+alias+r' ===',oldparty,re.M)
    assert '#define '+row['symbol'] in (R/'include/constants/opponents.h').read_text()
# Execute the actual common reward helper: successful receipt is the only write.
code=[];labels={}
for line in s[s.index('GregRoam_Reward::'):].splitlines():
    line=line.strip()
    if re.fullmatch(r'\w+::?',line):labels[line.rstrip(':')]=len(code)
    elif line and not line.startswith('.string'):code.append(line)
for owned,room in itertools.product([0,1],repeat=2):
    flag=owned;pc=labels['GregRoam_Reward'];gifts=0;result=0
    for _ in range(30):
        op,_,args=code[pc].partition(' ');pc+=1;a=[v.strip() for v in args.split(',')]
        if op=='return':break
        elif op=='goto_if_set':
            assert a[0]=='FLAG_GREG_WAWA_REWARDED'
            if flag:pc=labels[a[1]]
        elif op=='giveitem':assert a[0]=='ITEM_POTION';gifts+=room;result=room
        elif op=='goto_if_eq':
            if result==0:pc=labels[a[2]]
        elif op=='setflag':assert a[0]=='FLAG_GREG_WAWA_REWARDED';flag=1
        elif op=='msgbox':pass
        else:raise AssertionError(op)
    else:raise AssertionError('no return')
    assert gifts==int(not owned and room);assert flag==bool(owned or room)
assert 'heal' not in s and 'setrespawn' not in s and 'setflag FLAG_BADGE' not in s
setup=(R/'src/battle_setup.c').read_text()
for name in ['GetTrainerFlag','HasTrainerBeenFought','SetTrainerFlag','ClearTrainerFlag','SetBattledTrainersFlags']:
    assert 'TrioGreg_' in re.search(r'(?:bool8|void) '+name+r'\([^)]*\)\n\{(.*?)\n\}',setup,re.S)[1],name
print('PASS38 dialogue boxes, shared one-time/full-Bag Wawa paths, reclaimed flag guards, old Greg wins and unchanged saved ABI')
