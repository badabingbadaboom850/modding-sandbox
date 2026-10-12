"""Execute actual authored puzzle/gift branches and check geometry/history; not an emulator."""
from pathlib import Path
import collections,itertools,json,re,struct,subprocess,sys
R=Path(__file__).resolve().parents[2];BASE='b5b341eb998812a896d86d354724483b5a813d57'
S=(R/'data/scripts/trio_halloween_trail.inc').read_text();LABELS={};CODE=[]
for line in S.splitlines():
 line=line.strip()
 if not line or line.startswith('@') or line.startswith('.string'):continue
 if re.fullmatch(r'\w+::?',line):
  assert line.rstrip(':') not in LABELS;LABELS[line.rstrip(':')]=len(CODE)
 else:CODE.append(line)
VARS=['VAR_TRIO_HALLOWEEN_'+f for f in ['RIKO','BIJUU','PENNY','RETURN']]
ITEMS=['ITEM_RIKOS_WITCH_HAT','ITEM_BIJUUS_VAMPIRE_CAPE','ITEM_PENNYS_PUMPKIN_SUIT']
class Run:
 def __init__(self,state=0,family=0,owned=False,room=True,answers=(),badge=True):
  self.vars={v:0 for v in VARS};self.vars[VARS[family]]=state;self.owned=set([ITEMS[family]]) if owned else set();self.room=room;self.answers=iter(answers);self.lock=False;self.gifts=[];self.warps=[];self.flags={'FLAG_BADGE05_GET'} if badge else set()
 def value(self,x):
  if x.startswith('VAR_'):return self.vars.get(x,0)
  return {'TRUE':1,'FALSE':0,'YES':1,'NO':0,'MULTI_B_PRESSED':127}.get(x,int(x) if x.isdigit() else x)
 def run(self,label):
  pc=LABELS['TrioHalloween_'+label]
  for _ in range(250):
   line=CODE[pc];pc+=1;op,_,rest=line.partition(' ');a=[x.strip() for x in rest.split(',')]
   if op=='end':assert not self.lock;return self
   if op=='return':return self
   if op in ['lockall','lock']:self.lock=True
   elif op in ['releaseall','release']:self.lock=False
   elif op=='setvar':assert a[0] in VARS;self.vars[a[0]]=self.value(a[1])
   elif op=='msgbox':
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=next(self.answers,1)
   elif op=='dynmultichoice':self.vars['VAR_RESULT']=next(self.answers,127)
   elif op=='checkitem':self.vars['VAR_RESULT']=int(a[0] in self.owned)
   elif op=='giveitem':
    assert a[0] not in self.owned
    self.vars['VAR_RESULT']=int(self.room)
    if self.room:self.owned.add(a[0]);self.gifts.append(a[0])
   elif op=='warp':self.warps.append(tuple(a))
   elif op=='goto':pc=LABELS[a[0]]
   elif op in ['goto_if_set','goto_if_unset']:
    if (a[0] in self.flags)==(op=='goto_if_set'):pc=LABELS[a[1]]
   elif op.startswith('goto_if_'):
    x,y=self.value(a[0]),self.value(a[1]);test={'eq':x==y,'ne':x!=y,'gt':x>y,'ge':x>=y}[op[8:]]
    if test:pc=LABELS[a[2]]
   elif op in ['faceplayer','playmoncry','waitmoncry','closemessage','waitstate']:pass
   else:raise AssertionError(line)
  raise AssertionError('script loop')
cases=0
for state,owned,room,answer in itertools.product(range(5),[False,True],[False,True],[0,1,127]):
 r=Run(state,owned=owned,room=room,answers=[answer]).run('Offer');assert bool(r.warps)==(answer==1);assert not r.gifts and r.vars[VARS[0]]==state;cases+=1
 r=Run(state,owned=owned,room=room,answers=[answer]).run('Exit');assert bool(r.warps)==(answer==1);assert not r.gifts and r.vars[VARS[0]]==state;cases+=1
for state,owned,room,words in itertools.product(range(5),[False,True],[False,True],itertools.product([0,1,2,3,127],repeat=3)):
 r=Run(state,owned=owned,room=room,answers=[1,*words]).run('Memory')
 solved=state>=3 or words==(1,0,2)
 assert r.vars[VARS[0]]==(4 if solved and (owned or room) else max(state,3) if solved else state)
 assert len(r.gifts)==int(solved and not owned and room);cases+=1
