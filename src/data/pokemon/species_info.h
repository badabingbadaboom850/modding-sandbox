#include "constants/abilities.h"
#include "constants/teaching_types.h"
#include "species_info/shared_dex_text.h"
#include "species_info/shared_front_pic_anims.h"

// Macros for ease of use.

#define EVOLUTION(...) (const struct Evolution[]) { __VA_ARGS__, { EVOLUTIONS_END }, }
#define CONDITIONS(...) ((const struct EvolutionParam[]) { __VA_ARGS__, {CONDITIONS_END} })

#define ANIM_FRAMES(...) (const union AnimCmd *const[]) { sAnim_GeneralFrame0, (const union AnimCmd[]) { __VA_ARGS__ ANIMCMD_END, }, }

#if P_FOOTPRINTS
#define FOOTPRINT(sprite) .footprint = gMonFootprint_## sprite,
#else
#define FOOTPRINT(sprite)
#endif

#if B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE
#define SHADOW(x, y, size)  .enemyShadowXOffset = x, .enemyShadowYOffset = y, .enemyShadowSize = size,
#define NO_SHADOW           .suppressEnemyShadow = TRUE,
#else
#define SHADOW(x, y, size)  .enemyShadowXOffset = 0, .enemyShadowYOffset = 0, .enemyShadowSize = 0,
#define NO_SHADOW           .suppressEnemyShadow = FALSE,
#endif

#define SIZE_32x32 1
#define SIZE_64x64 0

// Set .compressed = OW_GFX_COMPRESS
#define COMP OW_GFX_COMPRESS

#if OW_POKEMON_OBJECT_EVENTS
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
#define OVERWORLD_PAL(...)                                  \
    .overworldPalette = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPalette = DEFAULT_2(NULL, __VA_ARGS__),
#if P_GENDER_DIFFERENCES
#define OVERWORLD_PAL_FEMALE(...)                                 \
    .overworldPaletteFemale = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPaletteFemale = DEFAULT_2(NULL, __VA_ARGS__),
#else
#define OVERWORLD_PAL_FEMALE(...)
#endif //P_GENDER_DIFFERENCES
#else
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE

#define OVERWORLD_DATA(picTable, _size, shadow, _tracks, _anims)                                                                     \
{                                                                                                                                       \
    .tileTag = TAG_NONE,                                                                                                                \
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,                                                                                            \
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,                                                                                     \
    .size = (_size == SIZE_32x32 ? 512 : 2048),                                                                                         \
    .width = (_size == SIZE_32x32 ? 32 : 64),                                                                                           \
    .height = (_size == SIZE_32x32 ? 32 : 64),                                                                                          \
    .paletteSlot = PALSLOT_NPC_1,                                                                                                       \
    .shadowSize = shadow,                                                                                                               \
    .inanimate = FALSE,                                                                                                                 \
    .compressed = COMP,                                                                                                                 \
    .tracks = _tracks,                                                                                                                  \
    .oam = (_size == SIZE_32x32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_64x64),                                             \
    .subspriteTables = (_size == SIZE_32x32 ? sOamTables_32x32 : sOamTables_64x64),                                                     \
    .anims = _anims,                                                                                                                    \
    .images = picTable,                                                                                                                 \
}

#define OVERWORLD(objEventPic, _size, shadow, _tracks, _anims, ...)                                 \
    .overworldData = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),                   \
    OVERWORLD_PAL(__VA_ARGS__)

#if P_GENDER_DIFFERENCES
#define OVERWORLD_FEMALE(objEventPic, _size, shadow, _tracks, _anims, ...)                          \
    .overworldDataFemale = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),             \
    OVERWORLD_PAL_FEMALE(__VA_ARGS__)
#else
#define OVERWORLD_FEMALE(...)
#endif //P_GENDER_DIFFERENCES

#else
#define OVERWORLD(...)
#define OVERWORLD_FEMALE(...)
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_POKEMON_OBJECT_EVENTS

// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define MON_TYPES(type1, ...) { type1, DEFAULT(type1, __VA_ARGS__) }
#define MON_EGG_GROUPS(group1, ...) { group1, DEFAULT(group1, __VA_ARGS__) }

#define FLIP    0
#define NO_FLIP 1

