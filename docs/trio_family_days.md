# Dinner, radio and family homecoming

Three optional midgame chapters add family outings without battles, costs, deadlines, forced party changes or original-story prerequisites beyond their stated gates. Existing saves can begin them immediately when eligible. All three girls are assumed present in family scenes.

## Scott's dinner date

After Morty's Badge, Scott waits south of Goldenrod's Radio Tower at **15,25**. Accept his free dinner reservation to enter a separate restaurant using Olivine Cafe's proven layout. The normal cafe and Goldenrod buildings retain their services. Scott observes the city's civilian Rocket-takeover visibility; the date waits until the city is safe.

Talk to Riko and choose **Plain chicken**, call Bijuu back from the kitchen with Scott's toy, then sit with Penny. Wrong answers and cancellation preserve progress. Scott offers the takeout finale once everyone is settled. Dinner becomes paper boxes, stolen cushions and a kiss—the kind of date this family actually has. Completion records a Sister moments scrapbook page and heals. Scott's three small Wawa are once per save, separately tracked after successful receipt; full Bag or decline preserves the pending reward, without another finale. Optional replay never resets progress.

The native south exit returns to Goldenrod's Radio Tower doorway, even after in-game save/reload. Visit Scott outside to resume or replay.

## Tails of the Trio radio

After the normal radio quiz and Whitney's Badge, speak to the existing woman at **23,8** in Radio Tower 1F. Her original conversation stays. Accept the optional studio visit; the civilian/tower takeover conditions remain intact. The small separate studio reuses the safe Mirror House layout. Its native south exit returns to the tower lobby.

Check Riko's microphone, Bijuu's cue card, then Penny's comfortable recording spot. Each step is optional, saved and gentle. Ask the producer to record when ready. A permanent scrapbook page and a native Pokégear station unlock after recording; no radio/Badge/story flags are granted.

**Tails of the Trio** occupies dial position52, near the right end. Retuning randomly selects Riko's opinions, Bijuu's advice, Penny's comforting goodnight, or Scott's dedication. Content reads existing earned dinner, island, garden, bread mystery, Rift, homecoming and Champion states, with explicit priority. Listening writes no progress, rewards or statistics. The producer's menu offers the exact same segments for convenient listening. The original Oak, music, Buena/password, Unown and Rocket services stay; active Rocket takeover replaces this station too. No real-time gate limits the family station.

## Family homecoming

Pryce's original first Badge-award script delivers Mom's brief invitation without changing its TM/rewards/story flow. After that Badge, Mom offers the evening through her normal New Bark interaction. Old eligible saves need no earlier invitation flag. Declining returns to her original gifts, dialogue and healing. Acceptance opens a separate instance of the original home room, with Mom, Scott and all three girls, leaving normal house objects and introductory triggers unchanged.

Inspect **Riko's left parcel**, **Bijuu's parcel near the stairs**, then **Penny's lower blanket**. These are permanent virtual story gifts, not new Bag items or transformations. Each step saves independently. Mom starts the evening once all three are found, heals, records the permanent Sister moments chapter, and offers three Chicky Fil-A snacks. Successful receipt alone records that reward; full Bag/decline keeps it pending. Optional replay never gives another reward.

Festival, restored garden and completed island keepsakes reconstruct visually on each return. Dialogue also remembers dinner and radio completion. Photo props close native mon pictures before returning controls. Scott adds existing outfit commentary. The homecoming room remains available through Mom for returns and healing; its native exit returns outside the normal New Bark home. No clock or party check is required.

## Save compatibility and validation

Six audited unused addresses in the existing persistent variable array:

| Variable | Address | Meaning |
| --- | --- | --- |
| VAR_TRIO_DINNER_STATE | 0x413E | 0 waiting,1 reserved,2 Riko,3 Bijuu,4 Penny/ready,5 completed |
| VAR_TRIO_RADIO_STATE | 0x413F | 0 microphone,1 cue,2 cushion,3 ready,4 recorded |
| VAR_TRIO_HOMECOMING_STATE | 0x4140 | 0 waiting,1 completed |
| VAR_TRIO_DINNER_REWARD | 0x4141 | 1 Wawa received |
| VAR_TRIO_HOME_GIFTS | 0x4142 | 0-3 sequential virtual gifts |
| VAR_TRIO_HOME_REWARD | 0x4143 | 1 Chicky Fil-A received |

Three maps append to existing IndoorGoldenrod/NewBark groups. No new layouts, species, moves, items, trainer IDs, permanent flags, save arrays or startup grants. All historical IDs and earned progress remain. Homecoming's TEMP1-3 hide flags are recomputed from actual earned achievements on transition; they do not grant completion. The authorized New Bark island-test mailbox remains unchanged.

`tools/family_days/validate.py` executes actual scripts for gates, clues, wrong choices, cancellation, replay, full-Bag retries, completion, all listening selections, inherited lock ownership, photo cleanup and decor combinations, and decodes actual map reachability/object limits. `test/trio_family_days.c` checks actual native-radio helpers, saved ABI, progress preservation, buffered broadcasts and every segment's line/buffer bounds across128 historical achievement combinations. Source/native builds are separate from interactive emulator confirmation.

Rendered testing still needed: each native entrance/exit; leaving/reloading mid-clue; radio dial and scrolling; recording without the original trio party; declined/full-Bag claims; Mom's normal healing after declining; home decor and scrapbook after actual in-game save/reload. The previous New Bark island shortcut remains available only for the user's separate authorized Road Trip test.