for family,labels in [(1,['Fish','Moon','Star']),(2,['Left','Right','Middle'])]:
 for initial,sequence in itertools.product(range(5),itertools.product(labels,repeat=4)):
  r=Run(initial,family=family);expected=initial
  for label in sequence:
   r.run(label)
   if expected==labels.index(label):expected+=1
   assert r.vars[VARS[family]]==expected and not r.gifts
   # Reload: reconstruct only saved progress; no transient latch required.
   r=Run(expected,family=family)
  cases+=1
for family,host in enumerate(['Memory','CandyHost','PumpkinHost']):
 for state,owned,room in itertools.product([3,4],[False,True],[False,True]):
  r=Run(state,family,owned,room).run(host)
  assert r.vars[VARS[family]]==(4 if owned or room else state)
  assert len(r.gifts)==int(not owned and room)
  r.room=True;r.run(host);assert r.vars[VARS[family]]==4
  n=len(r.gifts);r.run(host);assert len(r.gifts)==n
  cases+=1
 for state in range(3):
  r=Run(state,family,answers=[0]).run(host);assert not r.gifts and r.vars[VARS[family]]==state
print('PASS',cases,'actual offer/memory/search/order/duplicate/full-Bag/reload branches')
# All map actors/rewards are reachable; two native south-arrow exits remain open.
sys.path.insert(0,str(R/'tools/greg'));from geometry import geometry
m,w,h,walk=geometry('TrioHalloweenTrail');l=next(x for x in json.loads((R/'data/layouts/layouts.json').read_text())['layouts'] if x['id']==m['layout']);blocks=struct.unpack('<'+str(w*h)+'H',(R/l['blockdata_filepath']).read_bytes())
attrs=(R/'data/tilesets/primary/johto_general/metatile_attributes.bin').read_bytes()
def canwalk(x,y):
 if walk(x,y):return True
 if not(0<=x<w and 0<=y<h):return False
 v=blocks[y*w+x];i=v&2047
 return not(v&0x800) and i<1024 and (struct.unpack_from('<H',attrs,i*2)[0]&255)==0x65
occupied={(o['x'],o['y']) for o in m['object_events']};assert len(occupied)==len(m['object_events'])
seen={(12,15)};q=collections.deque(seen)
while q:
 x,y=q.popleft()
 for p in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
  if p not in seen and p not in occupied and canwalk(*p):seen.add(p);q.append(p)
for o in m['object_events']:
 x,y=o['x'],o['y'];assert walk(x,y);assert any(p in seen for p in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]),o['script'];assert o['script'] in LABELS
assert len(m['object_events'])+2<=16
for e in m['warp_events']:assert (e['x'],e['y']) in seen and e['dest_map']=='MAP_OLIVINE_CITY_CAFE' and e['dest_warp_id']=='0'
old=lambda p:subprocess.check_output(['git','show',BASE+':'+p],cwd=R,text=True)
p='data/maps/OlivineCity_Cafe/map.json';house=json.loads((R/p).read_text());before=json.loads(old(p));assert house['object_events'][:-1]==before['object_events']
for k in before:
 if k!='object_events':assert house[k]==before[k]
_,_,_,hw=geometry('OlivineCity_Cafe');assert hw(1,6) and hw(2,7)
for p in ['data/maps/OlivineCity_Cafe/scripts.inc','data/maps/EcruteakCity_House4/map.json','data/maps/EcruteakCity_House4/scripts.inc']:
 assert (R/p).read_text()==old(p),p
p='data/maps/map_groups.json';before=json.loads(old(p));now=json.loads((R/p).read_text())
for k,value in before.items():assert now[k]==(value+['TrioHalloweenTrail'] if k=='gMapGroup_IndoorEcruteak' else value)
for p in ['include/global.h','include/global.fieldmap.h','src/new_game.c','include/constants/flags.h']:assert (R/p).read_text()==old(p),p
for p,prefix in [('include/constants/items.h','ITEM_'),('include/constants/species.h','SPECIES_')]:
 pattern=r'(?:#define\s+|\b)('+prefix+r'\w+)\s*(?:=|\s)\s*(\d+)\b'
 current=dict(re.findall(pattern,(R/p).read_text()))
 for name,value in re.findall(pattern,old(p)):assert current.get(name)==value,(name,value)
