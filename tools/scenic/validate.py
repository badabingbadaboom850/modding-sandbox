#!/usr/bin/env python3
"""Actual event wiring, geometry, save allocation and font checks; no rendering."""
from pathlib import Path
import collections,json,re,struct,subprocess
R=Path(__file__).resolve().parents[2]
BASE='8007203b24ffa73a1ba85c0c51a86e9ac1009d86'
def old(p):return subprocess.check_output(['git','show',BASE+':'+p],cwd=R,text=True)
S=(R/'data/scripts/trio_scenic.inc').read_text()
# No gameplay mutation beyond the explicit capture helper; itemless/full Bag independent.
assert not re.search(r'^\s*(giveitem|removeitem|trainerbattle\w*|warp|setweather|setflag|setvar VAR_TRIO_)\b',S,re.M)
assert 'goto_if_ne VAR_RESULT, YES, TrioScenic_Close' in S
assert S.count('specialvar VAR_RESULT, TakeTrioScenicPhoto')==1
assert S.count('showmonpic ')==3 and S.count('\thidemonpic')==3
assert 'goto_if_ge VAR_RESULT, 3, TrioScenic_Return' in S
labels=collections.Counter()
for p in list((R/'data/maps').rglob('scripts.inc'))+list((R/'data/scripts').glob('*.inc')):
 labels.update(re.findall(r'^(\w+)::?',p.read_text(),re.M))
for name in re.findall(r'^(\w+)::?',S,re.M):assert labels[name]==1,name
for name in re.findall(r'(TrioScenic_\w+)',S):assert labels[name]==1,name
for name in ['TakeTrioScenicPhoto','ReadTrioScenicPhoto']:
 assert (R/'data/specials.inc').read_text().count('def_special '+name)==1
assert (R/'data/event_scripts.s').read_text().count('.include "data/scripts/trio_scenic.inc"')==1
assert 'goto_if_eq VAR_RESULT, 6, TrioScenic_Album' in (R/'data/scripts/trio_memories.inc').read_text()
# Every allocation was unused in baseline, raw hex and decimal across source/data/tests.
for i in range(0x4161,0x416B):
 pat=rf'\b(0x0*{i:x}|{i})\b'
 out=subprocess.run(['git','grep','-inE',pat,BASE,'--','include','src','data','test'],cwd=R,text=True,capture_output=True)
 assert out.returncode==1,(i,out.stdout)
vars=(R/'include/constants/vars.h').read_text()
for i in range(0x4161,0x416B):assert len(re.findall(rf'^#define VAR_TRIO_SCENIC_\w+\s+0x{i:04X}\b',vars,re.M))==1
for p in ['include/global.h','include/constants/items.h','include/constants/species.h']:
 assert (R/p).read_text()==old(p),p
maps=lambda s: {n:(a,b) for n,a,b in re.findall(r'(MAP_\w+)\s*=\s*\((\d+) \| \((\d+) << 8\)\)',s)}
for n,value in maps(old('include/constants/map_groups.h')).items():
 assert maps((R/'include/constants/map_groups.h').read_text())[n]==value,n
