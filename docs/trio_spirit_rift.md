# Spirit Rift

The Rift is an optional family adventure between the Goldenrod festival and Scott's planned ultimate arena. It never blocks Johto, Kanto, the League, the snack cartel, or any existing Spirit trial. Existing saves can enter when eligible; no new save is required. No party form is forcibly changed.

## Progression design

| Chapter | Entry and gate | Gameplay | Planned reward |
| --- | --- | --- | --- |
| Riko: Echo Woods | Old man at (10,6), Goldenrod Center, after festival picnic | Three bark pads open paths; Bijuu calms a lonely echo, Penny helps call the final guardian | Implemented: Riko's Wand, scrapbook memory |
| Bijuu: Mirror House | Proposed: Ecruteak, after Echo Woods and Badge05 | Clues about ordinary family habits distinguish real Bijuu from flattering copies; Riko and Penny corroborate | Planned: mirror keepsake and memory |
| Penny: Lantern Trail | Proposed: Olivine, after Mirror House and Badge06 | Sisters hold safe points while Penny lights a garden one step at a time; pauses never count as failure | Planned: lantern keepsake and memory |
| Shared sanctuary | Proposed: Goldenrod guide, all three chapters plus Badge08 | Three connected wings revisit bark, reflection and light mechanics; sisters open the final door together | Planned: shared keepsake and invitation to Scott's arena |
| Scott's ultimate arena | Planned after sanctuary and Champion | Extremely difficult rival team using maxed Spirit forms; optional indefinitely | Undecided |

Only Echo Woods is implemented. Later locations, gates and rewards are design defaults, subject to map review. The shared boss is proposed as a lonely echo that imitates the girls' powers, then learns what makes a family; battle species and difficulty remain to be selected. Existing permanent forms add clues/dialogue, never mandatory purchases or forced evolution. Spirit boss species remain distinct from party forms and battle Mega transformations.

## First playable chapter

The Center's ninth NPC is the old man at (10,6), separate from the festival guide at (9,5). After `FLAG_TRIO_FESTIVAL_PICNIC`, he offers an optional trip with the full trio. Declining changes nothing. Warp destination is (12,27) on a new 24x30 map using existing Johto General/National Park tilesets, no cave, weather callbacks, connections or wild encounter table.

For quick testing, finishing the festival picnic offers an optional direct warp to Echo Woods after either Scott outcome. If declined, the festival host at (16,47) repeats the offer on later interactions after the picnic. No festival completion, Badges, party members or Rift progress are granted by the shortcut. The original host menu follows a decline; Center entry and both Woods exits remain.

Bottom clearing: Riko (9,26), first echo pad (10,26), exit guide (9,27). Second clearing: Bijuu (14,21), pad (10,21). Third: Penny (9,13), pad (10,13). Final clearing: Riko Spirit guardian (12,4). Three two-wide corridors at x11-12, rows24-25,16-17,8-9 are blocked until the corresponding pad is accepted. They are restored open on map load from persistent state. Bottom warps (11-12,28) and the exit guide return to Goldenrod. Backtracking always remains possible.

Winged Riko waits rather than flying ahead; Psychic Bijuu feels the echo; guardian-form Penny lowers her shield for her sister. Ordinary forms provide the same progression. All three girls are checked before new puzzle steps or a battle; exits and an earned reward remain available without them.

The guardian explicitly uses the existing safe Spirit-trial lifecycle: heal before/after, temporarily prevent catching, restore previous catch restriction, return after victory/loss/escape without blackout or money loss. This differs intentionally from normal-loss squirrel battles. Level follows highest non-egg party level +5 plus up to five additional levels, capped100. Moves are Flamethrower, Snarl, Swift, Protect. Old Riko cave scripts do not call this setup and remain untouched.

## Save state and rewards

`VAR_TRIO_RIFT_RIKO_STATE = 0x412A`, audited against prior named/raw/numeric source uses, fits unchanged save arrays:

| Value | Meaning |
| --- | --- |
| 0 | No paths opened |
| 1 | First path open |
| 2 | Two paths open |
| 3 | All paths open; guardian retry available |
| 4 | Victory recorded; Wand pending |
| 5 | Wand successfully granted |

Chapter victory and the scrapbook page use state>=4; full Bag does not undo victory. Only a successful `giveitem` advances to5. Return to the guardian for an unclaimed Wand without rebattling, including after leaving/saving. Each reward is once per save; an already owned Wand is allowed because this is an earned spare, and reverse/evolution mechanics are unchanged. New map/layout entries append; original IDs stay stable. No trainer IDs, flags, new species or special IDs are allocated.

## Validation and playtest

Automated source-flow/decoded geometry checks are in `tools/rift/validate_rift.py`; actual guardian setup tests are in `test/trio_rift.c`. Compilation, engine checks, source simulation, decoded map preview and rendered emulator confirmation are separate evidence.

Interactive checklist: existing festival-complete save enters; pre-festival save is refused; decline works; all three pads reveal actual paths; save/reload in each clearing restores opened paths; leave and return from each stage; base/evolved dialogues; decline guardian; lose/escape and retry without blackout; win and reclaim with full Bag; repeated claim does not duplicate; replay through Mom's scrapbook; original festival/Center/story/cave behavior stays intact. No temporary startup/test warp tools are added.
