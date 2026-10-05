Warning: truncated output (original token count: 65991)
Total output lines: 7886

#include "global.h"
#include "achievements.h"
#include "malloc.h"
#include "apprentice.h"
#include "battle.h"
#include "battle_facility_bgm.h"
#include "battle_ai_util.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_dome.h"
#include "battle_message.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "battle_z_move.h"
#include "caps.h"
#include "data.h"
#include "daycare.h"
#include "dexnav.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "evolution_scene.h"
#include "field_player_avatar.h"
#include "field_specials.h"
#include "field_weather.h"
#include "fishing.h"
#include "follower_npc.h"
#include "frontier_util.h"
#include "graphics.h"
#include "item.h"
#include "link.h"
#include "m4a.h"
#include "main.h"
#include "move_relearner.h"
#include "naming_screen.h"
#include "overworld.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokeblock.h"
#include "pokemon.h"
#include "pokemon_animation.h"
#include "pokemon_icon.h"
#include "pokemon_summary_screen.h"
#include "pokemon_storage_system.h"
#include "pokerus.h"
#include "random.h"
#include "recorded_battle.h"
#include "replay_options.h"
#include "regions.h"
#include "rtc.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "test_runner.h"
#include "text.h"
#include "trainer_hill.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/battle_frontier.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_partner.h"
#include "constants/battle_script_commands.h"
#include "constants/battle_string_ids.h"
#include "constants/cries.h"
#include "constants/event_objects.h"
#include "constants/form_change_types.h"
#include "constants/item_effects.h"
#include "constants/items.h"
#include "constants/layouts.h"
#include "constants/moves.h"
#include "constants/party_menu.h"
#include "constants/regions.h"
#include "constants/songs.h"
#include "constants/trainers.h"
#include "constants/union_room.h"
#include "constants/weather.h"
#include "wild_encounter.h"

extern u16 gSpecialVar_ItemId;

extern u16 gSpecialVar_ItemId;

#define FRIENDSHIP_EVO_THRESHOLD ((P_FRIENDSHIP_EVO_THRESHOLD >= GEN_8) ? 160 : 220)

struct SpeciesItem
{
    u16 species;
    enum Item item;
    enum Item item2;
};

static metloc_u16_t GetBoxMonMetLocation(struct BoxPokemon *boxMon);
static void SetBoxMonMetLocation(struct BoxPokemon *boxMon, metloc_u16_t metLocation);
static u8 GetBoxMonMetLocationHi(struct BoxPokemon *boxMon);
static void SetBoxMonMetLocationHi(struct BoxPokemon *boxMon, u8 metLocationHi);
static void TryToSetBoxFormChangeMoves(struct BoxPokemon *boxMon, enum FormChanges method, u16 targetSpecies);
static void Task_PlayMapChosenOrBattleBGM(u8 taskId);
void TrySpecialOverworldEvo();

EWRAM_DATA static u8 sLearningMoveTableID = 0;
EWRAM_DATA u8 gPlayerPartyCount = 0;
EWRAM_DATA u8 gEnemyPartyCount = 0;
EWRAM_DATA struct Pokemon gPlayerParty[PARTY_SIZE] = {0};
EWRAM_DATA struct Pokemon gEnemyParty[PARTY_SIZE] = {0};
EWRAM_DATA struct SpriteTemplate gMultiuseSpriteTemplate = {0};
EWRAM_DATA static struct MonSpritesGfxManager *sMonSpritesGfxManagers[MON_SPR_GFX_MANAGERS_COUNT] = {NULL};
EWRAM_DATA static u8 sTriedEvolving = 0;
EWRAM_DATA u16 gFollowerSteps = 0;

#include "data/abilities.h"

// Used in an unreferenced function in RS.
// Unreferenced here and in FRLG.
struct CombinedMove
{
    u16 move1;
    u16 move2;
    u16 newMove;
};

static const struct CombinedMove sCombinedMoves[2] =
{
    {MOVE_EMBER, MOVE_GUST, MOVE_HEAT_WAVE},
    {0xFFFF, 0xFFFF, 0xFFFF}
};

// NOTE: The order of the elements in the array below is irrelevant.
// To reorder the pokedex, see the values in include/constants/pokedex.h.

#define HOENN_TO_NATIONAL(name)     [HOENN_DEX_##name - 1] = NATIONAL_DEX_##name

// Assigns all Hoenn Dex Indexes to a National Dex Index
static const enum NationalDexOrder sHoennToNationalOrder[HOENN_DEX_COUNT - 1] =
{
    HOENN_TO_NATIONAL(TREECKO),
    HOENN_TO_NATIONAL(GROVYLE),
    HOENN_TO_NATIONAL(SCEPTILE),
    HOENN_TO_NATIONAL(TORCHIC),
    HOENN_TO_NATIONAL(COMBUSKEN),
    HOENN_TO_NATIONAL(BLAZIKEN),
    HOENN_TO_NATIONAL(MUDKIP),
    HOENN_TO_NATIONAL(MARSHTOMP),
    HOENN_TO_NATIONAL(SWAMPERT),
    HOENN_TO_NATIONAL(ZIGZAGOON),
    HOENN_TO_NATIONAL(LINOONE),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GALARIAN_FORMS
    HOENN_TO_NATIONAL(OBSTAGOON),
#endif
    HOENN_TO_NATIONAL(LOTAD),
    HOENN_TO_NATIONAL(LOMBRE),
    HOENN_TO_NATIONAL(LUDICOLO),
    HOENN_TO_NATIONAL(SEEDOT),
    HOENN_TO_NATIONAL(NUZLEAF),
    HOENN_TO_NATIONAL(SHIFTRY),
    HOENN_TO_NATIONAL(WINGULL),
    HOENN_TO_NATIONAL(PELIPPER),
    HOENN_TO_NATIONAL(RALTS),
    HOENN_TO_NATIONAL(KIRLIA),
    HOENN_TO_NATIONAL(GARDEVOIR),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(GALLADE),
#endif
    HOENN_TO_NATIONAL(SHROOMISH),
    HOENN_TO_NATIONAL(BRELOOM),
    HOENN_TO_NATIONAL(ABRA),
    HOENN_TO_NATIONAL(KADABRA),
    HOENN_TO_NATIONAL(ALAKAZAM),
    HOENN_TO_NATIONAL(NINCADA),
    HOENN_TO_NATIONAL(NINJASK),
    HOENN_TO_NATIONAL(SHEDINJA),
    HOENN_TO_NATIONAL(MAKUHITA),
    HOENN_TO_NATIONAL(HARIYAMA),
    HOENN_TO_NATIONAL(MAGIKARP),
    HOENN_TO_NATIONAL(GYARADOS),
    HOENN_TO_NATIONAL(AZURILL),
    HOENN_TO_NATIONAL(MARILL),
    HOENN_TO_NATIONAL(AZUMARILL),
    HOENN_TO_NATIONAL(GEODUDE),
    HOENN_TO_NATIONAL(GRAVELER),
    HOENN_TO_NATIONAL(GOLEM),
    HOENN_TO_NATIONAL(NOSEPASS),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(PROBOPASS),
#endif
    HOENN_TO_NATIONAL(ZUBAT),
    HOENN_TO_NATIONAL(GOLBAT),
    HOENN_TO_NATIONAL(CROBAT),
    HOENN_TO_NATIONAL(TENTACOOL),
    HOENN_TO_NATIONAL(TENTACRUEL),
    HOENN_TO_NATIONAL(SABLEYE),
    HOENN_TO_NATIONAL(MAWILE),
    HOENN_TO_NATIONAL(ARON),
    HOENN_TO_NATIONAL(LAIRON),
    HOENN_TO_NATIONAL(AGGRON),
    HOENN_TO_NATIONAL(MACHOP),
    HOENN_TO_NATIONAL(MACHOKE),
    HOENN_TO_NATIONAL(MACHAMP),
    HOENN_TO_NATIONAL(MEDITITE),
    HOENN_TO_NATIONAL(MEDICHAM),
    HOENN_TO_NATIONAL(ELECTRIKE),
    HOENN_TO_NATIONAL(MANECTRIC),
    HOENN_TO_NATIONAL(MAGNEMITE),
    HOENN_TO_NATIONAL(MAGNETON),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(MAGNEZONE),
#endif
    HOENN_TO_NATIONAL(VOLTORB),
    HOENN_TO_NATIONAL(ELECTRODE),
    HOENN_TO_NATIONAL(ODDISH),
    HOENN_TO_NATIONAL(GLOOM),
    HOENN_TO_NATIONAL(VILEPLUME),
    HOENN_TO_NATIONAL(BELLOSSOM),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(BUDEW),
#endif
    HOENN_TO_NATIONAL(ROSELIA),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(ROSERADE),
#endif
    HOENN_TO_NATIONAL(CARVANHA),
    HOENN_TO_NATIONAL(SHARPEDO),
    HOENN_TO_NATIONAL(NUMEL),
    HOENN_TO_NATIONAL(CAMERUPT),
    HOENN_TO_NATIONAL(TORKOAL),
    HOENN_TO_NATIONAL(GRIMER),
    HOENN_TO_NATIONAL(MUK),
    HOENN_TO_NATIONAL(KOFFING),
    HOENN_TO_NATIONAL(WEEZING),
    HOENN_TO_NATIONAL(SANDSHREW),
    HOENN_TO_NATIONAL(SANDSLASH),
    HOENN_TO_NATIONAL(SKARMORY),
    HOENN_TO_NATIONAL(TRAPINCH),
    HOENN_TO_NATIONAL(VIBRAVA),
    HOENN_TO_NATIONAL(FLYGON),
    HOENN_TO_NATIONAL(CACNEA),
    HOENN_TO_NATIONAL(CACTURNE),
    HOENN_TO_NATIONAL(SWABLU),
    HOENN_TO_NATIONAL(ALTARIA),
    HOENN_TO_NATIONAL(BARBOACH),
    HOENN_TO_NATIONAL(WHISCASH),
    HOENN_TO_NATIONAL(BALTOY),
    HOENN_TO_NATIONAL(CLAYDOL),
    HOENN_TO_NATIONAL(LILEEP),
    HOENN_TO_NATIONAL(CRADILY),
    HOENN_TO_NATIONAL(IGGLYBUFF),
    HOENN_TO_NATIONAL(JIGGLYPUFF),
    HOENN_TO_NATIONAL(WIGGLYTUFF),
    HOENN_TO_NATIONAL(FEEBAS),
    HOENN_TO_NATIONAL(MILOTIC),
    HOENN_TO_NATIONAL(STARYU),
    HOENN_TO_NATIONAL(STARMIE),
    HOENN_TO_NATIONAL(SHUPPET),
    HOENN_TO_NATIONAL(BANETTE),
    HOENN_TO_NATIONAL(DUSKULL),
    HOENN_TO_NATIONAL(DUSCLOPS),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(DUSKNOIR),
#endif
    HOENN_TO_NATIONAL(TROPIUS),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(CHINGLING),
#endif
    HOENN_TO_NATIONAL(CHIMECHO),
    HOENN_TO_NATIONAL(ABSOL),
    HOENN_TO_NATIONAL(VULPIX),
    HOENN_TO_NATIONAL(NINETALES),
    HOENN_TO_NATIONAL(PICHU),
    HOENN_TO_NATIONAL(PIKACHU),
    HOENN_TO_NATIONAL(RAICHU),
    HOENN_TO_NATIONAL(WYNAUT),
    HOENN_TO_NATIONAL(WOBBUFFET),
    HOENN_TO_NATIONAL(NATU),
    HOENN_TO_NATIONAL(XATU),
    HOENN_TO_NATIONAL(GIRAFARIG),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_9_CROSS_EVOS
    HOENN_TO_NATIONAL(FARIGIRAF),
#endif
    HOENN_TO_NATIONAL(PHANPY),
    HOENN_TO_NATIONAL(DONPHAN),
    HOENN_TO_NATIONAL(PINSIR),
    HOENN_TO_NATIONAL(HERACROSS),
    HOENN_TO_NATIONAL(RHYHORN),
    HOENN_TO_NATIONAL(RHYDON),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(RHYPERIOR),
#endif
    HOENN_TO_NATIONAL(SNORUNT),
    HOENN_TO_NATIONAL(GLALIE),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(FROSLASS),
#endif
    HOENN_TO_NATIONAL(SPHEAL),
    HOENN_TO_NATIONAL(SEALEO),
    HOENN_TO_NATIONAL(WALREIN),
    HOENN_TO_NATIONAL(CLAMPERL),
    HOENN_TO_NATIONAL(HUNTAIL),
    HOENN_TO_NATIONAL(GOREBYSS),
    HOENN_TO_NATIONAL(RELICANTH),
    HOENN_TO_NATIONAL(CORSOLA),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GALARIAN_FORMS
    HOENN_TO_NATIONAL(CURSOLA),
#endif
    HOENN_TO_NATIONAL(CHINCHOU),
    HOENN_TO_NATIONAL(LANTURN),
    HOENN_TO_NATIONAL(HORSEA),
    HOENN_TO_NATIONAL(SEADRA),
    HOENN_TO_NATIONAL(KINGDRA),
    HOENN_TO_NATIONAL(BAGON),
    HOENN_TO_NATIONAL(SHELGON),
    HOENN_TO_NATIONAL(SALAMENCE),
    HOENN_TO_NATIONAL(BELDUM),
    HOENN_TO_NATIONAL(METANG),
    HOENN_TO_NATIONAL(METAGROSS),
    HOENN_TO_NATIONAL(REGIROCK),
    HOENN_TO_NATIONAL(REGICE),
    HOENN_TO_NATIONAL(REGISTEEL),
    HOENN_TO_NATIONAL(LATIAS),
    HOENN_TO_NATIONAL(LATIOS),
    HOENN_TO_NATIONAL(KYOGRE),
    HOENN_TO_NATIONAL(GROUDON),
    HOENN_TO_NATIONAL(RAYQUAZA),
    HOENN_TO_NATIONAL(JIRACHI),
    HOENN_TO_NATIONAL(DEOXYS),
};

#define JOHTO_DEX(name) [JOHTO_DEX_##name - 1] = NATIONAL_DEX_##name,
static const enum NationalDexOrder sJohtoToNationalOrder[JOHTO_DEX_COUNT - 1] =
{
#include "constants/johto_dex_order.h"
};
#undef JOHTO_DEX

const struct SpindaSpot gSpindaSpotGraphics[] =
{
    {.x = 16, .y =  7, .image = INCBIN_U16("graphics/pokemon/spinda/spots/spot_0.1bpp")},
    {.x = 40, .y =  8, .image = INCBIN_U16("graphics/pokemon/spinda/spots/spot_1.1bpp")},
    {.x = 22, .y = 25, .image = INCBIN_U16("graphics/pokemon/spinda/spots/spot_2.1bpp")},
    {.x = 34, .y = 26, .image = INCBIN_U16("graphics/pokemon/spinda/spots/spot_3.1bpp")}
};

// In Battle Palace, moves are chosen based on the pokemons nature rather than by the player
// Moves are grouped into "Attack", "Defense", or "Support" (see PALACE_MOVE_GROUP_*)
// Each nature has a certain percent chance of selecting a move from a particular group
// and a separate percent chance for each group when at or below 50% HP
// The table below doesn't list percentages for Support because you can subtract the other two
// Support percentages are listed in comments off to the side instead
#define PALACE_STYLE(atk, def, atkLow, defLow) {atk, atk + def, atkLow, atkLow + defLow}