const struct SpeciesInfo gSpeciesInfo[] =
{
    [SPECIES_NONE] =
    {
        .speciesName = _("??????????"),
        .cryId = CRY_PORYGON,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = gFallbackPokedexText,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_TwoFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(40, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(QuestionMark)
        SHADOW(-1, 0, SHADOW_SIZE_M)
    #if OW_POKEMON_OBJECT_EVENTS
        .overworldData = {
            .tileTag = TAG_NONE,
            .paletteTag = OBJ_EVENT_PAL_TAG_SUBSTITUTE,
            .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
            .size = 512,
            .width = 32,
            .height = 32,
            .paletteSlot = PALSLOT_NPC_1,
            .shadowSize = SHADOW_SIZE_M,
            .inanimate = FALSE,
            .compressed = COMP,
            .tracks = TRACKS_FOOT,
            .oam = &gObjectEventBaseOam_32x32,
            .subspriteTables = sOamTables_32x32,
            .anims = sAnimTable_Following,
            .images = sPicTable_Substitute,
        },
    #endif
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .eggMoveLearnset = sNoneEggMoveLearnset,
    },

    #include "species_info/gen_1_families.h"
    #include "species_info/gen_2_families.h"
    #include "species_info/gen_3_families.h"
    #include "species_info/gen_4_families.h"
    #include "species_info/gen_5_families.h"
    #include "species_info/gen_6_families.h"
    #include "species_info/gen_7_families.h"
    #include "species_info/gen_8_families.h"
    #include "species_info/gen_9_families.h"

    [SPECIES_EGG] =
    {
        .frontPic = gMonFrontPic_Egg,
        .frontPicSize = MON_COORDS_SIZE(24, 24),
        .frontPicYOffset = 20,
        .backPic = gMonFrontPic_Egg,
        .backPicSize = MON_COORDS_SIZE(24, 24),
        .backPicYOffset = 20,
        .palette = gMonPalette_Egg,
        .shinyPalette = gMonShinyPalette_Egg,
        .iconSprite = gMonIcon_Egg,
        .iconPalIndex = 1,
        .iconPalette = gMonIconPalette_Egg,
        .shinyIconPalette = gMonShinyIconPalette_Egg,
    },

    /* You may add any custom species below this point based on the following structure: */

#if P_FAMILY_RIKO
    [SPECIES_RIKO] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("Riko"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Its fluffy coat stores fairy\nenergy. It demands compliments,\nsnacks, and a dramatic entrance."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_Riko, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_Riko,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_Riko, .shinyPalette = gMonShinyPalette_Riko,
        .iconSprite = gMonIcon_Riko, .iconPalette = gMonIconPalette_Riko,
        .shinyIconPalette = gMonShinyIconPalette_Riko, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_Riko,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Riko,
            gShinyOverworldPalette_Riko
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_POM_PARTY_HAT, SPECIES_RIKO_PARTY}, {EVO_ITEM, ITEM_POM_SANTA_HAT, SPECIES_RIKO_SANTA}, {EVO_ITEM, ITEM_RIKOS_FEATHER_FAN, SPECIES_RIKO_TURKEY}, {EVO_ITEM, ITEM_RIKOS_LEAF_BUNDLE, SPECIES_RIKO_LEAVES}, {EVO_ITEM, ITEM_RIKOS_WITCH_HAT, SPECIES_RIKO_WITCH}, {EVO_ITEM, ITEM_RIKOS_BUTTERFLY_WINGS, SPECIES_RIKO_BUTTERFLY}, {EVO_ITEM, ITEM_RIKOS_HONEYCOMB, SPECIES_RIKO_BUG}, {EVO_ITEM, ITEM_POM_DRAGON_PLUSH, SPECIES_RIKO_DRAGON}, {EVO_ITEM, ITEM_RIKOS_BLACK_BELT, SPECIES_RIKO_FIGHTING}, {EVO_ITEM, ITEM_POM_TIARA, SPECIES_RIKO_PRINCESS}, {EVO_ITEM, ITEM_RIKOS_RAINCOAT, SPECIES_RIKO_RAINCOAT}, {EVO_ITEM, ITEM_RIKOS_BALLOON, SPECIES_RIKO_BALLOON}, {EVO_ITEM, ITEM_RIKOS_BLOOM, SPECIES_RIKO_FLOWER}, {EVO_ITEM, ITEM_RIKOS_COURAGE, SPECIES_RIKO_ECHO}, {EVO_ITEM, ITEM_RIKOS_WAND, SPECIES_RIKO_WING}, {EVO_ITEM, ITEM_GREEN_PEPPER, SPECIES_RIKO_FIRE}, {EVO_ITEM, ITEM_EEL_SUSHI, SPECIES_RIKO_ELECTRIC}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sRikoFormChangeTable,
    },
    [SPECIES_RIKO_BALLOON] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoBalloon"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Its fluffy coat stores fairy\nenergy. It demands compliments,\nsnacks, and a dramatic entrance."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoBalloon, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoBalloon,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoBalloon, .shinyPalette = gMonShinyPalette_RikoBalloon,
        .iconSprite = gMonIcon_RikoBalloon, .iconPalette = gMonIconPalette_RikoBalloon,
        .shinyIconPalette = gMonShinyIconPalette_RikoBalloon, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoBalloon,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoBalloon,
            gShinyOverworldPalette_RikoBalloon
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_HONEYCOMB, SPECIES_RIKO_BUG}, {EVO_ITEM, ITEM_POM_DRAGON_PLUSH, SPECIES_RIKO_DRAGON}, {EVO_ITEM, ITEM_RIKOS_BLACK_BELT, SPECIES_RIKO_FIGHTING}, {EVO_ITEM, ITEM_POM_TIARA, SPECIES_RIKO_PRINCESS}, {EVO_ITEM, ITEM_RIKOS_RAINCOAT, SPECIES_RIKO_RAINCOAT}, {EVO_ITEM, ITEM_RIKOS_BALLOON, SPECIES_RIKO}, {EVO_ITEM, ITEM_RIKOS_BLOOM, SPECIES_RIKO_FLOWER}, {EVO_ITEM, ITEM_RIKOS_COURAGE, SPECIES_RIKO_ECHO}, {EVO_ITEM, ITEM_RIKOS_WAND, SPECIES_RIKO_WING}, {EVO_ITEM, ITEM_GREEN_PEPPER, SPECIES_RIKO_FIRE}, {EVO_ITEM, ITEM_EEL_SUSHI, SPECIES_RIKO_ELECTRIC}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sRikoCostumeEntryTable,
    },
    [SPECIES_RIKO_RAINCOAT] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoRain"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Its fluffy coat stores fairy\nenergy. It demands compliments,\nsnacks, and a dramatic entrance."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoRaincoat, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoRaincoat,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoRaincoat, .shinyPalette = gMonShinyPalette_RikoRaincoat,
        .iconSprite = gMonIcon_RikoRaincoat, .iconPalette = gMonIconPalette_RikoRaincoat,
        .shinyIconPalette = gMonShinyIconPalette_RikoRaincoat, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoRaincoat,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoRaincoat,
            gShinyOverworldPalette_RikoRaincoat
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_HONEYCOMB, SPECIES_RIKO_BUG}, {EVO_ITEM, ITEM_POM_DRAGON_PLUSH, SPECIES_RIKO_DRAGON}, {EVO_ITEM, ITEM_RIKOS_BLACK_BELT, SPECIES_RIKO_FIGHTING}, {EVO_ITEM, ITEM_POM_TIARA, SPECIES_RIKO_PRINCESS}, {EVO_ITEM, ITEM_RIKOS_RAINCOAT, SPECIES_RIKO}, {EVO_ITEM, ITEM_RIKOS_BLOOM, SPECIES_RIKO_FLOWER}, {EVO_ITEM, ITEM_RIKOS_COURAGE, SPECIES_RIKO_ECHO}, {EVO_ITEM, ITEM_RIKOS_WAND, SPECIES_RIKO_WING}, {EVO_ITEM, ITEM_GREEN_PEPPER, SPECIES_RIKO_FIRE}, {EVO_ITEM, ITEM_EEL_SUSHI, SPECIES_RIKO_ELECTRIC}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sRikoCostumeEntryTable,
    },
    [SPECIES_RIKO_BUTTERFLY] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoFlutter"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Its fluffy coat stores fairy\nenergy. It demands compliments,\nsnacks, and a dramatic entrance."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoButterfly, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoButterfly,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoButterfly, .shinyPalette = gMonShinyPalette_RikoButterfly,
        .iconSprite = gMonIcon_RikoButterfly, .iconPalette = gMonIconPalette_RikoButterfly,
        .shinyIconPalette = gMonShinyIconPalette_RikoButterfly, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoButterfly,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_RikoButterfly,
            gShinyOverworldPalette_RikoButterfly
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_HONEYCOMB, SPECIES_RIKO_BUG}, {EVO_ITEM, ITEM_POM_DRAGON_PLUSH, SPECIES_RIKO_DRAGON}, {EVO_ITEM, ITEM_RIKOS_BLACK_BELT, SPECIES_RIKO_FIGHTING}, {EVO_ITEM, ITEM_POM_TIARA, SPECIES_RIKO_PRINCESS}, {EVO_ITEM, ITEM_RIKOS_BUTTERFLY_WINGS, SPECIES_RIKO}, {EVO_ITEM, ITEM_RIKOS_BLOOM, SPECIES_RIKO_FLOWER}, {EVO_ITEM, ITEM_RIKOS_COURAGE, SPECIES_RIKO_ECHO}, {EVO_ITEM, ITEM_RIKOS_WAND, SPECIES_RIKO_WING}, {EVO_ITEM, ITEM_GREEN_PEPPER, SPECIES_RIKO_FIRE}, {EVO_ITEM, ITEM_EEL_SUSHI, SPECIES_RIKO_ELECTRIC}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sRikoCostumeEntryTable,
    },
    [SPECIES_RIKO_WITCH] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoWitch"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Its fluffy coat stores fairy\nenergy. It demands compliments,\nsnacks, and a dramatic entrance."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoWitch, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoWitch,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoWitch, .shinyPalette = gMonShinyPalette_RikoWitch,
        .iconSprite = gMonIcon_RikoWitch, .iconPalette = gMonIconPalette_RikoWitch,
        .shinyIconPalette = gMonShinyIconPalette_RikoWitch, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoWitch,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_RikoWitch,
            gShinyOverworldPalette_RikoWitch
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_HONEYCOMB, SPECIES_RIKO_BUG}, {EVO_ITEM, ITEM_POM_DRAGON_PLUSH, SPECIES_RIKO_DRAGON}, {EVO_ITEM, ITEM_RIKOS_BLACK_BELT, SPECIES_RIKO_FIGHTING}, {EVO_ITEM, ITEM_POM_TIARA, SPECIES_RIKO_PRINCESS}, {EVO_ITEM, ITEM_RIKOS_WITCH_HAT, SPECIES_RIKO}, {EVO_ITEM, ITEM_RIKOS_BLOOM, SPECIES_RIKO_FLOWER}, {EVO_ITEM, ITEM_RIKOS_COURAGE, SPECIES_RIKO_ECHO}, {EVO_ITEM, ITEM_RIKOS_WAND, SPECIES_RIKO_WING}, {EVO_ITEM, ITEM_GREEN_PEPPER, SPECIES_RIKO_FIRE}, {EVO_ITEM, ITEM_EEL_SUSHI, SPECIES_RIKO_ELECTRIC}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sRikoCostumeEntryTable,
    },
    [SPECIES_RIKO_PARTY] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoParty"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Its fluffy coat stores fairy\nenergy. It demands compliments,\nsnacks, and a dramatic entrance."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoParty, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoParty,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoParty, .shinyPalette = gMonShinyPalette_RikoParty,
        .iconSprite = gMonIcon_RikoParty, .iconPalette = gMonIconPalette_RikoParty,
        .shinyIconPalette = gMonShinyIconPalette_RikoParty, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoParty,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_RikoParty,
            gShinyOverworldPalette_RikoParty
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_HONEYCOMB, SPECIES_RIKO_BUG}, {EVO_ITEM, ITEM_POM_DRAGON_PLUSH, SPECIES_RIKO_DRAGON}, {EVO_ITEM, ITEM_RIKOS_BLACK_BELT, SPECIES_RIKO_FIGHTING}, {EVO_ITEM, ITEM_POM_TIARA, SPECIES_RIKO_PRINCESS}, {EVO_ITEM, ITEM_POM_PARTY_HAT, SPECIES_RIKO}, {EVO_ITEM, ITEM_RIKOS_BLOOM, SPECIES_RIKO_FLOWER}, {EVO_ITEM, ITEM_RIKOS_COURAGE, SPECIES_RIKO_ECHO}, {EVO_ITEM, ITEM_RIKOS_WAND, SPECIES_RIKO_WING}, {EVO_ITEM, ITEM_GREEN_PEPPER, SPECIES_RIKO_FIRE}, {EVO_ITEM, ITEM_EEL_SUSHI, SPECIES_RIKO_ELECTRIC}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sRikoCostumeEntryTable,
    },
    [SPECIES_RIKO_SANTA] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoSanta"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Its fluffy coat stores fairy\nenergy. It demands compliments,\nsnacks, and a dramatic entrance."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoSanta, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoSanta,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoSanta, .shinyPalette = gMonShinyPalette_RikoSanta,
        .iconSprite = gMonIcon_RikoSanta, .iconPalette = gMonIconPalette_RikoSanta,
        .shinyIconPalette = gMonShinyIconPalette_RikoSanta, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoSanta,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_RikoSanta,
            gShinyOverworldPalette_RikoSanta
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_HONEYCOMB, SPECIES_RIKO_BUG}, {EVO_ITEM, ITEM_POM_DRAGON_PLUSH, SPECIES_RIKO_DRAGON}, {EVO_ITEM, ITEM_RIKOS_BLACK_BELT, SPECIES_RIKO_FIGHTING}, {EVO_ITEM, ITEM_POM_TIARA, SPECIES_RIKO_PRINCESS}, {EVO_ITEM, ITEM_POM_SANTA_HAT, SPECIES_RIKO}, {EVO_ITEM, ITEM_RIKOS_BLOOM, SPECIES_RIKO_FLOWER}, {EVO_ITEM, ITEM_RIKOS_COURAGE, SPECIES_RIKO_ECHO}, {EVO_ITEM, ITEM_RIKOS_WAND, SPECIES_RIKO_WING}, {EVO_ITEM, ITEM_GREEN_PEPPER, SPECIES_RIKO_FIRE}, {EVO_ITEM, ITEM_EEL_SUSHI, SPECIES_RIKO_ELECTRIC}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sRikoCostumeEntryTable,
    },
    [SPECIES_RIKO_TURKEY] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoTurkey"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Its fluffy coat stores fairy\nenergy. It demands compliments,\nsnacks, and a dramatic entrance."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoTurkey, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoTurkey,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoTurkey, .shinyPalette = gMonShinyPalette_RikoTurkey,
        .iconSprite = gMonIcon_RikoTurkey, .iconPalette = gMonIconPalette_RikoTurkey,
        .shinyIconPalette = gMonShinyIconPalette_RikoTurkey, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoTurkey,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_RikoTurkey,
            gShinyOverworldPalette_RikoTurkey
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_HONEYCOMB, SPECIES_RIKO_BUG}, {EVO_ITEM, ITEM_POM_DRAGON_PLUSH, SPECIES_RIKO_DRAGON}, {EVO_ITEM, ITEM_RIKOS_BLACK_BELT, SPECIES_RIKO_FIGHTING}, {EVO_ITEM, ITEM_POM_TIARA, SPECIES_RIKO_PRINCESS}, {EVO_ITEM, ITEM_RIKOS_FEATHER_FAN, SPECIES_RIKO}, {EVO_ITEM, ITEM_RIKOS_BLOOM, SPECIES_RIKO_FLOWER}, {EVO_ITEM, ITEM_RIKOS_COURAGE, SPECIES_RIKO_ECHO}, {EVO_ITEM, ITEM_RIKOS_WAND, SPECIES_RIKO_WING}, {EVO_ITEM, ITEM_GREEN_PEPPER, SPECIES_RIKO_FIRE}, {EVO_ITEM, ITEM_EEL_SUSHI, SPECIES_RIKO_ELECTRIC}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sRikoCostumeEntryTable,
    },
    [SPECIES_RIKO_LEAVES] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoLeaves"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Its fluffy coat stores fairy\nenergy. It demands compliments,\nsnacks, and a dramatic entrance."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoLeaves, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoLeaves,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoLeaves, .shinyPalette = gMonShinyPalette_RikoLeaves,
        .iconSprite = gMonIcon_RikoLeaves, .iconPalette = gMonIconPalette_RikoLeaves,
        .shinyIconPalette = gMonShinyIconPalette_RikoLeaves, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoLeaves,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_RikoLeaves,
            gShinyOverworldPalette_RikoLeaves
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_HONEYCOMB, SPECIES_RIKO_BUG}, {EVO_ITEM, ITEM_POM_DRAGON_PLUSH, SPECIES_RIKO_DRAGON}, {EVO_ITEM, ITEM_RIKOS_BLACK_BELT, SPECIES_RIKO_FIGHTING}, {EVO_ITEM, ITEM_POM_TIARA, SPECIES_RIKO_PRINCESS}, {EVO_ITEM, ITEM_RIKOS_LEAF_BUNDLE, SPECIES_RIKO}, {EVO_ITEM, ITEM_RIKOS_BLOOM, SPECIES_RIKO_FLOWER}, {EVO_ITEM, ITEM_RIKOS_COURAGE, SPECIES_RIKO_ECHO}, {EVO_ITEM, ITEM_RIKOS_WAND, SPECIES_RIKO_WING}, {EVO_ITEM, ITEM_GREEN_PEPPER, SPECIES_RIKO_FIRE}, {EVO_ITEM, ITEM_EEL_SUSHI, SPECIES_RIKO_ELECTRIC}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sRikoCostumeEntryTable,
    },
    [SPECIES_RIKO_PRINCESS] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoRoyal"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Its fluffy coat stores fairy\nenergy. It demands compliments,\nsnacks, and a dramatic entrance."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoPrincess, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoPrincess,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoPrincess, .shinyPalette = gMonShinyPalette_RikoPrincess,
        .iconSprite = gMonIcon_RikoPrincess, .iconPalette = gMonIconPalette_RikoPrincess,
        .shinyIconPalette = gMonShinyIconPalette_RikoPrincess, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoPrincess,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoPrincess,
            gShinyOverworldPalette_RikoPrincess
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_HONEYCOMB, SPECIES_RIKO_BUG}, {EVO_ITEM, ITEM_POM_DRAGON_PLUSH, SPECIES_RIKO_DRAGON}, {EVO_ITEM, ITEM_RIKOS_BLACK_BELT, SPECIES_RIKO_FIGHTING}, {EVO_ITEM, ITEM_RIKOS_RAINCOAT, SPECIES_RIKO_RAINCOAT}, {EVO_ITEM, ITEM_POM_TIARA, SPECIES_RIKO}, {EVO_ITEM, ITEM_RIKOS_BLOOM, SPECIES_RIKO_FLOWER}, {EVO_ITEM, ITEM_RIKOS_COURAGE, SPECIES_RIKO_ECHO}, {EVO_ITEM, ITEM_RIKOS_WAND, SPECIES_RIKO_WING}, {EVO_ITEM, ITEM_GREEN_PEPPER, SPECIES_RIKO_FIRE}, {EVO_ITEM, ITEM_EEL_SUSHI, SPECIES_RIKO_ELECTRIC}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sRikoCostumeEntryTable,
    },
    [SPECIES_RIKO_ASPECT_MIND] =
    {
        .baseHP = 95, .baseAttack = 65, .baseDefense = 80, .baseSpeed = 115,
        .baseSpAttack = 120, .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_PSYCHIC, TYPE_FAIRY), .catchRate = 0, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_SYNCHRONIZE, ABILITY_NONE, ABILITY_SYNCHRONIZE },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoMind"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("An echo of Riko\ncalled home by her family.\nIts aura holds her mind."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_Riko, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_Riko,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoAspectMind, .shinyPalette = gMonPalette_RikoAspectMind,
        .iconSprite = gMonIcon_Riko, .iconPalette = gMonIconPalette_RikoAspectMind,
        .shinyIconPalette = gMonIconPalette_RikoAspectMind, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_Riko,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoAspectMind,
            gOverworldPalette_RikoAspectMind
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
    },
    [SPECIES_RIKO_ASPECT_BODY] =
    {
        .baseHP = 115, .baseAttack = 115, .baseDefense = 110, .baseSpeed = 80,
        .baseSpAttack = 65, .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 0, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_BATTLE_ARMOR, ABILITY_NONE, ABILITY_BATTLE_ARMOR },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoBody"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("An echo of Riko\ncalled home by her family.\nIts aura holds her body."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_Riko, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_Riko,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoAspectBody, .shinyPalette = gMonPalette_RikoAspectBody,
        .iconSprite = gMonIcon_Riko, .iconPalette = gMonIconPalette_RikoAspectBody,
        .shinyIconPalette = gMonIconPalette_RikoAspectBody, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_Riko,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoAspectBody,
            gOverworldPalette_RikoAspectBody
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
    },
    [SPECIES_RIKO_ASPECT_SOUL] =
    {
        .baseHP = 110, .baseAttack = 65, .baseDefense = 90, .baseSpeed = 95,
        .baseSpAttack = 110, .baseSpDefense = 120,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 0, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_CUTE_CHARM },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoSoul"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("An echo of Riko\ncalled home by her family.\nIts aura holds her soul."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_Riko, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_Riko,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoAspectSoul, .shinyPalette = gMonPalette_RikoAspectSoul,
        .iconSprite = gMonIcon_Riko, .iconPalette = gMonIconPalette_RikoAspectSoul,
        .shinyIconPalette = gMonIconPalette_RikoAspectSoul, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_Riko,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoAspectSoul,
            gOverworldPalette_RikoAspectSoul
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
    },
    [SPECIES_RIKO_FLOWER] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("FlowerRiko"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Garden Floof"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Flowers rest in its soft coat.\nIt tends small gardens with\nits sisters, then naps nearby."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoFlower, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoFlower,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoFlower, .shinyPalette = gMonShinyPalette_RikoFlower,
        .iconSprite = gMonIcon_RikoFlower, .iconPalette = gMonIconPalette_RikoFlower,
        .shinyIconPalette = gMonShinyIconPalette_RikoFlower, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoFlower,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoFlower,
            gShinyOverworldPalette_RikoFlower
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoFlowerLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_BLOOM, SPECIES_RIKO}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },
#if P_GEN_9_MEGA_EVOLUTIONS
    [SPECIES_MEGA_RIKO] =
    {
        .baseHP = 90, .baseAttack = 85, .baseDefense = 95, .baseSpeed = 130,
        .baseSpAttack = 135, .baseSpDefense = 125,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 300,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_PIXILATE, ABILITY_PIXILATE, ABILITY_PIXILATE },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("Riko"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("When it Mega Evolves, its three\nheads share one mighty, fluffy\nroar."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoMega, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoMega,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoMega, .shinyPalette = gMonShinyPalette_RikoMega,
        .iconSprite = gMonIcon_Riko, .iconPalette = gMonIconPalette_Riko,
        .shinyIconPalette = gMonShinyIconPalette_Riko, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        .isMegaEvolution = TRUE,
        OVERWORLD(
            sPicTable_Riko,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Riko,
            gShinyOverworldPalette_Riko
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sTrioSpiritMegaReturnTable,
    },
#endif
    [SPECIES_RIKO_WING] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_FLYING), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoWing"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Winged Floof"), .height = 8, .weight = 100,
        .description = COMPOUND_STRING("Its tiny wings sparkle when it\n"
                                       "spreads them. A trail of twinkles\n"
                                       "follows wherever it flies."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoWing, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoWing,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoWing, .shinyPalette = gMonShinyPalette_RikoWing,
        .iconSprite = gMonIcon_RikoWing, .iconPalette = gMonIconPalette_RikoWing,
        .shinyIconPalette = gMonShinyIconPalette_RikoWing, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoWing,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoWing,
            gShinyOverworldPalette_RikoWing
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_BLUE_BRUSH, SPECIES_RIKO}, {EVO_ITEM, ITEM_RIKOS_COURAGE, SPECIES_RIKO_ECHO}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },
    [SPECIES_RIKO_ECHO] =
    {
        .baseHP = 95, .baseAttack = 80, .baseDefense = 90, .baseSpeed = 110,
        .baseSpAttack = 110, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoEcho"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Brave Echo"), .height = 8, .weight = 100,
        .description = COMPOUND_STRING("When Riko called, her courage\n"
                                       "answered. Two voices share one\n"
                                       "heart, keeping her sisters safe."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoEcho, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoEcho,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoEcho, .shinyPalette = gMonShinyPalette_RikoEcho,
        .iconSprite = gMonIcon_RikoEcho, .iconPalette = gMonIconPalette_RikoEcho,
        .shinyIconPalette = gMonShinyIconPalette_RikoEcho, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoEcho,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoEcho,
            gShinyOverworldPalette_RikoEcho
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoEchoLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_COURAGE, SPECIES_RIKO}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },
    [SPECIES_RIKO_SPIRIT] =
    {
        .baseHP = 115, .baseAttack = 115, .baseDefense = 85, .baseSpeed = 100,
        .baseSpAttack = 90, .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_FIRE, TYPE_FAIRY), .catchRate = 3, .expYield = 290,
        .evYield_HP = 1, .evYield_Attack = 2, .genderRatio = MON_FEMALE,
        .eggCycles = 80, .friendship = 35, .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PRESSURE, ABILITY_NONE, ABILITY_FLASH_FIRE },
        .bodyColor = BODY_COLOR_BLACK, .speciesName = _("RikoSpirit"), .cryId = CRY_ENTEI,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Cerberus"), .height = 15, .weight = 420,
        .description = COMPOUND_STRING("A spirit born from Riko.\nIts three heads guard its\nfamily with a blazing roar."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoSpirit, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoSpirit,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoSpirit, .shinyPalette = gMonShinyPalette_RikoSpirit,
        .iconSprite = gMonIcon_RikoSpirit, .iconPalette = gMonIconPalette_RikoSpirit,
        .shinyIconPalette = gMonShinyIconPalette_RikoSpirit, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_M)
        OVERWORLD(
            sPicTable_RikoSpirit,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoSpirit,
            gShinyOverworldPalette_RikoSpirit
        )
        .isSubLegendary = TRUE, .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoSpiritLevelUpLearnset,
        FOOTPRINT(Riko)
    },
