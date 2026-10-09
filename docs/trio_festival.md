# The Girls' Day Out

Goldenrod's optional family festival opens after the fourth Johto Badge with Riko, Bijuu and Penny in the party; the shared family checks support their approved forms. Mom supplies the location hint. Talk to the new guide at (9,5) in GoldenrodCity_PokemonCenter to enter a separate garden using the National Park scenery. Existing Center services and the original park stay intact. No wild encounter table is registered for the festival.

## Normal play build

Festival testing shortcuts are disabled (`TRIO_FESTIVAL_TEST_MODE` is 0). Fresh saves start normally with level-5 Riko and Penny, no free Badges, and Bijuu joining through her Route 31 story encounter. The previously approved Mega Ring/Bondstone startup equipment stays unchanged. New Bark's neighbor no longer offers a shuttle, and the festival host no longer offers debug return/reset tools. Normal host rest, itinerary and return-to-Center services remain.

The festival opens after the fourth Johto Badge with all three girls; Mom gives a location hint and the guide on the right inside Goldenrod's Center provides entry. Existing saves retain their party, progress, certificates and scrapbook memories. A previously created testing save retains its granted Badges and levels; use a fresh save for the normal opening.

The optional developer switch can still be re-enabled for later debugging. Numeric 1 enables the shuttle, level-30 full trio, four Badge flags and host debug tools; numeric 0 restores normal play. The validator explicitly checks both configurations rather than assuming the current build enables testing.

## Activities and locations

| Activity | Location and behavior |
| --- | --- |
| Riko's Grand Performance | Northwest lawn, (11,14). Watch her face left/right or jump and identify it three times. Wrong answers offer a gentle retry; B/Exit leaves without a ribbon. Repeatable. |
| Bijuu's mystery | Bijuu at (25,10), Lass witness at (18,10), child witness at (32,48). Hear both clues in either order, then inspect the middle of three south-path baskets at x29/31/33,y47. Clues survive leaving/saving. Wrong baskets do not advance the case. |
| Penny's Little Courage Course | Penny at (32,28). Start with her, then visit round markers north (32,26), east (34,26), south (34,28). At each marker encourage, demonstrate, or ask her sister. All supportive choices succeed. Out-of-order markers do not advance. B/Exit or leaving cancels unfinished course progress; earned ribbons remain. Repeatable. |
| Snack hunt | Aipom at (11,28) supplies the first level-27/28 battle; after victory Greedent at (30,34) offers a level-29 battle. Only real wins complete each step. Defeat/forfeit allow retry and return healed. |
| Scott's sunset match | Near entrance, (20,44). Three completed activities and recovered snacks unlock his level-32/33 team: Guardian Penny, Psychic Bijuu and Winged Riko. The player heals before and after the friendly battle. First win OR loss leads to the picnic and letter; only a win records the separate victory flag. Later visits allow a rematch. |
| Rest | Nurse (18,47), or host Rest. |
| Visitor | (25,31); dialogue expands for each earned ribbon. Witness dialogue changes after Bijuu's case. |

Riko's Big Voice, Bijuu's Tiny Detective and Penny's Brave Heart ribbons are saved festival certificates displayed in host itinerary and Trio Camp's stats shelf. They are not new inventory items or Pokémon contest-ribbon fields. Mom's Scrapbook adds the festival picnic and Scott letter under Sister moments; its checklist supplies the guide hint before completion. Recorded memories require no current party to read. Existing saves qualify naturally when they meet the Badge/party gate.

## Implementation and verification

The new map is appended to gMapGroup_IndoorGoldenrod, preserving all prior map IDs, and shares LAYOUT_NATIONAL_PARK_NORMAL. It has independent NPCs/events, no original park callbacks or trainer sightings. Its original scenery exits all return to Goldenrod's Center. The host also supplies explicit-coordinate return warps. Seventeen templates are distributed through the garden; decoded geometry checks show all objects have a reachable approach and the conservative viewport count plus follower is below the engine's sixteen-object budget.

Persistent flags 0x1071-0x107A were audited free against source/header/map/script uses. Save array sizes remain fixed. Map-local VAR_TEMP_B/C store Riko's round/random move; D/E store Penny's checkpoint/active latch and reset on entry. Trainer slots 1159-1161 previously named UNUSED_295-297 are reused without expanding trainer flag storage. Their authoring entries live in trainers.party. Scott's other rival encounters and the original TRAINER_SCOTT fisherman remain untouched.

Friendly trainer returns are guarded by BOTH the festival map and one of the three new trainer IDs in CB2_EndTrainerBattle. This heals and resumes the script after victory, loss or forfeiture without setting persistent global whiteout/catching restrictions. Ordinary trainer callbacks retain their original paths. Scripts check the real outcome immediately after battle. No caught Pokémon, prize item consumption or Bag-capacity-sensitive rewards are introduced.

Run `python tools/festival/validate_festival.py` for ten regression groups covering actual source-flow branches, decoded walkability/reachability/viewport budgets, cancellation/retry, clue order, supportive choices, picnic endings/replay, reset isolation and text references/wrapping. This interpreter does not emulate graphics or battle execution. ROM compilation and GitHub CI are separate checks. Interactive testing must still confirm map rendering, Riko's visual cues, cushion markers, follower behavior, locks after menus/warps, both battle outcomes and save/reload. Disable test mode and check a normal fresh save before release.

Local verification for this implementation: the full Soulgold ROM compiled successfully. The targeted headless engine suite completed with 41 passing tests and 7 expected failures belonging to runner self-tests (48 total); it includes the actual fresh-save initialization test, Camp, Spirit and Bag tests. The ten festival source-flow/geometry groups and inclusive docs validation passed. This does not establish rendered festival playtesting or the remote CI result.

The test-mode switch uses numeric 1/0 because event-script CPP does not define the C TRUE/FALSE macros. The validator also checks enabled/disabled prompts through real preprocessing (eleven groups total).

Snack custody battle repair: the Skwovet/Greedent family must be enabled in species_enabled.h; disabled family data previously caused Greedent to appear unknown and crash when entering battle. This repair does not change the trainer ID, event object, completion flags, or save layout. Existing test saves can retry with the updated ROM. test/trio_festival.c checks required data for every festival species and creates the level-29 boss through the engine.