const struct NatureInfo gNaturesInfo[NUM_NATURES] =
{
    [NATURE_HARDY] =
    {
        .name = COMPOUND_STRING("Hardy"),
        .statUp = STAT_ATK,
        .statDown = STAT_ATK,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_HARDY, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(61, 7, 61, 7), //32% support >= 50% HP, 32% support < 50% HP
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_LONELY] =
    {
        .name = COMPOUND_STRING("Lonely"),
        .statUp = STAT_ATK,
        .statDown = STAT_DEF,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_LONELY, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(20, 25, 84, 8), //55%,  8%
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_BRAVE] =
    {
        .name = COMPOUND_STRING("Brave"),
        .statUp = STAT_ATK,
        .statDown = STAT_SPEED,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_BRAVE, AFFINE_TURN_UP},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(70, 15, 32, 60), //15%, 8%
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_ADAMANT] =
    {
        .name = COMPOUND_STRING("Adamant"),
        .statUp = STAT_ATK,
        .statDown = STAT_SPATK,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_ADAMANT, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(38, 31, 70, 15), //31%, 15%
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_NAUGHTY] =
    {
        .name = COMPOUND_STRING("Naughty"),
        .statUp = STAT_ATK,
        .statDown = STAT_SPDEF,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_NAUGHTY, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(20, 70, 70, 22), //10%, 8%
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_BOLD] =
    {
        .name = COMPOUND_STRING("Bold"),
        .statUp = STAT_DEF,
        .statDown = STAT_ATK,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_BOLD, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(30, 20, 32, 58), //50%, 10%
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_DOCILE] =
    {
        .name = COMPOUND_STRING("Docile"),
        .statUp = STAT_DEF,
        .statDown = STAT_DEF,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_DOCILE, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(56, 22, 56, 22), //22%, 22%
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_RANDOM,
    },
    [NATURE_RELAXED] =
    {
        .name = COMPOUND_STRING("Relaxed"),
        .statUp = STAT_DEF,
        .statDown = STAT_SPEED,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_RELAXED, AFFINE_TURN_UP_AND_DOWN},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(25, 15, 75, 15), //60%, 10%
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_IMPISH] =
    {
        .name = COMPOUND_STRING("Impish"),
        .statUp = STAT_DEF,
        .statDown = STAT_SPATK,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_IMPISH, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(69, 6, 28, 55), //25%, 17%
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_LAX] =
    {
        .name = COMPOUND_STRING("Lax"),
        .statUp = STAT_DEF,
        .statDown = STAT_SPDEF,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_LAX, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(35, 10, 29, 6), //55%, 65%
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_TIMID] =
    {
        .name = COMPOUND_STRING("Timid"),
        .statUp = STAT_SPEED,
        .statDown = STAT_ATK,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_TIMID, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(62, 10, 30, 20), //28%, 50%
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_HASTY] =
    {
        .name = COMPOUND_STRING("Hasty"),
        .statUp = STAT_SPEED,
        .statDown = STAT_DEF,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_HASTY, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(58, 37, 88, 6), //5%, 6%
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_SERIOUS] =
    {
        .name = COMPOUND_STRING("Serious"),
        .statUp = STAT_SPEED,
        .statDown = STAT_SPEED,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_SERIOUS, AFFINE_TURN_DOWN},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(34, 11, 29, 11), //55%, 60%
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_JOLLY] =
    {
        .name = COMPOUND_STRING("Jolly"),
        .statUp = STAT_SPEED,
        .statDown = STAT_SPATK,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_JOLLY, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(35, 5, 35, 60), //60%, 5%
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_NAIVE] =
    {
        .name = COMPOUND_STRING("Naive"),
        .statUp = STAT_SPEED,
        .statDown = STAT_SPDEF,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_NAIVE, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(56, 22, 56, 22), //22%, 22%
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_RANDOM,
    },
    [NATURE_MODEST] =
    {
        .name = COMPOUND_STRING("Modest"),
        .statUp = STAT_SPATK,
        .statDown = STAT_ATK,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_MODEST, AFFINE_TURN_DOWN_SLOW},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(35, 45, 34, 60), //20%, 6%
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_MILD] =
    {
        .name = COMPOUND_STRING("Mild"),
        .statUp = STAT_SPATK,
        .statDown = STAT_DEF,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_MILD, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(44, 50, 34, 6), //6%, 60%
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_QUIET] =
    {
        .name = COMPOUND_STRING("Quiet"),
        .statUp = STAT_SPATK,
        .statDown = STAT_SPEED,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_QUIET, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(56, 22, 56, 22), //22%, 22%
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_BASHFUL] =
    {
        .name = COMPOUND_STRING("Bashful"),
        .statUp = STAT_SPATK,
        .statDown = STAT_SPATK,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_BASHFUL, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(30, 58, 30, 58), //12%, 12%
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_RASH] =
    {
        .name = COMPOUND_STRING("Rash"),
        .statUp = STAT_SPATK,
        .statDown = STAT_SPDEF,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_RASH, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(30, 13, 27, 6), //57%, 67%
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_CALM] =
    {
        .name = COMPOUND_STRING("Calm"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_ATK,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_CALM, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(40, 50, 25, 62), //10%, 13%
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_GENTLE] =
    {
        .name = COMPOUND_STRING("Gentle"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_DEF,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_GENTLE, AFFINE_TURN_DOWN_SLIGHT},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(18, 70, 90, 5), //12%, 5%
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_SASSY] =
    {
        .name = COMPOUND_STRING("Sassy"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_SPEED,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_SASSY, AFFINE_TURN_UP_HIGH},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(88, 6, 22, 20), //6%, 58%
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_CAREFUL] =
    {
        .name = COMPOUND_STRING("Careful"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_SPATK,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_CAREFUL, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(42, 50, 42, 5), //8%, 53%
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_QUIRKY] =
    {
        .name = COMPOUND_STRING("Quirky"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_SPDEF,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_QUIRKY, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(56, 22, 56, 22), //22%, 22%
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
};

#include "data/graphics/pokemon.h"

#include "data/pokemon/trainer_class_lookups.h"
#include "data/pokemon/experience_tables.h"

#if P_LVL_UP_LEARNSETS >= GEN_9
#if P_LEGACY_LVL_UP_LEARNSETS
#include "data/pokemon/level_up_learnsets/generated_legacy_level_up_learnsets.h" // Scarlet/Violet with missing USUM moves
#else
#include "data/pokemon/level_up_learnsets/gen_9.h" // Scarlet/Violet
#endif
#elif P_LVL_UP_LEARNSETS >= GEN_8
#include "data/pokemon/level_up_learnsets/gen_8.h" // Sword/Shield
#elif P_LVL_UP_LEARNSETS >= GEN_7
#include "data/pokemon/level_up_learnsets/gen_7.h" // Ultra Sun/Ultra Moon
#elif P_LVL_UP_LEARNSETS >= GEN_6
#include "data/pokemon/level_up_learnsets/gen_6.h" // Omega Ruby/Alpha Sapphire
#elif P_LVL_UP_LEARNSETS >= GEN_5
#include "data/pokemon/level_up_learnsets/gen_5.h" // Black 2/White 2
#elif P_LVL_UP_LEARNSETS >= GEN_4
#include "data/pokemon/level_up_learnsets/gen_4.h" // HeartGold/SoulSilver
#elif P_LVL_UP_LEARNSETS >= GEN_3
#include "data/pokemon/level_up_learnsets/gen_3.h" // Ruby/Sapphire/Emerald
#elif P_LVL_UP_LEARNSETS >= GEN_2
#include "data/pokemon/level_up_learnsets/gen_2.h" // Crystal
#elif P_LVL_UP_LEARNSETS >= GEN_1
#include "data/pokemon/level_up_learnsets/gen_1.h" // Yellow
#endif

#include "data/pokemon/teachable_learnsets.h"
#include "data/pokemon/egg_moves.h"
#include "data/pokemon/form_species_tables.h"
#include "data/pokemon/form_change_tables.h"
#include "data/pokemon/form_change_table_pointers.h"
#include "data/object_events/object_event_pic_tables_followers.h"

#include "data/pokemon/custom_species.h"

#include "data/pokemon/species_info.h"

#define PP_UP_SHIFTS(val)           val,        (val) << 2,        (val) << 4,        (val) << 6
#define PP_UP_SHIFTS_INV(val) (u8)~(val), (u8)~((val) << 2), (u8)~((val) << 4), (u8)~((val) << 6)

// PP Up bonuses are stored for a Pokémon as a single byte.
// There are 2 bits (a value 0-3) for each move slot that
// represent how many PP Ups have been applied.
// The following arrays take a move slot id and return:
// gPPUpGetMask - A mask to get the number of PP Ups applied to that move slot
// gPPUpClearMask - A mask to clear the number of PP Ups applied to that move slot
// gPPUpAddValues - A value to add to the PP Bonuses byte to apply 1 PP Up to that move slot
const u8 gPPUpGetMask[MAX_MON_MOVES]   = {PP_UP_SHIFTS(3)};
const u8 gPPUpClearMask[MAX_MON_MOVES] = {PP_UP_SHIFTS_INV(3)};
const u8 gPPUpAddValues[MAX_MON_MOVES] = {PP_UP_SHIFTS(1)};

const u8 gStatStageRatios[MAX_STAT_STAGE + 1][2] =
{
    {10, 40}, // -6, MIN_STAT_STAGE
    {10, 35}, // -5
    {10, 30}, // -4
    {10, 25}, // -3
    {10, 20}, // -2
    {10, 15}, // -1
    {10, 10}, //  0, DEFAULT_STAT_STAGE
    {15, 10}, // +1
    {20, 10}, // +2
    {25, 10}, // +3
    {30, 10}, // +4
    {35, 10}, // +5
    {40, 10}, // +6, MAX_STAT_STAGE
};

// The classes used by other players in the Union Room.
// These should correspond with the overworld graphics in sUnionRoomObjGfxIds
const u16 gUnionRoomFacilityClasses[NUM_UNION_ROOM_CLASSES * GENDER_COUNT] =
{
    // Male classes
    FACILITY_CLASS_COOLTRAINER_M,
    FACILITY_CLASS_BLACK_BELT,
    FACILITY_CLASS_CAMPER,
    FACILITY_CLASS_YOUNGSTER,
    FACILITY_CLASS_PSYCHIC_M,
    FACILITY_CLASS_BUG_CATCHER,
    FACILITY_CLASS_PKMN_BREEDER_M,
    FACILITY_CLASS_GUITARIST,
    // Female classes
    FACILITY_CLASS_COOLTRAINER_F,
    FACILITY_CLASS_HEX_MANIAC,
    FACILITY_CLASS_PICNICKER,
    FACILITY_CLASS_LASS,
    FACILITY_CLASS_PSYCHIC_F,
    FACILITY_CLASS_BATTLE_GIRL,
    FACILITY_CLASS_PKMN_BREEDER_F,
    FACILITY_CLASS_BEAUTY
};

const struct SpriteTemplate gBattlerSpriteTemplates[MAX_BATTLERS_COUNT] =
{
    [B_POSITION_PLAYER_LEFT] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpritePlayerSide,
        .anims = NULL,
        .images = gBattlerPicTable_PlayerLeft,
        .affineAnims = gAffineAnims_BattleSpritePlayerSide,
        .callback = SpriteCB_BattleSpriteStartSlideLeft,
    },
    [B_POSITION_OPPONENT_LEFT] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpriteOpponentSide,
        .anims = NULL,
        .images = gBattlerPicTable_OpponentLeft,
        .affineAnims = gAffineAnims_BattleSpriteOpponentSide,
        .callback = SpriteCB_WildMon,
    },
    [B_POSITION_PLAYER_RIGHT] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpritePlayerSide,
        .anims = NULL,
        .images = gBattlerPicTable_PlayerRight,
        .affineAnims = gAffineAnims_BattleSpritePlayerSide,
        .callback = SpriteCB_BattleSpriteStartSlideLeft,
    },
    [B_POSITION_OPPONENT_RIGHT] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpriteOpponentSide,
        .anims = NULL,
        .images = gBattlerPicTable_OpponentRight,
        .affineAnims = gAffineAnims_BattleSpriteOpponentSide,
        .callback = SpriteCB_WildMon
    },
};

static const struct SpriteTemplate sTrainerBackSpriteTemplate =
{
    .tileTag = TAG_NONE,
    .paletteTag = 0,
    .oam = &gOamData_BattleSpritePlayerSide,
    .anims = NULL,
    .affineAnims = gAffineAnims_BattleSpritePlayerSide,
    .callback = SpriteCB_BattleSpriteStartSlideLeft,
};

#define NUM_SECRET_BASE_CLASSES 5
static const u8 sSecretBaseFacilityClasses[GENDER_COUNT][NUM_SECRET_BASE_CLASSES] =
{
    [MALE] = {
        FACILITY_CLASS_YOUNGSTER,
        FACILITY_CLASS_BUG_CATCHER,
        FACILITY_CLASS_RICH_BOY,
        FACILITY_CLASS_CAMPER,
        FACILITY_CLASS_COOLTRAINER_M
    },
    [FEMALE] = {
        FACILITY_CLASS_LASS,
        FACILITY_CLASS_SCHOOL_KID_F,
        FACILITY_CLASS_LADY,
        FACILITY_CLASS_PICNICKER,
        FACILITY_CLASS_COOLTRAINER_F
    }
};

static const u8 sGetMonDataEVConstants[] =
{
    MON_DATA_HP_EV,
    MON_DATA_ATK_EV,
    MON_DATA_DEF_EV,
    MON_DATA_SPEED_EV,
    MON_DATA_SPDEF_EV,
    MON_DATA_SPATK_EV
};

static const u8 sGetMonDataIVConstants[] =
{
    MON_DATA_HP_IV,
    MON_DATA_ATK_IV,
    MON_DATA_DEF_IV,
    MON_DATA_SPEED_IV,
    MON_DATA_SPDEF_IV,
    MON_DATA_SPATK_IV
};

static const u8 sGetMonDataIVConstantsByStat[NUM_STATS] =
{
    [STAT_HP] = MON_DATA_HP_IV,
    [STAT_ATK] = MON_DATA_ATK_IV,
    [STAT_DEF] = MON_DATA_DEF_IV,
    [STAT_SPEED] = MON_DATA_SPEED_IV,
    [STAT_SPATK] = MON_DATA_SPATK_IV,
    [STAT_SPDEF] = MON_DATA_SPDEF_IV,
};

// For stat-raising items
static const enum Stat sStatsToRaise[] =
{
    STAT_ATK, STAT_ATK, STAT_DEF, STAT_SPEED, STAT_SPATK, STAT_SPDEF, STAT_ACC
};

// 3 modifiers each for how much to change friendship for different ranges
// 0-99, 100-199, 200+
static const s8 sFriendshipEventModifiers[][3] =
{
    [FRIENDSHIP_EVENT_GROW_LEVEL]      = { 5,  3,  2},
    [FRIENDSHIP_EVENT_VITAMIN]         = { 5,  3,  2},
    [FRIENDSHIP_EVENT_BATTLE_ITEM]     = { 1,  1,  0},
    [FRIENDSHIP_EVENT_LEAGUE_BATTLE]   = { 3,  2,  1},
    [FRIENDSHIP_EVENT_LEARN_TMHM]      = { 1,  1,  0},
    [FRIENDSHIP_EVENT_WALKING]         = { 1,  1,  1},
    [FRIENDSHIP_EVENT_FAINT_SMALL]     = {-1, -1, -1},
    [FRIENDSHIP_EVENT_FAINT_FIELD_PSN] = {-5, -5, -10},
    [FRIENDSHIP_EVENT_FAINT_LARGE]     = {-5, -5, -10},
};

static const struct SpeciesItem sAlteringCaveWildMonHeldItems[] =
{
    {SPECIES_NONE,      ITEM_NONE},
    {SPECIES_MAREEP,    ITEM_GANLON_BERRY},
    {SPECIES_PINECO,    ITEM_APICOT_BERRY},
    {SPECIES_HOUNDOUR,  ITEM_BIG_MUSHROOM},
    {SPECIES_TEDDIURSA, ITEM_PETAYA_BERRY},
    {SPECIES_AIPOM,     ITEM_BERRY_JUICE},
    {SPECIES_SHUCKLE,   ITEM_BERRY_JUICE},
    {SPECIES_STANTLER,  ITEM_PETAYA_BERRY},
    {SPECIES_SMEARGLE,  ITEM_SALAC_BERRY},
};

static const struct OamData sOamData_64x64 =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0
};

static const struct SpriteTemplate sSpriteTemplate_64x64 =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &sOamData_64x64,
};

// NOTE: Reordering this array will break compatibility with existing
// saves.
static const u32 sCompressedStatuses[] =
{
    STATUS1_NONE,
    STATUS1_SLEEP_TURN(1),
    STATUS1_SLEEP_TURN(2),
    STATUS1_SLEEP_TURN(3),
    STATUS1_SLEEP_TURN(4),
    STATUS1_SLEEP_TURN(5),
    STATUS1_POISON,
    STATUS1_BURN,
    STATUS1_FREEZE,
    STATUS1_PARALYSIS,
    STATUS1_TOXIC_POISON,
    STATUS1_FROSTBITE,
};

// Attempt to detect situations where the BoxPokemon struct is unable to
// contain all the values.
// TODO: Is it possible to compute:
// - The maximum experience.
// - The maximum PP.
// - The maximum HP.
// - The maximum form countdown.

// The following STATIC_ASSERT will prevent developers from compiling the game if the value of the constant on the left does not fit within the number of bits defined in PokemonSecureData (currently located in include/pokemon.h).

// To successfully compile, developers will need to do one of the following:
// 1) Decrease the size of the constant.
// 2) Increase the number of bits both on the struct AND in the corresponding assert. This will likely break user's saves unless there is free space after the member that is being adjsted.
// 3) Repurpose unused IDs.

// EXAMPLES
// If a developer has added enough new items so that ITEMS_COUNT now equals 1200, they could...
// 1) remove new items until ITEMS_COUNT is 1023, the max value that will fit in 10 bits.
// 2) change heldItem:10 to heldItem:11 AND change the below assert for ITEMS_COUNT to check for (1 << 11).
// 3) repurpose IDs from other items that aren't being used, like ITEM_GOLD_TEETH or ITEM_SS_TICKET until ITEMS_COUNT equals 1023, the max value that will fit in 10 bits.

