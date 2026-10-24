"""Decode this engine's 11-bit metatiles, collision and beach-ground behavior."""
from pathlib import Path
import json, re, struct
ROOT = Path(__file__).resolve().parents[2]
def geometry(city):
    m = json.loads((ROOT/f'data/maps/{city}/map.json').read_text())
    layout = next(v for v in json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts'] if v['id']==m['layout'])
    w,h = layout['width'],layout['height']
    blocks = struct.unpack('<'+str(w*h)+'H',(ROOT/layout['blockdata_filepath']).read_bytes())
    headers = (ROOT/'src/data/tilesets/headers.h').read_text()
    metatiles = (ROOT/'src/data/tilesets/metatiles.h').read_text()
    attrs=[]
    for key in ['primary_tileset','secondary_tileset']:
        body=headers.split('const struct Tileset '+layout[key]+' =',1)[1].split('};',1)[0]
        symbol=re.search(r'\.metatileAttributes = (\w+)',body)[1]
        path=re.search(symbol+r'\[\] = INCBIN_U16\("([^"]+)',metatiles)[1]
        attrs.append((ROOT/path).read_bytes())
    def walk(x,y):
        if not (0<=x<w and 0<=y<h): return False
        tile=blocks[y*w+x];index=tile&0x7FF
        behavior=struct.unpack_from('<H',attrs[index>=1024],(index%1024)*2)[0]&255
        return not (tile&0x800) and behavior in [0,2,3,7,8,0x21]
    def elevation(x,y): return blocks[y*w+x]>>12
    return m,w,h,walk,elevation
