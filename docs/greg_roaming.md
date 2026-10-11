# Greg everywhere

Greg now has15 custom appearances: the original Route29, Cherrygrove and Route30
encounters plus twelve independent Johto/Kanto stops. Route37's original Psychic
Greg remains a separate ordinary trainer. All original scripts/wins/rewards remain.

| New stop | Coordinates | Trainer alias |
| --- | --- | --- |
| Goldenrod | 49,37 | 1080 |
| Route38 | 32,16 | 1081 |
| Ecruteak | 52,40 | 1082 |
| Cianwood | 20,46 | 1083 |
| Route42 | 65,14 | 1084 |
| Blackthorn | 35,43 | 1085 |
| Pewter | 26,23 | 1086 |
| Cerulean | 31,21 | 1087 |
| Vermilion | 33,21 | 1088 |
| Celadon | 30,25 | 1089 |
| Fuchsia | 20,33 | 1090 |
| Saffron | 28,41 | 1091 |

New Gregs face down with a two-tile sight line, using the original man graphic.
They automatically challenge players in sight and can also be talked to. Each
sideline has a walkable route around the whole sight line, stays clear of doors,
triggers/signs and fits the conservative16-object viewport budget including player
and follower. Existing object indices, actors, scripts, services, warps and maps
stay intact; only one new last actor is appended per map. Cianwood checks include
ordinary walkable beach sand. No compulsory route-entry ambush is added.

All twelve copy the original six level99 Pokemon/items/IVs/EVs/moves. Losses use
ordinary blackouts and leave Greg waiting; winning quiets that stop's automatic
challenges permanently. Other Gregs remain undefeated until actually beaten.
There are no friendly heals, quest resets, new Badge gates or rematch timers.
New intro/defeat/after jokes have local personality, shameless Garchomp bragging,
Scott/family callbacks and excuses. No optional scene or Badge victory is assumed.

Examples: Scott's dinner plans become six level99 problems; Erika grows flowers
while Greg grows increasingly unbearable; a sea breeze means Greg demands a rematch
in a vacuum; crossing the ocean fails to escape him. Old Caleb/Garchomp, Aunt Susan
and Joey jokes and later Badge/Champion banter remain byte-for-byte unchanged.

All encounters share FLAG_GREG_WAWA_REWARDED. The first successful gift is one
small Wawa. Full Bags can retry by talking after the win without another battle;
older rewarded saves never receive extras. No other item/progress flag is changed.

Trainer aliases1080-1091 refer to existing UNUSED216-227 slots, with no changes to
old constants or MAX_TRAINERS_COUNT1164. Their ordinary flag addresses0x938-0x943
belong to unrelated replay/story state, so Greg MUST NEVER read or write those.
VAR_TRIO_GREG_WINS4145 uses12 bits of the existing saved variable array. The actual
trainer sight/interaction/won APIs and normal victory setter all use those bits;
clear/set APIs preserve every other bit. Older saves default this unused variable
to zero. Saved structs/arrays, startup, old Greg wins and earned progress remain.

Implementation: include/trio_greg.h, src/trio_greg.c, battle_setup.c guards,
data/scripts/trio_greg_roaming.inc, map JSON actors, trainer aliases/party entries.
No new art assets are needed. New labels are globally included and active object
pointers are checked in the production ROM. Generated map-event IDs append.

Validation:44 focused engine/battle checks pass plus21 intentional harness failures
and zero unexpected failures. Three Greg tests cover independent wins/all trainer
APIs, reclaimed flags in four prior-state patterns, old wins/Wawa/neighbor progress
and saved ABI. Squirrel chase, Road Trip, hats and Spirit Mega checks pass.
Source checks cover twelve sight-line bypasses, original map/event/party history,
38 text boxes, shared Wawa/full-Bag retry and trainer hooks. Seven squirrel source
groups pass; its validator now tolerates appended Gregs while retaining hideout IDs
and checks the actual flag-guard function bodies. Production ROM validation confirms
72 level99 Pokemon, their authored moves and twelve NPC/script/text registrations.
Rendered sightings, trainer approaches and actual save/reload remain user testing.
Keep PR2 draft/unmerged.
