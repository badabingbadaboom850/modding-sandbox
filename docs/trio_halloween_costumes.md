# Permanent Halloween costumes

Witch Riko, Vampire Bijuu and Pumpkin Penny are purely cosmetic and remain
obtainable all year. No date, Badge, battle or new quest requirement is added.
A friendly Gastly in Ecruteak's Itemfinder house (city door19,33; Gastly9,5)
invites an optional trip to the Trick-or-Treat Trail. Halloween items now come
from its three games, replacing the direct gifts from costume vendors. Earlier
collected items/forms/photos stay intact; existing original/extra costume gifts
and the Itemfinder service remain. No party, date, Badge or battle gate.

| Costume | Reusable protected Key Item | Game |
| --- | --- | --- |
| Witch Riko | Riko Witch Hat | Gastly's BOO/POM/TREAT memory game |
| Vampire Bijuu | Vampire Cape | Haunter's Fish/Moon/Star treat hunt |
| Pumpkin Penny | Pumpkin Suit | Duskull's Left/Right/Middle Pumpkaboo trail |

Wrong guesses allow retries without losing completed searches. Partial hunt
progress and solved-but-unclaimed rewards save normally. Full Bags can reclaim
without replaying; owned items prevent duplicates. Exit Gastly and two native
south-arrow exits return to the original house. The trail remains year-round.

Use each item on the ordinary girl to dress up; use it again to revert. Return
from other personal forms with their existing item first. Stats, types,
abilities, growth, learnsets, tutor/TM access and female identity match the
ordinary stage. Pumpkin Penny has both Fidough and Dachsbun metadata, retaining
her costume through level26 and her evolved stage after reversion. Normal
progression and learned moves remain. Costumes persist through ordinary battle
end/fainting; Mega cleanup restores the exact starting costume.

Battle front/back, menu, six follower frames and24px item icons have native
16-color palettes. Built-in imagegen generated the transparent reference
atlases under graphics/pokemon/{riko_witch,bijuu_vampire,penny_pumpkin}/source.png.
The Vampire atlas received a targeted up-facing follower correction.
import_halloween.py handles formats/packing; existing new_render.c owns pixel
cropping, nearest-neighbor conversion and palette selection. Prompts requested
black/brown/cream Riko with purple witch hat/cape; cream/dark-pointed blue-eyed
Bijuu with red-lined vampire cape; fully blonde long-bodied Penny in orange
pumpkin suit with green leaf collar, all with front/back/icon/six directions/item.

Species1637-1640/items975-977 append; historical real IDs/form indices/save
arrays stay fixed. Album bits13-15 fill the final three positions of the
existing16bit mask, preserving bits0-12 and the Poison bonus at9. Album counts
15 costumes plus that bonus. Penny stages share a portrait. Future portraits
need a separately audited storage design; never shift beyond bit15 here.
Scott comments, outfit reactions, family checks, Camp, signatures and normal/
Spirit Mega eligibility include the new costumes. Three audited unused variables4147-4149 record the games; no save arrays or flags change.

Validation:3454 actual authored puzzle/offer/retry/reward source paths pass,
plus13 actors/two exits and original service/map/save-ID preservation.48 prior
extra gift paths, costume metadata/native palettes/art registration, all39
reusable items and docs-summary/diff checks pass. Native costume/storage/level26/Mega/album
engine tests are extended, but local ARM compilation is unavailable (missing
arm-none-eabi-gcc and libpng headers). CI compilation/tests and rendered emulator
confirmation must be reported separately. Keep PR2 draft and unmerged.

See [Focused emulator pass](trio_costume_emulator_pass.md).

See [Trick-or-Treat Trail](trio_halloween_trail.md) for locations and game details.
