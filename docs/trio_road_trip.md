# The Great Trio Road Trip

An optional island holiday opens after Chuck's Johto Badge (`FLAG_BADGE05_GET`). Scott waits on Cianwood's beach at **22,48** and in Olivine's port at **17,5**. Travel is free. The ferry saves the departure port so an in-game save/reload on the island returns to the correct mainland location.

## Playable chapter

The island shore has a northeast cabin, a western woodland guide, an eastern cove guide, three optional exhibition opponents and the picnic clearing. All routes, guides, cabin rest and ferry remain available throughout the chapter, including during the shower. There is no clock, weekday, Champion requirement or prerequisite quest.

- **Riko's woodland adventure:** talk to Riko by the southern woodland path. Visit the west marker, then the east snack tin. Choose the written east direction and the sketch's north direction; Riko's confident wrong answers produce affectionate detours and allow retries. Inspect the north lookout to save her photo.
- **Bijuu's guardian mystery:** the west cove caretaker opens the case. Ask the southeast fisherman, inspect the cushion's pawprints, then inspect the northeast windchime. The tide/delivery rope, wind and toy mouse explain the bell. Bijuu happily retains the guardian title and fish privileges. Her photo is permanent.
- **Penny's storm rescue:** deliberately start the picnic at the island cushion. A shower begins; it blocks nothing. Talk to Penny nearby and choose any supportive option. Enter the northeast cabin, inspect its lower-right dry blanket, then rest on the left cushion. Penny settles only after checking on everyone. Rest heals, completes her photo and clears the shore shower on return.
- **Sunset:** once all three adventures are complete, interact with the picnic cushion. No exhibition victory is required. Riko dozes, Bijuu takes Scott's seat, Penny settles beside Mom, and Scott calls it his perfect date. Completion permanently adds the chapter and his letter to Mom's scrapbook's Sister moments.

The cabin remains accessible on every visit. It has family conversations, Scott's outfit reactions, permanent illustrated trip-photo pages, the existing outfit album, healing and a letter. After the sunset, Scott offers one Leftovers picnic tin. Decline or a full Bag leaves it pending; successful receipt is once per save.

## Optional exhibition

Marina's beach doubles team is level34, Fern's woodland-themed team level36, Scott's vacation team level38. They may be fought/retried in any order before or after the sunset. Two healthy non-Egg partners are required after pre-battle healing. Every outcome heals and resumes the same field script through an exact island-map AND trainer guard, before the normal whiteout branch. Ordinary battles and the squirrel gang retain normal losses. Island doubles overrides the global replay singles setting only for these three opponents on this map.

Unused trainer IDs1151-1153 are repurposed, preserving trainer counts. Their ordinary flags overlap Rinto/Vajra/Ariana progression. Trainer flag accessors isolate these IDs, using independent road-trip victory bits and never writing those reclaimed flags. Actual-source checks, engine tests and production-party decoding are separate from rendered battle testing.

## Save and map compatibility

Persistent variables append in audited free existing slots:

| Address | Symbol | Meaning |
| --- | --- | --- |
| 0x4136 | VAR_TRIO_ROAD_RIKO | 0 offer,1 tour,2 first marker,3 snack sketch,4 lookout/photo |
| 0x4137 | VAR_TRIO_ROAD_BIJUU | 0 rumor,1 case,2 fisherman,3 pawprints,4 reveal/photo |
| 0x4138 | VAR_TRIO_ROAD_PENNY | 0 picnic,1 shower,2 cabin route,3 sheltered,4 rested/photo |
| 0x4139 | VAR_TRIO_ROAD_COMPLETE | 1 sunset/book chapter |
| 0x413A | VAR_TRIO_ROAD_RETURN | 0 Cianwood,1 Olivine |
| 0x413B | VAR_TRIO_ROAD_BATTLES | bits0-2 beach/forest/Scott wins |
| 0x413C | VAR_TRIO_ROAD_SOUVENIR | 1 picnic tin claimed |
| 0x413D | VAR_TRIO_ROAD_VISITS | capped ferry-arrival count |

Four maps append to IndoorCianwood; three layouts append, and the cabin shares the proven Mirror House room layout with separate objects/scripts. The shore/cove use Cianwood's existing tileset pair; woods use JohtoGeneral/NationalPark. Cabin entry is Cianwood's actual native house-door tile; its south-arrow exit returns to the new shore. Earlier map/layout/item/species/move/flag IDs, save arrays, earned achievements and palette files stay fixed. No startup grants, progression resets or testing warp are added. Older saves can accept the holiday immediately after the existing Badge gate.

## Validation and rendered test plan

`tools/roadtrip/validate.py` executes the actual event scripts with engine stubs, including clues, cancellation, every story state, replay, no-battle finale, battle outcomes, full-Bag retry, saved ports, photo closure, menu lock ownership, tile behaviors, every object's approaches, object budgets and historical IDs. `test/trio_roadtrip.c` checks the actual C helpers, reclaimed flag isolation, saved port/count, save ABI and enabled species graphics.

These are not interactive emulator confirmation. Test on a copy of an existing in-game save: both ferry stops; the house door/native exit; leave/reload each unfinished adventure; wrong choices and B; completed photos without the original party; lost/repeated exhibition with two partners; full-Bag souvenir; all three photos, sunset and scrapbook after in-game save/reload. The user has not yet confirmed a rendered road-trip playthrough.

## Temporary New Bark preview

At the user's request, the player-house mailbox (17,11) offers island travel without a Badge requirement. It preserves all existing quest states, saves return mode2, and the island ferry returns to New Bark (18,12), including after in-game save/reload. Cianwood/Olivine departures overwrite the return mode normally. No Badge, item or victory grants and no resets. Remove this temporary offer after the user confirms testing; preserve earned progress.
