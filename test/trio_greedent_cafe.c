#include "global.h"
#include "test/test.h"
#include "overworld.h"
#include "event_data.h"
#include "constants/map_groups.h"
#include "constants/vars.h"
#include "constants/event_objects.h"
#include "constants/species.h"
#include "constants/trainer_types.h"

extern const u8 TrioSilly_ApologyOffer[];

TEST("Greedent cafe replaces only its Vermilion house after final victory including full Bag winners")
{
    u32 wins, phase, active;
    const struct MapHeader *house = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_VERMILION_CITY_HOUSE3), MAP_NUM(MAP_VERMILION_CITY_HOUSE3));
    const struct MapHeader *cafe = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TRIO_GREEDENT_CAFE), MAP_NUM(MAP_TRIO_GREEDENT_CAFE));
    for (wins = 0; wins <= 6; wins++)
        for (phase = 0; phase <= 2; phase++)
            for (active = 0; active <= 6; active++)
            {
                bool32 unlocked = wins == 6 || (active == 6 && phase == 2);
                VarSet(VAR_TRIO_GANG_WINS, wins);
                VarSet(VAR_TRIO_GANG_PHASE, phase);
                VarSet(VAR_TRIO_GANG_ACTIVE_WAVE, active);
                VarSet(VAR_TRIO_CAFE_TEST_RETURN, 1);
                SetWarpDestinationToMapWarp(MAP_GROUP(MAP_VERMILION_CITY_HOUSE3), MAP_NUM(MAP_VERMILION_CITY_HOUSE3), 0);
                EXPECT_EQ(GetDestinationWarpMapHeader(), unlocked ? cafe : house);
                EXPECT_EQ(VarGet(VAR_TRIO_CAFE_TEST_RETURN), 1);
                EXPECT_EQ(VarGet(VAR_TRIO_GANG_WINS), wins);
                EXPECT_EQ(VarGet(VAR_TRIO_GANG_PHASE), phase);
                EXPECT_EQ(VarGet(VAR_TRIO_GANG_ACTIVE_WAVE), active);
            }
    SetWarpDestinationToMapWarp(MAP_GROUP(MAP_VERMILION_CITY_HOUSE2), MAP_NUM(MAP_VERMILION_CITY_HOUSE2), 0);
    EXPECT_EQ(GetDestinationWarpMapHeader(), Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_VERMILION_CITY_HOUSE2), MAP_NUM(MAP_VERMILION_CITY_HOUSE2)));
}

TEST("Greedent cafe native exit ignores retired test mode and returns to Vermilion without affecting other city warps")
{
    struct WarpData old = gSaveBlock1Ptr->location;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TRIO_GREEDENT_CAFE);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TRIO_GREEDENT_CAFE);
    VarSet(VAR_TRIO_CAFE_TEST_RETURN, 1);
    SetWarpDestinationToMapWarp(MAP_GROUP(MAP_VERMILION_CITY), MAP_NUM(MAP_VERMILION_CITY), 7);
    EXPECT_EQ(GetDestinationWarpMapHeader(), Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_VERMILION_CITY), MAP_NUM(MAP_VERMILION_CITY)));
    SetWarpDestinationToMapWarp(MAP_GROUP(MAP_VERMILION_CITY), MAP_NUM(MAP_VERMILION_CITY), 0);
    EXPECT_EQ(GetDestinationWarpMapHeader(), Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_VERMILION_CITY), MAP_NUM(MAP_VERMILION_CITY)));
    VarSet(VAR_TRIO_CAFE_TEST_RETURN, 0);
    SetWarpDestinationToMapWarp(MAP_GROUP(MAP_VERMILION_CITY), MAP_NUM(MAP_VERMILION_CITY), 7);
    EXPECT_EQ(GetDestinationWarpMapHeader(), Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_VERMILION_CITY), MAP_NUM(MAP_VERMILION_CITY)));
    gSaveBlock1Ptr->location = old;
}

TEST("Greedent cafe registrations retain original employees and the appended apology clerk")
{
    const struct MapHeader *cafe = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TRIO_GREEDENT_CAFE), MAP_NUM(MAP_TRIO_GREEDENT_CAFE));
    const struct MapHeader *source = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_OLIVINE_CITY_CAFE), MAP_NUM(MAP_OLIVINE_CITY_CAFE));
    EXPECT_EQ(cafe->mapLayout, source->mapLayout);
    EXPECT_EQ((u32)cafe->events->objectEventCount, 10);
    const struct ObjectEventTemplate *clerk = &cafe->events->objectEvents[9];
    EXPECT_EQ(clerk->graphicsId, OBJ_EVENT_GFX_SPECIES(GREEDENT));
    EXPECT_EQ(clerk->x, 4);
    EXPECT_EQ(clerk->y, 6);
    EXPECT_EQ(clerk->trainerType, TRAINER_TYPE_NONE);
    EXPECT_EQ(clerk->script, TrioSilly_ApologyOffer);
    EXPECT_EQ((u32)cafe->events->warpCount, 1);
    EXPECT_EQ(MAP_NUM(MAP_TRIO_GREEDENT_CAFE), 9);
    EXPECT_EQ(MAP_NUM(MAP_VERMILION_CITY_HOUSE3), 8);
    EXPECT_EQ(sizeof(struct SaveBlock1), 15444);
    EXPECT_EQ(sizeof(struct SaveBlock2), 2864);
    EXPECT_EQ(sizeof(struct SaveBlock3), 100);
}
