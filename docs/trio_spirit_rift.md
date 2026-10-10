# Spirit Rift

The Rift is an optional family adventure between the Goldenrod festival and Scott's planned ultimate arena. It never blocks Johto, Kanto, the League, the snack cartel, or any existing Spirit trial. Existing saves can enter when eligible; no new save is required. No party form is forcibly changed.

## Progression design

| Chapter | Entry and gate | Gameplay | Planned reward |
| --- | --- | --- | --- |
| Riko: Echo Woods | Old man at (10,6), Goldenrod Center, after festival picnic | Three bark pads open paths; Bijuu calms a lonely echo, Penny helps call the final guardian | Implemented: reusable Riko's Courage, two-headed Echo form, scrapbook memory |
| Bijuu: Mirror House | Ecruteak Center guide (10,6), after earning Riko's Courage; Goldenrod/festival shortcut | Clues about ordinary family habits distinguish real Bijuu from flattering copies; Riko and Penny corroborate | Implemented: Bijuu's Fire, Ember form and memory |
| Penny: Lantern Trail | Olivine Center guide (10,6), after earning Bijuu's Fire; Goldenrod/festival shortcut | Sisters hold safe points while Penny lights a garden one step at a time; pauses never count as failure | Implemented: Penny's Bravery, Brave form and memory |
| Shared sanctuary | Proposed: Goldenrod guide, all three chapters plus Badge08 | Three connected wings revisit bark, reflection and light mechanics; sisters open the final door together | Planned: shared keepsake and invitation to Scott's arena |
| Scott's ultimate arena | Planned after sanctuary and Champion | Extremely difficult rival team using maxed Spirit forms; optional indefinitely | Undecided |

All three personal chapters are implemented. The shared sanctuary and Scott arena remain design defaults, subject to map review. The shared boss is proposed as a lonely echo that imitates the girls' powers, then learns what makes a family; battle species and difficulty remain to be selected. Existing permanent forms add clues/dialogue, never mandatory purchases or forced evolution. Spirit boss species remain distinct from party forms and battle Mega transformations.

## First playable chapter

The Center's ninth NPC is the old man at (10,6), separate from the festival guide at (9,5). After `FLAG_TRIO_FESTIVAL_PICNIC`, he offers an optional trip with the full trio. Declining changes nothing. Warp destination is (12,27) on a new 24x30 map using existing Johto General/National Park tilesets, no cave, weather callbacks, connections or wild encounter table.

For quick testing, finishing the festival picnic offers an optional direct warp to the next unfinished Rift chapter after either Scott outcome. If declined, the festival host at (16,47) repeats the offer on later interactions after the picnic. No festival completion, Badges, party members or Rift progress are granted by the shortcut. The original host menu follows a decline; Center entry and both Woods exits remain. The Goldenrod Center guide follows the same next-chapter routing. After all three charms are collected, declining earlier revisit offers lets you select Mirror House or Lantern Trail. No later Badge requirement prevents testing these chapters after the festival.

Bottom clearing: Riko (13,27), first echo pad (10,26), exit guide (9,27). Second clearing: Bijuu (14,21), pad (10,21). Third: Penny (9,13), pad (10,13). Final clearing: two-headed Riko Echo guardian (12,4). Three two-wide corridors at x11-12, rows24-25,16-17,8-9 are blocked until the corresponding pad is accepted. They are restored open on map load from persistent state. Bottom warps (11-12,28) and the exit guide return to Goldenrod. Backtracking always remains possible.

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

## Bijuu's Mirror House

The optional Ecruteak Center old man at (10,6) offers entry after Riko's Courage is claimed; the Goldenrod/festival guide offers the same trip. The 13x10 room is derived from a normal Johto house, with furniture cleared from the playable floor. Entry (4,7), guide (2,7), real door warp (4,8) and the guide return to Goldenrod Center. Normal house tiles and callbacks are used; no old cave foundation is involved.

Listen to Riko at (1,6), then Penny at (9,6), before choosing the real Bijuu at (8,4). The copies at (2,4)/(5,4) brag about crowds or abandoning her sisters; the real cat remembers being a cocoa, loving the backyard and staying with a worried Penny. Wrong copies and declining never reset clues. Two-headed Riko and guardian Penny add supportive lines. After finding Bijuu, the Ember guardian at (5,2) offers an optional level1 fight, then Bijuu's Fire. Completed/pending rewards can be collected without a party or rebattle.

