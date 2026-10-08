# Trio world-building action items

## Goal

Give Riko, Penny, Bijuu, and their trainer a journey residents remember. New rumors should follow witnessed scenes or completed adventures. Mix affection, ordinary life, doubts, jokes, and earned respect. Preserve the original game's directions, services, battles, and progression.

## First implementation batch

- [x] Add badge- and Champion-aware callbacks for Caleb, Chelsea, Aunt Susan, and Mom.
- [x] Give Greg distinct Route 29, Route 30, and Cherrygrove battle jokes, plus later post-victory banter.
- [x] Keep Caleb's "Nothing beats this view" and Chelsea's "This is the beach I hate" as their opening lines.
- [x] Extend the existing Cherrygrove/Violet research quest into a readable three-page scrapbook.
- [x] Add an optional Azalea visit: the trio quietly befriends a youngster's shy Hoothoot.
- [x] Add an optional Goldenrod visit: the trio helps a woman recover a purse containing a family photo.
- [x] Add persistent aftermath conversations at both chapter NPCs and neighboring residents and family reactions to completed reports.
- [x] Reward the Azalea report with one medium Wawa and Goldenrod with Bijuu's Pom Poms.
- [x] Include Psychic Bijuu in the shared form-aware party check.
- [ ] Pass ROM compilation and CI tests for this batch.
- [ ] Verify all new paths in the emulator.

The new visits are interactive text vignettes on existing NPCs. They do not add visible Pokemon objects, new movement paths, maps, or warps. A later visual-polish pass can animate them once their progression is confirmed.

## Next batches

### 1. Olivine lighthouse chapter

- [ ] Trace the active lighthouse sick-Pokemon and Jasmine progression before adding the scene.
- [ ] Let Penny choose to sit with a nervous Pokemon; Riko gives space and Bijuu follows Penny's lead.
- [ ] Show the interaction on screen using confirmed graphics and unobstructed movement paths.
- [ ] Add Jasmine's response and later Olivine gossip after the scene completes.
- [ ] Extend Penny's arc beyond her existing two-badge Mom moments. Confidence means choosing connection, not becoming fearless.

### 2. Ecruteak mystery chapter

- [x] Add rumors of a celestial visitor, floating pebbles, glowing eyes, and an unexpected interest in treat bags.
- [x] Follow two existing town witnesses to a fish-shaped toy behind Burned Tower's notice board.
- [x] Find Bijuu's Fish Toy and use the existing Bag evolution system.
- [x] Require actual Psychic Bijuu for the reveal: she was the visitor all along.
- [x] Give the believer and skeptic different aftermath conversations.
- [x] Add a completed-chapter family callback and an extra scrapbook page.
- [x] Provide a one-time catnip gift, full-Bag retries, and a local shop for replacement form items.
- [ ] Verify the evolution scene, battle/follower graphics, reverse evolution, and quest in the emulator.
- [ ] Add on-screen scene animation after the text-and-item quest is confirmed.

### 3. Riko learns to share the spotlight

- [ ] Add a small scene in which Riko is eager to lead.
- [ ] Give Penny or Bijuu the decisive contribution.
- [ ] End with Riko celebrating her sister, keeping her confident personality.
- [ ] Add a callback from someone who initially thought Riko did everything.

### 4. National Park picnic

- [ ] Pick a walkable spot and verify existing events and object limits.
- [ ] Add an optional quiet picnic with Riko choosing a seat, Bijuu investigating the basket, and Penny settling between her sisters.
- [ ] Make returning visits comforting without repeated item rewards.
- [ ] Add a family callback to the picnic after completion.

### 5. Regional identity and recurring friends

- [ ] Violet: students study the trio and revise their assumptions.
- [ ] Azalea: neighbors remember their kindness and woodland visits.
- [ ] Goldenrod: commerce, radio attention, admirers, and people tired of the hype.
- [ ] Ecruteak: conflicting interpretations of the trio's mythology.
- [ ] Olivine: practical help matters more than legendary status.
- [ ] Choose two recurring friends and give each an opinion that changes after actual events.
- [ ] Keep residents with unrelated concerns; avoid making every interaction a trio monologue.
- [ ] Extend family dialogue after each new chapter, retaining inside jokes.

### 6. League homecoming

- [ ] Add an optional homecoming scene after the actual Johto Champion flag.
- [ ] Let Mom and Elm refer only to optional chapters completed on that save.
- [ ] Give each baby one personal acknowledgment.
- [ ] Finish with a family moment and a quiet invitation to keep traveling.
- [ ] Keep the postgame and ordinary healing accessible.

### 7. Spirit trials and polish

- [ ] Fix and emulator-verify the Spirit cave load before making it a required story beat.
- [ ] Explain what the trials mean for the girls' bond.
- [ ] Verify battle restrictions, defeat cleanup, rewards, and save/reload.
- [ ] Add custom art to chapter scenes only after the scripts work.

## Current scrapbook state and compatibility

Uses the existing persistent VAR_TRIO_RESEARCH_STATE. No new save slots or flags.

| State | Meaning | Next interaction |
| --- | --- | --- |
| 0 | Original quest not accepted | Cherrygrove boy offers Violet research |
| 1 | Violet research accepted | Violet boy after Falkner |
| 2 | Violet report ready, reward pending | Cherrygrove boy, small Wawa |
| 3 | Original Violet reward claimed | Optional Azalea chapter offer |
| 4 | Azalea chapter accepted | Azalea youngster after Bugsy |
| 5 | Azalea vignette complete, reward pending | Cherrygrove boy, medium Wawa |
| 6 | Azalea reward claimed | Optional Goldenrod chapter offer |
| 7 | Goldenrod chapter accepted | Goldenrod woman after Whitney |
| 8 | Goldenrod vignette complete, reward pending | Cherrygrove boy, Bijuu's Pom Poms |
| 9 | Goldenrod reward claimed | Read the completed scrapbook |

