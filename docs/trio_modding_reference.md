# Tails of the Trio: item, species, graphics, and event reference

Reviewed source: `724570bfcb4268d48837a76d8f751d77ca4e8318` on `feat/riko-bijuu-mega-forms`. Research date: October 7, 2026 Pacific / October 8 UTC.
This document records source-verified behavior, checked asset headers, and recommended validation. It does not certify untested emulator behavior. No gameplay changes were made during this research.

## 1. Use the correct engine and sources

This Soulgold is an Emerald GBA source project, built on a customized pokeemerald-expansion base. The README mentions expansion 1.15.0 and 1.15.1; that is not enough to identify an exact upstream version. The CI sets GAME_VERSION=EMERALD and uploads `Soulgold.gba`. Nintendo DS HeartGold/SoulSilver editing instructions and older vanilla Emerald table layouts are unsuitable.

Priority: current fork source and Makefile > this pinned reference > bundled tutorials > matching upstream documentation. Upstream master currently differs from this fork. In particular, upstream tutorial examples use shared icon palette indices and LZ assets; this fork uses per-species iconPalette/shinyIconPalette pointers and custom battle graphics compressed as .smol.

Primary references:
- [Expansion new-species tutorial](https://github.com/rh-hideout/pokeemerald-expansion/blob/master/docs/tutorials/how_to_new_pokemon.md), 1.7.x onward.
- [Expansion project](https://github.com/rh-hideout/pokeemerald-expansion).
- The fork also includes `docs/tutorials/how_to_new_pokemon.md`, `docs/tutorials/how_to_testing_system.md`, and `tools/poryscript/README.md`.
- The previous `docs/riko_in_game_implementation_and_evolution.md` is useful historical context but says Riko has no evolution and Spirit is the last custom species. Both statements are outdated at this commit.

## 2. Current species inventory

Stats below are HP / Attack / Defense / Sp. Attack / Sp. Defense / Speed.

| Identity | Source ID | Type | Stats | Current wiring |
|---|---:|---|---|---|
| Riko | 1578 | Normal/Fairy | 90/75/85/105/95/110 | Own battle/icon/follower assets; custom Riko learnset; Wand evolves into Wing |
| Bijuu | 1579 | Normal | 80/85/70/95/80/120 | Own assets; Meowth level-up, teachable, and egg learnsets |
| Mega Riko | 1580 | Normal/Fairy | 90/85/95/135/125/130 | Own Mega battle art; base Riko icon/follower; Pixilate |
| Mega Bijuu | 1581 | Normal | 80/125/90/105/85/145 | Reuses base Bijuu graphics; Technician |
| Elemental Rikos | 1582–1589 | Fire, Water, Grass, Electric, Ice, Psychic, Flying, Dragon | Same stats as base Riko | Separate species entries with individual asset references and borrowed learnsets |
| Elemental Bijuus | 1590–1597 | Fighting, Poison, Ground, Rock, Bug, Ghost, Dark, Steel | See individual entries | Separate species entries with individual asset references |
| Riko Spirit | 1598 | Fire/Fairy | 115/115/85/90/75/100 | Separate assets and Entei-like custom learnset; sublegendary flag |
| Wing Riko | 1599 | Fairy/Flying | 90/75/85/105/95/110 | Separate assets; base Riko learnset; Brush evolves back to base |
| Penny | `SPECIES_FIDOUGH` | Fairy | 37/55/70/30/55/65 | Existing Fidough species renamed Penny; remains Fidough internally |

Base Riko has Cute Charm, no second normal ability, and hidden Fluffy. Bijuu has Limber, no second normal ability, and hidden Technician. Spirit has Pressure and hidden Flash Fire.

Penny is not an additional species ID. Its `gen_9_families.h` entry still references Fidough assets, dex number, and learnsets and evolves into Dachsbun at level 26. Trainer-party text can therefore correctly say `Fidough` while the displayed species is Penny. Inspect the referenced Fidough art before treating any appearance as an asset bug.

All custom Riko identities share `NATIONAL_DEX_RIKO`; Bijuu identities share `NATIONAL_DEX_BIJUU`. Sharing a dex number does not automatically register a form relationship or make a variant reachable. The current form-species tables list base plus Mega only; elemental variants and Wing are not automatically available through those tables.

Fresh-save setup in `src/new_game.c`:
1. Clear the party and create level-5 Riko, Fidough/Penny, and Riko Spirit in slots 0, 1, 2.
2. The chosen starter is added later by the starter flow.
3. Clear the Bag, then add the personalized testing items, including one Wand and one Blue Brush.
4. Under the Mega config, add Mega Ring and Bondstone.

Bijuu is not part of this initial three-member party. Changes here run only during new-game creation. Existing saves need an actual gift/pickup/migration path.

Spirit is also referenced by the Shoal Cave Suicune replacement event: level 90 and 80 non-catchable battles, followed by a level 70 final encounter. Old Suicune labels and flags are reused. Renaming a story character does not require indiscriminately renaming those identifiers.

## 3. Why the custom species function

The registration chain is:
`include/constants/species.h` species ID → enabled family config → `src/data/pokemon/custom_species.h` asset declarations and learnsets → `gSpeciesInfo` in `src/data/pokemon/species_info.h` → generic battle, party icon, and follower systems.

`src/pokemon.c` includes form species tables, form change tables, follower pic tables, then custom_species.h, then species_info.h. Preserve declaration order: symbols must exist before an entry references them.

Custom asset declarations use:
- Front/back: `INCBIN_U32(".../front.4bpp.smol")`, same for back.
- Battle palettes: `INCBIN_U16(".../normal.gbapal")` and shiny.
- Icon: `INCBIN_U8(".../icon.4bpp")`; separate normal/shiny icon palettes.
- Follower: uncompressed `INCBIN_U32(".../overworld.4bpp")`; separate normal/shiny follower palettes.
- Follower frame table: `overworld_ascending_frames(gObjectEventPic_Name, 4, 4)`.

The species entry links all pointers and uses `OVERWORLD(sPicTable_Name, SIZE_32x32, ..., sAnimTable_Following, normalPalette, shinyPalette)`. Putting a PNG in a plausible folder alone has no effect.

The working custom followers read `graphics/pokemon/<species>/overworld.png` and their species-specific palettes. Earlier files under `graphics/object_events/pics/pokemon/followers/` were not their active assets.

## 4. Exact graphics contract for this custom-species pattern

| Asset | Source dimensions/layout | Output | Uncompressed data size |
|---|---|---|---:|
| Front battle art | 64×64, single frame for current custom entries | .4bpp.smol | 2048 bytes before compression |
| Back battle art | 64×64 | .4bpp.smol | 2048 bytes before compression |
| Party icon | 32×64: two vertically stacked 32×32 frames | .4bpp | 1024 bytes |
| Follower | 192×32: six horizontal 32×32 frames | .4bpp | 3072 bytes |
| Item icon | 24×24: 3×3 tiles of 8×8 | .4bpp.smol | 288 bytes before compression |
| 4bpp palette | 16 ordered RGB entries in JASC-PAL source | .gbapal | 32 bytes |

These dimensions apply to the current pattern; the engine supports other explicitly configured species sizes. Do not silently change a sheet size without updating its metadata and conversion.

Palette requirements:
- Indexed PNG, not RGB/RGBA. Use at most 16 referenced indices (0–15), including transparent slot 0.
- Empty pixels must be index 0. A PNG alpha channel or tRNS chunk is not a substitute for the GBA transparent index.
- For normal display, the numeric PNG palette indices must match the corresponding .pal color order.
- Shiny palettes keep identical index meanings while intentionally changing colors.
- Front and back must use the same index-to-color mapping because these species entries provide one normal and one shiny battle palette. The existence of `back_normal.pal` does not mean it is selected at runtime.
- Icon and follower palettes can differ from battle palettes; each must match its own PNG.
- The .pal begins with `JASC-PAL`, `0100`, `16`, then 16 RGB triples.
- The GBA palette conversion reduces RGB precision; inspect the compiled result if subtle shades merge.

Important correction to the older handoff: source PNG bit depth need not always be 4. Header checks show base Riko is indexed 4-bit, but Wing Riko and the Wand/Brush are indexed 8-bit. `tools/gbagfx/convert_png.c` accepts indexed input and converts bit depth. 8-bit input is acceptable only when all referenced indices fit the 4bpp output. Palette length of 256 alone is not proof of excessive used colors.

Header checks in this review confirmed the dimensions above for base Riko front/back/icon/follower, Wing front/icon/follower, and Wand/Brush item icons. Wing front/follower and Wand .pal files match their PNG's first 16 palette colors. Pixel data were not decompressed to exhaustively check all used indices in this review.

Follower frame order, from `sAnimTable_Following` and its animation commands:

| Frames, zero-based | Meaning |
|---|---|
| 0, 1 | Facing/walking south |
| 2, 3 | Facing/walking north |
| 4, 5 | Facing/walking west |
| East | Frames 4, 5 mirrored horizontally |

There are two frames per direction, not a three-pose walk cycle. Do not put unique east-facing art into this six-frame layout. Asymmetric east art would require the asymmetric animation table and additional frames, including checking enter/exit animations.

Preserve the custom frame-aware Makefile conversion:
```make
$(filter %.4bpp,$(RIKO_OVERWORLD_GFX)): %.4bpp: %.png
	$(GFX) $< $@ -mwidth 4 -mheight 4
```
A 32×32 frame is a 4×4 tile block. Ordinary row-major conversion of a wide strip interleaves tiles from different frames; the special conversion makes each frame contiguous. This was a distinct cause of the earlier broken/blob followers even after correcting palettes.

Add new follower outputs and both palette outputs to `RIKO_OVERWORLD_GFX`; preserve its `pokemon.o` dependency. Follow the current `RIKO_VARIANT_GFX` and `RIKO_MEGA_GFX` patterns for corresponding new battle/icon outputs. Build-generated files are outputs; edit the PNG/PAL sources and ensure the output is regenerated. Tracked compiled assets can hide mistakes during incremental builds, so use a clean checkout/build for release validation.

## 5. Adding a species without breaking existing saves

1. Decide whether this is a new species, permanent evolution, or temporary form.
2. Append a new species ID after 1599 and before the egg sentinel. At this snapshot, 1600 is the next candidate; recheck current head before allocation.
3. Update `SPECIES_EGG` to the last real species + 1; `NUM_SPECIES` remains `SPECIES_EGG`. Do not count Egg as a regular species.
4. Never renumber existing real species: their IDs are saved in Pokémon data.
5. Enable the family where applicable in `include/config/species_enabled.h`. Keep declarations, entries, and form tables under consistent config guards.
6. Declare referenced battle/icon/follower symbols in custom_species.h before gSpeciesInfo uses them. Prefer copying the complete RikoWing pattern.
7. Supply a complete species entry: stats, types, abilities, gender, growth/friendship/egg data, catch/experience/EV yields, cry, name/dex text, size/offsets, all graphics and palettes, icon, follower, and learnsets.
8. Terminate custom level-up lists with `LEVEL_UP_END`. Borrowed lists can be reused when intentional. An ALL_TEACHABLES policy is broad compatibility, not a carefully balanced custom TM list.
9. For a new independent dex identity, append National/Johto dex constants and review count/mapping/order logic plus alphabetical, height, and weight lists in `src/data/pokemon/pokedex_orders.h`. For a same-dex variant, explicitly choose which dex and form behavior is intended.
10. Register evolution or form-change tables only for the intended mechanism, with their terminators.
11. Add an actual acquisition path. A valid species entry does not create an encounter or give a Pokémon.
12. Validate all appearances, including shiny art and reload after evolution.

Fork text limits: `POKEMON_NAME_LENGTH=12`, `ITEM_NAME_LENGTH=20`, plural item length 22, trainer name length 10, move name length 16, ability name length 16, player name length 7. Use the appropriate encoding macros and leave room for terminators according to their definitions. Character count alone does not guarantee that text fits a UI window; check rendered width.

## 6. Item definitions, graphics, and behavior

Current added IDs:

| Item | ID | Behavior | Art |
|---|---:|---|---|
| Bondstone | 919 | Mega Stone held effect; not consumed | Audinite icon/palette |
| Riko's Purse | 930 | Wise Glasses held effect, parameter 10 | Coin Case |
| Bijuu's Pom Poms | 931 | Choice Scarf held effect | Fluffy Tail |
| Penny's Blankey | 932 | Leftovers held effect | Silk Scarf |
| Riko's Wand | 933 | Evolution item: Riko → Wing | Custom wand |
| Blue Brush | 934 | Evolution item: Wing → Riko | Custom brush |

The three held items use existing generic effects; their names do not restrict them to a particular pet. Restrictions require additional mechanics. The Blankey's source parameter is 10, but the authoritative healing rule is the Leftovers handler; do not interpret that field as a promise of 10 HP or 10 percent.

New item checklist:
1. Append a unique item enum before `ITEMS_COUNT` in `include/constants/items.h`. At this commit 935 is next, but check head first. Preserve existing IDs and special sentinels, including `ITEM_FIELD_ARROW`.
2. Add designated `[ITEM_NEW]` data to `gItemsInfo` in `src/data/items.h`.
3. Set name/plural if needed, description, price, pocket, sort type, held slot, use type/function, and relevant battle/held/effect fields. Clone the nearest working behavior, not an unrelated item.
4. For new art, add a 24×24 indexed PNG under `graphics/items/icons/` and a matching 16-color palette under `graphics/items/icon_palettes/`.
5. Declare compressed picture and palette symbols in `src/data/graphics/items.h`, then link `.iconPic` and `.iconPalette` in gItemsInfo.
6. Add a gift, shop, or pickup and verify it is reachable in the right game state.

Do not populate a legacy standalone item icon table from vanilla tutorials. This fork's `src/data/item_icon_table.h` is effectively empty; `src/item_icon.c` obtains icons directly from gItemsInfo.

The item renderer decompresses a 288-byte 24×24 source into a 32×32 display buffer. A 32×32 source supplied to this contract is therefore not a safe substitute.

For an evolution item, the current working contract is:
```c
.pocket = POCKET_ITEMS,
.sortType = ITEM_TYPE_EVOLUTION_STONE,
.heldSlot = 0,
.type = ITEM_USE_PARTY_MENU,
.fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
.effect = gItemEffect_EvoItem,
```
The species provides the actual allowed target:
```c
// Base Riko:
.evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_WAND, SPECIES_RIKO_WING}),
// Wing:
.evolutions = EVOLUTION({EVO_ITEM, ITEM_BLUE_BRUSH, SPECIES_RIKO}),
```
These are persistent species changes through the standard evolution flow. The items have no notConsumed flag, so treat them as consumable evolution items and verify consumption during playtesting.

Mega is separate: Riko/Bijuu form-change tables use `FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM` with Bondstone and revert on faint/end of battle. Wing has no Mega form table. Do not use `SPECIES_MEGA_RIKO` as a permanent evolution target.

Reskins preserve the existing ID and mechanics. Potion is displayed as McDonalds Wawa S and still restores 20 HP; Great Ball and berry reskins similarly affect every use of those original item IDs. Creating a distinct item avoids globally replacing an existing item.

## 7. Placing items and encounters on the actual map

Trace what the player can activate:
displayed place → map.json object/coord event → script label → trainer/item/species constant → implementation.
Do not choose a map or trainer by an inherited name alone.

First rival battle:
- The current New Bark Town script references `TRAINER_RIVALGOLD1` and `TRAINER_RIVALCRYSTAL1`.
- Each current trainer record contains three level-5 Fidoughs.
- Route30 has normal trainers and Elm's call, but no rival battle command in the reviewed script.
- Old trainer IDs such as `TRAINER_BRENDAN_ROUTE_103_...` describe other records and do not identify the opening battle.

Current Route30 item object:
- `OBJ_EVENT_GFX_POKE_BALL`, x=28, y=32, elevation=0.
- Script `Route30_EventScript_RikoEvolutionItems`.
- Persistent visibility flag `FLAG_ITEM_ROUTE30_RIKO_EVOLUTION_ITEMS` = 0x3EC.
- The script gives Wand, checks VAR_RESULT, gives Brush, checks again, sets the flag, and displays a message.

The object exists in source; its collision, reachability, and elevation have not been checked in an emulator here. Setting its flag hides it on subsequent map loading; immediate removal was not implemented in this script.

A two-item gift has an edge case: if Wand succeeds but Brush fails because the Bag is full, the completion flag stays unset and retry can grant another Wand. It is not atomic. Prefer separate flagged pickups, per-item flags, or a correctly designed combined-space/rollback operation. Two independent space checks alone can both succeed while competing for the same final pocket slot.

For ordinary item balls this fork stores the item ID in `trainer_sight_or_berry_tree_id`; quantity comes from movement_range_x (zero defaults to one), per src/item_ball.c. Follow the standard item-ball script when giving one item. A custom two-item script is responsible for its own flag and removal behavior.

For any placement:
- Use the actual map JSON/layout. Verify coordinates, adjacent walkable tiles, elevation, and trigger direction in Porymap or an emulator.
- Appending an object preserves existing array-based local IDs; insertion can shift IDs used by applymovement/removeobject.
- Allocate unique persistent flags; flags also live in saves. Do not casually reuse a historical event flag.
- Check lock/release behavior on every failure path.
- A shop requires its active script path and state gating, not just an item definition. Raw assembly mart lists are halfwords ending in ITEM_NONE; Poryscript mart declarations generate this structure.
- Cherrygrove's reviewed .pory has different clerk paths before/after VAR_NEWBARK_TOWN_STATE thresholds, illustrating why adding an item to the wrong stock list may never show it.

## 8. A concrete source-of-truth problem: .pory versus .inc

NewBarkTown contains both scripts.pory and scripts.inc.
At this commit:
- scripts.inc says “I've got three Fidoughs of my own.”
- scripts.pory still has the older “That's a cute Pokémon you have!”, follower tutorial text, and “both of our Pokémon” post-battle wording.

The Makefile declares:
```make
data/%.inc: data/%.pory
	$(SCRIPT) -i $< -o $@ -fc tools/poryscript/font_config.json -cc tools/poryscript/command_config.json -lm=false
```
.pory files are also listed among generated targets. When Make regenerates the .inc, edits made only to that .inc can be overwritten by the older .pory source. This is a source-verified overwrite mechanism and a plausible explanation for reverted dialogue; the exact ROM dialogue has not been inspected here.

Rule: when a .pory counterpart exists, edit .pory and regenerate .inc. When none exists, edit the assembly .inc directly. Do not perform a broad text replacement on both without respecting their different syntax. The NewBarkTown .pory includes raw assembly plus Poryscript, so preserve raw blocks and syntax.

Before a future dialogue pass, reconcile those two versions, regenerate, and inspect the generated text. This is the highest-priority follow-up from this review.

## 9. Trainer and text formatting

Edit `src/data/trainers.party`, not generated trainers.h. The file's own documentation requires a blank line between trainer metadata and the first Pokémon and between Pokémon records. Keep a blank line before the next `=== TRAINER_ID ===` too. trainerproc explicitly reports “expected empty line”.

Minimal shape:
```text
=== TRAINER_RIVALGOLD1 ===
Name: Gold
Pic: Brendan
Gender: Male

Fidough
Level: 5
Ability: Own Tempo
- Tackle
- Tail Whip

Fidough
Level: 5
Ability: Own Tempo
- Tackle
- Tail Whip

```
Use parser-recognized names or constants for species, moves, abilities, and items. Preserve required Name/Pic fields and stay within party size 6. A display rename does not automatically change the parser's species token.

Assembly dialogue uses .string, appropriate escaped line/page breaks, and a final $. C strings use _()/COMPOUND_STRING and supported charmap characters. Poryscript strings use its own rules. ASCII punctuation is a conservative editing convention, not evidence that all accented characters are invalid: this fork already contains Pokémon. Confirm charmap support and text width.

## 10. Validation sequence for every iteration

Before editing, record the base SHA and the exact player trigger. Limit each change to one testable feature.

Fast checks:
1. Check actual constants, guards, symbols, input files, and output suffixes.
2. Inspect PNG dimensions, indexed mode, used indices, palette slot 0, and palette order.
3. Regenerate any .pory-controlled script and .party-controlled trainer header; check generated results.
4. Parse edited map JSON and check script labels, unique flags, local IDs, and placement.
5. Run the docs validator when adding Markdown pages; every relevant docs/*.md must appear in docs/SUMMARY.md.
6. Run the feature's asset/generator targets before the full ROM build, in a configured Linux/WSL toolchain.
7. Review the diff for unintended generated/source divergence.

Full build, using the CI configuration in a configured Bash/Linux environment:
```bash
GAME_VERSION=EMERALD GAME_REVISION=0 GAME_LANGUAGE=ENGLISH COMPARE=0 UNUSED_ERROR=1 DEPRECATED_ERROR=1 make -j"$(nproc)" -O all
TEST=1 GAME_VERSION=EMERALD GAME_REVISION=0 GAME_LANGUAGE=ENGLISH COMPARE=0 UNUSED_ERROR=1 DEPRECATED_ERROR=1 make -j"$(nproc)" check
python3 .github/docs_validate/inclusive_summary.py
```
These are reference commands, not checks executed in this research session. The local shell could not start because of an environment setup error. Source review and binary-header inspection were performed through the repository connector.

Workflow detail: current ROM step says `make -j${nproc} -O all`; unless that variable is defined, it expands to bare -j (unlimited jobs). `$(nproc)` is the intended core-count command used by the Test step. This is a follow-up build-stability improvement, not a proven cause of the recent syntax failures.

Avoid rebuilding everything blindly after a failure. Read the first actual parser/compiler/converter error, not just the final “make failed” message, and fix the owning source. Clean builds are useful for source/output validation, especially after graphics changes; incremental builds are useful while iterating.

Emulator acceptance checks:
- Artifact branch and head SHA match the intended commit.
- Fresh save has the expected party and items in their correct Bag pockets.
- Existing save can obtain added items without replaying completed story events.
- Wand on Riko produces Wing; wrong targets fail cleanly; item consumption is correct.
- Brush restores base Riko; repeat the cycle, save, reload, and inspect summary/dex.
- Battle front/back, menu icon, all follower directions, and shiny palettes are correct.
- Mega transforms/reverts correctly; Wing's unsupported Mega behavior is understood.
- Both player-gender rival variants use the correct team and updated dialogue.
- Bag-full pickup failure and retry do not duplicate or lose items.
- Check event object disappearance immediately and after leaving/reentering the map.

Compilation proves the data can build. Automated battle tests do not prove that an object is reachable or that the player saw the intended script.

Build #80/run 37712988132 status during this review: ROM step and Upload ROM artifact succeeded; Test was still in progress at the check. Artifact `soulgold-rom` belongs to SHA 724570bfcb4268d48837a76d8f751d77ca4e8318. This is a confirmed built/uploaded ROM, not yet confirmation that all tests or manual gameplay checks passed.

## 11. Suggested safeguards for a later implementation

These are proposals, not installed tooling:
- A custom-content manifest of stable species/item IDs, source asset paths, expected dimensions, palette files, and acquisition scripts.
- A pre-build validator for manifest IDs/guards, referenced files, indexed PNGs/used indices, palette ordering, trainer separators, and docs index coverage.
- An explicit generator consistency check for edited .pory/.inc pairs, ideally in CI before compiling the ROM.
- A small in-game verification NPC/menu that reports a build marker and grants test content on demand without changing normal new-game progression.
- A reliable artifact record containing source SHA, branch, filename, and acceptance-check results.

Next implementation order: reconcile NewBarkTown .pory/.inc; repair the multi-item pickup retry/removal semantics; verify Route30 coordinates in-game; then add automated preflight checks. The engine architecture is already suitable for further pets/items; the largest recurring risk is incomplete registration or editing a generated/inactive source.

## 12. Source file map and handoff capsule

Core source links pinned to the reviewed commit:
- [README.md](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/README.md)
- [Makefile](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/Makefile)
- [.github/workflows/build.yml](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/.github/workflows/build.yml)
- [include/constants/species.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/include/constants/species.h)
- [include/config/species_enabled.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/include/config/species_enabled.h)
- [include/constants/global.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/include/constants/global.h)
- [include/constants/pokedex.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/include/constants/pokedex.h)
- [src/data/pokemon/custom_species.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/data/pokemon/custom_species.h)
- [src/data/pokemon/species_info.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/data/pokemon/species_info.h)
- [src/data/pokemon/species_info/gen_9_families.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/data/pokemon/species_info/gen_9_families.h)
- [src/data/pokemon/form_species_tables.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/data/pokemon/form_species_tables.h)
- [src/data/pokemon/form_change_tables.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/data/pokemon/form_change_tables.h)
- [src/data/pokemon/pokedex_orders.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/data/pokemon/pokedex_orders.h)
- [src/data/object_events/object_event_anims.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/data/object_events/object_event_anims.h)
- [include/constants/items.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/include/constants/items.h)
- [src/data/items.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/data/items.h)
- [src/data/graphics/items.h](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/data/graphics/items.h)
- [src/item_icon.c](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/item_icon.c)
- [src/item_ball.c](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/item_ball.c)
- [src/new_game.c](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/new_game.c)
- [data/maps/NewBarkTown/scripts.pory](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/data/maps/NewBarkTown/scripts.pory)
- [data/maps/NewBarkTown/scripts.inc](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/data/maps/NewBarkTown/scripts.inc)
- [data/maps/Route30/map.json](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/data/maps/Route30/map.json)
- [data/maps/Route30/scripts.inc](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/data/maps/Route30/scripts.inc)
- [src/data/trainers.party](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/src/data/trainers.party)
- [tools/trainerproc/main.c](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/tools/trainerproc/main.c)
- [tools/gbagfx/convert_png.c](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/tools/gbagfx/convert_png.c)
- [asm/macros/event.inc](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/asm/macros/event.inc)
- [.github/docs_validate/inclusive_summary.py](https://github.com/badabingbadaboom850/modding-sandbox/blob/724570bfcb4268d48837a76d8f751d77ca4e8318/.github/docs_validate/inclusive_summary.py)

Copy into a future editing session:
> Use the current fork source as authority. This is an Emerald GBA expansion project. Preserve species/item IDs. Edit .pory when present; .inc may be generated. Edit trainers.party and preserve blank record separators. Custom species use per-species icon palettes, .smol battle pictures, and species-linked follower assets. Followers are 192×32, ordered south/south/north/north/west/west, with east mirrored and frame-aware -mwidth 4 -mheight 4 conversion. Item sources are 24×24. Keep indexed pixel indices within 0–15 and slot 0 transparent. Verify source SHA against the built artifact, then test the actual event in an emulator. Read the current guide and source before treating this snapshot as current.
