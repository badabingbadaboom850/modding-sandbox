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
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("Riko"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Its fluffy coat holds fairy\nenergy and charms all who\nstroke it."),
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
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sRikoFormChangeTable,
    },
#if P_GEN_9_MEGA_EVOLUTIONS
    [SPECIES_MEGA_RIKO] =
    {
        .baseHP = 90, .baseAttack = 85, .baseDefense = 95, .baseSpeed = 130,
        .baseSpAttack = 135, .baseSpDefense = 125,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY), .catchRate = 45, .expYield = 300,
        .evYield_SpAttack = 2, .evYield_Speed = 1, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_PIXILATE, ABILITY_PIXILATE, ABILITY_PIXILATE },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("Riko"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("Mega Evolution intensifies its\nfairy energy, making its coat\nshine like a charm."),
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
        .formSpeciesIdTable = sRikoFormSpeciesIdTable, .formChangeTable = sRikoFormChangeTable,
    },
#endif
#endif
#if P_FAMILY_BIJUU
    [SPECIES_BIJUU] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 220, .evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50), .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("Bijuu"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("It studies Meowth's tricks,\ncopying techniques in the\nblink of an eye."),
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
    },
#if P_GEN_9_MEGA_EVOLUTIONS
    [SPECIES_MEGA_BIJUU] =
    {
        .baseHP = 80, .baseAttack = 125, .baseDefense = 90, .baseSpeed = 145,
        .baseSpAttack = 105, .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_NORMAL), .catchRate = 60, .expYield = 280, .evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50), .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW, .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_TECHNICIAN, ABILITY_TECHNICIAN, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("Bijuu"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("Mega Evolution lets it reproduce\nMeowth's techniques with\nperfect precision."),
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
        .formSpeciesIdTable = sBijuuFormSpeciesIdTable, .formChangeTable = sBijuuFormChangeTable,
    }        OVERWORLD(
            sPicTable_Bijuu,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Bijuu,
            gShinyOverworldPalette_Bijuu
        )
,
#endif
#endif

#if P_FAMILY_RIKO
    [SPECIES_RIKO_FIRE] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_FIRE), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoFire"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("A playful Riko variant\nwith fire energy."),
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
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sFuecocoLevelUpLearnset,
    },

    [SPECIES_RIKO_WATER] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_WATER), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoWater"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("A playful Riko variant\nwith water energy."),
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
    },

    [SPECIES_RIKO_GRASS] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_GRASS), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoGrass"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("A playful Riko variant\nwith grass energy."),
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
    },

    [SPECIES_RIKO_ELECTRIC] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_ELECTRIC), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoVolt"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("A playful Riko variant\nwith electric energy."),
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
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sPawmiLevelUpLearnset,
    },

    [SPECIES_RIKO_ICE] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_ICE), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoIce"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("A playful Riko variant\nwith ice energy."),
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
    },

    [SPECIES_RIKO_PSYCHIC] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_PSYCHIC), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoMind"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("A playful Riko variant\nwith psychic energy."),
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
    },

    [SPECIES_RIKO_FLYING] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_FLYING), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoWing"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("A playful Riko variant\nwith flying energy."),
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
    },

    [SPECIES_RIKO_DRAGON] =
    {
        .baseHP = 90, .baseAttack = 75, .baseDefense = 85, .baseSpeed = 110,
        .baseSpAttack = 105, .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_DRAGON), .catchRate = 45, .expYield = 240,
        .evYield_SpAttack = 2, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE, .speciesName = _("RikoDrake"), .cryId = CRY_SYLVEON,
        .natDexNum = NATIONAL_DEX_RIKO, .categoryName = _("Fluff Bunny"), .height = 6, .weight = 95,
        .description = COMPOUND_STRING("A playful Riko variant\nwith dragon energy."),
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
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sFrigibaxLevelUpLearnset,
    },

#endif
#if P_FAMILY_BIJUU
    [SPECIES_BIJUU_FIGHTING] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_FIGHTING), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuFight"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("A playful Bijuu variant\nwith fighting energy."),
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
    },

    [SPECIES_BIJUU_POISON] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_POISON), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuVenom"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("A playful Bijuu variant\nwith poison energy."),
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
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sKoffingLevelUpLearnset,
    },

    [SPECIES_BIJUU_GROUND] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_GROUND), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuTerra"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("A playful Bijuu variant\nwith ground energy."),
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
    },

    [SPECIES_BIJUU_ROCK] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_ROCK), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuRock"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("A playful Bijuu variant\nwith rock energy."),
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
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sNacliLevelUpLearnset,
    },

    [SPECIES_BIJUU_BUG] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_BUG), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuBug"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("A playful Bijuu variant\nwith bug energy."),
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
    },

    [SPECIES_BIJUU_GHOST] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_GHOST), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuGhost"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("A playful Bijuu variant\nwith ghost energy."),
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
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sMisdreavusLevelUpLearnset,
    },

    [SPECIES_BIJUU_DARK] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_DARK), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuDark"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("A playful Bijuu variant\nwith dark energy."),
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
        .teachingType = ALL_TEACHABLES, .levelUpLearnset = sSableyeLevelUpLearnset,
    },

    [SPECIES_BIJUU_STEEL] =
    {
        .baseHP = 80, .baseAttack = 85, .baseDefense = 70, .baseSpeed = 120,
        .baseSpAttack = 95, .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_STEEL), .catchRate = 60, .expYield = 220,
        .evYield_Speed = 3, .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20, .friendship = STANDARD_FRIENDSHIP, .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LIMBER, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BROWN, .speciesName = _("BijuuSteel"), .cryId = CRY_MEOWTH,
        .natDexNum = NATIONAL_DEX_BIJUU, .categoryName = _("Copy Cat"), .height = 7, .weight = 120,
        .description = COMPOUND_STRING("A playful Bijuu variant\nwith steel energy."),
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
