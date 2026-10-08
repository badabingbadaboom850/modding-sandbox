# Trio test portal and reputation pilot

This update follows the tested Riko/Elm dialogue pilot. The earlier outside-house-door shortcut produced a black screen in the user's emulator. Source warp IDs were valid; the exact runtime cause remains unconfirmed. The user also reported a black screen after the terrain repair and explicit-coordinate portal in commit 79cb54.

## Test trip

The outdoor home doorway once again enters the normal downstairs room.

Talk to **Mom's friend inside your home**. While this test portal is installed, the house transition explicitly clears her hide flag at every story stage, so she remains available on existing saves. After her normal dialogue, she offers a test trip. Choose Yes to use the existing script warp command with explicit coordinates **(4,5)** in `MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM_SUICUNE`. Choose No to skip travel and receive a second optional prompt for a direct Spirit Riko battle. Choose No again to receive the optional upstairs control-teleport prompt. Decline all three prompts to stay home without battling or traveling.

To return, stand at (4,5), face north toward the entrance at (4,4), and press A. The return prompt warps to **(20,12)** in New Bark, immediately outside the home doorway. This interaction does not rely on the cave entrance having a working warp metatile.

The cave's legacy warp entry still points to New Bark warp 1. Flash remains disabled. The cave battle levels and object completion flags remain unchanged. Existing saves do not reset defeated spirits.

## New Bark mailbox encounter tests

The user confirmed the upstairs control teleport works, while the cave still blackscreens with weather and time callbacks disabled. The direct standard Spirit battle works too. The cave's remaining runtime failure is unresolved.

Three existing mailboxes now launch tests:

| Mailbox | Map coordinate | Encounter | Completion flag |
|---|---|---|---|
| Player's home | (17,11) | Level 90, cannot catch | `FLAG_SUICUNE_BATTLE_1` |
| Elm's home | (12,21) | Level 80, cannot catch | `FLAG_SUICUNE_BATTLE_2` |
| Rival's home | (12,29) | Level 70, catchable, Charcoal | `FLAG_DEFEATED_SUICUNE` |

Stand beside the mailbox and press A. Each prompt identifies its trial and asks permission to start. Completed trials display a completion message. No new NPCs, sprites, flags, or map layouts are added.

Both the real cave callers and the mailbox callers use the same three setup subroutines in `data/scripts/trio_spirit_trials.inc`, included immediately after the cave scripts in `data/event_scripts.s`. These subroutines contain the original cries, levels, item, music setup, stat-helper calls, battle launch mode, and outcome retrieval. Cave callers retain their own departure movement and object removal; mailbox callers do not move or remove town objects.

The final mailbox uses the original legendary-battle setup, unlike Mom's friend's simple direct-battle fallback. The final trial does not require earlier completion flags, matching the original cave scripts.

**Use a test save.** Winning either early trial sets its real cave completion flag. Winning or catching the final spirit sets the real final flag; capture also adds a Pokémon normally. Those flags hide the corresponding cave objects when that room is eventually usable. There is no reset command in this patch.

The setup routines share code, so successful town tests provide evidence for battle setup, catching restrictions, outcome branching, and saved progress. They do not prove the cave loads, that its overworld sprites/puzzle/departure paths work, or that cave-specific battle terrain behaves correctly.

### Catching configuration correction

The old scripts set `FLAG_SYS_NO_CATCHING`, but `B_FLAG_NO_CATCHING` in `include/config/battle.h` was `0`. The engine configuration now points to the existing `FLAG_SYS_NO_CATCHING`; no flag slot is allocated.

Each noncatchable shared setup clears the flag when the battle returns. Defeat follows ordinary whiteout; `DoWhiteOut` calls `Overworld_ResetStateAfterWhiteOut`, which calls `Overworld_ResetBattleFlagsAndVars` with the enabled reset option and clears `B_FLAG_NO_CATCHING`. This prevents the catching restriction from persisting after a loss. This configuration also makes other scripts using that same legacy flag enforce their intended restriction.

The shared setups call the stat helpers directly. Their original scratch-flag guard was always set immediately before the call; removing that redundant guard preserves the call and avoids leaving `FLAG_GARBAGEFLAG` set when whiteout skips the script tail.

### Mailbox test checklist

1. Decline each trial and verify normal movement resumes.
2. Check levels 90/80 and that a Poké Ball is refused.
3. Run from an early trial and verify it remains available.
4. Lose a trial and check recovery plus catching in a later ordinary encounter.
5. Win an early trial and verify its mailbox reports completion.
6. Test the final legendary encounter: catch/win completes it, running does not.
7. Save/reload and verify completion persists.
8. Recheck the independent direct battle and upstairs control trip.

The mailboxes replace ordinary mailbox text temporarily. Restore their original scripts when testing ends:
- (17,11): `NewBarkTown_EventScript_PlayersHouseMailbox`
- (12,21): `NewBarkTown_EventScript_ElmsHouseMailbox`
- (12,29): `RivalsMailbox`

Keep the shared battle subroutines/include if the cave callers continue using them. Restoring the mailbox text does not undo flags or captures already saved.

## Earlier callback isolation and control teleport