Existing saves at state 3 can accept the new chapters. Other original states retain their meaning. Declining an offer or a scene leaves its state unchanged. New chapter acceptance and scenes require all three girls, with Riko/Bijuu permanent forms recognized. Reports and pending rewards can be claimed even if the party changes afterward. The scrapbook shows a new page only after its scene has actually occurred.

The Goldenrod woman follows her existing civilian visibility flag during the Rocket takeover. The quest can resume after civilians return; do not force her visible. Scene dialogue and both maps' original directions remain. All chapter rewards mark completion only after giveitem succeeds, so a full Bag allows retry without duplicates.

Champion family dialogue uses FLAG_IS_CHAMPION, verified against PokemonLeague_HallOfFame_EventScript_SetFirstGameClearFlags. The original generic FLAG_SYS_GAME_CLEAR is not substituted.

Greg keeps his existing trainer encounters and global one-time small-Wawa reward. This batch does not change his level-99 teams, automatic sight battles, whiteout behavior, or introduce repeat battles after his trainer flags are set.

## In-game verification checklist

1. Start a fresh save. Read Caleb/Chelsea's original lines and Susan's early joke. Confirm Mom still heals normally.
2. Complete the original Violet research quest. Verify its original small Wawa once.
3. On a save already at state 3, talk to the Cherrygrove boy. Decline the next offer, return, then accept.
4. Visit the Azalea youngster before Bugsy's Badge, without one girl, and with evolved Riko/Psychic Bijuu. Verify only the eligible party can start the scene.
5. Decline the Azalea scene and return. Accept; read all pages and confirm the youngster remembers it on repeated visits.
6. Return to Cherrygrove with a full Bag. Verify the medium-Wawa reward stays pending, then succeeds once after making room. Read the new notebook page.
7. Accept Goldenrod. Test before Whitney, an incomplete party, a declined scene, a completed scene, and repeated visits.
8. Test Goldenrod's pending reward with a full Bag; collect Pom Poms once. Verify the notebook now has three pages.
9. Visit the family after badge 1, badge 3, badge 8, both turned-in chapters, and becoming Champion. Check that uncompleted chapter events are never claimed.
10. Check Greg's three encounter locations and post-victory callbacks. Confirm his shared Wawa cannot be farmed across locations.
11. Save/reload at accepted, report-ready, and finished states. Check that the active quest and NPC recollection persist.
12. Verify Goldenrod's Rocket takeover and restored civilian phases without changing the original visibility rules.

## Validation record

55 source-path simulation checks passed, covering offers, declined scenes, Badge gates, absent-party cases, permanent forms, reward retries, notebook pages, family branches, Mom healing, and Greg's shared reward. This simulation does not execute the game engine or verify rendering. Source validation covers new label uniqueness/references, ASCII text with conservative two-line pages, synchronization of edited raw Pory sections, active map-object hooks, and progression/reward paths. CI compilation and tests and user emulator confirmation are separate checks; update this section with the exact committed SHA and results.

## Ecruteak mystery playtest path

This is independent of the three-page research quest and available on existing saves. It uses VAR_ECRUTEAK_BIJUU_MYSTERY = 0x4124 in the existing save-variable array.

| State | Meaning | Next step |
| --- | --- | --- |
| 0 | Not accepted | Woman beside Eevee, south of Dance Theater (35,43) |
| 1 | Accepted | Woman south of Burned Tower (19,22) |
| 2 | First clue found | Boy near the southeastern edge (52,49) |
| 3 | Both clues found | Inspect Burned Tower sign (23,14) with Bijuu |
| 4 | Fish Toy received | Use it on base Bijuu in Bag > Items, then return with Psychic Bijuu |
| 5 | Psychic Bijuu revealed, catnip pending | Return to host with Bag room; party can change |
| 6 | Complete | Witness aftermath, Mom callback, and optional scrapbook page |

The chapter uses existing visible NPCs and the existing sign interaction; no map movement, new warp, or new Pokemon object is needed. The original Burned Tower warning is preserved. Rumors describe brief glimpses of latent power; the Fish Toy focuses that power through the existing permanent evolution. There is no separate celestial creature to catch.

The host sells Fish Toys and Cat Nip for 500 each once the first toy has been found. Existing Goldenrod 4F stock remains. That also supports older saves that have already evolved Bijuu or used a form item.

Required checks: declined offer; no Bijuu at acceptance/discovery; witnesses out of order; repeated clues; full Bag at toy pickup; base/other forms do not trigger reveal; Psychic form triggers it; full Bag at catnip reward; changed/absent party while reward is pending; repeated sign and reward visits do not duplicate gifts; replacement item purchase; save/reload in every state. Confirm the notebook page appears only after completion. Test Burned Tower witness dialogue before/after releasing the beasts.

Fresh-save inventory now omits Riko's Purse, Penny's Blankey, and all initial Bag Pokeballs. Mega Ring and Bondstone remain when Mega Evolution is enabled. This does not remove already-owned items from existing saves or change normal story gifts and shop purchases.

Source validation for the Ecruteak batch: 35 source-path simulation checks pass for offers, clues, out-of-order visits, Bag-full retries, exact-form recognition, existing Psychic Bijuu saves, one-time gifts, replacement shop access, and witness aftermath. Edited raw Pory blocks match assembly; new labels and references resolve; original labels and story commands remain; new text uses ASCII and at most two lines per page. Starting Bag grants are exactly Mega Ring and Bondstone. ROM CI and emulator tests remain pending.