`VAR_TRIO_RIFT_BIJUU_STATE = 0x412B` saves0=no clues,1=Riko clue,2=both clues,3=real Bijuu identified,4=victory/gift pending,5=charm collected. `FLAG_TRIO_RIFT_FIRE_RECEIVED = 0x108A` records successful charm receipt. Bijuu's Fire is a reusable protected Key Item: ordinary or Psychic Bijuu -> Bijuu Ember, Ember -> ordinary Bijuu. Ember is female Normal/Fire, with a small tail flame and Ember learned on evolution. This is not the final Spirit or a Mega branch. Its base stats are80/85/70/120/110/85.

## Penny's Lantern Trail

The optional Olivine Center old man at (10,6) offers entry after Bijuu's Fire is claimed; the Goldenrod/festival guide offers the same trip. This new garden reuses the tested Woods geometry/tilesets, with a separate saved puzzle state. Lantern orbs at (10,26)/(10,21)/(10,13) open the passages in order. Riko waits at (13,27), Bijuu at (14,21), Penny at (9,13) and Brave Penny's guardian at (12,4). Existing lower exit guide and automatic south-arrow exits remain open.

A modest darkness radius4 starts the garden. Each lantern uses the established gym `animateflash` mechanism to brighten to3,2,then0; transition scripts reconstruct the radius from progress. The saved state also reconstructs open paths. Guide exit explicitly clears darkness; normal destination maps reset it. There is no weather/cave callback or field Flash requirement. Bijuu's Ember form supplies an extra supportive line about using her fire to warm a sister, not showing off. The guardian is an optional level1 fight using the same safe lifecycle as the other introductions.

`VAR_TRIO_RIFT_PENNY_STATE = 0x412C` saves0-3 lantern count,4=victory/gift pending,5=charm collected. `FLAG_TRIO_RIFT_BRAVERY_RECEIVED = 0x108B` records successful receipt. Penny's Bravery is a reusable protected Key Item: Fidough, Dachsbun or existing Guardian Penny -> Penny Brave, Brave -> starter Fidough/Penny. The lightly armored blonde dachshund has no shield or magic barrier. She is female Fairy with85/90/100/85/55/85 base stats and learns Helping Hand on evolution. Existing Guardian/elemental forms and final Spirit remain separate.

Both new victories add Mom's scrapbook Sister memories. Maps38/39 append to IndoorGoldenrod; layouts1031/1032 append after Echo Woods. Species1608/1609 and items950/951 append after existing real IDs. The new flags/variables were audited free against baseline3dd224e0. SaveBlock1/2/3 sizes and saved field offsets match that baseline under the production ARM ABI. No new save, start grant, free Badge, trainer ID or forced party transformation is introduced.

Automated script simulation covers clue order, wrong copies, declines, absent girls, losses/escape, full Bag/repeated claims, light/path reconstruction from saved states, travel gates/revisit routing, reachable NPCs/exits and original map/layout stability. Actual engine tests in `test/rift_sisters.c` cover evolution targets, Key Item metadata, species/art registration, female/full-health level1 guardians, retained party level/species and Camp counters. Source/decoded asset checks and compilation are separate from interactive rendering. Still playtest both entries/exits, mirror selection, light animation, loss/retry, item evolution/reversion, followers and real save/reload with an existing save.

## Midgame art production

Built-in image generation supplied the two portrait source sheets, then `tools/rift/import_sisters_assets.py` deterministically imported the GBA frames. Final assets live in `graphics/pokemon/bijuu_ember/` and `graphics/pokemon/penny_brave/`; charm icons are `graphics/items/icons/bijuus_fire.png` and `graphics/items/icons/pennys_bravery.png`. Both retain palette index0 transparency and use frame-aware follower conversion.

Prompt set: Bijuu is a female cream Siamese with dark chocolate points and blue eyes, with only a small orange/gold flame at the tip of her ordinary tail, no armor/wings/extra tails/large Spirit aura. Penny is a female blonde long-bodied dachshund with floppy ears and short legs, simple small bronze shoulder plates/chest plate, visible fur, no shield/magic barrier/weapon/helmet. Both use chunky GBA pixel art, limited warm palettes, dark outlines and genuine transparency. Each portrait1024x1536 sheet has three columns/four rows: front battle/back battle/menu; down stand/down step/right stand; right step/up stand/up step; centered charm with empty side cells. Bijuu's charm is a flame enclosing a blue paw; Penny's is a bronze heart enclosing a blonde paw. All sprites have transparent padding and simple silhouettes suitable for64x64 battle,32x32 follower and24x24 icon reduction.
