# Player hats prototype

In the New Bark bedroom, interact with the right bookshelf at **6,1** (stand
below it at **6,2**). It now holds her free hat selection: **Original hat**,
**Pink bow**, **Vacation sunhat**, **Riko Hat**, **Penny Hat**, and **Bijuu Hat**. No Badge or trip completion is required.
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
variables array: zero means original, one bow, two sunhat, three Riko, four
Penny, five Bijuu; invalid values read
as original without rewriting saves. No save structures, species, items or
earned progress are changed. New field graphics occupy the explicit reserved
range **0x180-0x194**, resolved before the normal fallback. **NUM_OBJ_EVENT_GFX
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


## Walking-only family hats

Riko Hat is a pair of fluffy dark Pom ears with brown accents and a pink bow.
Bijuu Hat has chocolate Siamese ears, cream inner details and a pink ribbon.
Penny Hat is deliberately named without revealing its hot-dog shape on the
menu. The fitting dialogue reveals the joke after selection.

The three new choices apply only to normal walking/running graphics. On bikes,
while surfing/fishing/diving, in decoration previews, trainer portraits and
battles, the player uses her ordinary art. The saved selection is retained and
returns when she walks again. Existing bow/sunhat full-state behavior is intact.
All accessories use the current brown-hair/more-pink native palette.

Field IDs402-404 append after the original eighteen accessory IDs. Their native
16x32 frame size, nine walking frames followed by nine running frames, animation
metadata and reflection handling match MayNormal. Normalization explicitly
handles these IDs without changing NUM_OBJ_EVENT_GFX330 or old dynamic IDs.
Saved choices0-2 retain their meaning; no new variable or save format is added.

Built-in image generation supplied the three front/back/left accessory atlases
in `graphics/player_hats/family_sources/{riko,penny,bijuu}.png`. Prompts specified
isolated transparent GBA pixel accessories, dark Pom ears/brown accents/pink bow,
a bun/sausage/zigzag pink-red ketchup hot-dog hat, and chocolate/cream Siamese ears
with a pink ribbon, respectively. No faces/bodies/text were requested.
`build_family.py` only converts file formats; `family_render.c` identifies each
opaque silhouette, downsamples it to the native cap area, quantizes to existing
indices and preserves the original face/body below that area. Six indexed PNGs
compile with frame-contiguous2x4 tile rules. Source references never load into
GBA memory.

The validator checks all54 family frames plus186 original accessory frames,
indexed palette/body preservation and exact compiled tile order. Native engine
checks cover all six saved choices and avatar states, activity fallback and
restoration, trainer fallback and historical save IDs/size. Production build,
engine checks and source/binary verification are separate from emulator testing.

Family batch validation: production RELEASE build passes; focused engine suite
35passes plus21 intentional harness failures, no unexpected failures. All54
new frames match their actual production-ROM payloads. New rendered emulator
walking/running/save-reload remains for user confirmation.
