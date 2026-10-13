"""Halloween art/gameplay/save metadata audit; source puzzle flow has a separate runner."""
from pathlib import Path
import re,subprocess,sys
from PIL import Image
R=Path(__file__).resolve().parents[2]
BASE='b5b341eb998812a896d86d354724483b5a813d57'
def old(p):return subprocess.check_output(['git','show',BASE+':'+p],cwd=R,text=True)
for p in ['include/global.h','include/global.fieldmap.h','src/new_game.c','include/constants/flags.h']:
 assert (R/p).read_text()==old(p),p
assert (R/'include/constants/vars.h').read_text().startswith(old('include/constants/vars.h'))
for name in ['riko_witch','bijuu_vampire','penny_pumpkin']:
 for asset,size in [('front',(64,64)),('back',(64,64)),('icon',(32,64)),('overworld',(192,32))]:
  im=Image.open(R/'graphics/pokemon'/name/(asset+'.png'));assert im.size==size and im.mode=='P';assert max(im.tobytes())<16 and im.info['transparency']==0
 for kind in ['normal','shiny','icon_normal','icon_shiny','overworld_normal','overworld_shiny']:
  text=(R/'graphics/pokemon'/name/(kind+'.pal')).read_text();assert text.splitlines()[:3]==['JASC-PAL','0100','16'] and len(text.splitlines())==19
 im=Image.open(R/'graphics/items/icons'/(name+'.png'));assert im.size==(24,24) and im.mode=='P' and max(im.tobytes())<16
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
