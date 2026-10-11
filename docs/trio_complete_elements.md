# Completing the trio's elemental wardrobe

Six functional forms add distinct battle/front/back art, menu icons, six follower
poses and reusable protected Key Items. Each original resident offers the gift
when the matching girl is in the party. There is no Badge, battle, payment or quest
flag requirement. Declines and full Bags can retry; possession prevents duplicates.
The resident's original atmosphere/story dialogue follows every outcome.

| Form | Types | Keepsake | Existing resident |
| --- | --- | --- | --- |
| Dragon Riko | Dragon/Fairy | Pom Dragon Plush | Blackthorn cooltrainer, 44,31 |
| Bumble Riko | Bug/Fairy | Riko Honeycomb | Azalea elder, 44,14 |
| Midnight Bijuu | Normal/Dark | Cocoa Sneaky Cape | Ecruteak man, 22,42 |
| Crystal Bijuu | Normal/Rock | Shiny Pebble | Mahogany elder, 7,13 |
| Digging Penny | Fairy/Ground | Garden Trowel | Violet elder, 28,36 |
| Handy Penny | Fairy/Steel | Dad's Toolbox | Olivine sailor, 33,46 |

Riko's two keepsakes work on ordinary/Balloon/Princess/Raincoat Riko; Bijuu's work
on ordinary/Box/Bread/Detective Bijuu. Their matching items return them to ordinary
Riko/Bijuu. Penny's two forms branch from **Guardian Penny**, matching her existing
Water/Grass pathways, and return to Guardian Penny. Use Dad's Keys first to reach
Guardian Penny. Other permanent forms revert through their own existing items
before changing. The keepsakes are never consumed, sold, held or tossed.

Digging Penny is a blonde long-haired dachshund head with floppy ears poking out
of earth like Diglett, with a little muddy paw and no exposed torso or legs.
Handy Penny wears a hardhat, tool belt and silver guards. Dragon Riko has lavender
horns/wings/tail detail; Bumble Riko has bee stripes and little cream wings.
Midnight Bijuu has a purple hood and smoky tail; Crystal Bijuu wears crystals.
Both remain blue-eyed Siamese cats; Riko stays a black Pom with brown cheeks/brows.

The girls retain female gender, family dex/growth identity, signature eligibility,
Camp transformation stats and Spirit keepsake eligibility. Riko has her existing
560-point elemental spread; Bijuu's existing reserved Dark/Rock stats remain;
Penny shares Guardian's 100/100/120/85/55/95 spread. New own learnsets emphasize
dragon attacks/setup, bee pivots, stealth/priority, crystals, digging and sturdy
steel support. Status moves remain normal level-up moves. Scott offers eligible
damaging current-type attacks at the actual level and skips known moves. Equipped
attacks survive reversion. Level40 adds Outrage/Bug Buzz/Crunch/Stone Edge/
Earthquake/Heavy Slam respectively; each has an immediate transformation attack.

Existing species1589 Dragon Riko,1593 Rock Bijuu and1596 Dark Bijuu are reused.
New species1630 Bug Riko,1631 Ground Penny and1632 Steel Penny append after Pom Fu.
Items966-971 append. Real historical IDs and all family form indices stay fixed;
Egg sentinel follows the new tail. No saved arrays, flags/vars, initialization,
map objects, geometry, trainers, album photos or earned progress are changed.
The costume album remains for cosmetic outfits plus its existing Poison bonus.

Built-in imagegen produced six approved transparent atlases stored as source.png
under each species directory. Native tools/elements/render.c detects occupied
row clusters, crops separate cells and scales/quantizes to matched16-color art;
import_assets.py handles formats/native byte assembly. Followers compile as
contiguous4x4 tile frames; front/back are64x64, icons32x64 and items24x24. Normal
and shiny palettes intentionally use the approved colors. The Makefile includes
all compiled assets and deduplicates the follower target list.

Validation source/binary checks cover96 actual gift outcomes, original NPC dispatch,
text paging, unchanged maps/save source/historical IDs/form indices,60 packed native
frames and six item palettes. validate_rom.py compares72 actual production-ROM
payloads. test/trio_complete_elements.c covers all six evolution/reversion paths,
current-level lessons, exclusive item eligibility and stored identity/move retention;
Spirit Mega tests include each form and exact starting-form restoration.
A rendered emulator playthrough and actual emulator save/reload remain separate
from those checks. Keep PR2 draft and unmerged.

Final local validation: RELEASE production build32712496 linked bytes,
EWRAM255416;122 focused engine/battle/species/text checks pass with21 intentional
harness failures and zero unexpected failures. Includes25 new form checks plus
Spirit Mega exact-form parameters. All240 existing hat frames and Pom Fu gift/art
regressions pass. The downloadable ROM is padded to32MiB.
