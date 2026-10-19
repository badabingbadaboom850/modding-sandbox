# Trio Action Arena

An optional native GBA real-time training arena. Talk to the gentleman at
**New Bark (18,14)**, in front of the player's house, for free travel. In the
garden lobby, **Scott at (9,6)** starts practice. The southern guide and both
walk-out exits return to **New Bark (18,12)**. No badges or party composition
are required for this testing entrance.

Choose Riko, Bijuu or Penny with Left/Right and press A. Each match has three
one-on-one Greedent rounds, introducing a telegraphed charge, aimed berry
volleys, then a close stomp. Enemy warnings lock their target before attacking.
Between rounds, recover up to 25 training HP. All three rounds are replayable.

| Input | Action |
| --- | --- |
| D-pad | Move; last movement direction aims attacks |
| A (hold) | Repeat the primary attack when ready |
| B (press) | Use the secondary attack when ready |
| R (press) | Dodge with brief invulnerability |
| L (hold) | Face the opponent while moving freely |
| Start / Select | Pause; A/Start resumes, B leaves |

Riko fires medium-range barks and a close radial Pom Boom. Bijuu fires
long-range moon orbs and a three-shot frost fan that slows the opponent.
Penny has a short paw swipe and an invulnerable Brave Charge that hits once.
Bars show HP and attack recharge. A visible floor line marks a charge/volley
target; a warning ring marks the stomp radius.

Practice uses independent temporary health and fixed training attacks. It
does **not** use or modify party HP, levels, moves, forms, gender, inventory,
money, experience, quest progress, or the existing turn-based battle engine.
The selectable girls are training representations with their ordinary native
overworld graphics; party costumes and learned moves are not imported yet.
There are no prizes, capture mechanics or persistent arena records in this
first version. Normal save access is available in the lobby, outside combat.

## Implementation and compatibility

- `src/trio_action_arena_core.c` owns the deterministic frame simulation and
  bounded projectile pools. It has no engine/save/RNG calls.
- `src/trio_action_arena.c` owns the native arena scene, graphics, controls,
  menus, palette fades and return callback. It follows the existing minigame
  lifecycle and returns to the waiting referee script on every exit.
- `TrioActionArena` appends to IndoorNewBark; previous map numbers and all
  existing layouts remain unchanged. The lobby shares the proven garden layout.
- The New Bark actor appends after existing local IDs. Its conservative
  viewport count, including player/follower, is at most sixteen.
- The new special appends to the table. No save fields, saved flags/variables,
  species, items or trainer IDs are allocated. Only map-local `VAR_TEMP_A`
  dispatches the lobby's walk-out exits.
- The original New Bark scripts, mailbox, quiz, Scott tutor and story are
  retained. The user explicitly requested this separate NPC testing entrance.

## Validation

Run `python3 tools/action_arena/validate.py` for actual event wiring, text/font,
decoded collision/exit behaviors, historical-map stability and reachable paths.
`test/trio_action_arena.c` tests cooldowns, directional movement, invulnerability,
single-hit attacks, girl-specific specials, slow, round transitions, defeat,
terminal states and actual party preservation through the native test runner.

Compilation, source checks and simulation do not prove rendered emulator
behavior. The focused interactive pass should verify every girl's sprites and
controls, visible telegraphs, all three rounds, pause/resume, retry, defeat,
leaving mid-match, lobby save/reload and both returns to New Bark. Use ordinary
in-game saves when updating ROMs; an emulator snapshot contains old code state.
