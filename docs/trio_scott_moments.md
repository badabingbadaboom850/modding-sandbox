# Scott's gym-city moments

Four optional stops pace the Johto journey around every second Gym Badge. Talk to the new Scott (Silver graphic) and accept his invitation. Before the relevant victory he cheers her on; declining saves nothing and leaves the invitation available. Returning after an accepted scene offers a replay.

| City | Gate | Where Scott stands | Moment |
| --- | --- | --- | --- |
| Azalea | Bugsy, Badge02 | East path south of Slowpoke Well, (46,16) | A proud check-in, with praise for all three girls |
| Ecruteak | Morty, Badge04 | Garden beside the northern pond, west of Tin Tower, (29,23) | Tea and a quiet date |
| Olivine | Jasmine, Badge06 | Grass south of the lighthouse entrance, (37,51) | A seaside snack and a little flirting |
| Blackthorn | Clair, Badge08 | Outside the Pokemon Center, (25,50) | Pride, a kiss and encouragement before the League |

Clair's gate is the actual Badge awarded in the Dragon's Den shrine, rather than the initial Gym defeat. All four moments use their individual Badge flags, so beating another leader early cannot unlock the wrong praise. There is no time-of-day, party, reward, inventory or battle requirement. Dialogue assumes the girls are with her, as requested for this personalized adventure.

Mom's Scrapbook has a new **Scott moments** category. Saved scenes replay; waiting pages show a location and the leader to beat. Memory checklist also shows saved/waiting status. The category keeps the existing four menu indices and appends its new entry before Exit. Original story rivals, residents, map callbacks, warps and event IDs are unchanged; the new objects are appended.

Existing saves can visit all earned stops in any order. Flags `0x1081`–`0x1084` record only accepted moments and fit the existing save arrays. Merely opening the scrapbook or checklist does not mark scenes seen. Replaying a scene writes no flags and gives no duplicate rewards. Normal starting parties and festival testing remain unchanged (`TRIO_FESTIVAL_TEST_MODE 0`).

## Verification

`python tools/moments/validate_scott_moments.py` interprets the actual new event scripts and decodes the four maps' collision/behavior data. Six groups cover exact Badge gates, decline/retry, all 24 visit orders, repeat/decline replay, all 16 scrapbook/checklist combinations, lock release, unchanged original events, reachable approaches, conservative object budgets, separate original-rival viewports, registration/labels, two-line text pages and flag allocation. These are source checks, not a rendered emulator test.

Interactive checklist:

1. Load a save before a relevant Badge and talk to Scott: he should offer encouragement without recording a page.
2. Earn the Badge normally. Decline once, then accept. Verify the complete scene and the scrapbook notification.
3. Revisit, decline the replay, then accept it. Verify normal walking resumes after each interaction.
4. Use Mom's Scrapbook: open Scott moments, read saved scenes and waiting hints, then return and exit. Read the checklist as well.
5. Save, reload and revisit. Use an advanced existing save to catch up in any order; read saved pages with the girls absent from the party.
6. Check the original Azalea rival, Ecruteak theater/Tin Tower access, Olivine rival/lighthouse and Blackthorn Dragon's Den, Center and Spirit events. Scott's additions must not intercept them.

A local ROM build and the source checks establish compilation and the tested source paths. GitHub CI and rendered gameplay/save-reload results are separate.
