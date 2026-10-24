#include "global.h"
#include <string.h>
#include "battle_setup.h"
#include "event_data.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/flags.h"
#include "constants/maps.h"

TEST("Spirit trial rejects an empty or egg-only party without changing enemies")
{
    struct Pokemon before[PARTY_SIZE];
    u32 isEgg = TRUE;
    ZeroPlayerPartyMons();
    CreateMon(&gEnemyParty[0], SPECIES_CLEFAIRY, 7, 0, OTID_STRUCT_PLAYER_ID);
    memcpy(before, gEnemyParty, sizeof(before));
    gSpecialVar_0x8004 = SPECIES_PENNY_SPIRIT;
    EXPECT(!PrepareTrioSpiritTrial());
    EXPECT_EQ(memcmp(before, gEnemyParty, sizeof(before)), 0);
    CreateMon(&gPlayerParty[0], SPECIES_RIKO, 100, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, &isEgg);
    EXPECT(!PrepareTrioSpiritTrial());
    EXPECT_EQ(memcmp(before, gEnemyParty, sizeof(before)), 0);
}

TEST("Spirit trial scales to the strongest girl and heals even a fainted team")
{
    u32 hp = 0;
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_RIKO, 5, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_FIDOUGH, 12, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_HP, &hp);
    SetMonData(&gPlayerParty[1], MON_DATA_HP, &hp);
    gSpecialVar_0x8004 = SPECIES_PENNY_SPIRIT;
    EXPECT(PrepareTrioSpiritTrial());
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_SPECIES), SPECIES_PENNY_SPIRIT);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 18);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE1), MOVE_METAL_CLAW);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP), GetMonData(&gPlayerParty[0], MON_DATA_MAX_HP));
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_HP), GetMonData(&gPlayerParty[1], MON_DATA_MAX_HP));
    EXPECT_EQ(GetMonGender(&gEnemyParty[0]), MON_FEMALE);
    gSpecialVar_0x8004 = SPECIES_BIJUU_SPIRIT;
    EXPECT(PrepareTrioSpiritTrial());
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM), ITEM_RING_TARGET);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE1), MOVE_CONFUSION);
}

TEST("Spirit trial ignores eggs and caps its stronger move set at level 100")
{
    u32 isEgg = TRUE;
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_RIKO, 20, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_BIJUU, 100, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[1], MON_DATA_IS_EGG, &isEgg);
    gSpecialVar_0x8004 = SPECIES_BIJUU_SPIRIT;
    EXPECT(PrepareTrioSpiritTrial());
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 27);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE1), MOVE_SHADOW_BALL);
    EXPECT_EQ(GetMonGender(&gEnemyParty[0]), MON_FEMALE);
    CreateMon(&gPlayerParty[0], SPECIES_RIKO, 100, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(PrepareTrioSpiritTrial());
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 100);
}

TEST("Spirit milestones require every Johto Badge or the League victory")
{
    u32 badge;
    for (badge = FLAG_BADGE01_GET; badge <= FLAG_BADGE08_GET; badge++)
        FlagClear(badge);
    FlagClear(FLAG_IS_CHAMPION);
    gSpecialVar_0x8004 = SPECIES_PENNY_SPIRIT;
    EXPECT(!CheckTrioSpiritMilestone());
    FlagSet(FLAG_BADGE08_GET);
    EXPECT(!CheckTrioSpiritMilestone());
    for (badge = FLAG_BADGE01_GET; badge <= FLAG_BADGE08_GET; badge++)
        FlagSet(badge);
    EXPECT(CheckTrioSpiritMilestone());
    for (badge = FLAG_BADGE01_GET; badge <= FLAG_BADGE08_GET; badge++)
    {
        FlagClear(badge);
        EXPECT(!CheckTrioSpiritMilestone());
        FlagSet(badge);
    }
    gSpecialVar_0x8004 = SPECIES_BIJUU_SPIRIT;
    EXPECT(!CheckTrioSpiritMilestone());
    FlagSet(FLAG_IS_CHAMPION);
    EXPECT(CheckTrioSpiritMilestone());
    gSpecialVar_0x8004 = SPECIES_RIKO;
    EXPECT(!CheckTrioSpiritMilestone());
    for (badge = FLAG_BADGE01_GET; badge <= FLAG_BADGE08_GET; badge++)
        FlagClear(badge);
    FlagClear(FLAG_IS_CHAMPION);
}

TEST("Spirit level advantage grows from five to ten without exceeding 100")
{
    u32 i;
    static const u8 partyLevels[] = {5, 10, 30, 49, 50, 89, 95, 99, 100};
    static const u8 spiritLevels[] = {10, 16, 38, 58, 60, 99, 100, 100, 100};
    for (i = 0; i < ARRAY_COUNT(partyLevels); i++)
    {
        ZeroPlayerPartyMons();
        CreateMon(&gPlayerParty[0], SPECIES_RIKO, partyLevels[i], 0, OTID_STRUCT_PLAYER_ID);
        gSpecialVar_0x8004 = SPECIES_PENNY_SPIRIT;
        EXPECT(PrepareTrioSpiritTrial());
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), spiritLevels[i]);
        gSpecialVar_0x8004 = SPECIES_BIJUU_SPIRIT;
        EXPECT(PrepareTrioSpiritTrial());
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), spiritLevels[i]);
    }
}

TEST("Spirit opponents start at full health in story arenas")
{
    u32 i;
    u8 oldMapNum = gSaveBlock1Ptr->location.mapNum;
    u8 oldMapGroup = gSaveBlock1Ptr->location.mapGroup;
    static const u16 maps[] = {MAP_BLACKTHORN_CITY, MAP_ECRUTEAK_CITY};
    static const u16 species[] = {SPECIES_PENNY_SPIRIT, SPECIES_BIJUU_SPIRIT};

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_RIKO, 5, 0, OTID_STRUCT_PLAYER_ID);
    for (i = 0; i < ARRAY_COUNT(species); i++)
    {
        u32 hp = 1;
        gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(maps[i]);
        gSaveBlock1Ptr->location.mapNum = MAP_NUM(maps[i]);
        gSpecialVar_0x8004 = species[i];
        EXPECT(PrepareTrioSpiritTrial());
        EXPECT_GT(GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP), 1);
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_HP), GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP));
        SetMonData(&gEnemyParty[0], MON_DATA_HP, &hp);
        EXPECT(PrepareTrioSpiritTrial());
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_HP), GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP));
    }
    gSaveBlock1Ptr->location.mapGroup = oldMapGroup;
    gSaveBlock1Ptr->location.mapNum = oldMapNum;
}
