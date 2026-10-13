# Outfit stories and little family adventures

This batch implements all five requested ideas on the existing test branch.
No new map, species, item, trainer or save-array layout is introduced. The
original nine costumes and Poison Bijuu remain from the preceding build.

## Outfit reactions and Scott

All ten costume/Poison gift NPCs comment on the first dressed girl in party
order. Three ordinary residents have a different set of reactions: Violet's
western youngster, Ecruteak's sage by the tower, and Olivine's youngster. Their
original dialogue and story commands remain after the new comment, with Pory
and assembly synchronized. Ordinary forms, unrelated Pokemon and Eggs do not
trigger an outfit line.

Scott comments separately on each dressed girl at the New Bark tutor and his
four existing Azalea/Ecruteak/Olivine/Blackthorn moments. There is a unique line
for all nine outfits and Poison Bijuu, retaining affectionate/flirty language
and the whistle joke. Existing Badge gates, recorded moments, tutor lessons,
party selection and cancellation remain. Outfits do not grant a Scott memory.

## Outfit photo album

Open **Outfit album** from Scott's New Bark tutor menu or Mom's scrapbook.
Wearing an outfit earns a permanent portrait, rather than merely obtaining the
item. Evolution completion records it; opening the album also records current
non-Egg costumes so older dressed saves work. Both Penny stages share the
same photo. Reverting, boxing or changing outfits does not erase portraits.

Riko, Bijuu and Penny each have three pages. Every unlocked page displays the
actual native battle sprite plus a personal caption. Locked pages explain how
to earn them. Back/B and all image returns close the portrait before returning.
The cover counts nine costumes, with Poison Bijuu as a tenth bonus portrait.
No new generated art or image downloads are needed.

## Tiny treasure hunts

Talk to the original costume giver with the matching girl. Each offers a short
optional quest after the costume is owned or received. These searches use
visible item-ball props at these exact locations:

| Girl | Giver | Search | Once-only reward |
| --- | --- | --- | --- |
| Riko | Cherrygrove balloon girl43,9 | Picnic basket39,17, south of Mart | Three Chicky Fil A (Oran Berries) |
| Bijuu | Violet courier36,46 | Parcel18,39, south-east of Mart | Three small McDonald's Wawa |
| Penny | Azalea bun vendor36,19 | Mitten43,15, south-east of Mart | Three Penny Pup Cups (Pecha Berries) |

Acceptance and searching require the matching family; claiming a found item
does not. Return to the giver after discovery. There are no battles, thefts,
consumed quest items, forced party changes or movement paths. Full Bags keep
rewards pending; claiming marks completion only after giveitem succeeds. Repeat
visits do not duplicate rewards. Their memories appear in the Sisters section
of the scrapbook after claiming.

## The golden-armored legendary

Goldenrod's frightened man53,14 reports a silent blue-eyed, golden-armored beast.
Accept his optional investigation, then speak to the woman61,29 beside the
far-right house, east of the apartment building. Her clue points into that house
(door61,33, GoldenrodCity_House4). Inspect the Bread Bijuu visitor9,3 inside.

The supposed prophecy is a cocoa sitting in toast, with Riko and Penny's
reactions. Return to the frightened man for two medium Wawa. Full Bag retries
need no repeat discovery; completed dialogue and the kitchen reveal replay
without rewards. The Sisters scrapbook gains its memory upon discovery, even
if the Bag reward remains pending. Before acceptance/clue, inspecting the cat
only provides harmless flavor; it never skips the investigation. Original
house residents, Venipede, warps and scripts remain.

## Save and implementation details

The existing saved variable array reserves audited-unused slots4131-4135:
three hunt states0 offer/1 accepted/2 found-reward-pending/3 claimed; bread
state0 rumor/1 accepted/2 clue/3 reveal-reward-pending/4 claimed; photo bits0-8
for costumes and bit9 for Poison. Previous IDs, variable bounds and saved sizes
stay fixed. Numeric sprite tags4132-4134 are unrelated to saved variable
addresses0x4132-0x4134. No fresh-save grants or resetting earned progress.

Shared scripts are data/scripts/trio_outfit_stories.inc. src/trio_outfits.c
maps exact current forms, excludes Eggs and records photo bits. Its evolution
hook extends TrioCamp_RecordEvolution without changing existing stat counters.
New specials append so prior special indices remain stable. The scrapbook menu
appends Album at5, preserving earlier options0-4; Exit moves to6. Scott's service
menu is Signatures0/Elemental1/Album2/Exit3, with cancellation checks updated.

Validation includes actual C engine tests for all costume/Poison mappings,
Penny-stage deduplication, Egg exclusions, older dressed saves, evolution hooks,
photo retention and cover count. tools/costumes/validate_stories.py executes
192 hunt paths and60 mystery paths, all portrait/locked/Back/B flows, reactions
and Scott dispatch, source/Pory parity, historical IDs and map geometry. All
six new props/actors have four walkable approaches and modest nearby actor
budgets. Existing gift/tutor validators retain their checks and execute new
helpers separately. Rendered UI, dialogue, portraits and real save/reload
still require emulator confirmation; headless tests are not a playthrough.

## Focused emulator checks

1. Wear one costume per girl. Talk to Scott for outfit lines and open Album.
2. View one unlocked and one locked page; Back/B out. Revert and reopen to
   confirm the unlocked page persists. Check the Poison bonus too.
3. Ask the three original costume givers for their hunts. Search, return,
   revisit and read the new Sisters scrapbook pages.
4. Accept Goldenrod's rumor, get the eastern woman's clue, inspect the kitchen
   cat, return for Wawa and replay. Original house dialogue/exit should work.
5. Save normally, reload and confirm photos/quest stages and rewards persist.

Validation: RELEASE=1 production ROM compiled (32528344 bytes ROM,255416 bytes
EWRAM). All70 focused engine/Camp/battle checks pass plus7 expected harness
self-test failures, zero unexpected failures. New checks cover every portrait
bit, both Penny stages, Egg exclusions, current-family reactions, existing dressed
saves, evolution hook retention and photo count; prior costumes/Poison/Megas/
Camp/cafe/cavern/trainers pass. Actual-source checks execute192 hunt paths,60
bread-mystery paths and all portrait/locked/Back/B/reaction/Scott flows; original
22528 test-gift states,304 natural gifts, all60 compiled follower frames,
tutor cancel/mode resets, geometry/Pory/history/docs/diff checks also pass.
Rendered new dialogue, portraits, quests and real save/reload still need testing.
Previous costume batch CI167 completed successfully. This batch has separate CI.
