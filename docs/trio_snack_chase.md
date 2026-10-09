# The Broad-Daylight Snack Cartel

The snack theft is now a mandatory, escalating six-encounter story. Each new encounter adds one Greedent. There is no yes/no battle prompt. Losing uses normal trainer defeat: blackout, the normal money penalty, and a return to the healing location. Winning does not grant a free heal. The festival's separate exhibition matches retain their existing rules.

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

The first route entry after Whitney starts the theft automatically. Greedent hides in the northern grass at (17,19); finding it there sends it to (32,23), beside the eastern Berry tree. Talking there starts its battle immediately. If the player instead heads for Ecruteak, Greedent intercepts all four walkable northern-exit tiles at y=12, x=16–19. Both active chase states are covered. The original Ecruteak entry triggers at y=11 remain.

Later qualifying route entries start their battles automatically. The story grows from a thief with a friend to a pretend snack manager, road-tax collectors, a regional protection racket and a full snack cartel. The final team has perfect IVs, 252 HP/252 Attack EVs, held Berries/Leftovers and varied setup, recovery and offensive moves. Defeated gangs recruit; losing a retry does not add another member to that same encounter.

## Item custody

Each encounter removes one real Bag Berry, preferring Oran/Chicky, and stores its exact ID before any battle starts. With no Berries, a narrative picnic snack is taken, with no inventory item removed or granted. Held items, medicine, evolution items and key items are never candidates.

Blackout can skip the entire script tail. Persistent custody is therefore recorded before battle; defeat leaves the current wave and stolen item pending. Returning to the relevant route permits a retry without stealing a second item. The first chase can resume at its hiding spots or mandatory exit gate.

A victory is recorded before trying to return the item. A full stack/pocket retains both the item and won status. Make room, then revisit the route or talk to Mom: the item returns without another battle. The next wave starts only after successful return. Repeating helpers, scene replays or completed route visits cannot duplicate or steal extra items.

The first rescue remains in Mom's Scrapbook → Sister moments. Completing all six adds the cartel finale, including Scott's quip. Memory checklist shows the next route and Badge gate.

## Implementation and compatibility

Existing state meanings are retained: `VAR_TRIO_SNACK_CHASE_STATE 0x4125` uses 0 untouched, 1 northern grass, 2 grove/battle pending, 3 won/return pending, 4 first chase complete. `VAR_TRIO_SNACK_STOLEN_ITEM 0x4126` holds exact item custody. New variables 0x4127–0x4129 hold completed waves, active wave and battle/return phase; save-array sizes remain unchanged.

Route callbacks preserve their time encounters and add preparation plus an on-frame table using previously unused local VAR_TEMP_B. First theft has its own pursuit scene; later ambushes have no new overworld objects or movement, so original route object budgets and paths remain. Route 37's original objects/events stay, with eight northern gate entries appended. Pory and compiled scripts stay synchronized where both exist. No test starts or startup grants are added.

Trainer 1162 remains the first thief; unused 1154–1158 provide the five larger parties without increasing trainer counts. **Unused trainer IDs are not necessarily unused trainer flags:** these slots overlap reclaimed Vajra/Lati puzzle flags. Gang flag reads use saved gang wins, and its ordinary trainer-flag writers skip these slots. This isolation preserves existing puzzle state while leaving battle defeat callbacks normal. Do not remove that protection or return to reading/writing `TRAINER_FLAGS_START + gangTrainerId`.

## Validation and playtest

`tools/snack/validate_gang.py` interprets the actual mandatory scripts, including the first pursuit and exit battle, all six team dispatches, victory/blackout/retry, full-Bag return without another battle, route callbacks/Pory stability, original events, party sizes, normal defeat callbacks, puzzle-flag guards and wrapped text. `validate_chase.py` retains legacy chase, decoded geometry and escape-path coverage.

Five actual engine tests in `test/greedent_gang.c` cover Badge/map/order gates, all six theft/retry/return cycles, full-stack recovery, legacy migration, reclaimed puzzle-flag isolation. A separate production-ROM check decodes the actual compiled parties/levels/IVs/EVs/held items using C-derived ARM ABI offsets; the headless runner substitutes mocked trainer tables. Existing custody, festival, Camp and fresh-save checks also run in the targeted suite. Script and headless checks do not establish rendered emulator confirmation.

Playtest: load before Whitney or an advanced existing save; observe the first theft, pursue both hiding spots, try walking past the northern exit without pursuing, lose and return, and save/reload while custody is pending. Win each wave in order. Fill the stolen Berry stack before recovery, then retrieve through Mom and through route reentry without another battle. Check final six-member party, ordinary money loss and healing-location return, no automatic win heal, scrapbook/checklist and original route trainers, Suicune and Ecruteak events. CI and interactive playtests remain separate from local compilation/source/headless results.

Final local verification: production ROM compiled; 27 targeted engine checks passed plus 7 expected runner self-test failures (34 total). Production-ROM decoding confirmed all six party sizes/levels and the final team IVs, EVs and held items. Six gang and six legacy chase source/geometry groups pass, alongside existing Scott/Camp/festival and docs checks. Remote CI and interactive emulator confirmation remain separate.
