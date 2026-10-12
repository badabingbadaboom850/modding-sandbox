# Permanent Halloween costumes

Witch Riko, Vampire Bijuu and Pumpkin Penny are purely cosmetic and remain
obtainable all year. No date, Badge, battle or new quest requirement is added.
Bring the matching girl and accept an optional gift from the existing host:

| Costume | Protected reusable Key Item | Existing host |
| --- | --- | --- |
| Witch Riko | Riko Witch Hat | Ecruteak raincoat giver,47,43 |
| Vampire Bijuu | Vampire Cape | Ecruteak detective giver,25,33 |
| Pumpkin Penny | Pumpkin Suit | Olivine beach-vest giver,34,57 |

Halloween offers precede the existing extra/original costume conversations.
Owned items skip duplicate gifts; decline, absent party and full Bag return
normally. A full Bag can retry on another visit. There are no new map objects,
visibility changes, startup grants, test shortcuts or real-time checks.

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
Spirit Mega eligibility include the new costumes. No new save variables/flags.

Validation:48 Halloween and48 prior extra gift source paths pass, including
owned/absent/decline/full-Bag states; historical map/save/ID checks, native indexed
asset format checks, text wrapping, all39 reusable transformation-item checks
and docs-summary/diff checks pass. Native costume/storage/level26/Mega/album
engine tests are extended, but local ARM compilation is unavailable (missing
arm-none-eabi-gcc and libpng headers). CI compilation/tests and rendered emulator
confirmation must be reported separately. Keep PR2 draft and unmerged.

See [Focused emulator pass](trio_costume_emulator_pass.md).
