# Hat packing and custom battle-ball repair

The first hat build compiled horizontal avatar sheets in whole-image tile
order. The engine copies one contiguous frame at a time; it therefore rendered
pieces of adjacent hats instead of a whole character. The new rules in
`spritesheet_rules.mk` use the native May frame sizes: 2x4 tiles for narrow
walking/running/decoration, 4x4 for other field sheets, and 8x8 for trainer art.
The rules file is an asset dependency so cached prototype tiles are rebuilt.
Hat choices, source PNG art, palettes and all saved variables stay unchanged.

The player-hat validator now decodes the actual compiled 4bpp frame blocks
against every PNG pixel. It reproduces the prototype failure and passes for
all186 corrected frames. Checking the source PNG alone did not catch this.

The four rethemed balls previously changed only their Bag icons. Battle
graphics now use matching three-frame closed/opening/open sheets for Trio
(Great), Riko Ultra, Bijuu Moon and Penny Love, bound to the exact existing
Bag palettes. Great and Ultra bypass the standard open-frame overwrite so
their custom shells survive `LoadBallGfx`. Other balls retain their original
art and loader behavior. Existing captured Pokémon with those historical ball
IDs also show the new art during send-out. Item IDs, prices, effects, catch
rates, rewards and save data are unchanged; no balls are granted or consumed
by this update.

The built-in imagegen tool produced each three-cell battle sheet using its
existing Bag icon as the exact design/color reference and native battle sheet
as the geometry reference. Prompts requested closed/opening/fully-open frames,
transparent backgrounds, crisp GBA pixels, and no new design or labels.
References are committed under `graphics/balls/custom_sources`; the C native
palette compiler and format converter live under `tools/custom_balls`.

Two new actual-engine tests check historical registration and all1536 bytes
loaded into VRAM for the four custom sheets, covering their twelve frames.
The focused hats/balls/radio/Road Trip suite passes34 checks plus21 expected
runner self-test failures across three shards, with no unexpected failures.
Compiled ball/frame/palette and historical-source checks pass. RELEASE=1 ROM
build succeeds (32666372 linked bytes, EWRAM255416). This is distinct from the
wife's next rendered emulator test. Keep PR#2 draft/unmerged.
