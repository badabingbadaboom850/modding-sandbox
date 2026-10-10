# Definitely Legitimate Snack Cafe

After the sixth squirrel-mafia battle, Vermilion's house east of the Gym
(door38,22; old House3) becomes a cafe run by six reformed Greedents. Original
house/map IDs and the city door remain unchanged. Before that victory, the
original gentleman and Diglett-tunnel hint remain. The cafe boss also retains
his useful hint afterward. A final-wave full-Bag winner qualifies immediately
(active wave6, phase2), without reclaiming the stolen item or fighting again.
Historical six-wave winners qualify automatically.

The user confirmed the cafe in a rendered emulator. The release removes the
New Bark mailbox shortcut and its return routing. Both cafe exits now return
to Vermilion, including old saves made inside the preview cafe. Saved memories,
parcels and cartel victories remain intact.

The independent cafe map uses Olivine Cafe's proven8x10 native layout/tilesets,
with nine actors: six nontrainer Greedents plus Riko, Penny and Bijuu. Every
actor is reachable, including the shopkeeper across the existing counter, and
the entry/exit aisle stays clear. There are no battles, thefts or forced walks.
The first visit records an apology scrapbook memory. Each employee has a
specific honest job, questionable bookkeeping or a personal girl interaction.

The counter sells existing small/medium/large Wawa, Oran Berries and Riko Puffs
at their normal prices (Puffs500). The courier has three once-only Scott parcels:
three small Wawa, then three Puffs, then one Leftovers, each with his own flirty
note. Declining preserves the parcel. A full Bag keeps it pending. After a
successful claim, leaving and returning readies the next; in-cafe loading and
saving/reloading do not. No real-time timers or repeatable free gifts.

Allocations audited against d7894d87:
- `VAR_TRIO_CAFE_TEST_RETURN=0x412F`:reserved legacy test slot, now unused.
- `VAR_TRIO_CAFE_DELIVERY_STATE=0x4130`:0/2/4 ready,1/3 delivered awaiting exit,5 done.
- `FLAG_TRIO_CAFE_VISITED=0x108F`:apology/scrapbook recorded.
- IndoorVermilion map9 appended; all old maps/layouts/items/species stay stable.
- SaveBlock1/2/3 remain15444/2864/100. No save arrays are resized. Decimal slot
  matches in old trainer source were only #line directives, not flag/var uses.

`tools/cafe/validate_cafe.py` executes actual cafe assembly with stubs for gifts,
full-Bag retry, decline, visit readiness, release host travel and once-only intro.
It also checks native geometry, all actor approaches, original ID prefixes,
script/Pory parity, registrations and text wrapping. `test/trio_greedent_cafe.c`
checks actual engine warp selection for all147 saved-state combinations, native
retired-mode compatibility/isolation, registered map assets and saved ABI. These are source and
headless engine checks, not rendered interactive emulator playtesting. Verify
cafe load, counter interaction, first apology, native/host exits, saving/reloading
inside, parcels and the natural Vermilion door in a rendered emulator.


Cafe validation:100 focused actual engine/battle/text tests pass, plus7 expected
runner self-test failures and zero unexpected failures. All3 new cafe engine
checks pass, including147 access states and native exit routing.89 family
source/geometry groups and docs-summary/diff checks pass. Shared Spirit-family
metadata now includes every eligible personal form, and the previous no-Mega-
table assertions now verify entry eligibility plus absence of automatic normal
form faint/end reversion. Permanent evolution, all30 Spirit Mega starting-form
returns and standard species/form metadata tests pass. The user has since confirmed the rendered cafe preview works and approved it.
Release exit cleanup has separate source and engine checks.

Final production ROM compilation passed (ROM32517676 bytes; EWRAM255420 bytes).

Release cleanup validation: RELEASE=1 production ROM compiled successfully
(ROM32444588 bytes, EWRAM255416 bytes). All44 focused engine/battle checks pass,
plus7 expected runner self-test failures and zero unexpected failures; cafe
access/legacy exit/save ABI, Riko gates/scaling, Spirit Megas and species metadata
are covered. All89 family source groups, docs-summary and diff checks pass.
Release routing changes have headless coverage; user confirmed the cafe preview.
