"""Decode route collision/behavior for hideout placement checks."""
import json,struct,re,collections
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
def geometry(city):
 m=json.loads((ROOT/f'data/maps/{city}/map.json').read_text());ls=json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts'];l=next(x for x in ls if x['id']==m['layout']);w,h=l['width'],l['height'];b=struct.unpack('<'+str(w*h)+'H',(ROOT/l['blockdata_filepath']).read_bytes());headers=(ROOT/'src/data/tilesets/headers.h').read_text();mts=(ROOT/'src/data/tilesets/metatiles.h').read_text();attrs=[]
 for key in ['primary_tileset','secondary_tileset']:
  body=headers.split('const struct Tileset '+l[key]+' =',1)[1].split('};',1)[0];name=re.search(r'\.metatileAttributes = (\w+)',body).group(1);path=re.search(name+r'\[\] = INCBIN_U16\("([^"]+)',mts).group(1);attrs.append((ROOT/path).read_bytes())
 def walk(x,y):
  if not(0<=x<w and 0<=y<h):return False
  v=b[y*w+x];i=v&2047;behavior=struct.unpack_from('<H',attrs[i>=1024],(i%1024)*2)[0]&255
  return not(v&0x800) and behavior in [0,2,3,7]
 return m,w,h,walk