The user confirmed the direct Spirit Riko battle works, while the snow-disabled cave trip still blackscreens. This confirms the standard battle path and its graphics can load; static overworld Spirit graphics remain a separate unverified path.

This pass removes only the cave's transition and resume registrations from its map-script table. The table now contains just the terminating byte. The original transition handler is retained for rollback but is no longer registered. The cave entrance coordinate event, object battle scripts, return interaction, layout, terrain, and portal coordinates stay intact. Snow remains disabled.

The handlers being bypassed are `ShoalCave_LowTideIceRoom_Suicune_OnTransition` (which calls `SetTimeBasedEncounters`) and `SetTimeEncounters`. Their full native implementation has not been located or verified, so this is a temporary diagnostic that may affect time-based encounters, not a confirmed root-cause fix.

After declining both the cave trip and direct battle, Mom's friend offers a **control teleport to the upstairs bedroom at (4,4)**. It uses the same ordinary scripted warp and waitstate pattern as the cave trip, with a destination that already loads at the start of a fresh game.

Test interpretation:
- Upstairs works, cave works: the disabled cave callbacks are a leading suspect.
- Upstairs works, cave still fails: next inspect cave object graphics and map rendering/loading.
- Upstairs also fails: investigate the shared scripted-warp path or whether the intended new ROM is running.

Restore the two original map-script registrations after their behavior is understood. This test does not alter the cave's persistent completion flags.

## Earlier snow isolation

The preceding isolation changed only the cave's weather setting from `WEATHER_SNOW` to `WEATHER_NONE` in this pass. Its terrain, objects, transition/resume callbacks, popup, and portal coordinates are retained.

`Snow_InitAll` in `src/field_weather_effect.c` contains a blocking loop until the snow graphics are loaded. Loading requires the snowflake count to reach its target; `CreateSnowflakeSprite` can fail at `MAX_SPRITES`, leaving the count unchanged, and that failure is ignored by the update loop. This is a concrete conditional hang risk, not proof that this map exhausts sprite slots.

The user reported that version still failed. Disabling snow alone was therefore insufficient; the current pass targets map callbacks. Local emulator execution is unavailable.

## Direct battle fallback

Mom's friend's second prompt starts a normal scripted wild battle with `SPECIES_RIKO_SPIRIT`, level 70, holding Charcoal, directly from the house. It uses existing `setwildbattle` and `dowildbattle` commands without loading the cave or invoking the cave's custom event scripts.

The encounter is catchable under normal catching rules; catching adds the Pokémon to the party/PC. This is repeatable testing and does not set any Suicune/Spirit completion flags or hide cave objects. It does not reproduce the cave's staged fights, special legendary setup, puzzle, or entrance event. Losing follows the existing scripted battle loss/whiteout behavior. The player's save may still be affected by ordinary battle/capture results.

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

Source checks: JSON parses; portal coordinate destinations are in bounds and unoccupied; return tile is directly south of the existing doorway; binary terrain IDs are in range; new labels are unique; authoring/generated additions agree.

CI compilation and in-game tests remain required:
1. Home doorway enters normally.
2. Accept Mom's friend's cave trip and check whether it loads.
3. Decline the cave trip and battle, then accept the upstairs control teleport; check the bedroom and normal stairs.
4. Cave entrance A prompt returns outside home.
5. Decline travel, accept the direct battle, and check its battle/capture behavior.
6. On a regular repeat Mom visit, verify Penny's comfort line and normal healing; repeat without Penny.
7. Elm's tested Riko beat remains intact.
8. Cherrygrove rumor and Violet before/after-badge dialogue appear.

No claim of a confirmed runtime black-screen fix should be made until step 2 succeeds.

## Restore test-only changes later

Remove the unconditional hide-flag clear added to the house transition and the extra trip, direct-battle, and control-teleport prompts/handlers/text from the Mom's friend script, and remove the cave return background event and its handlers/text. Restore the cave's original warp destination `MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM` and `requires_flash: true` when normal story behavior is desired. Restore `weather: WEATHER_SNOW` only after investigating the loading failure. Keep the normal home doorway, repaired terrain, and reputation dialogue.

## New Bark form-item restock

Speak to Mom's friend downstairs in the player's house. Before the existing portal/battle/control dialogue, she checks for Riko's Wand and the Blue Brush in the Bag and grants one of each missing item. Both belong in the **Items** pocket, not Key Items. The checks are independent, so a full Bag after the first grant can be retried without duplicating that item. A full Bag displays an explicit message; no success flag is recorded.

This temporary test aid works on existing saves without a new flag or save migration and can replenish items consumed during form-change tests. It does not give extra copies while an item is already in the Bag. Items held by Pokémon or stored in the PC are outside this Bag check.

The source still grants both items in fresh-save initialization (`src/new_game.c`) and retains the Route 30 pickup. Those facts do not establish why a particular tested save lacked them; verify the ROM commit and inspect the Items pocket. Do not reset a save solely to obtain them.

Validation: speak to Mom's friend with neither item, with both items, with only one item, and with a full Bag. Confirm the Items pocket, use the Wand on Riko and the Brush on RikoWing, then speak to her again to restock consumed items.
