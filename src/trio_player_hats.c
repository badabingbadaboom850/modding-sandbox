#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "sprite.h"
#include "trio_player_hats.h"
#include "constants/event_objects.h"
#include "constants/trainers.h"
#include "constants/vars.h"

static const u16 sBaseGraphics[TRIO_PLAYER_HAT_GFX_STATES] = {
    OBJ_EVENT_GFX_MAY_NORMAL, OBJ_EVENT_GFX_MAY_MACH_BIKE,
    OBJ_EVENT_GFX_MAY_ACRO_BIKE, OBJ_EVENT_GFX_MAY_SURFING,
    OBJ_EVENT_GFX_MAY_FIELD_MOVE, OBJ_EVENT_GFX_MAY_UNDERWATER,
    OBJ_EVENT_GFX_MAY_FISHING, OBJ_EVENT_GFX_MAY_WATERING,
    OBJ_EVENT_GFX_MAY_DECORATING,
};

u32 TrioPlayerHat_GetStyle(void)
{
    u32 style = VarGet(VAR_TRIO_PLAYER_HAT);
    return style < TRIO_PLAYER_HAT_COUNT ? style : 0;
}

u16 TrioPlayerHat_BaseGraphics(u16 graphicsId)
{
    if (graphicsId >= TRIO_PLAYER_HAT_GFX_BASE && graphicsId < TRIO_PLAYER_HAT_GFX_BASE + 2 * TRIO_PLAYER_HAT_GFX_STATES)
        return sBaseGraphics[(graphicsId - TRIO_PLAYER_HAT_GFX_BASE) % TRIO_PLAYER_HAT_GFX_STATES];
    return graphicsId;
}

u16 TrioPlayerHat_Graphics(u16 graphicsId, u32 gender)
{
    u32 style = TrioPlayerHat_GetStyle();
    graphicsId = TrioPlayerHat_BaseGraphics(graphicsId);
    if (gender == FEMALE && style)
        for (u32 i = 0; i < ARRAY_COUNT(sBaseGraphics); i++)
            if (graphicsId == sBaseGraphics[i])
                return TRIO_PLAYER_HAT_GFX_BASE + (style - 1) * TRIO_PLAYER_HAT_GFX_STATES + i;
    return graphicsId;
}

u16 TrioPlayerHat_FrontPic(u32 gender)
{
    if (gender != FEMALE) return TRAINER_PIC_FRONT_BRENDAN;
    switch (TrioPlayerHat_GetStyle())
    {
    case 1: return TRAINER_PIC_FRONT_MAY_BOW;
    case 2: return TRAINER_PIC_FRONT_MAY_SUNHAT;
    default: return TRAINER_PIC_FRONT_MAY;
    }
}

u16 TrioPlayerHat_BackPic(u32 gender)
{
    if (gender != FEMALE) return TRAINER_PIC_BACK_BRENDAN;
    switch (TrioPlayerHat_GetStyle())
    {
    case 1: return TRAINER_PIC_BACK_MAY_BOW;
    case 2: return TRAINER_PIC_BACK_MAY_SUNHAT;
    default: return TRAINER_PIC_BACK_MAY;
    }
}

void ApplyTrioPlayerHat(void)
{
    if (gSpecialVar_Result >= TRIO_PLAYER_HAT_COUNT || gPlayerAvatar.gender != FEMALE)
        return;
    VarSet(VAR_TRIO_PLAYER_HAT, gSpecialVar_Result);
    struct ObjectEvent *player = &gObjectEvents[gPlayerAvatar.objectEventId];
    ObjectEventSetGraphicsId(player, TrioPlayerHat_Graphics(player->graphicsId, FEMALE));
    StartSpriteAnim(&gSprites[player->spriteId], GetFaceDirectionAnimNum(player->facingDirection));
}
