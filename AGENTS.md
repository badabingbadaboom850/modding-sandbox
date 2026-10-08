# Repository guidance for future agents

## Purpose and source of truth

This is the user's personalized Soulgold GBA ROM hack for their wife, built on an Emerald-derived engine with Johto/Kanto maps. Do not treat it as a Nintendo DS HeartGold/SoulSilver binary-editing project, or assume Emerald's opening-route numbering describes the active story.

The legendary girls are Riko (Pomeranian), Penny (rescue dachshund, represented by Fidough), and Bijuu (Siamese cat). Keep dialogue affectionate, playful, and specific to their personalities. Penny's confidence grows through safety and her sisters' support; avoid treating fear as failure. The user explicitly permits dialogue to assume all three girls remain with the player.

Read current code before relying on this file or old handoffs. This file records findings verified against test-branch commit 69562abdc0cb6706b87d837898614936516f97fb on 2026-10-08. It is not a claim that every current feature has passed an emulator test.

Repository: badabingbadaboom850/modding-sandbox.
At this snapshot, draft PR #2 uses feat/riko-lab-interruption-pilot and targets feat/riko-bijuu-mega-forms. Check the current head before editing. Work on the requested branch, preserve other sessions' changes, and do not merge the gameplay branch unless requested. Publish related multi-file changes atomically; use an expected-head lease when updating a remote ref.

## Map awareness and event wiring

- The early story runs New Bark Town -> Route 29 -> Cherrygrove -> Route 30/31 -> Violet. The first active rival encounter belongs to the Route 30 story, not the leftover Route 103 Brendan scripts. Bijuu's early chase is on Route 31.
- Legacy Route 101/102/103 scripts can still be included in the build without being the scene the player reaches. A successful build or an edited text label does not prove the player encounters that dialogue.
- For an interaction, trace data/maps/<map>/map.json object_events, coord_events, bg_events, and map-script dispatch to the exact script and text label. Then verify its inclusion in data/event_scripts.s. For layouts/warps, also inspect the assigned layout and tilesets.
- Preserve exact spelling and case. CherryGroveCity and CherrygroveCity both occur in labels; Mahoganytown is the outdoor map directory while MahoganyTown_Gym uses another capitalization.
- Read visibility flags and story-state branches. An NPC can disappear during story events. Goldenrod civilians and Rocket NPCs have different takeover visibility; cover both without forcibly unhiding them.
- Cinnabar's ordinary persistent speakers are in its Pokemon Center. Blue and Blaine's outdoor appearances are story-gated and may disappear. Do not count temporary cameos as permanent town coverage.
- Main Gym introductions are not the only leader dialogue. Follow defeat, rewards, return visits, and rematches. SaffronCity_FightingDojoVIP has separate rematch introductions and defeat text for all 16 leaders.
- Validate warp destination map, warp index versus explicit coordinates, bounds, occupancy, and tile behavior. Valid source coordinates do not establish successful runtime map loading.
- When adding NPCs, reuse an existing registered human graphic where appropriate, choose an unused local object ID and safe walkable coordinates, and connect the object script explicitly. Inspect all existing map events first. Preserve story objects, item flags, warps, and movement paths.

## Dialogue authoring and propagation

Some maps have scripts.pory plus compiled scripts.inc, often with large raw blocks. Others have only scripts.inc. Inspect each map rather than assuming one uniform authoring format.

When both exist, change the authoring source and corresponding assembly consistently. Raw Pory content should match its assembly section. Text generated from high-level Pory msgbox calls must be edited in the high-level source and regenerated or matched correctly; do not assume a generated label exists verbatim in the Pory file.

Earlier Goldenrod/Ecruteak authoring files contained missing closing quotes and punctuation mismatches despite usable assembly. Those raw blocks were reconciled during the broad dialogue pass. Check quotes, duplicate labels, unresolved references, and source/assembly agreement.

