# Riko in-game implementation and evolution handoff

Repository: `badabingbadaboom850/modding-sandbox`  
Branch: `feat/riko-bijuu-mega-forms`  
Reviewed at: `a243613` (the current branch includes the first rival battle party update).

## The short version

Riko’s follower did not need a Riko-specific map script or a new command in the general follower script. The important custom work was:

1. Register Riko as a real species and describe her follower data in `gSpeciesInfo`.
2. Put the follower image and normal/shiny palettes at `graphics/pokemon/riko/` and reference those assets from the species data.
3. Add a Makefile conversion rule that rearranges the 32×32 tiles into the frame order the follower animation expects. Ordinary PNG-to-4bpp conversion produced the broken/duplicated frames.
4. Make the indexed PNG’s palette order agree with the `.pal` files. Palette index 0 is transparent.

The generic follower engine then reads the image, palette, dimensions, and animation from Riko’s `gSpeciesInfo` entry.

## How the follower works

### Source art and palette

The base follower source is:

- `graphics/pokemon/riko/overworld.png`
- `graphics/pokemon/riko/overworld_normal.pal`
- `graphics/pokemon/riko/overworld_shiny.pal`

The PNG is a 192×32 horizontal strip: six 32×32 animation frames. It is an indexed 4-bit image with 16 palette slots, not an RGBA image. Empty pixels must use palette index 0. The `.pal` entries must be in the exact same order as the indexed PNG; the earlier palettes had the wrong order, which caused incorrect colors and apparent transparency problems. The game treats slot 0 as transparent.

The build produces `overworld.4bpp`, `overworld_normal.gbapal`, and `overworld_shiny.gbapal` from those source files. The compiled `.gbapal` files are what the species data includes at runtime.

### The special Makefile rule

`Makefile` defines the custom follower asset list in `RIKO_OVERWORLD_GFX`, then applies this rule to its `.4bpp` outputs:

```make
# Overworld followers are animated in 32x32 frames. Reorder the PNG's 4x4-tile
# blocks so each frame is contiguous in the generated 4bpp data.
$(filter %.4bpp,$(RIKO_OVERWORLD_GFX)): %.4bpp: %.png
	$(GFX) $< $@ -mwidth 4 -mheight 4
```

Each 32×32 frame is a 4×4 block of 8×8 tiles. The `-mwidth 4 -mheight 4` conversion makes those tile blocks contiguous in frame-major order, which is what the animation table expects. Without it, the graphics converter’s normal tile ordering interleaved the frame data. The result looked duplicated, broken, or like a blob even though the PNG looked right.

The `pokemon.o` Makefile dependency also includes `$(RIKO_OVERWORLD_GFX)`, so changes to the source assets cause the species object to rebuild. The list includes Riko and the other custom follower variants; Riko Spirit was added to this conversion/dependency list separately.

### C registration and runtime selection

The relevant registration is spread across these files:

- `src/pokemon.c` includes the custom species definitions and species table. It includes the form tables and follower pic tables before `custom_species.h`, then includes `species_info.h`.
- `src/data/pokemon/custom_species.h` declares `gObjectEventPic_Riko`, the normal/shiny overworld palette pointers, `sPicTable_Riko`, and Riko’s learnset. The frame table uses `overworld_ascending_frames(gObjectEventPic_Riko, 4, 4)`.
- `src/data/pokemon/species_info.h` gives `SPECIES_RIKO` its follower record through `OVERWORLD(...)`: `sPicTable_Riko`, `SIZE_32x32`, `SHADOW_SIZE_M`, `TRACKS_FOOT`, `sAnimTable_Following`, and the two palette pointers.
- The general overworld/follower code obtains the graphics record from `gSpeciesInfo[species].overworldData`. Riko works because her species entry is complete; no one-off route script is needed to paint her follower.

The Mega Riko species entry currently points at the same `sPicTable_Riko` and base palettes. It therefore follows as base Riko during the Mega form unless that is changed. Riko Spirit has a separate overworld asset/table/palette registration.

## Debugging history and fixes

1. The first attempt put images under `graphics/object_events/pics/pokemon/followers/`. That is not the path used for these custom species. The working assets are under `graphics/pokemon/riko/`, referenced from the custom species data.
2. The indexed PNG’s palette order did not match the associated `.pal` files. Palette index 0 must be the transparent slot, and every pixel’s numeric index must point to the intended color in the `.pal`. Regenerating palettes to match the PNG corrected this layer.
3. Palette correction alone did not fix the duplicated/broken animation. The remaining cause was tile/frame ordering.
4. Commit `2127459` added the frame-aware Makefile conversion. After this, Riko and Bijuu’s follower sprites displayed and animated correctly.
5. Commit `a0a3e24` aligned Riko and Bijuu’s overworld palettes to their indexed PNGs.
6. Commit `12ed08d` added Riko Spirit’s overworld graphics and palettes to the special frame conversion/dependency list; the Spirit sheet needs the same layout handling.

Related earlier commits include `94989128` (initial Riko/Bijuu species registry) and `51d36563` (overworld graphics registration). `9bb123e1` added Riko Spirit and placed it in the fresh-save party.

## Riko’s current species setup

