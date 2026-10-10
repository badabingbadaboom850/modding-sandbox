# Spirit of Riko cavern pilot

A dedicated cave replaces reliance on the unresolved Shoal Cave loading path for
new Riko boss development. The old cave and its Suicune-backed flags remain
unchanged; this pilot does not establish a fix for it.

## How to test

Inspect the mailbox beside Mom's house in New Bark (17,11). After its original
house sign, accept the explicitly labeled TEST entrance. New and existing saves
can enter without Badges, trial completion, or Bijuu recruitment. No startup
warp, free levels, party mutation or Badge grant is introduced.

The cave is a fresh 32x30 layout using Johto General / Cave Default tiles (the
Union Cave pair), no snow, weather, time-of-day, Flash, connections, wild encounter
entry, or old cave callbacks. It has an oval chamber, three inset aspect stations,
a reunion point, a narrow southern passage, Bijuu and Penny, an exit guide, and a
healing cushion. Family staging assumes the girls' presence as authorized.

1. Violet Mind in the west: Psychic/Fairy, special attacks and tricks.
2. Amber Body in the east: Normal/Fairy, physical strength and endurance.
3. Pale blue Soul in the north: Normal/Fairy, healing and resilience.
4. The three aspects settle at the center. A camera pan, cries, white fades and
   affectionate dialogue precede their reunion into the existing Spirit of Riko.
   Speak to the Spirit for the final Fire/Fairy fight when ready.

The aspects preserve ordinary Riko's proven battle/icon/follower geometry with
separate native aura palettes. They are female boss entities with no evolution
or Mega routes. Each boss is strongest non-egg party level +10, capped at100.
Below party level20, gentler move sets allow testing with early starters. The
four stages use distinct existing legendary/Champion themes, scoped to these exact
species and this exact map, never a global music override.

The shared safe Spirit callback heals before and after battles and restores the
previous no-catching flag on victory, loss or escape. Loss does not blackout,
charge money, or erase won phases. The cave does not block normal progression.
The cushion is an additional deliberate recovery point before the finale.

The guide returns to New Bark. The two southern arrow warps return through Mom's
existing outdoor doorway warp. Declining the guide's exit offers a second,
explicitly confirmed TEST restart of these four fights only. Badges, other
quests, already earned memories, pending rewards and keepsakes remain earned.

## Saved state, rewards and registrations

- `VAR_RIKO_CAVERN_STATE = 0x412E`: 0 Mind waiting,1 Mind won,2 Body won,
  3 Soul won/reunited/finale waiting,4 finale won. Each win alone advances it.
- `FLAG_RIKO_CAVERN_COMPLETE = 0x108D`: permanent final victory, retained through
  the testing restart. This gates the scrapbook memory, Riko letter/checklist
  and existing Riko's Spark keepsake. Full-Bag gifts can be reclaimed by Mom or
  the Spirit without a new fight or current-party requirement.
- Existing `FLAG_DEFEATED_SUICUNE` wins still qualify for their old Riko letter
  and Spark. The new cave never sets that flag or duplicates its reward.
- Boss species append at1611/1612/1613: `SPECIES_RIKO_ASPECT_MIND/BODY/SOUL`.
  Original real species IDs remain stable; the Egg/UI sentinel moves.
- Layout1034 and IndoorNewBark map6 append, preserving every old map/layout ID.
- Temporary flags1-4 reconstruct local visibility. Template coordinates reset
  on entry before settling earned aspects. Only Soul's south approach is open,
  providing a fixed safe camera-pan origin; no forced player walking is used.
- Production save arrays and SaveBlock ABI are unchanged. New var/flag slots
  were audited in active source, headers and scripts against5eaa4ea0. Decimal
  4237 occurred only in an unrelated generated trainer `#line` directive.

Final evolution unlocks and permanent late-game sanctuary entrance remain a
separate chapter. This pilot awards the existing narrative keepsake, never
captures a boss or evolves the player's Riko automatically.

