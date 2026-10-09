# The evolving Trio Camp playroom

The girls' room in New Bark's southwest house gradually fills with Scott's gifts and adventure keepsakes. Updates appear on the next visit and work retroactively on existing saves. The girls do not need to be in the party for earned decorations to remain visible. Normal Camp petting, games, favorites, rest, stats and the scrapbook page continue to work.

| Milestone | Visible addition | Interaction |
| --- | --- | --- |
| First Johto Badge | Penny's round cushion, northwest corner (1,2) | A soft spot where Penny is allowed to take up space. |
| Third Johto Badge | Riko's Torchic/chicky plush (3,2), plus a framed travel photo on the west wall | Riko disputes whether the toy can be eaten; the photo remembers the girls' attempts to pose. |
| Fourth Johto Badge | Bijuu's Meowth/cat toy (5,2), plus a soft play mat around her western roaming lane | Bijuu investigates the tiny cat; the girls disagree about whose stage the mat is. |
| Goldenrod festival picnic | Festival cushion (7,2) | A picnic souvenir with a snack-custody joke. Winning Scott's match alone is not the unlock; the completed picnic is. |
| Penny's Spirit encounter completed | Guardian/diamond cushion (10,3) | A reminder that bravery includes having a safe place to return to. Historical home-test wins also qualify. |
| Eight Johto Badges | League display on the north wall (6,1) | A framed achievement and encouragement before the League. |
| Champion | Second north-wall display (8,0), plus Champion commentary at the League display | Scott celebrates the Champion and her girls. |
| Bijuu's Spirit encounter completed | Moon/Clefairy plush (6,8) | Bijuu has claimed the moon. Historical home-test wins also qualify. |

Talk to the host and choose **Room keepsakes** to read the stories of everything currently earned, including the mat and displays. Inspect the six physical gifts directly, the photo from below its west-wall tile, or the League display from below its north-wall tile. Missing upgrades have no item pickup, fee, or inventory requirement. Photos and wall displays use existing interior art as representations rather than new custom portraits or badge icons.

## Implementation and verification

Six new object templates are appended after the room's original eight; existing object IDs, services and the outside warp remain stable. All fourteen templates, player and follower fit the engine's sixteen-object limit. The new gifts do not intersect the original three roaming lanes. Geometry checks cover every combination of the four visual progression flags with all fourteen templates present and verify reachable interactions, the exit, shelf and unchanged collision/elevation masks.

`TrioCamp_UpdateKeepsakes` recomputes only six hide flags (0x107B-0x1080) from existing achievements on transition. These are visibility latches, not new quest rewards. Their raw values were audited free; save array sizes remain unchanged. The helper does not grant Badges, items, Spirit completion, festival progress or counters. Earlier Spirit home-test victory flags remain supported.

A separate on-load script restores the affected sites to the original tiles before applying the earned upgrades. The one new mat-center metatile is appended to the existing House/Lab secondary tileset, preserving every existing tile ID; it composites already-loaded interior graphic tiles and introduces no new palette slot. Other houses sharing that tileset remain unchanged. The existing table and furniture stay intact. The new special is appended after the existing special table entries.

Run `python tools/camp/validate_keepsakes.py` for six actual-script/geometry/registration/text groups, including all sixteen visual combinations, repeated loading and removal of unearned visual upgrades. Headless engine tests in `test/trio_camp_keepsakes.c` check independent achievements, older saves with zero hide flags, historical Spirit wins, unchanged progress and counters. Existing Camp/festival/new-game regressions remain included in targeted verification. These source and headless checks do not establish rendered emulator playtesting. On an updated ROM, enter Camp at each milestone and verify the objects, mat, wall displays, follower movement, host menu and save/reload.

The festival test-mode switch remains 0. Fresh saves still begin normally; no new testing shortcuts or free progression are introduced.

Local verification: the final full ROM compiled successfully; six Camp script/geometry groups and eleven festival groups pass. The targeted headless suite passed 24 checks plus 7 expected runner self-test failures (31 total), including actual keepsake, Camp, festival species and normal fresh-save checks. A 6,938-file source/header/script/map audit found no numeric flag conflicts. Decoded asset previews were inspected; rendered emulator/save-reload confirmation and remote CI remain separate.
