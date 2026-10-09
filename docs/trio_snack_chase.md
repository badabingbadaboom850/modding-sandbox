# The Broad-Daylight Snack Cartel

The snack theft is an escalating six-encounter side story. Each new encounter adds one Greedent. Route entry triggers a one-time mugging scene, never a battle. Pursuing the thief and choosing Yes at its hideout starts an optional fight. Every route remains open; the entire gang story can be left unfinished. Losing uses normal trainer defeat: blackout, the normal money penalty, and a return to the healing location. Winning does not grant a free heal. The festival's separate exhibition matches retain their existing rules.

| Encounter | Place | Required milestone | Team |
| --- | --- | --- | --- |
| 1 | Route 37 | Whitney's Badge | One level-22 Greedent |
| 2 | Route 38 | Morty's Badge | Two level-35 Greedents |
| 3 | Route 42 | Jasmine's Badge | Three level-48 Greedents |
| 4 | Route 44 | Pryce's Badge | Four level-62 Greedents |
| 5 | Route 26 | All eight Johto Badges | Five level-78 Greedents |
| 6 | Route 6, Kanto | Champion | Six level-100 Greedents |

Complete and reclaim the previous encounter's snack before the next gang appears. Badge flags use the actual matching leaders; an advanced save can catch up by visiting these routes in order. A completed old Route 37 chase counts as encounter one, without another theft.

## Pursuit and ambushes

The first route entry after Whitney starts the theft automatically. Greedent hides in the northern grass at (17,19); finding it there sends it to (32,23), beside the eastern Berry tree. Talking there offers a Yes/No battle choice. The northern interception events have been removed: heading to Ecruteak works even with the snack still stolen. The original Ecruteak entry triggers at y=11 remain.

Later qualifying route entries steal once, explain where the gang fled, then return control without a battle. A stationary Greedent represents the gang at a side hideout; it has no trainer sight or movement that can intercept the player. Talking to it offers Yes/No. Declining leaves the snack safe and all paths open. Returning after a defeat or simply ignoring the gang never triggers another entry scene or removes another item.

| Route | Hideout | Coordinates |
| --- | --- | --- |
| 38 | South of the Berry tree | (17,26) |
| 42 | Southeast of the western gate | (10,12) |
| 44 | South of the western Berry tree | (7,12) |
| 26 | Southeast of the northern house | (25,13) |
| 6 | Southwest of the Berry tree | (34,7) |

The story grows from a thief with a friend to a pretend snack manager, road-tax collectors, a regional protection racket and a full snack cartel. The final team has perfect IVs, 252 HP/252 Attack EVs, held Berries/Leftovers and varied setup, recovery and offensive moves. Defeated gangs recruit; losing a retry does not add another member to that same encounter.

## Item custody

Each encounter removes one real Bag Berry, preferring Oran/Chicky, and stores its exact ID before any battle starts. With no Berries, a narrative picnic snack is taken, with no inventory item removed or granted. Held items, medicine, evolution items and key items are never candidates.

Blackout can skip the entire script tail. Persistent custody is therefore recorded before battle; defeat leaves the current wave and stolen item pending. Return to the hiding spot whenever ready and choose Yes to retry. Merely passing through never restarts a battle. The first pursuit resumes at its two hiding spots. Until the snack is recovered, later waves wait; this only pauses the optional cartel story and does not gate any Gym, route, League, Kanto, Spirit or arena progression.

A victory is recorded before trying to return the item. A full stack/pocket retains both the item and won status. Make room, then revisit the route or talk to Mom: the item returns without another battle. The next wave starts only after successful return. Repeating helpers, scene replays or completed route visits cannot duplicate or steal extra items.

The first rescue remains in Mom's Scrapbook → Sister moments. Completing all six adds the cartel finale, including Scott's quip. Memory checklist shows the next route and Badge gate.

## Implementation and compatibility

Existing state meanings are retained: `VAR_TRIO_SNACK_CHASE_STATE 0x4125` uses 0 untouched, 1 northern grass, 2 grove/battle pending, 3 won/return pending, 4 first chase complete. `VAR_TRIO_SNACK_STOLEN_ITEM 0x4126` holds exact item custody. New variables 0x4127–0x4129 hold completed waves, active wave and battle/return phase; save-array sizes remain unchanged.

Route callbacks preserve their time encounters and add preparation plus an on-frame table using previously unused local VAR_TEMP_B. First theft has its own pursuit scene; five later hideouts append one stationary non-trainer Greedent each; decoded collision/behavior and connected-path checks show none disconnects an existing path or blocks an event/entrance. Shared hide flag 0x1088 is recomputed for the current map and pending wave before objects spawn. Route 37's original objects/events stay; its eight northern interception events are removed. Pory and compiled scripts stay synchronized where both exist. No test starts or startup grants are added.

Trainer 1162 remains the first thief; unused 1154–1158 provide the five larger parties without increasing trainer counts. **Unused trainer IDs are not necessarily unused trainer flags:** these slots overlap reclaimed Vajra/Lati puzzle flags. Gang flag reads use saved gang wins, and its ordinary trainer-flag writers skip these slots. This isolation preserves existing puzzle state while leaving battle defeat callbacks normal. Do not remove that protection or return to reading/writing `TRAINER_FLAGS_START + gangTrainerId`.

## Validation and playtest

`tools/snack/validate_gang.py` interprets the actual mugging and optional battle scripts, including entry without battles, Yes/No hideout interactions, all six team dispatches, victory/blackout/retry, full-Bag return without another battle, route callbacks/Pory stability, original events, party sizes, normal defeat callbacks, puzzle-flag guards and wrapped text. `validate_chase.py` retains legacy chase, decoded geometry and escape-path coverage.

Six actual engine tests in `test/greedent_gang.c` cover Badge/map/order gates, all six theft/retry/return cycles, full-stack recovery, legacy migration, reclaimed puzzle-flag isolation, and ignoring every gang across all six routes without rescheduling fights or thefts. A separate production-ROM check decodes the actual compiled parties/levels/IVs/EVs/held items using C-derived ARM ABI offsets; the headless runner substitutes mocked trainer tables. Existing custody, festival, Camp and fresh-save checks also run in the targeted suite. Script and headless checks do not establish rendered emulator confirmation.

Playtest: load before Whitney or an advanced existing save; observe the first theft, pursue both hiding spots, walk past the northern exit without pursuing, decline the hideout fight, lose, pass through without a rematch, then return when ready, and save/reload while custody is pending. Win each wave in order. Fill the stolen Berry stack before recovery, then retrieve through Mom and through route reentry without another battle. Check final six-member party, ordinary money loss and healing-location return, no automatic win heal, scrapbook/checklist and original route trainers, Suicune and Ecruteak events. CI and interactive playtests remain separate from local compilation/source/headless results.

Optional-battle local verification: ROM compiled successfully; targeted engine suite passed 28 checks plus 7 expected runner self-test failures (35 total). Seven gang and six chase source/geometry groups, existing Scott/Camp/festival groups, docs validation and diff checks passed. Actual production-ROM party decoding still confirms all six teams and the final IVs/EVs/items. CI and rendered entry/hideout/blackout/save-reload playtests remain separate.
