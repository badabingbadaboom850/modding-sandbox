# Bag icon buffer overflow repair

The user reported a freeze while looking through the Bag to use Riko's Wand.
The Wand's icon itself passes native decompression and repeated creation tests,
and its evolution eligibility path passes. Exact cursor/action at the freeze
is unknown. A concrete nearby Bag hazard was reproduced: Bijuu's Fish Toy and
Cat Nip have32x32 icons that decompress to512 bytes, but all three shared icon
loaders allocated only288 bytes for24x24 images. Loading either icon writes224
bytes past the allocation into heap metadata/data, so a later highlighted item
or menu operation can freeze. This can explain the report; user playtesting
must confirm the observed freeze has gone away.

src/item_icon.c now reserves512 bytes and checks supported source dimensions
before decompression. Standard288-byte icons retain the original three-row
padding into their32x32 destination. Full512-byte icons copy directly, preserving
their native four-row art. Standard sprites, custom-template sprites and window
blits share this bounded conversion. Unsupported dimensions fail through each
caller's existing failure result and free temporary buffers. Existing sprite
and palette art, Bag item IDs, pockets, quantities, descriptions, reusable item
logic, evolution rules, party contents and all saved data remain unchanged.
Temporary decompression allocation increases224 bytes; EWRAM globals/save sizes
stay unchanged. No new images or inventory migration.

Regression: the old code failed EXPECT_GE(288,512) in the real GBA allocation
check. The corrected build passes8 new checks: Wand source/canary decompression,
repeated Wand creation, actual capacity for both Bijuu images, repeated intact
512-byte VRAM/heap loads, all registered icon dimensions, Wand evolution
selection, custom-template sprite output and window tiles/palette output.
37 focused native checks pass plus7 intentional harness failures, zero
unexpected failures. Production RELEASE32736364 linked bytes/EWRAM255432/
padded32MiB passes. Existing33 reusable item history and compiled silly-scene/
parade registries pass. The corrected ROM needs normal player Bag testing.

Replace the ROM and load a normal in-game save from before the freeze. A frozen
emulator snapshot retains the old program/heap state, so avoid resuming it.
If the same freeze remains, obtain exact cursor/item/action and the normal save
needed to reproduce it; do not attribute another cause without evidence.
Keep PR2 draft/unmerged and all prior family features,5% run-off and normal mailbox.