# Decode production tile behaviors (this engine's eleven-bit metatile selector).
ls=json.loads((R/'data/layouts/layouts.json').read_text())['layouts']
headers=(R/'src/data/tilesets/headers.h').read_text();mts=(R/'src/data/tilesets/metatiles.h').read_text()
for name,x,y,label,start in [('OlivineCity_LighthouseTop',9,11,'Lighthouse',(7,12)),('LakeOfRage',35,43,'Lake',(32,51)),('IcePath_1F',13,22,'Ice',(14,23))]:
 p=f'data/maps/{name}/map.json';m=json.loads((R/p).read_text());before=json.loads(old(p))
 assert m['object_events'][:-1]==before['object_events']
 assert {k:v for k,v in m.items() if k!='object_events'}=={k:v for k,v in before.items() if k!='object_events'}
 actor=m['object_events'][-1];assert (actor['x'],actor['y'],actor['script'])==(x,y,'TrioScenic_'+label)
 assert actor['trainer_type']=='TRAINER_TYPE_NONE' and actor['flag']=='0'
 l=next(v for v in ls if v['id']==m['layout']);w,h=l['width'],l['height'];b=struct.unpack('<'+str(w*h)+'H',(R/l['blockdata_filepath']).read_bytes());attrs=[]
 for key in ['primary_tileset','secondary_tileset']:
  body=headers.split('const struct Tileset '+l[key]+' =',1)[1].split('};',1)[0];sym=re.search(r'\.metatileAttributes = (\w+)',body)[1];path=re.search(sym+r'\[\] = INCBIN_U16\("([^"]+)',mts)[1];attrs.append((R/path).read_bytes())
 def walk(p):
  xx,yy=p
  if not(0<=xx<w and 0<=yy<h):return False
  v=b[yy*w+xx];idx=v&0x7FF;mb=struct.unpack_from('<H',attrs[idx>=1024],(idx%1024)*2)[0]&255
  return not(v&0x800) and mb in [0,2,3,7,8]
 pos=(x,y);assert walk(pos)
 occupied={(o['x'],o['y']) for o in before['object_events']}
 assert pos not in occupied|{(e['x'],e['y']) for k in ['bg_events','coord_events','warp_events'] for e in m[k]}
 def flood(block):
  assert walk(start);seen={start};q=collections.deque(seen)
  while q:
   xx,yy=q.popleft()
   for p in [(xx+1,yy),(xx-1,yy),(xx,yy+1),(xx,yy-1)]:
    if p not in seen and p not in block and walk(p):seen.add(p);q.append(p)
  return seen
 initial=flood(occupied);after=flood(occupied|{pos});assert after==initial-{pos},name
 assert any(p in after for p in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]),name
 for xx in range(x-10,x+11):
  for yy in range(y-8,y+9):assert sum(abs(o['x']-xx)<=10 and abs(o['y']-yy)<=8 for o in m['object_events'])+2<=16,name
 # Existing authoring and layouts remain identical.
 for f in ['scripts.inc','scripts.pory']:
  p=f'data/maps/{name}/{f}'
  if (R/p).exists():assert (R/p).read_text()==old(p)
 assert (R/l['blockdata_filepath']).read_bytes()==subprocess.check_output(['git','show',BASE+':'+l['blockdata_filepath']],cwd=R)
print('PASS: three reachable photographers, all original map data/actors and story scripts preserved; no disconnected paths or actor overflow')
# Actual normal-font widths, including the longest saved species display name.
font=(R/'src/fonts.c').read_text();chars={}
for line in (R/'charmap.txt').read_text().splitlines():
 m=re.match(r"^('.*?')\s*=\s*([\da-fA-F]{2})\b",line)
 if m:chars[m[1][1:-1].replace("\\'","'")]=int(m[2],16)
widths=list(map(int,re.findall(r'\b\d+\b',font.split('gFontNormalLatinGlyphWidths[] = {')[1].split('};')[0])))
texts=re.findall(r'\.string "(.*?)"',S)+re.findall(r'_\("(.*?)"\)',(R/'src/trio_scenic.c').read_text())
for t in texts:
 t=t.rstrip('$')
 for page in t.split(r'\p'):
  assert len(page.split(r'\n'))<=2,page
  for line in page.split(r'\n'):
   line=line.replace('{STR_VAR_1}','WWWWWWWWWWW')
   assert len(line)<=26,(line,len(line))
   assert sum(widths[chars[c]] for c in line)<=208,line
# Follower uses the actual first live mon and actual current weather, no automatic callback.
e=(R/'src/event_object_movement.c').read_text();body=e.split('void GetFollowerAction(',1)[1].split('// otherwise, a basic',1)[0]
assert 'GetFirstLiveMon()' in body and 'TrioWeatherReaction(species, GetCurrentWeather())' in body
assert 'weatherText != NULL && mon->status == 0 && mon->hp * 2 >= mon->maxHP' in body
assert 'ScriptCall(ctx, EventScript_FollowerGeneric)' in body
print('PASS: saved slots unused in baseline, historical IDs/ABI preserved, text fits, exact active follower/weather dispatch, explicit cancel/portrait cleanup')
# Execute the actual event instructions with only engine helper/menu stubs.
code=[];targets={}
for line in S.splitlines():
 line=line.strip()
 if not line or line.startswith('@') or line.startswith('.string'):continue
 if re.fullmatch(r'\w+::?',line):targets[line.rstrip(':')]=len(code)
 else:code.append(line)
