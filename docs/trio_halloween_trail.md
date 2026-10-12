# Trick-or-Treat Trail

A friendly Gastly waits in western Olivine Cafe, city doorway8,43, at
interior1,6. The normal invitation unlocks after Chuck's fifth Badge
(FLAG_BADGE05_GET), on the way to Jasmine's sixth Badge. Before that, Gastly
explains when to return. Talk and accept an optional trip to a haunted garden
with Riko, Bijuu and Penny. No battle, fee, party or real-time requirement.
The trail remains available all year and works on existing saves. The earlier
Ecruteak ghost is removed; the original Itemfinder/cafe services remain.

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

Exit Gastly9,15 and both walk-out exits11/12,16 return normal visitors to
Olivine Cafe2,7. Boundary south-arrow warps11/12,17 use its native entrance0.
The player can save, quit, return and resume searches. There is no timer,
encounter restriction, forced follower hiding, party mutation or additional story gate.
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

## Authorized New Bark testing shortcut

Inspect the mailbox outside the player's house (17,11) and accept the
Halloween test-trip offer. It works on fresh/existing saves without party,
Badges, battles, progress resets or automatic item grants. Decline continues
the original house sign. Both raw Pory and assembly contain the same one call.

The saved return choice VAR_TRIO_HALLOWEEN_RETURN0x414A is0 for the normal
Olivine invitation and1 for the New Bark test trip. Successful entry sets the
origin; declines preserve it. Exit Gastly and both walk-out coordinate exits
at11/12,16 route to New Bark18,12 for test trips or Olivine Cafe at2,7 for
normal invitations. On-load initializes only the map-local temporary exit
latch, so saving/reloading inside retains the origin and all puzzle progress.
The original south-arrow warps remain a normal-route fallback at the boundary.

Thirty additional origin/decline/save-reconstruction/ghost+walk return source
combinations and mailbox rawPory parity/safe home tile checks pass. Actual
rendered travel and fresh-save/reload still need emulator confirmation.
This is an explicitly authorized temporary testing hook. Remove the mailbox
call/helper when requested, preserving safe return-mode1 handling for saves
already visiting the trail and retaining all earned outfits/game progress.

Build repair: CI192 failed during event-script assembly because the New Bark
return used MAP_NEWBARK_TOWN, while the registered symbol is MAP_NEW_BARK_TOWN.
Corrected that one warp target. No map numbers, saved origin, rewards or puzzle
rules change. The source runner now invokes the production map generator and
resolves all four authored warp targets against its actual constants, while
checking every historical map number.3454 puzzle and30 return cases pass.
Compilation/CI results must still be reported separately.

Separate older CI190/191 engine-test failure: the cafe fixture still expected9
actors after the authorized apology clerk was appended. It now expects10 and
checks the final clerk's Greedent graphic,4,6 position, harmless trainer type
and actual apology-offer script. No cafe runtime/map changes. The silly-scenes
source history check now permits the subsequently authorized appended costume
IDs/variables while preserving every historical numeric ID and saved structure.
All five scene/source groups and actual cafe clerk registration checks pass.

## User-requested pacing move to the sixth Badge approach

Gastly is now in Olivine Cafe1,6 (west-side city door8,43), after Chuck's
fifth Badge and before Jasmine's sixth. A pre-Badge5 visit gives a clear hint.
Normal travel/return and both native boundary warps use the cafe; New Bark
testing mode1 still returns home and bypasses the normal Badge gate. No earned
game/item/photo reset, new save allocation or map-ID change. Original Ecruteak
house and Olivine cafe dialogue/scripts/services remain unchanged. Added30
pre-Badge5 normal/preview source cases; all original cafe paths/approaches stay
connected with the new ghost, including Jasmine's story-gated spot.

CI196 also exposed120px Halloween item description wording vs102px limit.
All three now say "Reusable costume. / Use again to revert." A glyph-based
source audit verifies every one of39 family transformation descriptions fits
the actual Bag/Shop font bound. Item behavior/IDs/pockets stay unchanged.