p='include/constants/vars.h';assert (R/p).read_text().startswith(old(p))
for value,name in zip(['0x4147','0x4148','0x4149'],VARS):assert '#define '+name in (R/p).read_text() and value in (R/p).read_text()
assert not re.search(r'\b(?:trainerbattle|removeitem|takeitem|setflag|clearflag|checkspecies|setrespawn|setdynamicwarp)\b',S)
for label,text in re.findall(r'^(\w+):\n\s*\.string "([^\n]+)"',S,re.M):
 assert text.endswith('$') and text.isascii()
 for page in text[:-1].split(r'\p'):
  assert len(page.split(r'\n'))<=2 and all(len(l)<=26 for l in page.split(r'\n')),(label,page)
allsource='\n'.join(p.read_text() for p in (R/'data').rglob('*.inc'))
for label in LABELS:assert len(re.findall(r'^'+label+r'::?$',allsource,re.M))==1,label
assert 'data/scripts/trio_halloween_trail.inc' in (R/'data/event_scripts.s').read_text()
assert 'data/maps/TrioHalloweenTrail/scripts.inc' in (R/'data/event_scripts.s').read_text()
for name in ['RikoWitch','BijuuVampire','PennyPumpkin']:assert 'TrioCostume_'+name+'Gift' not in (R/'data/scripts/trio_costumes.inc').read_text()
print('PASS thirteen actors/two exits/host geometry, original service/map IDs/save ABI, three audited vars, item-source replacement and script/text registration')
# Authorized fresh-save test trip, saved return routing, decline and original mailbox parity.
returnvar=VARS[3];routes=0
for state,mode,answer in itertools.product(range(5),[0,1],[0,1,127]):
 r=Run(state,answers=[answer]);r.vars[returnvar]=mode;r.lock=True;r.run('TestOffer')
 assert r.vars[VARS[0]]==state and not r.gifts
 if answer==1:
  assert r.vars[returnvar]==1 and r.warps==[('MAP_TRIO_HALLOWEEN_TRAIL','12','15')] and not r.lock
 else:
  assert r.vars[returnvar]==mode and not r.warps and r.lock # caller retains its lock/sign/release
 r=Run(state,answers=[answer]);r.vars[returnvar]=mode;r.run('Offer')
 assert r.vars[returnvar]==(0 if answer==1 else mode) and r.vars[VARS[0]]==state
 for label in ['Exit','WalkExit']:
  r=Run(state,answers=[1]);r.vars[returnvar]=mode;r.run(label)
  assert r.warps==[('MAP_NEW_BARK_TOWN','18','12') if mode else ('MAP_OLIVINE_CITY_CAFE','2','7')]
  assert r.vars[VARS[0]]==state and not r.gifts and not r.lock
  # Return choice survives a normal save reconstruction.
  reload=Run(state);reload.vars[returnvar]=mode;reload.run('WalkExit');assert reload.warps==r.warps
 routes+=1
for filename in ['scripts.inc','scripts.pory']:
 p='data/maps/NewBarkTown/'+filename;s=(R/p).read_text()
 assert s.count('\tcall TrioHalloween_TestOffer\n')==1
 assert s.replace('\tcall TrioHalloween_TestOffer\n','')==old(p),p
m=json.loads((R/'data/maps/TrioHalloweenTrail/map.json').read_text())
for e in m['coord_events']:
 assert e['script']=='TrioHalloween_WalkExit' and e['var']=='VAR_TEMP_A' and e['var_value']=='1'
 assert (e['x'],e['y']) in seen
