# Riko Puffs

Riko Puffs are inexpensive consumable kibble that raise any eligible Pokemon by five levels per use. They cost ₽500 at Blackthorn's Mart's left-hand TM/ball clerk, once all eight Johto Badge flags are earned. Existing saves qualify automatically; no new quest, flag, variable, free item or startup grant is needed. The original stock and the other clerk remain available.

Puffs reuse the normal candy party flow, including bulk selection, stat changes, every intervening level's move/innate learning and normal evolution checks. Effects work across growth rates and cap at level100 or the current enabled candy level cap. Eggs, empty slots and zero quantities are rejected. At level100 they have no effect and are not consumed to force an evolution. Ordinary Cat Food Tins/Rare Candy, EXP Candies and Reverse Candy keep their own behavior.

All BW, HGSS and SwSh party styles calculate the number needed with ceiling division by five. For example, level1→100 needs20 Puffs, level95→100 needs1, and level96→100 also needs1. Additional Bag stock is preserved. Each successful Puffs use consumes one item; it is not a reusable form charm.

The 24×24 inventory icon is a small pile of toasted brown kibble, indexed to16 colors with palette0 transparent. It was generated with the built-in image tool using a prompt for five warm-brown kibble nuggets, dark outlines and gold highlights on transparency, then converted by tools/puffs/import_icon.py. Final assets: graphics/items/icons/riko_puffs.png and graphics/items/icon_palettes/riko_puffs.pal.

`ITEM_RIKO_PUFFS=953` is appended without changing existing real item IDs or saved structure layouts. Source checks in tools/puffs/validate_puffs.py exercise all256 Badge combinations, original stock/map preservation, authoring hooks, all-party-style safety and icon/text metadata. Six engine tests in test/riko_puffs.c cover growth rates, preview/invalid targets, bulk use, normal candy regression, evolution eligibility, all three party quantity limits, enabled caps, price/Bag/text and saved ABI.

Compilation, automated engine checks, source simulation and rendered interactive confirmation are separate evidence. New shop purchase/quantity UI and actual move/evolution animations still need a hands-on emulator check.
