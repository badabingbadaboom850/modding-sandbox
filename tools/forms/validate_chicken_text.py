"""Use actual FONT_NARROW glyph widths and charmap for the corrected Bag text."""
from pathlib import Path
import re,subprocess
R=Path(__file__).resolve().parents[2]
body=(R/'src/fonts.c').read_text().split('const u8 gFontNarrowLatinGlyphWidths[] = {',1)[1].split('};',1)[0]
widths=list(map(int,re.findall(r'\b\d+\b',body)))
charmap={key:int(value,16) for key,value in re.findall(r"^'([^']+)'\s*=\s*([0-9A-Fa-f]{2})\b",(R/'charmap.txt').read_text(),re.M)}
def description(s):
 entry=s.split('[ITEM_PIECE_OF_CHICKEN]',1)[1].split('\n    },',1)[0]
 return re.search(r'\.description = COMPOUND_STRING\("(.*?)"\)',entry,re.S)[1].split(r'\n')
def measure(lines):return [sum(widths[charmap[c]] for c in line) for line in lines]
prior=subprocess.check_output(['git','show','b5b341eb998812a896d86d354724483b5a813d57:src/data/items.h'],cwd=R,text=True)
old=measure(description(prior));new=measure(description((R/'src/data/items.h').read_text()))
assert max(old)==107 and max(new)<=102,(old,new)
assert 'Reusable' in description((R/'src/data/items.h').read_text())[0]
print('PASS FONT_NARROW actual prior chicken107px overflow; corrected line widths',new,'fit102px Bag/Shop bound')
