#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "event_data.h"
#include "item.h"
#include "trio_snack_chase.h"
#include "test/test.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/opponents.h"
#include "constants/species.h"
#include "constants/vars.h"

static const struct {u8 group,num;u16 badge,trainer,level;} sStops[] = {
    {MAP_GROUP(MAP_ROUTE37),MAP_NUM(MAP_ROUTE37),FLAG_BADGE03_GET,TRAINER_ROUTE37_SNACK_THIEF,22},
    {MAP_GROUP(MAP_ROUTE38),MAP_NUM(MAP_ROUTE38),FLAG_BADGE04_GET,TRAINER_GREEDENT_GANG_2,35},
    {MAP_GROUP(MAP_ROUTE42),MAP_NUM(MAP_ROUTE42),FLAG_BADGE06_GET,TRAINER_GREEDENT_GANG_3,48},
    {MAP_GROUP(MAP_ROUTE44),MAP_NUM(MAP_ROUTE44),FLAG_BADGE07_GET,TRAINER_GREEDENT_GANG_4,62},
    {MAP_GROUP(MAP_ROUTE26),MAP_NUM(MAP_ROUTE26),FLAG_BADGE08_GET,TRAINER_GREEDENT_GANG_5,78},
    {MAP_GROUP(MAP_ROUTE6),MAP_NUM(MAP_ROUTE6),FLAG_IS_CHAMPION,TRAINER_GREEDENT_GANG_6,100},
};
static void ResetGang(void)
{
    u32 i;
    ClearBag();
    VarSet(VAR_TRIO_GANG_WINS,0);
    VarSet(VAR_TRIO_GANG_PHASE,0);
    VarSet(VAR_TRIO_GANG_ACTIVE_WAVE,0);
    VarSet(VAR_TRIO_SNACK_CHASE_STATE,0);
    VarSet(VAR_TRIO_SNACK_STOLEN_ITEM,ITEM_NONE);
    for(i=0;i<ARRAY_COUNT(sStops);i++)FlagClear(sStops[i].badge);
}
static void Visit(u32 i)
{
    gSaveBlock1Ptr->location.mapGroup=sStops[i].group;
    gSaveBlock1Ptr->location.mapNum=sStops[i].num;
    FlagSet(sStops[i].badge);
    TrioGang_PrepareAmbush();
}

TEST("Greedent gang requires exact map, badge and previous completed wave")
{
    u32 i;
    ResetGang();
    for(i=0;i<ARRAY_COUNT(sStops);i++)
    {
        Visit(i);
        EXPECT_EQ(VarGet(VAR_TEMP_B),i==0?8:0);
        FlagClear(sStops[i].badge);
        TrioGang_PrepareAmbush();
        EXPECT_EQ(VarGet(VAR_TEMP_B),0);
    }
    gSaveBlock1Ptr->location.mapGroup=MAP_GROUP(MAP_ROUTE36);
    gSaveBlock1Ptr->location.mapNum=MAP_NUM(MAP_ROUTE36);
    FlagSet(FLAG_BADGE03_GET);
    TrioGang_PrepareAmbush();
    EXPECT_EQ(VarGet(VAR_TEMP_B),0);
}

TEST("All six ambushes steal once, retry a loss, and restore exact items in order")
{
    u32 i;
    ResetGang();
    EXPECT(AddBagItem(ITEM_ORAN_BERRY,6));
    for(i=0;i<ARRAY_COUNT(sStops);i++)
    {
        Visit(i);EXPECT_EQ(VarGet(VAR_TEMP_B),i==0?8:i+1);
        TrioGang_BeginAmbush();
        EXPECT(gSpecialVar_Result);EXPECT(gSpecialVar_0x8005);
        EXPECT_EQ(VarGet(VAR_TRIO_GANG_ACTIVE_WAVE),i+1);
        EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ORAN_BERRY),5);
        gBattleOutcome=B_OUTCOME_LOST;
        TrioGang_RecordVictory();
        EXPECT_EQ(VarGet(VAR_TRIO_GANG_PHASE),1);
        EXPECT_EQ(VarGet(VAR_TRIO_GANG_WINS),i);
        TrioSnack_ReturnItem();EXPECT(!gSpecialVar_Result);
        // Blackout may never execute a script tail. A later route reload and
        // retry must preserve custody rather than removing another item.
        TrioGang_PrepareAmbush();EXPECT_EQ(VarGet(VAR_TEMP_B),i==0?0:i+1);
        TrioGang_BeginAmbush();EXPECT(gSpecialVar_Result);EXPECT(!gSpecialVar_0x8005);
        EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ORAN_BERRY),5);
        gBattleOutcome=B_OUTCOME_WON;
        TrioGang_RecordVictory();EXPECT_EQ(VarGet(VAR_TRIO_GANG_PHASE),2);
        TrioSnack_ReturnItem();EXPECT(gSpecialVar_Result);
        EXPECT_EQ(VarGet(VAR_TRIO_GANG_WINS),i+1);
        EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ORAN_BERRY),6);
        TrioSnack_ReturnItem();EXPECT(!gSpecialVar_Result);
        TrioGang_PrepareAmbush();EXPECT_EQ(VarGet(VAR_TEMP_B),0);
    }
}