- Assembly text ends with $. Use \n for the second line, \p for a new page, and \l only for intentional scrolling. Avoid consecutive \n controls that produce more than two rows.
- New dialogue was conservatively wrapped to 26 characters per line and two lines per page. This is a useful baseline; account for font width, substitutions, and mugshots rather than assuming character count alone guarantees fit.
- Prefer simple ASCII punctuation for new game strings. Preserve necessary original controls and substitutions such as {PLAYER}. Avoid adding unsupported Unicode, smart quotes, or accidental unterminated strings.
- Preserve original directions, quest hints, yes/no outcomes, services, healing, rewards, and lock/release behavior when adding flavor.
- Vary stories: individual pet quirks, local opinions, ordinary moments, the mysterious trainer's travels, and respect for leaders who held their own. Do not repeat a generic legendary-trio rumor everywhere.
- Gate claims about completed Gym matches with the actual corresponding Badge flag. Follow the gym's setflag path to confirm the mapping. Do not invent a victory before it happens.
- Broad pass: 183 expanded entries across 44 map scripts, plus 19 badge-dependent rumor variants. These counts describe source edits, not exhaustive runtime verification.

## Species registration, forms, and identity

Current definitions live in include/constants/species.h, src/data/pokemon/species_info.h, and src/data/pokemon/custom_species.h. Family/configuration guards must enable the entries.

Verified IDs at the recorded snapshot:

| Identity | Symbol / range |
| --- | --- |
| Riko | SPECIES_RIKO = 1578 |
| Bijuu | SPECIES_BIJUU = 1579 |
| Mega Riko / Mega Bijuu | 1580 / 1581 |
| Riko elemental variants | 1582-1589 |
| Bijuu elemental variants | 1590-1597 |
| Spirit of Riko | SPECIES_RIKO_SPIRIT = 1598 |
| Winged Riko | SPECIES_RIKO_WING = 1599 |
| Psychic Bijuu | SPECIES_BIJUU_PSYCHIC = 1600 |
| Egg sentinel | SPECIES_EGG = SPECIES_BIJUU_PSYCHIC + 1 |

Use symbols in game code. Do not allocate a new species from this table without checking the current tail, egg sentinel, NUM_SPECIES, table sizes, family guards, dex identity/order, and any generated tables.

A complete custom species needs stats, types, abilities, naming/dex data, learnsets, battle front/back graphics and normal/shiny palettes, menu icon registration, and follower data. Trace includes through src/pokemon.c; an asset file by itself is not registration.

Penny uses SPECIES_FIDOUGH. Inspect her actual entry in src/data/pokemon/species_info/gen_9_families.h and any renamed evolution/display data before changing her line. Do not invent SPECIES_PENNY or assume a display rename changes engine identity.

Party checks are exact-ID comparisons: Scrcmd_checkspecies in src/scrcmd.c calls CheckPartyHasSpecies in src/field_specials.c. That helper compares MON_DATA_SPECIES and does not normalize forms or explicitly exclude eggs.

Use/extend data/scripts/trio_party_checks.inc for Riko/Bijuu form-family checks. Verify coverage whenever adding a species; the newly added Psychic Bijuu must be considered. Spirit of Riko is a separate story entity and must not count as ordinary Riko without an explicit design change. Do not assume a Mega-only battle species must occur in an ordinary overworld party.

## Custom follower sprites: the fixes that mattered

Working custom followers use species assets under graphics/pokemon/<species>/, not simply graphics/object_events/pics/pokemon/followers/.

For the established Riko/Bijuu follower format:

- overworld.png is a 192x32 horizontal strip of six 32x32 frames.
- Use indexed 4-bit art with 16 palette entries. Empty pixels must be palette index 0, which is transparent.
- The indexed PNG's palette order and overworld_normal.pal / overworld_shiny.pal must agree exactly. Wrong palette order caused black/distorted sprites even when the source art looked correct.
- Palette correction alone did not fix duplicated/choppy frames. Frame-aware tile conversion was also required.
- Makefile lists custom follower outputs in RIKO_OVERWORLD_GFX and converts them using $(GFX) $< $@ -mwidth 4 -mheight 4. A 32x32 frame is a 4x4 group of 8x8 tiles; this keeps each frame contiguous.
- Add new follower assets to both the special conversion list and the pokemon.o dependencies so edits actually rebuild.
- custom_species.h declares graphics/palette pointers and a picture table using overworld_ascending_frames(..., 4, 4).
- The species entry's OVERWORLD(...) registration supplies the picture table, SIZE_32x32, shadow/tracks, sAnimTable_Following, and normal/shiny palettes.
- Generated .4bpp and .gbapal assets are consumed by runtime registration. Test direction/frame order, idle/walk, normal/shiny colors, and the evolved follower after form changes.

