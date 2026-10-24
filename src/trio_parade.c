#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "sprite.h"
#include "trio_parade.h"
#include "constants/map_groups.h"

// Nine Poms, three spectators (including Scott), Penny and Bijuu. With the
// player and one follower, this uses the existing sixteen-object limit.
#define PARADE_ACTORS 14

static bool32 IsParadeMap(void)
{
    return gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_TRIO_POM_PARADE)
        && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_TRIO_POM_PARADE);
}

bool32 TrioParade_ActorsReady(void)
{
    if (!IsParadeMap())
        return FALSE;
    for (u32 localId = 1; localId <= PARADE_ACTORS; localId++)
    {
        u8 id;
        if (TryGetObjectEventIdByLocalIdAndMap(localId,
                MAP_NUM(MAP_TRIO_POM_PARADE), MAP_GROUP(MAP_TRIO_POM_PARADE), &id)
            || gObjectEvents[id].mapGroup != MAP_GROUP(MAP_TRIO_POM_PARADE)
            || gObjectEvents[id].mapNum != MAP_NUM(MAP_TRIO_POM_PARADE)
            || gObjectEvents[id].spriteId >= MAX_SPRITES
            || !gSprites[gObjectEvents[id].spriteId].inUse)
            return FALSE;
    }
    return TRUE;
}

void PrepareTrioParadeActors(void)
{
    gSpecialVar_Result = FALSE;
    if (!IsParadeMap())
        return;
    // Explicitly load the rear of the procession outside the initial viewport.
    // Abort to the ordinary street if any allocation fails; never issue a
    // scripted movement against the missing-object sentinel.
    for (u32 localId = 1; localId <= PARADE_ACTORS; localId++)
    {
        u8 id;
        if (TryGetObjectEventIdByLocalIdAndMap(localId,
                MAP_NUM(MAP_TRIO_POM_PARADE), MAP_GROUP(MAP_TRIO_POM_PARADE), &id)
            && TrySpawnObjectEvent(localId, MAP_NUM(MAP_TRIO_POM_PARADE),
                MAP_GROUP(MAP_TRIO_POM_PARADE)) == OBJECT_EVENTS_COUNT)
            return;
    }
    gSpecialVar_Result = TrioParade_ActorsReady();
}
