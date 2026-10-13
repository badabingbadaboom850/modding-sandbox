#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "string_util.h"
#include "trio_family_days.h"
#include "constants/characters.h"
#include "constants/flags.h"
#include "constants/vars.h"

TEST("Family radio needs the existing radio unlock and a completed recording")
{
    for (u32 enabled = 0; enabled < 2; enabled++)
    {
        if (enabled) FlagSet(FLAG_ENABLE_RADIO);
        else FlagClear(FLAG_ENABLE_RADIO);
        for (u32 state = 0; state <= 4; state++)
        {
            VarSet(VAR_TRIO_RADIO_STATE, state);
            EXPECT_EQ(TrioFamilyRadio_IsUnlocked(), enabled && state == 4);
        }
    }
}

TEST("Family broadcasts react to earned stories and never write quest progress")
{
    VarSet(VAR_TRIO_DINNER_STATE, 0);
    VarSet(VAR_TRIO_ROAD_COMPLETE, 0);
    VarSet(VAR_TRIO_GARDEN_STATE, 0);
    VarSet(VAR_TRIO_BREAD_MYSTERY, 0);
    VarSet(VAR_TRIO_RIFT_BIJUU_STATE, 0);
    VarSet(VAR_TRIO_HOMECOMING_STATE, 0);
    VarSet(VAR_TRIO_RIFT_PENNY_STATE, 0);
    FlagClear(FLAG_IS_CHAMPION);
    const u8 *riko = TrioFamilyRadio_GetTopic(0);
    const u8 *bijuu = TrioFamilyRadio_GetTopic(1);
    const u8 *penny = TrioFamilyRadio_GetTopic(2);
    const u8 *scott = TrioFamilyRadio_GetTopic(3);
    VarSet(VAR_TRIO_ROAD_COMPLETE, 1);
    EXPECT(TrioFamilyRadio_GetTopic(0) != riko);
    EXPECT(TrioFamilyRadio_GetTopic(1) != bijuu);
    EXPECT(TrioFamilyRadio_GetTopic(2) != penny);
    EXPECT(TrioFamilyRadio_GetTopic(3) != scott);
    const u8 *road = TrioFamilyRadio_GetTopic(3);
    VarSet(VAR_TRIO_DINNER_STATE, 4);
    EXPECT_EQ(TrioFamilyRadio_GetTopic(3), road);
    VarSet(VAR_TRIO_DINNER_STATE, 5);
    EXPECT(TrioFamilyRadio_GetTopic(3) != road);
    VarSet(VAR_TRIO_HOMECOMING_STATE, 1);
    const u8 *home = TrioFamilyRadio_GetTopic(3);
    FlagSet(FLAG_IS_CHAMPION);
    EXPECT(TrioFamilyRadio_GetTopic(3) != home);
    EXPECT_EQ(VarGet(VAR_TRIO_DINNER_STATE), 5);
    EXPECT_EQ(VarGet(VAR_TRIO_ROAD_COMPLETE), 1);
    EXPECT_EQ(VarGet(VAR_TRIO_HOMECOMING_STATE), 1);
}

TEST("Studio and field radio share bounded complete broadcasts on historical save arrays")
{
    EXPECT_EQ(sizeof(struct SaveBlock1), 15444);
    EXPECT_EQ(sizeof(struct SaveBlock2), 2864);
    EXPECT_EQ(sizeof(struct SaveBlock3), 100);
    for (u32 scenario = 0; scenario < 128; scenario++)
    {
        if (scenario & 64) FlagSet(FLAG_IS_CHAMPION);
        else FlagClear(FLAG_IS_CHAMPION);
        VarSet(VAR_TRIO_DINNER_STATE, scenario & 1 ? 5 : 0);
        VarSet(VAR_TRIO_ROAD_COMPLETE, scenario & 2 ? 1 : 0);
        VarSet(VAR_TRIO_GARDEN_STATE, scenario & 4 ? 5 : 0);
        VarSet(VAR_TRIO_BREAD_MYSTERY, scenario & 8 ? 3 : 0);
        VarSet(VAR_TRIO_RIFT_BIJUU_STATE, scenario & 8 ? 4 : 0);
        VarSet(VAR_TRIO_HOMECOMING_STATE, scenario & 16 ? 1 : 0);
        VarSet(VAR_TRIO_RIFT_PENNY_STATE, scenario & 32 ? 4 : 0);
        for (u32 segment = 0; segment < 4; segment++)
        {
            gSpecialVar_0x8004 = segment;
            BufferTrioFamilyRadio();
            const u8 *topic = TrioFamilyRadio_GetTopic(segment);
            u32 breaks = 0;
            for (u32 i = 0; topic[i] != EOS; i++)
            {
                u8 expected = topic[i];
                if (expected == CHAR_NEWLINE && ++breaks % 2 == 0)
                    expected = CHAR_PROMPT_CLEAR;
                EXPECT_EQ(gStringVar4[i], expected);
            }
            EXPECT_EQ(gSpecialVar_0x8004, segment);
            EXPECT_LT(StringLength(gStringVar4), 400);
            u32 lines = 1, length = 0;
            for (const u8 *p = gStringVar4; *p != EOS; p++)
            {
                if (*p == CHAR_NEWLINE || *p == CHAR_PROMPT_CLEAR)
                {
                    EXPECT_LE(length, 26);
                    length = 0;
                    lines++;
                }
                else length++;
            }
            EXPECT_LE(length, 26);
            EXPECT_LE(lines, 12);
        }
    }
}
