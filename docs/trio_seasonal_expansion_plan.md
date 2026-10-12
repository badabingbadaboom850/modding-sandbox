# Permanent seasonal chapters

Implemented on PR2's draft branch following approval of varied replay rounds and
small snack rewards. These four optional chapters stay open permanently after
their story milestone. There is no calendar check, timer, compulsory battle or
party edit. Halloween remains after Chuck's fifth Badge in western Olivine Cafe;
its authorized New Bark mailbox preview and pending saves are preserved.

| Chapter | Stationary host | Opens after | Game | One snack per win |
| --- | --- | --- | --- | --- |
| Leaf-Pile Picnic | Mahogany Pokemon Center,5,6 | Jasmine's sixth Badge | Search three named leaf piles in the saved clue order | Small Wawa (`ITEM_POTION`) |
| Thankful Table | Blackthorn Pokemon Center,5,6 | All eight Johto Badges | Choose the feast recipe props in the saved order | Medium Wawa (`ITEM_SUPER_POTION`) |
| Three Little Helpers | Celadon Pokemon Center,5,6 | Hall of Fame Champion flag | Deliver to the three sisters in the saved gift order | Medium Wawa (`ITEM_SUPER_POTION`) |
| Midnight Pawty | Saffron Pokemon Center,5,6 | All sixteen Badges | Repeat a three-beat Pom/Meow/Wag rhythm | One Riko Puffs |

Each round chooses one of three clue patterns. Accepting a new round saves the
pattern; re-entry, hints and reloads never reroll it. Wrong or repeated choices
preserve progress. Later/B cancellation, both exits and saving preserve the
unfinished round. After winning, the host resumes claims before offering a new
round. The first win gives three permanent costume items in order, then a snack;
later wins give only the snack. Pre-owned costumes are acknowledged without a
second copy. A full Bag leaves the next gift or snack pending. Successfully
claimed gifts stay claimed across reloads; a second visit cannot duplicate them.
Repeated random patterns are possible; the games have three available variants.

| Chapter | Riko | Bijuu | Penny |
| --- | --- | --- | --- |
| Fall | Leaf pile | Sage knit and burgundy scarf | Pink cardigan |
| Thanksgiving | Turkey feather fan | Chef hat and apron | Sweet potato wrap |
| Christmas | Santa hat and coat | Green present with red ribbon | Antlers and scarf |
| New Year | Golden party hat | Silver bow and collar | Pink star dress |

Twelve protected, zero-price Key Items append at978-989; sixteen species append
at1641-1656 because Penny keeps both ordinary and Dachsbun costume stages. Each
item toggles its ordinary family stage to its costume and back through normal
evolution routing. Costume stats, types, abilities, growth, learnsets, signature
eligibility and female identity match the corresponding ordinary stage. Dressed
Penny still evolves at level26. Normal/Spirit Mega entry and exact-form return
use the established tables. No transformation consumes the reusable item.

Every costume has native indexed front/back, menu icon, six distinct follower
poses, item icon and matching normal/shiny palettes. The native importer isolates
poses before cropping, avoiding the adjacent-tail problem previously fixed for
Pumpkin Penny. Original source atlases are committed for reproducibility.

The old16bit photo mask keeps all original bits, including Poison. Twelve new
portraits use `VAR_TRIO_SEASONAL_PHOTOS` at0x414B; all four Penny evolved stages
share their outfit page. Album menus append four pages per girl, with locked
pages, Back/B cleanup and new outfit/Scott reactions. The outfit count is27 plus
the existing Poison bonus page, which stays excluded from the displayed count.

Each chapter uses five appended saved variables: STATE(0idle,1active,2won),
ROUND(0-2), PROGRESS(0-3), GIFTS(0-3 sequential costume claims), SNACK(0pending,
1claimed). These occupy0x414C-0x415F and were audited for prior raw hexadecimal
and decimal use. Existing saves see zero/unearned seasonal state. No save-array,
Bag capacity, save structure, historical flag/species/item/map ID is changed.
The existing50-slot Key Items limit remains; a full pocket keeps prizes pending.

Four new garden stages append within the relevant indoor map groups. Original
Center actors, services, scripts and warp IDs remain. Added hosts are stationary
and have reachable approaches. Explicit return exits land at the source
Center7,7; boundary warps return through its original entrance0. Original
Halloween behavior is unchanged.

Validation: `tools/costumes/validate_seasonal.py` executes1238 actual source
branches, audits old save/numeric usage, all host/stage approaches, actor limits,
production map constants, native art registration, palettes, frame differences,
metadata and actual font widths. Existing Halloween3454-branch checks,30origin
returns,30pre-Badge normal/preview paths and Pumpkin Penny native crop regression
remain. All51 family transformation items are audited reusable (38Key/13Items);
all51 descriptions fit actual102px Bag text. Engine costume, dressed evolution,
photo preservation and Mega tests now include every seasonal form.

These checks do not establish rendered emulator behavior. Use the focused pass
in `trio_costume_emulator_pass.md` for animation, evolutions, follower movement,
boxing, fainting, reusable Bag items, actual save/reload, old saves and all chapter
routes/replays. PR2 remains draft and unmerged; CI ROM/full engine results are
reported separately from source/native checks.
