# Eight silly family interactions

Free, optional, repeatable discoveries spread across Johto and Kanto. Talk to
one new stationary host and accept the invitation. Decline or B leaves normal
exploration available. The seven short scenes automatically return to the same
house or cafe; Greg's room lets you talk to each disguise and use its door.

- Penny valet: Olivine's trade house, doorway27,24; gentleman6,7. Keys jingle,
  Penny trots over, "Ma'am, your hot dog has arrived." Scott gives five stars.
- Forbidden box: Ecruteak's Lugia-story house, doorway19,40; scientist6,7.
  Bijuu approaches a moving-box prop and the fade reveals existing Box Bijuu
  NPC art. The actual party never changes form. The artifact owns the house.
- Barking ordinance: Mahogany teacher's house, doorway27,10; official6,7.
  Riko barks and immediately receives an exemption. Bijuu complains about
  the complaint; Penny requests inside voices.
- Greg Fan Club: Blackthorn granny/Dratini house, doorway21,39; Greg6,7.
  Five individually talkable Greg disguises use existing man/fisherman/hiker/
  expert/ninja graphics. Each "independent source" exposes himself. Scott
  questions peer review. No battles, fees, trainer or Greg-win writes.
- Long hot dog: Cianwood's three-resident house, doorway23,39; vendor6,7.
  Penny walks up, Scott defends his favorite customer, imaginary pup cup.
- Pom traffic: Pewter Nidoran house, doorway35,15; host6,7. A staged native
  Pewter road shows three Poms, snack bag and spectators. Pretend chicken
  resolves the negotiations and the Poms march away. Actual roads stay clear.
- Fishing inspection: Cerulean Badge house, doorway18,11; fisherman6,7.
  Bijuu approaches the catch on a staged native river street. Fade, empty
  bucket joke. Bucket/catch are described in dialogue, not new fish props.
- Apology department: unlocked Vermilion squirrel cafe, doorway38,22;
  new Greedent4,6. A clerk presents a box of apology forms. Another Greedent
  takes it and disappears. Only fictional paperwork is stolen. Existing cafe
  access requirements, shop, parcels, memories and exits stay unchanged.

All three girls can be assumed present. Seven automatic scenes show the girls
and Scott. The freely explorable club shows five disguises plus Scott and
mentions the girls. Registered existing sprites, cries, movements and music
are reused; no new raster art, items, species, trainer IDs or saved fields.

Eight maps append to their indoor groups. Every old map ID and source object
index remains. The seven scene maps set only VAR_TEMP_A and the temporary
follower hide flag; Box Bijuu also uses FLAG_TEMP_1 for the hidden reveal.
Both normal and failed setup returns clear those temporary flags. All actual
party, inventory, earned victories, scrapbook and story state stay unchanged.
Normal sources and scripts remain, with one appended host per source map.

PrepareTrioSillyActors uses exact-map, live-sprite checks and safe spawning
before movement. Missing actors return without running movements. Five to ten
visible scene actors fit the sixteen-object budget with player/follower space.
The Box reveal removes two objects before adding its static cat-in-box actor;
no movement targets the new reveal sprite. Greg uses ordinary interaction
scripts and its native door back to the source house.

Checks: tools/silly/validate.py executes all24 offer answers,28 scene/replay/
setup paths and six club speakers, including exact movement/collision routes,
source services/approaches, wrapped dialogue and historical saves/map IDs.
tools/silly/validate_rom.py decodes all50 actors, eight guide/map registries,
seven frame scripts, club door and every authored text byte from the build.
test/trio_silly.c exercises all seven engine readiness gates, invalid sprites,
missing actors, wrong maps and existing Greg progress. New scenes still need
rendered player playtesting and real save/reload. Keep PR2 draft/unmerged.

Validation: RELEASE32736532 linked bytes/EWRAM255432/padded32MiB passed;
29 focused native checks passed +7 intentional harness failures, zero
unexpected failures.5 new source-flow/geometry/history groups and6 existing
cafe groups passed.8 compiled guide/map registries,50 actors,7 auto-frames,
6 club speakers and every authored dialogue byte checked in actual ROM.
All33 reusable item audits, normal5% run-off/mailbox and prior parade ROM
checks passed. New rendered scene/save-reload playtesting remains for user.
