# Family signature moves and Scott tutor

Scott temporarily stands in New Bark at (20,14), south of the player's house,
for the user-authorized test encounter. He uses the established Brendan/Scott
appearance. Choose a girl, a move, read its explanation, confirm and select a
party member. Normal replacement/cancel prompts remain. Lessons are free and
repeatable; no Badges, items, flags, variables or progress are granted/reset.
The production location will be chosen after rendered testing.

Six new signatures per girl support Penny's patient defense/healing, Bijuu's
fast aggression and Riko's attitude. Riko also has Floof Fury and Pom Supremacy
(the old Mega Riko move, same ID and behavior). Personal forms and their Megas
qualify through the established form-family metadata. Boss Spirits, other
species and Eggs do not. Form changes keep learned moves as normal.

New moves append after historical Z/Max IDs. Every existing move ID and saved
structure stays unchanged; new IDs fit the existing 11-bit move fields.
MOVES_COUNT retains its historical ordinary-move boundary; the new tutor-only
moves are outside the existing random Metronome pool. MOVES_COUNT_ALL includes
them. The runtime heap-backed relearner capacity rises160 ->192 because the
generated tutor pool includes these lessons; no saved array changes. Normal Z/Max generation is driven by registered type/category data.
IS_STANDARD_MOVE distinguishes the appended signatures from historical Z/Max
ranges for battle names, scripted gifts, trainer/contest validation and the
battle test runner. Trainer deduplication uses a temporary stack bitset sized
for MOVES_COUNT_ALL; no saved fields are involved.

Safe With You cures an effective major status and raises only Sp.Def by one
stage. With no status it still raises Sp.Def; at capped Sp.Def it can still
cure status. Both unavailable fails normally. Contrary/Simple use the existing
stat-change path. Sleep/freeze can prevent acting under normal battle rules.
Long Game uses the standard binding duration and switch restrictions.
Excuse You uses Revenge's damage-trigger behavior at ordinary priority.
All new moves initially reuse established animations. Headless tests do not
replace rendered tutor/summary/animation/real save/reload confirmation.

| Girl | Move | Power / Accuracy / PP | Effect |
| --- | --- | --- | --- |
| Penny | Blankey Time | 0 / 0 / 5 | Restores half the user's HP. |
| Penny | Good Girl Guard | 0 / 0 / 10 | Protects for a turn. Repeated use may fail. |
| Penny | Penny Patience | 0 / 0 / 15 | Raises Defense and Sp. Def by one stage. |
| Penny | Tiny Nibbles | 60 / 100 / 15 | Little bites restore HP equal to half the damage. |
| Penny | Long Game | 35 / 100 / 15 | Traps and chips away at the foe for several turns. |
| Penny | Safe With You | 0 / 0 / 10 | Cures the user's status and raises Sp. Def. |
| Bijuu | Cocoa Pounce | 75 / 100 / 15 | Pounces on the foe and lowers its Attack. |
| Bijuu | Backyard Blitz | 40 / 100 / 20 | A backyard dash that strikes with priority. |
| Bijuu | Midnight Zoom | 70 / 100 / 15 | Attacks, then switches with another party member. |
| Bijuu | Claw Enforcement | 85 / 100 / 10 | Breaks protective screens before striking the foe. |
| Bijuu | Cocoa Chaos | 0 / 0 / 15 | Raises Attack and Speed by one stage. |
| Bijuu | Absolutely Feral | 120 / 100 / 10 | A wild attack with recoil of one-third the damage. |
| Riko | Pom Tantrum | 80 / 100 / 15 | A dramatic blast that may lower the foe's Sp. Def. |
| Riko | Excuse You | 60 / 100 / 10 | Hits twice as hard if hurt by the target this turn. |
| Riko | Side Eye | 0 / 100 / 15 | Lowers the foe's Attack and Sp. Atk by one stage. |
| Riko | Main Character | 0 / 0 / 15 | Raises Sp. Atk and Sp. Def by one stage. |
| Riko | Last Word | 40 / 100 / 20 | A sharp comeback that strikes with priority. |
| Riko | Drama Queen | 130 / 90 / 5 | A huge blast that lowers the user's Sp. Atk by two. |

Validation:50 focused engine/battle/storage/metadata checks pass, plus7 expected
runner self-test failures and zero unexpected failures. Includes18 actual-effect
smoke parameters, all personal/Mega family eligibility, capped/no-status/cured
Safe With You, Contrary/Simple, correct drain ratio, setup/debuffs, personalized
battle names and compressed move storage; Spirit Megas/cafe/cavern/trainer
regressions are included. The source validator checks all975 historical IDs,
20 lesson/decline/cancel paths, text references/wrapping and Scott's geometry.
Cafe source tests and docs-summary/diff checks pass. Rendered tutor UI, move
animations and an actual player's save/reload remain for user confirmation.

## Current-form elemental lessons

Scott now offers Signature moves or Elemental moves. Elemental lessons first
choose a party member, then show damaging non-Normal attacks matching either
current species type in that form's level-up learnset. Actual level applies,
including level-zero transformation attacks; known moves and duplicates hide.
No previous-form or pre-evolution learnsets are imported, and no TM/tutor pages
can be opened from this service. Unrelated Pokemon, Eggs and boss Spirits are
ineligible. Empty lists explain changing form or gaining levels. Teaching and
replacement use the existing free relearner; cancellation returns to Scott,
and normal relearner mode is restored on every exit. Equipped attacks remain
when a girl changes form. There is no saved unlock history or save ABI change.

Emulator check: transform Riko to Electric, select Elemental moves, teach an
available attack, cancel replacement once, then teach successfully. Change her
to Fire and confirm the new list; retain the equipped Electric attack. Repeat
with Water Penny and Ice Bijuu, then save in-game and reload. Higher-level
attacks still require their learnset level; TMs supplement the modest Ice/Water
learnsets.

Elemental validation: RELEASE=1 production ROM compiled (32447576 bytes ROM,
255416 bytes EWRAM). All52 focused engine/battle checks pass, plus7 expected
runner self-test failures and no unexpected failures. Includes current-form
selection, actual-level limits, deduplication/known moves, transformation
attacks, family/Egg exclusions, equipped-move retention and mode reset.
Source service/empty/cancel flows, historic move IDs/save files, text, docs
and diff checks pass. ManicEMU UI and in-game save/reload remain user checks.
