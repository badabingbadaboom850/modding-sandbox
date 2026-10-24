# Scenic family photos and weather reactions

Three permanent, optional photographers use existing gentleman graphics:

| Place | Photographer | Access |
| --- | --- | --- |
| Olivine lighthouse roof | 9,11 | Ordinary lighthouse route/roof access |
| Lake of Rage, south shore | 35,43 | Ordinary Route43 access |
| Ice Path 1F, entrance floor | 13,22 | Ordinary Route44 access |

Talk to a photographer with all three non-egg girls in the party. Personal
forms and costumes count; boss Spirits and eggs do not. A free photo records
one exact species per girl, including Penny's ordinary/evolved costume stage.
The first eligible party member of each family supplies the picture. The
photographer shows three native portrait panels and Scott's location/family
captions. These are scrapbook illustrations, not a screenshot export or a
new scenic bitmap. Clothing/form names identify each saved look.

Mom's Scrapbook adds **Scenic photos** after Outfit album. Choose a place to
view the stored portraits and captions, even after changing forms, storing
keys, depositing the girls or reloading. Empty pages give location hints.
Retaking requires an explicit replacement confirmation and replaces only that
location's three portraits. Declining or missing a girl preserves every page.
No photo needs an item, Bag slot, battle, new badge or earlier chapter.

Saved vars4161-416A append to the existing array: one three-bit ownership mask
and nine exact-species snapshots. No saved structure, historical variable,
map/item/species ID, old costume portrait mask or inventory changes. Invalid
saved identities fail closed before loading a picture. Old saves start with
empty pages. All original map objects, layouts, scripts, weather and services
remain. Three static nontrainer photographers append; no automatic interruption.

Follower comments are selected in the actual GetFollowerAction interaction,
after GetFirstLiveMon and GetCurrentWeather. Rain/downpour/thunderstorm, snow,
sun/drought, fog, sand and ash each have distinct girl-specific comments.
Raincoat Riko has a special rainy line. Ordinary weather and unrelated Pokemon
keep the existing selection. Status conditions and below-half HP also keep
ordinary reactions. No weather changes, stats, random battles, saved cooldowns
or automatic dialogue are introduced. Snow comments only appear if the engine
actually reports snow; Ice Path's ordinary WEATHER_NONE is not treated as snow.

## Verification

Source/native checks and compiled engine tests are separate from rendered
player confirmation. The focused engine suite covers exact forms, evolved
Penny, independent locations, absent party reads, eggs/bosses, invalid data,
old masks and weather selection. The source validator checks actual script
paths, map geometry/reachability, original event preservation, allocations,
text bounds, sprite closing and active follower dispatch.

Player pass: take each photo, decline a retake, retake with different costumes,
read all pages after depositing the girls, save normally and reload. Check
Back/B, full Bag independence, all three portraits/captions and ordinary map
services. At Lake of Rage, talk to healthy raincoat Riko, Bijuu and Penny as
the active follower; repeat with an unrelated Pokemon and an injured girl.
Confirm actual rendered placement, text, portrait panels and save/reload.

Local validation: production ROM compiled (33027000 linked bytes,
EWRAM255436, padded32MiB). All3 new native engine tests passed in the
headless emulator.52 actual-script paths, three decoded placement/reachability
checks, actual-font limits and audited saved slots pass. Actual linked-ROM
photographer/script/special/weather/album registrations pass. Existing1238
seasonal/254wardrobe source paths, all51 reusable-item/description checks and
Halloween/Pumpkin follower regressions pass. Rendered player confirmation and
remote CI are separate from these local checks.
