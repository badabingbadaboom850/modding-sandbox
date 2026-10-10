# Trio costume collectibles

All nine cosmetic forms are now implemented: Balloon/Princess/Raincoat Riko,
Box/Bread/Detective Bijuu and Hot Dog/Blankey/Lifeguard Penny. Stats, types, abilities, growth, tutor/TM compatibility and
level-up moves match the ordinary girl exactly. Each has battle front/back,
party icon, six walking frames and a matching gift icon. All stay female.

| Costume | Gift and encounter | Location |
| --- | --- | --- |
| Balloon Riko | Riko Balloon from a party-balloon vendor; bring Riko and accept | Cherrygrove: between Mart and Pokemon Center,43,9 |
| Box Bijuu | Bijuu Box after an optional friendly courier battle; bring Bijuu | Violet: west of Pokemon Center,36,46 |
| Hot Dog Penny | Penny Hot Dog from a food vendor; bring Penny and accept | Azalea: south-east of Pokemon Center,36,19 |
| Princess Riko | Pom Tiara from a crown admirer | Goldenrod: near Gym/Flower Shop,42,15 |
| Raincoat Riko | Riko Raincoat from a rainy-day friend | Ecruteak: south of Mart,47,43 |
| Bread Bijuu | Cocoa Toast from a cook | Goldenrod: near Department Store,36,38 |
| Detective Bijuu | Detective Kit from a sleuth | Ecruteak: near western houses,25,33 |
| Blankey Penny | Penny Cozy Wrap from a blanket giver | Mahogany: south-east of Center,23,21 |
| Lifeguard Penny | Penny Beach Vest from a shore guard | Olivine: by the wharf,34,57 |
| Poison Bijuu | Toxic Mouse from a Poison enthusiast; elemental rather than cosmetic | Fuchsia: west of Gym entrance,6,33 |

Morgan the courier uses a level12 Meowth and Zigzagoon. Losses use the normal
blackout and allow retry; declining never blocks a route. A full-Bag winner can
claim the box later without another win or party requirement. The two other
gifts similarly retry. Gifts are protected reusable Key Items: no charge,
consumption, startup grants or test warps. Bag possession prevents duplicates.

Use the matching item on ordinary Riko/Bijuu/Penny to dress up, and use it on
the costume to return. Elemental and special story forms first return to their
ordinary form using their own existing item. Penny supports both ordinary
Fidough and evolved Dachsbun stages with identical art but separate metadata,
so dressing her up preserves her stage and stats. Level26 evolution changes
Hot Dog Penny to the dressed Dachsbun stage, and reverting returns Dachsbun.
The normal item evolution branches remain available from each costume.

Scott's signatures and current-form elemental lessons, family-party checks,
Camp form-swap statistics and keepsake Mega eligibility include the costumes.
Costumes do not strip at fainting or ordinary battle completion. Bondstone
Riko/Bijuu and keepsake Megas restore the exact starting costume through the
existing PartyState.changedSpecies mechanism. Normal Mega Riko/Bijuu return
entries now use that mechanism instead of a fixed ordinary-species target.

## Compatibility and implementation

Four real species append1617-1620; the fourth is Penny's evolved metadata using
the same bun art. Existing real IDs and form indices retain their values/order.
Egg remains a sentinel after real species, as with earlier form additions.
Items955-957 append; existing item IDs remain. The audited unused trainer slot
1163 becomes Morgan without changing TRAINERS_COUNT, MAX_TRAINERS_COUNT or
saved trainer flag bounds. No new persistent flags/vars, saved arrays or save
layout changes are introduced. Existing saves can visit all three encounters.

Shared encounter assembly lives in data/scripts/trio_costumes.inc, included by
event_scripts.s; map JSON appends static no-sight NPCs without changing earlier
objects, coordinates, warps, scripts or visibility. No map Pory source changes
are needed for the shared script. The generated trainer header is built from
src/data/trainers.party. tools/costumes/validate_costumes.py exercises192 source
paths and validates geometry, text, historical IDs and indexed asset packing.
Run with --compiled after building to compare all18 follower frames/palettes.

## Art provenance

Built-in image generation created each sheet using the existing Riko/Bijuu
battle sprites and Penny Brave as identity references. Approved prompt set:

- Riko: black female Pomeranian, brown eyebrows, cream chest, one pink balloon
  tethered to her harness; grounded poses with balloon contained in each cell.
- Bijuu: cream female Siamese, dark face/ears/paws/tail and blue eyes, head/paws/
  tail visible through a plain open cardboard box costume.
- Penny: golden blonde long-haired female miniature dachshund wearing a bun
  around her long torso, ketchup zigzag, natural blonde ears/legs/tail visible.

Each request specified transparent16-color pixel art, no labels or grid lines,
front/back/icon then down/down-step/left and left-step/up/up-step poses, plus
an isolated gift icon. User approved all three generated sheets with no notes.
import_assets.py crops inspected cells, downsamples without dithering, creates
one16-color indexed palette per girl, preserves Bijuu's blue eyes, and packs
followers in engine order down/up/left. Normal/shiny art shares these palettes.

## Emulator checks

1. Visit each giver with the matching girl. Decline once, accept, and revisit.
2. Fight Morgan, then claim the box. Check loss/retry and full-Bag recovery if
   practical; neither should block ordinary exploration.
3. Dress each girl, inspect party/battle/back/follower views in all directions,
   then use the gift again. Check both ordinary Penny stages.
