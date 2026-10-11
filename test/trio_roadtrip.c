#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "battle_setup.h"
#include "pokemon.h"
#include "trio_roadtrip.h"
#include "constants/flags.h"
#include "constants/map_groups.h"
#include "constants/opponents.h"
#include "constants/species.h"
#include "constants/vars.h"

TEST("Road trip friendly return requires exact island map and its three exhibition trainers")
{
    u16 trainers[] = {TRAINER_ROAD_BEACH, TRAINER_ROAD_FOREST, TRAINER_ROAD_SCOTT};
    for (u32 i = 0; i < ARRAY_COUNT(trainers); i++)
    {
        EXPECT(TrioRoad_IsTrainer(trainers[i]));
        EXPECT(TrioRoad_IsFriendlyBattle(MAP_GROUP(MAP_TRIO_ROAD_ISLAND), MAP_NUM(MAP_TRIO_ROAD_ISLAND), trainers[i]));
        EXPECT(!TrioRoad_IsFriendlyBattle(MAP_GROUP(MAP_TRIO_ROAD_COVE), MAP_NUM(MAP_TRIO_ROAD_COVE), trainers[i]));
        EXPECT(!TrioRoad_IsFriendlyBattle(MAP_GROUP(MAP_TRIO_ROAD_WOODS), MAP_NUM(MAP_TRIO_ROAD_WOODS), trainers[i]));
        EXPECT(!TrioRoad_IsFriendlyBattle(MAP_GROUP(MAP_CIANWOOD_CITY), MAP_NUM(MAP_CIANWOOD_CITY), trainers[i]));
    }
    EXPECT(!TrioRoad_IsTrainer(TRAINER_FESTIVAL_SCOTT));
    EXPECT(!TrioRoad_IsFriendlyBattle(MAP_GROUP(MAP_TRIO_ROAD_ISLAND), MAP_NUM(MAP_TRIO_ROAD_ISLAND), TRAINER_GREEDENT_GANG_6));
}

TEST("Road trip exhibitions never alter reclaimed Rinto Vajra or Ariana quest flags")
{
    u16 trainers[] = {TRAINER_ROAD_BEACH, TRAINER_ROAD_FOREST, TRAINER_ROAD_SCOTT};
    u16 flags[] = {FLAG_RINTO_TRADE_COMPLETE, FLAG_VAJRAPYRAMID1_URN, FLAG_SOUTHPASSAGE_ARIANA};
    for (u32 mask = 0; mask < 8; mask++)
    {
        VarSet(VAR_TRIO_ROAD_BATTLES, 0);
        for (u32 i = 0; i < 3; i++)
        {
            if (mask & (1 << i)) FlagSet(flags[i]);
            else FlagClear(flags[i]);
            EXPECT_EQ(TRAINER_FLAGS_START + trainers[i], flags[i]);
            EXPECT(!HasTrainerBeenFought(trainers[i]));
            SetTrainerFlag(trainers[i]);
            ClearTrainerFlag(trainers[i]);
            EXPECT_EQ(FlagGet(flags[i]), (mask & (1 << i)) != 0);
            gSpecialVar_0x8004 = trainers[i];
            TrioRoad_RecordBattleWin();
            TrioRoad_RecordBattleWin();
            EXPECT(HasTrainerBeenFought(trainers[i]));
            EXPECT_EQ(FlagGet(flags[i]), (mask & (1 << i)) != 0);
        }
        EXPECT_EQ(VarGet(VAR_TRIO_ROAD_BATTLES), 7);
        gSpecialVar_0x8004 = TRAINER_FESTIVAL_SCOTT;
        TrioRoad_RecordBattleWin();
        EXPECT_EQ(VarGet(VAR_TRIO_ROAD_BATTLES), 7);
    }
}

TEST("Road trip saved return port and arrival count preserve all quest progress")
{
    VarSet(VAR_TRIO_ROAD_RIKO, 3);
    VarSet(VAR_TRIO_ROAD_BIJUU, 4);
    VarSet(VAR_TRIO_ROAD_PENNY, 2);
    VarSet(VAR_TRIO_ROAD_VISITS, 0);
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_OLIVINE_CITY_PORT_OUTSIDE);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_OLIVINE_CITY_PORT_OUTSIDE);
    TrioRoad_RecordDeparture();
    EXPECT_EQ(VarGet(VAR_TRIO_ROAD_RETURN), 1);
    EXPECT_EQ(VarGet(VAR_TRIO_ROAD_VISITS), 1);
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_CIANWOOD_CITY);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_CIANWOOD_CITY);
    for (u32 i = 0; i < 5; i++) TrioRoad_RecordDeparture();
    EXPECT_EQ(VarGet(VAR_TRIO_ROAD_RETURN), 0);
    EXPECT_EQ(VarGet(VAR_TRIO_ROAD_VISITS), 3);
    EXPECT_EQ(VarGet(VAR_TRIO_ROAD_RIKO), 3);
    EXPECT_EQ(VarGet(VAR_TRIO_ROAD_BIJUU), 4);
    EXPECT_EQ(VarGet(VAR_TRIO_ROAD_PENNY), 2);
    EXPECT_EQ(sizeof(struct SaveBlock1), 15444);
    EXPECT_EQ(sizeof(struct SaveBlock2), 2864);
    EXPECT_EQ(sizeof(struct SaveBlock3), 100);
}

TEST("Road trip exhibition species have enabled battle and overworld registrations")
{
    u16 species[] = {SPECIES_AZUMARILL, SPECIES_PELIPPER, SPECIES_LANTURN, SPECIES_LEAFEON, SPECIES_BUTTERFREE, SPECIES_PACHIRISU, SPECIES_DACHSBUN, SPECIES_TOGETIC, SPECIES_LAPRAS, SPECIES_FIDOUGH};
    for (u32 i = 0; i < ARRAY_COUNT(species); i++)
    {
        EXPECT(gSpeciesInfo[species[i]].baseHP > 0);
        EXPECT(gSpeciesInfo[species[i]].frontPic != NULL);
        EXPECT(gSpeciesInfo[species[i]].backPic != NULL);
        EXPECT(gSpeciesInfo[species[i]].palette != NULL);
    }
}