#endif
#if P_FAMILY_BIJUU
    [SPECIES_BIJUU] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 220, .evYield_Speed = 3,
        .genderRatio = MON_FEMALE, .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("Bijuu"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It studies every creature nearby,\nthen copies their tricks before\nthey know they were observed."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_Bijuu, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_Bijuu,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_Bijuu, .shinyPalette = gMonShinyPalette_Bijuu,
        .iconSprite = gMonIcon_Bijuu, .iconPalette = gMonIconPalette_Bijuu,
        .shinyIconPalette = gMonShinyIconPalette_Bijuu, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_Bijuu,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Bijuu,
            gShinyOverworldPalette_Bijuu
        )
        .levelUpLearnset = sMeowthLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable, .formChangeTable = sBijuuFormChangeTable,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_COCOA_SILVER_BOW, SPECIES_BIJUU_GALA}, {EVO_ITEM, ITEM_COCOA_GIFT_BOX, SPECIES_BIJUU_PRESENT}, {EVO_ITEM, ITEM_COCOAS_CHEF_HAT, SPECIES_BIJUU_CHEF}, {EVO_ITEM, ITEM_COCOAS_KNIT_SET, SPECIES_BIJUU_SWEATER}, {EVO_ITEM, ITEM_BIJUUS_VAMPIRE_CAPE, SPECIES_BIJUU_VAMPIRE}, {EVO_ITEM, ITEM_BIJUUS_SPACE_HELMET, SPECIES_BIJUU_ASTRONAUT}, {EVO_ITEM, ITEM_COCOAS_SHINY_PEBBLE, SPECIES_BIJUU_ROCK}, {EVO_ITEM, ITEM_COCOAS_SNEAKY_CAPE, SPECIES_BIJUU_DARK}, {EVO_ITEM, ITEM_COCOA_TOAST, SPECIES_BIJUU_BREAD}, {EVO_ITEM, ITEM_COCOAS_DETECTIVE_KIT, SPECIES_BIJUU_DETECTIVE}, {EVO_ITEM, ITEM_BIJUUS_BOX, SPECIES_BIJUU_BOX}, {EVO_ITEM, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER}, {EVO_ITEM, ITEM_BIJUUS_FISH_TOY, SPECIES_BIJUU_PSYCHIC}, {EVO_ITEM, ITEM_MOUSE_TOY, SPECIES_BIJUU_GHOST}, {EVO_ITEM, ITEM_FROZEN_FISH, SPECIES_BIJUU_ICE}, {EVO_ITEM, ITEM_TOXIC_MOUSE, SPECIES_BIJUU_POISON}),
    },
    [SPECIES_BIJUU_BOX] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 220, .evYield_Speed = 3,
        .genderRatio = MON_FEMALE, .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuBox"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It studies every creature nearby,\nthen copies their tricks before\nthey know they were observed."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuBox, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuBox,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuBox, .shinyPalette = gMonShinyPalette_BijuuBox,
        .iconSprite = gMonIcon_BijuuBox, .iconPalette = gMonIconPalette_BijuuBox,
        .shinyIconPalette = gMonShinyIconPalette_BijuuBox, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuBox,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuBox,
            gShinyOverworldPalette_BijuuBox
        )
        .levelUpLearnset = sMeowthLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable, .formChangeTable = sBijuuCostumeEntryTable,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_COCOAS_SHINY_PEBBLE, SPECIES_BIJUU_ROCK}, {EVO_ITEM, ITEM_COCOAS_SNEAKY_CAPE, SPECIES_BIJUU_DARK}, {EVO_ITEM, ITEM_COCOA_TOAST, SPECIES_BIJUU_BREAD}, {EVO_ITEM, ITEM_COCOAS_DETECTIVE_KIT, SPECIES_BIJUU_DETECTIVE}, {EVO_ITEM, ITEM_BIJUUS_BOX, SPECIES_BIJUU}, {EVO_ITEM, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER}, {EVO_ITEM, ITEM_BIJUUS_FISH_TOY, SPECIES_BIJUU_PSYCHIC}, {EVO_ITEM, ITEM_MOUSE_TOY, SPECIES_BIJUU_GHOST}, {EVO_ITEM, ITEM_FROZEN_FISH, SPECIES_BIJUU_ICE}, {EVO_ITEM, ITEM_TOXIC_MOUSE, SPECIES_BIJUU_POISON}),
    },
    [SPECIES_BIJUU_DETECTIVE] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 220, .evYield_Speed = 3,
        .genderRatio = MON_FEMALE, .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuSleuth"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It studies every creature nearby,\nthen copies their tricks before\nthey know they were observed."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuDetective, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuDetective,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuDetective, .shinyPalette = gMonShinyPalette_BijuuDetective,
        .iconSprite = gMonIcon_BijuuDetective, .iconPalette = gMonIconPalette_BijuuDetective,
        .shinyIconPalette = gMonShinyIconPalette_BijuuDetective, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuDetective,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuDetective,
            gShinyOverworldPalette_BijuuDetective
        )
        .levelUpLearnset = sMeowthLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable, .formChangeTable = sBijuuCostumeEntryTable,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_COCOAS_SHINY_PEBBLE, SPECIES_BIJUU_ROCK}, {EVO_ITEM, ITEM_COCOAS_SNEAKY_CAPE, SPECIES_BIJUU_DARK}, {EVO_ITEM, ITEM_COCOA_TOAST, SPECIES_BIJUU_BREAD}, {EVO_ITEM, ITEM_COCOAS_DETECTIVE_KIT, SPECIES_BIJUU}, {EVO_ITEM, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER}, {EVO_ITEM, ITEM_BIJUUS_FISH_TOY, SPECIES_BIJUU_PSYCHIC}, {EVO_ITEM, ITEM_MOUSE_TOY, SPECIES_BIJUU_GHOST}, {EVO_ITEM, ITEM_FROZEN_FISH, SPECIES_BIJUU_ICE}, {EVO_ITEM, ITEM_TOXIC_MOUSE, SPECIES_BIJUU_POISON}),
    },
    [SPECIES_BIJUU_ASTRONAUT] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 220, .evYield_Speed = 3,
        .genderRatio = MON_FEMALE, .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuSpace"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It studies every creature nearby,\nthen copies their tricks before\nthey know they were observed."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuAstronaut, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuAstronaut,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuAstronaut, .shinyPalette = gMonShinyPalette_BijuuAstronaut,
        .iconSprite = gMonIcon_BijuuAstronaut, .iconPalette = gMonIconPalette_BijuuAstronaut,
        .shinyIconPalette = gMonShinyIconPalette_BijuuAstronaut, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuAstronaut,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuAstronaut,
            gShinyOverworldPalette_BijuuAstronaut
        )
        .levelUpLearnset = sMeowthLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable, .formChangeTable = sBijuuCostumeEntryTable,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_COCOAS_SHINY_PEBBLE, SPECIES_BIJUU_ROCK}, {EVO_ITEM, ITEM_COCOAS_SNEAKY_CAPE, SPECIES_BIJUU_DARK}, {EVO_ITEM, ITEM_COCOA_TOAST, SPECIES_BIJUU_BREAD}, {EVO_ITEM, ITEM_BIJUUS_SPACE_HELMET, SPECIES_BIJUU}, {EVO_ITEM, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER}, {EVO_ITEM, ITEM_BIJUUS_FISH_TOY, SPECIES_BIJUU_PSYCHIC}, {EVO_ITEM, ITEM_MOUSE_TOY, SPECIES_BIJUU_GHOST}, {EVO_ITEM, ITEM_FROZEN_FISH, SPECIES_BIJUU_ICE}, {EVO_ITEM, ITEM_TOXIC_MOUSE, SPECIES_BIJUU_POISON}),
    },
    [SPECIES_BIJUU_VAMPIRE] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 220, .evYield_Speed = 3,
        .genderRatio = MON_FEMALE, .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuVamp"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It studies every creature nearby,\nthen copies their tricks before\nthey know they were observed."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuVampire, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuVampire,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuVampire, .shinyPalette = gMonShinyPalette_BijuuVampire,
        .iconSprite = gMonIcon_BijuuVampire, .iconPalette = gMonIconPalette_BijuuVampire,
        .shinyIconPalette = gMonShinyIconPalette_BijuuVampire, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuVampire,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuVampire,
            gShinyOverworldPalette_BijuuVampire
        )
        .levelUpLearnset = sMeowthLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable, .formChangeTable = sBijuuCostumeEntryTable,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_COCOAS_SHINY_PEBBLE, SPECIES_BIJUU_ROCK}, {EVO_ITEM, ITEM_COCOAS_SNEAKY_CAPE, SPECIES_BIJUU_DARK}, {EVO_ITEM, ITEM_COCOA_TOAST, SPECIES_BIJUU_BREAD}, {EVO_ITEM, ITEM_BIJUUS_VAMPIRE_CAPE, SPECIES_BIJUU}, {EVO_ITEM, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER}, {EVO_ITEM, ITEM_BIJUUS_FISH_TOY, SPECIES_BIJUU_PSYCHIC}, {EVO_ITEM, ITEM_MOUSE_TOY, SPECIES_BIJUU_GHOST}, {EVO_ITEM, ITEM_FROZEN_FISH, SPECIES_BIJUU_ICE}, {EVO_ITEM, ITEM_TOXIC_MOUSE, SPECIES_BIJUU_POISON}),
    },
    [SPECIES_BIJUU_GALA] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 220, .evYield_Speed = 3,
        .genderRatio = MON_FEMALE, .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuGala"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It studies every creature nearby,\nthen copies their tricks before\nthey know they were observed."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuGala, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuGala,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuGala, .shinyPalette = gMonShinyPalette_BijuuGala,
        .iconSprite = gMonIcon_BijuuGala, .iconPalette = gMonIconPalette_BijuuGala,
        .shinyIconPalette = gMonShinyIconPalette_BijuuGala, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuGala,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuGala,
            gShinyOverworldPalette_BijuuGala
        )
        .levelUpLearnset = sMeowthLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable, .formChangeTable = sBijuuCostumeEntryTable,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_COCOAS_SHINY_PEBBLE, SPECIES_BIJUU_ROCK}, {EVO_ITEM, ITEM_COCOAS_SNEAKY_CAPE, SPECIES_BIJUU_DARK}, {EVO_ITEM, ITEM_COCOA_TOAST, SPECIES_BIJUU_BREAD}, {EVO_ITEM, ITEM_COCOA_SILVER_BOW, SPECIES_BIJUU}, {EVO_ITEM, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER}, {EVO_ITEM, ITEM_BIJUUS_FISH_TOY, SPECIES_BIJUU_PSYCHIC}, {EVO_ITEM, ITEM_MOUSE_TOY, SPECIES_BIJUU_GHOST}, {EVO_ITEM, ITEM_FROZEN_FISH, SPECIES_BIJUU_ICE}, {EVO_ITEM, ITEM_TOXIC_MOUSE, SPECIES_BIJUU_POISON}),
    },
    [SPECIES_BIJUU_PRESENT] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 220, .evYield_Speed = 3,
        .genderRatio = MON_FEMALE, .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuGift"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It studies every creature nearby,\nthen copies their tricks before\nthey know they were observed."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuPresent, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuPresent,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuPresent, .shinyPalette = gMonShinyPalette_BijuuPresent,
        .iconSprite = gMonIcon_BijuuPresent, .iconPalette = gMonIconPalette_BijuuPresent,
        .shinyIconPalette = gMonShinyIconPalette_BijuuPresent, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuPresent,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuPresent,
            gShinyOverworldPalette_BijuuPresent
        )
        .levelUpLearnset = sMeowthLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable, .formChangeTable = sBijuuCostumeEntryTable,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_COCOAS_SHINY_PEBBLE, SPECIES_BIJUU_ROCK}, {EVO_ITEM, ITEM_COCOAS_SNEAKY_CAPE, SPECIES_BIJUU_DARK}, {EVO_ITEM, ITEM_COCOA_TOAST, SPECIES_BIJUU_BREAD}, {EVO_ITEM, ITEM_COCOA_GIFT_BOX, SPECIES_BIJUU}, {EVO_ITEM, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER}, {EVO_ITEM, ITEM_BIJUUS_FISH_TOY, SPECIES_BIJUU_PSYCHIC}, {EVO_ITEM, ITEM_MOUSE_TOY, SPECIES_BIJUU_GHOST}, {EVO_ITEM, ITEM_FROZEN_FISH, SPECIES_BIJUU_ICE}, {EVO_ITEM, ITEM_TOXIC_MOUSE, SPECIES_BIJUU_POISON}),
    },
    [SPECIES_BIJUU_CHEF] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 220, .evYield_Speed = 3,
        .genderRatio = MON_FEMALE, .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuChef"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It studies every creature nearby,\nthen copies their tricks before\nthey know they were observed."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuChef, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuChef,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuChef, .shinyPalette = gMonShinyPalette_BijuuChef,
        .iconSprite = gMonIcon_BijuuChef, .iconPalette = gMonIconPalette_BijuuChef,
        .shinyIconPalette = gMonShinyIconPalette_BijuuChef, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuChef,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuChef,
            gShinyOverworldPalette_BijuuChef
        )
        .levelUpLearnset = sMeowthLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable, .formChangeTable = sBijuuCostumeEntryTable,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_COCOAS_SHINY_PEBBLE, SPECIES_BIJUU_ROCK}, {EVO_ITEM, ITEM_COCOAS_SNEAKY_CAPE, SPECIES_BIJUU_DARK}, {EVO_ITEM, ITEM_COCOA_TOAST, SPECIES_BIJUU_BREAD}, {EVO_ITEM, ITEM_COCOAS_CHEF_HAT, SPECIES_BIJUU}, {EVO_ITEM, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER}, {EVO_ITEM, ITEM_BIJUUS_FISH_TOY, SPECIES_BIJUU_PSYCHIC}, {EVO_ITEM, ITEM_MOUSE_TOY, SPECIES_BIJUU_GHOST}, {EVO_ITEM, ITEM_FROZEN_FISH, SPECIES_BIJUU_ICE}, {EVO_ITEM, ITEM_TOXIC_MOUSE, SPECIES_BIJUU_POISON}),
    },
    [SPECIES_BIJUU_SWEATER] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 220, .evYield_Speed = 3,
        .genderRatio = MON_FEMALE, .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuKnit"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It studies every creature nearby,\nthen copies their tricks before\nthey know they were observed."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuSweater, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuSweater,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuSweater, .shinyPalette = gMonShinyPalette_BijuuSweater,
        .iconSprite = gMonIcon_BijuuSweater, .iconPalette = gMonIconPalette_BijuuSweater,
        .shinyIconPalette = gMonShinyIconPalette_BijuuSweater, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuSweater,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuSweater,
            gShinyOverworldPalette_BijuuSweater
        )
        .levelUpLearnset = sMeowthLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable, .formChangeTable = sBijuuCostumeEntryTable,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_COCOAS_SHINY_PEBBLE, SPECIES_BIJUU_ROCK}, {EVO_ITEM, ITEM_COCOAS_SNEAKY_CAPE, SPECIES_BIJUU_DARK}, {EVO_ITEM, ITEM_COCOA_TOAST, SPECIES_BIJUU_BREAD}, {EVO_ITEM, ITEM_COCOAS_KNIT_SET, SPECIES_BIJUU}, {EVO_ITEM, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER}, {EVO_ITEM, ITEM_BIJUUS_FISH_TOY, SPECIES_BIJUU_PSYCHIC}, {EVO_ITEM, ITEM_MOUSE_TOY, SPECIES_BIJUU_GHOST}, {EVO_ITEM, ITEM_FROZEN_FISH, SPECIES_BIJUU_ICE}, {EVO_ITEM, ITEM_TOXIC_MOUSE, SPECIES_BIJUU_POISON}),
    },
    [SPECIES_BIJUU_BREAD] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 220, .evYield_Speed = 3,
        .genderRatio = MON_FEMALE, .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuToast"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It studies every creature nearby,\nthen copies their tricks before\nthey know they were observed."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuBread, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuBread,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuBread, .shinyPalette = gMonShinyPalette_BijuuBread,
        .iconSprite = gMonIcon_BijuuBread, .iconPalette = gMonIconPalette_BijuuBread,
        .shinyIconPalette = gMonShinyIconPalette_BijuuBread, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuBread,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuBread,
            gShinyOverworldPalette_BijuuBread
        )
        .levelUpLearnset = sMeowthLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable, .formChangeTable = sBijuuCostumeEntryTable,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_COCOAS_SHINY_PEBBLE, SPECIES_BIJUU_ROCK}, {EVO_ITEM, ITEM_COCOAS_SNEAKY_CAPE, SPECIES_BIJUU_DARK}, {EVO_ITEM, ITEM_COCOAS_DETECTIVE_KIT, SPECIES_BIJUU_DETECTIVE}, {EVO_ITEM, ITEM_COCOA_TOAST, SPECIES_BIJUU}, {EVO_ITEM, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER}, {EVO_ITEM, ITEM_BIJUUS_FISH_TOY, SPECIES_BIJUU_PSYCHIC}, {EVO_ITEM, ITEM_MOUSE_TOY, SPECIES_BIJUU_GHOST}, {EVO_ITEM, ITEM_FROZEN_FISH, SPECIES_BIJUU_ICE}, {EVO_ITEM, ITEM_TOXIC_MOUSE, SPECIES_BIJUU_POISON}),
    },
