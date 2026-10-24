#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "sprite.h"
#include "trio_silly.h"
#include "constants/map_groups.h"
#include "constants/vars.h"

TEST("Silly scenes reject missing actors wrong maps and dead sprites before movement")
{
    const u16 maps[] = {MAP_TRIO_SILLY_VALET, MAP_TRIO_SILLY_BOX,
        MAP_TRIO_SILLY_NOISE, MAP_TRIO_SILLY_HOTDOG, MAP_TRIO_SILLY_JAM,
        MAP_TRIO_SILLY_FISHING, MAP_TRIO_SILLY_APOLOGY};
    const u8 counts[] = {5, 6, 5, 5, 10, 5, 7};
    struct ObjectEvent savedObjects[OBJECT_EVENTS_COUNT];
    struct Sprite savedSprites[10];
    struct WarpData location = gSaveBlock1Ptr->location;
    memcpy(savedObjects, gObjectEvents, sizeof(savedObjects));
    memcpy(savedSprites, gSprites, sizeof(savedSprites));
    for (u32 m = 0; m < ARRAY_COUNT(maps); m++)
    {
        memset(gObjectEvents, 0, sizeof(gObjectEvents));
        gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(maps[m]);
        gSaveBlock1Ptr->location.mapNum = MAP_NUM(maps[m]);
        EXPECT(!TrioSilly_ActorsReady());
        for (u32 i = 0; i < counts[m]; i++)
        {
            gObjectEvents[i].active = TRUE;
            gObjectEvents[i].localId = i + 1;
            gObjectEvents[i].mapGroup = MAP_GROUP(maps[m]);
            gObjectEvents[i].mapNum = MAP_NUM(maps[m]);
            gObjectEvents[i].spriteId = i;
            gSprites[i].inUse = TRUE;
        }
        EXPECT(TrioSilly_ActorsReady());
        gObjectEvents[counts[m]-1].active = FALSE;
        EXPECT(!TrioSilly_ActorsReady());
        gObjectEvents[counts[m]-1].active = TRUE;
        gSprites[0].inUse = FALSE;
        EXPECT(!TrioSilly_ActorsReady());
        gSprites[0].inUse = TRUE;
        gObjectEvents[0].spriteId = MAX_SPRITES;
        EXPECT(!TrioSilly_ActorsReady());
        gObjectEvents[0].spriteId = 0;
        gObjectEvents[0].mapNum++;
        EXPECT(!TrioSilly_ActorsReady());
    }
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_GOLDENROD_CITY);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_GOLDENROD_CITY);
    VarSet(VAR_TRIO_GREG_WINS, 0xB53);
    EXPECT(!TrioSilly_ActorsReady());
    PrepareTrioSillyActors();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
    EXPECT_EQ(VarGet(VAR_TRIO_GREG_WINS), 0xB53);
    memcpy(gObjectEvents, savedObjects, sizeof(savedObjects));
    memcpy(gSprites, savedSprites, sizeof(savedSprites));
    gSaveBlock1Ptr->location = location;
}
