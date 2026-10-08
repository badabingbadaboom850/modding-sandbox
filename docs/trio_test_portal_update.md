# Spirit encounter tests and cleanup

This update follows the tested Riko/Elm dialogue pilot. The earlier outside-house-door shortcut produced a black screen in the user's emulator. Source warp IDs were valid; the exact runtime cause remains unconfirmed. The user also reported a black screen after the terrain repair and explicit-coordinate portal in commit 79cb54.

## Mom's friend behavior and test travel

Mom's temporary cave, direct-battle, and upstairs control prompts have been removed. Her original visitor dialogue is restored, and the house transition no longer forcibly unhides her on existing saves. Her original story-stage placement logic remains.

The outdoor home doorway still enters the normal downstairs room. The cave's test return interaction and diagnostic map settings remain while its black-screen issue is unresolved. The previous upstairs control test worked; the cave load still failed.

## New Bark encounter test (retired)

The three temporary mailbox triggers have been removed and their normal sign scripts restored after the user confirmed the Spirit battles worked and had the expected difficulty. Their battle setup remains shared with the real cave encounters in `data/scripts/trio_spirit_trials.inc`.

The cave encounters still set their real completion flags on the original win/catch paths. The New Bark mailbox tests were only a way to reach the battles while the cave remained inaccessible; their successful battles do not prove cave loading, object movement, or cave-specific terrain behavior.

### Catching configuration correction

The old scripts set `FLAG_SYS_NO_CATCHING`, but `B_FLAG_NO_CATCHING` in `include/config/battle.h` was `0`. The engine configuration now points to the existing `FLAG_SYS_NO_CATCHING`; no flag slot is allocated.

Each noncatchable shared setup clears the flag when the battle returns. Defeat follows ordinary whiteout; `DoWhiteOut` calls `Overworld_ResetStateAfterWhiteOut`, which calls `Overworld_ResetBattleFlagsAndVars` with the enabled reset option and clears `B_FLAG_NO_CATCHING`. This prevents the catching restriction from persisting after a loss. This configuration also makes other scripts using that same legacy flag enforce their intended restriction.

The shared setups call the stat helpers directly. Their original scratch-flag guard was always set immediately before the call; removing that redundant guard preserves the call and avoids leaving `FLAG_GARBAGEFLAG` set when whiteout skips the script tail.

## Cave callback isolation and control-teleport test history

The cave's transition and resume registrations remain disabled; the transition handler is retained but unregistered. The original cave return interaction, layout, terrain repair, and portal coordinates remain. Snow remains disabled. These are temporary diagnostics and have not fixed cave loading.

The bypassed handlers are `ShoalCave_LowTideIceRoom_Suicune_OnTransition` (which calls `SetTimeBasedEncounters`) and `SetTimeEncounters`. Their native behavior remains unverified, so this diagnostic may affect time-based encounters.

The upstairs control teleport was a temporary option from Mom's friend and is now removed. The user confirmed the bedroom loaded correctly. The cave still blackscreened, so the ordinary scripted warp path itself is not the cause.

## Earlier snow isolation

The preceding isolation changed only the cave's weather setting from `WEATHER_SNOW` to `WEATHER_NONE` in this pass. Its terrain, objects, transition/resume callbacks, popup, and portal coordinates are retained.

`Snow_InitAll` in `src/field_weather_effect.c` contains a blocking loop until the snow graphics are loaded. Loading requires the snowflake count to reach its target; `CreateSnowflakeSprite` can fail at `MAX_SPRITES`, leaving the count unchanged, and that failure is ignored by the update loop. This is a concrete conditional hang risk, not proof that this map exhausts sprite slots.

The user reported that version still failed. Disabling snow alone was therefore insufficient; the current pass targets map callbacks. Local emulator execution is unavailable.

## Direct battle test history

Mom's friend temporarily offered a level 70 catchable Spirit battle with Charcoal. That prompt is removed with the other test options. The user confirmed the direct battle worked; the test did not load the cave or set cave completion flags.

## Penny comfort interaction

When the existing regular Mom/healing branch runs, she reassures Penny if `SPECIES_FIDOUGH` is in the party. Both the present and absent paths retain the original shared healing call. First-visit story dialogue, its rewards, and Mom's progression dispatch remain intact. This is a repeatable character moment, not yet a persistent bravery quest.

## Terrain repair

The engine uses `MAPGRID_METATILE_ID_MASK = 0x07FF` and 1024 primary metatile slots. The assigned `gTileset_General` actually contains 531 metatiles, and `gTileset_Cave` contains 414.

The room's binary layout contained primary tile references **631 at (4,7)** and **639 at (7,7)**. Both exceed the General tileset's actual entries. Reading their attributes/render data would go beyond the assigned table.

These two cells now use **1281**, the same registered Cave floor metatile used at neighboring cells (secondary index 257). Their collision and elevation bits are preserved. All 1600 room cells now reference entries within the assigned tileset tables.

