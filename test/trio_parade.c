#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "sprite.h"
#include "trio_parade.h"
#include "constants/map_groups.h"
#include "constants/vars.h"

TEST("Parade movement requires all fourteen live actors on the exact staged map")
{
    struct ObjectEvent savedObjects[OBJECT_EVENTS_COUNT];
    struct Sprite savedSprites[14];
    struct WarpData savedLocation = gSaveBlock1Ptr->location;
    memcpy(savedObjects, gObjectEvents, sizeof(savedObjects));
    memcpy(savedSprites, gSprites, sizeof(savedSprites));
    memset(gObjectEvents, 0, sizeof(gObjectEvents));
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TRIO_POM_PARADE);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TRIO_POM_PARADE);
    EXPECT(!TrioParade_ActorsReady());
    for (u32 i = 0; i < 14; i++)
    {
        gObjectEvents[i].active = TRUE;
        gObjectEvents[i].localId = i + 1;
        gObjectEvents[i].mapGroup = MAP_GROUP(MAP_TRIO_POM_PARADE);
        gObjectEvents[i].mapNum = MAP_NUM(MAP_TRIO_POM_PARADE);
        gObjectEvents[i].spriteId = i;
        gSprites[i].inUse = TRUE;
    }
    EXPECT(TrioParade_ActorsReady());
    gObjectEvents[8].active = FALSE;
    EXPECT(!TrioParade_ActorsReady());
    gObjectEvents[8].active = TRUE;
    gSprites[8].inUse = FALSE;
    EXPECT(!TrioParade_ActorsReady());
    gSprites[8].inUse = TRUE;
    gObjectEvents[8].spriteId = MAX_SPRITES;
    EXPECT(!TrioParade_ActorsReady());
    gObjectEvents[8].spriteId = 8;
    gObjectEvents[8].mapNum++;
    EXPECT(!TrioParade_ActorsReady());
    gObjectEvents[8].mapNum--;
    VarSet(VAR_TRIO_POM_PARADE, 1);
    VarSet(VAR_TRIO_GREG_WINS, 0xB53);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_GOLDENROD_CITY);
    EXPECT(!TrioParade_ActorsReady());
    PrepareTrioParadeActors();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT_EQ(VarGet(VAR_TRIO_POM_PARADE), 1);
    EXPECT_EQ(VarGet(VAR_TRIO_GREG_WINS), 0xB53);
    memcpy(gObjectEvents, savedObjects, sizeof(savedObjects));
    memcpy(gSprites, savedSprites, sizeof(savedSprites));
    gSaveBlock1Ptr->location = savedLocation;
}
