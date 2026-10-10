# Spirit Rift

The Rift is an optional family adventure between the Goldenrod festival and Scott's planned ultimate arena. It never blocks Johto, Kanto, the League, the snack cartel, or any existing Spirit trial. Existing saves can enter when eligible; no new save is required. No party form is forcibly changed.

## Progression design

| Chapter | Entry and gate | Gameplay | Planned reward |
| --- | --- | --- | --- |
| Riko: Echo Woods | Old man at (10,6), Goldenrod Center, after festival picnic | Three bark pads open paths; Bijuu calms a lonely echo, Penny helps call the final guardian | Implemented: reusable Riko's Courage, two-headed Echo form, scrapbook memory |
| Bijuu: Mirror House | Proposed: Ecruteak, after Echo Woods and Badge05 | Clues about ordinary family habits distinguish real Bijuu from flattering copies; Riko and Penny corroborate | Planned: mirror keepsake and memory |
| Penny: Lantern Trail | Proposed: Olivine, after Mirror House and Badge06 | Sisters hold safe points while Penny lights a garden one step at a time; pauses never count as failure | Planned: lantern keepsake and memory |
| Shared sanctuary | Proposed: Goldenrod guide, all three chapters plus Badge08 | Three connected wings revisit bark, reflection and light mechanics; sisters open the final door together | Planned: shared keepsake and invitation to Scott's arena |
| Scott's ultimate arena | Planned after sanctuary and Champion | Extremely difficult rival team using maxed Spirit forms; optional indefinitely | Undecided |

Only Echo Woods is implemented. Later locations, gates and rewards are design defaults, subject to map review. The shared boss is proposed as a lonely echo that imitates the girls' powers, then learns what makes a family; battle species and difficulty remain to be selected. Existing permanent forms add clues/dialogue, never mandatory purchases or forced evolution. Spirit boss species remain distinct from party forms and battle Mega transformations.

## First playable chapter

The Center's ninth NPC is the old man at (10,6), separate from the festival guide at (9,5). After `FLAG_TRIO_FESTIVAL_PICNIC`, he offers an optional trip with the full trio. Declining changes nothing. Warp destination is (12,27) on a new 24x30 map using existing Johto General/National Park tilesets, no cave, weather callbacks, connections or wild encounter table.

For quick testing, finishing the festival picnic offers an optional direct warp to Echo Woods after either Scott outcome. If declined, the festival host at (16,47) repeats the offer on later interactions after the picnic. No festival completion, Badges, party members or Rift progress are granted by the shortcut. The original host menu follows a decline; Center entry and both Woods exits remain.

Bottom clearing: Riko (9,26), first echo pad (10,26), exit guide (9,27). Second clearing: Bijuu (14,21), pad (10,21). Third: Penny (9,13), pad (10,13). Final clearing: two-headed Riko Echo guardian (12,4). Three two-wide corridors at x11-12, rows24-25,16-17,8-9 are blocked until the corresponding pad is accepted. They are restored open on map load from persistent state. Bottom warps (11-12,28) and the exit guide return to Goldenrod. Backtracking always remains possible.

Winged Riko waits rather than flying ahead; Psychic Bijuu feels the echo; guardian-form Penny lowers her shield for her sister. Ordinary forms provide the same progression. All three girls are checked before new puzzle steps or a battle; exits and an earned reward remain available without them.

The guardian explicitly uses the existing safe Spirit-trial lifecycle: heal before/after, temporarily prevent catching, restore previous catch restriction, return after victory/loss/escape without blackout or money loss. This differs intentionally from normal-loss squirrel battles. The Echo Woods guardian is level1 at the user's request for quick reward/evolution testing. Moves are Disarming Voice, Tackle, Baby-Doll Eyes and Helping Hand. It introduces the midgame form; the three-headed Spirit guardian and existing level90 encounter remain separate endgame content. Old Riko cave scripts do not call this setup and remain untouched.

## Save state and rewards

`VAR_TRIO_RIFT_RIKO_STATE = 0x412A`, audited against prior named/raw/numeric source uses, fits unchanged save arrays:

| Value | Meaning |
| --- | --- |
| 0 | No paths opened |
| 1 | First path open |
| 2 | Two paths open |
| 3 | All paths open; guardian retry available |
| 4 | Victory recorded; Courage pending |
| 5 | Reward successfully granted (older builds granted a Wand) |

Chapter victory and the scrapbook page use state>=4; full Bag does not undo victory. New `FLAG_TRIO_RIFT_COURAGE_RECEIVED = 0x1089` records the actual new reward independently of the old state5. It was free in the baseline source audit and fits the existing flag arrays. Only a successful `giveitem` sets the flag and advances to5. Older state4/5 saves can return to the guardian and claim Courage without the girls or another battle; their existing Wand is preserved. Repeated claims cannot duplicate the charm.

## Riko's Courage and Echo form

Riko's Courage is a reusable, protected Key Item. Use it from the Bag on ordinary or Winged Riko to evolve into the two-headed Normal/Fairy Riko Echo. Use it again on Echo to return to ordinary Riko. Winged Riko remains a separate branch; reverting Echo always produces ordinary Riko. Existing training, identity and moves use the normal evolution system. Echo learns Echoed Voice on evolution and has its own front/back, menu and six-frame follower sprites. Its stats are95/80/90/110/110/95 (HP/Attack/Defense/Speed/Sp. Attack/Sp. Defense), with Cute Charm and hidden Fluffy.

The lore is one Riko whose courage answers her call: two voices, one heart. Bijuu helps her listen and Penny reassures both heads. This is a permanent midgame species, distinct from Spirit boss species and temporary Mega transformations. No automatic evolution is performed by chapter scripts. Final Spirit unlocks and charms remain planned for true endgame, after hard trials such as the existing level90 Riko fight; this change does not grant that final form.

`SPECIES_RIKO_ECHO = 1607` and `ITEM_RIKOS_COURAGE = 949` append after existing real IDs; only the egg/UI sentinels move. No existing real species, item, map or layout IDs change, and save structures/arrays retain their sizes. No trainer IDs or special IDs are allocated.

## Validation and playtest

Automated source-flow/decoded geometry checks are in `tools/rift/validate_rift.py`; actual guardian setup tests are in `test/trio_rift.c`; evolution routing, item metadata and species data checks are in `test/riko_courage.c`. Compilation, engine checks, source simulation, decoded map preview and rendered emulator confirmation are separate evidence.

Interactive checklist: existing festival-complete save enters; pre-festival save is refused; decline works; all three pads reveal actual paths; save/reload in each clearing restores opened paths; leave and return from each stage; base/evolved dialogues; decline guardian; lose/escape and retry without blackout; win and reclaim with full Bag; old Wand-winning save claims Courage without rebattling; repeated claim does not duplicate; use Courage in both directions, check battle/menu/follower art, save/reload each form and confirm the charm remains; replay through Mom's scrapbook; original festival/Center/story/cave behavior stays intact. No temporary startup/test warp tools are added.
