#!/usr/bin/env python3
"""Actual-source gift flow, historical IDs, geometry and indexed-art checks."""
from pathlib import Path
import re,sys,json,subprocess,struct
from PIL import Image
R=Path(__file__).resolve().parents[2]
s=(R/'data/scripts/trio_costumes.inc').read_text();labels={};code=[]
for l in s.splitlines():
 l=l.strip()
 if not l or l.startswith('@'):continue
 if re.fullmatch(r'\w+::?',l):labels[l.rstrip(':')]=len(code)
 else:code.append(l)
for line in s.splitlines():
 if line.strip().startswith('.string'):assert re.fullmatch(r'\s*\.string ".*\$"',line),line
for text in re.findall(r'\.string "(.*)"',s):
 assert text.endswith('$')
 for page in text[:-1].split(r'\p'):
  lines=page.split(r'\n');assert len(lines)<=2
  for line in lines:assert len(line)<=26,(line,len(line))
for token in re.findall(r'\bTrioCostume_\w+',s):assert token in labels,token
class Run:
 def __init__(self,owned,present,yes,won,room,prior):
  self.owned=owned;self.present=present;self.yes=yes;self.won=won;self.room=room;self.prior=prior
  self.vars={};self.cmp=False;self.lock=False;self.battles=0;self.gifts=0
 def run(self,start):
  pc=labels[start]
  for _ in range(100):
   op,_,args=code[pc].partition(' ');pc+=1;a=[x.strip() for x in args.split(',')]
   if op=='lock':self.lock=True
   elif op=='release':self.lock=False
   elif op=='end':return self
   elif op=='goto':pc=labels[a[0]]
   elif op=='goto_if':
    if self.cmp:pc=labels[a[1]]
   elif op in ['goto_if_eq','goto_if_ne']:
    value={'TRUE':1,'FALSE':0,'NO':0,'B_OUTCOME_WON':1}[a[1]]
    same=self.vars.get(a[0])==value
    if same==(op=='goto_if_eq'):pc=labels[a[2]]
   elif op=='checkitem':self.vars['VAR_RESULT']=int(self.owned)
   elif op=='checktrainerflag':self.cmp=self.prior
   elif op=='call':assert a[0].startswith('TrioParty_Check');self.vars['VAR_RESULT']=int(self.present)
   elif op=='msgbox':
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=int(self.yes)
   elif op=='trainerbattle_no_intro':self.battles+=1
   elif op=='specialvar':assert a[1]=='GetBattleOutcome';self.vars[a[0]]=int(self.won)
   elif op=='giveitem':self.gifts+=int(self.room);self.vars['VAR_RESULT']=int(self.room)
   elif op=='faceplayer':pass
   else:raise AssertionError(op)
  raise AssertionError('Nonterminating gift script')
import itertools
cases=0
for owned,present,yes,won,room,prior in itertools.product([False,True],repeat=6):
 for name in ['Balloon','Box','Hotdog']:
  r=Run(owned,present,yes,won,room,prior).run('TrioCostume_'+name)
  eligible=(prior or (present and yes and won)) if name=='Box' else present and yes
  assert r.gifts==int(not owned and eligible and room),(name,vars(r))
  assert r.battles==int(name=='Box' and not owned and not prior and present and yes)
  assert not r.lock
  cases+=1
print(cases,'gift/decline/missing-party/win/loss/Bag-full/reclaim source paths pass')
sys.path.insert(0,str(R/'tools/snack'));from gang_geometry import geometry
for city in ['CherrygroveCity','VioletCity','AzaleaTown']:
 m,w,h,walk=geometry(city);npc=m['object_events'][-1];x,y=npc['x'],npc['y']
 assert all(walk(a,b) for a,b in [(x,y),(x-1,y),(x+1,y),(x,y-1),(x,y+1)])
 occupied={(e['x'],e['y']) for k in ['object_events','warp_events','coord_events','bg_events'] for e in (m[k][:-1] if k=='object_events' else m[k])};assert (x,y) not in occupied
 old=json.loads(subprocess.check_output(['git','show','c82cdaaffb38ac96761d15943a95f0412de08e7b:data/maps/'+city+'/map.json'],cwd=R,text=True));assert old['object_events']==m['object_events'][:-1]
 for k in old:
  if k!='object_events':assert old[k]==m[k]
 assert npc['trainer_type']=='TRAINER_TYPE_NONE' and npc['flag']=='0'
 assert npc['script'] in labels