A species can intentionally share follower art. Inspect its actual table pointer before expecting unique art, especially for Mega entries. Battle sprites, icons, and follower sheets are separate asset paths; fixing one does not fix the others.

## Items: wire behavior, graphics, and availability separately

Item IDs are in include/constants/items.h. Current custom items use complete entries in src/data/items.h, including iconPic/iconPalette pointers. Trace those symbols to their graphics declarations/includes rather than assuming an older separate icon table is authoritative.

An evolution item needs all of:
- a unique current item ID and valid name/description;
- the intended pocket and sort type;
- ITEM_USE_PARTY_MENU;
- ItemUseOutOfBattle_EvolutionStone;
- gItemEffect_EvoItem;
- matching species EVO_ITEM evolution data;
- registered icon/palette assets;
- a reachable source such as a shop, pickup, or explicit test grant.

A new item name or sprite alone does not make it usable or obtainable. A shop must include its ID in the actual pokemart list; price comes from item data. Goldenrod Department Store 4F's vitamin shop uses the historically named Goldenrod_DepartmentStore_3F_Pokemart_Vitamins list: trace the map script rather than trusting that label's floor number.

Verified Riko's Wand / Blue Brush price is 500 each, stocked on Goldenrod Department Store 4F. Route 30's Riko pickup remains. Their fresh-save grants were removed during cleanup. Current Bijuu Fish Toy / Cat Nip test grants were subsequently added; do not remove or conflate those with the retired Riko grants.

The held items currently reuse existing behavior/art:
- Riko's Purse: Wise Glasses effect, Coin Case icon.
- Bijuu's Pom Poms: Choice Scarf effect, Fluffy Tail icon.
- Penny's Blankey: Leftovers effect, Silk Scarf icon.
Reuse proven held-effect code unless the user requests a distinct mechanic.

Potions are presented as McDonald's Wawa in this project. Scripts can still use ITEM_POTION; new reward dialogue should call it Wawa rather than restoring the old presentation.

Changing an existing item's name/icon rethemes every use of that item. Add a separate ID when a pet-specific item should not replace a standard stone globally.

## Permanent evolution versus temporary battle transformation

Permanent item evolution uses the species entry's .evolutions = EVOLUTION({EVO_ITEM, ITEM_..., SPECIES_...}). Reverse item evolution can return the evolved species to its base entry.

Current verified pairs:

| Source | Item | Target |
| --- | --- | --- |
| SPECIES_RIKO | ITEM_RIKOS_WAND | SPECIES_RIKO_WING |
| SPECIES_RIKO_WING | ITEM_BLUE_BRUSH | SPECIES_RIKO |
| SPECIES_BIJUU | ITEM_BIJUUS_FISH_TOY | SPECIES_BIJUU_PSYCHIC |
| SPECIES_BIJUU_PSYCHIC | ITEM_BIJUUS_CAT_NIP | SPECIES_BIJUU |

Riko's two items were confirmed to work by the user. Do not describe Bijuu's pair as emulator-confirmed based only on source registration.

Mega forms use separate form_species_tables.h / form_change_tables.h rules, including battle-end/faint reversion. Keep ITEM_BONDSTONE's battle Mega behavior separate from permanent evolution; do not repurpose SPECIES_MEGA_RIKO as a permanent target.

Existing elemental variants do not automatically become reachable evolution branches. Check the current base species evolution list; several branches can share one EVOLUTION list, but their trigger mapping is a design choice.

