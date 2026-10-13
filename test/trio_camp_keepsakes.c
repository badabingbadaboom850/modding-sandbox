#include "global.h"
#include "event_data.h"
#include "overworld.h"
#include "trio_camp.h"
#include "test/test.h"
#include "constants/flags.h"
#include "constants/game_stat.h"

static const u16 sMilestones[] = {
    FLAG_BADGE01_GET, FLAG_BADGE03_GET, FLAG_BADGE04_GET,
    FLAG_TRIO_FESTIVAL_PICNIC, FLAG_TRIO_PENNY_SPIRIT_COMPLETE,
    FLAG_TRIO_BIJUU_SPIRIT_COMPLETE,
};
static const u16 sHideFlags[] = {
    FLAG_HIDE_TRIO_CAMP_PENNY_CORNER, FLAG_HIDE_TRIO_CAMP_RIKO_CHICKY,
    FLAG_HIDE_TRIO_CAMP_BIJUU_TOY, FLAG_HIDE_TRIO_CAMP_FESTIVAL,
    FLAG_HIDE_TRIO_CAMP_PENNY_SPIRIT, FLAG_HIDE_TRIO_CAMP_BIJUU_SPIRIT,
};

static void ResetKeepsakes(void)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sMilestones); i++)
        FlagClear(sMilestones[i]);
    FlagClear(FLAG_TRIO_PENNY_HOME_WIN);
    FlagClear(FLAG_TRIO_BIJUU_HOME_WIN);
    FlagClear(FLAG_TRIO_FESTIVAL_SCOTT_WIN);
}

TEST("Camp hides unearned gifts even on an older save with zero visibility flags")
{
    u32 i;
    ResetKeepsakes();
    for (i = 0; i < ARRAY_COUNT(sHideFlags); i++)
        FlagClear(sHideFlags[i]);
    SetGameStat(GAME_STAT_STEPS, 12345);
    SetGameStat(GAME_STAT_TRIO_CAMP_GAMES, 7);
    TrioCamp_UpdateKeepsakes();
    for (i = 0; i < ARRAY_COUNT(sHideFlags); i++)
    {
        EXPECT(FlagGet(sHideFlags[i]));
        EXPECT(!FlagGet(sMilestones[i]));
    }
    EXPECT_EQ(GetGameStat(GAME_STAT_STEPS), 12345);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_CAMP_GAMES), 7);
}

TEST("Camp gifts follow each actual milestone independently and recompute on entry")
{
    u32 i, j;
    for (i = 0; i < ARRAY_COUNT(sMilestones); i++)
    {
        ResetKeepsakes();
        FlagSet(sMilestones[i]);
        TrioCamp_UpdateKeepsakes();
        for (j = 0; j < ARRAY_COUNT(sHideFlags); j++)
            EXPECT_EQ(FlagGet(sHideFlags[j]), i != j);
        FlagClear(sMilestones[i]);
        TrioCamp_UpdateKeepsakes();
        EXPECT(FlagGet(sHideFlags[i]));
    }
}

TEST("Camp honors historical Spirit victories but requires the festival picnic")
{
    ResetKeepsakes();
    FlagSet(FLAG_TRIO_PENNY_HOME_WIN);
    FlagSet(FLAG_TRIO_BIJUU_HOME_WIN);
    FlagSet(FLAG_TRIO_FESTIVAL_SCOTT_WIN);
    TrioCamp_UpdateKeepsakes();
    EXPECT(!FlagGet(FLAG_HIDE_TRIO_CAMP_PENNY_SPIRIT));
    EXPECT(!FlagGet(FLAG_HIDE_TRIO_CAMP_BIJUU_SPIRIT));
    EXPECT(FlagGet(FLAG_HIDE_TRIO_CAMP_FESTIVAL));
    EXPECT(!FlagGet(FLAG_TRIO_PENNY_SPIRIT_COMPLETE));
    EXPECT(!FlagGet(FLAG_TRIO_BIJUU_SPIRIT_COMPLETE));
    FlagSet(FLAG_TRIO_FESTIVAL_PICNIC);
    TrioCamp_UpdateKeepsakes();
    EXPECT(!FlagGet(FLAG_HIDE_TRIO_CAMP_FESTIVAL));
}
