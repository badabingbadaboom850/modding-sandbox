# Seasonal expansion proposal

Status: design draft, not implemented. User requested fall, Thanksgiving,
Christmas and New Year content to extend the adventure. Preserve permanent
access, optional participation, cosmetic-only outfits, female family identity,
reusable protected items and existing saves. Halloween remains after Chuck5.

## Four seasonal chapters and twelve proposed costumes

| Chapter | Riko | Bijuu | Penny | Main activity |
| --- | --- | --- | --- | --- |
| Fall: Leaf-Pile Picnic | Leaf-pile pom, face/paws/tail peeking through leaves | Cozy scarf and knit sweater | Oversized cable-knit sweater, blonde ears visible | Leaf search and picnic preparation |
| Thanksgiving: Thankful Table | Turkey-feather costume with her own face | Little chef hat and apron | Sweet-potato outfit with a tiny butter patch | Help each girl prepare a family feast |
| Christmas: Three Little Helpers | Santa hat and red coat | Gift-box costume with ribbon | Reindeer antlers and warm scarf | Sort gifts and deliver them to the right sister |
| New Year: Midnight Pawty | Gold party hat and confetti collar | Silver bow tie and sparkly collar | Party dress with tiny star clips | Restore lanterns and complete a celebratory rhythm/memory round |

All costumes need separate battle front/back, party icon, six follower frames
and matching item icon. Penny needs both ordinary/evolved metadata and dressed
level26 evolution. Original stats/types/abilities/moves/growth/female identity
stay; Mega cleanup returns the exact starting outfit. No real food or actual
feeding is implied by Thanksgiving costume props.

## Longevity design decision to settle before implementation

A one-time chapter model would spread discoveries across later Johto/Kanto
milestones, with permanent costume rewards and new scrapbook/album memories.
A replay model would additionally provide optional varied rounds after reward
completion, with modest existing Wawa/Puffs prizes under safe full-Bag handling.
Both models can coexist: one-time costume unlocks plus repeatable minigames.
No real-date lock or system-clock dependency is needed. Decide the desired
revisit behavior before implementing progress/reward state or scripting art.

Pacing proposal: Fall near the seventh-Badge approach, Thanksgiving after eight
Johto Badges, Christmas during Kanto, New Year as a League/Kanto celebration.
Exact hosts, routes and triggers must be traced and audited before placement.
These are proposed milestones, not currently wired events or promises about
what an existing save has completed. Halloween's current event stays unchanged.

## Implementation constraints verified against current code

The existing16bit outfit photo mask is full: fifteen costumes plus Poison bonus.
Append a separate audited saved-variable mask for seasonal photos, preserving
every old bit and existing save-array layout. Never shift past bit15 or silently
reset prior portraits. New progress variables/flags need a raw/numeric-use audit.
Do not allocate speculative numeric species/item/map IDs from old handoffs.

Use the existing costume/toggle and normal/Spirit Mega integration, the fixed
Penny crop isolation, frame-contiguous follower packing and palette contracts.
Measure new item names/descriptions using actual font tables, not character
counts alone. All51 eventual family transformation items must retain reusable
routing; full-Bag rewards must remain pending rather than require another win.

Test normal and old saves, cancellation/loss/exit/replay, independently earned
outfits, boxing/fainting/reversion/restart, dressed Penny evolution, exact-form
Mega returns, photo bit preservation, native asset/frame registration, safe
host/warp geometry and production-generated map constants. Keep PR2 draft and
unmerged. Rendered event checks remain separate from source/native/CI checks.