STATIC_ASSERT(NUM_SPECIES < (1 << 11), PokemonSecureData_species_TooSmall);
STATIC_ASSERT(NUMBER_OF_MON_TYPES + 1 <= (1 << 5), PokemonSecureData_teraType_TooSmall);
STATIC_ASSERT(ITEMS_COUNT < (1 << 10), PokemonSecureData_heldItem_TooSmall);
STATIC_ASSERT(MAX_LEVEL <= 150, PokemonSecureData_experience_PotentiallyTooSmall); // Maximum of ~16 million exp.
STATIC_ASSERT(POKEBALL_COUNT <= (1 << 6), PokemonSecureData_pokeball_TooSmall);
STATIC_ASSERT(MOVES_COUNT_ALL < (1 << 11), PokemonSecureData_moves_TooSmall);
STATIC_ASSERT(ARRAY_COUNT(sCompressedStatuses) <= (1 << 4), PokemonSecureData_compressedStatus_TooSmall);
STATIC_ASSERT(MAX_LEVEL < (1 << 7), PokemonSecureData_metLevel_TooSmall);
STATIC_ASSERT(NUM_VERSIONS < (1 << 4), PokemonSecureData_metGame_TooSmall);
STATIC_ASSERT(MAX_PER_STAT_IVS < (1 << 5), PokemonSecureData_ivs_TooSmall);
STATIC_ASSERT(MAPSEC_COUNT <= (1 << 15), PokemonSecureData_metLocationHi_TooSmall);
STATIC_ASSERT(sizeof(struct PokemonSecureData) % sizeof(u16) == 0, PokemonSecureData_SizeNotHalfwordAligned);
STATIC_ASSERT(NUM_NATURES <= (1 << 5), BoxPokemon_hiddenNatureModifier_TooSmall);

static u32 CompressStatus(u32 status)
{
    s32 i;
    for (i = 0; i < ARRAY_COUNT(sCompressedStatuses); i++)
    {
        if (sCompressedStatuses[i] == status)
            return i;
    }
    return 0; // STATUS1_NONE
}

static u32 UncompressStatus(u32 compressedStatus)
{
    if (compressedStatus < ARRAY_COUNT(sCompressedStatuses))
        return sCompressedStatuses[compressedStatus];
    else
        return STATUS1_NONE;
}

void ZeroBoxMonData(struct BoxPokemon *boxMon)
{
    u8 *raw = (u8 *)boxMon;
    u32 i;
    for (i = 0; i < sizeof(struct BoxPokemon); i++)
        raw[i] = 0;
}

void ZeroMonData(struct Pokemon *mon)
{
    u32 arg;
    ZeroBoxMonData(&mon->box);
    arg = 0;
    SetMonData(mon, MON_DATA_STATUS, &arg);
    SetMonData(mon, MON_DATA_LEVEL, &arg);
    SetMonData(mon, MON_DATA_HP, &arg);
    SetMonData(mon, MON_DATA_MAX_HP, &arg);
    SetMonData(mon, MON_DATA_ATK, &arg);
    SetMonData(mon, MON_DATA_DEF, &arg);
    SetMonData(mon, MON_DATA_SPEED, &arg);
    SetMonData(mon, MON_DATA_SPATK, &arg);
    SetMonData(mon, MON_DATA_SPDEF, &arg);
    arg = MAIL_NONE;
    SetMonData(mon, MON_DATA_MAIL, &arg);
}

void ZeroPlayerPartyMons(void)
{
    s32 i;
    for (i = 0; i < PARTY_SIZE; i++)
        ZeroMonData(&gPlayerParty[i]);
}

void ZeroEnemyPartyMons(void)
{
    s32 i;
    for (i = 0; i < PARTY_SIZE; i++)
        ZeroMonData(&gEnemyParty[i]);
}

void CreateRandomMon(struct Pokemon *mon, u16 species, u8 level)
{
    CreateRandomMonWithIVs(mon, species, level, USE_RANDOM_IVS);
}

void CreateRandomMonWithIVs(struct Pokemon *mon, u16 species, u8 level, u8 fixedIv)
{
    CreateMonWithIVs(mon, species, level, Random32(), OTID_STRUCT_PLAYER_ID, fixedIv);
    GiveMonInitialMoveset(mon);
}

void CreateMon(struct Pokemon *mon, u16 species, u8 level, u32 personality, struct OriginalTrainerId trainerId)
{
    u32 mail;
    ZeroMonData(mon);
    CreateBoxMon(&mon->box, species, level, personality, trainerId);
    SetMonData(mon, MON_DATA_LEVEL, &level);
    mail = MAIL_NONE;
    SetMonData(mon, MON_DATA_MAIL, &mail);
}

u32 GetCurrentShinyOdds(void)
{
    if (FlagGet(FLAG_RELEASE_SHINY_ODDS))
        return RELEASE_SHINY_ODDS;

    return SHINY_ODDS;
}

enum ShinyRateOption GetShinyRateOption(void)
{
    u32 selection = VarGet(VAR_SHINY_RATE);
    return selection >= SHINY_RATE_256 && selection < SHINY_RATE_COUNT ? selection : SHINY_RATE_256;
}

u32 GetShinyGenerationOdds(void)
{
    switch (GetShinyRateOption())
    {
    case SHINY_RATE_256: return 256;
    case SHINY_RATE_512: return 128;
    case SHINY_RATE_1024: return 64;
    default: return 256;
    }
}

u32 GetTradeShinyGenerationOdds(void)
{
    return 12 * GetShinyGenerationOdds();
}

void CreateMonWithIVs(struct Pokemon *mon, u16 species, u8 level, u32 personality, struct OriginalTrainerId trainerId, u8 fixedIV)
{
    CreateMon(mon, species, level, personality, trainerId);
    SetBoxMonIVs(&mon->box, fixedIV);
    CalculateMonStats(mon);
}

void CreateMonLegacy(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 hasFixedPersonality, u32 fixedPersonality, u8 otIdType, u32 fixedOtId)
{
    u32 personality = hasFixedPersonality ? fixedPersonality : Random32();
    struct OriginalTrainerId otId = {otIdType, fixedOtId};
    CreateMonWithIVs(mon, species, level, personality, otId, fixedIV);
    GiveMonInitialMoveset(mon);
}

void CreateBoxMonLegacy(struct BoxPokemon *boxMon, u16 species, u8 level, u8 fixedIV, u8 hasFixedPersonality, u32 fixedPersonality, u8 otIdType, u32 fixedOtId)
{
    u32 personality = hasFixedPersonality ? fixedPersonality : Random32();
    struct OriginalTrainerId otId = {otIdType, fixedOtId};
    CreateBoxMon(boxMon, species, level, personality, otId);
    SetBoxMonIVs(boxMon, fixedIV);
    GiveBoxMonInitialMoveset(boxMon);
}

void SetBoxMonIVs(struct BoxPokemon *mon, u8 fixedIV)
{
    u32 i, value;
    enum Stat availableIVs[NUM_STATS];
    enum Stat selectedIvs[NUM_STATS];

    if (fixedIV < USE_RANDOM_IVS)
    {
        for (i = 0; i < NUM_STATS; i++)
            SetBoxMonData(mon, MON_DATA_HP_IV + i, &fixedIV);
        return;
    }

    u32 iv;
    u32 ivRandom = Random32();
    u32 species = GetBoxMonData(mon, MON_DATA_SPECIES);
    value = (u16)ivRandom;

    iv = value & MAX_IV_MASK;
    SetBoxMonData(mon, MON_DATA_HP_IV, &iv);
    iv = (value & (MAX_IV_MASK << 5)) >> 5;
    SetBoxMonData(mon, MON_DATA_ATK_IV, &iv);
    iv = (value & (MAX_IV_MASK << 10)) >> 10;
    SetBoxMonData(mon, MON_DATA_DEF_IV, &iv);

    value = (u16)(ivRandom >> 16);

    iv = value & MAX_IV_MASK;
    SetBoxMonData(mon, MON_DATA_SPEED_IV, &iv);
    iv = (value & (MAX_IV_MASK << 5)) >> 5;
    SetBoxMonData(mon, MON_DATA_SPATK_IV, &iv);
    iv = (value & (MAX_IV_MASK << 10)) >> 10;
    SetBoxMonData(mon, MON_DATA_SPDEF_IV, &iv);

    if (gSpeciesInfo[species].perfectIVCount != 0)
    {
        iv = MAX_PER_STAT_IVS;
        // Initialize a list of IV indices.
        for (i = 0; i < NUM_STATS; i++)
            availableIVs[i] = i;

        // Select the IVs that will be perfected.
        for (i = 0; i < NUM_STATS && i < gSpeciesInfo[species].perfectIVCount; i++)
        {
            u8 index = Random() % (NUM_STATS - i);
            selectedIvs[i] = availableIVs[index];
            RemoveIVIndexFromList(availableIVs, index);
            SetBoxMonData(mon, MON_DATA_HP_IV + selectedIvs[i], &iv);
        }
    }
}

void CreateBoxMon(struct BoxPokemon *boxMon, u16 species, u8 level, u32 personality, struct OriginalTrainerId trainerId)
{
    u8 speciesName[POKEMON_NAME_LENGTH + 1];
    u32 value;
    u32 shinyOdds = GetShinyGenerationOdds();
    bool32 isShiny;

    ZeroBoxMonData(boxMon);
    // Determine original trainer ID
    if (trainerId.method == OT_ID_RANDOM_NO_SHINY)
    {
        value = Random32();
        isShiny = FALSE;
    }
    else if (trainerId.method == OT_ID_PRESET)
    {
        value = trainerId.value;
        isShiny = GET_SHINY_VALUE(value, personality) < shinyOdds;
    }
    else // Player is the OT
    {
        value = READ_OTID_FROM_SAVE;
        if (P_FLAG_FORCE_NO_SHINY != 0 && FlagGet(P_FLAG_FORCE_NO_SHINY))
        {
            isShiny = FALSE;
        }
        else if (P_FLAG_FORCE_SHINY != 0 && FlagGet(P_FLAG_FORCE_SHINY))
        {
            isShiny = TRUE;
        }
        else if (P_ONLY_OBTAINABLE_SHINIES && (CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE || (B_FLAG_NO_CATCHING != 0 && FlagGet(B_FLAG_NO_CATCHING))))
        {
            isShiny = FALSE;
        }
        else if (P_NO_SHINIES_WITHOUT_POKEBALLS && !HasAtLeastOnePokeBall())
        {
            isShiny = FALSE;
        }
        else
        {
            u32 totalRerolls = 0;
            if (CheckBagHasItem(ITEM_SHINY_CHARM, 1))
                totalRerolls += I_SHINY_CHARM_ADDITIONAL_ROLLS;
            if (LURE_STEP_COUNT != 0)
                totalRerolls += 1;
            totalRerolls += CalculateChainFishingShinyRolls();
            if (gDexNavSpecies)
                totalRerolls += CalculateDexNavShinyRolls();

            u32 shinyPersonality = personality;
            while (GET_SHINY_VALUE(value, shinyPersonality) >= shinyOdds && totalRerolls > 0)
            {
                shinyPersonality = Random32();
                totalRerolls--;
            }

            isShiny = GET_SHINY_VALUE(value, shinyPersonality) < shinyOdds;
        }
    }

    SetBoxMonData(boxMon, MON_DATA_PERSONALITY, &personality);
    SetBoxMonData(boxMon, MON_DATA_OT_ID, &value);

    SetBoxMonData(boxMon, MON_DATA_IS_SHINY, &isShiny);
    StringCopy(speciesName, GetSpeciesName(species));
    SetBoxMonData(boxMon, MON_DATA_NICKNAME, speciesName);
    SetBoxMonData(boxMon, MON_DATA_LANGUAGE, &gGameLanguage);
    SetBoxMonData(boxMon, MON_DATA_OT_NAME, gSaveBlock2Ptr->playerName);
    SetBoxMonData(boxMon, MON_DATA_SPECIES, &species);
    SetBoxMonData(boxMon, MON_DATA_EXP, &gExperienceTables[gSpeciesInfo[species].growthRate][level]);
    SetBoxMonData(boxMon, MON_DATA_FRIENDSHIP, &gSpeciesInfo[species].friendship);
    value = GetCurrentRegionMapSectionId();
    SetBoxMonData(boxMon, MON_DATA_MET_LOCATION, &value);
    SetBoxMonData(boxMon, MON_DATA_MET_LEVEL, &level);
    SetBoxMonData(boxMon, MON_DATA_MET_GAME, &gGameVersion);
    value = ITEM_POKE_BALL;
    SetBoxMonData(boxMon, MON_DATA_POKEBALL, &value);
    SetBoxMonData(boxMon, MON_DATA_OT_GENDER, &gSaveBlock2Ptr->playerGender);

    value = boxMon->personality & 0x1;
    u32 teraType = value == 0 ? GetSpeciesType(species, 0) : GetSpeciesType(species, 1);
    SetBoxMonData(boxMon, MON_DATA_TERA_TYPE, &teraType);
    //using gen 3-4 ability formula, it was changed in later gens
    if (GetSpeciesAbility(species, 1))
        SetBoxMonData(boxMon, MON_DATA_ABILITY_NUM, &value);
}

static bool32 IsValidGender(u32 gender)
{
    switch (gender)
    {
    case MON_MALE:
    case MON_FEMALE:
    case MON_GENDERLESS:
    case MON_GENDER_RANDOM:
        return TRUE;
    default:
        return FALSE;
    }
}

u32 GetMonPersonality(u16 species, u8 gender, u8 nature, u8 unownLetter)
{
    u32 personality, actualLetter;

    assertf(IsValidGender(gender), "invalid gender: %d", gender)
    {
        gender = MON_GENDER_RANDOM;
    }

    assertf(nature <= NATURE_RANDOM, "invalid nature: %d", nature)
    {
        nature = NATURE_RANDOM;
    }

    assertf(unownLetter <= NUM_UNOWN_FORMS, "invalid letter: %d", unownLetter)
    {
        unownLetter = RANDOM_UNOWN_LETTER;
    }

    //gender outside valid gender ratios for species is not asserted because it could be triggered by cute charm
    do
    {
        personality = Random32();
        actualLetter = GET_UNOWN_LETTER(personality);
    }
    while ((nature != GetNatureFromPersonality(personality) && nature != NATURE_RANDOM)
            || (gender != GetGenderFromSpeciesAndPersonality(species, personality) && gender != MON_GENDER_RANDOM)
            || ((actualLetter != unownLetter - 1) && unownLetter > 0));
    return personality;
}

// This is only used to create Wally's Ralts.
void CreateMaleMon(struct Pokemon *mon, u16 species, u8 level)
{
    u32 personality = GetMonPersonality(species, MON_MALE, NATURE_RANDOM, RANDOM_UNOWN_LETTER);
    CreateMonWithIVs(mon, species, level, personality, OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    GiveMonInitialMoveset(mon);
}

void CreateMonWithIVsPersonality(struct Pokemon *mon, u16 species, u8 level, u32 ivs, u32 personality)
{
    CreateMon(mon, species, level, personality, OTID_STRUCT_PLAYER_ID);
    SetMonData(mon, MON_DATA_IVS, &ivs);
    CalculateMonStats(mon);
    GiveMonInitialMoveset(mon);
}

void CreateBattleTowerMon(struct Pokemon *mon, struct BattleTowerPokemon *src)
{
    s32 i;
    u8 nickname[max(32, POKEMON_NAME_BUFFER_SIZE)];
    enum Language language;
    u8 value;

    CreateMon(mon, src->species, src->level, src->personality, OTID_STRUCT_PRESET(src->otId));

    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(mon, src->moves[i], i);

    SetMonData(mon, MON_DATA_PP_BONUSES, &src->ppBonuses);
    for (i = 0; i < MAX_MON_ITEMS; i++)
        SetMonData(mon, MON_DATA_HELD_ITEM + i, &src->heldItem[i]);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &src->friendship);

    StringCopy(nickname, src->nickname);

    if (nickname[0] == EXT_CTRL_CODE_BEGIN && nickname[1] == EXT_CTRL_CODE_JPN)
    {
        language = LANGUAGE_JAPANESE;
        StripExtCtrlCodes(nickname);
    }
    else
    {
        language = GAME_LANGUAGE;
    }

    SetMonData(mon, MON_DATA_LANGUAGE, &language);
    SetMonData(mon, MON_DATA_NICKNAME, nickname);
    SetMonData(mon, MON_DATA_HP_EV, &src->hpEV);
    SetMonData(mon, MON_DATA_ATK_EV, &src->attackEV);
    SetMonData(mon, MON_DATA_DEF_EV, &src->defenseEV);
    SetMonData(mon, MON_DATA_SPEED_EV, &src->speedEV);
    SetMonData(mon, MON_DATA_SPATK_EV, &src->spAttackEV);
    SetMonData(mon, MON_DATA_SPDEF_EV, &src->spDefenseEV);
    value = src->abilityNum;
    SetMonData(mon, MON_DATA_ABILITY_NUM, &value);
    value = src->hpIV;
    SetMonData(mon, MON_DATA_HP_IV, &value);
    value = src->attackIV;
    SetMonData(mon, MON_DATA_ATK_IV, &value);
    value = src->defenseIV;
    SetMonData(mon, MON_DATA_DEF_IV, &value);
    value = src->speedIV;
    SetMonData(mon, MON_DATA_SPEED_IV, &value);
    value = src->spAttackIV;
    SetMonData(mon, MON_DATA_SPATK_IV, &value);
    value = src->spDefenseIV;
    SetMonData(mon, MON_DATA_SPDEF_IV, &value);
    MonRestorePP(mon);
    CalculateMonStats(mon);
}