TEST("Gang full-stack recovery survives departure and only advances after return")
{
    ResetGang();
    VarSet(VAR_TRIO_SNACK_CHASE_STATE,4);
    Visit(1);EXPECT_EQ(VarGet(VAR_TRIO_GANG_WINS),1);
    EXPECT(AddBagItem(ITEM_ORAN_BERRY,1));
    TrioGang_BeginAmbush();
    EXPECT(AddBagItem(ITEM_ORAN_BERRY,MAX_BAG_ITEM_CAPACITY));
    gBattleOutcome=B_OUTCOME_WON;TrioGang_RecordVictory();
    TrioSnack_ReturnItem();EXPECT(!gSpecialVar_Result);
    EXPECT_EQ(VarGet(VAR_TRIO_GANG_WINS),1);
    EXPECT_EQ(VarGet(VAR_TRIO_GANG_PHASE),2);
    Visit(2);EXPECT_EQ(VarGet(VAR_TEMP_B),0);
    Visit(1);EXPECT_EQ(VarGet(VAR_TEMP_B),7);
    TrioGang_BeginAmbush();EXPECT(!gSpecialVar_Result);
    EXPECT(RemoveBagItem(ITEM_ORAN_BERRY,1));
    TrioSnack_ReturnItem();EXPECT(gSpecialVar_Result);
    EXPECT_EQ(VarGet(VAR_TRIO_GANG_WINS),2);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ORAN_BERRY),MAX_BAG_ITEM_CAPACITY);
}

TEST("Legacy completed, active and return-pending snack saves migrate without extra theft")
{
    u32 state;
    for(state=1;state<=4;state++)
    {
        ResetGang();VarSet(VAR_TRIO_SNACK_CHASE_STATE,state);
        VarSet(VAR_TRIO_SNACK_STOLEN_ITEM,state==4?ITEM_NONE:ITEM_CHERI_BERRY);
        Visit(0);
        EXPECT_EQ(VarGet(VAR_TEMP_B),state==3?7:0);
        if(state<=2)
        {
            TrioGang_BeginAmbush();EXPECT(gSpecialVar_Result);EXPECT(!gSpecialVar_0x8005);
            EXPECT_EQ(VarGet(VAR_TRIO_SNACK_STOLEN_ITEM),ITEM_CHERI_BERRY);
        }
        if(state==4)EXPECT_EQ(VarGet(VAR_TRIO_GANG_WINS),1);
        EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_CHERI_BERRY),0);
    }
}

TEST("Greedent trainer slots never alter their reclaimed puzzle flags")
{
    u32 i;
    ResetGang();
    for(i=0;i<ARRAY_COUNT(sStops);i++)
    {
        u16 flag=TRAINER_FLAGS_START+sStops[i].trainer;
        FlagSet(flag);
        EXPECT(!HasTrainerBeenFought(sStops[i].trainer));
        ClearTrainerFlag(sStops[i].trainer);
        EXPECT(FlagGet(flag));
        FlagClear(flag);
        SetTrainerFlag(sStops[i].trainer);
        EXPECT(!FlagGet(flag));
        VarSet(VAR_TRIO_GANG_WINS,i+1);
        EXPECT(HasTrainerBeenFought(sStops[i].trainer));
        VarSet(VAR_TRIO_GANG_WINS,0);
    }
    EXPECT_EQ(TrioGang_WaveForTrainer(TRAINER_GREG),0);
}