Test item eligibility, correct target, item consumption, evolution scene, menu icon, battle art, dex entry, follower, save/reload, reverse evolution, and faint/battle-end behavior.

## Saves, one-time quests, and battle cleanup

src/new_game.c initializes fresh saves only. Starting-party/inventory changes do not add or remove items from an existing save. Confirm the actual initialization and story grants; do not assume the trio is all granted by one function.

Named save variables already reserved:
- VAR_ROUTE31_BIJUU_CHASE = 0x4121.
- VAR_TRIO_RESEARCH_STATE = 0x4122.
- VAR_PENNY_CONFIDENCE_STATE = 0x4123.

Before adding a var/flag, search all definitions and raw/numeric uses, confirm save bounds, and avoid scratch/temp storage for persistent progression. Do not assume the next numeric slot remains free.

The giveitem macro calls Std_ObtainItem in data/scripts/obtain_item.inc. Its final VAR_RESULT is TRUE on success, FALSE on failure. Check it immediately before another command clobbers it. Mark a one-time reward claimed only after success; a full Bag must allow retry without duplicated rewards.

Penny's Mom quest is Badge-gated and retains Mom's original healing call. Pending-reward dialogue must still make sense if other party members are absent on a later visit.

Shared Spirit battle setup is in data/scripts/trio_spirit_trials.inc. FLAG_SYS_NO_CATCHING only works because include/config/battle.h connects B_FLAG_NO_CATCHING to it. Clear restrictions on normal battle returns and verify whiteout cleanup. Do not rely on a trailing script clear after defeat if whiteout skips that tail. Prefer direct helper calls to unnecessary scratch-flag guards.

## Unresolved cave issue and retired diagnostics

The Spirit cave is ShoalCave_LowTideIceRoom_Suicune. User-tested direct battles worked and were difficult as intended; an upstairs-room control warp also worked. Cave loading still blackscreened in the reported tests.

Two verified out-of-range primary metatiles were repaired without changing collision/elevation. Snow was disabled and transition/resume time callbacks were bypassed. Those changes did not establish a fix. Snow sprite-allocation hang risk is a hypothesis, not a proven cause.

Temporary New Bark mailbox battles, Mom's friend's travel/battle/bedroom prompts, and forced visibility overrides were removed. Do not reintroduce them as ordinary gameplay without request. Keep her normal dialogue and ordinary home entrance.

Further cave work should isolate map rendering, tilesets, object graphics, and callbacks with controlled tests. A successful direct battle does not validate cave loading or cave completion flags.

## Validation and reporting

- Check the current branch/head and scoped AGENTS.md files before editing.
- Use rg for local source searches; inspect every touched registration and active event reference.
- For scripts, check label preservation/uniqueness, reference resolution, Pory/assembly synchronization, text terminators/page controls, and unchanged unrelated gameplay commands.
- Follow the current CI workflow. It builds Soulgold.gba and uploads soulgold-rom, then runs make check. ROM build/artifact success and later test-job success are separate results.
- CI runs for pull_request events; pushing a branch does not always trigger the push workflow because branch filters apply. Verify a run for the exact committed SHA.
- New pages under docs/ must be listed in docs/SUMMARY.md. Root AGENTS.md is outside that validator's docs tree.
- Check new and existing saves when appropriate, including absent-party cases, full Bag, repeated/out-of-order interactions, and whiteout.
- Report source checks, compilation, artifact availability, CI tests, and emulator/user confirmation separately. Do not claim monitoring after a turn ends.
- Keep this file updated when a later verified change makes a rule or snapshot obsolete.

## Additional references

docs/riko_in_game_implementation_and_evolution.md explains follower registration and tile ordering, but its older species/evolution snapshot and planning notes are stale in several places. Current code overrides statements such as "Riko has no evolutions" or "Spirit is the final species ID."

docs/trio_test_portal_update.md records cave diagnostics, cleanup, research/Penny pilots, and the broad dialogue pass. Earlier sections describe historical states; read later sections and current scripts before assuming a feature is absent.
