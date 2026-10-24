#!/usr/bin/env python3
"""Shop gate simulation and authoring/asset checks, not rendered playtesting."""
from pathlib import Path
from PIL import Image
import itertools,re,subprocess,unittest
R=Path(__file__).resolve().parents[2];S=(R/'data/maps/BlackthornCity_Mart/scripts.inc').read_text();LABELS={};CODE=[]
for line in S.splitlines():
 line=line.strip()
 if re.fullmatch(r'\w+::?',line):LABELS[line.rstrip(':')]=len(CODE)
 else:CODE.append(line)
def inventory(label,text=S):
 return re.findall(r'\.2byte (ITEM_\w+)',text[text.index(label+':'):].split('\t.2byte ITEM_NONE')[0])
def shop(flags):
 pc=LABELS['TrioPuffs_Shop'];result=[]
 for _ in range(50):
  op,_,args=CODE[pc].partition(' ');pc+=1;a=[v.strip() for v in args.split(',')]
  if op=='goto_if_unset':
   if a[0] not in flags:pc=LABELS[a[1]]
  elif op=='pokemart':result.append(a[0])
  elif op=='return':return result
  elif op=='msgbox':pass
  else:raise AssertionError(CODE[pc-1])
 raise AssertionError('loop')
class Checks(unittest.TestCase):
 def test_all_256_badge_combinations(self):
  badges=[f'FLAG_BADGE0{i}_GET' for i in range(1,9)]
  for bits in itertools.product([0,1],repeat=8):
   flags={b for b,v in zip(badges,bits) if v};self.assertEqual(shop(flags),['BlackthornPuffs' if all(bits) else 'Blackthorn2'])
 def test_original_shop_and_map_are_preserved(self):
  old=subprocess.check_output(['git','show','cd6da734:data/maps/BlackthornCity_Mart/scripts.inc'],cwd=R,text=True)
  self.assertEqual(inventory('Blackthorn2'),inventory('Blackthorn2',old));self.assertEqual(inventory('BlackthornPuffs'),['ITEM_RIKO_PUFFS']+inventory('Blackthorn2'))
  self.assertEqual((R/'data/maps/BlackthornCity_Mart/map.json').read_bytes(),subprocess.check_output(['git','show','cd6da734:data/maps/BlackthornCity_Mart/map.json'],cwd=R))
 def test_authoring_parity_and_locked_caller(self):
  s=(R/'data/maps/BlackthornCity_Mart/scripts.pory').read_text();self.assertIn('call(TrioPuffs_Shop)',s);self.assertIn('call TrioPuffs_Shop',S)
  for n in range(1,9):self.assertIn(f'goto_if_unset FLAG_BADGE0{n}_GET, TrioPuffs_OriginalShop',s)
  block=S[S.index('Blackthorn_Mart2::'):S.index('Blackthorn2:')];self.assertIn('\tlock',block);self.assertIn('\trelease',block)
 def test_item_and_each_party_style_share_candy_safety(self):
  for f in ['src/party_menu.c','src/swsh_party_menu.c']:
   s=(R/f).read_text();self.assertIn('(levelCap - level + levelsPerItem - 1) / levelsPerItem',s)
   self.assertIn('item == ITEM_RIKO_PUFFS ? 5 : 1',s)
   self.assertIn('tHoldEffectParam == 0 && gSpecialVar_ItemId != ITEM_RIKO_PUFFS',s)
   self.assertIn('for (; sInitialLevel <= sFinalLevel; sInitialLevel++)',s)
   self.assertIn('RemoveBagItem(gSpecialVar_ItemId, tItemCount)',s)
  source=(R/'src/data/items.h').read_text();block=source[source.index('[ITEM_RIKO_PUFFS]'):source.index('[ITEM_RARE_CANDY]')]
  self.assertIn('.price = 500',block);self.assertIn('.effect = gItemEffect_RareCandy',block);self.assertIn('.pocket = POCKET_ITEMS',block)
 def test_icon_and_text(self):
  with Image.open(R/'graphics/items/icons/riko_puffs.png') as im:
   self.assertEqual(im.size,(24,24));self.assertEqual(im.mode,'P');self.assertLessEqual(len(im.getcolors()),16);self.assertEqual(im.info['transparency'],0)
  self.assertEqual((R/'graphics/items/icon_palettes/riko_puffs.pal').read_text().splitlines()[2],'16')
  for t in re.findall(r'\.string "(.*)"',S[S.index('TrioPuffs_ShopText:'):].split('\n\n')[0]):
   for page in t.rstrip('$').split(r'\p'):
    rows=page.split(r'\n');self.assertLessEqual(len(rows),2)
    for row in rows:self.assertLessEqual(len(row),26)
if __name__=='__main__':unittest.main()