## Verification

`tools/riko_arena/validate.py` executes actual assembly with engine stubs for
order/decline/loss/escape/no-party, all four wins and reunion, full-Bag recovery,
repeat claims, historical wins, testing entry/reset and all saved-state geometry.
It checks actual metatile behavior, warp approaches, actor approaches, camera
origin, script/Pory parity, wrapping, label resolution and original ID prefixes.

`test/riko_cavern.c` checks actual engine battle preparation, healthy/female
identity, thematic moves, scaling/caps/Egg exclusion, invalid input preservation,
asset registration and SaveBlock ABI. These engine checks and source simulation
are distinct from rendered interactive playtesting.

Still verify in an emulator: mailbox entry, cave loading and scrolling, native
palette colors, each battle's animation/music, camera pan/reunion, input after
loss, exits, saving/reloading after every phase, and restart/full-Bag reclaim.

Local final verification: production ROM compiled, all five new engine tests
passed, five new source/geometry groups and26 existing Garden/Rift/Sisters groups
passed, and docs-summary/diff checks passed. Rendered interaction remains pending.

## Scott's amulet and temporary level-one testing

Scott gives Riko's Amulet (`ITEM_RIKOS_AMULET=954`) immediately after the
festival picnic. Return visits check the saved picnic flag before party or
battle checks, so older completed saves and full-Bag retries need neither the
trio in the party nor another sunset match. Receipt is recorded only after a
successful grant (`FLAG_RIKOS_AMULET_RECEIVED=0x108E`, audited unused).

The reusable, protected Key Item uses the normal Bag/registered-item field
callback. Only both actual story completion flags, Penny in Blackthorn and
Bijuu in Ecruteak, awaken its travel prompt. Home tests, earlier Rift trials,
keepsake ownership, and historical Riko wins do not substitute for either win.
Declining or using a dormant amulet changes no progress. Accepting travels to
cavern (16,26), retaining completed phases. Use it on land outside in a town,
city or ordinary route; indoor/facility/underwater/surfing use and travel with a
companion who cannot leave are refused. Existing cave exits return to New Bark.
The explicitly labeled New Bark mailbox TEST entrance remains an ungated bypass.

`RIKO_CAVERN_LEVEL_ONE_TEST=1` temporarily creates all four cavern opponents at
level 1 with their early moves. Set it to 0 to restore strongest non-egg +10
(capped 100) and normal move selection. This affects neither Penny/Bijuu's final
story battles nor the midgame Rift guardians. Testing victories still save
cavern progress, memories and pending Spark rewards; the guide can reset the
four phases without erasing earned rewards.

The approved charcoal-and-gold Pom pendant has three violet/amber/blue gems.
Its generated standalone art is converted by tools/amulet/import_icon.py into
one 24x24, sixteen-color Bag icon. The awakened glow is conveyed in dialogue;
the Bag icon itself stays the same. No save structure or old ID changes.

## Reunion camera return repair

Player testing reached the three-aspect reunion, then left the player offscreen
and controls unavailable. The old sequence detached its temporary camera while
still scrolled six tiles south. RemoveCameraObject only changes the followed
sprite and resets camera tracking; it does not undo the accumulated scroll.
The reveal now plays a normal cry with a bounded 60-frame pause, pans six tiles
north, waits for the camera movement explicitly, and removes it BEFORE the
Awakened dialogue. The final reveal no longer depends on cry completion to
reach camera cleanup. The cry wait's role in the reported stall is unconfirmed.

The script validator now tracks actual movement definitions and refuses camera
removal with a nonzero accumulated offset. This regression fails the old script
and passes the repaired sequence. Pory and assembly remain identical; saved
phase IDs, victories, pending rewards and level-one testing remain unchanged.
Reload a normal in-game save before the sequence to replay it; an emulator save
state captured during the old locked script is not a reliable recovery point.
