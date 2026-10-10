# The abandoned seaside garden

A quiet, optional outing in Olivine after Chuck's Badge (`FLAG_BADGE05_GET`), away from Goldenrod's festival and Rift hub. Speak to the little girl feeding Mareanie on the wharf at (33,58); her original conversation runs before the garden offer. Declining changes nothing. Original city objects, warps and progression are unchanged.

There are no battles, purchases, timers or required trial victories. Bring the three sisters for restoration; all recognized permanent forms count. The girls plant Riko's found seeds, warm the seedlings with Bijuu, and shelter them with Penny. Each step requires leaving the garden and returning for another visit. Saving/reloading inside does not advance growth. A cushion heals the party, the caretaker offers a return to the wharf, and the two southern arrows return through Olivine's existing Lighthouse entrance.

| Saved state | Garden |
| --- | --- |
| 0 | Abandoned; Riko can plant seeds |
| 1 | Planted; waiting for departure |
| 2 | Next visit; Bijuu can warm the soil |
| 3 | Warmed; waiting for departure |
| 4 | Next visit; Penny can shelter the seedlings |
| 5 | Bloomed; charm pending |
| 6 | Bloomed; charm received |

`TrioGarden_OnReturn` advances 1→2 and 3→4 during Olivine's existing transition callback. It never resets or completes an unfinished task. Garden load reconstructs tiles and the visible Riko from saved state without granting items or altering the party. The flowering Riko NPC replaces the ordinary NPC only inside this garden.

## Riko's Bloom and Flower Riko

The caretaker awards the reusable Key Item **Riko's Bloom** after all three steps. Ordinary Riko evolves into **FlowerRiko**; using the same charm on FlowerRiko returns her to ordinary Riko. Other forms must return to ordinary Riko first. FlowerRiko is a permanent Normal/Fairy alternate with Riko's existing stats and abilities, flowers tucked into her fluffy charcoal-and-cream coat, complete battle/menu/follower art, and Aromatherapy as an evolution move. It has no Mega or temporary Spirit transformation table. Existing elemental, Echo, Wing and Spirit pathways retain their own items and behavior.

A full Bag leaves the reward pending. Return to the caretaker or Mom with room; no repeat restoration or party requirement. The receipt flag prevents duplicate gifts. Completion adds a returning scrapbook memory and a pressed-flower Camp wall display on the next visit. These use completion state, so full-Bag winners receive the atmosphere and memory too.

## Allocations and compatibility

- `ITEM_RIKOS_BLOOM=952`, `SPECIES_RIKO_FLOWER=1610`; existing real species/item IDs unchanged.
- `VAR_TRIO_GARDEN_STATE=0x412D`, `FLAG_TRIO_GARDEN_BLOOM_RECEIVED=0x108C`; audited free in aa7efd8.
- Garden appended to IndoorOlivine and layouts, preserving every existing map/layout ID.
- Temporary flags 1/2 select garden Riko visibility on each load. No saved structure, original map object, trainer flag or existing quest variable is repurposed.
- Existing saves start with an abandoned garden and qualify automatically once Chuck's Badge is earned. Saves after planting, warming, blooming or a full-Bag reward remain resumable.

## Validation

`python3 tools/garden/validate_garden.py` executes the actual assembly with engine stubs and decodes geometry/art. It covers entry/decline, three separate visits, reload behavior, missing party, pending rewards, exits, NPC access, temporary visibility, stable IDs, authoring parity, connected sprites and completion memories. `test/trio_garden.c` covers reversible evolution eligibility, complete species assets, female gender, evolution move, protected charm metadata and Camp statistics. Existing family validators and engine tests remain regression checks.

Source simulation, production compilation, automated mGBA engine tests, decoded asset inspection and a rendered interactive emulator playthrough are separate evidence. New garden travel, animations, evolution, and actual save/reload still need rendered confirmation.
