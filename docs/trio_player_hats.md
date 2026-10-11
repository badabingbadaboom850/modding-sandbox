# Player hats prototype

In the New Bark bedroom, interact with the right bookshelf at **6,1** (stand
below it at **6,2**). It now holds her free hat selection: **Original hat**,
**Pink bow**, and **Vacation sunhat**. No Badge or trip completion is required.
Cancel leaves the current selection unchanged. Selecting a look updates the
field sprite immediately; ordinary in-game saving preserves it.

The female player's ten native field sheets, front portrait and four battle
throw frames have accessory variants. The original brown-hair/pink-clothes
palettes, native animation order, poses and body pixels outside the head area
stay intact. Decoration, Pokédex comparison, local trainer card, Hall of Fame,
and local battle transitions use the same saved selection. Ordinary NPCs,
Copycat's historical May graphic, rival graphics and received link cards keep
their original art. Link battle trainer art remains the ordinary default.

`VAR_TRIO_PLAYER_HAT` uses audited unused **0x4144** inside the existing saved
variables array: zero means original, one bow, two sunhat; invalid values read
as original without rewriting saves. No save structures, species, items or
earned progress are changed. New field graphics occupy the explicit reserved
range **0x180-0x191**, resolved before the normal fallback. **NUM_OBJ_EVENT_GFX
remains 330**, so historical dynamic graphics IDs remain unchanged. Four
trainer IDs append after all historical trainer IDs; the old front-count
boundary and existing back IDs remain unchanged.

Accessory art was made with the built-in imagegen tool. The production prompt
requested six transparent accessory tiles: forward/back/left pink bow with
brown hair, and forward/back/left straw sunhat with pink ribbon; crisp GBA pixel
style using existing outline, hair, pink, straw and white palette colors.
The untouched generated reference lives in
`graphics/player_hats/accessory-reference.png`. `tools/player_hats/build.py`
converts file formats and invokes the native indexed-frame compiler
`render.c`; committed PNG variants are consumed by the ordinary asset build.
The compiler places accessories relative to each original cap, including
individual fishing and throwing poses, and keeps the rest of each frame.
Underwater variants preserve the native monochrome diving palette.

The battle throw handler now indexes its palette by the same full trainer ID
used by the registered back-sprite table, matching the existing decompression
path and supporting the appended hat sprites.

Validation: four new actual-engine tests pass; the focused hat/radio/Road Trip
suite reports **32 passes plus 21 expected runner self-test failures**, zero
unexpected failures across three shards. All **186 native accessory frames**
retain the source dimensions, indexed palettes and body pixels outside the
head region. Nine family-days and ten Road Trip source/script/geometry groups
pass. Historical saved ABI, species/flags/field graphics and current palettes
remain unchanged. The new committed head's CI is separate.

This is a first playable prototype. Source/native-engine validation and a
production build are distinct from a rendered emulator playthrough. Verify
all directions, running, both bikes, surfing/fishing, a battle entrance, local
trainer card, original-hat restoration and an in-game save/reload in testing.
