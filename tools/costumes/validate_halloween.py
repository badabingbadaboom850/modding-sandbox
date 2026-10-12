"""Audit actual new gift bytecode source, saved IDs and native asset formats."""
from pathlib import Path
import re,itertools,subprocess
from PIL import Image
R=Path(__file__).resolve().parents[2]
BASE='b5b341eb998812a896d86d354724483b5a813d57'
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
for family,sym,item,name,base in [('Riko','RikoWitch','RIKOS_WITCH_HAT','riko_witch','RikoRaincoat'),('Bijuu','BijuuVampire','BIJUUS_VAMPIRE_CAPE','bijuu_vampire','BijuuDetective'),('Penny','PennyPumpkin','PENNYS_PUMPKIN_SUIT','penny_pumpkin','PennyLifeguard')]:
 assert 'TrioCostume_'+base+'Gift::\n\tlock\n\tfaceplayer\n\tcall TrioCostume_'+sym+'Gift' in source
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
for form in ['RIKO_WITCH','BIJUU_VAMPIRE','PENNY_PUMPKIN','PENNY_PUMPKIN_DACHSBUN']:
 assert 'case SPECIES_'+form+':' in (R/'src/battle_util.c').read_text()
 assert 'checkspecies SPECIES_'+form+'\n' in (R/'data/scripts/trio_party_checks.inc').read_text()
print('PASS',cases,'new gift flows, old save/ID/map preservation, new family eligibility, text and indexed native assets')
# Compare gameplay metadata with the established exact ordinary-stage costumes.
for path,pairs in [('src/data/pokemon/species_info.h',[('RIKO_BUTTERFLY','RIKO_WITCH'),('BIJUU_ASTRONAUT','BIJUU_VAMPIRE')]),('src/data/pokemon/species_info/gen_9_families.h',[('PENNY_BALLERINA','PENNY_PUMPKIN'),('PENNY_BALLERINA_DACHSBUN','PENNY_PUMPKIN_DACHSBUN')])]:
 s=(R/path).read_text()
 def entry(name):return re.search(r'\[SPECIES_'+name+r'\] =\n    \{(.*?)\n    \},',s,re.S)[1]
 for base,form in pairs:
  before,after=entry(base),entry(form)
  # Sprite pointers/names/evolutions are intentionally costume-specific.
  fields=['baseHP','baseAttack','baseDefense','baseSpeed','baseSpAttack','baseSpDefense','types','genderRatio','abilities','innates','growthRate','levelUpLearnset','teachableLearnset','eggMoveLearnset','natDexNum','formSpeciesIdTable','formChangeTable']
  for field in fields:
   pattern=r'\.'+field+r'\s*=\s*([^\n]*?)(?=,\s*\.|,\s*$|$)'
   assert re.findall(pattern,before,re.M)==re.findall(pattern,after,re.M),(form,field)
  assert '.genderRatio = MON_FEMALE' in after
  assert re.search(r'\.formChangeTable\s*=\s*(sRikoCostumeEntryTable|sBijuuCostumeEntryTable|sPennySpiritMegaEntryTable)',after)
# New assets are actually connected to runtime registration and frame-contiguous conversion.
for name,sym in [('riko_witch','RikoWitch'),('bijuu_vampire','BijuuVampire'),('penny_pumpkin','PennyPumpkin')]:
 assert name in (R/'Makefile').read_text()
 assert 'overworld_ascending_frames(gObjectEventPic_'+sym+', 4, 4)' in (R/'src/data/pokemon/custom_species.h').read_text()
 assert 'graphics/items/icons/'+name+'.4bpp.smol' in (R/'src/data/graphics/items.h').read_text()
 for asset,kind in [('front','normal'),('back','normal'),('icon','icon_normal'),('overworld','overworld_normal')]:
  im=Image.open(R/'graphics/pokemon'/name/(asset+'.png'))
  values=[int(v) for line in (R/'graphics/pokemon'/name/(kind+'.pal')).read_text().splitlines()[3:] for v in line.split()]
  assert im.getpalette()[:48]==values,(name,asset)
  assert 0 in im.tobytes() and any(im.tobytes()),(name,asset)
# All saved mask bits and old pages keep their meaning; no wrap beyond16bits.
s=(R/'src/trio_outfits.c').read_text()
assert 'gSpecialVar_0x8004 >= 16' in s and '& 0xFDFF' in s and 'i < 16' in s
for species,index in [('RIKO_WITCH',14),('BIJUU_VAMPIRE',15),('PENNY_PUMPKIN_DACHSBUN',16)]:
 assert 'case SPECIES_'+species+': return '+str(index)+';' in s
print('PASS four ordinary-stage metadata comparisons, runtime asset wiring/palette packing and final16bit photo bounds')
