# Pom Fu Riko

Talk to Cianwood City's existing martial artist at **20,54** with any ordinary
Riko family form in the party. She recognizes Riko's stance and offers a free
**Riko Black Belt**. Decline/full Bag can retry; ownership prevents duplicates.
No Badge or battle is required. Her original story/atmosphere dialogue still
follows; no map object, event, visibility or collision is changed.

Use the protected reusable Key Item on ordinary, Balloon, Princess or Raincoat
Riko to become **PomFuRiko**. Use it again on Pom Fu Riko to return to ordinary
Riko. Other elemental/permanent forms return through their own existing items
first. Transformation uses normal item evolution and never consumes the belt.
No new-game/testing grant is added.

She is female **Normal/Fighting**, retaining Riko's dex identity and growth:
HP90, Attack110, Defense95, Speed105, Special Attack70, Special Defense90 (560).
Cute Charm/hidden Fluffy remain. Her own white gi/black belt battle sprites,
menu icon and six directional follower frames use matched transparent16-color
normal/shiny palettes. She is a functional elemental form, not a cosmetic skin.

Force Palm is the transformation attack. Level progression: Tackle/Focus Energy1,
Rock Smash8, Mach Punch12, Force Palm16, Brick Break20, Bulk Up24, Drain Punch28,
Detect32, Aura Sphere36 and Close Combat44. Scott's existing elemental lesson menu
teaches eligible damaging Fighting attacks at her actual level, skipping known
moves. Equipped attacks remain through reversion. Riko signature eligibility,
family scripts, Camp statistics and Spirit Mega eligibility include this form.

Species1629 and item965 append; all historical real IDs, Riko form indices,
saved arrays/ABI and earned progress remain intact. Egg sentinel follows the
new species. Costume album is unchanged because this is an elemental form.

Built-in imagegen supplied the isolated front/back/icon/down/left/up/Black Belt
atlas under graphics/pokemon/riko_fighting/source.png. Prompt requested a black
female Pom with brown brows/cheeks, white chest, white gi and black belt, dog paws,
transparent pixel art and separate native sprite poses. Native C conversion in
tools/costumes/pom_fu_render.c owns inspected cell crops, scaling and quantization;
import_pom_fu.py handles image formats only. Followers are compiled as contiguous
4x4 tile frames. Source and engine validation remain separate from rendered
in-game gift/evolution/animation/save-reload confirmation.

Validation:103 focused engine/battle/species/text checks pass with21 expected
harness failures and zero unexpected failures. Includes belt eligibility,
current-level lessons, encrypted form/move persistence, saved ABI and a Spirit
Mega battle returning to Pom Fu.16 actual NPC gift flows, matched compiled art
and all240 player hat frames pass source/binary checks. No emulator playthrough
is claimed.