- `SPECIES_RIKO` is ID `1578`; Riko’s family is enabled with `P_FAMILY_RIKO TRUE`.
- Base typing is Normal/Fairy. Current base stats are HP 90, Attack 75, Defense 85, Speed 110, Sp. Attack 105, Sp. Defense 95 (total 560).
- Abilities are Cute Charm and Fluffy as the hidden ability. The species data points at the custom front/back, normal/shiny battle palettes, icon, learnset, and overworld follower data.
- `src/new_game.c` currently gives a fresh save Riko in party slot 0, Penny/Fidough in slot 1, Riko Spirit in slot 2, then the chosen starter is added by the starter flow. A new-game party change will not alter an already-created save.
- Riko’s custom learnset is in `src/data/pokemon/custom_species.h`.

## Evolution feasibility

**Yes, a normal permanent evolution is supported.** `gSpeciesInfo` entries carry an `.evolutions` field. For example, Fidough evolves to Dachsbun in `src/data/pokemon/species_info/gen_9_families.h` with:

```c
.evolutions = EVOLUTION({EVO_LEVEL, 26, SPECIES_DACHSBUN}),
```

Riko’s `SPECIES_RIKO` entry in `src/data/pokemon/species_info.h` currently has no `.evolutions` field, so a standard level, item, friendship, or other supported evolution can be added there using the same pattern and an appropriate target species.

### Don’t use the existing Mega form as a permanent evolution target

`SPECIES_MEGA_RIKO` is ID `1580` and is already configured as a Mega form. `src/data/pokemon/form_species_tables.h` lists it as a form of Riko; `src/data/pokemon/form_change_tables.h` changes Riko into it with `FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM` and `ITEM_BONDSTONE`, then returns to base Riko on faint or at the end of battle. That is temporary battle transformation behavior, not a normal evolution. Reusing this ID for a permanent evolution would mix two different systems.

### Possible evolution targets

- **Use existing `SPECIES_RIKO_SPIRIT`** if the intended evolved look/story is already the Spirit/Cerberus Riko. It is ID `1598`, already has its own battle/icon/follower assets, species data, and learnset. It currently has Fire/Fairy typing, 115/115/85/100/90/75 base stats, and is also given to the player at the start of a fresh save. Reusing it is mechanically the smallest change, but the starting-party/story use should be considered first.
- **Create a distinct permanent evolution species** if the evolved form should be separate from the current Spirit starter or from Mega Riko. That needs a new species ID, species data, battle sprites/palettes, icon/palettes, learnset, and follower sprite/palettes. The target’s `OVERWORLD(...)` registration and `RIKO_OVERWORLD_GFX` Makefile list must be added too; omitting either is a common reason for a follower to appear wrong or fall back to generic art.

At this branch tip, `SPECIES_RIKO_SPIRIT` is the final custom species ID (`1598`) and `SPECIES_EGG` is defined relative to it. A newly allocated species must be inserted before the egg sentinel and the relevant `NUM_SPECIES`, species-info, dex, and generated-data tables must stay aligned. If the new form should share Riko’s existing Pokédex entry, it can follow the current Spirit pattern (`.natDexNum = NATIONAL_DEX_RIKO`); if it should receive its own entry, add the corresponding dex constant/order and text too.

## Safe implementation checklist for a later evolution pass

1. Decide whether “evolution” means a permanent Riko-to-Spirit/Cerberus species change or a new species distinct from both Spirit and battle-only Mega Riko.
2. Choose the trigger and level/item requirement. Do not make up a level until the intended game pacing is decided.
3. Add `.evolutions = EVOLUTION(...)` to Riko’s base species entry and confirm the target species data exists.
4. If adding a new target, allocate its species ID before `SPECIES_EGG`; add its stats, type, abilities, dex identity, learnset, assets, and any evolution-specific text.
5. Register a distinct follower image and palette only if the evolved look differs. Keep the 192×32/six-frame format and the frame-major Makefile conversion; set the new species’ `OVERWORLD(...)` fields.
6. Build the ROM, start a fresh save if party initialization is part of the change, evolve a test Riko, and check battle art, party/menu icon, Pokédex, follower animation, palettes, faint/reload behavior, and shiny behavior.

## Source links

- [Custom Riko assets and learnset](https://github.com/badabingbadaboom850/modding-sandbox/blob/feat/riko-bijuu-mega-forms/src/data/pokemon/custom_species.h)
- [Riko species and follower registration](https://github.com/badabingbadaboom850/modding-sandbox/blob/feat/riko-bijuu-mega-forms/src/data/pokemon/species_info.h)
- [Frame-aware overworld asset build rule](https://github.com/badabingbadaboom850/modding-sandbox/blob/feat/riko-bijuu-mega-forms/Makefile)
- [Species and form IDs](https://github.com/badabingbadaboom850/modding-sandbox/blob/feat/riko-bijuu-mega-forms/include/constants/species.h)
- [Mega/form species list](https://github.com/badabingbadaboom850/modding-sandbox/blob/feat/riko-bijuu-mega-forms/src/data/pokemon/form_species_tables.h)
- [Mega/form change rules](https://github.com/badabingbadaboom850/modding-sandbox/blob/feat/riko-bijuu-mega-forms/src/data/pokemon/form_change_tables.h)
- [Fresh-save party initialization](https://github.com/badabingbadaboom850/modding-sandbox/blob/feat/riko-bijuu-mega-forms/src/new_game.c)
- [General follower script](https://github.com/badabingbadaboom850/modding-sandbox/blob/feat/riko-bijuu-mega-forms/data/scripts/follower.inc)