4. Teach a Scott signature to a costume. Check regular and Spirit Mega return.
5. Save in-game while dressed, close/reload the ROM, and verify costume, moves
   and gifts remain. Headless storage/ABI checks do not replace this check.

The user confirmed the first three costumes work in the emulator. The six new
costumes and Poison Bijuu still require rendered testing. All costumes preserve
base/stage stats. Each Penny outfit has both ordinary and evolved metadata.

Poison Bijuu reuses existing species1591, preserving its original stats and
family/Spirit eligibility. Toxic Mouse958 is a reusable ordinary Items-pocket
transformation item, gifted outside Fuchsia Gym rather than sold at the Mart.
Use it on ordinary or Box Bijuu to become Poison, and on Poison to return to
ordinary Bijuu. Other elemental forms first revert with their own items.
Poison Fang is a level-zero transformation/Scott lesson attack. Later lessons
unlock Acid Spray12, Venoshock20, Poison Jab28, Sludge Bomb32 and Gunk Shot44;
Toxic24 remains a level-up/status attack and is excluded from the damaging-only
elemental menu. Equipped moves remain after reverting, as with other forms.

The full batch appends cosmetic species1621-1628 (eight entries for six skins)
and items959-964. Old real species/item IDs and form table indices remain.
No new saved flags/vars/arrays or trainer changes are introduced. All seven new
gifts are optional yes/no encounters: bring the matching girl, accept, and use
Bag possession to prevent duplicates. Full Bags can retry; no battles or
Gym progression requirements are added.

Validation: RELEASE=1 production ROM compiled (ROM32471016 bytes,
EWRAM255416 bytes). All57 focused checks and93 broader species/text/Mega
regression checks pass, each suite with7 expected harness self-test failures
and no unexpected failures. Checks include both Penny stages/level26, exact
metadata/TM/signature access, encrypted storage, toggle eligibility, normal
and Spirit Mega/faint returns, historical saved ABI,192 gift paths, geometry
and all18 compiled follower frames/palettes. Docs-summary/diff checks pass.
Approved art and headless checks are separate from in-game emulator testing.

## Temporary New Bark testing supplies

At the user's request, Mom's friend (the wandering lass at9,16 in New Bark)
now offers all nine costume Key Items plus Toxic Mouse before her ordinary dialogue. Say Yes
to receive any missing gifts; repeat visits skip owned items. A full Bag keeps
earlier successful gifts and lets the next visit finish the rest. No battle,
party, Badge or quest requirement, and no trainer/progression flags are set.
Her original story dialogue and movement still follow; No continues normally.
Both Pory raw authoring and compiled scripts match. Remove this temporary
call/helper when the user requests production test cleanup; keep earned items.

Testing-supply validation: production RELEASE=1 ROM compiled
(ROM32471372 bytes, EWRAM255416 bytes). All64 supply helper decline/owned/
partial-Bag/retry/repeat source cases pass, alongside192 natural gift flows,
text termination/wrapping, full Pory/assembly original-branch parity,
compiled follower art, historical IDs/save files, docs-summary and diff checks.
This script-only addition does not alter the engine covered by the previous
57 focused and93 broader passing checks. New prompt/gifts await emulator use.

## Full batch art provenance

Built-in image generation used the approved first costume sheets as identity
references and transparent pixel-art sheets with front/back/icon, six walking
poses, and one isolated gift icon. Prompts specified: black/brown/cream Riko
with gold/pink tiara or yellow hooded coat; cream/dark-pointed blue-eyed Bijuu
with bread framing her face, tweed cap/cape, or airborne purple poison bubbles;
blonde long-haired low-bodied Penny in lavender blanket or red/white vest with
whistle. No labels, extra animals, wings or previous costumes. Item icons were
matching tiara, coat, toast, detective kit, blanket, vest and purple mouse toy.

Final consumed assets live in graphics/pokemon/{riko_princess,riko_raincoat,
bijuu_bread,bijuu_detective,penny_blanket,penny_lifeguard,bijuu_poison}/,
graphics/items/icons/ and graphics/items/icon_palettes/. The deterministic
import_assets.py converts generated source art to indexed 16-color native sizes;
blue eyes and the small tiara jewel have reserved palette colors. Normal/shiny
art currently shares palettes. forms.json and placements.json record metadata.

Full-batch validation: RELEASE=1 production ROM compiled (32520152 bytes ROM,
255416 bytes EWRAM). All60 focused engine checks and93 broader species/text/Mega
checks pass, each with7 expected harness self-test failures and zero unexpected
failures. Covers all12 costume stage entries, three dressed Penny level26
evolutions, Poison item eligibility/current-level lessons, signature/TM metadata,
encrypted storage/save ABI and normal/Spirit Mega/faint exact-form return.
Source checks cover22528 test-supply combinations,192 prior gift flows,112 new
gift flows, seven collision/elevation/old-event-preserving placements, all60
compiled follower frames/palettes, historical IDs, text and docs-summary.
The user confirmed the original three costumes; new seven forms and actual
in-game save/reload still require focused emulator confirmation.


Outfit testing cleanup (2026-10-10): user confirmed every new outfit works.
Removed the Mom-friend testing call in both New Bark sources, restoring her
original story dialogue. Existing inventory, forms and saved progress remain;
all ten natural gift sources remain available. Scott stays in New Bark.
