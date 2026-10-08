# Trio test portal and reputation pilot

This update follows the tested Riko/Elm dialogue pilot. The earlier outside-house-door shortcut produced a black screen in the user's emulator. Source warp IDs were valid; the exact runtime cause remains unconfirmed.

## Test trip

The outdoor home doorway once again enters the normal downstairs room.

Talk to **Mom's friend inside your home**. After her normal dialogue, she offers a test trip. Choose Yes to use the existing script warp command with explicit coordinates **(4,5)** in `MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM_SUICUNE`. Choose No to stay home.

To return, stand at (4,5), face north toward the entrance at (4,4), and press A. The return prompt warps to **(20,12)** in New Bark, immediately outside the home doorway. This interaction does not rely on the cave entrance having a working warp metatile.

The cave's legacy warp entry still points to New Bark warp 1. Flash remains disabled. Battle levels, object completion flags, and scripts are unchanged. Existing saves do not reset defeated spirits.

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
2. Mom's friend No stays home; Yes loads the cave.
3. Cave entrance A prompt returns outside home.
4. Elm's tested Riko beat remains intact.
5. Cherrygrove rumor and Violet before/after-badge dialogue appear.

No claim of a confirmed runtime black-screen fix should be made until step 2 succeeds.

## Restore test-only changes later

Remove the extra trip prompt/handler/text from the Mom's friend script, and remove the cave return background event and its handlers/text. Restore the cave's original warp destination `MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM` and `requires_flash: true` when normal story behavior is desired. Keep the normal home doorway, repaired terrain, and reputation dialogue.
