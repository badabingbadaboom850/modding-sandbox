# Trick-or-Treat Trail

A friendly Gastly waits in Ecruteak's Itemfinder house, city doorway19,33,
at interior9,5. Talk and accept an optional trip to a haunted garden with
Riko, Bijuu and Penny. No battle, fee, party, Badge or real-time requirement.
The trail remains available all year and works on existing saves.
The original Itemfinder NPC/service and all original house events remain.

## Games and rewards

| Host | Game | Prize |
| --- | --- | --- |
| Gastly9,6 | Remember BOO, POM, TREAT in that order using the word menu | Riko Witch Hat |
| Haunter14,6 | Search Fish5,8, Moon18,8, then Star18,10 treat balls | Vampire Cape |
| Duskull12,9 | Greet Left10,12, Right14,12, then Middle12,12 Pumpkaboo | Pumpkin Suit |

Each ghost explains its game. Riko's wrong memory guess permits another try;
Cancel/B stops without a prize or progress change. Bijuu and Penny keep each
correct find; wrong-order/duplicate taps leave earlier finds untouched.
Haunter and Duskull award their prizes after the corresponding trail is solved.
Riko's reward follows her successful memory answer immediately.

All prizes are protected reusable Key Items. Bag possession prevents duplicate
copies; successful receipt moves only that game's state to4. A full Bag keeps
state3 pending, and speaking to the same host later retries without another win.
Already owning a Halloween item never strips it or forces another copy.
All three prior direct Halloween gift calls/helpers are removed, leaving the
ordinary/Butterfly/Astronaut/Ballerina sources intact. Previously earned items,
forms and album photos stay valid. Games can still be completed if already owned.

Exit Gastly9,15 offers an immediate return to8,6 in the Itemfinder house.
Both bottom south-arrow warps11/12,17 return through its native entrance warp0.
The player can save, quit, return and resume searches. There is no timer,
encounter restriction, forced follower hiding, party mutation or story gate.
The three ordinary girls are present as NPCs using the established permission
to assume their company. Treat props describe fictional sweets, not real food.

## Implementation and validation

TrioHalloweenTrail appends to IndoorEcruteak without shifting any old map ID.
It reuses the proven24x18 TrioGarden layout/tilesets with13 static actors,
Burned Tower music and no new layout data. Including player/follower uses15 of16
object slots. All actors have reachable approaches; both native exits remain
reachable, with the engine's south-arrow behavior0x65 explicitly checked.
Pumpkaboo's existing family/art is enabled for the three ghost-pumpkin actors;
its historical species IDs and saved structures remain unchanged.

Audited unused variables0x4147-0x4149 in the existing saved array hold independent
Riko/Bijuu/Penny progress.0-2 mean incomplete;3 solved/prize pending;4 claimed.
No new saved arrays/flags/initialization or Badge/trainer flags. The actual
source interpreter executes3454 offer/decline/cancel/memory/partial-search/
wrong-order/duplicate/full-Bag/retry/reload branches, plus geometry, original
Itemfinder/map-group/save ABI, item-source replacement and registration/text
checks. Costume metadata/native art/reusability and48 prior extra gifts pass.

Local ARM compilation remains unavailable. CI compilation/engine tests and
actual emulator map loading/puzzles/save-reload are separate checks; do not call
this a rendered playthrough. Follow docs/trio_costume_emulator_pass.md.
Keep PR2 draft/unmerged, run-off5%, normal mailbox and Bag-icon repair.
