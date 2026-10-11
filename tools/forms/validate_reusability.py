"""Audit all native family transformation items and protect historical inventory metadata."""
from pathlib import Path
import re, subprocess
R = Path(__file__).resolve().parents[2]
BASE = '8bf5c134f30b1c638a5902a27a2aa76452b644de'
def old(path): return subprocess.check_output(['git','show',BASE+':'+path],cwd=R,text=True)
def entries(source): return dict(re.findall(r'\[(ITEM_\w+)\]\s*=\s*\{(.*?)\n    \},', source, re.S))
items = entries((R/'src/data/items.h').read_text())
prior = entries(old('src/data/items.h'))
menu = (R/'src/party_menu.c').read_text()
switch = menu.split('static bool32 IsReusableTrioFormItem',1)[1].split('void ItemUseCB_EvolutionStone',1)[0]
reusable = set(re.findall(r'case (ITEM_\w+):', switch))
added = {'ITEM_RIKOS_WAND','ITEM_BLUE_BRUSH','ITEM_BIJUUS_FISH_TOY',
         'ITEM_BIJUUS_CAT_NIP','ITEM_DADS_KEYS','ITEM_PIECE_OF_CHICKEN'}
assert added <= reusable
old_switch = old('src/party_menu.c').split('static bool32 IsReusableTrioFormItem',1)[1].split('void ItemUseCB_EvolutionStone',1)[0]
assert reusable == added | set(re.findall(r'case (ITEM_\w+):',old_switch))
count = key = ordinary = 0
for name,body in items.items():
    # Family item entries occupy the established appended block.
    if '[%s]'%name not in (R/'src/data/items.h').read_text().split('[ITEM_RIKOS_PURSE]',1)[1]: continue
    if '.fieldUseFunc = ItemUseOutOfBattle_EvolutionStone' not in body: continue
    count += 1
    pocket = re.search(r'\.pocket = (\w+)',body).group(1)
    assert pocket == 'POCKET_KEY_ITEMS' or name in reusable, name
    key += pocket == 'POCKET_KEY_ITEMS'; ordinary += pocket == 'POCKET_ITEMS'
    if name in added:
        desc = re.search(r'\.description = COMPOUND_STRING\((.*?)\),',body,re.S).group(1)
        assert 'Reusable' in desc
        for line in re.findall(r'"(.*?)"',desc):
            assert all(len(x)<=26 for x in line.split(r'\n'))
    # Only descriptions change: pockets/prices/held behavior/art/gifts keep their meaning.
    strip = lambda x: re.sub(r'\.description = COMPOUND_STRING\(.*?\),','',x,flags=re.S)
    assert strip(body) == strip(prior[name]), name
assert (count,key,ordinary)==(33,20,13),(count,key,ordinary)
assert 'GetItemPocket(gSpecialVar_ItemId) != POCKET_KEY_ITEMS\n            && !IsReusableTrioFormItem(gSpecialVar_ItemId)' in menu
assert 'return TRUE;' in switch and 'default:\n        return FALSE;' in switch
assert 'ITEM_FIRE_STONE' not in reusable and 'ITEM_THUNDER_STONE' not in reusable
for path in ['include/constants/items.h','include/constants/species.h','include/constants/vars.h',
             'include/constants/flags.h','include/global.h','include/trio_runoff.h',
             'src/data/pokemon/species_info.h','src/data/pokemon/species_info/gen_9_families.h']:
    assert (R/path).read_text() == old(path),path
print('PASS all33 form items reusable (20 Key/13 Items), six updated descriptions, ordinary stones and historical saved inventory metadata preserved')