#if P_GEN_9_MEGA_EVOLUTIONS
    [SPECIES_MEGA_BIJUU] =
    {
        .baseHP = 80, .baseAttack = 125, .baseDefense = 90, .baseSpeed = 145,
        .baseSpAttack = 105, .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 280, .evYield_Speed = 3,
        .genderRatio = MON_FEMALE, .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_TECHNICIAN, ABILITY_TECHNICIAN, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("Bijuu"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("Its copied techniques become\nperfectly precise, though it still\npretends not to be listening."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_Bijuu, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_Bijuu,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_Bijuu, .shinyPalette = gMonShinyPalette_Bijuu,
        .iconSprite = gMonIcon_Bijuu, .iconPalette = gMonIconPalette_Bijuu,
        .shinyIconPalette = gMonShinyIconPalette_Bijuu, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sMeowthLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable, .formChangeTable = sTrioSpiritMegaReturnTable,
        OVERWORLD(
            sPicTable_Bijuu,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Bijuu,
            gShinyOverworldPalette_Bijuu
        )
    },
#endif
#endif

#if P_FAMILY_RIKO
    [SPECIES_RIKO_FIGHTING] =
    {
        .baseHP = 90, .baseAttack = 110, .baseDefense = 95, .baseSpeed = 105,
        .baseSpAttack = 70, .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FIGHTING), .catchRate = 45, .expYield = 240,
        .evYield_Attack = 2, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("PomFuRiko"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Pom Fu"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Her tiny paws strike with\nPom Fu precision. A snack\nbreak follows every lesson."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoFighting, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoFighting,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoFighting, .shinyPalette = gMonShinyPalette_RikoFighting,
        .iconSprite = gMonIcon_RikoFighting, .iconPalette = gMonIconPalette_RikoFighting,
        .shinyIconPalette = gMonShinyIconPalette_RikoFighting, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoFighting,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoFighting,
            gShinyOverworldPalette_RikoFighting
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoFightingTrioLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_BLACK_BELT, SPECIES_RIKO}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },

    [SPECIES_RIKO_BUG] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_BUG, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("BumbleRiko"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Riko buzzes around her sisters.\nShe guards every honey snack\nand thinks she runs the hive."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoBug, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoBug,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoBug, .shinyPalette = gMonShinyPalette_RikoBug,
        .iconSprite = gMonIcon_RikoBug, .iconPalette = gMonIconPalette_RikoBug,
        .shinyIconPalette = gMonShinyIconPalette_RikoBug, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoBug,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoBug,
            gShinyOverworldPalette_RikoBug
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoBugCompleteLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_RIKOS_HONEYCOMB, SPECIES_RIKO}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },

    [SPECIES_RIKO_FIRE] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_FIRE), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoFire"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Riko's fur crackles with\nwarmth. It mistakes every\ncampfire for a cozy bed."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoFire, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoFire,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoFire, .shinyPalette = gMonShinyPalette_RikoFire,
        .iconSprite = gMonIcon_RikoFire, .iconPalette = gMonIconPalette_RikoFire,
        .shinyIconPalette = gMonShinyIconPalette_RikoFire, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoFire,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoFire,
            gShinyOverworldPalette_RikoFire
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoFireTrioLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_GREEN_PEPPER, SPECIES_RIKO}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },

    [SPECIES_RIKO_WATER] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_WATER), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoWater"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Riko's fur gleams with\nwater energy. It still refuses\nto skip snack time."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoWater, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoWater,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoWater, .shinyPalette = gMonShinyPalette_RikoWater,
        .iconSprite = gMonIcon_RikoWater, .iconPalette = gMonIconPalette_RikoWater,
        .shinyIconPalette = gMonShinyIconPalette_RikoWater, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoWater,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoWater,
            gShinyOverworldPalette_RikoWater
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sQuaxlyLevelUpLearnset,
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },

    [SPECIES_RIKO_GRASS] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_GRASS), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoGrass"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Riko's coat carries fresh\nforest energy. It loves soft\ngrass almost as much as treats."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoGrass, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoGrass,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoGrass, .shinyPalette = gMonShinyPalette_RikoGrass,
        .iconSprite = gMonIcon_RikoGrass, .iconPalette = gMonIconPalette_RikoGrass,
        .shinyIconPalette = gMonShinyIconPalette_RikoGrass, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoGrass,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoGrass,
            gShinyOverworldPalette_RikoGrass
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sSprigatitoLevelUpLearnset,
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },

    [SPECIES_RIKO_ELECTRIC] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_ELECTRIC), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoVolt"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Riko's fluff holds a bright\ncharge. Its zoomies become\neven harder to predict."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoElectric, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoElectric,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoElectric, .shinyPalette = gMonShinyPalette_RikoElectric,
        .iconSprite = gMonIcon_RikoElectric, .iconPalette = gMonIconPalette_RikoElectric,
        .shinyIconPalette = gMonShinyIconPalette_RikoElectric, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoElectric,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoElectric,
            gShinyOverworldPalette_RikoElectric
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoElectricTrioLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_EEL_SUSHI, SPECIES_RIKO}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },

    [SPECIES_RIKO_ICE] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_ICE), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoIce"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Riko's coat gathers cool\nenergy. It leaves tiny frost\nprints near the treat bowl."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoIce, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoIce,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoIce, .shinyPalette = gMonShinyPalette_RikoIce,
        .iconSprite = gMonIcon_RikoIce, .iconPalette = gMonIconPalette_RikoIce,
        .shinyIconPalette = gMonShinyIconPalette_RikoIce, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoIce,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoIce,
            gShinyOverworldPalette_RikoIce
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sSwinubLevelUpLearnset,
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },

    [SPECIES_RIKO_PSYCHIC] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_PSYCHIC), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoMind"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Riko's thoughts are loud\nand mostly concern snacks,\npraise, and dramatic entrances."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoPsychic, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoPsychic,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoPsychic, .shinyPalette = gMonShinyPalette_RikoPsychic,
        .iconSprite = gMonIcon_RikoPsychic, .iconPalette = gMonIconPalette_RikoPsychic,
        .shinyIconPalette = gMonShinyIconPalette_RikoPsychic, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoPsychic,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoPsychic,
            gShinyOverworldPalette_RikoPsychic
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sFlittleLevelUpLearnset,
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },

    [SPECIES_RIKO_FLYING] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_FLYING), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoWing"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Riko's fluff catches the\nwind. It considers every breeze\na personal spotlight."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoFlying, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoFlying,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoFlying, .shinyPalette = gMonShinyPalette_RikoFlying,
        .iconSprite = gMonIcon_RikoFlying, .iconPalette = gMonIconPalette_RikoFlying,
        .shinyIconPalette = gMonShinyIconPalette_RikoFlying, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoFlying,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoFlying,
            gShinyOverworldPalette_RikoFlying
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sWattrelLevelUpLearnset,
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },

    [SPECIES_RIKO_DRAGON] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("DragonRiko"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Riko spreads tiny dragon wings.\nHer proud roar demands snacks.\nShe guards her family fiercely."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoDragon, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoDragon,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoDragon, .shinyPalette = gMonShinyPalette_RikoDragon,
        .iconSprite = gMonIcon_RikoDragon, .iconPalette = gMonIconPalette_RikoDragon,
        .shinyIconPalette = gMonShinyIconPalette_RikoDragon, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_RikoDragon,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoDragon,
            gShinyOverworldPalette_RikoDragon
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoDragonCompleteLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_POM_DRAGON_PLUSH, SPECIES_RIKO}),
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sRikoSpiritMegaEntryTable,
    },

