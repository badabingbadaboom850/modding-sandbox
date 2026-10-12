"""Execute real seasonal scripts and validate save/history/warp/art/text contracts.
This is source/native validation, not rendered emulator confirmation.
"""
from pathlib import Path
import collections,itertools,json,re,subprocess,sys,tempfile
from PIL import Image
R=Path(__file__).resolve().parents[2];BASE='8ce7bf9953021d5d808cc2c11336dc241feda872'
rows=json.loads((R/'tools/costumes/seasons.json').read_text());chapters=json.loads((R/'tools/costumes/chapters.json').read_text())
S=(R/'data/scripts/trio_seasonal_chapters.inc').read_text();labels={};code=[]
for line in S.splitlines():
 line=line.strip()
 if not line or line.startswith('@') or line.startswith('.string'):continue
 if re.fullmatch(r'\w+::?',line):
  n=line.rstrip(':');assert n not in labels,n;labels[n]=len(code)
 else:code.append(line)
for n in re.findall(r'\bTrioSeason\w+_\w+',S):assert n in labels,n
class Run:
 def __init__(self,c,round=0,answers=(),room=100,vars=None,bag=None,flags=None):
  self.c=c;self.p='TrioSeason'+chapters[c][0];self.v='VAR_TRIO_'+chapters[c][1]+'_';self.vars=dict(vars or {});self.bag=collections.Counter(bag or {});self.flags=set(chapters[c][8] if flags is None else flags);self.answers=iter(answers);self.room=room;self.round=round;self.gifts=[];self.warps=[];self.lock=False;self.exchanges=[];self.exchange_result=1
 def val(self,a):
  if a.startswith('VAR_'):return self.vars.get(a,0)
  return {'TRUE':1,'FALSE':0,'YES':1,'NO':0,'MULTI_B_PRESSED':127}.get(a,int(a) if a.isdigit() else a)
 def run(self,start,answers=None):
  if answers is not None:self.answers=iter(answers)
  pc=labels[self.p+'_'+start]
  for _ in range(500):
   op,_,arg=code[pc].partition(' ');pc+=1;a=[x.strip() for x in arg.split(',')]
   if op=='end':assert not self.lock;return self
   if op=='lockall':self.lock=True
   elif op=='releaseall':self.lock=False
   elif op in ['setvar','copyvar']:self.vars[a[0]]=self.val(a[1])
   elif op=='addvar':self.vars[a[0]]=self.val(a[0])+self.val(a[1])
   elif op=='random':assert a==['3'];self.vars['VAR_RESULT']=self.round
   elif op=='msgbox':
    if a[1]=='MSGBOX_YESNO':self.vars['VAR_RESULT']=next(self.answers,0)
   elif op=='dynmultichoice':self.vars['VAR_RESULT']=next(self.answers,127)
   elif op=='checkitem':self.vars['VAR_RESULT']=int(bool(self.bag[a[0]]))
   elif op=='giveitem':
    assert len(a)<=2 and (len(a)==1 or a[1]=='1');success=self.room>0;self.vars['VAR_RESULT']=int(success)
    if success:self.room-=1;self.bag[a[0]]+=1;self.gifts.append(a[0])
   elif op=='specialvar':
    assert a[1]=='ExchangeTrioSeasonalCostume';self.exchanges.append((self.vars['VAR_0x8004'],self.vars['VAR_0x8005']));self.vars[a[0]]=self.exchange_result
   elif op=='bufferitemname':pass
   elif op=='warp':self.warps.append(tuple(a))
   elif op=='goto':pc=labels[a[0]]
   elif op=='goto_if_unset':
    if a[0] not in self.flags:pc=labels[a[1]]
   elif op in ['goto_if_eq','goto_if_ne']:
    eq=self.val(a[0])==self.val(a[1])
    if eq==(op=='goto_if_eq'):pc=labels[a[2]]
   elif op in ['faceplayer','closemessage','waitstate','playmoncry','waitmoncry']:pass
   else:raise AssertionError((self.p,code[pc-1]))
  raise AssertionError('loop')
 def reload(self,answers=(),room=None):
  return Run(self.c,self.round,answers,self.room if room is None else room,{k:v for k,v in self.vars.items() if k.startswith('VAR_TRIO_')},self.bag,self.flags)