This repairs a verified source defect; it does not prove those cells caused the black screen. The script portal also bypasses the previous doorway-entry path and indexed landing tile. An emulator test is still required.

## Reputation dialogue

- Cherrygrove boy at (45,15): existing Pokédex-dependent dialogue adds a rumor of Bijuu racing a Pidgey.
- Violet boy at (28,25): existing trio rumor stays before the first badge. After `FLAG_BADGE01_GET`, he recognizes the Falkner victory and shares pet gossip.

Only existing flags and NPCs are used. Rumors do not assume the player owns all three pets. Both authoring `.pory` and corresponding raw `.inc` sections are updated.

## Verification

The user confirmed the temporary New Bark mailbox battles worked and had the intended difficulty, and that the Wand and Blue Brush changed Riko's form correctly. The mailbox redirects have been removed. The room control warp worked; the cave still blackscreens.

For the current build, verify the ordinary Mom's friend dialogue, that the three New Bark mailboxes show their original sign text, and that the form items can be bought on Goldenrod Department Store 4F. Test store purchases with an existing save. Fresh-save starting item changes only apply to newly started games; the existing Route 30 pickup remains available.

## Remaining cave diagnostics

The temporary Mom's friend prompts and forced visibility override are removed. The three New Bark mailbox signs are restored. Cave diagnostics remain: the transition/time callbacks are unregistered, snow is disabled, terrain IDs are repaired, and the cave return event remains. The cave's exact black-screen cause is still unknown. Restore the cave callbacks and snow only when testing the next cave-loading hypothesis. Keep the ordinary home doorway, restored Mom's friend dialogue, reputation dialogue, and shared cave battle setup.

## Riko form items at Goldenrod Department Store

The temporary Mom's friend restock has been removed. Riko's Wand and Blue Brush are stocked at **Goldenrod Department Store, 4F**, with the existing vitamin shop. Each costs **₽500**. Both remain in the Bag's **Items** pocket, and their evolution behavior is unchanged. The Wand and Brush are no longer granted in fresh-save inventory; the Route 30 pickup remains.

The user confirmed the Wand evolves Riko and the Brush restores her original form. Buying another copy allows the forms to be changed again after using an item.



## First-round trio field notes and Penny's confidence

The field-note sidequest starts with the existing Cherrygrove boy after the Pokédex is received, while a trio member is in the party. The Violet City boy near the Academy adds a short local report after the first Badge; returning to Cherrygrove completes it for one Wawa. The state advances only after each step succeeds, so a full Bag leaves the reward available for a later visit.

Mom's normal healing remains intact. With Penny (Fidough) in the party, the first confidence moment appears after the first Badge and recognizes her rescue gently without retelling it. After the second Badge, having both Riko and Bijuu in the party lets Mom describe Penny choosing a small hello with her sisters nearby. If the Bag is full, the Wawa remains available. These conversations use existing map NPCs and add no warps or new objects.

Party checks account for every declared Riko and Bijuu form because the engine compares exact species IDs. Riko Spirit is excluded as its own species. The confidence quest advances from Badge flags and party members rather than repeated conversation counts.


## Broad trio reputation dialogue pass

Adds 183 expanded dialogue entries across 44 map scripts, plus 19 badge-dependent rumor variants. Residents in all 20 main Johto/Kanto towns have pet-specific conversation; Cinnabar's persistent residents are in its Pokemon Center. Existing directions, services, quest hooks, visibility rules, and map objects remain. Goldenrod has both civilian and Rocket chatter for the takeover stage. The trainer and all three girls are assumed present by the user's design.

Stories vary between local sightings, individual preferences, affectionate jokes, the mysterious trainer's travels, and respect for Gym Leaders who stood their ground. Rumors about completed Gym matches are gated by their corresponding Badge flags. Early and later New Bark conversations are both covered. Additional route dialogue covers 26, 27, 32, 45, and 46, including pre-battle trainer conversations.

All 16 Gym Leaders receive distinct intro, defeat, and return-visit additions. Existing rematch messages in the gyms are updated, and all 16 leaders' rematch introductions and defeat lines in Saffron's Fighting Dojo VIP are covered. No new battles or rematch systems are introduced.

Validation: original labels and gameplay commands preserved, new branch labels unique and resolved, authoring raw blocks match their assembly counterparts, and new dialogue lines are conservatively wrapped to 26 characters with two lines per page. Reconciles older Goldenrod/Ecruteak authoring quote and ellipsis mismatches with the assembly. ROM CI and emulator checks remain required.

In-game spot checks: talk to Violet's lass before/after Falkner, Azalea's teacher before/after Bugsy, Goldenrod's gramps before/after Whitney and a Rocket during takeover, and Cinnabar Pokemon Center's resident before/after Blaine. Check leaders on first challenge, immediately after defeat, return visits, and later dojo rematches. Rumor variants follow actual Badge flags; they do not claim the local leader has already lost on a first visit.
