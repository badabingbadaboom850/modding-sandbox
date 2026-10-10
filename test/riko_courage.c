#include "global.h"
#include "pokemon.h"
#include "item.h"
#include "item_use.h"
#include "overworld.h"
#include "trio_camp.h"
#include "event_data.h"
#include "test/test.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/game_stat.h"
#include "constants/flags.h"

TEST("Riko Courage evolution recognizes base and Winged Riko, reverses Echo, rejects others")
{
    struct Pokemon mon;
    static const u16 from[] = {SPECIES_RIKO, SPECIES_RIKO_WING, SPECIES_RIKO_ECHO, SPECIES_BIJUU, SPECIES_FIDOUGH, SPECIES_RIKO_SPIRIT};
    static const u16 to[] = {SPECIES_RIKO_ECHO, SPECIES_RIKO_ECHO, SPECIES_RIKO, SPECIES_NONE, SPECIES_NONE, SPECIES_NONE};
    u32 i;
    for (i = 0; i < ARRAY_COUNT(from); i++)
    {
        CreateMon(&mon, from[i], 35, 0, OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, ITEM_RIKOS_COURAGE, NULL, NULL, CHECK_EVO), to[i]);
        EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), from[i]);
    }
}

TEST("Riko Echo is a healthy female permanent form with complete art and its own voice")
{
    struct Pokemon mon;
    const struct SpeciesInfo *info = &gSpeciesInfo[SPECIES_RIKO_ECHO];
    CreateMon(&mon, SPECIES_RIKO_ECHO, 35, 0, OTID_STRUCT_PLAYER_ID);
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
    EXPECT_EQ(info->levelUpLearnset[0].move, MOVE_ECHOED_VOICE);
    EXPECT_EQ(info->levelUpLearnset[0].level, 0);
}

TEST("Riko Courage is a protected key item routed through the existing reusable evolution path")
{
    ClearBag();
    EXPECT_EQ(GetItemPocket(ITEM_RIKOS_COURAGE), POCKET_KEY_ITEMS);
    EXPECT(GetItemImportance(ITEM_RIKOS_COURAGE));
    EXPECT_EQ(GetItemFieldFunc(ITEM_RIKOS_COURAGE), ItemUseOutOfBattle_EvolutionStone);
    EXPECT(AddBagItem(ITEM_RIKOS_COURAGE, 1));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_RIKOS_COURAGE), 1);
    EXPECT(gItemsInfo[ITEM_RIKOS_COURAGE].iconPic != NULL);
    EXPECT(gItemsInfo[ITEM_RIKOS_COURAGE].iconPalette != NULL);
}

TEST("Camp counts both Courage directions and the Winged entry, ignoring unmatched changes")
{
    FlagClear(FLAG_TRIO_CAMP_STATS_READY);
    TrioCamp_EnsureStatsInitialized();
    TrioCamp_RecordEvolution(SPECIES_RIKO, SPECIES_RIKO_ECHO, ITEM_RIKOS_COURAGE);
    TrioCamp_RecordEvolution(SPECIES_RIKO_ECHO, SPECIES_RIKO, ITEM_RIKOS_COURAGE);
    TrioCamp_RecordEvolution(SPECIES_RIKO_WING, SPECIES_RIKO_ECHO, ITEM_RIKOS_COURAGE);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_FORM_SWAPS), 3);
    TrioCamp_RecordEvolution(SPECIES_RIKO_ECHO, SPECIES_RIKO, ITEM_BLUE_BRUSH);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_FORM_SWAPS), 3);
}