class Run:
 def __init__(self,saved,party,answer,menu=()):
  self.saved=list(saved);self.party=party;self.answer=answer;self.menu=iter(menu);self.vars={};self.messages=[];self.writes=0;self.locked=False;self.pic=False;self.shown=[]
 def run(self,label):
  pc=targets[label];stack=[]
  def v(a):return int(a) if a.isdigit() else self.vars.get(a,{'TRUE':1,'FALSE':0,'YES':1,'NO':0}.get(a,0))
  for _ in range(300):
   line=code[pc];pc+=1;op,_,rest=line.partition(' ');a=[x.strip() for x in rest.split(',')]
   if op=='lockall':self.locked=True
   elif op=='releaseall':self.locked=False
   elif op=='end':return self
   elif op=='return':
    if not stack:return self
    pc=stack.pop()
   elif op=='call':stack.append(pc);pc=targets[a[0]]
   elif op=='goto':pc=targets[a[0]]
   elif op=='setvar':self.vars[a[0]]=v(a[1])
   elif op=='copyvar':self.vars[a[0]]=v(a[1])
   elif op in ['goto_if_eq','goto_if_ne','goto_if_ge','call_if_eq']:
    hit=(v(a[0])==v(a[1])) if op in ['goto_if_eq','call_if_eq'] else (v(a[0])!=v(a[1])) if op=='goto_if_ne' else (v(a[0])>=v(a[1]))
    if hit:
     if op=='call_if_eq':stack.append(pc)
     pc=targets[a[2]]
   elif op=='specialvar':
    spot=v('VAR_0x8004')
    if a[1]=='TakeTrioScenicPhoto':
     result=int(self.party)
     if result:self.saved[spot]=True;self.writes+=1
    else:
     assert a[1]=='ReadTrioScenicPhoto';result=int(self.saved[spot])
     if result:
      for i in range(3):self.vars[f'VAR_0x800{5+i}']=spot*3+i+1
    self.vars[a[0]]=result
   elif op=='msgbox':
    self.messages.append(a[0])
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=self.answer
   elif op=='dynmultichoice':self.vars['VAR_RESULT']=next(self.menu)
   elif op=='showmonpic':assert not self.pic;self.pic=True;self.shown.append(v(a[0]))
   elif op=='hidemonpic':assert self.pic;self.pic=False
   else:assert op in ['closemessage','faceplayer','bufferspeciesname'],line
  raise AssertionError('Script did not terminate')
cases=0
for spot,label in enumerate(['Lighthouse','Lake','Ice']):
 for owned in [False,True]:
  for party in [False,True]:
   for answer in [0,1,127]:
    saved=[False]*3;saved[spot]=owned;r=Run(saved,party,answer).run('TrioScenic_'+label)
    assert r.writes==int(party and answer==1)
    assert not r.locked and not r.pic
    assert r.saved==[saved[i] or (i==spot and party and answer==1) for i in range(3)]
    assert ('TrioScenic_RetakeQuestion' in r.messages)==owned
    assert len(r.shown)==(3 if party and answer==1 else 0)
    if r.shown:assert r.shown==[spot*3+i+1 for i in range(3)]
    cases+=1
for mask in range(8):
 for cancel in [3,127]:
  saved=[bool(mask&(1<<i)) for i in range(3)];r=Run(saved,False,0,[0,1,2,cancel]);r.locked=True;r.run('TrioScenic_Album')
  assert r.locked and not r.pic and r.writes==0 and r.saved==saved
  assert len(r.shown)==3*sum(saved)
  cases+=1
print(f'PASS: {cases} actual script paths for first/retake, Yes/No/B, missing party, all saved combinations, album navigation and closed portraits; no simulated rendering')
