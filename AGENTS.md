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

Verified Riko's Wand / Blue Brush price is 500 each, stocked on Goldenrod Department Store 4F. The Route 30 ground pickup has been removed; the shop stock remains. Neither Riko evolution item is granted in new saves.

Fresh saves currently start with only Mega Ring and Bondstone when `P_GEN_9_MEGA_EVOLUTIONS` is enabled. Riko Ultra Ball, Penny Love Ball, Riko's Purse, and Penny's Blankey are no longer initial Bag grants; existing saves are not stripped. Other former test grants (berries, custom balls, Wawa potions, Cat Food Tin, Bijuu's Pom Poms, Fish Toy, and Cat Nip) are removed. Starting-party initialization is separate.

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
- VAR_TRIO_RESEARCH_STATE = 0x4122. Violet states 0-3 retain their meaning; Azalea uses 4-6 and Goldenrod uses 7-9. See docs/trio_world_roadmap.md. State 3 on older saves can accept the next chapter.
- VAR_ECRUTEAK_BIJUU_MYSTERY = 0x4124. Independent of the scrapbook: 0 offer; 1 accepted; 2 tower clue; 3 both clues; 4 fish toy found; 5 actual Psychic form witnessed/reward pending; 6 reveal completed.
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

## World-building first batch

docs/trio_world_roadmap.md is the implementation checklist and in-game test plan. The Cherrygrove research boy holds a readable scrapbook; Azalea's existing youngster and Goldenrod's existing woman outside the Name Rater host optional text vignettes. They do not add visible Pokemon objects or movement paths. New chapter scenes/acceptance require the trio; reward retry does not. Preserve Goldenrod's existing civilian disappearance during the Rocket takeover.

New family callbacks use badge flags, completed research chapter states, and FLAG_IS_CHAMPION. That Champion flag is explicitly set by the active PokemonLeague_HallOfFame_EventScript_SetFirstGameClearFlags. Original Caleb/Chelsea lines remain. Greg's level-99 encounters, existing sight behavior, trainer flags, and shared one-time Wawa reward remain.

Psychic Bijuu is now included in TrioParty_CheckBijuu. Pending reward states advance only after successful giveitem. The new state meanings and source checks do not establish emulator confirmation.

## Ecruteak celestial mystery

The optional chapter starts with the existing woman beside Eevee (35,43). The existing woman south of Burned Tower (19,22) supplies the first clue; the boy at the southeastern edge (52,49) supplies the second. Inspect the existing Burned Tower sign (23,14) to find Bijuu's Fish Toy. Original map objects, sign text, visibility, story progression, and NPC dialogue are retained.

Use the Fish Toy through the existing evolution item system on base Bijuu, then return to the quest host with SPECIES_BIJUU_PSYCHIC. Only the exact Psychic form triggers the reveal; ordinary Bijuu and other forms do not. A previously evolved Bijuu can also complete the clues and reveal. No forced species mutation or scripted evolution helper is introduced.

Toy discovery and the one-time catnip gift advance state only after giveitem succeeds. State 5 retries the gift even if Bijuu later changes form or leaves the party. The quest host offers spare Fish Toys and Cat Nip for 500 each at state 4 (including before evolution) and after completion. Existing Goldenrod Department Store 4F stock of both items remains. Losing or using a toy cannot permanently block the chapter.

Witnesses and a skeptic acknowledge the reveal at state 5 or later. Mom's family callback and the optional extra Cherrygrove scrapbook page use completed state 6. The quest uses an unused slot in the existing variable array, with no SaveBlock layout or species/item ID changes. Source checks and CI results are separate from emulator confirmation.

## Pet gender and starting party update

Fresh saves start with level-5 Riko and Penny only; Spirit of Riko is no longer a starting-party grant. Bijuu remains a catchable Route 31 story encounter. Removing the initial grant does not delete Spirit from an existing save; deposit her in the PC to remove her from an existing party.

Riko, Bijuu, their Mega/elemental/permanent forms, Spirit of Riko, and Penny's Fidough/Dachsbun line use `.genderRatio = MON_FEMALE`. The engine's gender helpers special-case this value, so every personality is female, including already saved individuals. Do not revert these entries to a random ratio: the user's real pets are all girls. No personality, save layout, species ID, or evolution trigger changes are needed for this correction.


## Guardian Penny evolution test

SPECIES_PENNY_GUARDIAN = 1601 is the blonde, ketchup-backed Penny form. Existing real species IDs are unchanged; SPECIES_EGG follows the new tail at 1602 and NUM_SPECIES follows that sentinel. Her dex identity remains NATIONAL_DEX_FIDOUGH. The female-only form uses Dachsbun's learnsets, Fairy typing, Well-Baked Body/Aroma Veil and Sweet Veil innate. Stats are 100/100/120/85/55/95 (HP/Attack/Defense/Speed/SpAttack/SpDefense).

ITEM_DADS_KEYS = 937 evolves base Fidough/Penny into Guardian Penny. ITEM_PIECE_OF_CHICKEN = 938 returns her to base Fidough/Penny. Both use the existing party-menu evolution-stone behavior, consume one item per use, and have custom 24x24 item icons. Play builds stock both items for 500 each at Goldenrod Department Store 4F's existing vitamin/evolution-item clerk, without fresh-save grants. CI #119 at commit 3d7b74d is a separate test ROM whose fresh saves receive five of each; existing saves do not automatically receive test items. The normal level-26 Dachsbun evolution remains. The Keys apply only to base Penny, not Dachsbun.

The approved blonde/ketchup concept was converted into indexed 4-bit battle art, a two-frame 32x64 menu icon, and a six-frame 192x32 follower strip. Palette index 0 is transparent and each PNG matches its 16-entry JASC palette. Follower order is down 0/1, up 2/3, left 4/5; the existing animation table mirrors left for right. Makefile uses frame-contiguous 4x4 tile conversion and explicit pokemon.o dependencies. Normal and shiny colors intentionally share the approved blonde design.

TrioParty_CheckPenny now recognizes base Penny, Dachsbun and Guardian Penny. Mom's confidence branch calls the shared check so her evolved form retains those scenes. No save-block layout or quest-variable changes. Source and asset validation do not replace CI compilation and emulator tests of forward/reverse evolution, follower directions, battle art, and save/reload.

## Mom's friend: reusable testing supplies

At the user's request, Mom's friend in New Bark's house is the ongoing test-item supply NPC. Her original dialogue is followed by an optional yes/no offer. Yes grants five Dad's Keys and five Pieces of Chicken; No grants nothing. The offer is repeatable on new and existing saves while she is present. New test items can be added to this offer rather than toggling starting-Bag grants or maintaining separate test/play ROMs. Preserve her existing object, visibility flags and finishing movement.

Each giveitem immediately checks VAR_RESULT for Bag-full failure. If the second item fails, any first item received stays in the Bag, and the player can make room and ask again; repeat refills are intentional, not a one-time reward. No persistent flags/variables or automatic grants are added. The normal Goldenrod 4F shop stock remains for gameplay acquisition. New art/mechanics still require a build; receiving/refilling existing test supplies does not.

## New Bark trivia pilot

A new permanent human NPC (LOCALID_NEWBARK_TRIVIA, object 16, existing FR Lass graphic) stands at (22,13), elevation 3, in the front yard to the right of the player's house. The tile and approaches are walkable; the door warp at (20,11), mailbox, and rival movement paths remain clear. The object explicitly calls NewBarkTown_EventScript_TrioTrivia in the included map script.

The optional pilot asks three yes/no questions: Riko is a Pomeranian (YES), Bijuu is a dachshund (NO), Penny loves chicken (YES). Wrong answers end the attempt with a friendly retry invitation. Three correct answers grant one ITEM_POTION, presented as a small Wawa. Successful quizzes and rewards are intentionally repeatable for this pilot. A full Bag gives a make-room/retry message; VAR_RESULT is checked immediately. Declining grants nothing. No persistent variables, flags, or save-layout changes were added. New and existing saves can use the NPC.

The new raw Pory block and assembly block match. To personalize questions later, edit both sources and the corresponding YES/NO branch checks. Source checks cover labels/references, 26-character text wrapping, event occupancy, and 18 script paths including all answer combinations, full Bag and decline. Placement and interaction still require emulator confirmation. CI #121 at f45669dc passed ROM compilation, artifact upload, all test steps and docs validation before this trivia change.


## Gym trivia and reusable elemental keepsakes

The user confirmed the Guardian Penny forward/reverse items and New Bark trivia pilot worked in the emulator. That confirmation predates this elemental/Gym-trivia batch.

Six elemental forms use the user's approved sheets. Fire Riko (1582), Electric Riko (1585), and Ghost Bijuu (1595) retain their existing IDs. New tail entries are Ice Bijuu (1602), Water Penny (1603), and Grass Penny (1604); SPECIES_EGG now follows at 1605. All six remain female-only. Penny's elemental forms keep Guardian Penny's stats and blonde/ketchup/key identity and return to Guardian Penny, not Fidough. The normal Fidough-to-Dachsbun and Keys/Chicken pair remain.

| Reusable item | ID | Forward / reverse pair |
| --- | --- | --- |
| Green Pepper | 939 | Riko / Fire Riko |
| Eel Sushi | 940 | Riko / Electric Riko |
| Frozen Fish | 941 | Bijuu / Ice Bijuu |
| Mouse Toy | 942 | Bijuu / Ghost Bijuu |
| Dog Bowl | 943 | Guardian Penny / Water Penny |
| Fetching Stick | 944 | Guardian Penny / Grass Penny |

Use each keepsake again on its matching elemental form to revert. These six items alone are exempted from consumption in ItemUseCB_EvolutionStone; ordinary evolution items, Keys, and Chicken retain consumption. Forms offer an elemental attack on evolution through level-zero learnset entries. An evolved girl must return to her matching base before using the other keepsake. No new starting-Bag grants were added.

Mom's friend's optional repeatable supply offer now grants five Keys, five Chicken, and one of each reusable keepsake, with an immediate Bag-full check after each grant. Previously received items remain if a later grant fails. All six keepsakes are also sold for 500 each at the existing Goldenrod Department Store 4F clerk.

Sixteen permanent Lass NPCs stand on checked walkable tiles near the Gym cities' Pokemon Centers. Each calls a label in data/scripts/trio_gym_trivia.inc, included explicitly by data/event_scripts.s. Seven questions use the user's personal answers; nine use Pokemon trivia. Correct answers give one locally useful keepsake, except Fuchsia's held Pecha Berry. Each city's prize is once per save, with friendly no-penalty wrong-answer retries and optional replays. Bag-full returns before setting the claim flag. The sixteen claim flags occupy 0x1044-0x1053 in the existing persistent flag array; FLAGS_COUNT and SaveBlock layouts are unchanged. Existing city scripts and visibility remain; no Pory source was modified for the new shared include.

This engine's map format uses an eleven-bit metatile ID (0x07FF), one collision bit (0x0800), and elevation in bits 12-15; primary metatiles occupy IDs 0-1023. Do not apply vanilla Emerald's ten-bit-ID/two-bit-collision assumptions when checking NPC placement.

The six approved sheets were converted to 64x64 battle sprites, 32x64 icons, 192x32 followers, and 24x24 item icons with indexed 4-bit palettes. Palette index zero is transparent; normal and shiny art intentionally share the approved colors. Source/asset checks are separate from compilation and emulator verification. This batch needs in-game forward/reverse, move offers, Bag retention, follower directions, quiz rewards/replays/full Bag, and save/reload checks.

## Penny quiz prizes include Guardian access

Pewter, Cerulean, Vermilion, and Cinnabar's quizzes now give one Dad's Keys as well as their Dog Bowl or Fetching Stick. Dialogue explains Keys first, elemental keepsake second. The existing prize flag records the Bowl/Stick; separate Keys flags 0x1054-0x1057 record successful Keys delivery. Each giveitem immediately checks VAR_RESULT. If only the first item fits, it remains claimed and the next correct answer delivers only the pending Keys. Existing saves with the original prize already claimed can answer again to receive their missing Keys. Fully completed replays grant nothing. No save-array/layout change or new persistent variable; the entire original source/map/header audit found these four slots unused. Mom's friend's repeatable supplies already include five Keys, and Goldenrod 4F already stocks Keys alongside both keepsakes. CI #124 at 8730f2c passed all jobs before this follow-up; the new reward flow still needs its own build and emulator checks.

## All-element rumor dialogue pass

Residents in all 16 Gym cities now speculate that Riko, Penny, and Bijuu could wield every Pokemon type. Thirty-two before/after Gym text entries plus two Goldenrod Rocket-takeover entries retain their previous directions, personality stories, and badge-gated match recollections, then add varied local rumors. The five existing raw Pory sources match their assembly text edits. Cinnabar coverage uses its permanent Pokemon Center Cooltrainer. The active Pewter Bugcatcher used a lowercase-c alias that bypassed the existing Badge09 branch; that alias now delegates to the existing badge-aware script. Apart from that dispatch repair, script commands, objects, visibility, flags, variables, rewards, and species are unchanged. Rumors are speculation; they do not promise that every type currently has a usable item evolution. The user confirmed Bijuu's new transformation items and a Gym-city quiz worked in the emulator. This does not confirm every girl's new follower, every quiz, or the Keys follow-up. Penny/Bijuu spirit bosses remain proposals, not implemented encounters; the existing Riko Spirit cave loading problem is still unresolved.

CI #125 built/uploaded its ROM but the first test shard failed the stale hidden-grotto ID fixture: an earlier test left Applin in gEnemyParty, while the assertion assumed an empty slot despite the stated requirement to leave the party untouched. The fixture now establishes a Clefairy sentinel, snapshots the entire enemy party, and asserts byte-for-byte preservation plus a FALSE result. The runtime grotto rejection code is unchanged. This is a stronger order-independent fixture, not a relaxed failure expectation.

## Penny and Bijuu Spirit home test encounters

The user approved both Spirit concepts and explicitly requested temporary test encounters outside Mom's house. SPECIES_PENNY_SPIRIT = 1605 (Steel/Fairy, Battle Armor) and SPECIES_BIJUU_SPIRIT = 1606 (Ghost/Psychic, Levitate) are separate female-only story entities; SPECIES_EGG now follows at 1607. Existing real species IDs are unchanged. They are not evolutions, starting-party grants, or ordinary trio-party-check members. Their approved art is registered under graphics/pokemon/penny_spirit and bijuu_spirit: 64x64 front/back, two-frame 32x64 icon, six-frame 192x32 follower, matching 16-entry palettes with transparent index zero. Normal/shiny colors intentionally match. Frame-contiguous follower conversion and pokemon.o dependencies include both species.

New Bark has a 16-object runtime budget. Two unused decorative Pidgey slots were repurposed for the requested test spirits, keeping the map at 16 objects; existing story objects, quiz, lights, warps, triggers, mailbox and rival paths remain. Penny stands at (18,14), Bijuu at (22,14), elevation 3, on walkable normal-behavior tiles in front of Mom's house. They are explicit species graphic objects, not human placeholders. The shared assembly include data/scripts/trio_home_spirit_trials.inc is included by data/event_scripts.s; the original Pory map source is unchanged because neither original map script was edited.

Both encounters are optional and repeatable on new/existing saves. PrepareTrioSpiritTrial validates the requested Spirit species and a non-egg party, then heals and creates one opponent two levels above the strongest non-egg party member (cap 100). Below party level 20 it uses gentler moves; early Bijuu holds Ring Target so fresh starters' Normal attacks can hit her Ghost type. Later Penny uses Iron Head/Play Rough/Baby-Doll Eyes/Protect, Bijuu Shadow Ball/Psybeam/Confuse Ray/Swift. No held healing items, recovery moves, catch rewards or quest flags. Winning plays a distinct affectionate message to Mom; decline does nothing, loss/escape invites retry, and scenes can be reread after another win.

BattleSetup_StartTrioSpiritTrial uses a dedicated end callback. It restores the prior no-catching flag, heals the party on victory/defeat/escape, and returns to the field script on all outcomes without whiteout or money loss. It does not change the existing Riko battles or cave. Keep this callback separate from normal scripted-wild battles; trailing script cleanup alone is insufficient after whiteout. Future story placement, keepsakes and progression gates still need implementation; these test objects do not complete those quests.

CI #126 compiled/uploaded its ROM and passed docs, but test compilation failed because the grotto sentinel called the old eight-argument CreateMon signature. That single call now uses this engine's five-argument CreateMon with OTID_STRUCT_PLAYER_ID. Runtime grotto code stays unchanged. Asset/source validation and preparation tests do not replace emulator checks of the home NPCs, victory scenes, defeat/escape return, animations and following behavior.


## Spirit scaling, indexed alpha repair, and milestone arenas

The user confirmed both home Spirit fights and asked for stronger scaling plus milestone-gated story sightings. PrepareTrioSpiritTrial now uses highest non-egg party level + 5 + min(highest level / 10, 5), capped at MAX_LEVEL (100). This is +5 below level 10, +6 at 10, +7 at 20, +8 at 30, +9 at 40, and +10 from 50 onward. Near level 100 the cap necessarily reduces that advantage. Existing early/later move sets, healing, catch restrictions and safe defeat/escape callback remain. Scaling is recalculated on every attempt for both home and story battles.

The transparent holes were an indexed-conversion overflow: opaque dark pixels quantized into a padded palette slot 15, then adding one to reserve transparency produced index 16, which a 4-bit PNG truncated to transparent zero. Correct quantization chooses only the 15 intended visible colors before adding one, sets zero only where the source alpha mask is empty, and asserts both index range and exact alpha-mask equality before saving. All eight Penny/Bijuu Spirit PNGs were regenerated, restoring 1,470 opaque pixels without introducing any new transparent pixels or changing approved designs/palettes. Pixel-for-pixel decoding of their generated native GBA .4bpp tiles matched the indexed PNGs, including frame-contiguous overworld order.

CheckTrioSpiritMilestone uses the actual persistent completion flags: Penny requires every Johto Badge (FLAG_BADGE01_GET through FLAG_BADGE08_GET); Bijuu requires FLAG_IS_CHAMPION, set by the active Hall of Fame script. The story include data/scripts/trio_story_spirit_trials.inc is explicitly included. Blackthorn's transition calls Penny visibility before object spawning; Ecruteak's transition calls Bijuu visibility before its original time callback. The interaction checks the milestone again. Existing saves refresh visibility on city entry, so they need no new-game flag initialization or earlier clue acceptance.

Penny stands at (30,40), elevation 3, north of Blackthorn's Pokemon Center. Bijuu stands at (24,16), elevation 3, east/south of Burned Tower's entrance in Ecruteak. Their exact tiles and multiple adjacent approaches have normal walkable behavior. Objects, warps, triggers and signs do not overlap the placements. Source inspection found five and six nearby object candidates respectively, within the engine's 16-object viewport budget. These outdoor maps already load in ordinary play; the new placements still need independent emulator verification. Original NPCs, movement paths, warps and existing story progression remain.

The permanent New Bark Fat Man keeps his original dialogue and then supplies eligible, unfinished sighting clues, naming the city and landmark and wondering how the girl can be seen elsewhere when she is right here. His early state-2 dialogue remains unchanged. Edited New Bark/Ecruteak raw Pory blocks and assembly calls match. The clues can be reread until the corresponding story fight is won and are not prerequisites for visiting the arena.

Four unused persistent flags occupy 0x1058-0x105B: story visibility for each Spirit and separate story completion for each. All definitions/raw numeric uses were audited before allocation; CUSTOM_FLAGS_END was advanced without changing FLAGS_COUNT or SaveBlock layouts. Completion is set only after B_OUTCOME_WON. Defeat/escape allow retries; after winning, interaction rereads the emotional scene without another battle. No item or keepsake reward is implemented yet. The repeatable home trials never set these story completion flags and remain available without milestones. Riko's Spirit encounter and unresolved cave are unchanged.

CI #127 at 404c078 passed the full workflow before this follow-up. Local preparation tests cover empty/egg-only rejection, strongest/fainted-party scaling and healing, early move/held-item behavior, female identity, egg exclusion, the level cap, the entire 5-10 advantage curve, every individual missing Johto Badge, the League gate and unsupported species. Source/build/test checks do not establish emulator confirmation of the repaired sprite alpha or new story placements, milestone visibility, save/reload and dialogue replay.

Follow-up local validation: ROM compilation, all five focused Spirit tests, native tile decoding and the CI docs/SUMMARY validator passed. An additional optional docs parser suite passed 45/46 tests; its Gracidea location wording expectation ("after showing Shaymin") already differs from unchanged HEAD parser wording ("by showing Shaymin"). This pre-existing unrelated docs fixture was not changed. Full CI for the follow-up commit is separate.


## Automatic milestone sighting calls

The user asked to make both Spirit discoveries clear without a return trip to talk to the New Bark neighbor. A one-time PokeNav sighting call now runs on the next Blackthorn visit after all eight Johto Badges, and on the next outdoor New Bark visit after becoming Champion (the normal post-League return). Calls name Penny's Blackthorn Pokemon Center landmark and Bijuu's Ecruteak Burned Tower landmark, with the same paradoxical sighting clues the neighbor can repeat.

Each city's transition recomputes VAR_TEMP_9 as an explicit map-local pending latch; its original on-frame scripts run first, then the sighting call. Thus Blackthorn's original Elm call and New Bark's post-League Elm/rival scripts keep priority and progression. VAR_TEMP_9 was unused in both maps before this change. The shared helper checks the actual milestone and skips a completed Spirit or already-delivered automatic clue. The call clears its latch, locks all objects, waits for its PokeNav message, records delivery, releases all and ends. No movement, new object, arena, reward, forced fight, or saved quest variable was added.

Audited unused persistent flags 0x105C/0x105D record Penny/Bijuu automatic clue delivery; CUSTOM_FLAGS_END advances without changing flag-array/save layout. Existing saves already past the milestones receive an undelivered clue on their next corresponding city entry. Home trial wins still do not suppress story clues. New Bark raw Pory source and assembly dispatch/transition calls remain synchronized. The NPC clues remain optional and repeatable, and the Spirit arenas remain directly accessible after their milestones. This follow-up needs compilation and emulator checks of automatic call order, one-time delivery, old saves and free movement afterward.

Automatic-call follow-up validation: local ROM compilation and CI docs/SUMMARY validation passed. Source checks confirmed the edited New Bark Pory blocks match assembly, original map-script priority is preserved, the pending latch clears before either call, delivery is marked after the message, both calls release all objects, labels are unique and new text fits the established wrapping. Emulator verification remains pending.


## Spirit keepsakes, sister memories, scrapbook, and pom party

The user requested all four features. Appended Key Items 945-948 are ITEM_RIKOS_SPARK, ITEM_PENNYS_SHIELD, ITEM_BIJUUS_LIGHT, and ITEM_MOMS_SCRAPBOOK. Each is importance=1, price=0, ITEM_USE_FIELD with ItemUseOutOfBattle_TrioMemory, and uses existing registered icon/palette art. The common standard field-item callback supports Bag and registered use, copies the selected item into VAR_0x8004, starts EventScript_TrioMemoryItem, and destroys its task. The script locks/releases all objects, never removes the item, and closes cleanly on Exit/B. MULTI_TRIO_SCRAPBOOK=136 is registered with Our journey / Sister moments / Spirit letters / Exit.

Shared data/scripts/trio_memories.inc is explicitly included. Keepsakes have separate delivered flags from victories. giveitem immediately checks VAR_RESULT; delivery is recorded only after success. The shared helpers explicitly return TRUE for delivered/ineligible and FALSE after a Bag-full message. Mom's interaction retains all original dialogue, Penny progression, family callback and healing. Pending gifts and the scrapbook eligibility check run immediately after lock/faceplayer, before opening-story dispatch or healing. A full Bag stops that visit's delivery batch and leaves each unreceived gift pending. Book receipt is also once per successful grant. Existing saves with prior victories can collect missing gifts at Mom or Penny/Bijuu's story spirit; no forced refight or absent-party requirement applies to pending rewards.

Riko's final victory/capture script uses the existing FLAG_DEFEATED_SUICUNE and now calls the reward helper before the unchanged original cleanup/removal. Her cave loading and battle setup are not repaired or otherwise changed. Penny/Bijuu story wins already record their separate completion flags and now call their reward helpers after the personal scene. Home wins record separate testing markers and also allow keepsake delivery; these markers do not complete the milestone story quests, suppress their sighting calls, or bypass story eligibility. A gift earned at home is not duplicated by a later story win. Home full-Bag pending gifts can be collected at Mom. The corresponding scrapbook letters are available after either home or story victory, deliberately allowing immediate testing.

Mom's Scrapbook reads existing milestone flags for its journey pages, witnessed flags for sister/party pages, and real Spirit/home victories for letters. It needs no saved progression variable, item consumption or current party to read remembered pages. The Cherrygrove research boy keeps his original book, rewards and chapter states; his existing reading routine now offers the companion Mom scrapbook after its original pages. Both raw Pory and assembly sources contain the same added call. No old scene or quest is replaced.

Three new Lass objects at (5,5) stand in AzaleaTown_PokemonCenter, GoldenrodCity_PokemonCenter, and OlivineCity_PokemonCenter. Their short optional sister scenes require Badge01/02/04 respectively and all three existing shared party-family checks, allowing the approved forms. First viewing records a page after its dialogue; optional replays do not duplicate it. Their exact tiles and all four approaches have normal walkable behavior, no original object/warp/trigger overlaps, and total template counts of 6/7/5. Original Center services remain.

GoldenrodCity_House2 (existing PP-explanation house, city doorway 48,15) now has four Riko/Pom sprites at the corners (1,4), (3,4), (3,6), (1,6). Four clockwise phased engine walk-sequence types with range 2 share this exact eight-tile ring. Every ring tile has normal walkable behavior, and the existing two residents, furniture and doorway are clear. Six templates total leave ample runtime object room. MoveNextDirectionInSequence uses fast steps only for Riko graphics in this exact map; existing collision handling, pauses, phase correction and normal movement elsewhere remain. The first entry uses VAR_TEMP_A as a map-local latch to play a one-time welcome and record the party page; it resets on every entry and does not affect persistent story vars. The original host repeats "Ain't no party like a pom party!" after his retained PP explanation, and the woman's advice is unchanged. Interacting with a Pom plays its cry and releases normally.

Audited persistent allocations 0x105E-0x1067 cover three delivered keepsakes, book receipt, three sister pages, party welcome, and two home testing wins. CUSTOM_FLAGS_END advances; FLAGS_COUNT and SaveBlock layouts do not change. See docs/trio_memories_and_pom_party.md for locations, reward/page semantics, and the outstanding emulator checklist. Source checks and a build do not establish runtime confirmation of Bag/registered UI, full-Bag recovery, new Center NPCs or the party loop.

Memory/party batch validation: the final local ROM compiled successfully; all 16 existing Bag tests and all five Spirit preparation/milestone tests passed in the headless emulator. The CI docs/SUMMARY validator passed. Source checks covered unique new labels, 26-character/two-row text wrapping, immediate giveitem result checks before delivered flags, item non-consumption, raw Pory/assembly agreement, audited flag allocations, unchanged original map events/services, walkable route/approaches and object budgets. These checks do not establish emulator confirmation of the new item UI, reward retry scenes, scrapbook navigation, sister interactions, or visible Pom circle. Full CI for the new commit is separate.


## Temporary one-HP home Spirit shortcut

For quick keepsake-grant testing with starters, the user explicitly requested temporary 1-HP home opponents until the home objects are retired. Both New Bark home scripts now call SetTrioSpiritTrialTestHP only after successful normal preparation and explain the shortcut in their ready dialogue. The special changes current HP to 1 only for Penny/Bijuu Spirit species when the current map is New Bark; max HP, stats, moves and scaled level remain. Story scripts never call it, and its map guard prevents weakening the Blackthorn/Ecruteak fights. PrepareTrioSpiritTrial has no sticky test state; later normal fights remain full-health. Remove this shortcut along with the home test objects when requested. A focused regression checks both Spirit species, unchanged max HP, normal re-preparation, a story map and a non-Spirit enemy. Source/compile/tests still need to be recorded for this last steering change.

Final steering validation: the 1-HP local ROM compiled, all six Spirit tests (including the new map/species/maximum-HP/isolation regression) passed, and docs validation passed. CI #129 passed fully for the prior 4c8bb44 head. For quick testing, either home Spirit win now also qualifies for Mom's one-time scrapbook gift before Badge01; the normal first-Badge source remains and pages still follow actual milestone/seen/victory flags. The changed script was recompiled before publication. Full CI and user emulator checks for this batch remain separate.


## Mom scrapbook delivery control-flow repair

User testing confirmed home Spirit keepsakes were delivered but Mom's resting dialogue never offered the book. PlayersHouse_1F_EventScript_MomHealsParty jumps to PlayersHouse_1F_EventScript_HealParty, which releases and ends instead of returning; the previous TrioMemories_Mom call after that heal was unreachable. The single rewards call now runs at the active New Bark Mom entry before story-flag branches. This also supports pre-adventure home-test winners without changing story flags or healing. Existing victory/delivery flags and full-Bag retry behavior remain. Source checks confirm one reachable call and no unrelated command changes; ROM CI and emulator verification of this repair are pending.


## New Bark Spirit test retirement

The user reports the new features now work as intended, including Mom's scrapbook after its control-flow fix. The two New Bark test Spirits are retired: original decorative Pidgey templates are restored in their existing slots so later local object IDs do not shift. Their interaction/offer/shortcut scripts are removed; data/scripts/trio_home_spirit_trials.inc retains shared decline/no-party/retry handlers, ready text, and Penny/Bijuu victory letters used by story encounters and memories. SetTrioSpiritTrialTestHP is removed from C, the header, and the special table. Its obsolete test is replaced with full-health/retry checks for both story arenas. Keep existing HOME_WIN flags and delivery/page checks reserved and readable so earned rewards on older saves remain valid. Story locations, milestones, scaling and safe battle returns remain. Source checks passed; cleanup CI and updated-ROM verification are pending.


## Kanto memories, Champion picnic, and checklist

The user requested a mix of automatic and offered Kanto sister scenes plus the Champion family picnic and scrapbook checklist. The new code is appended to data/scripts/trio_memories.inc, already included by data/event_scripts.s. Cerulean/Vermilion city transitions prepare an explicitly reset VAR_TEMP_A latch (unused in both existing map scripts); new on-frame tables play a one-time narrated scene after Champion status with the trio. Vermilion leaves the latch clear during Suicune state 3. Both existing city NPCs offer yes/no replay/catch-up after their original dialogue. Celadon's existing Lass offers its optional scene, retaining both Badge branches. No objects, coordinate events, movement, warps or art were added.

Mom's entry now calls TrioChampionPicnic_Offer immediately after TrioMemories_Mom, before original story/healing dispatch. It requires Champion status and all shared trio form checks; decline/missing girls remain eligible. The vignette and Scott letter play before the once-only seen flag is set. Our journey reads the recorded Scott letter with no party requirement.

MULTI_TRIO_SCRAPBOOK retains its ID; Memory checklist is added before Exit, with selection 3 dispatch. It reads actual milestone/scene/Spirit flags, including old HOME_WIN letter eligibility, and gives saved/waiting hints without changing progress. Sister pages add the three Kanto scenes. Existing pages and book delivery remain.

Unused flags 0x1068-0x106B are allocated to Cerulean, Vermilion, Celadon and the picnic; CUSTOM_FLAGS_END advances while FLAGS_COUNT and SaveBlock layout stay unchanged. Current source/header/map/script audit covered 3,602 files, including a retried transient map read. Matching decimal 4200/4201 values were unrelated weight and experience-scaling table data, not flag uses. Scoped guidance checks found no additional AGENTS.md for the edited paths. Source-flow validation passed 26 scenarios (missing trio, eligible/repeated entries, Suicune priority, declined/offered scenes, replay, Champion gate, one-time picnic, parent lock preservation, PC-independent letter reads and historical home-letter checklist). New references/labels and 26-character/two-row string wrapping were checked. CI and interactive emulator checks remain pending; do not represent source simulation as emulator testing.


## Trio Camp and family statistics

Trio Camp uses NewBarkTown_House1, the existing southwest house in New Bark (outdoor doorway 4,21). The original daughter offers the camp menu after her existing dialogue; both residents, the warp, and the second bookshelf remain. A transition callback uses the established party-family helpers to show each girl's base overworld sprite only when her family is present. Three girls and three toy baskets are appended after the two original residents (8 objects total); Penny is local object 5. Walkable bounded wander routes are Riko x1-3,y3; Bijuu x2,y4-6; Penny x7-9,y7. The back-left shelf at 9,1 opens the stats board. No new art, layout or warp is added.

Interactions offer petting, a favorite, and a repeatable game. Riko plays three rounds of bark counting. Bijuu's toy is hidden in one of three physical floor baskets with a directional clue. Penny's two-turn finding game uses camp prop keys, not the actual Dad's Keys item. Fetch feedback uses in-place animation rather than a forced path through the player. Wrong choices allow gentle retry; starting another game or leaving cancels any unfinished finding game. VAR_TEMP_B/C/D/E are camp-local game/answer/round/girl state and transition explicitly resets the game. A completed game increments exactly once; baskets become ordinary toys afterward. Optional favorites explicitly consume one Chicky Fil-A (Oran), Bijuu's Springs (Cheri), or Penny's Pup Cup (Pecha) after yes/no confirmation, requiring successful RemoveBagItem; missing or declined favorites consume/count nothing. Reusable form items and keepsakes are never used for these offers.

Rest uses the existing returning Common_EventScript_OutOfCenterPartyHeal, then shows an early/midgame/Champion family vignette only with all three girls. The first full-trio rest records FLAG_TRIO_CAMP_MEMORY, readable later through Sister moments even if the girls are in the PC; the checklist also supplies its southwest-house hint. Existing book eligibility remains first Badge or a historical home-test win.

Statistics use the ten previously unused encrypted gameStats slots 54-63: Wawa S/M/L, Chicky Fil-A, Springs, Pup Cups, completed personal form swaps, camp visits, completed games, and petting sessions. NUM_USED_GAME_STATS increases to 64 while NUM_GAME_STATS stays 64; SaveBlock layouts do not change. Critical migration: older unused slots were never initialized by SetGameStat and may decrypt as garbage. TrioCamp_EnsureStatsInitialized clears only 54-63 once, under FLAG_TRIO_CAMP_STATS_READY, before any custom read/increment. Existing steps/battles/captures/home-rest/Center/evolution totals remain. New item/activity counters start with this version and cannot reconstruct earlier uses. Counters use the engine's 24-bit saturation and normal encryption-key rotation.

Medicine hooks count successful out-of-battle Bag application and player-side battle HP/status application, not failed/probed/canceled use, selling, tossing, or held-item procs. Camp favorites count actual consumption too. Personal transformations count exact before/after/item triples at the committed evolution scene, including returns; canceled scenes and unrelated evolutions do not count. Form changes are one combined total, not separate per-item counters. Do not claim held-item consumption is tracked.

Current source/header/map/script audit covered 3,582 files and retried one transient map read: flags 0x106C-0x1070 and raw equivalents 4204-4208 were free, and no existing numeric game-stat use occupied 54-63. FLAGS_COUNT and save-array sizes stay fixed. Menus 137-139 and five specials are registered; data/scripts/trio_camp.inc is included explicitly. Seven host tests against actual helper C with stubbed engine APIs passed, including old encrypted-slot migration, preservation, saturation/rekey, exact transformation pairs, consumable validation and safe formatting. Fifty script-flow scenarios plus label/reference, conservative text wrapping, floor/route and original-warp checks passed. Host/source simulation does not replace the ROM CI tests or interactive emulator verification of roaming, lock release, cries, Bag/battle hooks, and save/reload.

## Route 31 authoring repair after camp CI

CI #136 finished installing the unchanged ARM toolchain after a slow 110 MB download (11m38s), then failed before ROM compilation: Route31/scripts.pory contained bare assembly instead of Poryscript syntax. The repaired authoring file wraps the complete current scripts.inc in the documented raw backtick block. This preserves every current label, command, movement, expert interaction, Bijuu chase and text; copying the older .pory body alone would lose assembly-only content. The compiled .inc is unchanged. A scan of all 231 .pory files found Route31 was the only file beginning with an unwrapped assembly label; all reads succeeded. Raw content is checked equal to current assembly and contains no internal backticks. No toolchain or build-workflow change is introduced. Rebuild CI remains separate from these source checks.


## Goldenrod festival and temporary quick testing

The Girls' Day Out is a separate GoldenrodFestival map appended to gMapGroup_IndoorGoldenrod, sharing National Park scenery but no original park scripts/wild encounter table. Its Center guide is at (9,5). After four Johto Badges and the full trio, enter for Riko's three visual imitation rounds, Bijuu's two-witness/basket mystery, Penny's three physical course markers with supportive choices, two snack battles, Scott's friendly sunset battle and a picnic/letter after either first win or first loss. Virtual ribbon certificates are displayed at the host and Camp shelf; the picnic appears in scrapbook Sister moments and checklist. See docs/trio_festival.md for locations and the runtime test plan.

TRIO_FESTIVAL_TEST_MODE is temporarily 1 at the user's explicit request: new saves have four Badge flags and all three girls level 30; existing saves are untouched. The outdoor New Bark Fat Man offers a shuttle to Goldenrod Center. Host Exit offers testing tools for return home and a confirmed festival-only reset. Disable the config switch after testing; it restores normal starts and removes test prompts without removing the festival. Badge flags alone do not mean original story events/rewards are finished; treat these new saves as testing saves.

New persistent flags 0x1071-0x107A and formerly unused trainer IDs 1159-1161 fit unchanged save arrays. The separate map is appended, so earlier map IDs remain stable. Source audits found no conflicting uses. New trainer authoring names resolve to SPECIES_PENNY_GUARDIAN, SPECIES_BIJUU_PSYCHIC and SPECIES_RIKO_WING; preserve trainer counts and original rival/fisherman Scott entries. Festival friendly returns require both the exact map and exact trainer ID, heal and resume after any battle outcome without global restriction flags. MAP_GROUP/MAP_NUM expect the MAP_ prefixed constant in this engine.

Ten source-flow/geometry regression groups pass in tools/festival/validate_festival.py. They check all NPC approaches, conservative viewport budget, cancellation/retry, clue order, supportive course branches, win/loss picnic, replay and isolated reset. These checks do not establish emulator confirmation. ROM/CI and rendered game testing must be reported separately. Earlier Trio Camp linking failure was repaired with VAR_LAST_TALKED, which applymovement resolves through VarGet; LOCALID_LAST_TALKED does not exist.

Local festival ROM compilation succeeded. Targeted headless engine checks passed: 41 pass plus 7 expected runner self-test failures, including the new actual NewGameInitData badge/party test. Ten festival source-flow/geometry groups and inclusive docs validation passed. Rendered festival playtesting and remote CI remain separate.

Festival shuttle runtime repair: TRUE is defined in C but not in event-script CPP; using it in #if silently removed the shuttle and host test prompts despite giving the test party/badges. Use numeric 1/0 for TRIO_FESTIVAL_TEST_MODE. The regression validator now runs real CPP with production includes and checks enabled/disabled shuttle and host branches. Inspect compiled ROM bytecode as well as source-flow checks.

Festival snack custody crash: user confirmed shuttle works, then Greedent appeared unknown and blue-screened on battle entry. P_FAMILY_SKWOVET was FALSE, excluding Skwovet/Greedent species stats, battle sprites/palettes and overworld data despite existing numeric species IDs. Enable that family for the festival boss. Never add a trainer/object species by checking its constant alone: check its enabled family and actual gSpeciesInfo entry. test/trio_festival.c covers all festival species' required battle/overworld data plus healthy level-29 Greedent creation. ROM compilation, headless tests and user retry must be reported separately.

## Festival normal-play release

At the user's request after playtesting, TRIO_FESTIVAL_TEST_MODE is now 0: no free festival Badges, level-30/full-trio start, shuttle, or host reset/test tools. Normal level-5 Riko/Penny opening and Route 31 Bijuu recruitment are restored; approved Mega Ring/Bondstone starter equipment is unchanged. Festival, Camp, scrapbook and Greedent fix remain. Existing saves are not rewritten; old test saves keep granted levels/Badges. The source preprocessor regression explicitly forces both 1 and 0, so it works in the normal-play build. Actual NewGameInitData regression checks both starting species and all four absent Badge flags when disabled. Publish the playable build on the existing test branch; keep draft PR unmerged unless merging is specifically requested.

## Evolving Camp playroom

At the user's request, Camp now gains six gifts from existing achievements: Badge01 Penny cushion, Badge03 Riko chicky plush and travel photo, Badge04 Bijuu toy and soft mat, festival picnic cushion, Penny Spirit guardian cushion, and Bijuu Spirit moon plush. Badge08 adds a League wall display; Champion adds a second display and commentary. Host Room keepsakes reads earned stories. Objects 9-14 append after the original eight; the three roaming paths, host, shelf and warp are unchanged. All fourteen templates plus player/follower fit sixteen objects. Existing saves receive earned decor next visit, even without the girls currently in the party.

TrioCamp_UpdateKeepsakes recomputes hide flags 0x107B-0x1080 only; actual achievements and old home-test wins are the source of truth. No progress, inventory, counters or save sizes are changed. The special is appended after existing Camp specials to preserve older IDs. MAP_SCRIPT_ON_LOAD restores original sites then applies visual upgrades, while ON_TRANSITION recomputes object visibility before spawning. One mat-center metatile is appended at House/Lab 0x4D8; all original metatiles/attributes remain byte-identical. It uses existing Johto Building tiles; no new palette is loaded. This engine has twelve tile entries (three layers) per metatile, 640 primary graphic tiles, 1024 primary metatiles, collision mask 0x0800 and elevation mask 0xF000. Do not treat bit 10 (secondary metatile selector) as collision. Other houses are unaffected. The original blue table stays; a trial red table failed visual consistency and was removed before publication.

Six source/decoded geometry groups cover sixteen visual combinations, all gift approaches, original object/warp stability, roaming, collision/elevation preservation, repeat/reset load, menu-return/lock release and wrapped text. Actual helper tests check independent milestones, zeroed old hide flags, legacy Spirit victories and unchanged progress/counters. Local ROM and targeted engine suites must be reported separately from user rendering/save/reload confirmation. See docs/trio_camp_keepsakes.md. Festival test mode remains 0.

Final local evolving-Camp verification: ROM compiled; targeted suite 24 pass plus 7 expected runner self-test failures (31 total), including keepsakes/Camp/festival/new-game; six Camp and eleven festival source/preprocessor groups plus docs validation pass. The flag audit scanned 6,938 files without conflicting numeric uses. Decoded asset previews were inspected. Remote CI and rendered emulator/save-reload are separate checks.


## Scott's optional gym-city moments

Four permanent Scott NPCs append to Azalea (46,16), Ecruteak (29,23), Olivine (37,51), and Blackthorn (25,50), clear of original rival viewports and events. Shared scripts in data/scripts/trio_scott_moments.inc use actual Badge02/04/06/08 gates: Bugsy proud check-in, Morty garden tea date, Jasmine seaside snack, Clair pre-League encouragement. Badge08 is awarded in DragonsDen_Shrine, not the initial Clair defeat. No party or time gate: the user permits family dialogue to assume the girls are present.

Accepted scenes set independent flags 0x1081-0x1084 only after their dialogue. Declines, waiting, replays and scrapbook/checklist reads do not mark progress; existing saves can catch up in any order. Mom's Scrapbook appends Scott moments at index 4, leaving the previous four entries stable and moving Exit to 5. Helpers return into the caller's lock/menu state; only direct NPC interactions lock/release. No save-array, reward, battle, warp or movement changes. Original map scripts and Pory files need no changes because object scripts reference the globally included file. See docs/trio_scott_moments.md. Six actual-script/decoded geometry groups pass, including all 24 orders, 16 replay/checklist combinations, conservative template budgets and approach reachability. Rendered scenes and save/reload still need user testing.


## Route 37 snack chase

After actual Badge03, southern path row34 x12-15 triggers a single Greedent theft (or talk to object13 at14,33). It runs away to object14 at17,19; talking there flees to object15 at32,23 beside the Berry tree. Level22 trainer1162 replaces unused298 without expanding trainer counts. Only one thief appears, derived on transition from state0-4 and hideflags1085-1087. Original twelve objects, trainers, Ecruteak entry triggers, connections and time callbacks stay intact. Pory's high-level Route37Sign calls TrioSnack_Hint; don't edit only its generated assembly.

VAR_TRIO_SNACK_CHASE_STATE4125 and VAR_TRIO_SNACK_STOLEN_ITEM4126 fit existing save arrays. Actual helpers remove one Bag Berry (prefer Oran/Chicky) and escrow its exact ID, or use an inventory-free picnic snack if none. Never remove held, key, medicine or evolution items. State3 means battle won but item return pending: AddBagItem failure retains the ID and state; retry doesn't battle again. Completion clears escrow only after success and appears in scrapbook Sister moments/checklist. Repeated helper calls cannot duplicate or re-steal. Friendly battle callback is guarded by exact Route37 map group/number and trainer1162, heals/resumes after defeat, and changes no global restriction flags. Entry sets scratch VAR_FACING north before escape so a stale interaction-facing value cannot select a path through the player. Talk from north uses an alternate safe movement path.

Six actual-script/decoded route groups and five actual engine helper tests cover source branches, real item custody/full-stack retry, badge gate, independent restore, visibility and map/trainer guard. Targeted suite passed22 plus7 expected runner self-test failures; ROM compiled. All new inventory fields are persistent and source-audited; no startup test tools added. See docs/trio_snack_chase.md. Rendered chase/movement/battle/menu and save/reload confirmation remains separate.


## Mandatory escalating Greedent gang (supersedes friendly one-time chase rules)

The user requested proper losses and a mandatory escalating gag. Keep the first Route37 pursuit: entry after Badge03 steals once and starts state1, with hiding objects14/15; the northern y12 x16-19 gate covers every walkable exit tile for states1 and2, forcing the battle before Ecruteak's original y11 event. Old grove interaction also battles without a yes/no prompt. Later automatic route-entry ambushes are Route38/Badge04 twoLv35, Route42/Badge06 threeLv48, Route44/Badge07 fourLv62, Route26/Badge08 fiveLv78, Route6/Champion sixLv100. First thief staysLv22. Complete/reclaim waves in order; old completed first chase migrates as wave1. Final teams use trained EVs, perfect IVs and held items. No test starts added.

The former TrioSnack_IsFriendlyBattle heal/resume shortcut is removed. Every gang fight uses normal trainer blackout/money loss, with no free win heal or yes/no choice. Custody is recorded before battle so a blackout that skips the tail leaves the same item recoverable on retry. VAR_TRIO_GANG_WINS4127, ACTIVE_WAVE4128 and PHASE4129 supplement preserved first-chase state4125/item4126. First theft is on-frame value8; later waves1-6, return-pending7. Previously unused route VAR_TEMP_B is prepared only on transition, cleared before scripts, and shared table is wired in all six maps. Preserve time callbacks and Pory/raw authoring.

First completed page stays in Sister moments; six completed waves add the cartel memory. Checklist gives next route/gate. Won/full Bag can be reclaimed on route reentry or Mom, without another battle; only successful item return advances wave wins. Existing active/return-pending/complete first-chase saves retain custody/state meanings.

IMPORTANT trainer1154-1158 are unused IDs but their ordinary flag addresses982-986 are reclaimed Vajra/Lati puzzle flags. Gang progression is isolated: TrioGang_WaveForTrainer identifies its six IDs, flag reads derive from gang wins, normal flag setters/clearers and SetBattledTrainersFlags skip them. Don't set or clear the aliases or remove those guards. Trainer counts/save arrays are unchanged. Actual engine tests cover raw puzzle flags before/after gang flag APIs. The headless runner replaces gTrainers with mocked trainer fixtures, so check production parties through tools/snack/validate_rom_parties.py using ARM ABI offsets from party_layout.c. It decodes the real ROM table for sizes/levels/IVs/EVs/items. A GetTrainerPartyFromId headless test cannot verify production parties.

See docs/trio_snack_chase.md and tools/snack/validate_gang.py. Rendered entry/chase, normal defeat, save/reload, all six ambushes and final fight still need user testing. The Goldenrod festival remains a separate friendly exhibition.

Final local verification: production ROM compiled; 27 targeted engine checks passed plus 7 expected runner self-test failures (34 total). Production-ROM decoding confirmed all six party sizes/levels and the final team IVs, EVs and held items. Six gang and six legacy chase source/geometry groups pass, alongside existing Scott/Camp/festival and docs checks. Remote CI and interactive emulator confirmation remain separate.

## Optional cartel battles supersede the mandatory exit/ambush rules

At the user's request, every route stays open. Route entry only mugs once and reveals a hideout; no entry battle. Remove the eight Route37 northern interception coordinates/FirstGate script. First pursuit remains optional; grove interaction now asks Yes/No. Routes38/42/44/26/6 append one stationary Greedent (IDs11/20/28/14/11), respectively at (17,26)/(10,12)/(7,12)/(25,13)/(34,7). All are TRAINER_TYPE_NONE with no movement or sight; only direct interaction plus Yes battles. Shared visibility flag1088 is free within unchanged arrays and recomputed on transition. Pending phase1 schedules no on-frame event on any route, including after normal blackout; first state1/2 similarly stays quiet. Old pending mandatory-build saves get the side hideout automatically. Normal losses, exact item escrow, full-Bag/Mom recovery, sequential teams and puzzle flag guards remain. Leaving the cartel unfinished pauses only its later waves and memory, never main-game/arena progression. tools/snack/validate_gang.py includes entry/no-battle, optional decline/loss/retry, decoded placement and connected-path/object-budget checks.

Optional-battle local verification: ROM compiled successfully; targeted engine suite passed 28 checks plus 7 expected runner self-test failures (35 total). Seven gang and six chase source/geometry groups, existing Scott/Camp/festival groups, docs validation and diff checks passed. Actual production-ROM party decoding still confirms all six teams and the final IVs/EVs/items. CI and rendered entry/hideout/blackout/save-reload playtests remain separate.

## Spirit Rift: Echo Woods pilot

The first Rift chapter enters through Goldenrod Center's appended old man (10,6) after the festival picnic and with the trio. New TrioEchoWoods map/group37 in IndoorGoldenrod and layout1030 append without changing original IDs. The 24x30 forest uses Johto General/NationalPark tilesets; no old cave callbacks, weather, connections, trainer IDs or startup test tools. Three physical echo pads (10,26)/(10,21)/(10,13) open the two-wide x11-12 passages at rows24-25/16-17/8-9. MAP_SCRIPT_ON_LOAD reconstructs opened paths from persistent state. Exit NPC (9,27) and bottom south-arrow warps (11-12,28) return to Goldenrod. Warp events require actual warp tile behavior: plain ground is insufficient; 0x1DE uses the existing National Park south-arrow behavior0x65.

VAR_TRIO_RIFT_RIKO_STATE412A was free under a baseline whole-repository raw/numeric search and fits unchanged arrays. States0-3 count opened paths;4 records victory/gift pending;5 marks successful Wand grant. Victory enables a scrapbook Sister moment independently of Bag capacity. A full Bag allows reward retry without party requirement or rebattle. Forms add dialogue, never forced mutation or evolution. Riko Spirit is a separate guardian object/species, never ordinary party Riko.

PrepareTrioSpiritTrial now explicitly accepts SPECIES_RIKO_SPIRIT for Rift requests, with Flamethrower/Snarl/Swift/Protect and existing strongest-party scaling. Its shared callback preserves prior catching restrictions and heals/returns after any outcome without blackout/money loss. Legacy Riko cave scripts still use their original setup; their loading issue is unresolved. Squirrel normal losses are untouched. Mirror House, Lantern Trail, shared sanctuary and Scott's arena remain designs, not implemented maps. See docs/trio_spirit_rift.md.

Seven source/decoded geometry regression groups execute actual Rift script commands with engine stubs, including gate reconstruction, declines, absent girls, losses/escape, full-Bag/repeated claims, form dialogue, original map/layout stability, and south-arrow exit tiles. Guardian setup has two actual engine tests in test/trio_rift.c. Source simulation and decoded asset preview are separate from interactive rendering, save/reload and input playtesting.

Echo Woods local verification: production ROM compiled; targeted engine suite across four shards reported57 passes and21 expected runner self-test failures, zero unexpected failures (support checks repeat across shards). Both new Rift tests passed. Seven Rift, eleven festival, six Camp, six Scott, seven gang and six chase source/geometry groups plus docs validation and diff checks passed. Decoded terrain preview was inspected. Interactive map loading/input/save-reload and remote CI remain separate; do not describe the preview or script simulator as an emulator playtest.

At the user's request, festival picnic completion now offers an optional direct Echo Woods warp after either Scott outcome. The existing host(16,47) repeats that offer after the picnic, before its original menu; No or missing girls returns to the caller without unlocking/ending its menu. TrioRift_FestivalOffer never grants progress and ends/releases only after an accepted warp. The festival source simulator includes the actual Rift script for cross-file integration checks. Existing exit paths return to Goldenrod Center. User explicitly authorized publishing with a normal push; keep PR draft/unmerged.


## Riko Courage: two-headed midgame Echo supersedes the pilot reward/guardian

The user approved the two-headed Pom as a permanent midgame form. SPECIES_RIKO_ECHO1607 appends after existing species; ITEM_RIKOS_COURAGE949 appends after existing items. Existing real IDs remain stable; egg/UI sentinels move. Baseline/current ARM ABI checks verified SaveBlock1/2/3 sizes15444/2864/100 and SaveBlock3 dexNavChain/candyJarExp offsets12/96 unchanged. Current DexNav uses registered-species mode, not a NUM_SPECIES-sized saved array; item-description flags are disabled. Audit those configs before future species/item additions.

Echo has its own battle/menu/follower art and level-up Echoed Voice. It is female Normal/Fairy with95/80/90/110/110/95 stats, Cute Charm/hidden Fluffy, no Mega/formChangeTable. Base or Winged Riko plus Courage evolves to Echo; Echo plus Courage returns to ordinary Riko. Winged remains its separate branch. Party checks and Camp evolution statistics include Echo. The Key Item uses normal evolution UI, protects importance, and is reusable because ItemUseCB_EvolutionStone skips consumption for Key Items. Do not make Spirit boss species or temporary Mega forms equivalent to Echo.

Echo Woods now uses the Echo guardian, not the three-headed Spirit. PrepareTrioSpiritTrial accepts Echo alongside Penny/Bijuu Spirit and gives it level1 at the user's request for quick testing, Disarming Voice/Tackle/Baby-Doll Eyes/Helping Hand. Safe heal/return/catching restoration persists. Legacy level90 Riko cave remains unchanged. Final Spirit unlocks remain planned endgame content, not granted here.

Reward uses FLAG_TRIO_RIFT_COURAGE_RECEIVED1089, audited free at baseline37929c2a, within unchanged save arrays. State4/5 records victory independently; even older state5 Wand winners can collect Courage once without another fight or the trio. Set the flag/state5 only after successful giveitem, allowing full-Bag retry. Preserve existing Wands. Scripts.pory and.inc remain synchronized.

Local verification: production ROM compiled; targeted engine suite across three shards reported61 passes and21 expected runner self-test failures with zero unexpected failures. Four new Courage and two updated Rift tests passed. Eight Rift, twelve festival, six Camp, six Scott, seven gang and six chase source/geometry groups pass; inclusive docs-summary validation passes. Indexed assets/palettes were inspected and compiled six-frame follower data/palette matched PNG/palette sources byte-for-pixel. Save ABI comparison passed. Broader docs unit suite has45 passes and one pre-existing Gracidea wording mismatch (by versus after showing Shaymin); parser/test files are unchanged. User previously confirmed the pilot Woods loaded, but this new form's rendered evolution/follower/save-reload still requires interactive playtesting. CI status is separate.


## Mirror House and Lantern Trail: playable midgame sister chapters

User confirmed Riko Courage's evolution/reversion and introduction worked, then approved Bijuu tail-flame and lightly armored shield-free Penny. SPECIES_BIJUU_EMBER1608 / PENNY_BRAVE1609 and ITEM_BIJUUS_FIRE950 / PENNYS_BRAVERY951 append after existing real IDs. Preserve final Spirit species and existing Guardian/Psychic/elemental/Mega branches. Reusable protected Key Items enter from base/Psychic Bijuu and Fidough/Dachsbun/Guardian Penny, respectively; reverse returns to ordinary Bijuu/Fidough. Both are female; Ember learns Ember, Brave learns Helping Hand on evolution. All art lives under their own species directories; followers use six engine-ordered32x32 frames and matched16-color palettes.

New maps38/39 in IndoorGoldenrod and layouts1031/1032 append. Mirror House is13x10, ordinary Johto house tiles, entry(4,7), true south-arrow exit(4,8) and optional exit guide(2,7). Riko(1,6) gives first clue, Penny(9,6) second; wrong copies(2,4)/(5,4) never reset clues, real Bijuu(8,4) accepts after both. Ember guardian(5,2) fights only after finding her. VAR_TRIO_RIFT_BIJUU_STATE412B meanings0/1/2 clues,3 real cat,4 victory/gift pending,5 charm. FLAG_TRIO_RIFT_FIRE_RECEIVED108A is set only after successful giveitem.

Lantern Trail uses the verified Woods geometry with independent state. Orb lanterns(10,26)/(10,21)/(10,13) open physical gates in order. Existing gym animateflash/setflashlevel behavior brightens a modest radius4 ->3 ->2 ->0; transition reload reconstructs light and on-load reconstructs gates. No cave/weather callback or field Flash requirement. Guide exit explicitly sets darkness0 and ordinary map transitions reset it. VAR_TRIO_RIFT_PENNY_STATE412C meanings0-3 lights,4 victory/gift pending,5 charm; FLAG_TRIO_RIFT_BRAVERY_RECEIVED108B records actual successful receipt. Brave guardian at(12,4). Exit guide and south-arrow warp always accessible. Riko's starting NPC was moved to(13,27) in Woods and Lantern: old(9,26) was boxed in by the cushion/exit NPCs. Geometry checks now require an adjacent reachable interaction tile for every new object.

Both new vars/flags were free in baseline3dd224e0 source raw/numeric audit; save-array sizes and ARM ABI SaveBlock1/2/3 sizes15444/2864/100 plus SaveBlock3 offsets12/96 are unchanged. Shared trial setup gives both midgame bosses level1, heals before/after and restores catching restriction across outcomes, preserving ordinary squirrel blackout rules and high-level final Spirit setup. Full Bag retains victory for reclaim without party/rebattle. Mom scrapbook replays both won memories using returning helpers.

Natural entries are appended old men(10,6) in Ecruteak/Olivine Centers, requiring the preceding charm. Goldenrod guide and festival host now offer the next unclaimed chapter (Courage -> Fire -> Bravery). After all three, decline earlier revisit offers to choose later chapters. No new Badge gate/start grant/reset/forced party mutation. The guide selection uses local scratch8007 only while talking; progression uses persistent vars/flags. Shared sanctuary and Scott arena still planned, not implemented. See docs/trio_spirit_rift.md.

Local verification: production ROM compiled; three new engine tests plus existing targeted suite reported64 passes and21 expected runner self-test failures across three shards, no unexpected failure. Eight new sister script/geometry/asset groups and existing eight Rift/twelve festival/six Camp/six Scott/seven gang/six chase groups pass, alongside docs-summary and diff checks. Actual compiled follower frames matched source PNGs byte-for-pixel, and saved structure ABI matched baseline. User confirmed earlier Riko form only; new rooms, darkness animation, battle/evolution art, real save/reload and loss/retry need rendered interactive confirmation. CI remains separate.

## Rift trial polish (2026-10-10)

The player confirmed all three chapters and charms work in the emulator, then supplied screenshots showing Bijuu Ember walking sideways backward and Penny Brave's detached pixels. The follower animation table uses LEFT-facing frames4/5 and mirrors them for east, as recorded in the earlier Penny art notes. Bijuu's right-facing generated frames are now flipped in the importer. Penny's uniform crop had included neighboring tails/feet and truncated poses. An image-generated repair plus per-subject crop boxes preserves the blonde dachshund/light bronze armor/no shield design. Final battle and all six follower frames pass a connected-silhouette regression check with no detached pieces; indexed frame previews were inspected. Riko Echo's existing side frames already face left.

All three midgame guardians now scale to strongest non-egg party member+10, capped100, on each attempt. Stronger thematic moves replace level1 testing moves. Original Spirit species/trials retain their setup; final forms are not granted. The safe healing/loss/escape callback, pending full-Bag rewards, saved puzzle states and already-earned charms are unchanged.

After the picnic, Goldenrod's existing Gramps at(17,36), near Bill's house west of the Center, offers the next Rift chapter. His normal dialogue/scrapbook calls remain; only the picnic-gated optional call is appended. This civilian remains hidden during the Rocket takeover; Center/natural-city guides remain fallbacks. Festival host/picnic now provide a town hint instead of a direct warp. No new object/flag/variable is allocated. Keep authoring Pory and assembly hooks synchronized.

Local validation: production ROM compilation;65 targeted engine passes plus21 expected runner self-test failures, zero unexpected failures;55 source-flow/geometry/asset checks across Rift, festival, Camp, Scott and squirrel flows. New level tests cover all three guardians at levels1/35/95/100 and a level100 Egg alongside a level20 party member. This is not a new rendered emulator playthrough; walking-direction and town travel still need player confirmation on the updated ROM.

## Post-trial atmosphere and Goldenrod town-only entry

The player confirmed the corrected Bijuu/Penny sprites work, then requested removal of the Goldenrod Center's duplicate trial offer. Its dedicated last old-man object is now removed; the Center retains all original residents, festival guide, services and warps. Goldenrod outdoor Gramps near Bill's house is still picnic-gated and offers next/revisit chapters. Ecruteak/Olivine entries and chapter exit warps remain unchanged. Do not reintroduce the Goldenrod Center entry as a fallback without a new request.

Thirteen ordinary Johto/Kanto residents now have natural-phenomenon observations only after ALL THREE persistent Rift chapter states reach4 or higher. Use victory states, not charm possession/receipt flags, so full-Bag winners still get the atmosphere. TrioRift_CheckAtmosphere writes only scratch VAR_RESULT; no new save field/flag/variable is allocated. Dialogue is about answering echoes, lingering light, warmer breezes, gentler shadows and flowers/grass moving together; it does not claim NPCs heard the trio pass trials. Actual map weather/light/battle settings are unchanged. Existing party/forms/earned items are not prerequisites, and existing completed saves qualify automatically.

Hooks are listed in tools/rift/atmosphere_manifest.json. For Azalea and Mahogany, hook only the original post-Rocket Gramps branch; preserve the original dispatch and early story dialogue. Other hooks use plain resident conversations without services or quest rewards. Maintain raw Pory blocks and compiled scripts where present. tools/rift/validate_atmosphere.py simulates13 actual interactions across64 saved-state combinations (832 cases), full-Bag/missing-party completion, original map/story dispatch, Pory parity, text widths and removal of the Center object. Compiled/rendered playtesting remains separate from source simulation.

Atmosphere verification:60 source/geometry/asset groups pass across all existing family validators plus five new atmosphere groups; all modified Pory files compile and their generated hooks/text match checked assembly. Production ROM compilation passed. Actual engine test 'Item descriptions fit on Bag and Shop Screen' passes across all951 descriptions. Previous CI153 produced a ROM but failed this test at Bijuu's Fire (105px versus102px); fixing that exposed Penny's Bravery at110px. Both descriptions are now shorter without changing item behavior. New town-only entry and atmospheric dialogue still need a rendered emulator conversation check; the player already confirmed the previous sprite corrections.

## Abandoned seaside garden and Flower Riko (2026-10-10)

The approved flower charm/art is now implemented as a quiet optional Olivine outing after Chuck's Badge (`FLAG_BADGE05_GET`). The existing little girl feeding Mareanie at (33,58) retains her original dialogue, then offers a garden visit. City objects/warps/story dispatch are untouched. Do not move this back into Goldenrod's busy festival hub. Garden has no battles, purchases or real-time waiting.

`VAR_TRIO_GARDEN_STATE=0x412D` uses 0 abandoned,1 planted/waiting,2 ready Bijuu,3 warmed/waiting,4 ready Penny,5 bloom/reward pending,6 charm received. Olivine's returning transition helper advances only 1→2 or 3→4; saving/reloading inside does not count as another visit. All three recognized sisters are required only for restoration actions. Declining/missing party preserves progress. On-load reconstructs four beds and uses TEMP1/TEMP2 for ordinary/flower Riko NPC visibility; only one of their overlapping templates is visible. Map24x18 uses safe JohtoGeneral/NationalPark tilesets, appended IndoorOlivine map14 and layout1033. Caretaker returns to wharf(33,57); two south arrows return to existing city warp0/Lighthouse. Check every state for reachable interaction/exit tiles.

`ITEM_RIKOS_BLOOM=952`, `SPECIES_RIKO_FLOWER=1610`, receipt flag0x108C were appended/audited free against aa7efd8. Bloom is a protected reusable Key Item through the existing evolution-stone consumption guard. Only ordinary Riko↔FlowerRiko; other forms return to ordinary first. No Mega/Spirit/form-change table, no auto party evolution, no overwriting existing pathways. Same Normal/Fairy stats/abilities as Riko, female, Aromatherapy evolution move. Battle/menu/follower images use16color palettes; all6 follower frames are contiguous4x4tiles and side frames faceLEFT.

Caretaker or Mom can deliver pending Bloom to a full-Bag winner later without restoring again or bringing the party. Completion state5+ adds a returning Sisters scrapbook memory and pressed-flower Camp wall picture at(8,1), reconstructed on visit even before receipt. Camp stays within the existing object limit; picture uses a background sign. Original map/layout IDs and active saved ABI are unchanged; engine tests assert SaveBlock1/2/3 sizes15444/2864/100. Old saves begin at gardenstate0.

Local validation: production ROM compiled;108 engine passes across3 shards plus21 expected runner self-test failures, zero unexpected failures. All5 new garden tests pass, alongside Camp/Courage/Rift/squirrel/new-game regressions and full text-fit checks (including953 item records and enabled species).69 actual-source/geometry/art groups pass across9 family validators; inclusive docs-summary and diff checks pass. Compiled Flower Riko follower frames/palette match indexed source pixel-for-pixel. This is not a rendered interactive emulator garden playthrough: actual entry/exit input, evolution animations and real save/reload await player confirmation. CI is separate. See docs/trio_garden.md, tools/garden/validate_garden.py and validate_compiled.py.

## Riko Puffs: post-eight-Badge catch-up item (2026-10-10)

`ITEM_RIKO_PUFFS=953` is appended without new saved flags/vars or changing existing item IDs. It is a consumable ordinary Items-pocket candy, ₽500, with a24px16color kibble icon. Blackthorn Mart's existing left-hand TM/ball clerk offers it only after ALL EIGHT Johto Badge flags. The other clerk, original stock, map events and story progression remain. Both Pory and assembly use returning TrioPuffs_Shop, with all256 Badge combinations covered. Old eligible saves qualify on their next purchase.

PokemonUseItemEffects gives five levels per Puffs itemCount, capped100 or the current enabled candy cap. Eggs/empty slots/zero quantities are rejected; preview does not change experience. Ordinary Cat Food Tin/Rare Candy and EXP Candies retain their original calculations. BW/HGSS shared party_menu.c and separate SwSh party menu calculate ceil(remainingLevels/5), preserving excess Bag items (level1needs20 to reach100;95or96needs1). Level100/no-effect Puffs cannot be consumed to trigger a candy evolution. The existing level-by-level move/innate/evolution flow remains, including move-summary restoration. Do not change just one menu implementation.

Local production ROM compilation passed;79 engine passes across3 shards plus21 expected runner self-test failures, zero unexpected failures. All6 new Puffs checks pass, including36 species/level combinations across growth rates, batch/preview/no-effect/egg cases, enabled caps, all3 party quantity helpers, ordinary candy and evolution eligibility, price/Bag/text and SaveBlock1/2/3 sizes15444/2864/100. Reverse Candy, move-learning restoration, prior Courage/Garden and full text-fit checks pass.74 source/geometry/asset groups pass including5 Puffs groups (all256 Badge combinations), plus inclusive docs-summary/diff checks. The compiled kibble icon's576 pixels and palette match source. Actual shop purchase/quantity/move/evolution animations still need rendered emulator confirmation; remote CI is separate. Built-in image generation created the toasted-kibble source; tools/puffs/import_icon.py performs deterministic palette/size conversion. See docs/riko_puffs.md.


## Dedicated Spirit of Riko cave pilot (2026-10-10)

The user requested implementation of Mind/Body/Soul → Spirit of Riko with a
New Bark testing warp and a distant-feeling cave. RikoSpiritCavern appends as
IndoorNewBark map6/layout1034, using JohtoGeneral/CaveDefault (Union Cave pair)
without weather/time/Flash/old cave callbacks. Mailbox17,11 retains its sign,
then explicitly offers TEST travel; no Badge/trial/party gate, startup warp or
new NPC budget. Preserve the original .pory/.inc hook. Southern cave arrows use
0x407 behavior0x65 and return to outdoor New Bark warp1; guide returns18,12.

Boss-only RikoAspectMind1611/Body1612/Soul1613 share ordinary Riko geometry with
independent native violet/amber/pale-blue palettes, no evolution/formChangeTable,
and female identity. Old real species IDs remain; Egg sentinel moves. Four
battles scale highest non-Egg+10 cap100, with gentler attacks below party20.
PrepareRikoCavernBattle validates phase0-3 and uses the shared safe-heal/no-catch
restoration callback. GetBattleBGM scopes four legendary/Champion themes to the exact
cave and species; ordinary battles remain unchanged.

State412E=0Mind/1Mindwon/2Bodywon/3reunion+finale/4finalewon; permanent flag108D
records earned final memory/reward, retained through the guide's confirmed TEST
restart. Slots audited free against5eaa4ea0; decimal4237 was only a generated
trainer #line, not a flag use. Save arrays stay unchanged. Existing Spark/Mom
pending-delivery/letter helpers accept this flag OR historical Suicune victory,
never set FLAG_DEFEATED_SUICUNE, and retain once-only/full-Bag semantics. Cave
wins never grant a Spirit evolution/capture; true endgame unlock remains planned.

Transition restores base object coordinates/temporary visibility before settling
won aspects. removeobject sets its visibility flag, so clear temp flags before
respawning settled aspects. Soul's shrine permits only its south approach16,7;
camera pans six tiles to the reunion center and is removed afterward. No forced
player path. Eight actors plus player/follower/camera fit the runtime16 budget.
The old broken cave is unchanged and is not validated by this independent map.
See docs/riko_spirit_cavern.md, tools/riko_arena/validate.py, test/riko_cavern.c.
Compilation and source/engine checks do not replace rendered player testing.


Cavern pilot validation: final production ROM compiled (ROM32510852 bytes,
EWRAM255420 bytes); all5 new actual engine tests pass, including music scope and
saved ABI, and5 actual-script/geometry groups plus26 Garden/Rift/Sisters groups
pass. Inclusive docs-summary and diff checks pass. Existing rendered cave entry,
camera/fusion/animations/music/save-reload are still unconfirmed; user testing
must distinguish these from headless battle-preparation tests. CI is separate.

## Riko's Amulet and level-one cavern testing (2026-10-10)

Scott's festival picnic now grants ITEM_RIKOS_AMULET954, protected reusable Key
Item with custom 24px/16color icon. FLAG_RIKOS_AMULET_RECEIVED108E audited unused
(all numeric matches were trainer #line); custom flags bound advances only,
existing saved ABI stays fixed. Giveitem result checked before receipt flag.
Scott picnic replay precedes party checks: old completed saves/full-Bag retries
need no party or repeat battle. Earlier festival losses still allow the picnic.

IsRikosAmuletAwake requires BOTH real FLAG_TRIO_PENNY_SPIRIT_COMPLETE and
FLAG_TRIO_BIJUU_SPIRIT_COMPLETE, never home/Rift/keepsake flags. Bag and registered
use share the proven TrioMemory callback; script dispatch offers warp16,26 only
when awake and accepted, preserves phase state. Travel only on outdoor ordinary
land towns/cities/routes with leave-capable companion; no surfing/underwater.
Exit is still New Bark. No automatic warp; mailbox TEST bypass stays available.

User-requested temporary RIKO_CAVERN_LEVEL_ONE_TEST=1 creates all four bosses at
level1/early moves; toggle0 restores strongest+10/cap100. Other Spirit/Rift fights
unchanged. Tests exercise both modes via config-aware expectations. These are
real saved cavern wins/rewards; guide restart retains permanent completion.
No new permanent Riko evolution/capture introduced. See docs/riko_spirit_cavern.md.

Amulet verification: production ROM compiled (ROM32512256/EWRAM255420 bytes).
Focused headless suite passes51 engine/text checks plus7 expected runner
self-test failures, zero unexpected failures; all6 cavern/amulet engine checks
pass. Eight actual-script cavern/amulet groups plus12 festival groups and docs/
diff checks pass. Compiled amulet icon matches all576 source pixels. Rendered
Bag/registered use, travel, cave fusion and real save/reload still await user
confirmation. Temporary level-one wins do record real progress as described.

## Cavern reunion camera repair

User rendered testing confirmed cavern entry, aspect fights and merge, but then
reported player offscreen/controls unavailable. Camera handoff was unbalanced:
six walk_down steps with no return. RemoveCameraObject reselects the player's
sprite and resets tracking, without undoing the scroll. The script now waits
for six walk_up return steps and removes camera BEFORE Awakened dialogue. Final
Spirit cry uses CRY_MODE_NORMAL plus bounded delay60 instead of waitmoncry, so
cry completion cannot block cleanup; whether that wait caused the reported
stall is unconfirmed. Earlier cries and battle behavior remain unchanged.
The actual-script validator tracks camera movement definitions and rejects
nonzero offsets at removal; it fails old code and passes the fix. No saved ABI,
phase/victory/reward or level-one-test changes. Pory/assembly match. Reload a
normal in-game save to replay; old mid-script emulator snapshots may retain the
stalled state. Visual confirmation of the repaired reunion is still pending.

Camera repair validation: the production ROM was reassembled and relinked
successfully (ROM32512276/EWRAM255420 bytes). Nine actual-script cavern groups
and12 festival groups plus docs/diff checks pass. Runtime visual replay remains
unconfirmed; prior engine suite is unchanged because no C runtime code changed.


## Spirit keepsake Megas and normal cavern access (2026-10-10)

User confirmed the reunion camera repair works, then requested challenging Riko
fights and final keepsakes as Megas rather than permanent evolutions. This
supersedes the pilot mailbox/reset/level1 instructions above. Toggle is now0;
New Bark TEST entrance and guide reset are removed. Battle preparation requires
festival picnic, Bag amulet and BOTH real final Penny/Bijuu victories. All prior
saved wins/rewards remain; no forced resets or new save allocations.

Riko's Spark, Penny's Shield and Bijuu's Light stay protected Key Items and retain
field letters. Carrying the own keepsake plus own actual final victory enables
Spirit Mega through the normal Mega Ring/button, once per trainer. Riko requires
cavern completion AND both sisters' real final victories; historical Suicune/home
wins or earlier Rift trials alone never unlock a Spirit Mega. Held Mega Stones
retain priority. Opposing battlers/NPC partners cannot borrow player Bag gates.

New Mega-only species1614/1615/1616 reuse established Spirit art and remain
separate from bosses and permanent item evolutions. All30 ordinary/personal forms
have Mega eligibility, and new Mega return tables use existing changedSpecies
fallback to restore exact starting form on faint/end. Personal forms get entry-
only tables, avoiding unwanted end-battle reversion without a Mega. No new saved
flags/vars or item-pocket changes. Existing species IDs unchanged; Egg moves.

Cavern bosses scale strongest non-Egg+10 cap100, have31 IVs/252-252-4 EVs and
phase-specific Life Orb/Lum Berry/Leftovers. Final moves are special Flamethrower,
Moonblast, Dark Pulse, Calm Mind. Cavern-only AI improves effectiveness, setup,
finishing, HP and stall decisions without affecting ordinary wild/Rift battles.
See docs/riko_spirit_cavern.md and test/trio_spirit_megas.c.


Release verification:72 focused actual engine/battle/text tests pass, plus7
expected runner self-test failures and zero unexpected failures. Spirit tests
exercise all30 eligible forms, fainting and exact-form return, actual final
victory/Bag gates, opponents and NPC partners, and existing Bondstone Megas.
Cavern tests cover restored scaling/caps, trained stats/items, proper access
and save ABI.83 family source/geometry/flow groups plus inclusive docs-summary
and diff checks pass. The player confirmed the prior reunion camera repair;
new Spirit Mega UI/animations and difficult balance still need rendered
interactive confirmation. Headless battle tests are not a rendered playthrough.

Final production ROM compilation passed (ROM32514296 bytes, EWRAM255420 bytes).


## Reformed squirrel-mafia cafe preview (2026-10-10)

User requested the reformed cartel cafe and explicit New Bark mailbox testing.
TrioGreedentCafe appends IndoorVermilion map9 and shares Olivine Cafe's proven
layout. Nine static nontrainer actors are six Greedents plus three girls. Its
southern native exit is the original cafe warp tile; all actor approaches and
entry/exit aisle are verified. No battles/thefts/progress grants in the cafe.

SetWarpDestinationToMapWarp redirects ONLY House3 warp0 after six saved wins OR
activewave6/phase2 (actual final victory/full Bag pending). Beforeward its original
gentleman remains; cafe boss preserves his Diglett hint. Natural Vermilion door
38,22 resets return mode0. Test mailbox17,11 reads original sign then offers
travel3,7, sets returnmode1; native exit and host return18,12 New Bark. Saved test
mode survives in-cafe reload. Both natural exits otherwise return Vermilion.
This mailbox cafe call supersedes the previous no-testing-mailbox instruction
for this user-authorized preview; it does not restore the Riko cavern bypass.

New vars412F(testreturn) and4130(parcels), flag108F(cafe visit) audited free against
d7894d87; numeric old matches were trainer #line only. No save arrays/old IDs
change. Delivery states0/2/4 ready,1/3 claimed waiting,5 done; only New Bark and
Vermilion outside transition helpers ready the next parcel. In-cafe transitions
never advance it. Successful giveitem alone advances; decline/full Bag keeps
pending. Scott parcels3smallWawa/3Puffs/1Leftovers each once with a flirty note.
Stock uses existing Wawa/Oran/Puffs at unchanged prices. First apology flag adds
Sisters scrapbook memory. Old winners qualify without reset or another fight.
See docs/trio_greedent_cafe.md, tools/cafe/validate_cafe.py, test/trio_greedent_cafe.c.


Cafe validation:100 focused actual engine/battle/text tests pass, plus7 expected
runner self-test failures and zero unexpected failures. All3 new cafe engine
checks pass, including147 access states and native exit routing.89 family
source/geometry groups and docs-summary/diff checks pass. Shared Spirit-family
metadata now includes every eligible personal form, and the previous no-Mega-
table assertions now verify entry eligibility plus absence of automatic normal
form faint/end reversion. Permanent evolution, all30 Spirit Mega starting-form
returns and standard species/form metadata tests pass. No rendered cafe
playthrough is claimed; mailbox/counter/exit/parcels/save-reload await testing.

Final production ROM compilation passed (ROM32517676 bytes; EWRAM255420 bytes).


## Family release cleanup (2026-10-10)

User confirmed the rendered cafe preview works and requested removal of all
test features before updating his wife. This supersedes the preview instructions
above. New Bark mailbox is a normal sign; cafe test offer/text/return routing and
New Bark parcel hook are removed. Both exits return to Vermilion even from old
preview saves. VAR_TRIO_CAFE_TEST_RETURN=0x412F stays reserved and unused; no
IDs, save arrays, earned victories, memories or parcel states are reset.
Natural House3 access still requires all six victories or final victory pending
full-Bag reclaim. Mom's friend's repeatable test supplies are removed, preserving
her original greeting and finishing movement. Fresh-save Mega Ring/Bondstone
test grants are removed; normal Radio Tower Ring and Elm Bondstone remain.
Festival test mode and Riko level-one override remain disabled (0); normal
level5 Riko/Penny opening and Route31 Bijuu join remain. Engine developer menu settings are FALSE in all builds; RELEASE=1 also
disables assertions. Do not delete legitimate quizzes or the
intentional level1 festival exhibition. Existing saves keep previously received
items and progress.

Release cleanup validation: RELEASE=1 production ROM compiled successfully
(ROM32444588 bytes, EWRAM255416 bytes). All44 focused engine/battle checks pass,
plus7 expected runner self-test failures and zero unexpected failures; cafe
access/legacy exit/save ABI, Riko gates/scaling, Spirit Megas and species metadata
are covered. All89 family source groups, docs-summary and diff checks pass.
Release routing changes have headless coverage; user confirmed the cafe preview.


## Family signature move tutor

New Bark Scott tutor at20,14 is explicitly authorized testing placement; relocate
only after the user chooses the permanent location. See docs/trio_signature_moves.md.
18 new moves append after historical Z/Max IDs, preserving every old move ID and
saved layout. MOVES_COUNT_ALL expands, MOVES_COUNT stays fixed (Metronome pool).
Form metadata enforces exclusive girl eligibility; boss Spirits/Eggs excluded.
Mega Riko move is now named Pom Supremacy with unchanged ID/effect. Free repeatable
lessons use standard party tutor and replacement/cancellation, no progress grants.
Safe With You is a new cure+Sp.Def effect using existing cure/stat-change commands.
Rendered tutor and save/reload confirmation is pending; compilation alone is insufficient.

Signature validation:50 focused engine checks pass plus7 expected self-test
failures; no unexpected failures. Save move fields/IDs, every18 effect, exclusive
form-family eligibility, stat-cap cure/Contrary/Simple, names, drain and prior
Spirit Mega/cafe/cavern/trainer behavior are covered. Source menu/cancel/text/
geometry and unchanged save files pass. Standard-move range handling explicitly
includes appended signatures; relearner runtime capacity192, trainer stack
bitset uses MOVES_COUNT_ALL. Neither changes save structures.

Scott's Elemental moves service uses a dedicated runtime relearner state,
current family form's damaging non-Normal STAB level-up attacks and actual
level. It excludes known moves, duplicates, previous forms and page cycling.
No saved fields/IDs change. Both party and move cancellations restore the
normal level-up state. See current-form lessons in trio_signature_moves.md.

Elemental validation: RELEASE=1 production ROM compiled (32447576 bytes ROM,
255416 bytes EWRAM). All52 focused engine/battle checks pass, plus7 expected
runner self-test failures and no unexpected failures. Includes current-form
selection, actual-level limits, deduplication/known moves, transformation
attacks, family/Egg exclusions, equipped-move retention and mode reset.
Source service/empty/cancel flows, historic move IDs/save files, text, docs
and diff checks pass. ManicEMU UI and in-game save/reload remain user checks.

## Cosmetic costume collectibles

First batch: Balloon Riko, Box Bijuu and Hot Dog Penny. Species1617-1620
append (fourth metadata preserves evolved Dachsbun Penny), items955-957 append.
Shared art for both Penny stages; level26 costume evolution stays dressed.
Cosmetic metadata exactly matches the ordinary base/stage: no battle benefit.
Entry-only costume form tables plus changedSpecies-based normal Mega returns
preserve clothing at battle/faint cleanup. Signature lessons, family checks,
Camp swaps and Spirit keepsake eligibility include all four species.

Cherrygrove43,9 balloon gift, Violet36,46 optional level12 courier battle/box,
Azalea36,19 bun gift. Static NPCs append; map progression/visibility unchanged.
Trainer1163 was audited unused and is now Morgan; trainer counts/flag bounds
remain1164. Items are protected reusable Key Items. Bag possession prevents
duplicate gifts; courier trainer flag allows full-Bag claim without a rematch.
No new persistent flags/vars or save fields. See docs/trio_costumes.md and
tools/costumes/validate_costumes.py --compiled. User approved generated art;
this does not establish rendered in-game costume/save confirmation.

Validation: RELEASE=1 production ROM compiled (ROM32471016 bytes,
EWRAM255416 bytes). All57 focused checks and93 broader species/text/Mega
regression checks pass, each suite with7 expected harness self-test failures
and no unexpected failures. Checks include both Penny stages/level26, exact
metadata/TM/signature access, encrypted storage, toggle eligibility, normal
and Spirit Mega/faint returns, historical saved ABI,192 gift paths, geometry
and all18 compiled follower frames/palettes. Docs-summary/diff checks pass.
Approved art and headless checks are separate from in-game emulator testing.

User explicitly requested easy costume testing supplies from Mom's friend.
The New Bark lass at9,16 now calls TrioCostume_TestSupplies after lock/faceplayer
before original story dispatch, in both Pory and assembly. Repeatable Yes gives
only missing costume Key Items; Bag-full retry preserves received items. No
party/progression requirement or courier victory flag; original dialogue follows.
This is authorized temporary test behavior, superseding the cleanup prohibition
only for these three gifts. Remove when the user requests test cleanup.

Testing-supply validation: production RELEASE=1 ROM compiled
(ROM32471372 bytes, EWRAM255416 bytes). All64 supply helper decline/owned/
partial-Bag/retry/repeat source cases pass, alongside192 natural gift flows,
text termination/wrapping, full Pory/assembly original-branch parity,
compiled follower art, historical IDs/save files, docs-summary and diff checks.
This script-only addition does not alter the engine covered by the previous
57 focused and93 broader passing checks. New prompt/gifts await emulator use.


## Complete costume batch and Poison Bijuu (2026-10-10)

User confirmed the first three costumes and Mom-friend gifts work, then requested
all six drafted outfits in one build. New species1621-1628 append for Princess/
Raincoat Riko, Bread/Detective Bijuu and Blankey/Lifeguard Penny; two extra Penny
entries preserve Dachsbun stats and dressed level26 evolution. All old real IDs
and form indices remain. Matching protected Key Items959-964 toggle to/from
ordinary stages, with exact cosmetic metadata, followers, icons and gifts.
Family checks, Camp swaps, signatures and Spirit/Bondstone exact-form returns
include the new outfits. No saved structures/flags/vars or trainers change.

Poison Bijuu uses existing1591, new Toxic Mouse958 ordinary Items-pocket reusable
item. Current-form learnset starts Poison Fang0, Acid Spray12, Venoshock20,
Toxic24, Poison Jab28, Sludge Bomb32, Gunk Shot44. Scott lists damaging attacks
at the actual level; Toxic remains normal status learning. The item toggles
regular/Box to Poison and Poison to ordinary. Existing other forms revert first.
Its airborne purple bubbles/vapor art replaces old unused Poison art; original
stats, female identity and family/Spirit eligibility stay fixed.

New optional static gift NPCs append without moving original objects or warps:
Goldenrod42,15 tiara and36,38 toast; Ecruteak47,43 raincoat and25,33 detective;
Mahogany23,21 blanket; Olivine34,57 beach vest; Fuchsia6,33 Toxic Mouse outside
Poison Gym. Bring the matching girl, accept, and retry full Bag. No new gates or
battles; ownership prevents duplicates. Mom friend temporarily offers all nine
costumes plus Toxic Mouse, skipping owned gifts; original story still follows.
This user authorization supersedes the earlier three-only testing restriction.
See docs/trio_costumes.md, tools/costumes/forms.json and placements.json.

Full-batch validation: RELEASE=1 production ROM compiled (32520152 bytes ROM,
255416 bytes EWRAM). All60 focused engine checks and93 broader species/text/Mega
checks pass, each with7 expected harness self-test failures and zero unexpected
failures. Covers all12 costume stage entries, three dressed Penny level26
evolutions, Poison item eligibility/current-level lessons, signature/TM metadata,
encrypted storage/save ABI and normal/Spirit Mega/faint exact-form return.
Source checks cover22528 test-supply combinations,192 prior gift flows,112 new
gift flows, seven collision/elevation/old-event-preserving placements, all60
compiled follower frames/palettes, historical IDs, text and docs-summary.
The user confirmed the original three costumes; new seven forms and actual
in-game save/reload still require focused emulator confirmation.


## Outfit reactions, photo album and optional side stories (2026-10-10)

User requested all five proposed ideas together. Ten costume/Poison gift NPCs
plus three ordinary residents react to current outfits; original dialogue stays.
Scott has one affectionate line per outfit/Poison at the tutor and four existing
Badge-city moments. New Bark tutor menu adds Album2, Exit3; Signatures0 and
Elemental1 keep their behavior. Scrapbook adds Album5 before Exit6, preserving
old options0-4. Image pages show actual native sprites, close on every return,
and keep earned portraits independent of current form/Bag ownership.

Audited-unused saved vars4131-4135 reserve three hunts0 offer/1 accepted/2 found/
3 claimed; bread mystery0 rumor/1 accepted/2 clue/3 reveal/4 claimed; photo bitmask
0-8 costumes,9 Poison. Existing arrays, bounds, IDs and earned progress unchanged.
Photo recording is in completed-evolution Camp hook and non-Egg party scan on
album opening; Penny stages share one bit, reversion cannot erase it. Numeric
sprite tags4132/4133/4134 are unrelated to hexadecimal saved addresses.

Original costume givers now offer optional hunts: Cherrygrove basket39,17 for
Riko, Violet parcel18,39 for Bijuu, Azalea mitten43,15 for Penny. Accept/search
needs own family; state2 reclaim does not. Rewards3 Oran/3smallWawa/3Pecha once,
state advances only after successful giveitem. Full Bags retry; no battles or
route gates. Goldenrod man53,14 offers fake legendary mystery, woman61,29 gives
clue, Bread Bijuu9,3 in eastern House4 reveals toast. Return reward2mediumWawa;
state3 full-Bag retry and replay preserve discovery. All four memories appear
in Sisters scrapbook; bread at discovery, hunts after successful claim.

Six props/actors append, no original events/warps change, four walkable approaches
and nearby actor budgets3-8. Three civilian hooks preserve all commands in both
Pory/assembly. Specials append, old indices fixed. See docs/trio_outfit_stories.md
and tools/costumes/validate_stories.py. Rendered new UI/story/save reload remains
unconfirmed. Mom friend's authorized ten-item testing supplies remain intact.

Validation: RELEASE=1 production ROM compiled (32528344 bytes ROM,255416 bytes
EWRAM). All70 focused engine/Camp/battle checks pass plus7 expected harness
self-test failures, zero unexpected failures. New checks cover every portrait
bit, both Penny stages, Egg exclusions, current-family reactions, existing dressed
saves, evolution hook retention and photo count; prior costumes/Poison/Megas/
Camp/cafe/cavern/trainers pass. Actual-source checks execute192 hunt paths,60
bread-mystery paths and all portrait/locked/Back/B/reaction/Scott flows; original
22528 test-gift states,304 natural gifts, all60 compiled follower frames,
tutor cancel/mode resets, geometry/Pory/history/docs/diff checks also pass.
Rendered new dialogue, portraits, quests and real save/reload still need testing.
Previous costume batch CI167 completed successfully. This batch has separate CI.


Outfit testing cleanup (2026-10-10): user confirmed every new outfit works.
Removed the Mom-friend testing call in both New Bark sources, restoring her
original story dialogue. Existing inventory, forms and saved progress remain;
all ten natural gift sources remain available. Scott stays in New Bark.


## Great Trio Road Trip (2026-10-10)

User approved the optional midgame island chapter. Scott at Cianwood22,48 and
Olivine PortOutside17,5 offers free travel after actual Badge05. Four appended
IndoorCianwood maps (shore/woods/cove/cabin), three appended layouts and the
proven MirrorHouse cabin layout preserve old IDs. All stories and exhibitions
are optional; rain never blocks exploration, cabin, ferry or original story.
Ferry return uses saved port413A so island in-game reload is safe.

Riko reads two physical trail clues then finds the lookout; Bijuu traces
caretaker/fisherman/pawprints/windchime to an ordinary guardian explanation;
Penny's deliberately started picnic shower leads to supportive choice, cabin
blanket and healing rest. Independent vars4136-4138 reach4 for permanent trip
photos. Sunset requires only those three stories, sets4139=1, adds Sisters
scrapbook memory/Scott letter. Cabin offers family/outfit talk, illustrated
photos, existing outfit album and rest forever. Leftovers gift413C advances
only after successful giveitem; full Bag/decline retry, no party requirement.

Trainer1151/1152/1153 were unused, but flags97F/980/981 belong to Rinto trade,
Vajra urn and Ariana. Road trainer flag guards MUST remain; independent wins
use413B bits0/1/2 and never alter those quest flags. Level34/36/38 doubles
exhibitions heal before/after every outcome with exact shore-map AND trainer
guard before whiteout; normal battle losses remain. Exact island battles force
doubles even if global replay is singles, with two non-Egg partners checked.
413D capped arrival count and413A saved port are runtime-special updates; other
road vars/old history stay intact. No save-array changes, new forms, real item
removal, startup grants or testing portals. See docs/trio_road_trip.md and
tools/roadtrip/validate.py; engine checks are test/trio_roadtrip.c.

Rendered entry/door/cabin/battle/portrait/save-reload still needs user testing.

Road trip validation: RELEASE=1 production ROM compiled (ROM32551784 bytes,
EWRAM255420 bytes). Four new actual-engine tests pass. The focused existing
family suite passes103 engine/Camp/battle checks plus21 expected runner self-
test failures across three shards, zero unexpected failures. Nine actual-
script/geometry groups, seven gang source groups, costume/story source checks,
production-ROM decoding of all3 new doubles teams, docs-summary and diff checks
pass. Native doorway tile and cabin south-arrow exit are inspected independently
of open-floor NPC reachability. No rendered playthrough is claimed. CI for the
new committed head is separate.

## Authorized Road Trip mailbox preview

User requested immediate New Bark testing. Player-house mailbox17,11 now retains its sign then offers TEST island travel, without Badge/party gates or progress grants/resets. Both Pory/assembly call TrioRoad_TestOffer; saved existing return var413A mode2 routes the island ferry to New Bark18,12 even after reload. Ordinary departures record0/1 normally. Remove the temporary offer only when requested, retaining earned chapter progress and safely routing historical preview saves. This supersedes the prior no-testing-portals rule only for this explicit preview.


## Dinner, native family radio and homecoming (2026-10-10)

User approved all three optional midgame chapters. Scott at Goldenrod15,25
(after Badge04, ordinary civilian visibility) offers TrioDinnerDate, appended
IndoorGoldenrod40, using native Olivine Cafe layout/arrow exit. RadioTower1F's
existing woman23,8 retains original text then offers separate TrioRadioStudio
(after normal FLAG_ENABLE_RADIO and Badge03, no Rocket takeover). That appended
IndoorGoldenrod41 shares MirrorHouse layout/exit to the lobby. Preserve both
Pory/assembly hooks and all original quiz/password/radio services.

Three saved recording prep steps unlock Tails of the Trio on native Pokégear
dial52. Random four segments read earned story state; they never write saves.
Existing Rocket takeover substitutes Rocket on this channel too. Studio and
field share bounded helper strings (<=12 lines,<=26 characters/line); station
music is existing radio lullaby. New special appends only. No new saved arrays.

Pryce's first Badge07 award supplies Mom's note; eligible older saves can talk
to Mom directly. Her optional offer precedes ordinary original story/heal
branches, returning normally on decline. Separate TrioHomecoming appends
IndoorNewBark7 and shares the original home layout, preserving normal home
objects/triggers. Mom/Scott/girls plus3 virtual story gifts and3 earned decor
props total12 actors+player/follower14. Native exit returns outdoor home.
TEMP1-3 hide flags reconstruct festival/garden/island decor on transition;
never grant achievements. Sequential gifts, finale, replay and healing persist.
Both meals give small existing snack rewards once, full-Bag/decline pending.

Vars413E dinner0-5,413F radio0-4,4140 homecompletion0/1,4141 dinnerreward0/1,
4142 homevirtualgifts0-3,4143 homereward0/1 were audited unused in source against
c8cf449076. Historical IDs, saved ABI, natural quests and authorized Road Trip
mailbox preview remain intact. Read docs/trio_family_days.md and actual code;
source/engine validation is distinct from rendered player confirmation.

Family-days verification: RELEASE=1 production ROM compiled (32564940 linked
bytes, EWRAM255416). Three new actual-engine radio tests pass, including512
segment/scenario bounds/page-format checks, saved ABI and earned-state gating.
Focused radio/Road Trip/outfit/cafe suite reports34 passes+21 expected runner
self-test failures over3shards, zero unexpected failures. Nine actual-script/
geometry groups,10 Road Trip groups,7 gang groups, costume-story source checks,
compiled active entry hooks, docs-summary and diff checks pass. Native exits
share the exact proven layouts/coordinates. Rendered restaurant/studio/home,
radio UI and real in-game save/reload remain for user testing; new CI is separate.

## Player hats prototype (2026-10-11)

User approved trying female-player hats. Right bedroom bookshelf6,1 (approach
6,2) is now a free hat shelf: original, pink bow, vacation sunhat. No Badge or
chapter gates. Cancel preserves current style; ApplyTrioPlayerHat updates the
actual player immediately. Male avatars retain their normal graphics.

VAR_TRIO_PLAYER_HAT4144 uses the existing saved array, zero original/one bow/
two sunhat, invalid values read as original without rewriting progress. Saved
ABI, palettes, historical IDs and dynamic object graphics remain unchanged.
Explicit field graphics384-401 are handled before ordinary invalid-ID fallback;
NUM_OBJ_EVENT_GFX must remain330 here, preserving old dynamic IDs331-346. All
nine native state tables (walking combines running) copy native geometry/anim/
palette/subsprite metadata. Normalize hat IDs for gender/state recognition.
Only player-state callers select the variants; Copycat and rival NPCs keep
their historical native IDs. Decoration preview, local trainer portrait/card,
Pokédex/Hall of Fame and Safari/normal battle entrances follow saved choice.
Link back art and received cards preserve default behavior. Four trainer IDs
append after historical back IDs without moving FRONT_COUNT. The intro throw
palette indexes the full back ID, matching its existing registered table.

Art uses imagegen accessory reference plus tools/player_hats native C compiler;
24 PNG variants preserve body art outside head regions and original palettes.
Underwater accessories retain the native monochrome palette. Read docs/
trio_player_hats.md and code before extending. Four new engine tests pass;
focused hats/radio/Road Trip suite32passes+21expected harness failures over
three shards, zero unexpected.186 accessory frames,9 family-days and10 Road
Trip source/geometry groups pass. Production build and committed CI are
separate from rendered emulator/save-reload confirmation. PR remains draft.

## Corrected hat packing and custom thrown balls (2026-10-11)

User's rendered screenshot showed strips instead of the player after selecting
a hat. Source PNG/native geometry checks had missed whole-sheet4bpp tile order.
spritesheet_rules.mk now packs narrow hat frames2x4 tiles, wide4x4, trainer8x8;
the rules file is also a dependency to repair old cached assets. Never assume
source PNGs or successful builds prove frame order. tools/player_hats/validate.py
now checks every compiled pixel against186 source frames, reproducing the
earlier defect and passing for the repair. Hat art/palettes/saved choice remain.

Trio/Great, Riko Ultra, Bijuu Moon and Penny Love previously only rethemed Bag
art. Their battle three-frame sheets now match that design and bind the exact
existing Bag palettes. Great/Ultra no longer receive generic gOpenPokeballGfx
overwrites. Standard Poke/Master/Net/Nest/Repeat/Safari handling remains. Existing
captured Pokémon keep the historical IDs and get the new send-out art; no
item/save/catch-rate changes or gifts. Imagegen source sheets live in graphics/
balls/custom_sources, native conversion in tools/custom_balls. Read docs/
trio_battle_sprite_repairs.md before extending this path.

Two new native-engine tests verify registration and every1536 custom-ball VRAM
byte after LoadBallGfx. Focused hats/balls/radio/RoadTrip suite34passes plus21
expected runner failures over3shards, zero unexpected.186 hat and12 ball frames,
source/save/palette checks and RELEASE=1 production build pass (32666372 linked
bytes, EWRAM255416). Rendered emulator hat/throw/open/send-out and save-reload
confirmation remain separate. Keep PR draft and all earned progress intact.


## More-pink player wardrobe (2026-10-11)

User confirmed the repaired hats and balls work, then requested more pink.
The four existing May palettes now give shorts/cap/sunhat pink shading and
jacket blush highlights. Skin, brown hair, outlines, transparency, white and
existing top pink remain unchanged. Shared hat palettes cover original/bow/
sunhat in field and trainer art; underwater keeps its native monochrome palette.
Source PNGs, frame packing, saved hat choice and all gameplay/saves remain fixed.
Player-hat validator now permits only the exact authorized palette indices,
continuing to check all186 compiled frames and historical ABI/body art.

Validation: production RELEASE build passes; all four linked ROM palettes
match the requested colors and all186 hat frames pass existing binary checks.
Sprite PNGs and gameplay/save source remain unchanged from8091d4e472.
Prior repair CI176 passed; user confirmed hats and thrown balls work.


## Walking/running family hats (2026-10-11)

User approved Riko Pom ears, Bijuu Siamese ears and surprise Penny hot-dog hat,
walking/running only. Existing wardrobe adds Riko Hat3/Penny Hat4/Bijuu Hat5;
Original0/Bow1/Sunhat2 and saved var4144 retain meaning. Exit6/B cancel never
apply a selection. Fitting dialogue reveals Penny's hot dog only after choice.
Three explicit graphic IDs402-404 append after384-401, normalized to MayNormal.
Other activities/trainers use ordinary art without clearing the selection;
walking restores it. Existing bow/sunhat full-state behavior remains unchanged.
NUM_OBJ_EVENT_GFX330 and historical dynamic IDs/saved ABI stay fixed.

Three built-in imagegen direction atlases are under player_hats/family_sources;
native C assembly and format-only Python entry preserve original body pixels,
existing shared more-pink palette and contiguous2x4 native frame packing.
Read docs/trio_player_hats.md and tools/player_hats/build_family.py before
extending. All54 new plus186 old accessory frames pass compiled/body checks.
Production RELEASE build passes (32680852 linked bytes/EWRAM255416).
Rendered hat directions and actual save/reload await user testing.

Focused native suite35passes plus21 expected runner self-test failures, zero
unexpected failures. All three actual production-ROM graphics payloads match
the verified54 compiled frames byte-for-byte. Existing hats/balls/radio/trip
checks pass. Source validators cover palette/body/frame order and cancel/Exit.


## Pom Fu Riko (2026-10-11)

User explicitly requested a functional new Normal/Fighting Riko form, not a
costume, with a reusable Black Belt granted by a recognizing karate NPC.
SPECIES_RIKO_FIGHTING1629/ITEM_RIKOS_BLACK_BELT965 append, old real IDs and form
indices preserved; Egg follows new tail. Female PomFuRiko has physical560BST,
whitegi/blackbelt battle/menu/six-frame follower art, matching16color palettes,
Force Palm evolution move and current-level Fighting lessons through Scott.
Protected reusable belt ordinary/three cosmetic Riko -> PomFu; reverse -> base.
Other permanent/elemental forms use existing reversions first. Family/Spirit
eligibility, signatures and Camp transformation stats include PomFu; no album
change or save-array/init/quest-progress changes. Existing Cianwood martial
artist20,54 calls optional gift before original atmosphere/story dispatch;
owned/decline/missing/full-Bag paths return normally, no battles or new objects.
See docs/pom_fu_riko.md, tools/costumes/validate_pom_fu.py and test/trio_pom_fu.c.

Pom Fu validation:103 focused engine/battle/species/text checks pass plus21
expected harness failures, zero unexpected. Four new Pom Fu checks pass and
Spirit Mega exact-form return includes Pom Fu.16 actual gift paths, body/history
checks and compiled art pass;240 player-hat frames retain packing and palettes.
The broader costume source validator reaches a pre-existing New Bark exact-file
assertion (later authorized Road Trip mailbox preview); no Pom Fu hook is there.

Verified RELEASE production build32688384 linked bytes/EWRAM255416; nine
actual ROM graphics/palette payloads match compiled native assets.

## Six complete elemental forms (2026-10-11)

User approved Dragon/Bumble Riko, Midnight/Crystal Bijuu, Digging/Handy Penny
and all six generated atlases. Digging Penny MUST remain head/floppy ears
poking out of earth like Diglett; no exposed torso/legs. Battle/menu/followers
and item art are native16-color sprites with matched approved normal/shiny
palettes. Source atlases stay under their species directories; native C owns
cropping/scaling/quantization; Python handles formats/native byte assembly.
Read docs/trio_complete_elements.md and tools/elements before extending.

Dragon1589/Rock1593/Dark1596 reuse existing species; Bug1630/Ground1631/Steel1632
append after PomFu1629. Items966-971 append, historical real IDs/form indices
unchanged. Riko ordinary/three costumes -> Dragon/Bug; Bijuu ordinary/three
costumes -> Dark/Rock; matching item reverses to ordinary. Guardian Penny ->
Ground/Steel -> Guardian, matching existing Water/Grass branches. Dad's Keys
is the entry item for Guardian. Other permanent forms revert first. All six
keep female family dex/growth/signature/Camp and Spirit Mega eligibility;
current-level damaging STAB Scott lessons and learned move retention follow
the existing service. No costume album additions or saved array/init changes.

Six original resident hooks: Blackthorn cooltrainer44,31 dragon plush; Azalea
elder44,14 honeycomb; Ecruteak man22,42 sneaky cape; Mahogany elder7,13 shiny
pebble; Violet elder28,36 garden trowel; Olivine sailor33,46 Dad's Toolbox.
Bring matching girl. Owned/missing/decline/full-Bag return to original dialogue,
no badges/battles/new objects/progress flags; Pory and assembly stay in sync.
No temporary New Bark grant. Existing maps/services/earned progress retained.

Validation:122 focused engine/battle/species/text checks pass plus21 expected
harness failures, zero unexpected.25 new form/evolution/lesson/storage/exclusive
item tests and new Spirit Mega exact-form parameters pass.96 actual gift flows,
six original map/NPC dispatches, save/history/form-index checks,60 compiled
sprite frames/six item palettes and72 actual linked-ROM payloads pass. Existing
240 hat frames and PomFu gift/art checks pass. RELEASE production build32712496
linked bytes/EWRAM255416, padded32MiB ROM. Rendered gift/evolution/follower and
actual emulator save/reload remain for user testing. Keep PR2 draft/unmerged.

## Greg roaming expansion (2026-10-11)

User requested enough Greg appearances for paranoia and very annoying local jokes,
especially Caleb's view/Garchomp boast.15 custom stops total: original3 unchanged
plus Goldenrod,Route38,Ecruteak,Cianwood,Route42,Blackthorn,Pewter,Cerulean,Vermilion,
Celadon,Fuchsia,Saffron. New last actors face down, two-tile sight, original man art;
walkable full sight-line bypasses, no doors/triggers/sign conflicts and conservative
16-object budgets. Existing scripts/objects/IDs/warps/services remain. Each copies
original six level99 mons with normal blackouts; independent wins quiet that stop.
38 text boxes add local intro/brag/defeat excuses and family/Scott callbacks.
All share the existing one-time Wawa flag, with full-Bag post-win claim retry.

IMPORTANT: aliases1080-1091/UNUSED216-227 overlap reclaimed0x938-0x943 replay/story
flags. All trainer sight/interaction/read/set/clear/victory paths MUST use Greg's
saved wins, NEVER those flags. VAR_TRIO_GREG_WINS4145 is a12bit mask in the existing
saved variable array; no new arrays/counts/init or changed historical wins/rewards.
Read docs/greg_roaming.md and tools/greg. Geometry includes beach sand0x21.
Source scripts are global assembly; active map JSON actors point directly to them.
Original Route37 Psychic Greg is independent, unmodified.

Validation44 focused engine/battle checks pass +21 expected harness failures,
zero unexpected.3 Greg tests cover independent wins/all APIs, prior reclaimed
flags, old Greg/Wawa/neighbor progress and saved ABI. RoadTrip/snack/hats/Spirit
regressions pass.12 bypasses/map budgets/history,38 texts, reward retries,7 squirrel
source groups and production-ROM72 mons/12 NPC-script-text pointers pass.
Rendered approaches/sightings/save-reload await user testing. Keep PR2 draft.

## Goldenrod Pom Parade (2026-10-11)

User approved a replayable parade with about nine Poms and a crowd on the
connecting street. Existing central woman30,25 offers it before original text
in both raw Pory/assembly; decline continues normally, Rocket visibility stays.
Appended IndoorGoldenrod TrioPomParade stages the exact native city layout. Nine
Riko-art Poms march up32/34, spectators including Scott watch from27/29/31,24,
Penny/Bijuu sit beside player30,23. Spin/sniff/bark and last-Pom fast catch-up
finish before crowd cheers and ordinary-city return30,24. Fourteen NPCs plus
player/possible follower fit16 slots. PrepareTrioParadeActors spawns offscreen
rear actors and verifies every live sprite; failure returns with no completion.
Map transition temporarily hides Pokemon follower; every return clears it.
No camera scroll, battle, gift, party gate, Badge gate or lasting road blockage.
HG Wi-Fi Parade music is explicitly enabled. Original city events/warps/layout
and historical IDs, saved ABI, other quests/Greg wins and mailbox stay intact.

Audited unused var4146 records full finale once; replays never reset it. Sisters
scrapbook page is read-only. Mapframe latch TEMP_A resets only staging. No normal
save/menu access during scene. Read docs/trio_pom_parade.md and tools/parade.
Source/path tests distinguish normal saved progress from emulator mid-script
snapshots; rendered parade/follower/return and real save-reload need user testing.

Validation: RELEASE build32726644 linked bytes/EWRAM255416/padded32MiB passed.
Five authored flow/geometry/history groups and actual linked-ROM14 actors,
organizer/frame/movement/memory pointers and enabled parade song passed.20 native
checks passed plus7 expected harness failures, zero unexpected; parade guards
and Greg/hats/road-trip regressions included. Keep PR2 draft/unmerged.

## Trio battle run-off: user-authorized testing (2026-10-11)

User authorized100% run-off for testing and home travel to Goldenrod for parade.
TRIO_RUNOFF_CHANCE100 is temporary; change to5 only when requested/approved.
One healthy non-egg family girl sits out an ordinary solo battle, chosen at start
before controller party IDs. Includes personal forms via existing keepsake-family
classifier, excludes boss species. At least1 singles/2 doubles starters remain.
No partner/multi/link/recorded/Frontier/Safari/tutorial/first/e-reader/Hill changes.

Read docs/trio_runoff.md. Battle-only personality/OT/family identity survives menu
reordering; duplicate family identities skipped to prevent multiple exclusions.
No HP/species/item/party removal/Box transfer/save IDs or structures altered.
IsValidForBattle/ButDead, loss detection, switching/forced random switch/reserves,
EXP eligibility, start forms, party menus/item effects and team status healing
honor absence. Intro text announces snack bag/mouse/Dad's keys; no new animation.
Common resource teardown and field return clear it for every end outcome.

New Bark home mailbox offers Goldenrod30,24 before existing island preview.
Organizer30,25 offers replayable parade; declining it offers TEST return18,12.
Declining travel returns to original dialogue. No quest reset, Badge/item grants,
island departure counts, or story visibility changes. Pory/assembly both updated.
Parade/trial/festival pacing relocation remains unimplemented/unapproved.

Validation: RELEASE32728292 linked bytes/EWRAM255432/padded32MiB passed.26 native
checks pass +7 expected harness failures, zero unexpected;9 run-off cases cover
actual intro message, lead substitution, doubles, loss, identity/reordering,
formats/forms, items and saved ABI, plus Greg/parade/Spirit Mega regressions.
Five parade source groups,12 test travel paths/two safe destinations and actual
ROM travel/helper/actor/music registrations passed. Rendered UI/real save reload
remain user tests. Keep PR2 draft/unmerged and authorized testing hooks in place.

## All family transformation items reusable (2026-10-11)

User approved making all family transformation/reversion items reusable after
an audit found6 consumed,7 reusable ordinary Items and20 reusable Key Items.
Riko's Wand/Blue Brush, Bijuu's Fish Toy/Cat Nip, Dad's Keys/Piece of Chicken
now join the shared callback's reusable exemptions; descriptions say Reusable.
All33 are reusable:13 ordinary Items and20 Key Items. Preserve their pockets,
prices, held behavior, shops/gifts, IDs, quantities and saved inventory ABI.
No pocket migration or restoration of previously consumed copies. Ordinary
stones still consume normally. Form rules and original successful/failed/cancel
routing stay. Read docs/trio_reusable_form_items.md and tools/forms validation.
The authorized100% run-off and round-trip parade/island testing remain.
Validation: all33 classification/description/history checks pass; RELEASE
32728296 linked bytes/EWRAM255432/padded32MiB and retained parade/run-off native
ROM registrations pass. Native battle behavior remains the prior26-check build;
this change adds6 consumption exemptions and descriptions only.

## Run-off fast-intro freeze repair and parade confirmation (2026-10-11)

User confirms Pom Parade works in emulator. Run-off froze after departure text
before player send-out. Fast trainer gate used an idle opponent-healthbox
callback to wait for its slide to start; added departure pages could outlast
slide, returning callback to idle and creating an endless wait. Prior battle
fixtures used recorded flags that skipped this gate. BattleIntro_ShouldWaitForHealthbox
now skips that pre-animation wait once TrioRunoff_DepartureAnnounced is true;
its caller already waits for text controller completion. No-run-off timing stays.

Production-flags regression covers all3 girls with completed/idle healthbox,
plus normal/recorded controls.27 native checks pass +7 expected harness failures,
zero unexpected.9 run-off tests with rendering enabled pass. RELEASE32728472
linked bytes/EWRAM255432, saved/33 reusable item audits and parade/travel ROM
registrations pass. Keep100% and authorized travel hooks, saves/IDs unchanged.
ManicEMU confirmation pending. Use normal in-game save before battle, not old
frozen battle snapshot. Keep PR2 draft/unmerged.

## Normal run-off rate, mailbox restoration and Olivine encore (2026-10-11)

User confirms freeze fix and parade work. Authorized normal rate:5% per eligible
battle, selecting one eligible girl. TRIO_RUNOFF_CHANCE5; explicit battle-test
opt-in stays100 to preserve deterministic intro regressions. No saved changes.
Mailbox now only original sign: remove active parade AND island offers in both
Pory/inc. Organizer test-home removed; parade remains. Keep historical island
return-mode2 support for saves already visiting the preview island.
OlivinePomParty appended IndoorOlivine clones GoldenrodHouse2 layout/4Pom ring.
New balding host6,7 in OlivineHouse2 invites optional free repeatable warp4,7;
door returns to that house's warp0. Original brothers/services/events retained.
Host: "'Cause a pom party don't stop!" Full catchphrase and sister callbacks.
Fast loop scoped to exact two party maps/Riko graphics; no saved flag changes.
Original Goldenrod party/memory remains. See docs/trio_pom_party_encore.md.

Validation: RELEASE32728960 linked bytes/EWRAM255432/padded32MiB passed.
28 focused native checks passed plus7 intentional harness failures, zero
unexpected. All100 percentage roll values checked:0-4 depart,5-99 stay.
Five parade source groups,10 island groups (retained historical return-mode2),
compiled encore actors/scripts/native exit and all33 reusable item audits pass.
Olivine encore rendered playback/save reload remains user testing. Keep PR2 draft.

## Eight optional silly family scenes (2026-10-11)

User authorized all8 ideas. Spread through quieter Johto/Kanto houses and the
unlocked squirrel cafe: Olivine Penny valet; Ecruteak Bijuu forbidden box;
Mahogany Riko barking ordinance; Blackthorn Greg Fan Club; Cianwood long-hot-dog
vendor; Pewter Pom traffic; Cerulean fishing inspection; Vermilion cafe apology.
See docs/trio_silly_scenes.md and tools/silly/locations.json for exact door/host
coordinates and source event tracing. Original residents/services/scripts kept.
One new static host appended per source, no changes to original local IDs/warps.
Cafe new clerk4,6 was checked to preserve every speaker's reachable approach.

Eight appended maps retain historical map IDs.7 automatic stages show all3 girls
plus Scott, return automatically, and are replayable without rewards/progression
writes. Greg's freely explorable room has5 talkable existing-sprite disguises
and Scott; native door returns to BlackthornHouse1. Ordinary family references
assume the girls present. Existing Box Bijuu art is an NPC-only reveal, not a
party transformation. Catch/bucket and pup cup are narrated fictional props;
Apology's moving-box prop is fictional paper. No actual items, battles or theft.

Only VAR_TEMP_A and TEMP_HIDE_FOLLOWER/TEMP_1 touched, clearing on every stage
return including failed readiness. No saved fields/flags/vars/items/species/
trainers or party edits. Maintain run-off5%, normal mailbox, all33 reusable
form items and prior parade/encore. PrepareTrioSillyActors guards7 exact maps,
spawns/checks5-10 visible actors and returns safely if missing; no movement to
newly revealed Box Bijuu. Source/native/ROM checks are not rendered playtests.
Previous CI186 ROM/artifact/docs succeeded; test canceled after runner shutdown,
not a compile failure. Keep PR2 draft/unmerged and use expected-head publication.

Validation: RELEASE32736532 linked bytes/EWRAM255432/padded32MiB passed;
29 focused native checks passed +7 intentional harness failures, zero
unexpected failures.5 new source-flow/geometry/history groups and6 existing
cafe groups passed.8 compiled guide/map registries,50 actors,7 auto-frames,
6 club speakers and every authored dialogue byte checked in actual ROM.
All33 reusable item audits, normal5% run-off/mailbox and prior parade ROM
checks passed. New rendered scene/save-reload playtesting remains for user.

## Bag freeze while looking for Riko's Wand (2026-10-12 UTC)

User's wife froze while looking in Bag to use Wand; exact action unknown.
Wand's288-byte icon and evolution selection pass native checks. Reproduced a
real shared-loader overflow: Fish Toy and Cat Nip512-byte32x32 icons decompressed
into288-byte buffer.224-byte overwrite can damage heap and manifest at a later
selection. Do not claim the exact user trigger proven without save/cursor info.

src/item_icon.c reserves512 bytes and shares bounded24x24/32x32 conversion in
standard/custom-template sprites and window blits. Standard padding unchanged;
full32x32 art copied directly. Unsupported dimensions free buffers and return
existing failure sentinel. No art, inventory/IDs/pockets/quantities/reusability/
form rules/save data changes. Only224 additional temporary heap bytes; no globals.
Old native testfailedEXPECT_GE(288,512).8 new loader/source/capacity/VRAM/window/
all-item-dimension/evolution checks pass.37 focused native passes+7 intentional
harness cases, zero unexpected. RELEASE32736364/EWRAM255432/padded32MiB passed.
See docs/trio_bag_icon_repair.md and test/trio_wand_bag.c. User Bag retest remains.
Use normal in-game save before freeze, not old frozen snapshot. Keep draft PR2.


## Three new purely cosmetic costumes (2026-10-12)

User chose cosmetic outfits with unchanged stats/types/moves. Butterfly Riko,
Astronaut Bijuu and Ballerina Penny append species1633-1636/items972-974.
Penny has ordinary and Dachsbun metadata and dressed level26 evolution.
Reusable Key Items: Riko Wings/Space Helmet/Penny Tutu. Existing raincoat,
detective and beach-vest givers offer additional optional gifts, then original
conversation; no new map objects or saved quest state. Album bits10-12 append
without changing old nine/Poison bits;12-photo count and new reactions/Scott
comments included. All family checks/Camp/signatures/Spirit return include them.
Existing elemental/other-costume forms first revert to ordinary to dress up.

Read docs/trio_new_costumes.md and tools/costumes/validate_new.py. Source atlases
are saved per species; new_render.c owns pixel conversions, import_new.py only
formats/packs bytes.48 source gift cases, old save/ID/map preservation and text/
indexed formats pass. Native tests now cover new forms but were not run locally:
ARM compiler/libpng dependencies unavailable. CI/build/actual emulator checks
remain separate. Keep Bag-icon repair, run-off5%, mailbox normal, PR2 draft.


## Permanent Halloween cosmetic costumes (2026-10-12)

User chose permanent optional gifts. Witch Riko/Vampire Bijuu/Pumpkin Penny
append species1637-1640/items975-977, female cosmetic ordinary-stage metadata.
Penny retains Fidough/Dachsbun and dressed level26 evolution. Protected reusable
Key Items are Riko Witch Hat/Vampire Cape/Pumpkin Suit, gifted before existing
raincoat/detective/beach-vest host conversations. No new map actors/date gates/
test supplies/save structures. Album bits13-15 fill existing16bit mask; no future
portrait may shift past15 without a new audited design. All15 costumes plus
Poison bonus preserve prior bit assignments; current count excludes Poison.
Native art reference atlases and C conversion follow existing workflow. Vampire
up-facing cells repaired with imagegen. See docs/trio_halloween_costumes.md and
docs/trio_costume_emulator_pass.md for all15 costume/stage restart/Box/faint/
reversion/existing-save checks. All39 form items audited reusable26 Key/13 Items;
historical inventories/pockets unchanged, lost older copies not auto-restored.
The inherited audit was updated for appended items, keeping historical numeric
IDs/inventory/save-layout checks.48 Halloween +48 prior extra gift/source/asset
checks pass; engine tests extended but local ARM/libpng dependencies unavailable.
CI build/tests and rendered emulator pass remain distinct. Keep5% run-off,
normal mailbox, Bag-icon repair and PR2 draft/unmerged.


## Ghost-led Trick-or-Treat Trail (2026-10-12)

User requested earning Halloween outfits through an optional ghost teleport
and minigame. Ecruteak Itemfinder house(city door19,33) appends Gastly9,5,
preserving original NPC/service/events. Accept -> appended IndoorEcruteak
TrioHalloweenTrail on existing garden layout.13actors+player/follower=15slots.
Gastly memory BOO/POM/TREAT -> Riko Witch Hat; Haunter Fish/Moon/Star balls
-> Vampire Cape; Duskull Left/Right/Middle Pumpkaboo -> Pumpkin Suit. Existing
Pumpkaboo family/art enabled. No battles/party/date/Badge gate. The ordinary
girls stay present. Earlier direct Halloween costume gift calls/helpers removed;
all other costume sources/earned copies/photos retained. ExitGastly warps to
house8,6; two native south-arrow exits return to house warp0. Original house
door remains normal. No temp follower restrictions, forced party edits or timers.
Audited saved vars4147-4149 append to existing array:0-2partial,3solved/pending,
4claimed. Wrong order/duplicates preserve finds; full Bag/reloads retain progress;
owned-item checks stop duplicate awards. Source interpreter3454branches plus
13actor/two-exit geometry/native behavior0x65/history/save/service/registration
checks pass. Costume art/metadata/39reusable items and48other extra gifts pass.
Local ARM/libpng unavailable; CI and actual rendered playthrough remain distinct.
See docs/trio_halloween_trail.md and extended emulator pass. Keep PRdraft.

## Authorized New Bark Halloween testing trip (2026-10-12)

User requested a fresh-save trigger from New Bark. Player-house mailbox17,11
calls TrioHalloween_TestOffer in matching rawPory/assembly. Decline returns to
original sign; accept enters trail12,15 with no party/Badge/progress/item grants.
Audited saved var414A stores origin0Ecruteak/1NewBark, set only on accepted entry.
Exit ghost and new walk-out coord events11/12,16 route to NewBark18,12 or normal
house8,6, keeping origin through actual save/reload. Mapload sets only TEMP_A1
for coord dispatch. Both old south-arrow warps stay a normal-route boundary
fallback. Original NewBark map/story state/mailbox sign and all game rewards
remain.30 additional source route/decline/reconstruction/Pory/home tile checks
pass alongside3454puzzle branches/art/39reusable items. Rendered travel/new-save
still needs emulator checks. Temporary authorized hook: remove only when asked,
retaining mode1 safe returns for saves already inside and earned progress.

## Halloween New Bark return build repair (2026-10-12)

CI192 failed in ROM event-script assembly, not runner setup. Return target was
incorrect MAP_NEWBARK_TOWN; engine registered name is MAP_NEW_BARK_TOWN.
One warp target corrected; saved map/origin/items/puzzles unchanged. Source
validator now runs production tools/mapjson groups and checks all4warp symbols
against generated constants plus historical map numbers.3454puzzle/30return
cases pass. Source-only mocked warp routing previously missed this typo.
Keep mailbox test hook/user progress/PRdraft; report rebuilt ROM separately.