void CreateBattleTowerMon_HandleLevel(struct Pokemon *mon, struct BattleTowerPokemon *src, bool8 lvl50)
{
    s32 i;
    u8 nickname[max(32, POKEMON_NAME_BUFFER_SIZE)];
    u8 level;
    enum Language language;
    u8 value;

    if (gSaveBlock2Ptr->frontier.lvlMode != FRONTIER_LVL_50)
        level = GetFrontierEnemyMonLevel(gSaveBlock2Ptr->frontier.lvlMode);
    else if (lvl50)
        level = FRONTIER_MAX_LEVEL_50;
    else
        level = src->level;

    CreateMon(mon, src->species, level, src->personality, OTID_STRUCT_PRESET(src->otId));

    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(mon, src->moves[i], i);

    SetMonData(mon, MON_DATA_PP_BONUSES, &src->ppBonuses);
    for (i = 0; i < MAX_MON_ITEMS; i++)
        SetMonData(mon, MON_DATA_HELD_ITEM + i, &src->heldItem[i]);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &src->friendship);

    StringCopy(nickname, src->nickname);

    if (nickname[0] == EXT_CTRL_CODE_BEGIN && nickname[1] == EXT_CTRL_CODE_JPN)
    {
        language = LANGUAGE_JAPANESE;
        StripExtCtrlCodes(nickname);
    }
    else
    {
        language = GAME_LANGUAGE;
    }

    SetMonData(mon, MON_DATA_LANGUAGE, &language);
    SetMonData(mon, MON_DATA_NICKNAME, nickname);
    SetMonData(mon, MON_DATA_HP_EV, &src->hpEV);
    SetMonData(mon, MON_DATA_ATK_EV, &src->attackEV);
    SetMonData(mon, MON_DATA_DEF_EV, &src->defenseEV);
    SetMonData(mon, MON_DATA_SPEED_EV, &src->speedEV);
    SetMonData(mon, MON_DATA_SPATK_EV, &src->spAttackEV);
    SetMonData(mon, MON_DATA_SPDEF_EV, &src->spDefenseEV);
    value = src->abilityNum;
    SetMonData(mon, MON_DATA_ABILITY_NUM, &value);
    value = src->hpIV;
    SetMonData(mon, MON_DATA_HP_IV, &value);
    value = src->attackIV;
    SetMonData(mon, MON_DATA_ATK_IV, &value);
    value = src->defenseIV;
    SetMonData(mon, MON_DATA_DEF_IV, &value);
    value = src->speedIV;
    SetMonData(mon, MON_DATA_SPEED_IV, &value);
    value = src->spAttackIV;
    SetMonData(mon, MON_DATA_SPATK_IV, &value);
    value = src->spDefenseIV;
    SetMonData(mon, MON_DATA_SPDEF_IV, &value);
    MonRestorePP(mon);
    CalculateMonStats(mon);
}

void CreateApprenticeMon(struct Pokemon *mon, const struct Apprentice *src, u8 monId)
{
    s32 i;
    u16 evAmount;
    u8 language;
    u32 otId = gApprentices[src->id].otId;
    u32 personality = ((gApprentices[src->id].otId >> 8) | ((gApprentices[src->id].otId & 0xFF) << 8))
                    + src->party[monId].species + src->number;

    CreateMonWithIVs(mon,
              src->party[monId].species,
              GetFrontierEnemyMonLevel(src->lvlMode - 1),
              personality,
              OTID_STRUCT_PRESET(otId),
              MAX_PER_STAT_IVS);
    for (i = 0; i < MAX_MON_ITEMS; i++)
        SetMonData(mon, MON_DATA_HELD_ITEM + i, &src->party[monId].item[i]);
    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(mon, src->party[monId].moves[i], i);

    evAmount = MAX_TOTAL_EVS / NUM_STATS;
    for (i = 0; i < NUM_STATS; i++)
        SetMonData(mon, MON_DATA_HP_EV + i, &evAmount);

    language = src->language;
    SetMonData(mon, MON_DATA_LANGUAGE, &language);
    SetMonData(mon, MON_DATA_OT_NAME, GetApprenticeNameInLanguage(src->id, language));
    CalculateMonStats(mon);
}

void ConvertPokemonToBattleTowerPokemon(struct Pokemon *mon, struct BattleTowerPokemon *dest)
{
    s32 i;
    u16 heldItem[MAX_MON_ITEMS_INTERNAL];

    dest->species = GetMonData(mon, MON_DATA_SPECIES);
    
    for (i = 0; i < MAX_MON_ITEMS; i++)
    {
        heldItem[i] = GetMonData(mon, MON_DATA_HELD_ITEM + i);

        if (heldItem[i] == ITEM_ENIGMA_BERRY_E_READER)
            heldItem[i] = ITEM_NONE;

        dest->heldItem[i] = heldItem[i];
    }

    for (i = 0; i < MAX_MON_MOVES; i++)
        dest->moves[i] = GetMonData(mon, MON_DATA_MOVE1 + i);

    dest->level = GetMonData(mon, MON_DATA_LEVEL);
    dest->ppBonuses = GetMonData(mon, MON_DATA_PP_BONUSES);
    dest->otId = GetMonData(mon, MON_DATA_OT_ID);
    dest->hpEV = GetMonData(mon, MON_DATA_HP_EV);
    dest->attackEV = GetMonData(mon, MON_DATA_ATK_EV);
    dest->defenseEV = GetMonData(mon, MON_DATA_DEF_EV);
    dest->speedEV = GetMonData(mon, MON_DATA_SPEED_EV);
    dest->spAttackEV = GetMonData(mon, MON_DATA_SPATK_EV);
    dest->spDefenseEV = GetMonData(mon, MON_DATA_SPDEF_EV);
    dest->friendship = GetMonData(mon, MON_DATA_FRIENDSHIP);
    dest->hpIV = GetMonData(mon, MON_DATA_HP_IV);
    dest->attackIV = GetMonData(mon, MON_DATA_ATK_IV);
    dest->defenseIV = GetMonData(mon, MON_DATA_DEF_IV);
    dest->speedIV  = GetMonData(mon, MON_DATA_SPEED_IV);
    dest->spAttackIV  = GetMonData(mon, MON_DATA_SPATK_IV);
    dest->spDefenseIV  = GetMonData(mon, MON_DATA_SPDEF_IV);
    dest->abilityNum = GetMonData(mon, MON_DATA_ABILITY_NUM);
    dest->personality = GetMonData(mon, MON_DATA_PERSONALITY);
    GetMonData(mon, MON_DATA_NICKNAME10, dest->nickname);
}

static void CreateEventMon(struct Pokemon *mon, u16 species, u8 level, u32 personality, struct OriginalTrainerId otId)
{
    bool32 isModernFatefulEncounter = TRUE;

    CreateMonWithIVs(mon, species, level, personality, otId, USE_RANDOM_IVS);
    GiveMonInitialMoveset(mon);
    SetMonData(mon, MON_DATA_MODERN_FATEFUL_ENCOUNTER, &isModernFatefulEncounter);
    CalculateMonStats(mon);
}

enum TrainerPicID GetUnionRoomTrainerPic(void)
{
    u8 linkId;
    u32 arrId;

    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
        linkId = gRecordedBattleMultiplayerId ^ 1;
    else
        linkId = GetMultiplayerId() ^ 1;

    arrId = gLinkPlayers[linkId].trainerId % NUM_UNION_ROOM_CLASSES;
    arrId |= gLinkPlayers[linkId].gender * NUM_UNION_ROOM_CLASSES;
    return FacilityClassToPicIndex(gUnionRoomFacilityClasses[arrId]);
}

enum TrainerClassID GetUnionRoomTrainerClass(void)
{
    u8 linkId;
    u32 arrId;

    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
        linkId = gRecordedBattleMultiplayerId ^ 1;
    else
        linkId = GetMultiplayerId() ^ 1;

    arrId = gLinkPlayers[linkId].trainerId % NUM_UNION_ROOM_CLASSES;
    arrId |= gLinkPlayers[linkId].gender * NUM_UNION_ROOM_CLASSES;
    return gFacilityClassToTrainerClass[gUnionRoomFacilityClasses[arrId]];
}

void CreateEnemyEventMon(void)
{
    s32 species = gSpecialVar_0x8004;
    s32 level = gSpecialVar_0x8005;
    s32 itemId = gSpecialVar_0x8006;
    u16 slot;

    ZeroEnemyPartyMons();

    CreateEventMon(&gEnemyParty[0], species, level, Random32(), OTID_STRUCT_PLAYER_ID);
    if (itemId)
    {
        u8 heldItem[2];
        heldItem[0] = itemId;
        heldItem[1] = itemId >> 8;

        slot = GetMonNextEmptySlot(&gEnemyParty[0], itemId);
        
        if (slot != MAX_MON_ITEMS)
            SetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM + slot, heldItem);  //leaving as one item to not mess with the specialVar (Multi)
    }
}

void CalculateMonStats(struct Pokemon *mon)
{
    s32 oldMaxHP = GetMonData(mon, MON_DATA_MAX_HP);
    s32 currentHP = GetMonData(mon, MON_DATA_HP);
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u8 friendship = GetMonData(mon, MON_DATA_FRIENDSHIP);
    s32 level = GetLevelFromMonExp(mon);
    s32 newMaxHP;

    u8 nature = GetMonData(mon, MON_DATA_HIDDEN_NATURE);

    SetMonData(mon, MON_DATA_LEVEL, &level);

    bool32 hyperTrained[NUM_STATS]; //In a battle test, hyper training flag indicates a fixed stat
    s32 iv[NUM_STATS];
    s32 ev[NUM_STATS];
    for (u32 i = 0; i < NUM_STATS; i++)
    {
        hyperTrained[i] = GetMonData(mon, MON_DATA_HYPER_TRAINED_HP + i);
        iv[i] = GetMonData(mon, MON_DATA_HP_IV + i);
        ev[i] = GetMonData(mon, MON_DATA_HP_EV + i);

        if (hyperTrained[i])
        {
        #if TESTING
            if (gMain.inBattle)
                continue;
        #endif
            iv[i] = MAX_PER_STAT_IVS;
        }

        if (i == STAT_HP)
            continue;

        u8 baseStat = GetSpeciesBaseStat(species, i);
        s32 n = (((2 * baseStat + iv[i] + ev[i] / 4) * level) / 100) + 5;
        n = ModifyStatByNature(nature, n, i);
        if (B_FRIENDSHIP_BOOST == TRUE)
            n = n + ((n * 10 * friendship) / (MAX_FRIENDSHIP * 100));
        SetMonData(mon, MON_DATA_MAX_HP + i, &n);
    }

#if TESTING
    if (hyperTrained[STAT_HP] && gMain.inBattle)
        return;
#endif

    if (species == SPECIES_SHEDINJA)
    {
        newMaxHP = 1;
    }
    else
    {
        s32 n = 2 * GetSpeciesBaseHP(species) + iv[STAT_HP];
        newMaxHP = (((n + ev[STAT_HP] / 4) * level) / 100) + level + 10;
    }

    gBattleScripting.levelUpHP = newMaxHP - oldMaxHP;
    if (gBattleScripting.levelUpHP == 0)
        gBattleScripting.levelUpHP = 1;
    SetMonData(mon, MON_DATA_MAX_HP, &newMaxHP);

    // Since a pokemon's maxHP data could either not have
    // been initialized at this point or this pokemon is
    // just fainted, the check for oldMaxHP is important.
    if (currentHP == 0 && oldMaxHP != 0)
        return;

    // Only add to currentHP if newMaxHP went up.
    if (newMaxHP > oldMaxHP)
        currentHP += newMaxHP - oldMaxHP;

    // Ensure currentHP does not surpass newMaxHP.
    if (currentHP > newMaxHP)
        currentHP = newMaxHP;

    SetMonData(mon, MON_DATA_HP, &currentHP);
}

void BoxMonToMon(const struct BoxPokemon *src, struct Pokemon *dest)
{
    u32 value = 0;
    dest->box = *src;
    dest->status = GetBoxMonData(&dest->box, MON_DATA_STATUS);
    dest->hp = 0;
    dest->maxHP = 0;
    value = MAIL_NONE;
    SetMonData(dest, MON_DATA_MAIL, &value);
    value = GetBoxMonData(&dest->box, MON_DATA_HP_LOST);
    CalculateMonStats(dest);
    value = GetMonData(dest, MON_DATA_MAX_HP) - value;
    SetMonData(dest, MON_DATA_HP, &value);
}

u8 GetLevelFromMonExp(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u32 exp = GetMonData(mon, MON_DATA_EXP);
    s32 level = 1;

    while (level <= MAX_LEVEL && gExperienceTables[gSpeciesInfo[species].growthRate][level] <= exp)
        level++;

    return level - 1;
}

u8 GetLevelFromBoxMonExp(struct BoxPokemon *boxMon)
{
    u16 species = GetBoxMonData(boxMon, MON_DATA_SPECIES);
    u32 exp = GetBoxMonData(boxMon, MON_DATA_EXP);
    s32 level = 1;

    while (level <= MAX_LEVEL && gExperienceTables[gSpeciesInfo[species].growthRate][level] <= exp)
        level++;

    return level - 1;
}

u16 GiveMoveToMon(struct Pokemon *mon, enum Move move)
{
    return GiveMoveToBoxMon(&mon->box, move);
}

u16 GiveMoveToBoxMon(struct BoxPokemon *boxMon, enum Move move)
{
    s32 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        enum Move existingMove = GetBoxMonData(boxMon, MON_DATA_MOVE1 + i);
        if (existingMove == MOVE_NONE)
        {
            u32 pp = GetMovePP(move);
            SetBoxMonData(boxMon, MON_DATA_MOVE1 + i, &move);
            SetBoxMonData(boxMon, MON_DATA_PP1 + i, &pp);
            return move;
        }
        if (existingMove == move)
            return MON_ALREADY_KNOWS_MOVE;
    }
    return MON_HAS_MAX_MOVES;
}

u16 GiveMoveToBattleMon(struct BattlePokemon *mon, enum Move move)
{
    s32 i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (mon->moves[i] == MOVE_NONE)
        {
            mon->moves[i] = move;
            mon->pp[i] = GetMovePP(move);
            return move;
        }
    }

    return MON_HAS_MAX_MOVES;
}

void SetMonMoveSlot(struct Pokemon *mon, enum Move move, u8 slot)
{
    SetBoxMonMoveSlot(&mon->box, move, slot);
}

void SetBoxMonMoveSlot(struct BoxPokemon *mon, enum Move move, u8 slot)
{
    SetBoxMonData(mon, MON_DATA_MOVE1 + slot, &move);
    u32 pp = GetMovePP(move);
    SetBoxMonData(mon, MON_DATA_PP1 + slot, &pp);
}

static void SetBoxMonMoveSlot_KeepPP(struct BoxPokemon *boxMon, enum Move move, u8 slot)
{
    u8 ppBonuses = GetBoxMonData(boxMon, MON_DATA_PP_BONUSES);
    u8 currPP = GetBoxMonData(boxMon, MON_DATA_PP1 + slot);
    u8 newPP = CalculatePPWithBonus(move, ppBonuses, slot);
    u8 finalPP = min(currPP, newPP);

    SetBoxMonData(boxMon, MON_DATA_MOVE1 + slot, &move);
    SetBoxMonData(boxMon, MON_DATA_PP1 + slot, &finalPP);
}

void SetBattleMonMoveSlot(struct BattlePokemon *mon, enum Move move, u8 slot)
{
    mon->moves[slot] = move;
    mon->pp[slot] = GetMovePP(move);
}

void GiveMonInitialMoveset(struct Pokemon *mon)
{
    GiveBoxMonInitialMoveset(&mon->box);
}

void GiveBoxMonInitialMoveset(struct BoxPokemon *boxMon) //Credit: AsparagusEduardo
{
    u16 species = GetBoxMonData(boxMon, MON_DATA_SPECIES);
    s32 level = GetLevelFromBoxMonExp(boxMon);
    s32 i;
    enum Move moves[MAX_MON_MOVES] = {MOVE_NONE};
    u8 addedMoves = 0;
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);

    for (i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        s32 j;
        bool32 alreadyKnown = FALSE;

        if (learnset[i].level > level)
            break;
        if (learnset[i].level == 0)
            continue;

        for (j = 0; j < addedMoves; j++)
      …35991 tokens truncated…>numFrames];
    }
}