#endif
#if P_FAMILY_BIJUU
    [SPECIES_BIJUU_FIGHTING] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_FIGHTING), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuFight"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It copies fighting stances\nperfectly, but prefers watching\nothers do the hard part."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuFighting, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuFighting,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuFighting, .shinyPalette = gMonShinyPalette_BijuuFighting,
        .iconSprite = gMonIcon_BijuuFighting, .iconPalette = gMonIconPalette_BijuuFighting,
        .shinyIconPalette = gMonShinyIconPalette_BijuuFighting, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuFighting,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuFighting,
            gShinyOverworldPalette_BijuuFighting
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sFlamigoLevelUpLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable,
        .formChangeTable = sBijuuSpiritMegaEntryTable,
    },

    [SPECIES_BIJUU_POISON] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_POISON), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuVenom"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("Purple poison hangs in the air.\nThis cocoa has a nasty bite\nand absolutely no regrets."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuPoison, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuPoison,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuPoison, .shinyPalette = gMonShinyPalette_BijuuPoison,
        .iconSprite = gMonIcon_BijuuPoison, .iconPalette = gMonIconPalette_BijuuPoison,
        .shinyIconPalette = gMonShinyIconPalette_BijuuPoison, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuPoison,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuPoison,
            gShinyOverworldPalette_BijuuPoison
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sBijuuPoisonTrioLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_TOXIC_MOUSE, SPECIES_BIJUU}),
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable,
        .formChangeTable = sBijuuSpiritMegaEntryTable,
    },

    [SPECIES_BIJUU_GROUND] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_GROUND), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuTerra"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It burrows into soft earth,\nthen emerges looking like it\nplanned the whole thing."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuGround, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuGround,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuGround, .shinyPalette = gMonShinyPalette_BijuuGround,
        .iconSprite = gMonIcon_BijuuGround, .iconPalette = gMonIconPalette_BijuuGround,
        .shinyIconPalette = gMonShinyIconPalette_BijuuGround, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuGround,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuGround,
            gShinyOverworldPalette_BijuuGround
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sPhanpyLevelUpLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable,
        .formChangeTable = sBijuuSpiritMegaEntryTable,
    },

    [SPECIES_BIJUU_ROCK] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_ROCK), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("CrystalCat"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("Bijuu wears sparkling crystals.\nShe admires her shiny collar\nwhile plotting her next pounce."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuRock, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuRock,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuRock, .shinyPalette = gMonShinyPalette_BijuuRock,
        .iconSprite = gMonIcon_BijuuRock, .iconPalette = gMonIconPalette_BijuuRock,
        .shinyIconPalette = gMonShinyIconPalette_BijuuRock, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuRock,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuRock,
            gShinyOverworldPalette_BijuuRock
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sBijuuRockCompleteLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_COCOAS_SHINY_PEBBLE, SPECIES_BIJUU}),
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable,
        .formChangeTable = sBijuuSpiritMegaEntryTable,
    },

    [SPECIES_BIJUU_BUG] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_BUG), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuBug"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It watches bugs closely and\ncopies their movements with\nuncanny little precision."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuBug, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuBug,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuBug, .shinyPalette = gMonShinyPalette_BijuuBug,
        .iconSprite = gMonIcon_BijuuBug, .iconPalette = gMonIconPalette_BijuuBug,
        .shinyIconPalette = gMonShinyIconPalette_BijuuBug, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuBug,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuBug,
            gShinyOverworldPalette_BijuuBug
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sSewaddleLevelUpLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable,
        .formChangeTable = sBijuuSpiritMegaEntryTable,
    },

    [SPECIES_BIJUU_GHOST] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_GHOST), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuGhost"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It copies ghostly tricks and\nthen acts innocent when the\nlights flicker."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuGhost, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuGhost,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuGhost, .shinyPalette = gMonShinyPalette_BijuuGhost,
        .iconSprite = gMonIcon_BijuuGhost, .iconPalette = gMonIconPalette_BijuuGhost,
        .shinyIconPalette = gMonShinyIconPalette_BijuuGhost, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuGhost,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuGhost,
            gShinyOverworldPalette_BijuuGhost
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sBijuuGhostTrioLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_MOUSE_TOY, SPECIES_BIJUU}),
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable,
        .formChangeTable = sBijuuSpiritMegaEntryTable,
    },

    [SPECIES_BIJUU_DARK] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_DARK), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("MidnightCat"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("Bijuu sneaks through shadows.\nHer midnight cape hides every\nsecret snack she has stolen."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuDark, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuDark,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuDark, .shinyPalette = gMonShinyPalette_BijuuDark,
        .iconSprite = gMonIcon_BijuuDark, .iconPalette = gMonIconPalette_BijuuDark,
        .shinyIconPalette = gMonShinyIconPalette_BijuuDark, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuDark,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuDark,
            gShinyOverworldPalette_BijuuDark
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sBijuuDarkCompleteLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_COCOAS_SNEAKY_CAPE, SPECIES_BIJUU}),
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable,
        .formChangeTable = sBijuuSpiritMegaEntryTable,
    },

    [SPECIES_BIJUU_STEEL] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_STEEL), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuSteel"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It copies the strength of\nsteel, though its favorite\nweapon remains curiosity."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuSteel, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuSteel,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuSteel, .shinyPalette = gMonShinyPalette_BijuuSteel,
        .iconSprite = gMonIcon_BijuuSteel, .iconPalette = gMonIconPalette_BijuuSteel,
        .shinyIconPalette = gMonShinyIconPalette_BijuuSteel, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuSteel,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuSteel,
            gShinyOverworldPalette_BijuuSteel
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sTinkatinkLevelUpLearnset,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable,
        .formChangeTable = sBijuuSpiritMegaEntryTable,
    },

    [SPECIES_BIJUU_EMBER] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 110, .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FIRE), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuEmber"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Warm Tail"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("A small flame warms her tail.\nShe found her own spark when\nher sisters knew the real her."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuEmber, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuEmber,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuEmber, .shinyPalette = gMonShinyPalette_BijuuEmber,
        .iconSprite = gMonIcon_BijuuEmber, .iconPalette = gMonIconPalette_BijuuEmber,
        .shinyIconPalette = gMonShinyIconPalette_BijuuEmber, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuEmber,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuEmber,
            gShinyOverworldPalette_BijuuEmber
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sBijuuEmberLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_BIJUUS_FIRE, SPECIES_BIJUU}),
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable,
        .formChangeTable = sBijuuSpiritMegaEntryTable,
    },
    [SPECIES_BIJUU_PSYCHIC] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_PSYCHIC), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuPsi"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Astral Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It lifts stones with its mind.\nIts eyes glow when it senses\nsomeone opening a treat bag."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuPsychic, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuPsychic,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuPsychic, .shinyPalette = gMonShinyPalette_BijuuPsychic,
        .iconSprite = gMonIcon_BijuuPsychic, .iconPalette = gMonIconPalette_BijuuPsychic,
        .shinyIconPalette = gMonShinyIconPalette_BijuuPsychic, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuPsychic,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuPsychic,
            gShinyOverworldPalette_BijuuPsychic
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sMeowthLevelUpLearnset,
        .teachableLearnset = sMeowthTeachableLearnset,
        .eggMoveLearnset = sMeowthEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_BIJUUS_CAT_NIP, SPECIES_BIJUU}, {EVO_ITEM, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER}),
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable,
        .formChangeTable = sBijuuSpiritMegaEntryTable,
    },