orders=[[0,1,2],[2,0,1],[1,2,0]];cases=0
for c,ch in enumerate(chapters):
 for answer in [0,1,127]:
  r=Run(c,answers=[answer]).run('Offer');assert bool(r.warps)==(answer==1);assert not r.gifts;cases+=1
 for missing in ch[8]:
  r=Run(c,answers=[1],flags=set(ch[8])-{missing}).run('Offer');assert not r.warps and not r.gifts;cases+=1
 # Decline does not seed or erase a round. Exits never alter saved progress.
 for state,progress,round in itertools.product(range(3),range(4),range(3)):
  v='VAR_TRIO_'+ch[1]+'_';saved={v+'STATE':state,v+'PROGRESS':progress,v+'ROUND':round,v+'GIFTS':2,v+'SNACK':1}
  for origin,answers in [('Offer',[0]),('Exit',[0]),('Exit',[1]),('WalkExit',[])]:
   r=Run(c,vars=saved,answers=answers).run(origin);assert all(r.vars[k]==val for k,val in saved.items());assert not r.gifts;cases+=1
 for round in range(3):
  order=orders[round]
  # Every possible wrong/cancel choice at every progress point, across reload.
  for step,choice in itertools.product(range(3),[0,1,2,3,127]):
   v='VAR_TRIO_'+ch[1]+'_';r=Run(c,round,vars={v+'STATE':1,v+'ROUND':round,v+'PROGRESS':step})
   if c in (1,3):r.run('Host',[choice,127])
   elif choice<3:r.run('Choice'+str(choice))
   else:continue
   expected=step+int(choice==order[step]);assert r.vars[v+'PROGRESS']==expected,(c,round,step,choice,r.vars)
   if expected<3:assert not r.gifts and r.vars[v+'STATE']==1
   r=r.reload();assert r.vars[v+'PROGRESS']==expected;cases+=1
  for initial_gifts,capacity,owned in itertools.product(range(4),range(5),[False,True]):
   v='VAR_TRIO_'+ch[1]+'_';items=['ITEM_'+r[3] for r in rows[c*3:c*3+3]]
   # Earlier received costumes remain owned; pre-owned later items must not duplicate.
   bag={item:1 for item in items[:initial_gifts]}
   if owned:bag.update({item:1 for item in items})
   r=Run(c,round,answers=[1,127],room=capacity,vars={v+'GIFTS':initial_gifts},bag=bag).run('Host')
   assert r.vars[v+'ROUND']==round and r.vars[v+'STATE']==1 and not r.gifts
   for step,choice in enumerate(order):
    r=r.reload(answers=[choice,127]);r.run('Host' if c in (1,3) else 'Choice'+str(choice))
    if step<2:assert r.vars[v+'PROGRESS']==step+1 and not r.gifts
   assert r.vars[v+'PROGRESS']==3
   assert all(r.bag[item]<=1 for item in items)
   r=r.reload(answers=[0],room=10).run('Host')
   assert all(r.bag[item]==1 for item in items) and r.bag[ch[7]]==1 and r.vars[v+'GIFTS']==3 and r.vars[v+'SNACK']==1 and r.vars[v+'STATE']==0
   r=r.reload(answers=[0]).run('Host');assert not r.gifts and r.bag[ch[7]]==1
   # Replay new variant: same keys, one more small snack, no replay of costume gifts.
   r.round=(round+1)%3;r.run('Host',[1,127]);assert r.vars[v+'ROUND']==r.round
   for choice in orders[r.round]:r.run('Host' if c in (1,3) else 'Choice'+str(choice),[choice,127])
   assert all(r.bag[item]==1 for item in items) and r.bag[ch[7]]==2
   r=r.reload(answers=[0]).run('Host');assert not r.gifts and r.bag[ch[7]]==2;cases+=1
print('PASS',cases,'seasonal source branches: gates, declines, all variants/wrong/cancel, old-save zero state, reloads, partial/full Bag, owned gifts and two-round rewards')
wardrobe_cases=0
for mode,index,yes,result in itertools.product([0,1],list(range(13))+[127],[0,1,127],[0,1,2]):
 r=Run(0,answers=[mode,index,yes,2]);r.p='TrioSeasonWardrobe';r.exchange_result=result;r.run('Offer')
 assert r.exchanges==([(index,mode)] if index<12 and yes==1 else []),(mode,index,yes,result,r.exchanges)
 assert not r.gifts and not r.warps and not r.lock;wardrobe_cases+=1
for choice in [2,127]:
 r=Run(0,answers=[choice]);r.p='TrioSeasonWardrobe';r.run('Offer');assert not r.exchanges;wardrobe_cases+=1
print('PASS',wardrobe_cases,'wardrobe menu/scroll/Back/B/decline/store/take/full/missing paths; actual transfers have native engine tests')

