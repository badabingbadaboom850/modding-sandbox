# Keepsakes, sister moments, and Mom's scrapbook

The girls now leave memories as well as victories. This page describes the new features and the emulator checks still needed.

## Spirit keepsakes

| Girl | Keepsake | Award condition |
| --- | --- | --- |
| Riko | Riko's Spark | Win or catch the final Spirit of Riko encounter |
| Penny | Penny's Shield | Win her milestone story encounter (prior home-test wins remain honored) |
| Bijuu | Bijuu's Light | Win her home trial or milestone story encounter |

Each keepsake is a protected Key Item. Use it from the Bag, or register it, to read her letter. It is never consumed and has no held-item battle effect. Item icons reuse existing registered orb, shield, and charm graphics.

The gift is once per girl. A victory is recorded separately from successful delivery: a full Key Items pocket keeps the gift pending. Mom checks pending gifts before her usual dialogue and healing; Penny and Bijuu also retry delivery when you revisit their Spirit encounter. Existing saves with an earlier story victory can collect their missing keepsake.

The two New Bark test Spirits and their 1-HP shortcut have been retired. Penny and Bijuu remain at their milestone story locations, with normal HP and the 5-10 level advantage.

Penny/Bijuu home wins have independent test markers. They allow keepsake and scrapbook-letter testing without completing either milestone story quest or bypassing the story arena gates. A later story victory does not duplicate a keepsake already received at home. Riko's cave loading issue remains unresolved; this batch adds a reward hook to its existing final victory without changing the cave, battle setup, or cleanup.

## Mom's scrapbook

After the first Johto Badge, visit Mom for normal dialogue and healing. Prior home-test victories remain valid for immediate book delivery on existing saves; new playthroughs obtain it after the first Badge. She gives **Mom's Scrapbook**, with a safe Bag-full retry on later visits. Use this protected Key Item from the Bag or registered shortcut to choose:

- **Our journey:** paw-written memories of starting together, the first Badge, Goldenrod's Badge, all eight Johto Badges, and becoming Champion. Pages follow actual milestone flags, not a new progress counter.
- **Sister moments:** pages from optional witnessed scenes and the pom party.
- **Spirit letters:** letters unlocked by the corresponding Spirit victories, including Penny/Bijuu home testing wins.

The existing Cherrygrove research boy keeps his original scrapbook, quests, rewards, and pages. When you accept his existing reading offer, he also offers these companion pages. Reading is optional and repeatable. Pages remain available even if the girls are in the PC.

## Sister moments

A new Lass at (5,5) in each listed Pokemon Center offers a short scene. Bring all three girls; their recognized regular, evolved, Mega, and elemental forms use the existing shared checks. The first viewing records a scrapbook page. Replays are optional and do not duplicate entries.

| Center | Available after | Moment |
| --- | --- | --- |
| Azalea | Violet's Badge | Bijuu investigates a leaf, Penny stands beside her, and Riko declares the situation handled. |
| Goldenrod | Azalea's Badge | A crowded city's quiet bench has room for every sister. |
| Olivine | Ecruteak's Badge | Penny shelters Bijuu from the sea wind while Riko supervises the ocean. |

Existing nurses, residents, services, quests, and warps are retained. Each exact new position and its approaches were checked against collision and metatile behavior.

## Pom party

Visit **Goldenrod House 2**, the existing PP-explanation house entered from Goldenrod at (48,15). Four Riko/Pomeranian sprites chase clockwise around a two-tile square on the left side of the room. The first visit greets you with:

> Ain't no party like a pom party!

The existing man repeats the party line after his original PP explanation. The woman retains her healing advice. You can talk to the Poms and revisit the party. Seeing the welcome records Riko's party-report scrapbook page.

The circle uses the engine's autonomous, collision-aware walk sequences with four starting phases. Only Riko objects in this house use the faster sequence step; other NPCs retain their original movement. A player blocking the circle makes the Poms wait rather than pass through them. The doorway, furniture and original residents remain clear; the house has six object templates.

## Save and validation notes

New items append at 945-948 without changing earlier IDs. Persistent flags 0x105E-0x1067 record delivered gifts, scrapbook receipt, three sister pages, the party welcome, and two home testing wins. No saved variable or SaveBlock layout was added. Home and story completion remain separate.

Required emulator checks:

- Win each eligible Spirit fight; receive exactly one keepsake and use/register it to read the letter.
- Repeat wins and revisit Mom: no duplicate gift. Try a full Key Items pocket, then make space and retry without another required story battle.
- Collect on an existing save with an earlier Spirit victory. Verify Riko's pending reward at Mom if her final victory flag is already set.
- Obtain/read/register the scrapbook, navigate all three menu sections, press B/Exit, and confirm free movement afterward.
- Confirm pages unlock only at their milestones or after witnessed scenes, and remain readable with girls deposited.
- Decline each sister offer, bring missing girls, view/replay with eligible forms, and check one page per scene.
- Enter/reenter the party house; watch complete clockwise loops, block/release the route, talk to each Pom and both residents, then leave through the original door.

Source checks and compilation do not replace these emulator checks.

## Test encounter cleanup

The user confirmed the implemented features are working. New Bark's two temporary test objects were restored to their original decorative Pidgey slots, preserving every later object index and original event. The test interaction scripts and 1-HP helper/registration are removed; shared Spirit letters remain included. Existing test-win flags, keepsakes, book receipt, and pages are retained for save compatibility. No new save is required. A full-health preparation regression replaces the retired shortcut regression. Cleanup CI and an updated-ROM check remain pending.
