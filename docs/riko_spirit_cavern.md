# Spirit of Riko cavern and keepsake Megas

A dedicated cave replaces reliance on the unresolved Shoal Cave loading path for
new Riko boss development. The old cave and its Suicune-backed flags remain
unchanged; this pilot does not establish a fix for it.

## Natural entrance

Scott gives Riko's Amulet after the Goldenrod festival picnic. Complete BOTH
actual final story Spirit battles: Penny in Blackthorn (eight Johto Badges) and
Bijuu in Ecruteak (Champion). Use the amulet from the Bag or registered slot
on ordinary outdoor land to accept travel to the cavern. Earlier Rift trials,
home wins and keepsake possession do not replace those final victories.
The New Bark mailbox testing entrance has been removed. No startup warp or
progression grants are present. Battle preparation also enforces the picnic,
amulet ownership and both final victories, including saves left inside during testing.

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
All six IVs are31 and each has a deliberate252/252/4 EV spread. Mind and final
Spirit carry Life Orb, Body a Lum Berry, and Soul Leftovers. Cavern-only AI
checks move effectiveness, setup/recovery value, finishing attacks and HP.
The final Spirit uses Flamethrower, Moonblast, Dark Pulse and Calm Mind.
Below party level20, gentler move sets allow testing with early starters. The
four stages use distinct existing legendary/Champion themes, scoped to these exact
species and this exact map, never a global music override.

The shared safe Spirit callback heals before and after battles and restores the
previous no-catching flag on victory, loss or escape. Loss does not blackout,
charge money, or erase won phases. The cave does not block normal progression.
The cushion is an additional deliberate recovery point before the finale.

The guide returns to New Bark. The two southern arrow warps return through Mom's
existing outdoor doorway warp. Declining the guide's exit returns control.
The temporary reset offer has been removed; all saved wins remain earned.

## Saved state, rewards and registrations

- `VAR_RIKO_CAVERN_STATE = 0x412E`: 0 Mind waiting,1 Mind won,2 Body won,
  3 Soul won/reunited/finale waiting,4 finale won. Each win alone advances it.
- `FLAG_RIKO_CAVERN_COMPLETE = 0x108D`: permanent final victory. This gates the scrapbook memory, Riko letter/checklist
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

## Keepsakes enable temporary Spirit Megas

| Girl | Protected Key Item | Actual victory required | Mega species |
| --- | --- | --- | --- |
| Riko | Riko's Spark | Cavern finale AND both final sister fights |1614 |
| Penny | Penny's Shield | Final Blackthorn Spirit |1615 |
| Bijuu | Bijuu's Light | Final Ecruteak Spirit |1616 |

Keep the keepsake in the Bag and use the normal battle Mega button with a Mega
Ring. This uses the normal once-per-trainer Mega limit. No held Key Item, item
consumption or permanent evolution is needed; using the keepsake in the field
still reads her letter. Existing keepsakes and full-Bag reward claims work.
Legacy home/Suicune keepsakes alone do not enable Spirit Megas.

All30 ordinary/personal forms qualify. Each returns to her exact starting form
on fainting or battle cleanup through the existing changedSpecies mechanism.
Permanent personal forms have entry-only tables so they are not reverted when
no Mega occurred. Holding a Mega Stone keeps its existing Mega pathway ahead
of the keepsake. NPC partners and opposing battlers cannot borrow the player's
Bag unlock. Boss entities and existing Mega species do not qualify.

These are separate Mega-only species reusing the established Spirit battle,
menu and follower art; boss stats/species remain independent. Existing species
IDs, saved flags/vars, Key Item IDs/pockets and SaveBlock ABI remain stable.

## Verification

`tools/riko_arena/validate.py` executes actual assembly with engine stubs for
order/decline/loss/escape/no-party, all four wins and reunion, full-Bag recovery,
repeat claims, historical wins, normal entry/no-reset and all saved-state geometry.
It checks actual metatile behavior, warp approaches, actor approaches, camera
origin, script/Pory parity, wrapping, label resolution and original ID prefixes.

`test/riko_cavern.c` checks actual engine battle preparation, healthy/female
identity, thematic moves, scaling/caps/Egg exclusion, invalid input preservation,
asset registration and SaveBlock ABI. These engine checks and source simulation
are distinct from rendered interactive playtesting.

Still verify in an emulator: amulet entry, cave loading and scrolling, native
palette colors, each battle's animation/music, camera pan/reunion, input after
loss, exits, saving/reloading after every phase, and full-Bag reclaim. Also check rendered Mega prompts/animations and saving after battle.

Local final verification: production ROM compiled, all five new engine tests
passed, five new source/geometry groups and26 existing Garden/Rift/Sisters groups
passed, and docs-summary/diff checks passed. Rendered interaction remains pending.

## Scott's amulet

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
The temporary New Bark mailbox bypass is removed.

`RIKO_CAVERN_LEVEL_ONE_TEST=0` restores endgame scaling and normal moves for all
four fights. Existing level-one test victories remain saved. No testing reset
or bypass remains in the scripts. Penny/Bijuu final story fights and midgame
Rift guardians retain their existing difficulty.

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
phase IDs, victories and pending rewards remain unchanged. The user confirmed
the repaired reunion works; this release restores difficulty separately.
Reload a normal in-game save before the sequence to replay it; an emulator save
state captured during the old locked script is not a reliable recovery point.


Release verification:72 focused actual engine/battle/text tests pass, plus7
expected runner self-test failures and zero unexpected failures. Spirit tests
exercise all30 eligible forms, fainting and exact-form return, actual final
victory/Bag gates, opponents and NPC partners, and existing Bondstone Megas.
Cavern tests cover restored scaling/caps, trained stats/items, proper access
and save ABI.83 family source/geometry/flow groups plus inclusive docs-summary
and diff checks pass. The player confirmed the prior reunion camera repair;
new Spirit Mega UI/animations and difficult balance still need rendered
interactive confirmation. Headless battle tests are not a rendered playthrough.

Final production ROM compilation passed (ROM32514296 bytes, EWRAM255420 bytes).