print('Three optional NPCs have walkable approaches; old map events/dispatch preserved')
for folder in ['riko_balloon','bijuu_box','penny_hotdog']:
 p=R/'graphics/pokemon'/folder
 colors=[tuple(map(int,l.split())) for l in (p/'normal.pal').read_text().splitlines()[3:]];assert len(colors)==16
 for file,size in [('front',(64,64)),('back',(64,64)),('icon',(32,64)),('overworld',(192,32))]:
  im=Image.open(p/(file+'.png'));assert im.mode=='P' and im.size==size and im.info['transparency']==0
  assert max(im.tobytes())<16 and im.getpalette()[:48]==[v for c in colors for v in c]
  if file=='overworld':
   for n in range(6):assert im.crop((n*32,0,(n+1)*32,32)).getbbox()
 icon=Image.open(R/'graphics/items/icons'/(folder+'.png'));assert icon.size==(24,24) and icon.mode=='P'
 if '--compiled' in sys.argv:
  raw=(p/'overworld.4bpp').read_bytes();assert len(raw)==3072;im=Image.open(p/'overworld.png')
  for n in range(6):
   for y in range(32):
    for x in range(32):
     b=raw[n*512+((y//8)*4+x//8)*32+(y%8)*4+(x%8)//2];assert ((b>>4 if x%2 else b)&15)==im.getpixel((n*32+x,y))
  expected=[(r>>3)|((g>>3)<<5)|((b>>3)<<10) for r,g,b in colors];assert list(struct.unpack('<16H',(p/'overworld_normal.gbapal').read_bytes()))==expected
print('All costume battle/icon/six follower frames/item art share transparent 16-color palettes')
if '--compiled' in sys.argv:print('All18 compiled follower frames and palettes match source pixels')
base='c82cdaaffb38ac96761d15943a95f0412de08e7b'
for f in ['include/global.h','include/pokemon.h','src/save.c','include/config/save.h']:
 assert (R/f).read_bytes()==subprocess.check_output(['git','show',base+':'+f],cwd=R)
for f,prefix,exceptions in [('include/constants/species.h','SPECIES_',{'SPECIES_EGG'}),('include/constants/opponents.h','TRAINER_',{'TRAINER_UNUSED_299'})]:
 old=subprocess.check_output(['git','show',base+':'+f],cwd=R,text=True);new=(R/f).read_text()
 for name,val in re.findall(r'^#define ('+prefix+r'\w+)\s+(\d+)\b',old,re.M):
  if name not in exceptions:assert re.search(r'^#define '+name+r'\s+'+val+r'\b',new,re.M),name
assert '#define TRAINERS_COUNT                      1164' in (R/'include/constants/opponents.h').read_text()
assert '#define MAX_TRAINERS_COUNT                  1164' in (R/'include/constants/opponents.h').read_text()
old=subprocess.check_output(['git','show',base+':include/constants/items.h'],cwd=R,text=True);new=(R/'include/constants/items.h').read_text()
for name,val in re.findall(r'\b(ITEM_\w+) = (\d+)\b',old):assert re.search(r'\b'+name+' = '+val+r'\b',new),name
print('Historical real species/items/trainers, trainer flag bounds and save files unchanged')

# Execute the actual temporary supply helper with partial-Bag and repeat visits.
items=['ITEM_RIKOS_BALLOON','ITEM_BIJUUS_BOX','ITEM_PENNYS_HOTDOG_BUN']
def supplies(owned,capacity,yes):
 pc=labels['TrioCostume_TestSupplies'];result=0;gifts=[]
 for _ in range(80):
  op,_,args=code[pc].partition(' ');pc+=1;a=[x.strip() for x in args.split(',')]
  if op=='return':return owned,gifts
  if op=='msgbox':
   if a[1]=='MSGBOX_YESNO':result=int(yes)
  elif op=='goto_if_eq':
   if result=={'TRUE':1,'FALSE':0,'NO':0}[a[1]]:pc=labels[a[2]]
  elif op=='checkitem':result=int(a[0] in owned)
  elif op=='giveitem':
   result=int(capacity>0)
   if result:assert a[0] not in owned;owned.add(a[0]);gifts.append(a[0]);capacity-=1
  else:raise AssertionError(op)
 raise AssertionError('Supply helper never returned')
count=0
for bits,capacity,yes in itertools.product(range(8),range(4),[False,True]):
 owned={v for j,v in enumerate(items) if bits&(1<<j)};initial=set(owned)
 after,gifts=supplies(owned,capacity,yes)
 assert len(gifts)==(min(capacity,3-len(initial)) if yes else 0)
 assert initial<=after
 again,extra=supplies(after,3,True);assert again==set(items)
 last,duplicate=supplies(again,3,True);assert not duplicate
 count+=1
print(count,'test supply owned/decline/partial-Bag/retry/repeat paths pass')
for file in ['data/maps/NewBarkTown/scripts.inc','data/maps/NewBarkTown/scripts.pory']:
 old=subprocess.check_output(['git','show','541b28b63a63acb7bbb037a41302fc885034a215:'+file],cwd=R,text=True)
 new=(R/file).read_text();assert new.count('\tcall TrioCostume_TestSupplies\n')==1
 assert new.replace('\tcall TrioCostume_TestSupplies\n','',1)==old
assert '\tcall TrioCostume_TestSupplies\n' in (R/'data/maps/NewBarkTown/scripts.inc').read_text().split('NewBarkTown_EventScript_Lass::',1)[1].split('NewBarkTown_EventScript_LassState2::',1)[0]
print('Mom friend Pory/assembly hook preserves every existing story branch/movement')