old=lambda p:subprocess.check_output(['git','show',BASE+':'+p],cwd=R,text=True)
sys.path.insert(0,str(R/'tools/greg'));from geometry import geometry
for c,ch in enumerate(chapters):
 season,key,title,source,sourceid,group,region,snack,gates,words,activity=ch
 m,w,h,walk=geometry(source);before=json.loads(old('data/maps/'+source+'/map.json'));assert m['object_events'][:-1]==before['object_events']
 for k in before:
  if k!='object_events':assert m[k]==before[k]
 occupied={(o['x'],o['y']) for o in m['object_events']};assert len(occupied)==len(m['object_events']);assert len(occupied)+2<=16
 assert walk(5,6) and walk(7,7) and (7,7) not in occupied
 def reachable(start,walk,occupied):
  seen={start};q=collections.deque(seen)
  while q:
   x,y=q.popleft()
   for p in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
    if p not in seen and p not in occupied and walk(*p):seen.add(p);q.append(p)
  return seen
 seen=reachable((7,7),walk,occupied)
 for o in m['object_events']:
  if o['y']==2 and o['x'] in (7,8):
   assert (7,4) in seen # Original nurse/Chansey are served across the counter.
   continue
  x,y=o['x'],o['y'];assert any(p in seen for p in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]),(source,o)
 garden='TrioSeason'+season
 assembly=(R/'data/event_scripts.s').read_text();include='\t.include \"data/maps/'+garden+'/scripts.inc\"'
 assert assembly.count(include)==1,(garden,'missing map-script assembly registration')
 mapscript=(R/'data/maps'/garden/'scripts.inc').read_text()
 assert garden+'_MapScripts::' in mapscript and 'map_script MAP_SCRIPT_ON_LOAD, '+garden+'_Load' in mapscript and 'setvar VAR_TEMP_A, 1' in mapscript
 m,w,h,walk=geometry(garden);occupied={(o['x'],o['y']) for o in m['object_events']};assert len(occupied)==len(m['object_events']) and len(occupied)+2<=16
 seen=reachable((12,15),walk,occupied)
 for o in m['object_events']:
  x,y=o['x'],o['y'];assert walk(x,y) and any(p in seen for p in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]),(garden,o);assert o['script'] in labels
 for coord in m['coord_events']:assert (coord['x'],coord['y']) in seen and coord['script']=='TrioSeason'+season+'_WalkExit'
 for warp in m['warp_events']:assert warp['dest_map']==sourceid and warp['dest_warp_id']=='0'
 assert (R/'data/maps'/source/'scripts.inc').read_text()==old('data/maps/'+source+'/scripts.inc')
for p in ['include/global.h','include/global.fieldmap.h','src/new_game.c','include/constants/flags.h']:
 assert (R/p).read_text()==old(p),p
vars=(R/'include/constants/vars.h').read_text();assert vars.startswith(old('include/constants/vars.h'))
# Numeric usage audit against all tracked baseline code/data, including decimal literals.
for value in range(0x414B,0x4161):
 assert len(re.findall(r'\b0x'+f'{value:04X}'+r'\b',vars,re.I))==1
 pat=rf'\b(0x{value:04X}|{value})\b'
 result=subprocess.run(['git','grep','-i','-n','-E',pat,BASE,'--','include','src','data'],cwd=R,stdout=subprocess.PIPE,text=True)
 assert result.returncode==1,result.stdout
with tempfile.TemporaryDirectory() as td:
 td=Path(td);(td/'maps').mkdir();(td/'constants').mkdir();subprocess.run([str(R/'tools/mapjson/mapjson'),'groups','emerald','data/maps/map_groups.json',str(td/'maps'),str(td/'constants')],cwd=R,check=True)
 generated=(td/'constants/map_groups.h').read_text();ids=set(re.findall(r'^\s*(MAP_\w+)\s*=',generated,re.M))
 for dest in re.findall(r'^\s*warp\s+(MAP_\w+)',S,re.M):assert dest in ids,dest
 before={n:(a,b) for n,a,b in re.findall(r'^\s*(MAP_\w+)\s*=\s*\((\d+) \| \((\d+) << 8\)\)',old('include/constants/map_groups.h'),re.M)}
 now={n:(a,b) for n,a,b in re.findall(r'^\s*(MAP_\w+)\s*=\s*\((\d+) \| \((\d+) << 8\)\)',generated,re.M)}
 for n,v in before.items():assert now[n]==v,(n,v,now[n])
