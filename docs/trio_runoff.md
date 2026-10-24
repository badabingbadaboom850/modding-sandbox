# Girls running off: 5% normal rate

There is a 5% chance per eligible ordinary solo wild/trainer battle that one
conscious non-egg family girl is randomly unavailable. The user confirmed the
freeze fix works and approved returning to the planned normal rate.
Riko follows a snack bag, Bijuu a mouse and Penny Dad's keys. A battle-intro
message announces her departure before the player sends out. This version
uses text rather than a new departure sprite animation.

She remains in the party with her actual HP, status, items and species.
Battle-only identity follows party-menu reordering. Shared eligibility,
lead selection, doubles slots, switch availability, forced random switching,
reserve counts, loss detection, experience eligibility and party item use
exclude her. She appears in the menu with an alternate palette and Summary
access. No saved variable, flag, species, trainer, item or save array changes.
One missing member cannot prevent a normal loss. Cleanup clears the restriction
before field callbacks and through common battle resource teardown, including
wins, blackouts, escape, captures and other endings.

Runoff never leaves fewer than one starter in singles or two in doubles.
Eggs, fainted girls and Spirit boss species do not qualify. Duplicate family
identities are skipped so a clone cannot make two slots unavailable. Borrowed
partner/multi parties, link/recorded battles, Frontier, Safari, tutorials,
first battle, e-reader and Trainer Hill formats retain their original behavior.
Normal solo bosses and doubles are eligible. Existing tests default to0;
explicit native battle fixtures opt into100 without changing production flags.

The home mailbox is a normal sign again: both Goldenrod and island test offers
have been removed from its active script. The Goldenrod organizer no longer
offers a test trip home. Historical island-preview return mode still routes
existing preview saves home safely; earned progress is untouched.

Validate with test/trio_runoff.c and tools/runoff/validate.py, plus the existing
parade scripts/geometry/ROM checks. Rendered battle text, all three party-menu
styles, parade playback and an actual player save/reload need emulator testing.
Keep PR2 draft and unmerged. Do not relocate the festival or trials as part of
this feature; that pacing change has not been authorized yet.

Validation: RELEASE production build32,728,292 linked bytes, EWRAM255,432,
padded32MiB passed. All26 focused native checks passed plus7 intentional
harness failures, zero unexpected failures. Nine new run-off checks include
actual intro text, missing lead, doubles, exhausted available team, temporary
identity, item rejection, formats/forms and saved ABI. Greg/parade/Spirit Mega
regressions passed. Five parade source groups and12 test travel paths passed;
production-ROM travel hooks, helper registrations, actors and music passed.

## Fast trainer-intro freeze repair

The user confirmed the Pom Parade works, but reported a freeze after the
run-off message and before the player's send-out. The fast trainer-intro gate
originally waited while the opponent healthbox callback was idle, expecting
its slide to start. The added multi-page departure text could outlast that
slide; its completed callback was idle again and the gate waited forever.
Recorded-battle flags in previous fixtures bypassed this production-only gate.

The gate now recognizes an announced departure and accepts an already finished
slide after the text controller completes. Normal intros without run-off keep
existing behavior. A production-flags regression exercises the idle healthbox
for Riko/Bijuu/Penny, plus ordinary and recorded controls. All27 focused checks
pass with7 intentional harness failures and zero unexpected failures. Nine
run-off tests also pass with emulator rendering enabled. RELEASE32728472 linked
bytes/EWRAM255432, existing ROM travel/parade registrations and all33 reusable
form-item/history checks pass. The user confirmed this repair works in ManicEMU.
Use a normal in-game save before the battle when replacing the ROM; a snapshot
of the old frozen battle retains the old execution state.