#endif


#if P_FAMILY_FIDOUGH
    [SPECIES_PENNY_BRAVE] =
    {
        .baseHP = 85, .baseAttack = 90, .baseDefense = 100, .baseSpeed = 85,
        .baseSpAttack = 55, .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_Defense = 2, .evYield_HP = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_WELL_BAKED_BODY, ABILITY_NONE, ABILITY_AROMA_VEIL },
        .innates = { ABILITY_SWEET_VEIL },
        .bodyColor = BODY_COLOR_YELLOW, .speciesName = _("PennyBrave"), .cryId = CRY_FIDOUGH,
        .natDexNum = NATIONAL_DEX_FIDOUGH, .categoryName = _("Brave Steps"), .height = 5, .weight = 149,
        .description = COMPOUND_STRING("A little armor, a growing heart.\nShe walks ahead knowing both\nher sisters will walk with her."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_PennyBrave, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_PennyBrave,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 4,
        .palette = gMonPalette_PennyBrave, .shinyPalette = gMonShinyPalette_PennyBrave,
        .iconSprite = gMonIcon_PennyBrave, .iconPalette = gMonIconPalette_PennyBrave,
        .shinyIconPalette = gMonShinyIconPalette_PennyBrave, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        FOOTPRINT(Fidough)
        OVERWORLD(
            sPicTable_PennyBrave,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_PennyBrave,
            gShinyOverworldPalette_PennyBrave
        )
        .levelUpLearnset = sPennyBraveLevelUpLearnset,
        .teachableLearnset = sDachsbunTeachableLearnset,
        .eggMoveLearnset = sFidoughEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_PENNYS_BRAVERY, SPECIES_FIDOUGH}),
        .formSpeciesIdTable = sPennySpiritFormSpeciesIdTable,
        .formChangeTable = sPennySpiritMegaEntryTable,
    },
    [SPECIES_PENNY_GUARDIAN] =
    {
        .baseHP = 100, .baseAttack = 100, .baseDefense = 120, .baseSpeed = 85,
        .baseSpAttack = 55, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_FAIRY), .catchRate = 45, .expYield = 240,
        .evYield_Defense = 2, .evYield_HP = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_WELL_BAKED_BODY, ABILITY_NONE, ABILITY_AROMA_VEIL },
        .innates = { ABILITY_SWEET_VEIL },
        .bodyColor = BODY_COLOR_YELLOW, .speciesName = _("PennyGuard"), .cryId = CRY_FIDOUGH,
        .natDexNum = NATIONAL_DEX_FIDOUGH, .categoryName = _("Hot Dog"), .height = 5, .weight = 149,
        .description = COMPOUND_STRING("Dad's keys make Penny brave.\n"
                                       "Her golden coat wears ketchup,\n"
                                       "but chicken brings her home."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_PennyGuardian, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_PennyGuardian,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 4,
        .palette = gMonPalette_PennyGuardian, .shinyPalette = gMonShinyPalette_PennyGuardian,
        .iconSprite = gMonIcon_PennyGuardian, .iconPalette = gMonIconPalette_PennyGuardian,
        .shinyIconPalette = gMonShinyIconPalette_PennyGuardian, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        FOOTPRINT(Fidough)
        OVERWORLD(
            sPicTable_PennyGuardian,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_PennyGuardian,
            gShinyOverworldPalette_PennyGuardian
        )
        .levelUpLearnset = sDachsbunLevelUpLearnset,
        .teachableLearnset = sDachsbunTeachableLearnset,
        .eggMoveLearnset = sFidoughEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_DADS_TOOLBOX, SPECIES_PENNY_STEEL}, {EVO_ITEM, ITEM_PENNYS_GARDEN_TROWEL, SPECIES_PENNY_GROUND}, {EVO_ITEM, ITEM_PENNYS_BRAVERY, SPECIES_PENNY_BRAVE}, {EVO_ITEM, ITEM_PIECE_OF_CHICKEN, SPECIES_FIDOUGH}, {EVO_ITEM, ITEM_DOG_BOWL, SPECIES_PENNY_WATER}, {EVO_ITEM, ITEM_FETCHING_STICK, SPECIES_PENNY_GRASS}),
        .formSpeciesIdTable = sPennySpiritFormSpeciesIdTable,
        .formChangeTable = sPennySpiritMegaEntryTable,
    },
