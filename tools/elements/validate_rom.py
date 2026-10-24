"""Compare linked production ROM assets with the verified compiled payloads."""
from pathlib import Path
import subprocess,json
R=Path(__file__).resolve().parents[2]
rom=(R/'Soulgold.gba').read_bytes()
nm=subprocess.check_output([str(R.parent/'toolchain13/bin/arm-none-eabi-nm'),'-S',str(R/'Soulgold.elf')],text=True)
symbols={}
for line in nm.splitlines():
    parts=line.split()
    if len(parts)==4:symbols[parts[3]]=(int(parts[0],16),int(parts[1],16))
entries=[('gMonFrontPic_','front.4bpp.smol'),('gMonBackPic_','back.4bpp.smol'),('gMonPalette_','normal.gbapal'),('gMonShinyPalette_','shiny.gbapal'),('gMonIcon_','icon.4bpp'),('gMonIconPalette_','icon_normal.gbapal'),('gMonShinyIconPalette_','icon_shiny.gbapal'),('gObjectEventPic_','overworld.4bpp'),('gOverworldPalette_','overworld_normal.gbapal'),('gShinyOverworldPalette_','overworld_shiny.gbapal')]
count=0
for f in json.loads((R/'tools/elements/forms.json').read_text()):
    files=[(prefix+f['camel'],R/'graphics/pokemon'/f['folder']/file) for prefix,file in entries]
    files += [('gItemIcon_'+f['camel']+'Keepsake',R/'graphics/items/icons'/(f['folder']+'_keepsake.4bpp.smol')),('gItemIconPalette_'+f['camel']+'Keepsake',R/'graphics/items/icon_palettes'/(f['folder']+'_keepsake.gbapal'))]
    for symbol,path in files:
        address,size=symbols[symbol];data=path.read_bytes();assert len(data)<=size,(symbol,len(data),size)
        offset=address-0x08000000;assert rom[offset:offset+len(data)]==data,symbol;count+=1
assert len(rom)==32*1024*1024
print('PASS'+str(count)+' linked production-ROM graphics/palette payloads and padded32MiB ROM')
