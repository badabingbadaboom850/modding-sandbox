#include "global.h"
#include "event_data.h"
#include "trio_roadtrip.h"
#include "constants/map_groups.h"
#include "constants/opponents.h"
#include "constants/vars.h"

static u16 RoadBattleBit(u16 trainerId)
{
    switch (trainerId)
    {
    case TRAINER_ROAD_BEACH: return 1;
    case TRAINER_ROAD_FOREST: return 2;
    case TRAINER_ROAD_SCOTT: return 4;
    default: return 0;
    }
}

bool32 TrioRoad_IsTrainer(u16 trainerId)
{
    return RoadBattleBit(trainerId) != 0;
}

bool32 TrioRoad_IsFriendlyBattle(u8 mapGroup, u8 mapNum, u16 trainerId)
{
    return mapGroup == MAP_GROUP(MAP_TRIO_ROAD_ISLAND)
        && mapNum == MAP_NUM(MAP_TRIO_ROAD_ISLAND)
        && TrioRoad_IsTrainer(trainerId);
}

bool32 TrioRoad_HasWon(u16 trainerId)
{
    u16 bit = RoadBattleBit(trainerId);
    return bit != 0 && (VarGet(VAR_TRIO_ROAD_BATTLES) & bit) != 0;
}

// Only called from the won branch; these trainers' ordinary flag addresses
// belong to unrelated Rinto/Vajra/Ariana quests and must never be touched.
void TrioRoad_RecordBattleWin(void)
{
    u16 bit = RoadBattleBit(gSpecialVar_0x8004);
    if (bit != 0)
        VarSet(VAR_TRIO_ROAD_BATTLES, VarGet(VAR_TRIO_ROAD_BATTLES) | bit);
}

// A saved return port makes native island save/reload independent of scratch vars.
void TrioRoad_RecordDeparture(void)
{
    u16 visits = VarGet(VAR_TRIO_ROAD_VISITS);
    VarSet(VAR_TRIO_ROAD_RETURN,
        gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_OLIVINE_CITY_PORT_OUTSIDE)
        && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_OLIVINE_CITY_PORT_OUTSIDE));
    if (visits < 3)
        VarSet(VAR_TRIO_ROAD_VISITS, visits + 1);
}