print('PASS all four hosts, stages, actor approaches/budgets, safe exits, 22 unused saved vars and production warp namespace; historical maps/IDs/save ABI unchanged')
# Actual-font limits and image registration/metadata contracts.
font=(R/'src/fonts.c').read_text();chars={}
for line in (R/'charmap.txt').read_text().splitlines():
 m=re.match(r"^('.*?')\s*=\s*([\da-fA-F]{2})\b",line)
 if m:chars[m[1][1:-1].replace("\\'","'")]=int(m[2],16)
def width(text,fontname):
 widths=list(map(int,re.findall(r'\b\d+\b',font.split('gFont'+fontname+'LatinGlyphWidths[] = {')[1].split('};')[0])))
 text=re.sub(r'\{STR_VAR_1\}', '27',text)
 text=re.sub(r'\{PLAYER\}', 'WWWWWWW',text)
 return sum(widths[chars[c]] for c in text)
for source in [S,(R/'data/scripts/trio_outfit_stories.inc').read_text()]:
 for t in re.findall(r'\.string "(.*?)"',source):
  assert t.endswith('$') and t.isascii()
  for page in t[:-1].split(r'\p'):
   assert len(page.split(r'\n'))<=2
   for line in page.split(r'\n'):assert len(line)<=26 and width(line,'Normal')<=208,(line,width(line,'Normal'))
for i,row in enumerate(rows):
 spec,sym,folder,item,name=row;p=R/'graphics/pokemon'/folder
 assert width(name,'Narrower')<=84
 palettes=[(p/(kind+'.pal')).read_text() for kind in ['normal','shiny','icon_normal','icon_shiny','overworld_normal','overworld_shiny']];assert len(set(palettes))==1
 values=[int(x) for line in palettes[0].splitlines()[3:] for x in line.split()];assert len(values)==48
 for asset,size in [('front',(64,64)),('back',(64,64)),('icon',(32,64)),('overworld',(192,32))]:
  im=Image.open(p/(asset+'.png'));assert im.mode=='P' and im.size==size and im.info['transparency']==0 and max(im.tobytes())<16;assert im.getpalette()[:48]==values
  if asset=='overworld':
   frames=[im.crop((32*f,0,32*(f+1),32)) for f in range(6)]
   for frame in frames:assert frame.getbbox() and frame.getbbox()[0]>0 and frame.getbbox()[2]<32 and frame.getbbox()[3]<32
   for f in [0,2,4]:assert frames[f].tobytes()!=frames[f+1].tobytes(),(folder,'identical walk poses',f)
 itemim=Image.open(R/'graphics/items/icons'/(folder+'.png'));assert itemim.size==(24,24) and itemim.mode=='P' and itemim.getpalette()[:48]==values
 assert 'overworld_ascending_frames(gObjectEventPic_'+sym+', 4, 4)' in (R/'src/data/pokemon/custom_species.h').read_text()
 assert folder in (R/'Makefile').read_text()
 path='src/data/pokemon/species_info/gen_9_families.h' if i%3==2 else 'src/data/pokemon/species_info.h';s=(R/path).read_text();template=['RIKO_WITCH','BIJUU_VAMPIRE','PENNY_PUMPKIN'][i%3]
 for suffix in (['','_DACHSBUN'] if i%3==2 else ['']):
  entry=lambda n:re.search(r'\[SPECIES_'+n+r'\] =\n    \{(.*?)\n    \},',s,re.S)[1]
  skin,base=entry(spec+suffix),entry(template+suffix)
  for field in ['baseHP','baseAttack','baseDefense','baseSpeed','baseSpAttack','baseSpDefense','types','genderRatio','abilities','innates','growthRate','levelUpLearnset','teachableLearnset','eggMoveLearnset','formSpeciesIdTable','formChangeTable']:
   pattern=r'\.'+field+r'\s*=\s*([^\n]*?)(?=,\s*\.|,\s*$|$)';assert re.findall(pattern,skin,re.M)==re.findall(pattern,base,re.M),(spec,field)
  display=re.search(r'\.speciesName = _\("(.*?)"\)',skin)[1];assert width(display,'SmallNarrower')<=55
  assert 'case SPECIES_'+spec+suffix+':' in (R/'src/battle_util.c').read_text()
  assert 'checkspecies SPECIES_'+spec+suffix+'\n' in (R/'data/scripts/trio_party_checks.inc').read_text()
 assert f'ITEM_{item}, SPECIES_'+['RIKO','BIJUU','FIDOUGH'][i%3] in entry(spec)
assert not re.search(r'\b(?:trainerbattle|removeitem|takeitem|setflag|clearflag|setrespawn|setdynamicwarp)\b',S)
print('PASS 12 palette-safe registered atlases, 72 distinct follower poses, 16 cosmetic-only species, actual font limits and reusable reverse routes')