#endif

#if P_FAMILY_BIJUU
    [SPECIES_BIJUU_ICE] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_ICE), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuIce"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("Bijuu leaves tiny frosty pawprints.\n"
                                       "Her frozen fish is still her\n"
                                       "favorite chilly treasure."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuIce, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuIce,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuIce, .shinyPalette = gMonShinyPalette_BijuuIce,
        .iconSprite = gMonIcon_BijuuIce, .iconPalette = gMonIconPalette_BijuuIce,
        .shinyIconPalette = gMonShinyIconPalette_BijuuIce, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuIce,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuIce,
            gShinyOverworldPalette_BijuuIce
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sBijuuIceTrioLevelUpLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_FROZEN_FISH, SPECIES_BIJUU}),
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable,
        .formChangeTable = sBijuuSpiritMegaEntryTable,
    },

#endif

#if P_FAMILY_FIDOUGH
    [SPECIES_PENNY_GROUND] =
    {
        .baseHP = 100, .baseAttack = 100, .baseDefense = 120, .baseSpeed = 85,
        .baseSpAttack = 55, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_GROUND), .catchRate = 45, .expYield = 240,
        .evYield_Defense = 2, .evYield_HP = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_WELL_BAKED_BODY, ABILITY_NONE, ABILITY_AROMA_VEIL },
        .innates = { ABILITY_SWEET_VEIL },
        .bodyColor = BODY_COLOR_YELLOW, .speciesName = _("DiggingPen"), .cryId = CRY_FIDOUGH,
        .natDexNum = NATIONAL_DEX_FIDOUGH, .categoryName = _("Hot Dog"), .height = 5, .weight = 149,
        .description = COMPOUND_STRING("Penny peeks from a cozy burrow.\nHer floppy ears hide the dirt\nas she watches over her family."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_PennyGround, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_PennyGround,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 4,
        .palette = gMonPalette_PennyGround, .shinyPalette = gMonShinyPalette_PennyGround,
        .iconSprite = gMonIcon_PennyGround, .iconPalette = gMonIconPalette_PennyGround,
        .shinyIconPalette = gMonShinyIconPalette_PennyGround, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        FOOTPRINT(Fidough)
        OVERWORLD(
            sPicTable_PennyGround,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_PennyGround,
            gShinyOverworldPalette_PennyGround
        )
        .levelUpLearnset = sPennyGroundCompleteLevelUpLearnset,
        .teachableLearnset = sDachsbunTeachableLearnset,
        .eggMoveLearnset = sFidoughEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_PENNYS_GARDEN_TROWEL, SPECIES_PENNY_GUARDIAN}),
        .formSpeciesIdTable = sPennySpiritFormSpeciesIdTable,
        .formChangeTable = sPennySpiritMegaEntryTable,
    },

    [SPECIES_PENNY_STEEL] =
    {
        .baseHP = 100, .baseAttack = 100, .baseDefense = 120, .baseSpeed = 85,
        .baseSpAttack = 55, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_STEEL), .catchRate = 45, .expYield = 240,
        .evYield_Defense = 2, .evYield_HP = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_WELL_BAKED_BODY, ABILITY_NONE, ABILITY_AROMA_VEIL },
        .innates = { ABILITY_SWEET_VEIL },
        .bodyColor = BODY_COLOR_YELLOW, .speciesName = _("HandyPenny"), .cryId = CRY_FIDOUGH,
        .natDexNum = NATIONAL_DEX_FIDOUGH, .categoryName = _("Hot Dog"), .height = 5, .weight = 149,
        .description = COMPOUND_STRING("Penny brings her trusty toolbox.\nHer little hardhat gives her\ncourage to help her sisters."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_PennySteel, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_PennySteel,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 4,
        .palette = gMonPalette_PennySteel, .shinyPalette = gMonShinyPalette_PennySteel,
        .iconSprite = gMonIcon_PennySteel, .iconPalette = gMonIconPalette_PennySteel,
        .shinyIconPalette = gMonShinyIconPalette_PennySteel, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        FOOTPRINT(Fidough)
        OVERWORLD(
            sPicTable_PennySteel,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_PennySteel,
            gShinyOverworldPalette_PennySteel
        )
        .levelUpLearnset = sPennySteelCompleteLevelUpLearnset,
        .teachableLearnset = sDachsbunTeachableLearnset,
        .eggMoveLearnset = sFidoughEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_DADS_TOOLBOX, SPECIES_PENNY_GUARDIAN}),
        .formSpeciesIdTable = sPennySpiritFormSpeciesIdTable,
        .formChangeTable = sPennySpiritMegaEntryTable,
    },

    [SPECIES_PENNY_WATER] =
    {
        .baseHP = 100, .baseAttack = 100, .baseDefense = 120, .baseSpeed = 85,
        .baseSpAttack = 55, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_WATER), .catchRate = 45, .expYield = 240,
        .evYield_Defense = 2, .evYield_HP = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_WELL_BAKED_BODY, ABILITY_NONE, ABILITY_AROMA_VEIL },
        .innates = { ABILITY_SWEET_VEIL },
        .bodyColor = BODY_COLOR_YELLOW, .speciesName = _("PennyWater"), .cryId = CRY_FIDOUGH,
        .natDexNum = NATIONAL_DEX_FIDOUGH, .categoryName = _("Hot Dog"), .height = 5, .weight = 149,
        .description = COMPOUND_STRING("Penny bravely guards her sisters.\n"
                                       "Her element changes, but her\n"
                                       "golden heart stays the same."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_PennyWater, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_PennyWater,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 4,
        .palette = gMonPalette_PennyWater, .shinyPalette = gMonShinyPalette_PennyWater,
        .iconSprite = gMonIcon_PennyWater, .iconPalette = gMonIconPalette_PennyWater,
        .shinyIconPalette = gMonShinyIconPalette_PennyWater, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        FOOTPRINT(Fidough)
        OVERWORLD(
            sPicTable_PennyWater,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_PennyWater,
            gShinyOverworldPalette_PennyWater
        )
        .levelUpLearnset = sPennyWaterTrioLevelUpLearnset,
        .teachableLearnset = sDachsbunTeachableLearnset,
        .eggMoveLearnset = sFidoughEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_DOG_BOWL, SPECIES_PENNY_GUARDIAN}),
        .formSpeciesIdTable = sPennySpiritFormSpeciesIdTable,
        .formChangeTable = sPennySpiritMegaEntryTable,
    },

    [SPECIES_PENNY_GRASS] =
    {
        .baseHP = 100, .baseAttack = 100, .baseDefense = 120, .baseSpeed = 85,
        .baseSpAttack = 55, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_GRASS), .catchRate = 45, .expYield = 240,
        .evYield_Defense = 2, .evYield_HP = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_WELL_BAKED_BODY, ABILITY_NONE, ABILITY_AROMA_VEIL },
        .innates = { ABILITY_SWEET_VEIL },
        .bodyColor = BODY_COLOR_YELLOW, .speciesName = _("PennyGrass"), .cryId = CRY_FIDOUGH,
        .natDexNum = NATIONAL_DEX_FIDOUGH, .categoryName = _("Hot Dog"), .height = 5, .weight = 149,
        .description = COMPOUND_STRING("Penny bravely guards her sisters.\n"
                                       "Her element changes, but her\n"
                                       "golden heart stays the same."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_PennyGrass, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_PennyGrass,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 4,
        .palette = gMonPalette_PennyGrass, .shinyPalette = gMonShinyPalette_PennyGrass,
        .iconSprite = gMonIcon_PennyGrass, .iconPalette = gMonIconPalette_PennyGrass,
        .shinyIconPalette = gMonShinyIconPalette_PennyGrass, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        FOOTPRINT(Fidough)
        OVERWORLD(
            sPicTable_PennyGrass,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_PennyGrass,
            gShinyOverworldPalette_PennyGrass
        )
        .levelUpLearnset = sPennyGrassTrioLevelUpLearnset,
        .teachableLearnset = sDachsbunTeachableLearnset,
        .eggMoveLearnset = sFidoughEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_FETCHING_STICK, SPECIES_PENNY_GUARDIAN}),
        .formSpeciesIdTable = sPennySpiritFormSpeciesIdTable,
        .formChangeTable = sPennySpiritMegaEntryTable,
    },

