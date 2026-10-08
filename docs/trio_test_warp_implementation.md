# Temporary New Bark Town ↔ Suicune cave test warp

This guide explains the shortcut implemented in [gameplay commit bfffe81](https://github.com/badabingbadaboom850/modding-sandbox/commit/bfffe8175638d01496038c75004e101bc6ab89a6) on `feat/riko-bijuu-mega-forms`. Its parent is `724570bfcb4268d48837a76d8f751d77ca4e8318`. The documentation lives separately on `docs/trio-modding-reference`; building that documentation branch alone does not include the shortcut.

The player's **own front door in New Bark Town** now leads to the existing Suicune encounter room, whose current encounters are Spirit Riko. The room's existing exit leads back to that same doorway. Flash is disabled for this test room. This is a temporary development shortcut, not a change to normal story progression.

## 1. The exact implementation

Only three field values changed, across two map JSON files. No entries were inserted or reordered.

| Source file | Field | Before | After |
|---|---|---|---|
| `data/maps/NewBarkTown/map.json` | `warp_events[1].dest_map` | `MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_1F` | `MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM_SUICUNE` |
| `data/maps/ShoalCave_LowTideIceRoom_Suicune/map.json` | `warp_events[0].dest_map` | `MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM` | `MAP_NEW_BARK_TOWN` |
| Same cave file | `requires_flash` | `true` | `false` |

The New Bark entry at **array index 1** now reads:

```json
{
  "x": 20,
  "y": 11,
  "elevation": 0,
  "dest_map": "MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM_SUICUNE",
  "dest_warp_id": "0"
}
```

The cave entry at **array index 0** now reads:

```json
{
  "x": 4,
  "y": 4,
  "elevation": 0,
  "dest_map": "MAP_NEW_BARK_TOWN",
  "dest_warp_id": "1"
}
```

Keep these entries in their original positions inside `warp_events`. The snippets are entries, not complete replacement map files. Both `dest_warp_id` values were already correct for the shortcut and were left unchanged.

## 2. How warp destinations work

A warp has two sides: a trigger on the source map and an arrival point on the destination map.

| Field | Meaning here |
|---|---|
| `x`, `y` | This entry's position on its own map, in map tiles. |
| `elevation` | The source warp's elevation; retain the working value when reusing an entrance. |
| `dest_map` | Destination map constant, matching that map JSON's `id`. |
| `dest_warp_id` | Zero-based index of an entry in the destination map's `warp_events` array. Preserve the repository's string representation. |

For the outbound trip, New Bark's doorway points to **cave warp 0**. That cave entry is at **(4,4)**, so the player arrives there. For the return trip, cave warp 0 points to **New Bark warp 1**, which is at **(20,11)**.

The index is not an NPC's local ID, a route number, a map enum number, or an arbitrary coordinate. Index `"0"` means the first warp entry; `"1"` means the second.

This behavior is confirmed in `src/overworld.c`, function `SetPlayerCoordsFromWarp`: when the destination warp index is valid, the engine takes the player's position from that destination entry's `x` and `y`. Invalid indices fall back to explicit coordinates or the center of the map. A JSON file can parse successfully while still having a wrong destination index.

Changing the outbound destination does **not** automatically change the return trip. Each direction needs its own source entry.

## 3. Why this particular entrance was chosen

The fresh game starts upstairs in `MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F` at (4,4). Its stairs and the downstairs exit were preserved:

| Step | Source | Destination |
|---|---|---|
| Start | Player's bedroom | Upstairs at (4,4) |
| Go downstairs | 2F warp 0 at (9,2) | 1F warp 1 at (10,2) |
| Leave home | 1F warp 0 at (9,8) | New Bark warp 1 at (20,11) |
| Enter home from outside | New Bark warp 1 at (20,11) | Cave warp 0 at (4,4) |
| Leave the cave | Cave warp 0 at (4,4) | New Bark warp 1 at (20,11) |

The shortcut uses existing warp positions instead of inventing an arrival tile. No cave object occupies (4,4) in the reviewed map JSON. Tile collision and actual movement still need emulator verification.

Entering the house from outside temporarily leads to the cave rather than the downstairs room. The cave's normal exit into the adjoining ice room is temporarily replaced too.

## 4. How to test it

1. Build or download a ROM from `feat/riko-bijuu-mega-forms` at **bfffe81 or a later commit that retains this change**.
2. Start a fresh save for untouched encounter flags.
3. Walk downstairs, leave your house, then walk back into your own front door from outside.
4. Confirm arrival in the Suicune/Spirit Riko room at its existing entrance.
5. Test the exit and verify return to New Bark Town.
6. Test the encounter you need, recording which spirit and which battle outcome you used.

A fresh save is useful for event state; an existing save can use the doorway too, but completed encounters remain completed. Entering the cave does not reset flags.

This shortcut provides access only. It does not grant Strength, change boulders or collision, supply a stronger party, change battle levels, or unlock other story events. The room's existing puzzle may still affect access to a particular spirit.

## 5. What the encounter room currently does

The inherited name “Suicune” remains in map and flag identifiers. It does not mean these objects still battle ordinary Suicune. The current scripts in `data/maps/ShoalCave_LowTideIceRoom_Suicune/scripts.inc` run the Spirit Riko encounters.

| Encounter | Object position | Script suffix | Level | Persistent completion flag |
|---|---|---|---|---|
| First | (20,12), local ID 7 | `RikoSpiritBattle1` | 90 | `FLAG_SUICUNE_BATTLE_1` |
| Second | (7,25), local ID 8 | `RikoSpiritBattle2` | 80 | `FLAG_SUICUNE_BATTLE_2` |
| Final | (5,15), local ID 1 | `RikoSpiritFinalBattle` | 70 | `FLAG_DEFEATED_SUICUNE` |

Full labels begin `ShoalCave_LowTideIceRoom_Suicune_`. The first two fights disable catching and remove their object after victory. The final encounter is catchable, holds Charcoal, and removes its object after victory or capture. The shortcut changes none of these scripts.

The entrance coordinate event is at **(8,8)** and checks `VAR_SUICUNE_EVENT == 0`; it runs the entrance howl and sets the variable to 1. Merely landing at (4,4) does not place the player on that trigger.

The reviewed battle scripts do not enforce a global late-game story prerequisite or require the earlier spirit flags before the final battle. Their objects use the completion flags above to hide defeated encounters. The warp itself does not add sequencing or reset logic.

## 6. Common reasons a warp edit appears broken

| Symptom or mistake | What to check |
|---|---|
| Door still enters the house | Confirm the ROM was built from the gameplay commit containing the change. A different branch, old artifact, or already-loaded ROM can have old map data. |
| Changed a similarly named map | Follow the actual source map's `id` and `warp_events`; consult the [progression reference](trio_progression_reference.md). This game starts in New Bark, not an inherited Hoenn town or Route 120. |
| Edited a backup or generated file | Edit the active `data/maps/<directory>/map.json`, not a `.bak` file or generated header. |
| Arrives in the wrong place | Check the destination map's warp array and zero-based index. Do not count from 1 or use NPC local IDs. |
| Other entrances change unexpectedly | Look for inserted, deleted, or reordered warp entries; incoming links depend on their indices. |
| Can enter but cannot return | Check the destination room's outbound warp separately. |
| Room is dark | Verify `requires_flash` in the room's active JSON. This shortcut explicitly sets it to false. |
| Spirit is missing | Inspect the save's encounter completion flags. A warp does not respawn defeated objects. |
| Can reach the room but cannot test the fight | Check party strength, boulders, Strength requirements, collision, and object scripts separately. |

A map JSON edit does not require a new `.pory` script. Build-generated map data must come from the modified JSON. Preserve valid JSON syntax, the existing map IDs, array order, and the existing field types.

## 7. Validation and remaining checks

Completed source checks for bfffe81:

- Parsed both map JSON files before and after editing.
- Checked the original doorway and cave exit positions and destinations before replacing them.
- Verified each destination map ID and target warp index, including the return path.
- Checked that the arrival warp has no object at the same coordinates in the cave JSON.
- Confirmed that exactly the three fields in section 1 changed.
- Read back the committed files and compared them with the intended content.

These checks establish the source wiring. They do not establish in-game movement, puzzle traversal, battle behavior, or emulator compatibility.

At the documentation check on October 8, 2026 UTC, [Actions run 37715243431](https://github.com/badabingbadaboom850/modding-sandbox/actions/runs/37715243431) for bfffe81 was still in progress. A successful ROM artifact and emulator walkthrough were not yet confirmed. Check the run before using its ROM.

## 8. Restore the normal entrances

Reverse only these three fields in the gameplay source:

| Field | Restore to |
|---|---|
| New Bark `warp_events[1].dest_map` | `MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_1F` |
| Cave `warp_events[0].dest_map` | `MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM` |
| Cave `requires_flash` | `true` |

Keep New Bark's `dest_warp_id` as `"0"`, the cave's as `"1"`, and retain every entry's original coordinates and array position. Rebuild the ROM.

Alternatively, revert commit bfffe81 if its patch still applies cleanly. If later edits touch these fields, inspect those changes before reverting so their intended destinations are preserved. The revert does not undo battle results already stored in a save.

## 9. Handoff for the next agent

> Work on gameplay branch feat/riko-bijuu-mega-forms. The temporary shortcut was introduced by bfffe8175638d01496038c75004e101bc6ab89a6. NewBarkTown/map.json warp_events[1] at (20,11) targets MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM_SUICUNE, warp "0". The cave's warp_events[0] at (4,4) targets MAP_NEW_BARK_TOWN, warp "1". The cave requires_flash is false. Preserve warp array order, the normal bedroom spawn, and the downstairs exit. No event flags reset on entry; battles remain levels 90/80/70. Before making further changes, inspect the current branch head and validate both directions. Restore the three original values above when the test shortcut is no longer needed.

Related references: [items and species](trio_modding_reference.md), [progression and map identity](trio_progression_reference.md).
