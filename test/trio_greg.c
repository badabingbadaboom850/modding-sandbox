#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "battle_setup.h"
#include "trio_greg.h"
#include "pokemon.h"
#include "constants/opponents.h"
#include "constants/flags.h"
#include "constants/vars.h"

TEST("Greg's twelve new stops have independent saved wins and read through every trainer API")
{
    VarSet(VAR_TRIO_GREG_WINS,0);
    for(u16 trainer=TRAINER_GREG_GOLDENROD_CITY;trainer<=TRAINER_GREG_SAFFRON_CITY;trainer++)
    {
        EXPECT(TrioGreg_IsTrainer(trainer));EXPECT(!HasTrainerBeenFought(trainer));
        TRAINER_BATTLE_PARAM.opponentA=trainer;
        EXPECT(!GetTrainerFlag());
        SetTrainerFlag(trainer);
        EXPECT(HasTrainerBeenFought(trainer));EXPECT(GetTrainerFlag());
        EXPECT_EQ(VarGet(VAR_TRIO_GREG_WINS),(1u << (trainer-TRAINER_GREG_GOLDENROD_CITY+1))-1);
    }
    EXPECT_EQ(VarGet(VAR_TRIO_GREG_WINS),0xFFF);
    ClearTrainerFlag(TRAINER_GREG_CIANWOOD_CITY);
    EXPECT(!HasTrainerBeenFought(TRAINER_GREG_CIANWOOD_CITY));
    EXPECT(HasTrainerBeenFought(TRAINER_GREG_BLACKTHORN_CITY));
    EXPECT_EQ(VarGet(VAR_TRIO_GREG_WINS),0xFF7);
}

TEST("Greg wins and resets never touch the twelve reclaimed story and replay flags")
{
    for(u32 mask=0;mask<4;mask++)
    {
        VarSet(VAR_TRIO_GREG_WINS,0);
        for(u16 trainer=TRAINER_GREG_GOLDENROD_CITY;trainer<=TRAINER_GREG_SAFFRON_CITY;trainer++)
        {
            bool32 flag=(trainer & 1) ? mask & 1 : mask & 2;
            u16 address=TRAINER_FLAGS_START+trainer;
            if(flag)FlagSet(address);else FlagClear(address);
            EXPECT(!HasTrainerBeenFought(trainer));
            SetTrainerFlag(trainer);EXPECT(HasTrainerBeenFought(trainer));
            EXPECT_EQ(FlagGet(address),flag!=0);
            ClearTrainerFlag(trainer);EXPECT(!HasTrainerBeenFought(trainer));
            EXPECT_EQ(FlagGet(address),flag!=0);
        }
    }
}

TEST("Greg preserves old wins global Wawa and all neighboring family progress")
{
    static const u16 oldGreg[]={TRAINER_GREG_ROUTE_29,TRAINER_GREG_ROUTE_30,TRAINER_GREG_CHERRYGROVE};
    VarSet(VAR_TRIO_GREG_WINS,0);VarSet(VAR_TRIO_PLAYER_HAT,4);VarSet(VAR_TRIO_ROAD_BATTLES,5);
    FlagSet(FLAG_GREG_WAWA_REWARDED);
    for(u32 i=0;i<ARRAY_COUNT(oldGreg);i++)SetTrainerFlag(oldGreg[i]);
    TrioGreg_SetWon(TRAINER_GREG_GOLDENROD_CITY,TRUE);
    EXPECT_EQ(VarGet(VAR_TRIO_GREG_WINS),1);
    for(u32 i=0;i<ARRAY_COUNT(oldGreg);i++)EXPECT(HasTrainerBeenFought(oldGreg[i]));
    EXPECT(FlagGet(FLAG_GREG_WAWA_REWARDED));EXPECT_EQ(VarGet(VAR_TRIO_PLAYER_HAT),4);EXPECT_EQ(VarGet(VAR_TRIO_ROAD_BATTLES),5);
    EXPECT(!TrioGreg_IsTrainer(TRAINER_GREG_ROUTE_29));EXPECT(!TrioGreg_IsTrainer(TRAINER_GREG));
    EXPECT(!TrioGreg_IsTrainer(TRAINER_ROAD_SCOTT));EXPECT(!TrioGreg_IsTrainer(TRAINER_GREEDENT_GANG_6));
    TrioGreg_SetWon(TRAINER_GREG,TRUE);EXPECT_EQ(VarGet(VAR_TRIO_GREG_WINS),1);
    EXPECT_EQ(sizeof(struct SaveBlock1),15444);EXPECT_EQ(sizeof(struct SaveBlock2),2864);EXPECT_EQ(sizeof(struct SaveBlock3),100);
    EXPECT_EQ(MAX_TRAINERS_COUNT,1164);
}