#endif


#if P_FAMILY_FIDOUGH
    [SPECIES_PENNY_SPIRIT] =
    {
        .baseHP = 95, .baseAttack = 85, .baseDefense = 105, .baseSpeed = 55,
        .baseSpAttack = 65, .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_STEEL, TYPE_FAIRY), .catchRate = 3, .expYield = 240,
        .evYield_Defense = 2, .evYield_HP = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_BATTLE_ARMOR, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_YELLOW, .speciesName = _("PennySoul"), .cryId = CRY_FIDOUGH,
        .natDexNum = NATIONAL_DEX_FIDOUGH, .categoryName = _("Hot Dog"), .height = 5, .weight = 149,
        .description = COMPOUND_STRING("Her armor remembers every hug.\nMom made a frightened little dog\nfeel safe enough to be brave."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_PennySpirit, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_PennySpirit,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 4,
        .palette = gMonPalette_PennySpirit, .shinyPalette = gMonShinyPalette_PennySpirit,
        .iconSprite = gMonIcon_PennySpirit, .iconPalette = gMonIconPalette_PennySpirit,
        .shinyIconPalette = gMonShinyIconPalette_PennySpirit, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        FOOTPRINT(Fidough)
        OVERWORLD(
            sPicTable_PennySpirit,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_PennySpirit,
            gShinyOverworldPalette_PennySpirit
        )
        .levelUpLearnset = sPennySpiritLevelUpLearnset,
        .teachableLearnset = sDachsbunTeachableLearnset,
        .eggMoveLearnset = sFidoughEggMoveLearnset,
    },
#endif

#if P_FAMILY_BIJUU
    [SPECIES_BIJUU_SPIRIT] =
    {
        .baseHP = 80, .baseAttack = 70, .baseDefense = 65, .baseSpeed = 110,
        .baseSpAttack = 95, .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_GHOST, TYPE_PSYCHIC), .catchRate = 3, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LEVITATE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuSoul"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("Her blue flames guard a soft heart.\nShe learned to shine because Mom\nloved every strange part of her."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuSpirit, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuSpirit,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuSpirit, .shinyPalette = gMonShinyPalette_BijuuSpirit,
        .iconSprite = gMonIcon_BijuuSpirit, .iconPalette = gMonIconPalette_BijuuSpirit,
        .shinyIconPalette = gMonShinyIconPalette_BijuuSpirit, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuSpirit,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuSpirit,
            gShinyOverworldPalette_BijuuSpirit
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sBijuuSpiritLevelUpLearnset,
    },
#endif

#if P_FAMILY_RIKO
    [SPECIES_MEGA_RIKO_SPIRIT] =
    {
        .baseHP = 115, .baseAttack = 145, .baseDefense = 105, .baseSpeed = 120,
        .baseSpAttack = 120, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_FIRE, TYPE_FAIRY), .catchRate = 3, .expYield = 290,
        .evYield_HP = 1, .evYield_Attack = 2, .genderRatio = MON_FEMALE,
        .eggCycles = 80, .friendship = 35, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PRESSURE, ABILITY_NONE, ABILITY_FLASH_FIRE },
        .bodyColor = BODY_COLOR_BLACK, .speciesName = _("RikoSpirit"), .cryId = CRY_ENTEI,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Cerberus"), .height = 15, .weight = 420,
        .description = COMPOUND_STRING("A spirit born from Riko.\nIts three heads guard its\nfamily with a blazing roar."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_RikoSpirit, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_RikoSpirit,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_RikoSpirit, .shinyPalette = gMonShinyPalette_RikoSpirit,
        .iconSprite = gMonIcon_RikoSpirit, .iconPalette = gMonIconPalette_RikoSpirit,
        .shinyIconPalette = gMonShinyIconPalette_RikoSpirit, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_M)
        OVERWORLD(
            sPicTable_RikoSpirit,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RikoSpirit,
            gShinyOverworldPalette_RikoSpirit
        )

        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sRikoSpiritLevelUpLearnset,
        FOOTPRINT(Riko)
        .isMegaEvolution = TRUE,
        .formSpeciesIdTable = sRikoFormSpeciesIdTable,
        .formChangeTable = sTrioSpiritMegaReturnTable,
    },
#endif

#if P_FAMILY_FIDOUGH
    [SPECIES_MEGA_PENNY_SPIRIT] =
    {
        .baseHP = 95, .baseAttack = 125, .baseDefense = 145, .baseSpeed = 65,
        .baseSpAttack = 65, .baseSpDefense = 130,
        .types = MON_TYPES(TYPE_STEEL, TYPE_FAIRY), .catchRate = 3, .expYield = 240,
        .evYield_Defense = 2, .evYield_HP = 1, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_BATTLE_ARMOR, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_YELLOW, .speciesName = _("PennySoul"), .cryId = CRY_FIDOUGH,
        .natDexNum = NATIONAL_DEX_FIDOUGH, .categoryName = _("Hot Dog"), .height = 5, .weight = 149,
        .description = COMPOUND_STRING("Her armor remembers every hug.\nMom made a frightened little dog\nfeel safe enough to be brave."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_PennySpirit, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_PennySpirit,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 4,
        .palette = gMonPalette_PennySpirit, .shinyPalette = gMonShinyPalette_PennySpirit,
        .iconSprite = gMonIcon_PennySpirit, .iconPalette = gMonIconPalette_PennySpirit,
        .shinyIconPalette = gMonShinyIconPalette_PennySpirit, .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        FOOTPRINT(Fidough)
        OVERWORLD(
            sPicTable_PennySpirit,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_PennySpirit,
            gShinyOverworldPalette_PennySpirit
        )
        .levelUpLearnset = sPennySpiritLevelUpLearnset,
        .teachableLearnset = sDachsbunTeachableLearnset,
        .eggMoveLearnset = sFidoughEggMoveLearnset,
        .isMegaEvolution = TRUE,
        .formSpeciesIdTable = sPennySpiritFormSpeciesIdTable,
        .formChangeTable = sTrioSpiritMegaReturnTable,
    },
#endif

#if P_FAMILY_BIJUU
    [SPECIES_MEGA_BIJUU_SPIRIT] =
    {
        .baseHP = 80, .baseAttack = 90, .baseDefense = 85, .baseSpeed = 135,
        .baseSpAttack = 135, .baseSpDefense = 105,
        .types = MON_TYPES(TYPE_GHOST, TYPE_PSYCHIC), .catchRate = 3, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = MON_FEMALE,
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LEVITATE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuSoul"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("Her blue flames guard a soft heart.\nShe learned to shine because Mom\nloved every strange part of her."),
        .pokemonScale = 256, .trainerScale = 256,
        .frontPic = gMonFrontPic_BijuuSpirit, .frontPicSize = MON_COORDS_SIZE(64, 64), .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, .backPic = gMonBackPic_BijuuSpirit,
        .backPicSize = MON_COORDS_SIZE(64, 64), .backPicYOffset = 0,
        .palette = gMonPalette_BijuuSpirit, .shinyPalette = gMonShinyPalette_BijuuSpirit,
        .iconSprite = gMonIcon_BijuuSpirit, .iconPalette = gMonIconPalette_BijuuSpirit,
        .shinyIconPalette = gMonShinyIconPalette_BijuuSpirit, .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 8, SHADOW_SIZE_S)
        OVERWORLD(
            sPicTable_BijuuSpirit,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BijuuSpirit,
            gShinyOverworldPalette_BijuuSpirit
        )
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sBijuuSpiritLevelUpLearnset,
        .isMegaEvolution = TRUE,
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable,
        .formChangeTable = sTrioSpiritMegaReturnTable,
    },
#endif

    /*
    [SPECIES_NONE] =
    {
        .baseHP        = 1,
        .baseAttack    = 1,
        .baseDefense   = 1,
        .baseSpeed     = 1,
        .baseSpAttack  = 1,
        .baseSpDefense = 1,
        .types = MON_TYPES(TYPE_MYSTERY),
        .catchRate = 255,
        .expYield = 67,
        .evYield_HP = 1,
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        .frontPicFemale = gMonFrontPic_CircledQuestionMark,
        .frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .backPicFemale = gMonBackPic_CircledQuestionMarkF,
        .backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .paletteFemale = gMonPalette_CircledQuestionMarkF,
        .shinyPaletteFemale = gMonShinyPalette_CircledQuestionMarkF,
        .iconSpriteFemale = gMonIcon_QuestionMarkF,
        .iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        FOOTPRINT(QuestionMark)
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    */
};

const struct EggData gEggDatas[EGG_ID_COUNT] =
{
#include "egg_data.h"
};


