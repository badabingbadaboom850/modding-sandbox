# Trio costume collectibles

The first three of the planned nine cosmetic forms are Balloon Riko, Box Bijuu
and Hot Dog Penny. Stats, types, abilities, growth, tutor/TM compatibility and
level-up moves match the ordinary girl exactly. Each has battle front/back,
party icon, six walking frames and a matching gift icon. All stay female.

| Costume | Gift and encounter | Location |
| --- | --- | --- |
| Balloon Riko | Riko Balloon from a party-balloon vendor; bring Riko and accept | Cherrygrove: between Mart and Pokemon Center,43,9 |
| Box Bijuu | Bijuu Box after an optional friendly courier battle; bring Bijuu | Violet: west of Pokemon Center,36,46 |
| Hot Dog Penny | Penny Hot Dog from a food vendor; bring Penny and accept | Azalea: south-east of Pokemon Center,36,19 |

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

The remaining six planned costumes are Princess/Raincoat Riko, Bread/Detective
Bijuu and Blankey/Lifeguard Penny; they are not implemented in this batch.

Validation: RELEASE=1 production ROM compiled (ROM32471016 bytes,
EWRAM255416 bytes). All57 focused checks and93 broader species/text/Mega
regression checks pass, each suite with7 expected harness self-test failures
and no unexpected failures. Checks include both Penny stages/level26, exact
metadata/TM/signature access, encrypted storage, toggle eligibility, normal
and Spirit Mega/faint returns, historical saved ABI,192 gift paths, geometry
and all18 compiled follower frames/palettes. Docs-summary/diff checks pass.
Approved art and headless checks are separate from in-game emulator testing.
