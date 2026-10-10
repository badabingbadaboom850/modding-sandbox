#include "global.h"
#include "pokemon.h"
#include "item.h"
#include "item_use.h"
#include "overworld.h"
#include "trio_camp.h"
#include "event_data.h"
#include "text.h"
#include "test/test.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/game_stat.h"
#include "constants/flags.h"

TEST("Garden Bloom evolution recognizes ordinary Riko, reverses Flower Riko, rejects others")
{
    struct Pokemon mon;
    static const u16 from[] = {SPECIES_RIKO, SPECIES_RIKO_WING, SPECIES_RIKO_FLOWER, SPECIES_BIJUU, SPECIES_FIDOUGH, SPECIES_RIKO_SPIRIT};
    static const u16 to[] = {SPECIES_RIKO_FLOWER, SPECIES_NONE, SPECIES_RIKO, SPECIES_NONE, SPECIES_NONE, SPECIES_NONE};
    u32 i;
    for (i = 0; i < ARRAY_COUNT(from); i++)
    {
        CreateMon(&mon, from[i], 35, 0, OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, ITEM_RIKOS_BLOOM, NULL, NULL, CHECK_EVO), to[i]);
        EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), from[i]);
    }
}

TEST("Flower Riko is a healthy female garden form with complete art and Aromatherapy")
{
    struct Pokemon mon;
    const struct SpeciesInfo *info = &gSpeciesInfo[SPECIES_RIKO_FLOWER];
    CreateMon(&mon, SPECIES_RIKO_FLOWER, 35, 0, OTID_STRUCT_PLAYER_ID);
    CalculateMonStats(&mon);
    EXPECT_EQ(GetMonGender(&mon), MON_FEMALE);
    EXPECT(GetMonData(&mon, MON_DATA_MAX_HP) > 35);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP), GetMonData(&mon, MON_DATA_MAX_HP));
    EXPECT(info->frontPic != NULL && info->backPic != NULL);
    EXPECT(info->palette != NULL && info->shinyPalette != NULL);
    EXPECT(info->iconSprite != NULL && info->iconPalette != NULL);
    EXPECT(info->overworldData.images != NULL);
    EXPECT(info->formChangeTable == NULL);
    EXPECT(!info->isMegaEvolution);
    EXPECT_EQ(info->baseHP, gSpeciesInfo[SPECIES_RIKO].baseHP);
    EXPECT_EQ(info->baseAttack, gSpeciesInfo[SPECIES_RIKO].baseAttack);
    EXPECT_EQ(info->baseDefense, gSpeciesInfo[SPECIES_RIKO].baseDefense);
    EXPECT_EQ(info->baseSpeed, gSpeciesInfo[SPECIES_RIKO].baseSpeed);
    EXPECT_EQ(info->baseSpAttack, gSpeciesInfo[SPECIES_RIKO].baseSpAttack);
    EXPECT_EQ(info->baseSpDefense, gSpeciesInfo[SPECIES_RIKO].baseSpDefense);
    EXPECT_EQ(info->levelUpLearnset[0].move, MOVE_AROMATHERAPY);
    EXPECT_EQ(info->levelUpLearnset[0].level, 0);
}

TEST("Garden Bloom is a protected key item routed through the existing reusable evolution path")
{
    ClearBag();
    EXPECT_EQ(GetItemPocket(ITEM_RIKOS_BLOOM), POCKET_KEY_ITEMS);
    EXPECT(GetItemImportance(ITEM_RIKOS_BLOOM));
    EXPECT_EQ(GetItemFieldFunc(ITEM_RIKOS_BLOOM), ItemUseOutOfBattle_EvolutionStone);
    EXPECT(AddBagItem(ITEM_RIKOS_BLOOM, 1));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_RIKOS_BLOOM), 1);
    EXPECT(gItemsInfo[ITEM_RIKOS_BLOOM].iconPic != NULL);
    EXPECT(gItemsInfo[ITEM_RIKOS_BLOOM].iconPalette != NULL);
}

TEST("Garden Bloom Camp counts both directions and rejects other forms or items")
{
    FlagClear(FLAG_TRIO_CAMP_STATS_READY);
    TrioCamp_EnsureStatsInitialized();
    TrioCamp_RecordEvolution(SPECIES_RIKO, SPECIES_RIKO_FLOWER, ITEM_RIKOS_BLOOM);
    TrioCamp_RecordEvolution(SPECIES_RIKO_FLOWER, SPECIES_RIKO, ITEM_RIKOS_BLOOM);
    TrioCamp_RecordEvolution(SPECIES_RIKO_WING, SPECIES_RIKO_FLOWER, ITEM_RIKOS_BLOOM);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_FORM_SWAPS), 2);
    TrioCamp_RecordEvolution(SPECIES_RIKO_FLOWER, SPECIES_RIKO, ITEM_BLUE_BRUSH);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_FORM_SWAPS), 2);
}

TEST("Garden Bloom charm and Flower Riko names fit the game UI")
{
    EXPECT_LE(GetStringWidth(FONT_NARROW, gItemsInfo[ITEM_RIKOS_BLOOM].description, 0), 102);
    EXPECT_LE(GetStringWidth(FONT_NARROWER, gItemsInfo[ITEM_RIKOS_BLOOM].name, 0), 88);
    EXPECT_LE(GetStringWidth(FONT_SMALL_NARROWER, gSpeciesInfo[SPECIES_RIKO_FLOWER].speciesName, 0), 50);
    EXPECT_LE(GetStringWidth(FONT_NARROWER, gSpeciesInfo[SPECIES_RIKO_FLOWER].speciesName, 0), 64);
    EXPECT_EQ(sizeof(struct SaveBlock1), 15444);
    EXPECT_EQ(sizeof(struct SaveBlock2), 2864);
    EXPECT_EQ(sizeof(struct SaveBlock3), 100);
}