static void InitMonSpritesGfx_FullParty(struct MonSpritesGfxManager *gfx)
{
    u16 i, j;
    for (i = 0; i < gfx->numSprites; i++)
    {
        gfx->templates[i] = sSpriteTemplate_64x64;
        for (j = 0; j < gfx->numFrames; j++)
            gfx->frameImages[i * gfx->numSprites + j].data = &gfx->spritePointers[i][j * MON_PIC_SIZE];

        gfx->templates[i].images = &gfx->frameImages[i * gfx->numSprites];
        gfx->templates[i].anims = gAnims_MonPic;
        gfx->templates[i].paletteTag = i;
    }
}

struct MonSpritesGfxManager *CreateMonSpritesGfxManager(u8 managerId, u8 mode)
{
    u8 i;
    u8 failureFlags;
    struct MonSpritesGfxManager *gfx;

    failureFlags = 0;
    managerId %= MON_SPR_GFX_MANAGERS_COUNT;
    // Mont note: If the manager is already active, return it to allow for reliable transitions between summary screen
    // and swsh party menu which also uses animated mon sprite
    if (sMonSpritesGfxManagers[managerId] != NULL && sMonSpritesGfxManagers[managerId]->active == GFX_MANAGER_ACTIVE)
        return sMonSpritesGfxManagers[managerId];
    gfx = AllocZeroed(sizeof(*gfx));
    if (gfx == NULL)
        return NULL;

    switch (mode)
    {
    case MON_SPR_GFX_MODE_FULL_PARTY:
        gfx->numSprites = PARTY_SIZE + 1;
        gfx->numSprites2 = PARTY_SIZE + 1;
        gfx->numFrames = MAX_MON_PIC_FRAMES;
        gfx->dataSize = 1;
        gfx->mode = MON_SPR_GFX_MODE_FULL_PARTY;
        break;
 // case MON_SPR_GFX_MODE_BATTLE:
    case MON_SPR_GFX_MODE_NORMAL:
    default:
        gfx->numSprites = MAX_BATTLERS_COUNT;
        gfx->numSprites2 = MAX_BATTLERS_COUNT;
        gfx->numFrames = MAX_MON_PIC_FRAMES;
        gfx->dataSize = 1;
        gfx->mode = MON_SPR_GFX_MODE_NORMAL;
        break;
    }

    // Set up sprite / sprite pointer buffers
    gfx->spriteBuffer = AllocZeroed(gfx->dataSize * MON_PIC_SIZE * MAX_MON_PIC_FRAMES * gfx->numSprites);
    gfx->spritePointers = AllocZeroed(gfx->numSprites * 32); // ? Only * 4 is necessary, perhaps they were thinking bits.
    if (gfx->spriteBuffer == NULL || gfx->spritePointers == NULL)
    {
        failureFlags |= ALLOC_FAIL_BUFFER;
    }
    else
    {
        for (i = 0; i < gfx->numSprites; i++)
            gfx->spritePointers[i] = gfx->spriteBuffer + (gfx->dataSize * MON_PIC_SIZE * MAX_MON_PIC_FRAMES * i);
    }

    // Set up sprite structs
    gfx->templates = AllocZeroed(sizeof(struct SpriteTemplate) * gfx->numSprites);
    gfx->frameImages = AllocZeroed(sizeof(struct SpriteFrameImage) * gfx->numSprites * gfx->numFrames);
    if (gfx->templates == NULL || gfx->frameImages == NULL)
    {
        failureFlags |= ALLOC_FAIL_STRUCT;
    }
    else
    {
        for (i = 0; i < gfx->numFrames * gfx->numSprites; i++)
            gfx->frameImages[i].size = MON_PIC_SIZE;

        switch (gfx->mode)
        {
        case MON_SPR_GFX_MODE_FULL_PARTY:
            InitMonSpritesGfx_FullParty(gfx);
            break;
        case MON_SPR_GFX_MODE_NORMAL:
        case MON_SPR_GFX_MODE_BATTLE:
        default:
            InitMonSpritesGfx_Battle(gfx);
            break;
        }
    }

    // If either of the allocations failed free their respective members
    if (failureFlags & ALLOC_FAIL_STRUCT)
    {
        TRY_FREE_AND_SET_NULL(gfx->frameImages);
        TRY_FREE_AND_SET_NULL(gfx->templates);
    }
    if (failureFlags & ALLOC_FAIL_BUFFER)
    {
        TRY_FREE_AND_SET_NULL(gfx->spritePointers);
        TRY_FREE_AND_SET_NULL(gfx->spriteBuffer);
    }

    if (failureFlags)
    {
        // Clear, something failed to allocate
        memset(gfx, 0, sizeof(*gfx));
        Free(gfx);
    }
    else
    {
        gfx->active = GFX_MANAGER_ACTIVE;
        sMonSpritesGfxManagers[managerId] = gfx;
    }

    return sMonSpritesGfxManagers[managerId];
}

void DestroyMonSpritesGfxManager(u8 managerId)
{
    struct MonSpritesGfxManager *gfx;

    managerId %= MON_SPR_GFX_MANAGERS_COUNT;
    gfx = sMonSpritesGfxManagers[managerId];
    // Clear global reference to avoid leaving a dangling pointer that others (swsh summary screen)
    // might read while the manager is being freed
    sMonSpritesGfxManagers[managerId] = NULL;
    if (gfx == NULL)
        return;

    if (gfx->active != GFX_MANAGER_ACTIVE)
    {
        memset(gfx, 0, sizeof(*gfx));
    }
    else
    {
        TRY_FREE_AND_SET_NULL(gfx->frameImages);
        TRY_FREE_AND_SET_NULL(gfx->templates);
        TRY_FREE_AND_SET_NULL(gfx->spritePointers);
        TRY_FREE_AND_SET_NULL(gfx->spriteBuffer);
        memset(gfx, 0, sizeof(*gfx));
        Free(gfx);
    }
}

u8 *MonSpritesGfxManager_GetSpritePtr(u8 managerId, u8 spriteNum)
{
    struct MonSpritesGfxManager *gfx = sMonSpritesGfxManagers[managerId % MON_SPR_GFX_MANAGERS_COUNT];
    if (gfx->active != GFX_MANAGER_ACTIVE)
    {
        return NULL;
    }
    else
    {
        if (spriteNum >= gfx->numSprites)
            spriteNum = 0;

        return gfx->spritePointers[spriteNum];
    }
}

u16 GetFormSpeciesId(u16 speciesId, u8 formId)
{
    if (GetSpeciesFormTable(speciesId) != NULL)
        return GetSpeciesFormTable(speciesId)[formId];
    else
        return speciesId;
}

u8 GetFormIdFromFormSpeciesId(u16 formSpeciesId)
{
    u8 targetFormId = 0;

    if (GetSpeciesFormTable(formSpeciesId) != NULL)
    {
        for (targetFormId = 0; GetSpeciesFormTable(formSpeciesId)[targetFormId] != FORM_SPECIES_END; targetFormId++)
        {
            if (formSpeciesId == GetSpeciesFormTable(formSpeciesId)[targetFormId])
                break;
        }
    }
    return targetFormId;
}

// Returns the current species if no form change is possible
u32 GetFormChangeTargetSpeciesBoxMon(struct BoxPokemon *boxMon, enum FormChanges method)
{
    u32 i;
    u32 species = GetBoxMonData(boxMon, MON_DATA_SPECIES, NULL);
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    if (formChanges == NULL)
        return species;

    struct FormChangeContext ctx =
    {
        .method = method,
        .currentSpecies = species,
        .partyItemUsed = gSpecialVar_ItemId,
        .multichoiceSelection = gSpecialVar_Result,
        .status = GetBoxMonData(boxMon, MON_DATA_STATUS),
    };

    for (i = 0; i < MAX_MON_ITEMS; i++)
        ctx.heldItems[i] = GetBoxMonData(boxMon, MON_DATA_HELD_ITEM + i);
    for (i = 0; i < MAX_MON_MOVES; i++)
        ctx.moves[i] = GetBoxMonData(boxMon, MON_DATA_MOVE1 + i);
    GetBoxMonData(boxMon, MON_DATA_NICKNAME, ctx.nickname);
    for (i = 0; i < MAX_MON_TRAITS; i++)
    {
        if (i == 0)
            ctx.traits[0] = GetAbilityBySpecies(species, GetBoxMonData(boxMon, MON_DATA_ABILITY_NUM));
        else
            ctx.traits[i] = gSpeciesInfo[ctx.currentSpecies].innates[i - 1];
    }

    return GetFormChangeTargetSpecies_Internal(ctx);
}

// Returns the current species if no form change is possible
u32 GetFormChangeTargetSpecies(struct Pokemon *mon, enum FormChanges method)
{
    return GetFormChangeTargetSpeciesBoxMon(&mon->box, method);
}

u32 FormChangeHasItem(struct FormChangeContext ctx, enum Item item)
{
    for (u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (ctx.heldItems[i] == item)
            return TRUE;
    }
    return FALSE;
}

u32 FormChangeHasTrait(struct FormChangeContext ctx, enum Ability ability)
{
    for (u32 i = 0; i < MAX_MON_TRAITS; i++)
    {
        if (ctx.traits[i] == ability)
            return TRUE;
    }
    return FALSE;
}

static const u8 *GetFormChangeNickname(u32 nicknameId)
{
    static const u8 sNicknameXD001[] = _("XD001");

    switch (nicknameId)
    {
    case FORM_CHANGE_NICKNAME_XD001:
        return sNicknameXD001;
    default:
        return NULL;
    }
}

static bool32 FormChangeHasNickname(const struct FormChangeContext *ctx, u32 nicknameId)
{
    const u8 *nickname = GetFormChangeNickname(nicknameId);

    if (nickname == NULL)
        return FALSE;
    return StringCompare(ctx->nickname, nickname) == 0;
}

u32 GetFormChangeTargetSpecies_Internal(struct FormChangeContext ctx)
{
    u32 i;
    u32 targetSpecies = ctx.currentSpecies;
    const struct FormChange *formChanges = GetSpeciesFormChanges(ctx.currentSpecies);

    if (formChanges == NULL)
        return ctx.currentSpecies;

    for (i = 0; formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        if (!(ctx.method == formChanges[i].method && ctx.currentSpecies != formChanges[i].targetSpecies))
            continue;

        switch (ctx.method)
        {
        case FORM_CHANGE_ITEM_HOLD:
            if ((FormChangeHasItem(ctx, formChanges[i].param1) || formChanges[i].param1 == ITEM_NONE)
                && (FormChangeHasTrait(ctx, formChanges[i].param2) || formChanges[i].param2 == ABILITY_NONE))
            {
                // This is to prevent reverting to base form when giving the item to the corresponding form.
                // Eg. Giving a Zap Plate to an Electric Arceus without an item (most likely to happen when using givemon)
                bool32 currentItemForm = FALSE;
                for (u32 j = 0; formChanges[j].method != FORM_CHANGE_TERMINATOR; j++)
                {
                    if (ctx.currentSpecies == formChanges[j].targetSpecies
                        && FormChangeHasItem(ctx, formChanges[j].param1)
                        && formChanges[j].param1 != ITEM_NONE)
                    {
                        currentItemForm = TRUE;
                        break;
                    }
                }
                if (!currentItemForm)
                    targetSpecies = formChanges[i].targetSpecies;
            }
            break;
        case FORM_CHANGE_ITEM_USE:
            if (ctx.partyItemUsed == formChanges[i].param1)
            {
                bool32 pass = TRUE;
                switch (formChanges[i].param2)
                {
                case DAY:
                    if (GetTimeOfDay() == TIME_NIGHT)
                        pass = FALSE;
                    break;
                case NIGHT:
                    if (GetTimeOfDay() != TIME_NIGHT)
                        pass = FALSE;
                    break;
                }

                if (formChanges[i].param3 != STATUS1_NONE && ctx.status & formChanges[i].param3)
                    pass = FALSE;

                if (pass)
                    targetSpecies = formChanges[i].targetSpecies;
            }
            break;
        case FORM_CHANGE_ITEM_USE_MULTICHOICE:
            if (ctx.partyItemUsed == formChanges[i].param1
             && ctx.multichoiceSelection == formChanges[i].param2)
            {
                targetSpecies = formChanges[i].targetSpecies;
            }
            break;
        case FORM_CHANGE_MOVE:
        {
            bool32 hasMove = FALSE;

            for (u32 j = 0; j < MAX_MON_MOVES; j++)
            {
                if (ctx.moves[j] == formChanges[i].param1)
                {
                    hasMove = TRUE;
                    break;
                }
            }

            if ((formChanges[i].param2 == WHEN_LEARNED && hasMove)
             || (formChanges[i].param2 == WHEN_FORGOTTEN && !hasMove))
                targetSpecies = formChanges[i].targetSpecies;
            break;
        }
        case FORM_CHANGE_BEGIN_BATTLE:
        case FORM_CHANGE_END_BATTLE:
            if (FormChangeHasItem(ctx, formChanges[i].param1) || formChanges[i].param1 == ITEM_NONE)
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_END_BATTLE_ENVIRONMENT:
            if (gBattleEnvironment == formChanges[i].param1)
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_WITHDRAW:
        case FORM_CHANGE_DEPOSIT:
        case FORM_CHANGE_FAINT:
        case FORM_CHANGE_DAYS_PASSED:
        case FORM_CHANGE_BEGIN_WILD_ENCOUNTER:
        case FORM_CHANGE_BATTLE_BOND:
            targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_STATUS:
            if (ctx.status & formChanges[i].param1)
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_TIME_OF_DAY:
            switch (formChanges[i].param1)
            {
            case DAY:
                if (GetTimeOfDay() != TIME_NIGHT)
                    targetSpecies = formChanges[i].targetSpecies;
                break;
            case NIGHT:
                if (GetTimeOfDay() == TIME_NIGHT)
                    targetSpecies = formChanges[i].targetSpecies;
                break;
            }
            break;
        case FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM:
        case FORM_CHANGE_BATTLE_PRIMAL_REVERSION:
        case FORM_CHANGE_BATTLE_ULTRA_BURST:
            if (FormChangeHasItem(ctx, formChanges[i].param1))
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE:
            if (ctx.moves[0] == formChanges[i].param1
                || ctx.moves[1] == formChanges[i].param1
                || ctx.moves[2] == formChanges[i].param1
                || ctx.moves[3] == formChanges[i].param1)
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_BATTLE_SWITCH_OUT:
            if (FormChangeHasTrait(ctx, formChanges[i].param1) || formChanges[i].param1 == ABILITY_NONE)
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_BATTLE_HP_PERCENT_DURING_MOVE:
            if (FormChangeHasTrait(ctx, formChanges[i].param1)
                && gCurrentMove == formChanges[i].param4)
            {
                // We multiply by 100 to make sure that integer division doesn't mess with the health check.
                u32 hpCheck = ctx.hp * 100 * 100 / ctx.maxHP;
                switch (formChanges[i].param2)
                {
                case HP_HIGHER_THAN:
                    if (hpCheck > formChanges[i].param3 * 100)
                        targetSpecies = formChanges[i].targetSpecies;
                    break;
                case HP_LOWER_EQ_THAN:
                    if (hpCheck <= formChanges[i].param3 * 100)
                        targetSpecies = formChanges[i].targetSpecies;
                    break;
                }
            }
            break;
        case FORM_CHANGE_BATTLE_HP_PERCENT_TURN_END:
        case FORM_CHANGE_BATTLE_HP_PERCENT_SEND_OUT:
            if (FormChangeHasTrait(ctx, formChanges[i].param1)
                && ctx.level >= formChanges[i].param4)
            {
                // We multiply by 100 to make sure that integer division doesn't mess with the health check.
                u32 hpCheck = ctx.hp * 100 * 100 / ctx.maxHP;
                switch (formChanges[i].param2)
                {
                case HP_HIGHER_THAN:
                    if (hpCheck > formChanges[i].param3 * 100)
                        targetSpecies = formChanges[i].targetSpecies;
                    break;
                case HP_LOWER_EQ_THAN:
                    if (hpCheck <= formChanges[i].param3 * 100)
                        targetSpecies = formChanges[i].targetSpecies;
                    break;
                }
            }
            break;
        case FORM_CHANGE_BATTLE_GIGANTAMAX:
            if (ctx.gmaxFactor)
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_BATTLE_WEATHER:
            // Check if there is a required ability and if the battler's ability does not match it
            // or is suppressed. If so, revert to the no weather form.
            if (formChanges[i].param2
                && !FormChangeHasTrait(ctx, formChanges[i].param2)
                && formChanges[i].param1 == B_WEATHER_NONE)
            {
                targetSpecies = formChanges[i].targetSpecies;
            }
            // We need to revert the weather form if the field is under Air Lock, too.
            else if (!HasWeatherEffect() && formChanges[i].param1 == B_WEATHER_NONE)
            {
                targetSpecies = formChanges[i].targetSpecies;
            }
            // Otherwise, just check for a match between the weather and the form change table.
            // Added a check for whether the weather is in effect to prevent end-of-turn soft locks with Cloud Nine / Air Lock
            else if (((gBattleWeather & formChanges[i].param1) && HasWeatherEffect())
                || (gBattleWeather == B_WEATHER_NONE && formChanges[i].param1 == B_WEATHER_NONE))
            {
                targetSpecies = formChanges[i].targetSpecies;
            }
            break;
        case FORM_CHANGE_BATTLE_HIT_BY_MOVE_CATEGORY:
            if (FormChangeHasTrait(ctx, formChanges[i].param1)
                && formChanges[i].param2 == GetBattleMoveCategory(gCurrentMove))
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_BATTLE_SWITCH_IN:
        case FORM_CHANGE_BATTLE_TURN_END:
        case FORM_CHANGE_BATTLE_HIT_BY_CONFUSION_SELF_DMG:
            if (FormChangeHasTrait(ctx, formChanges[i].param1))
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_BATTLE_TERASTALLIZATION:
            if (ctx.teraType == formChanges[i].param1)
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_BATTLE_BEFORE_MOVE:
        case FORM_CHANGE_BATTLE_AFTER_MOVE:
            if (formChanges[i].param1 == gCurrentMove
                && (formChanges[i].param2 == ABILITY_NONE || FormChangeHasTrait(ctx, formChanges[i].param2)))
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_BATTLE_BEFORE_MOVE_CATEGORY:
            if (formChanges[i].param1 == GetBattleMoveCategory(gCurrentMove)
                && (formChanges[i].param2 == ABILITY_NONE || FormChangeHasTrait(ctx, formChanges[i].param2)))
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_NICKNAME:
            if ((formChanges[i].param2 == FORM_CHANGE_NICKNAME_NOT_EQUALS && !FormChangeHasNickname(&ctx, formChanges[i].param1))
             || (formChanges[i].param2 != FORM_CHANGE_NICKNAME_NOT_EQUALS && FormChangeHasNickname(&ctx, formChanges[i].param1)))
                targetSpecies = formChanges[i].targetSpecies;
            break;
        case FORM_CHANGE_OVERWORLD_WEATHER:
        case FORM_CHANGE_TERMINATOR:
            break;
        }
    }

    return targetSpecies;
}


