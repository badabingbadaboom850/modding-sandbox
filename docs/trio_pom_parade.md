# Goldenrod Pom Parade

Talk to the existing woman at Goldenrod's central corner (30,25), north of
the Game Corner. She offers a free, optional and replayable parade before her
original conversation. Declining continues her original dialogue. Her existing
civilian visibility and an explicit takeover check preserve the Rocket story.
There is no Badge or party gate, gift, battle or permanent road obstruction.

The parade stages the same Goldenrod layout with the player at30,23. Nine Poms
(ordinary Riko follower art, with Riko as honorary lead) march north in two
columns on32/34. Three spectators including Scott watch from the crossing
street at27/29/31,24, with Penny and Bijuu beside the player. After six steps,
all nine Poms are together in the viewport: one spins, one sniffs a snack to
the right and returns, and Riko barks. Six more steps include a delayed fast
catch-up by the last Pom. The crowd and sisters cheer, then the player returns
to the organizer's approach tile30,24 on the ordinary city map.

Uses the existing HG Wi-Fi Parade music, explicitly enabled in song config.
No new graphics or alteration of the girls' species/forms is involved. The
camera stays on the player with no scroll or camera-object handoff. Movements
finish before dialogue and cleanup. All14 actors are explicitly loaded and
checked for live sprites before any movement; a failed allocation returns
without recording completion. The temporary follower hide flag is set during
the staged transition and cleared before every return, preserving follower
preferences. Fourteen NPCs plus player and possible NPC follower fit16 slots.

TrioPomParade appends to IndoorGoldenrod, reuses LAYOUT_GOLDENROD_CITY and has
no original story callbacks, connections or free-roam triggers. On entry its
frame script starts automatically; the player cannot open the save/menu during
the scene. Reentering via an emulator snapshot/map load starts a clean staging
transition. An ordinary save/reload after completion retains the scrapbook.
Normal city objects, doors, layout, IDs and services are unchanged.

Audited-unused VAR_TRIO_POM_PARADE0x4146 uses the existing saved array. Set to1
only after the full finale; replay/decline/failed setup never reset it. The
Sister moments scrapbook reads the page when completed and never mutates
progress. Old vars, flags, species, items, trainers, save struct sizes and
Greg's separate wins remain intact. Specials append without shifting old IDs.

Source validation: tools/parade/validate.py executes the actual authored event
and movement scripts for offer/decline/cancel/takeover, completion/replay and
failed actor setup; verifies every walked cell, concurrent actor separation,
fourteen-actor budget, original scripts/maps/ID history, reserved variable,
read-only memory and text bounds. test/trio_parade.c checks native actor/sprite
readiness, missing actors, wrong map and allocation guard behavior. Compilation,
linked-ROM registration checks and headless tests are separate from rendered
emulator confirmation. Test the approach, nine marching sprites, movement quirks,
music, exit controls, follower restoration, repeat and real save/reload.

Keep PR2 draft and unmerged. The existing authorized island mailbox shortcut
is unaffected.

Completed validation: RELEASE=1 production build passed (32,726,644 linked
bytes; EWRAM255,416; padded32MiB). All five source-flow/geometry/history groups
and linked-ROM actor/script/movement/music checks passed. Twenty focused native
checks passed with seven intentional harness failures and zero unexpected
failures, covering parade readiness and Greg/hat/road-trip regressions.
Rendered emulator playback and an actual player save/reload remain unconfirmed.