script=(R/'data/maps/TrioHalloweenTrail/scripts.inc').read_text();assert 'MAP_SCRIPT_ON_LOAD, TrioHalloweenTrail_Load' in script and 'setvar VAR_TEMP_A, 1' in script
_,_,_,walk=geometry('NewBarkTown');assert walk(18,12)
n=json.loads((R/'data/maps/NewBarkTown/map.json').read_text());assert (18,12) not in {(o['x'],o['y']) for key in ['object_events','warp_events','coord_events','bg_events'] for o in n[key]}
assert (R/'data/maps/NewBarkTown/map.json').read_text()==old('data/maps/NewBarkTown/map.json')
assert 'VAR_TRIO_HALLOWEEN_RETURN                   0x414A' in (R/'include/constants/vars.h').read_text()
print('PASS',routes,'test origin/decline/reload/ghost+walk return combinations, fresh-save no gates/grants, rawPory mailbox parity and safe home tile')
# Resolve authored warps through the production generator, not a mocked map namespace.
import tempfile
exe=R/'tools/mapjson/mapjson'
if not exe.exists():subprocess.run(['make','-C',str(R/'tools/mapjson')],check=True)
with tempfile.TemporaryDirectory() as td:
 td=Path(td);(td/'maps').mkdir();(td/'constants').mkdir()
 subprocess.run([str(exe),'groups','emerald','data/maps/map_groups.json',str(td/'maps'),str(td/'constants')],cwd=R,check=True)
 generated=(td/'constants/map_groups.h').read_text()
 ids=set(re.findall(r'^\s*(MAP_\w+)\s*=',generated,re.M))
 warps=re.findall(r'^\s*warp\s+(MAP_\w+)',S,re.M)
 for dest in warps:assert dest in ids,'Undefined production warp map: '+dest
 assert 'MAP_NEW_BARK_TOWN' in warps and 'MAP_NEWBARK_TOWN' not in S
 assert re.search(r'MAP_TRIO_HALLOWEEN_TRAIL\s*=\s*\(12 \| \(6 << 8\)\)',generated)
 oldmaps=re.findall(r'^\s*(MAP_\w+)\s*=\s*\((\d+) \| \((\d+) << 8\)\)',old('include/constants/map_groups.h'),re.M)
 current={n:(a,b) for n,a,b in re.findall(r'^\s*(MAP_\w+)\s*=\s*\((\d+) \| \((\d+) << 8\)\)',generated,re.M)}
 for n,a,b in oldmaps:assert current.get(n)==(a,b),(n,a,b,current.get(n))
print('PASS',len(warps),'warp references resolve in production-generated map constants; historical map numbers remain fixed')

# Normal invitation belongs after Chuck's fifth Badge; preview remains independent.
for state,mode,answer in itertools.product(range(5),[0,1],[0,1,127]):
 r=Run(state,answers=[answer],badge=False);r.vars[returnvar]=mode;r.run('Offer')
 assert not r.warps and not r.gifts and r.vars[VARS[0]]==state and r.vars[returnvar]==mode
 r=Run(state,answers=[answer],badge=False);r.vars[returnvar]=mode;r.lock=True;r.run('TestOffer')
 assert bool(r.warps)==(answer==1) and r.vars[VARS[0]]==state and not r.gifts
 assert r.vars[returnvar]==(1 if answer==1 else mode)
# Validate cafe access with all original actors, including story-gated Jasmine.
cm,w,h,cw=geometry('OlivineCity_Cafe');occ={(o['x'],o['y']) for o in cm['object_events']};seen={(3,8)};q=collections.deque(seen)
while q:
 x,y=q.popleft()
 for point in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
  if point not in seen and point not in occ and cw(*point):seen.add(point);q.append(point)
assert (2,7) in seen and len(cm['object_events'])+2<=16
before=json.loads(old('data/maps/OlivineCity_Cafe/map.json'));oldocc={(o['x'],o['y']) for o in before['object_events']};oldseen={(3,8)};q=collections.deque(oldseen)
while q:
 x,y=q.popleft()
 for point in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
  if point not in oldseen and point not in oldocc and cw(*point):oldseen.add(point);q.append(point)
assert seen==oldseen-{(1,6)} # no original approach/room path is disconnected
assert any(p in seen for p in [(0,6),(2,6),(1,5),(1,7)])

assert 'setflag FLAG_BADGE05_GET' in (R/'data/maps/CianwoodGym/scripts.inc').read_text()
assert 'setflag FLAG_BADGE06_GET' in (R/'data/maps/OlivineCity_Gym/scripts.inc').read_text()
print('PASS30 pre-Badge5 normal/preview cases and cafe reachability/service preservation; normal unlock is Chuck5 before Jasmine6')