void TrySetDayLimitToFormChange(struct Pokemon *mon)
{
    u32 i;
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    for (i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        if (formChanges[i].method == FORM_CHANGE_DAYS_PASSED && species != formChanges[i].targetSpecies)
        {
            SetMonData(mon, MON_DATA_DAYS_SINCE_FORM_CHANGE, &formChanges[i].param1);
            break;
        }
    }
}

bool32 DoesSpeciesHaveFormChangeMethod(u16 species, enum FormChanges method)
{
    u32 i;
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    for (i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        if (method == formChanges[i].method && species != formChanges[i].targetSpecies)
            return TRUE;
    }

    return FALSE;
}

u16 MonTryLearningNewMoveEvolution(struct Pokemon *mon, bool8 firstMove)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u8 level = GetMonData(mon, MON_DATA_LEVEL);
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);

    // Since you can learn more than one move per level,
    // the game needs to know whether you decided to
    // learn it or keep the old set to avoid asking
    // you to learn the same move over and over again.
    if (firstMove)
    {
        sLearningMoveTableID = 0;
    }
    while (learnset[sLearningMoveTableID].move != LEVEL_UP_MOVE_END)
    {
        while ((learnset[sLearningMoveTableID].level == 0 || learnset[sLearningMoveTableID].level == level)
             && !(P_EVOLUTION_LEVEL_1_LEARN >= GEN_8 && learnset[sLearningMoveTableID].level == 1))
        {
            gMoveToLearn = learnset[sLearningMoveTableID].move;
            sLearningMoveTableID++;
            return GiveMoveToMon(mon, gMoveToLearn);
        }
        sLearningMoveTableID++;
    }
    return 0;
}

// Removes the selected index from the given IV list and shifts the remaining
// elements to the left.
void RemoveIVIndexFromList(u8 *ivs, u8 selectedIv)
{
    s32 i, j;
    u8 temp[NUM_STATS];

    ivs[selectedIv] = 0xFF;
    for (i = 0; i < NUM_STATS; i++)
    {
        temp[i] = ivs[i];
    }

    j = 0;
    for (i = 0; i < NUM_STATS; i++)
    {
        if (temp[i] != 0xFF)
            ivs[j++] = temp[i];
    }
}

// Attempts to perform non-level/item related overworld evolutions; called by tryspecialevo command.
void TryScriptEvolution(void)
{
    u8 i;
    bool32 canStopEvo = gSpecialVar_0x8001;
    u16 tryMultiple = gSpecialVar_0x8002;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        u32 targetSpecies = GetEvolutionTargetSpecies(&gPlayerParty[i], EVO_MODE_SCRIPT_TRIGGER, 0, NULL, &canStopEvo, CHECK_EVO);

        if (targetSpecies != SPECIES_NONE && !(sTriedEvolving & (1u << i)))
        {
            GetEvolutionTargetSpecies(&gPlayerParty[i], EVO_MODE_SCRIPT_TRIGGER, 0, NULL, &canStopEvo, DO_EVO);
            sTriedEvolving |= 1u << i;
            if (gMain.callback2 == TryScriptEvolution) // This fixes small graphics glitches.
                EvolutionScene(&gPlayerParty[i], targetSpecies, canStopEvo, i);
            else
                BeginEvolutionScene(&gPlayerParty[i], targetSpecies, canStopEvo, i);

            if (tryMultiple)
                gCB2_AfterEvolution = TryScriptEvolution;
            else
                gCB2_AfterEvolution = CB2_ReturnToField;
            return;
        }
    }

    sTriedEvolving = 0;
    SetMainCallback2(CB2_ReturnToField);
}

void TrySpecialOverworldEvo(void)
{
    u8 i;
    bool32 canStopEvo = gSpecialVar_0x8001;
    u16 tryMultiple = gSpecialVar_0x8002;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        u32 targetSpecies = GetEvolutionTargetSpecies(&gPlayerParty[i], EVO_MODE_OVERWORLD_SPECIAL, 0, NULL, &canStopEvo, CHECK_EVO);

        if (targetSpecies != SPECIES_NONE && !(sTriedEvolving & (1u << i)))
        {
            GetEvolutionTargetSpecies(&gPlayerParty[i], EVO_MODE_OVERWORLD_SPECIAL, 0, NULL, &canStopEvo, DO_EVO);
            sTriedEvolving |= 1u << i;
            if (gMain.callback2 == TrySpecialOverworldEvo) // This fixes small graphics glitches.
                EvolutionScene(&gPlayerParty[i], targetSpecies, canStopEvo, i);
            else
                BeginEvolutionScene(&gPlayerParty[i], targetSpecies, canStopEvo, i);

            if (tryMultiple)
                gCB2_AfterEvolution = TrySpecialOverworldEvo;
            else
                gCB2_AfterEvolution = CB2_ReturnToField;
            return;
        }
    }

    sTriedEvolving = 0;
    SetMainCallback2(CB2_ReturnToField);
}

bool32 SpeciesHasGenderDifferences(u16 species)
{
#if P_GENDER_DIFFERENCES
    if (gSpeciesInfo[species].frontPicFemale != NULL
     || gSpeciesInfo[species].backPicFemale != NULL
     || gSpeciesInfo[species].paletteFemale != NULL
     || gSpeciesInfo[species].shinyPaletteFemale != NULL
     || gSpeciesInfo[species].iconSpriteFemale != NULL
     || gSpeciesInfo[species].iconPaletteFemale != NULL
     || gSpeciesInfo[species].shinyIconPaletteFemale != NULL)
        return TRUE;
#endif

    return FALSE;
}

static struct PartyState *GetBattlerPartyStateByPokemon(struct Pokemon *partyMon)
{
    if (gBattleStruct == NULL)
        return NULL;

    for (int i = 0; i < NUM_BATTLE_SIDES; i++)
    {
        for (int j = 0; j < PARTY_SIZE; j++)
        {
            struct Pokemon *mon = &GetSideParty(i)[j];
            if (partyMon == mon)
                return &gBattleStruct->partyState[i][j];
        }
    }
    return NULL;
}

bool32 TryFormChange(struct Pokemon *mon, enum FormChanges method)
{
    if (GetMonData(mon, MON_DATA_SPECIES_OR_EGG, 0) == SPECIES_NONE
     || GetMonData(mon, MON_DATA_SPECIES_OR_EGG, 0) == SPECIES_EGG)
        return FALSE;

    u32 currentSpecies = GetMonData(mon, MON_DATA_SPECIES);
    u32 targetSpecies = GetFormChangeTargetSpecies(mon, method);

    struct PartyState *battlePartyState = GetBattlerPartyStateByPokemon(mon);
    // If the battle ends, and there's not a specified species to change back to,
    // use the species at the start of the battle.
    if (targetSpecies == SPECIES_NONE
        && battlePartyState != NULL && battlePartyState->changedSpecies != SPECIES_NONE
        // This is added to prevent FORM_CHANGE_END_BATTLE_ENVIRONMENT from omitting move changes
        // at the end of the battle, as it was being counting as a successful form change.
        && (method == FORM_CHANGE_END_BATTLE || method == FORM_CHANGE_FAINT))
    {
        targetSpecies = battlePartyState->changedSpecies;
    }

    assertf(targetSpecies != SPECIES_NONE, "form change target returned NONE. cur:%d, method:%d", currentSpecies, method)
    {
        return FALSE;
    }

    if (targetSpecies != currentSpecies)
    {
        TryToSetBattleFormChangeMoves(mon, method, targetSpecies);
        SetMonData(mon, MON_DATA_SPECIES, &targetSpecies);
        TrySetDayLimitToFormChange(mon);
        CalculateMonStats(mon);
        return TRUE;
    }

    return FALSE;
}

bool32 TrySelectedMonNicknameFormChange(void)
{
    if (gSpecialVar_0x8004 == PC_MON_CHOSEN)
        return TryBoxMonFormChange(GetSelectedBoxMonFromPcOrParty(), FORM_CHANGE_NICKNAME);
    if (gSpecialVar_0x8004 < PARTY_SIZE)
        return TryFormChange(&gPlayerParty[gSpecialVar_0x8004], FORM_CHANGE_NICKNAME);
    return FALSE;
}

bool32 TryBoxMonFormChange(struct BoxPokemon *boxMon, enum FormChanges method)
{
    if (GetBoxMonData(boxMon, MON_DATA_SPECIES_OR_EGG, 0) == SPECIES_NONE
     || GetBoxMonData(boxMon, MON_DATA_SPECIES_OR_EGG, 0) == SPECIES_EGG)
        return FALSE;

    u32 currentSpecies = GetBoxMonData(boxMon, MON_DATA_SPECIES, NULL);
    u32 targetSpecies = GetFormChangeTargetSpeciesBoxMon(boxMon, method);

    assertf(targetSpecies != SPECIES_NONE, "form change target returned NONE. cur:%d, method:%d", currentSpecies, method)
    {
        return FALSE;
    }

    if (targetSpecies != currentSpecies)
    {
        TryToSetBoxFormChangeMoves(boxMon, method, targetSpecies);
        SetBoxMonData(boxMon, MON_DATA_SPECIES, &targetSpecies);
        return TRUE;
    }
    return FALSE;
}

u16 SanitizeSpeciesId(u16 species)
{
    assertf(species <= NUM_SPECIES && (species == SPECIES_NONE || IsSpeciesEnabled(species)), "invalid species: %d", species)
    {
        return SPECIES_NONE;
    }

    return species;
}

bool32 IsSpeciesEnabled(u16 species)
{
    // This function should not use the GetSpeciesBaseHP function, as the included sanitation will result in an infinite loop
    return gSpeciesInfo[species].baseHP > 0 || species == SPECIES_EGG;
}

static bool32 GetFormChangeMoveSwap(const struct FormChange *formChange, enum FormChanges method, u16 *originalMove, u16 *newMove)
{
    switch (method)
    {
    case FORM_CHANGE_BEGIN_BATTLE:
    case FORM_CHANGE_END_BATTLE:
        *originalMove = formChange->param2;
        *newMove = formChange->param3;
        break;
    case FORM_CHANGE_NICKNAME:
        *originalMove = formChange->param3;
        *newMove = formChange->param4;
        break;
    default:
        return FALSE;
    }

    return *originalMove != MOVE_NONE && *newMove != MOVE_NONE;
}

static void TryToSetBoxFormChangeMoves(struct BoxPokemon *boxMon, enum FormChanges method, u16 targetSpecies)
{
    int i, j;
    u16 species = GetBoxMonData(boxMon, MON_DATA_SPECIES);
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    if (formChanges == NULL)
        return;

    for (i = 0; formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        u16 originalMove;
        u16 newMove;

        if (formChanges[i].method == method
            && formChanges[i].targetSpecies == targetSpecies
            && GetFormChangeMoveSwap(&formChanges[i], method, &originalMove, &newMove))
        {
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                u16 currMove = GetBoxMonData(boxMon, MON_DATA_MOVE1 + j);
                if (currMove == originalMove)
                    SetBoxMonMoveSlot_KeepPP(boxMon, newMove, j);
            }
            break;
        }
    }
}

void TryToSetBattleFormChangeMoves(struct Pokemon *mon, enum FormChanges method, u16 targetSpecies)
{
    TryToSetBoxFormChangeMoves(&mon->box, method, targetSpecies);
}

u32 GetMonFriendshipScore(struct Pokemon *pokemon)
{
    u32 friendshipScore = GetMonData(pokemon, MON_DATA_FRIENDSHIP);

    if (friendshipScore == MAX_FRIENDSHIP)
        return FRIENDSHIP_MAX;
    if (friendshipScore >= 200)
        return FRIENDSHIP_200_TO_254;
    if (friendshipScore >= 150)
        return FRIENDSHIP_150_TO_199;
    if (friendshipScore >= 100)
        return FRIENDSHIP_100_TO_149;
    if (friendshipScore >= 50)
        return FRIENDSHIP_50_TO_99;
    if (friendshipScore >= 1)
        return FRIENDSHIP_1_TO_49;

    return FRIENDSHIP_NONE;
}

u32 GetMonAffectionHearts(struct Pokemon *pokemon)
{
    u32 friendship = GetMonData(pokemon, MON_DATA_FRIENDSHIP);

    if (friendship == MAX_FRIENDSHIP)
        return AFFECTION_FIVE_HEARTS;
    if (friendship >= 220)
        return AFFECTION_FOUR_HEARTS;
    if (friendship >= 180)
        return AFFECTION_THREE_HEARTS;
    if (friendship >= 130)
        return AFFECTION_TWO_HEARTS;
    if (friendship >= 80)
        return AFFECTION_ONE_HEART;

    return AFFECTION_NO_HEARTS;
}

void UpdateMonPersonality(struct BoxPokemon *boxMon, u32 personality)
{
    bool32 isShiny = GetBoxMonData(boxMon, MON_DATA_IS_SHINY);
    u32 hiddenNature = GetBoxMonData(boxMon, MON_DATA_HIDDEN_NATURE);
    enum Type teraType = GetBoxMonData(boxMon, MON_DATA_TERA_TYPE);

    boxMon->personality = personality;

    SetBoxMonData(boxMon, MON_DATA_IS_SHINY, &isShiny);
    SetBoxMonData(boxMon, MON_DATA_HIDDEN_NATURE, &hiddenNature);
    SetBoxMonData(boxMon, MON_DATA_TERA_TYPE, &teraType);
}

void HealPokemon(struct Pokemon *mon)
{
    u32 data;

    data = GetMonData(mon, MON_DATA_MAX_HP);
    SetMonData(mon, MON_DATA_HP, &data);

    data = STATUS1_NONE;
    SetMonData(mon, MON_DATA_STATUS, &data);

    MonRestorePP(mon);
}

void HealBoxPokemon(struct BoxPokemon *boxMon)
{
    u32 data;

    data = 0;
    SetBoxMonData(boxMon, MON_DATA_HP_LOST, &data);

    data = STATUS1_NONE;
    SetBoxMonData(boxMon, MON_DATA_STATUS, &data);

    BoxMonRestorePP(boxMon);
}

enum PokemonCry GetCryIdBySpecies(u16 species)
{
    species = SanitizeSpeciesId(species);
    if (P_CRIES_ENABLED == FALSE || gSpeciesInfo[species].cryId >= CRY_COUNT || gTestRunnerHeadless)
        return CRY_NONE;
    return gSpeciesInfo[species].cryId;
}

u16 GetSpeciesPreEvolution(u16 species)
{
    int i, j;

    for (i = SPECIES_BULBASAUR; i < NUM_SPECIES; i++)
    {
        if (!IsSpeciesEnabled(i))
            continue;

        const struct Evolution *evolutions = GetSpeciesEvolutions(i);
        if (evolutions == NULL)
            continue;

        for (j = 0; evolutions[j].method != EVOLUTIONS_END; j++)
        {
            if (IsSpeciesEnabled(evolutions[j].targetSpecies) && SanitizeSpeciesId(evolutions[j].targetSpecies) == species)
                return i;
        }
    }

    return SPECIES_NONE;
}

