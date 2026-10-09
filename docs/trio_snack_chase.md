# The Great Snack Chase

After Whitney's Badge, enter Route 37's southern path (cross row 34 at x=12–15), or speak to the Greedent just north of it. It swipes one real Berry from the Bag, runs north, and hides in the northern grass at (17,19), just above the ledge. Find and talk to it there; it flees again to (32,23), beside the eastern Berry tree. Accept the level-22 Greedent battle to recover the snack. The route sign repeats the current trail hint.

The event happens once per save and is separate from the Goldenrod festival. Advanced existing saves can trigger it by visiting the southern path; no new save or startup shortcut is needed. The pursuit has no timer and can be left unfinished while the player travels elsewhere.

## Item custody and battle returns

The helper prefers an Oran Berry (Chicky), then checks other Bag Berries in item order. It removes exactly one and stores its actual ID in a persistent save variable. Medicine, held items, key items, evolution items and other pockets are never candidates. With no Berries, the narrative picnic snack is stolen; this fallback removes or grants no inventory item.

Declining the final battle leaves Greedent waiting. Defeat heals and returns to the same field script, with the snack still recoverable by winning a retry. This friendly callback requires both Route 37 and the exact new trainer ID; other battles retain their existing behavior. Trainer battles prevent capturing without changing a global catching/whiteout flag.

Winning advances to return-pending before attempting to add the item. If its Bag stack/pocket is full, Greedent waits at the Berry tree until there is room; another battle is not required. The stolen ID is cleared and the chase completes only after successful return. Replays, repeated interactions and repeated helpers cannot duplicate or steal another item.

Completion records **The Great Snack Chase** in Mom's Scrapbook → Sister moments. Memory checklist gives saved status or the current location hint. Reading a memory or hint does not change custody or stage.

## Implementation

- `VAR_TRIO_SNACK_CHASE_STATE = 0x4125`: 0 untouched, 1 northern grass, 2 Berry grove, 3 won/return pending, 4 complete.
- `VAR_TRIO_SNACK_STOLEN_ITEM = 0x4126`: exact removed item, or ITEM_NONE for the picnic fallback.
- Visibility flags 0x1085–0x1087 derive from the stage on Route 37 transition.
- New objects 13–15 append to the original twelve. Only the relevant thief is visible; original story/trainer objects, coordinates, connections and signs remain.
- Trainer 1162 replaces an unused slot; trainer counts and save arrays remain unchanged. Greedent's enabled species family is retained.
- Route 37 Pory/assembly callbacks preserve time encounters and add visibility refresh. The original sign retains its directions and adds a trail hint.

## Verification

Six actual-script/decoded-map groups in `tools/snack/validate_chase.py` cover entry gating, chase advancement, decline/loss/win, full-Bag return without another battle, hints/replay, safe follower flag cleanup, original events, reachable objects and escape paths, viewport budget, Pory synchronization, text and registration.

Five actual engine tests in `test/trio_snack_chase.c` cover one-item removal, other-Berry and empty-Bag cases, exact return, filled-stack retry, duplicate prevention, persistent visibility and the narrowly scoped friendly-battle predicate. The targeted suite passed 22 tests plus 7 expected test-runner self-test failures (29 total), including existing Camp/festival/normal-start checks. The local ROM compiled successfully. Existing six Scott, six Camp and eleven festival source groups and docs validation pass.

Rendered playtest still needed: walk across the southern trigger after Whitney, observe both fleeing animations, find each hiding spot, decline/lose/retry/win, fill the stolen Berry stack before recovery, leave and save/reload at each stage, and check the route sign and scrapbook. Also check the original twin/Greg encounters and Ecruteak entry event. Source and headless tests are not rendered emulator confirmation; remote CI is separate.
