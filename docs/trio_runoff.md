# Girls running off: 100% testing build

One conscious non-egg family girl is randomly unavailable for each ordinary
solo wild/trainer battle. The user authorized a temporary100% rate to test;
TRIO_RUNOFF_CHANCE in include/trio_runoff.h will become5 after approval.
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

The home mailbox now offers TEST travel to Goldenrod30,24 before its existing
island offer. The organizer at30,25 offers the parade. Decline the parade and
accept her TEST trip home to New Bark18,12; declining both preserves original
dialogue. Travel grants no Badges/items, changes no quest progress and records
no island departure. Existing earned memories and Greg wins stay intact.

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