void UpdateDaysPassedSinceFormChange(u16 days)
{
    u32 i;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        u32 currentSpecies = GetMonData(mon, MON_DATA_SPECIES);
        u8 daysSinceFormChange;

        if (currentSpecies == SPECIES_NONE)
            continue;

        daysSinceFormChange = GetMonData(mon, MON_DATA_DAYS_SINCE_FORM_CHANGE, 0);
        if (daysSinceFormChange == 0)
            continue;

        if (daysSinceFormChange > days)
            daysSinceFormChange -= days;
        else
            daysSinceFormChange = 0;

        SetMonData(mon, MON_DATA_DAYS_SINCE_FORM_CHANGE, &daysSinceFormChange);

        if (daysSinceFormChange == 0)
            TryFormChange(mon, FORM_CHANGE_DAYS_PASSED);
    }
}

enum Type CheckDynamicMoveType(struct Pokemon *mon, enum Move move, enum BattlerId battler, enum MonState state)
{
    enum Type moveType = GetDynamicMoveType(mon, move, battler, state);
    if (moveType != TYPE_NONE)
        return moveType;
    return GetMoveType(move);
}

uq4_12_t GetDynamaxLevelHPMultiplier(u32 dynamaxLevel, bool32 inverseMultiplier)
{
    if (inverseMultiplier)
        return UQ_4_12(1.0/(1.5 + 0.05 * dynamaxLevel));
    return UQ_4_12(1.5 + 0.05 * dynamaxLevel);
}

bool32 IsSpeciesRegionalForm(u32 species)
{
    return gSpeciesInfo[species].isAlolanForm
        || gSpeciesInfo[species].isGalarianForm
        || gSpeciesInfo[species].isHisuianForm
        || gSpeciesInfo[species].isPaldeanForm;
}

bool32 IsSpeciesRegionalFormFromRegion(u32 species, u32 region)
{
    switch (region)
    {
    case REGION_ALOLA:  return gSpeciesInfo[species].isAlolanForm;
    case REGION_GALAR:  return gSpeciesInfo[species].isGalarianForm;
    case REGION_HISUI:  return gSpeciesInfo[species].isHisuianForm;
    case REGION_PALDEA: return gSpeciesInfo[species].isPaldeanForm;
    default:            return FALSE;
    }
}

bool32 SpeciesHasRegionalForm(u32 species)
{
    u32 formId;
    const u16 *formTable = GetSpeciesFormTable(species);
    for (formId = 0; formTable != NULL && formTable[formId] != FORM_SPECIES_END; formId++)
    {
        if (IsSpeciesRegionalForm(formTable[formId]))
            return TRUE;
    }
    return FALSE;
}

u32 GetRegionalFormByRegion(u32 species, u32 region)
{
    u32 formId = 0;
    u32 firstFoundSpecies = 0;
    const u16 *formTable = GetSpeciesFormTable(species);

    if (formTable != NULL)
    {
        for (formId = 0; formTable[formId] != FORM_SPECIES_END; formId++)
        {
            if (firstFoundSpecies == 0)
                firstFoundSpecies = formTable[formId];

            if (IsSpeciesRegionalFormFromRegion(formTable[formId], region))
                return formTable[formId];
        }
        if (firstFoundSpecies != 0)
            return firstFoundSpecies;
    }
    return species;
}

bool32 IsSpeciesForeignRegionalForm(u32 species, u32 currentRegion)
{
    u32 i;
    for (i = 0; i < REGIONS_COUNT; i++)
    {
        if (currentRegion != i && IsSpeciesRegionalFormFromRegion(species, i))
            return TRUE;
        else if (currentRegion == i && SpeciesHasRegionalForm(species) && !IsSpeciesRegionalFormFromRegion(species, i))
            return TRUE;
    }
    return FALSE;
}

enum Type GetTeraTypeFromPersonality(struct Pokemon *mon)
{
    const u8 *types = gSpeciesInfo[GetMonData(mon, MON_DATA_SPECIES)].types;
    return (GetMonData(mon, MON_DATA_PERSONALITY) & 0x1) == 0 ? types[0] : types[1];
}

struct Pokemon *GetSavedPlayerPartyMon(u32 index)
{
    return &gSaveBlock1Ptr->playerParty[index];
}

u8 *GetSavedPlayerPartyCount(void)
{
    return &gSaveBlock1Ptr->playerPartyCount;
}

void SavePlayerPartyMon(u32 index, struct Pokemon *mon)
{
    gSaveBlock1Ptr->playerParty[index] = *mon;
}

void RestoreFacilitySketchedMoves(struct Pokemon *savedMon, struct Pokemon *facilityMon)
{
#if P_FAMILY_SMEARGLE
    bool8 savedMoveMatched[MAX_MON_MOVES] = {FALSE};

    if (GetMonData(savedMon, MON_DATA_SPECIES) != SPECIES_SMEARGLE)
        return;

    for (u32 facilitySlot = 0; facilitySlot < MAX_MON_MOVES; facilitySlot++)
    {
        enum Move facilityMove = GetMonData(facilityMon, MON_DATA_MOVE1 + facilitySlot);
        u32 savedSlot;

        for (savedSlot = 0; savedSlot < MAX_MON_MOVES; savedSlot++)
        {
            enum Move savedMove = GetMonData(savedMon, MON_DATA_MOVE1 + savedSlot);

            if (!savedMoveMatched[savedSlot]
             && savedMove != MOVE_SKETCH
             && savedMove == facilityMove)
            {
                savedMoveMatched[savedSlot] = TRUE;
                break;
            }
        }

        if (savedSlot == MAX_MON_MOVES && facilityMove != MOVE_SKETCH)
            SetMonMoveSlot(facilityMon, MOVE_SKETCH, facilitySlot);
    }
#else
    (void)savedMon;
    (void)facilityMon;
#endif
}

bool32 IsSpeciesOfType(u32 species, enum Type type)
{
    if (gSpeciesInfo[species].types[0] == type
     || gSpeciesInfo[species].types[1] == type)
        return TRUE;
    return FALSE;
}

#define RANDOM_SPECIES_COUNT ARRAY_COUNT(sRandomSpecies)
static const u16 sRandomSpecies[] =
{
    //SPECIES_NONE                    ,
    SPECIES_BULBASAUR               ,
    SPECIES_IVYSAUR                 ,
    SPECIES_VENUSAUR                ,
    SPECIES_CHARMANDER              ,
    SPECIES_CHARMELEON              ,
    SPECIES_CHARIZARD               ,
    SPECIES_SQUIRTLE                ,
    SPECIES_WARTORTLE               ,
    SPECIES_BLASTOISE               ,
    SPECIES_CATERPIE                ,
    SPECIES_METAPOD                 ,
    SPECIES_BUTTERFREE              ,
    SPECIES_WEEDLE                  ,
    SPECIES_KAKUNA                  ,
    SPECIES_BEEDRILL                ,
    SPECIES_PIDGEY                  ,
    SPECIES_PIDGEOTTO               ,
    SPECIES_PIDGEOT                 ,
    SPECIES_RATTATA                 ,
    SPECIES_RATICATE                ,
    SPECIES_SPEAROW                 ,
    SPECIES_FEAROW                  ,
    SPECIES_EKANS                   ,
    SPECIES_ARBOK                   ,
    SPECIES_PIKACHU                 ,
    SPECIES_RAICHU                  ,
    SPECIES_SANDSHREW               ,
    SPECIES_SANDSLASH               ,
    SPECIES_NIDORAN_F               ,
    SPECIES_NIDORINA                ,
    SPECIES_NIDOQUEEN               ,
    SPECIES_NIDORAN_M               ,
    SPECIES_NIDORINO                ,
    SPECIES_NIDOKING                ,
    SPECIES_CLEFAIRY                ,
    SPECIES_CLEFABLE                ,
    SPECIES_VULPIX                  ,
    SPECIES_NINETALES               ,
    SPECIES_JIGGLYPUFF              ,
    SPECIES_WIGGLYTUFF              ,
    SPECIES_ZUBAT                   ,
    SPECIES_GOLBAT                  ,
    SPECIES_ODDISH                  ,
    SPECIES_GLOOM                   ,
    SPECIES_VILEPLUME               ,
    SPECIES_PARAS                   ,
    SPECIES_PARASECT                ,
    SPECIES_VENONAT                 ,
    SPECIES_VENOMOTH                ,
    SPECIES_DIGLETT                 ,
    SPECIES_DUGTRIO                 ,
    SPECIES_MEOWTH                  ,
    SPECIES_PERSIAN                 ,
    SPECIES_PSYDUCK                 ,
    SPECIES_GOLDUCK                 ,
    SPECIES_MANKEY                  ,
    SPECIES_PRIMEAPE                ,
    SPECIES_GROWLITHE               ,
    SPECIES_ARCANINE                ,
    SPECIES_POLIWAG                 ,
    SPECIES_POLIWHIRL               ,
    SPECIES_POLIWRATH               ,
    SPECIES_ABRA                    ,
    SPECIES_KADABRA                 ,
    SPECIES_ALAKAZAM                ,
    SPECIES_MACHOP                  ,
    SPECIES_MACHOKE                 ,
    SPECIES_MACHAMP                 ,
    SPECIES_BELLSPROUT              ,
    SPECIES_WEEPINBELL              ,
    SPECIES_VICTREEBEL              ,
    SPECIES_TENTACOOL               ,
    SPECIES_TENTACRUEL              ,
    SPECIES_GEODUDE                 ,
    SPECIES_GRAVELER                ,
    SPECIES_GOLEM                   ,
    SPECIES_PONYTA                  ,
    SPECIES_RAPIDASH                ,
    SPECIES_SLOWPOKE                ,
    SPECIES_SLOWBRO                 ,
    SPECIES_MAGNEMITE               ,
    SPECIES_MAGNETON                ,
    SPECIES_FARFETCHD               ,
    SPECIES_DODUO                   ,
    SPECIES_DODRIO                  ,
    SPECIES_SEEL                    ,
    SPECIES_DEWGONG                 ,
    SPECIES_GRIMER                  ,
    SPECIES_MUK                     ,
    SPECIES_SHELLDER                ,
    SPECIES_CLOYSTER                ,
    SPECIES_GASTLY                  ,
    SPECIES_HAUNTER                 ,
    SPECIES_GENGAR                  ,
    SPECIES_ONIX                    ,
    SPECIES_DROWZEE                 ,
    SPECIES_HYPNO                   ,
    SPECIES_KRABBY                  ,
    SPECIES_KINGLER                 ,
    SPECIES_VOLTORB                 ,
    SPECIES_ELECTRODE               ,
    SPECIES_EXEGGCUTE               ,
    SPECIES_EXEGGUTOR               ,
    SPECIES_CUBONE                  ,
    SPECIES_MAROWAK                 ,
    SPECIES_HITMONLEE               ,
    SPECIES_HITMONCHAN              ,
    SPECIES_LICKITUNG               ,
    SPECIES_KOFFING                 ,
    SPECIES_WEEZING                 ,
    SPECIES_RHYHORN                 ,
    SPECIES_RHYDON                  ,
    SPECIES_CHANSEY                 ,
    SPECIES_TANGELA                 ,
    SPECIES_KANGASKHAN              ,
    SPECIES_HORSEA                  ,
    SPECIES_SEADRA                  ,
    SPECIES_GOLDEEN                 ,
    SPECIES_SEAKING                 ,
    SPECIES_STARYU                  ,
    SPECIES_STARMIE                 ,
    SPECIES_MR_MIME                 ,
    SPECIES_SCYTHER                 ,
    SPECIES_JYNX                    ,
    SPECIES_ELECTABUZZ              ,
    SPECIES_MAGMAR                  ,
    SPECIES_PINSIR                  ,
    SPECIES_TAUROS                  ,
    SPECIES_MAGIKARP                ,
    SPECIES_GYARADOS                ,
    SPECIES_LAPRAS                  ,
    SPECIES_DITTO                   ,
    SPECIES_EEVEE                   ,
    SPECIES_VAPOREON                ,
    SPECIES_JOLTEON                 ,
    SPECIES_FLAREON                 ,
    SPECIES_PORYGON                 ,
    SPECIES_OMANYTE                 ,
    SPECIES_OMASTAR                 ,
    SPECIES_KABUTO                  ,
    SPECIES_KABUTOPS                ,
    SPECIES_AERODACTYL              ,
    SPECIES_SNORLAX                 ,
    // SPECIES_ARTICUNO  ,
    // SPECIES_ZAPDOS    ,
    // SPECIES_MOLTRES   ,
    SPECIES_DRATINI                 ,
    SPECIES_DRAGONAIR               ,
    SPECIES_DRAGONITE               ,
    // SPECIES_MEWTWO    ,
    // SPECIES_MEW       ,
    SPECIES_CHIKORITA                  ,
    SPECIES_BAYLEEF                    ,
    SPECIES_MEGANIUM                   ,
    SPECIES_CYNDAQUIL                  ,
    SPECIES_QUILAVA                    ,
    SPECIES_TYPHLOSION                 ,
    SPECIES_TOTODILE                   ,
    SPECIES_CROCONAW                   ,
    SPECIES_FERALIGATR                 ,
    SPECIES_SENTRET                    ,
    SPECIES_FURRET                     ,
    SPECIES_HOOTHOOT                   ,
    SPECIES_NOCTOWL                    ,
    SPECIES_LEDYBA                     ,
    SPECIES_LEDIAN                     ,
    SPECIES_SPINARAK                   ,
    SPECIES_ARIADOS                    ,
    SPECIES_CROBAT                     ,
    SPECIES_CHINCHOU                   ,
    SPECIES_LANTURN                    ,
    SPECIES_PICHU                      ,
    SPECIES_CLEFFA                     ,
    SPECIES_IGGLYBUFF                  ,
    SPECIES_TOGEPI                     ,
    SPECIES_TOGETIC                    ,
    SPECIES_NATU                       ,
    SPECIES_XATU                       ,
    SPECIES_MAREEP                     ,
    SPECIES_FLAAFFY                    ,
    SPECIES_AMPHAROS                   ,
    SPECIES_BELLOSSOM                  ,
    SPECIES_MARILL                     ,
    SPECIES_AZUMARILL                  ,
    SPECIES_SUDOWOODO                  ,
    SPECIES_POLITOED                   ,
    SPECIES_HOPPIP                     ,
    SPECIES_SKIPLOOM                   ,
    SPECIES_JUMPLUFF                   ,
    SPECIES_AIPOM                      ,
    SPECIES_SUNKERN                    ,
    SPECIES_SUNFLORA                   ,
    SPECIES_YANMA                      ,
    SPECIES_WOOPER                     ,
    SPECIES_QUAGSIRE                   ,
    SPECIES_ESPEON                     ,
    SPECIES_UMBREON                    ,
    SPECIES_MURKROW                    ,
    SPECIES_SLOWKING                   ,
    SPECIES_MISDREAVUS                 ,
    SPECIES_UNOWN                      ,
    SPECIES_WOBBUFFET                  ,
    SPECIES_GIRAFARIG                  ,
    SPECIES_PINECO                     ,
    SPECIES_FORRETRESS                 ,
    SPECIES_DUNSPARCE                  ,
    SPECIES_GLIGAR                     ,
    SPECIES_STEELIX                    ,
    SPECIES_SNUBBULL                   ,
    SPECIES_GRANBULL                   ,
    SPECIES_QWILFISH                   ,
    SPECIES_SCIZOR                     ,
    SPECIES_SHUCKLE                    ,
    SPECIES_HERACROSS                  ,
    SPECIES_SNEASEL                    ,
    SPECIES_TEDDIURSA                  ,
    SPECIES_URSARING                   ,
    SPECIES_SLUGMA                     ,
    SPECIES_MAGCARGO                   ,
    SPECIES_SWINUB                     ,
    SPECIES_PILOSWINE                  ,
    SPECIES_CORSOLA                    ,
    SPECIES_REMORAID                   ,
    SPECIES_OCTILLERY                  ,
    SPECIES_DELIBIRD                   ,
    SPECIES_MANTINE                    ,
    SPECIES_SKARMORY                   ,
    SPECIES_HOUNDOUR                   ,
    SPECIES_HOUNDOOM                   ,
    SPECIES_KINGDRA                    ,
    SPECIES_PHANPY                     ,
    SPECIES_DONPHAN                    ,
    SPECIES_PORYGON2                   ,
    SPECIES_STANTLER                   ,
    SPECIES_SMEARGLE                   ,
    SPECIES_TYROGUE                    ,
    SPECIES_HITMONTOP                  ,
    SPECIES_SMOOCHUM                   ,
    SPECIES_ELEKID                     ,
    SPECIES_MAGBY                      ,
    SPECIES_MILTANK                    ,
    SPECIES_BLISSEY                    ,
    //SPECIES_RAIKOU                     ,
    //SPECIES_ENTEI                      ,
    //SPECIES_SUICUNE                    ,
    SPECIES_LARVITAR                   ,
    SPECIES_PUPITAR                    ,
    SPECIES_TYRANITAR                  ,
    // SPECIES_LUGIA     ,
    // SPECIES_HO_OH     ,
    // SPECIES_CELEBI    ,
    // SPECIES_OLD_UNOWN_B,
    // SPECIES_OLD_UNOWN_C,
    // SPECIES_OLD_UNOWN_D,
    // SPECIES_OLD_UNOWN_E,
    // SPECIES_OLD_UNOWN_F,
    // SPECIES_OLD_UNOWN_G,
    // SPECIES_OLD_UNOWN_H,
    // SPECIES_OLD_UNOWN_I,
    // SPECIES_OLD_UNOWN_J,
    // SPECIES_OLD_UNOWN_K,
    // SPECIES_OLD_UNOWN_L,
    // SPECIES_OLD_UNOWN_M,
    // SPECIES_OLD_UNOWN_N,
    // SPECIES_OLD_UNOWN_O,
    // SPECIES_OLD_UNOWN_P,
    // SPECIES_OLD_UNOWN_Q,
    // SPECIES_OLD_UNOWN_R,
    // SPECIES_OLD_UNOWN_S,
    // SPECIES_OLD_UNOWN_T,
    // SPECIES_OLD_UNOWN_U,
    // SPECIES_OLD_UNOWN_V,
    // SPECIES_OLD_UNOWN_W,
    // SPECIES_OLD_UNOWN_X,
    // SPECIES_OLD_UNOWN_Y,
    // SPECIES_OLD_UNOWN_Z,
    SPECIES_TREECKO           ,
    SPECIES_GROVYLE           ,
    SPECIES_SCEPTILE          ,
    SPECIES_TORCHIC           ,
    SPECIES_COMBUSKEN         ,
    SPECIES_BLAZIKEN          ,
    SPECIES_MUDKIP            ,
    SPECIES_MARSHTOMP         ,
    SPECIES_SWAMPERT          ,
    SPECIES_POOCHYENA         ,
    SPECIES_MIGHTYENA         ,
    SPECIES_ZIGZAGOON         ,
    SPECIES_LINOONE           ,
    SPECIES_WURMPLE           ,
    SPECIES_SILCOON           ,
    SPECIES_BEAUTIFLY         ,
    SPECIES_CASCOON           ,
    SPECIES_DUSTOX            ,
    SPECIES_LOTAD             ,
    SPECIES_LOMBRE            ,
    SPECIES_LUDICOLO          ,
    SPECIES_SEEDOT            ,
    SPECIES_NUZLEAF           ,
    SPECIES_SHIFTRY           ,
    SPECIES_NINCADA           ,
    SPECIES_NINJASK           ,
    // SPECIES_SHEDINJA          ,
    SPECIES_TAILLOW           ,
    SPECIES_SWELLOW           ,
    SPECIES_SHROOMISH         ,
    SPECIES_BRELOOM           ,
    SPECIES_SPINDA            ,
    SPECIES_WINGULL           ,
    SPECIES_PELIPPER          ,
    SPECIES_SURSKIT           ,
    SPECIES_MASQUERAIN        ,
    SPECIES_WAILMER           ,
    SPECIES_WAILORD           ,
    SPECIES_SKITTY            ,
    SPECIES_DELCATTY          ,
    SPECIES_KECLEON           ,
    SPECIES_BALTOY            ,
    SPECIES_CLAYDOL           ,
    SPECIES_NOSEPASS          ,
    SPECIES_TORKOAL           ,
    SPECIES_SABLEYE           ,
    SPECIES_BARBOACH          ,
    SPECIES_WHISCASH          ,
    SPECIES_LUVDISC           ,
    SPECIES_CORPHISH          ,
    SPECIES_CRAWDAUNT         ,
    SPECIES_FEEBAS            ,
    SPECIES_MILOTIC           ,
    SPECIES_CARVANHA          ,
    SPECIES_SHARPEDO          ,
    SPECIES_TRAPINCH          ,
    SPECIES_VIBRAVA           ,
    SPECIES_FLYGON            ,
    SPECIES_MAKUHITA          ,
    SPECIES_HARIYAMA          ,
    SPECIES_ELECTRIKE         ,
    SPECIES_MANECTRIC         ,
    SPECIES_NUMEL             ,
    SPECIES_CAMERUPT          ,
    SPECIES_SPHEAL            ,
    SPECIES_SEALEO            ,
    SPECIES_WALREIN           ,
    SPECIES_CACNEA            ,
    SPECIES_CACTURNE          ,
    SPECIES_SNORUNT           ,
    SPECIES_GLALIE            ,
    SPECIES_LUNATONE          ,
    SPECIES_SOLROCK           ,
    SPECIES_AZURILL           ,
    SPECIES_SPOINK            ,
    SPECIES_GRUMPIG           ,
    SPECIES_PLUSLE            ,
    SPECIES_MINUN             ,
    SPECIES_MAWILE            ,
    SPECIES_MEDITITE          ,
    SPECIES_MEDICHAM          ,
    SPECIES_SWABLU            ,
    SPECIES_ALTARIA           ,
    SPECIES_WYNAUT            ,
    SPECIES_DUSKULL           ,
    SPECIES_DUSCLOPS          ,
    SPECIES_ROSELIA           ,
    SPECIES_SLAKOTH           ,
    SPECIES_VIGOROTH          ,
    SPECIES_SLAKING           ,
    SPECIES_GULPIN            ,
    SPECIES_SWALOT            ,
    SPECIES_TROPIUS           ,
    SPECIES_WHISMUR           ,
    SPECIES_LOUDRED           ,
    SPECIES_EXPLOUD           ,
    SPECIES_CLAMPERL          ,
    SPECIES_HUNTAIL           ,
    SPECIES_GOREBYSS          ,
    SPECIES_ABSOL             ,
    SPECIES_SHUPPET           ,
    SPECIES_BANETTE           ,
    SPECIES_SEVIPER           ,
    SPECIES_ZANGOOSE          ,
    SPECIES_RELICANTH         ,
    SPECIES_ARON              ,
    SPECIES_LAIRON            ,
    SPECIES_AGGRON            ,
    // SPECIES_CASTFORM          ,
    SPECIES_VOLBEAT           ,
    SPECIES_ILLUMISE          ,
    SPECIES_LILEEP            ,
    SPECIES_CRADILY           ,
    SPECIES_ANORITH           ,
    SPECIES_ARMALDO           ,
    SPECIES_RALTS             ,
    SPECIES_KIRLIA            ,
    SPECIES_GARDEVOIR         ,
    SPECIES_BAGON             ,
    SPECIES_SHELGON           ,
    SPECIES_SALAMENCE         ,
    SPECIES_BELDUM            ,
    SPECIES_METANG            ,
    SPECIES_METAGROSS         ,
    // SPECIES_REGIROCK  ,
    // SPECIES_REGICE    ,
    // SPECIES_REGISTEEL ,
    // SPECIES_KYOGRE    ,
    // SPECIES_GROUDON   ,
    // SPECIES_RAYQUAZA  ,
    // SPECIES_LATIAS    ,
    // SPECIES_LATIOS    ,
    // SPECIES_JIRACHI   ,
    // SPECIES_DEOXYS    ,
    SPECIES_CHIMECHO          ,
    SPECIES_AMBIPOM           ,
    //SPECIES_ARCEUS            ,
    SPECIES_BONSLY            ,
    SPECIES_BUDEW             ,
    SPECIES_CHINGLING         ,
    SPECIES_DUSKNOIR          ,
    SPECIES_ELECTIVIRE        ,
    SPECIES_FROSLASS          ,
    SPECIES_GALLADE           ,
    SPECIES_GLACEON           ,
    SPECIES_GLISCOR           ,
    SPECIES_HAPPINY           ,
    SPECIES_HONCHKROW         ,
    SPECIES_LEAFEON           ,
    SPECIES_LICKILICKY        ,
    SPECIES_MAGMORTAR         ,
    SPECIES_MAGNEZONE         ,
    SPECIES_MAMOSWINE         ,
    SPECIES_MANTYKE           ,
    SPECIES_MISMAGIUS         ,
    SPECIES_MIME_JR           ,
    SPECIES_MUNCHLAX          ,
    SPECIES_PORYGON_Z         ,
    SPECIES_PROBOPASS         ,
    //SPECIES_REGIDRAGO         ,
    //SPECIES_REGIELEKI         ,
    //SPECIES_REGIGIGAS         ,
    SPECIES_RHYPERIOR         ,
    SPECIES_ROSERADE          ,
    SPECIES_SYLVEON           ,
    SPECIES_TANGROWTH         ,
    SPECIES_TOGEKISS          ,
    SPECIES_WEAVILE           ,
    SPECIES_YANMEGA           ,
    //SPECIES_DEOXYS_ATTACK     ,
    //SPECIES_DEOXYS_DEFENSE    ,
    //SPECIES_DEOXYS_SPEED      ,
    SPECIES_ANNIHILAPE           ,
    SPECIES_FARIGIRAF           ,
    SPECIES_DUDUNSPARCE           ,
    SPECIES_WYRDEER           ,
    SPECIES_URSALUNA           ,
    SPECIES_URSALUNA_BLOODMOON           ,
    SPECIES_KLEAVOR           ,
    //SPECIES_UNUSED_SPACE5           ,
    //SPECIES_UNUSED_SPACE6           ,
    //SPECIES_UNUSED_SPACE7           ,
    //SPECIES_UNUSED_SPACE8           ,
    //SPECIES_UNUSED_SPACE9           ,
    //SPECIES_UNUSED_SPACE10            ,
    // SPECIES_EGG       ,
};

