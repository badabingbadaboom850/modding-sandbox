"""Measure every family transformation description with actual FONT_NARROW glyph widths."""
from pathlib import Path
import re
R=Path(__file__).resolve().parents[2]
body=(R/'src/fonts.c').read_text().split('const u8 gFontNarrowLatinGlyphWidths[] = {',1)[1].split('};',1)[0]
widths=list(map(int,re.findall(r'\b\d+\b',body)));charmap={}
for line in (R/'charmap.txt').read_text().splitlines():
 m=re.match(r"^('.*?')\s*=\s*([0-9a-fA-F]{2})\b",line)
 if m:charmap[m[1][1:-1].replace("\\'","'")]=int(m[2],16)
source=(R/'src/data/items.h').read_text().split('[ITEM_RIKOS_PURSE]',1)[1];count=0
for name,body in re.findall(r'\[(ITEM_\w+)\]\s*=\s*\{(.*?)\n    \},',source,re.S):
 if 'ItemUseOutOfBattle_EvolutionStone' not in body:continue
 desc=re.search(r'\.description = COMPOUND_STRING\((.*?)\),',body,re.S);assert desc,name
 text=''.join(re.findall(r'"(.*?)"',desc[1]));sizes=[sum(widths[charmap[c]] for c in line) for line in text.split(r'\n')]
 assert len(sizes)<=3 and max(sizes)<=102,(name,sizes,text)
 count+=1
assert count==51,count
print('PASS all51 family transformation descriptions fit actual102px Bag/Shop FONT_NARROW limit')
