#include "global.h"
#include "event_data.h"
#include "item.h"
#include "overworld.h"
#include "string_util.h"
#include "trio_camp.h"
#include "test/test.h"
#include "constants/flags.h"
#include "constants/game_stat.h"
#include "constants/items.h"
#include "constants/species.h"

static void ResetCampStats(void)
{
    FlagClear(FLAG_TRIO_CAMP_STATS_READY);
    TrioCamp_EnsureStatsInitialized();
}

TEST("Camp initializes old encrypted spare slots without resetting adventure totals")
{
    u32 i;
    FlagClear(FLAG_TRIO_CAMP_STATS_READY);
    SetGameStat(GAME_STAT_STEPS, 12345);
    for (i = GAME_STAT_TRIO_WAWA_S; i < NUM_GAME_STATS; i++)
        gSaveBlock1Ptr->gameStats[i] = 0xDEADBEEF;
    TrioCamp_EnsureStatsInitialized();
    EXPECT(FlagGet(FLAG_TRIO_CAMP_STATS_READY));
    EXPECT_EQ(GetGameStat(GAME_STAT_STEPS), 12345);
    for (i = GAME_STAT_TRIO_WAWA_S; i < NUM_GAME_STATS; i++)
        EXPECT_EQ(GetGameStat(i), 0);
    TrioCamp_RecordMedicineUse(ITEM_POTION);
    TrioCamp_EnsureStatsInitialized();
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_WAWA_S), 1);
}

TEST("Camp tracks the three Wawa sizes and personal consumables separately")
{
    static const u16 items[] = {ITEM_POTION, ITEM_SUPER_POTION, ITEM_HYPER_POTION, ITEM_ORAN_BERRY, ITEM_CHERI_BERRY, ITEM_PECHA_BERRY};
    u32 i;
    ResetCampStats();
    for (i = 0; i < ARRAY_COUNT(items); i++)
        TrioCamp_RecordMedicineUse(items[i]);
    TrioCamp_RecordMedicineUse(ITEM_MAX_POTION);
    TrioCamp_RecordMedicineUse(ITEM_DADS_KEYS);
    TrioCamp_RecordMedicineUse(ITEM_NONE);
    for (i = GAME_STAT_TRIO_WAWA_S; i <= GAME_STAT_TRIO_PUP_CUP; i++)
        EXPECT_EQ(GetGameStat(i), 1);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_FORM_SWAPS), 0);
}

TEST("Camp counters saturate and survive save-stat encryption key changes")
{
    u32 oldKey = gSaveBlock2Ptr->encryptionKey;
    u32 newKey = oldKey ^ 0x12345678;
    ResetCampStats();
    SetGameStat(GAME_STAT_TRIO_WAWA_S, 0xFFFFFE);
    TrioCamp_RecordMedicineUse(ITEM_POTION);
    TrioCamp_RecordMedicineUse(ITEM_POTION);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_WAWA_S), 0xFFFFFF);
    TrioCamp_RecordGame();
    ApplyNewEncryptionKeyToGameStats(newKey);
    gSaveBlock2Ptr->encryptionKey = newKey;
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_WAWA_S), 0xFFFFFF);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_CAMP_GAMES), 1);
    TrioCamp_EnsureStatsInitialized();
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_CAMP_GAMES), 1);
    ApplyNewEncryptionKeyToGameStats(oldKey);
    gSaveBlock2Ptr->encryptionKey = oldKey;
}

TEST("Camp counts completed personal transformations and returns only with matching items")
{
    ResetCampStats();
    TrioCamp_RecordEvolution(SPECIES_RIKO, SPECIES_RIKO_FIRE, ITEM_GREEN_PEPPER);
    TrioCamp_RecordEvolution(SPECIES_RIKO_FIRE, SPECIES_RIKO, ITEM_GREEN_PEPPER);
    TrioCamp_RecordEvolution(SPECIES_FIDOUGH, SPECIES_PENNY_GUARDIAN, ITEM_DADS_KEYS);
    TrioCamp_RecordEvolution(SPECIES_PENNY_GUARDIAN, SPECIES_PENNY_WATER, ITEM_DOG_BOWL);
    TrioCamp_RecordEvolution(SPECIES_PENNY_WATER, SPECIES_PENNY_GUARDIAN, ITEM_DOG_BOWL);
    TrioCamp_RecordEvolution(SPECIES_BIJUU, SPECIES_BIJUU_PSYCHIC, ITEM_BIJUUS_FISH_TOY);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_FORM_SWAPS), 6);
    TrioCamp_RecordEvolution(SPECIES_RIKO, SPECIES_RIKO, ITEM_GREEN_PEPPER);
    TrioCamp_RecordEvolution(SPECIES_RIKO, SPECIES_RIKO_FIRE, ITEM_EEL_SUSHI);
    TrioCamp_RecordEvolution(SPECIES_FIDOUGH, SPECIES_PENNY_WATER, ITEM_DOG_BOWL);
    TrioCamp_RecordEvolution(SPECIES_BULBASAUR, SPECIES_IVYSAUR, ITEM_GREEN_PEPPER);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_FORM_SWAPS), 6);
}

TEST("Camp favorites require an actual consumable and never remove reusable form items")
{
    ResetCampStats();
    ClearBag();
    EXPECT(AddBagItem(ITEM_GREEN_PEPPER, 1));
    gSpecialVar_0x8004 = 0;
    EXPECT(!TrioCamp_UseFavorite());
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_CHICKY), 0);
    EXPECT(CheckBagHasItem(ITEM_GREEN_PEPPER, 1));
    EXPECT(AddBagItem(ITEM_ORAN_BERRY, 2));
    EXPECT(TrioCamp_UseFavorite());
    EXPECT(CheckBagHasItem(ITEM_ORAN_BERRY, 1));
    EXPECT(!CheckBagHasItem(ITEM_ORAN_BERRY, 2));
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_CHICKY), 1);
    gSpecialVar_0x8004 = 3;
    EXPECT(!TrioCamp_UseFavorite());
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_CHICKY), 1);
    ClearBag();
}

TEST("Camp activities use independent persistent counters")
{
    ResetCampStats();
    TrioCamp_RecordVisit();
    TrioCamp_RecordVisit();
    TrioCamp_RecordGame();
    TrioCamp_RecordPet();
    TrioCamp_RecordPet();
    TrioCamp_RecordPet();
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_CAMP_VISITS), 2);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_CAMP_GAMES), 1);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_CAMP_PETS), 3);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_WAWA_S), 0);
}

TEST("Camp stats board formats maximum counts and safely handles an invalid page")
{
    ResetCampStats();
    SetGameStat(GAME_STAT_TRIO_WAWA_S, 0xFFFFFF);
    gSpecialVar_0x8004 = 2;
    TrioCamp_BufferStats();
    EXPECT_EQ(StringCompare(gStringVar1, COMPOUND_STRING("16777215")), 0);
    SetGameStat(GAME_STAT_STEPS, 42);
    gSpecialVar_0x8004 = 0xFFFF;
    TrioCamp_BufferStats();
    EXPECT_EQ(StringCompare(gStringVar1, COMPOUND_STRING("42")), 0);
}
