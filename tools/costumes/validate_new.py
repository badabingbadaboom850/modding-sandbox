"""Audit actual new gift bytecode source, saved IDs and native asset formats."""
from pathlib import Path
import re,itertools,subprocess
from PIL import Image
R=Path(__file__).resolve().parents[2]
BASE='be744111538531e7f27978e5bcc7b31f3c7ed1fe'
def old(p):return subprocess.check_output(['git','show',BASE+':'+p],cwd=R,text=True)
for p in ['include/global.h','include/global.fieldmap.h','src/new_game.c','include/constants/vars.h','include/constants/flags.h']:
 assert (R/p).read_text()==old(p),p
for p,prefix in [('include/constants/species.h','SPECIES_'),('include/constants/items.h','ITEM_')]:
 for name,value in re.findall(r'(?:#define\s+|\b)('+prefix+r'\w+)\s*(?:=|\s)\s*(\d+)\b',old(p)):
  assert re.search(r'\b'+name+r'\s*(?:=|\s)\s*'+value+r'\b',(R/p).read_text()),name
source=(R/'data/scripts/trio_costumes.inc').read_text();labels={};code=[]
for line in source.splitlines():
 line=line.strip()
 if not line or line.startswith('@'):continue
 if re.fullmatch(r'\w+::?',line):assert line.rstrip(':') not in labels;labels[line.rstrip(':')]=len(code)
 else:code.append(line)
cases=0
for family,sym,item,name,base in [('Riko','RikoButterfly','RIKOS_BUTTERFLY_WINGS','riko_butterfly','RikoRaincoat'),('Bijuu','BijuuAstronaut','BIJUUS_SPACE_HELMET','bijuu_astronaut','BijuuDetective'),('Penny','PennyBallerina','PENNYS_BALLET_TUTU','penny_ballerina','PennyLifeguard')]:
 entry=source.split('TrioCostume_'+base+'Gift::',1)[1].split('TrioCostume_'+base+'Ready:',1)[0]
 assert '\tcall TrioCostume_'+sym+'Gift' in entry
 for owned,present,yes,room in itertools.product([0,1],repeat=4):
  pc=labels['TrioCostume_'+sym+'Gift'];result=0;gifts=0
  for step in range(60):
   op,_,args=code[pc].partition(' ');pc+=1;a=[v.strip() for v in args.split(',')]
   if op=='return':break
   elif op=='checkitem':assert a[0]=='ITEM_'+item;result=owned
   elif op=='call':assert a[0]=='TrioParty_Check'+family;result=present
   elif op=='msgbox':
    if a[1]=='MSGBOX_YESNO':result=yes
   elif op=='giveitem':assert a[0]=='ITEM_'+item;gifts+=room;result=room
   elif op=='goto_if_eq':
    if result=={'TRUE':1,'FALSE':0,'NO':0}[a[1]]:pc=labels[a[2]]
   else:raise AssertionError(op)
  else:raise AssertionError('gift loop')
  assert gifts==int(not owned and present and yes and room);cases+=1
 for asset,size in [('front',(64,64)),('back',(64,64)),('icon',(32,64)),('overworld',(192,32))]:
  im=Image.open(R/'graphics/pokemon'/name/(asset+'.png'));assert im.size==size and im.mode=='P';assert max(im.tobytes())<16;assert im.info['transparency']==0
 for kind in ['normal','shiny','icon_normal','icon_shiny','overworld_normal','overworld_shiny']:
  text=(R/'graphics/pokemon'/name/(kind+'.pal')).read_text();assert text.splitlines()[:3]==['JASC-PAL','0100','16'];assert len(text.splitlines())==19
 im=Image.open(R/'graphics/items/icons'/(name+'.png'));assert im.size==(24,24)
for p in ['data/scripts/trio_costumes.inc','data/scripts/trio_outfit_stories.inc']:
 s=(R/p).read_text()
 for text in re.findall(r'\.string "(.*)"',s):
  assert text.endswith('$')
  for page in text[:-1].split(r'\p'):
   assert len(page.split(r'\n'))<=2
   assert all(len(l)<=26 for l in page.split(r'\n')),(p,page)
# These sources/maps remain identical; no actors, visibility, movement or warps added.
for city in ['EcruteakCity','OlivineCity']:
 for f in ['map.json','scripts.inc','scripts.pory']:
  p='data/maps/'+city+'/'+f
  if (R/p).exists():assert (R/p).read_text()==old(p),p
for form in ['RIKO_BUTTERFLY','BIJUU_ASTRONAUT','PENNY_BALLERINA','PENNY_BALLERINA_DACHSBUN']:
 assert 'case SPECIES_'+form+':' in (R/'src/battle_util.c').read_text()
 assert 'checkspecies SPECIES_'+form+'\n' in (R/'data/scripts/trio_party_checks.inc').read_text()
print('PASS',cases,'new gift flows, old save/ID/map preservation, new family eligibility, text and indexed native assets')