u16 GetSpeciesRandomSeeded(u16 species, u8 type, u16 additionalOffset)
{
    u16 speciesResult = species;
    //generate species based on the type
    //different types have different parameters, e.g. abilities are never mapBased
    //speciesResult = GetRandomSpecies(species, mapBased, type, additionalOffset);
    speciesResult = (Random() % 1407 + 1); //only randomizes up to SPECIES_IRON_LEAVES

    return speciesResult;
}

u16 GetRandomSpeciesScripted(u16 species)
{
    u16 speciesResult = species;
    u32 newSpecies = species;
    //generate species based on the type
    //different types have different parameters, e.g. abilities are never mapBased
    //speciesResult = GetRandomSpecies(species, mapBased, type, additionalOffset);
    speciesResult = (Random() % 1407 + 1); //only randomizes up to SPECIES_IRON_LEAVES
    CreateMonLegacy(&gEnemyParty[0], speciesResult, 5, USE_RANDOM_IVS, TRUE, Random32(), OT_ID_PLAYER_ID, 0);
    VarSet(VAR_TEMP_F, newSpecies);
    return speciesResult;
}
struct BoxPokemon *GetSelectedBoxMonFromPcOrParty(void)
{
    struct BoxPokemon *boxmon;
    if (gSpecialVar_0x8004 == PC_MON_CHOSEN)
        boxmon = GetBoxedMonPtr(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos);
    else
        boxmon = &(gPlayerParty[gSpecialVar_0x8004].box);
    return boxmon;
}

u32 GiveScriptedMonToPlayer(struct Pokemon *mon, u8 slot)
{
    u32 sentToPc;
    u32 i = 0;

    ApplyReplayEasyIVs(mon);

    if (slot < PARTY_SIZE)
    {
        CopyMon(&gPlayerParty[slot], mon, sizeof(struct Pokemon));
        sentToPc = MON_GIVEN_TO_PARTY;
    }
    else
    {
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) == SPECIES_NONE)
                break;
        }
        if (i >= PARTY_SIZE)
        {
            sentToPc = CopyMonToPC(mon);
        }
        else
        {
            sentToPc = MON_GIVEN_TO_PARTY;
            CopyMon(&gPlayerParty[i], mon, sizeof(struct Pokemon));
            gPlayerPartyCount = i + 1;
        }
    }
    if (sentToPc != MON_CANT_GIVE)
    {
        HandleSetPokedexFlagFromMon(mon, FLAG_SET_SEEN);
        HandleSetPokedexFlagFromMon(mon, FLAG_SET_CAUGHT);
        Achievement_OnPokemonObtained(GetMonData(mon, MON_DATA_SPECIES));
    }
    return sentToPc;
}

void ChangePokemonNicknameWithCallback(void (*callback)(void))
{
    struct BoxPokemon *boxMon = GetSelectedBoxMonFromPcOrParty();
    GetBoxMonData(boxMon, MON_DATA_NICKNAME, gStringVar3);
    GetBoxMonData(boxMon, MON_DATA_NICKNAME, gStringVar2);
    DoNamingScreen(NAMING_SCREEN_NICKNAME, gStringVar2,
                   GetBoxMonData(boxMon, MON_DATA_SPECIES),
                   GetBoxMonGender(boxMon),
                   GetBoxMonData(boxMon, MON_DATA_PERSONALITY),
                   GetBoxMonData(boxMon, MON_DATA_IS_SHINY),
                   callback);
}
//Traits Block

u8 GetInnateUnlockLevel(u32 innateNum)
{
    static const u8 sInnateUnlockLevels[MAX_MON_INNATES_INTERNAL] =
    {
        INNATE_1_UNLOCK_LEVEL,
        INNATE_2_UNLOCK_LEVEL,
        INNATE_3_UNLOCK_LEVEL,
    };

    if (innateNum == 0 || innateNum > MAX_MON_INNATES_INTERNAL)
        return 0;

    return sInnateUnlockLevels[innateNum - 1];
}

bool32 IsInnateUnlockedByLevel(u32 innateNum, u32 level)
{
    u32 unlockLevel = GetInnateUnlockLevel(innateNum);

    if (AreReplayInnatesDisabled())
        return FALSE;

    return AreBattleFacilityInnatesForced()
        || FlagGet(FLAG_ALL_INNATES_UNLOCKED)
        || unlockLevel == 0
        || level >= unlockLevel;
}

//Returns the slot the Innate is found in, assuming the Ability is already slot 1. Returns 0 if not found.
u32 SpeciesHasInnate(u32 species, enum Ability ability)
{
    u32 innateNum = 0;

    if (AreReplayInnatesDisabled())
        return 0;

    for (u32 i = 0; i < MAX_MON_INNATES; i++)
    {
        if (gSpeciesInfo[species].innates[i] == ability)
            {
                innateNum = i + 2;
                //DebugPrintf("INNATE FOUND: %d", innateNum - 1);
            }
    }

        return innateNum;
}

u32 SpeciesHasInnateAtLevel(u32 species, enum Ability ability, u32 level)
{
    u32 innateNum = SpeciesHasInnate(species, ability);

    if (innateNum == 0)
        return 0;

    return IsInnateUnlockedByLevel(innateNum - 1, level) ? innateNum : 0;
}

bool32 BoxMonHasInnate(struct BoxPokemon *boxmon,  enum Ability ability)
{
    u32 species = GetBoxMonData(boxmon, MON_DATA_SPECIES, NULL);
    u32 level = GetLevelFromBoxMonExp(boxmon);

    return SpeciesHasInnateAtLevel(species, ability, level);
}

bool32 MonHasTrait(struct Pokemon *mon,  enum Ability ability)
{
    u32 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u32 level = GetMonData(mon, MON_DATA_LEVEL, NULL);

    return (GetMonAbility(mon) == ability || SpeciesHasInnateAtLevel(species, ability, level));
} 

enum Ability GetSpeciesInnate(u32 species, u32 traitNum)
{
    if (MAX_MON_INNATES > 0)
            return gSpeciesInfo[species].innates[traitNum - 1];
    else
        return 0;
}

//Multi Item Block
u32 MonHasItem(struct Pokemon *mon, enum Item item)
{
    for(u32 i = 0; i < MAX_MON_ITEMS; i++)
        if(item == GetMonData(mon, MON_DATA_HELD_ITEM + i))
            return TRUE;

    return FALSE;
}
u32 MonHasItemHoldEffect(struct Pokemon *mon, enum HoldEffect holdEffect)
{
    enum Item item;
    enum HoldEffect itemHoldEffect;

    for(u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        item = GetMonData(mon, MON_DATA_HELD_ITEM + i);
        itemHoldEffect = GetItemHoldEffect(item);
        if(holdEffect == itemHoldEffect)
            return TRUE;
    }

    return FALSE;
}

u32 BoxMonHasItem(struct BoxPokemon *mon, enum Item item)
{
    u32 helditem;

    for(u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        helditem = GetBoxMonData(mon, MON_DATA_HELD_ITEM + i);
        if(item == helditem)
            return TRUE;
    }

    return FALSE;
}

u32 BoxMonHasItemHoldEffect(struct BoxPokemon *mon, enum HoldEffect holdEffect)
{
    u32 helditem;

    for(u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        helditem = GetBoxMonData(mon, MON_DATA_HELD_ITEM + i);
        if(GetItemHoldEffect(helditem) == holdEffect)
            return TRUE;
    }

    return FALSE;
}

u32 SwitchInCandidateHeldItemWithEffect(struct BattlePokemon switchinCandidate, enum HoldEffect holdEffect)
{
    enum Item item = ITEM_NONE;

    for (u32 i = 0; i < MAX_MON_ITEMS; i++)
    {
        item = switchinCandidate.items[i];
        if(GetItemHoldEffect(item) == holdEffect)
            return item;
    }
    return ITEM_NONE;
}
