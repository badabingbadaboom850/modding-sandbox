#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "sprite.h"
#include "trio_silly.h"
#include "constants/map_groups.h"

struct SillyScene
{
    u16 map;
    u8 actors;
};

// Only actors visible before the scene starts. Box Bijuu is revealed after
// two objects are removed; she never receives a scripted movement.
static const struct SillyScene sScenes[] =
{
    {MAP_TRIO_SILLY_VALET, 5},
    {MAP_TRIO_SILLY_BOX, 6},
    {MAP_TRIO_SILLY_NOISE, 5},
    {MAP_TRIO_SILLY_HOTDOG, 5},
    {MAP_TRIO_SILLY_JAM, 10},
    {MAP_TRIO_SILLY_FISHING, 5},
    {MAP_TRIO_SILLY_APOLOGY, 7},
};

static const struct SillyScene *CurrentScene(void)
{
    for (u32 i = 0; i < ARRAY_COUNT(sScenes); i++)
        if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(sScenes[i].map)
            && gSaveBlock1Ptr->location.mapNum == MAP_NUM(sScenes[i].map))
            return &sScenes[i];
    return NULL;
}

bool32 TrioSilly_ActorsReady(void)
{
    const struct SillyScene *scene = CurrentScene();
    if (scene == NULL)
        return FALSE;
    for (u32 localId = 1; localId <= scene->actors; localId++)
    {
        u8 id;
        if (TryGetObjectEventIdByLocalIdAndMap(localId, MAP_NUM(scene->map), MAP_GROUP(scene->map), &id)
            || gObjectEvents[id].spriteId >= MAX_SPRITES
            || !gSprites[gObjectEvents[id].spriteId].inUse)
            return FALSE;
    }
    return TRUE;
}

void PrepareTrioSillyActors(void)
{
    const struct SillyScene *scene = CurrentScene();
    gSpecialVar_Result = FALSE;
    if (scene == NULL)
        return;
    for (u32 localId = 1; localId <= scene->actors; localId++)
    {
        u8 id;
        if (TryGetObjectEventIdByLocalIdAndMap(localId, MAP_NUM(scene->map), MAP_GROUP(scene->map), &id)
            && TrySpawnObjectEvent(localId, MAP_NUM(scene->map), MAP_GROUP(scene->map)) == OBJECT_EVENTS_COUNT)
            return;
    }
    gSpecialVar_Result = TrioSilly_ActorsReady();
}
