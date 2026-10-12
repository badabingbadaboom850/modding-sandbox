# Focused costume and reusable-item emulator pass

## Baseline and result recording

Use a copied normal in-game .sav, preserving the original. Record the ROM commit,
emulator/version, save provenance, girl/stage/level, held item, ability, six stats,
moves/PP and Bag item quantity. Start from an existing pre-update save; also run
one fresh-save smoke test through normal acquisition. Load the new ROM and its
in-game save directly, rather than restoring an old-ROM frozen snapshot.

Mark each row below Pending, Pass or Fail for each sequence step. Record observed
behavior and screenshots; do not infer an emulator pass from native/source tests.
All rows remain Pending until actually exercised. Existing user confirmations of
older costume presentation are useful history, not confirmation of this full pass.

| Girl | Costume | Reusable item | Stages |
| --- | --- | --- | --- |
| Riko | Balloon | Riko Balloon | ordinary Riko |
| Riko | Princess | Pom Tiara | ordinary Riko |
| Riko | Raincoat | Riko Raincoat | ordinary Riko |
| Riko | Butterfly | Riko Wings | ordinary Riko |
| Riko | Witch | Riko Witch Hat | ordinary Riko |
| Bijuu | Box | Bijuu Box | ordinary Bijuu |
| Bijuu | Bread | Cocoa Toast | ordinary Bijuu |
| Bijuu | Detective | Detective Kit | ordinary Bijuu |
| Bijuu | Astronaut | Space Helmet | ordinary Bijuu |
| Bijuu | Vampire | Vampire Cape | ordinary Bijuu |
| Penny | Hot Dog | Penny Hot Dog | Fidough and Dachsbun |
| Penny | Blankey | Penny Cozy Wrap | Fidough and Dachsbun |
| Penny | Lifeguard | Penny Beach Vest | Fidough and Dachsbun |
| Penny | Ballerina | Penny Tutu | Fidough and Dachsbun |
| Penny | Pumpkin | Pumpkin Suit | Fidough and Dachsbun |
| Bijuu | Poison (elemental control) | Toxic Mouse | ordinary/Box to Poison; reverse ordinary |

## Repeat for every costume and Penny stage

1. Record initial quantity. Cancel party selection and try an unrelated species
   and an Egg. No quantity decrease, transformation, freeze or party corruption.
2. Dress the ordinary girl. Confirm unchanged stats/type/ability/moves/level/sex/
   held item and item quantity. Inspect evolution UI, front/back battle picture,
   party icon, follower idle/walk down/up/left/right and palette/transparency.
   Use the same item to revert, then dress again. Repeat at least three cycles.
3. Save in-game while dressed, completely close/reopen the emulator/ROM, load
   the save, verify costume and quantity, then reuse that same item to revert.
   Save/restart once while ordinary and dress again after loading.
4. Dress, deposit in a PC Box, save/restart with her boxed, inspect stored icon/
   summary, withdraw and verify form/stats/moves/held item. Revert using the same
   item and confirm unchanged quantity. Box transfer must not strip a costume.
5. Dress and faint in an ordinary battle. Finish the battle, revive/heal, confirm
   costume persists and reuse to revert. Run one full-party blackout control
   per girl and verify recovery, Bag quantity and form after field return.
6. Where legitimately unlocked, test normal Riko/Bijuu Mega and Spirit Mega.
   Check victory/end cleanup and Mega fainting restore the exact starting
   costume; save/restart afterward and reuse the costume item.
7. Open the album while dressed, check portrait/reaction/Scott comment, revert,
   box and restart; the earned photo must persist. Teach one eligible Scott
   signature and verify its retention through dress/revert and restart.
8. For each Penny outfit independently: start at25, dress, reach26 normally,
   confirm dressed Dachsbun, then revert to ordinary Dachsbun. Compare with
   same-level evolved-stage baseline rather than expecting level25 stats.
   Re-dress, save/reload and confirm the evolved stage remains.

## Acquisition and existing-save controls

For ordinary costume gift sources: absent matching girl, decline, accept, repeat while owned
and visit with full Key Item storage (on a separate test-save copy if practical).
Full storage must leave the gift retryable; repeated successful visits must not
multiply protected costume items. Original conversations/services and routes
must remain available. Morgan's Box encounter separately needs decline/loss/
full-Bag victory recovery without a forced second win.

Use an existing save with all old photos to earn each Halloween portrait. Old
bits and optional quest progress must remain; the album should show15 costumes
when complete, excluding the separate Poison bonus. Save/reload with bit15 set
and check Pumpkin Penny's portrait in both stages. Calendar changes must not
remove Halloween access.

Poison Bijuu is elemental, so its stats/type differ legitimately. Toxic Mouse
stays in the ordinary Items pocket. Test forward/reverse quantity, moves learned
through transformation/Scott, save/Box/faint/reload and form persistence. On
reversion, equipped moves remain but species returns to ordinary Bijuu.

## Consumption/disappearance findings and failures

Current ItemUseCB_EvolutionStone removes one item only when it is neither in the
Key Items pocket nor in IsReusableTrioFormItem. All39 personal transformation
items pass the source classification audit:26 Key Items and13 ordinary Items.
All15 costume gifts have importance1 and Key Items pocket. Toxic Mouse is an
ordinary Items-pocket reusable exemption. No inventory pocket migration occurs.

Older builds consumed Wand/Blue Brush/Fish Toy/Cat Nip/Dad's Keys/Chicken.
Previously consumed copies are not restored by loading the new ROM. Missing
before the first new-ROM use is therefore distinct from disappearing on use.
Ordinary Items may also be held: check the girl's held item and PC storage before
calling a Bag absence consumption. Protected costume Key Items should not be
holdable, sellable or discardable; any successful destructive option is a failure.

Fail immediately on any family item quantity decrease during use/reversion,
item lost after save/reload/Box/fainting, costume stripped outside an intended
reversion, wrong Penny stage, changed ordinary costume stats/type/moves, unusable
item after restart, corrupt followers/Bag, crash or softlock. Report exact ROM
commit/save/action and before/after quantities. An ordinary evolution stone
consuming one is expected control behavior; a family item doing so is not.

## Halloween trail rendered checks

Visit Ecruteak's Itemfinder house (city door19,33), talk to Gastly9,5, decline
once, then accept. Verify the original Itemfinder still works. No party gate.
Explore all13 actors and inspect Gastly/Haunter/Duskull/Pumpkaboo followers.
Try wrong/cancelled memory answers, then BOO/POM/TREAT for Riko's hat.
Find Fish/Moon/Star treat balls for Bijuu; visit Left/Right/Middle Pumpkaboo
for Penny. Use host hints, try wrong order/duplicate searches, save/restart
after one correct find, exit/reenter and resume without resets. Speak to
Haunter/Duskull for prizes. Test full-Bag solved rewards, then retry claims
without repeating the game. Repeat host interactions while owning items.
Both south-arrow exits and the exit Gastly return safely. Save inside/reload
and leave. Old costume copies/photos stay; earlier direct Halloween gift calls
are removed. Then run every costume item/storage/faint/reversion check above.

For the authorized fresh-save shortcut, inspect the player's New Bark mailbox
at17,11 and accept Halloween test travel. Decline once to confirm the original
house sign, then accept and play normally. Save/restart inside, use Exit Gastly
and each walk-out exit on separate visits, and confirm return to New Bark18,12.
No automatic costume gifts, Badges, party additions or story resets should occur.
Then enter through Ecruteak's Gastly and confirm the origin changes back to
Ecruteak for every exit. All earned games/items/photos must remain.
