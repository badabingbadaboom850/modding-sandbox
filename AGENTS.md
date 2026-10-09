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
