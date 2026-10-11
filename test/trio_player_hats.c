#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "trio_player_hats.h"
#include "constants/event_objects.h"
#include "constants/trainers.h"
#include "constants/vars.h"

TEST("Player hats preserve historical IDs and the saved ABI")
{
    EXPECT_EQ(sizeof(struct SaveBlock1), 15444);
    EXPECT_EQ(sizeof(struct SaveBlock2), 2864);
    EXPECT_EQ(NUM_OBJ_EVENT_GFX, 330);
    EXPECT_EQ(OBJ_EVENT_GFX_VARS, 331);
    EXPECT_EQ(VAR_TRIO_PLAYER_HAT, 0x4144);
    VarSet(VAR_TRIO_PLAYER_HAT, 0);
    EXPECT_EQ(TrioPlayerHat_Graphics(OBJ_EVENT_GFX_MAY_NORMAL, FEMALE), OBJ_EVENT_GFX_MAY_NORMAL);
    EXPECT_EQ(TrioPlayerHat_BackPic(FEMALE), TRAINER_PIC_BACK_MAY);
}

TEST("Every female avatar state keeps native animation geometry for all hats")
{
    for (u32 hat = 0; hat < TRIO_PLAYER_HAT_COUNT; hat++)
    {
        VarSet(VAR_TRIO_PLAYER_HAT, hat);
        gPlayerAvatar.gender = FEMALE;
        for (u32 state = 0; state <= PLAYER_AVATAR_STATE_VSSEEKER; state++)
        {
            u16 id = GetPlayerAvatarGraphicsIdByStateId(state);
            u16 base = TrioPlayerHat_BaseGraphics(id);
            const struct ObjectEventGraphicsInfo *info = GetObjectEventGraphicsInfo(id);
            const struct ObjectEventGraphicsInfo *original = GetObjectEventGraphicsInfo(base);
            EXPECT_EQ(GetPlayerAvatarGenderByGraphicsId(id), FEMALE);
            EXPECT_EQ(info->width, original->width);
            EXPECT_EQ(info->height, original->height);
            EXPECT_EQ(info->paletteTag, original->paletteTag);
            EXPECT_EQ(info->anims, original->anims);
            EXPECT_EQ(TrioPlayerHat_Graphics(id, FEMALE), id);
            EXPECT_EQ(TrioPlayerHat_Graphics(base, MALE), base);
        }
        EXPECT_EQ(TrioPlayerHat_Graphics(OBJ_EVENT_GFX_RIVAL_MAY_NORMAL, FEMALE), OBJ_EVENT_GFX_RIVAL_MAY_NORMAL);
        EXPECT_EQ(TrioPlayerHat_BackPic(MALE), TRAINER_PIC_BACK_BRENDAN);
        EXPECT_EQ(TrioPlayerHat_FrontPic(MALE), TRAINER_PIC_FRONT_BRENDAN);
    }
}

TEST("Player hat trainer art uses complete battle frames and the existing palettes")
{
    for (u32 hat = 0; hat < TRIO_PLAYER_HAT_COUNT; hat++)
    {
        VarSet(VAR_TRIO_PLAYER_HAT, hat);
        u16 front = TrioPlayerHat_FrontPic(FEMALE), back = TrioPlayerHat_BackPic(FEMALE);
        EXPECT_EQ(gTrainerSprites[front].palette.data, gTrainerSprites[TRAINER_PIC_FRONT_MAY].palette.data);
        EXPECT_EQ(gTrainerBacksprites[back].palette.data, gTrainerBacksprites[TRAINER_PIC_BACK_MAY].palette.data);
        EXPECT_EQ(gTrainerBacksprites[back].backPic.size, TRAINER_PIC_SIZE);
        EXPECT_EQ(gTrainerBacksprites[back].coordinates.y_offset, 4);
        EXPECT_EQ(gTrainerBacksprites[back].animation, gTrainerBacksprites[TRAINER_PIC_BACK_MAY].animation);
    }
}

TEST("Invalid saved hat choices fall back safely without rewriting progress")
{
    VarSet(VAR_TRIO_ROAD_COMPLETE, 1);
    VarSet(VAR_TRIO_PLAYER_HAT, 0xffff);
    EXPECT_EQ(TrioPlayerHat_GetStyle(), 0);
    EXPECT_EQ(TrioPlayerHat_Graphics(OBJ_EVENT_GFX_MAY_NORMAL, FEMALE), OBJ_EVENT_GFX_MAY_NORMAL);
    EXPECT_EQ(TrioPlayerHat_BackPic(FEMALE), TRAINER_PIC_BACK_MAY);
    EXPECT_EQ(VarGet(VAR_TRIO_PLAYER_HAT), 0xffff);
    EXPECT_EQ(VarGet(VAR_TRIO_ROAD_COMPLETE), 1);
}

TEST("Family hats appear only on foot and restore across activity changes")
{
    for (u32 hat = 3; hat < TRIO_PLAYER_HAT_COUNT; hat++)
    {
        VarSet(VAR_TRIO_PLAYER_HAT, hat);
        u16 walking = TrioPlayerHat_Graphics(OBJ_EVENT_GFX_MAY_NORMAL, FEMALE);
        EXPECT_EQ(walking, TRIO_PLAYER_FAMILY_HAT_GFX_BASE + hat - 3);
        EXPECT_EQ(TrioPlayerHat_BaseGraphics(walking), OBJ_EVENT_GFX_MAY_NORMAL);
        EXPECT_EQ(TrioPlayerHat_Graphics(walking, FEMALE), walking);
        EXPECT_EQ(TrioPlayerHat_Graphics(walking, MALE), OBJ_EVENT_GFX_MAY_NORMAL);
        const struct ObjectEventGraphicsInfo *info = GetObjectEventGraphicsInfo(walking);
        const struct ObjectEventGraphicsInfo *base = GetObjectEventGraphicsInfo(OBJ_EVENT_GFX_MAY_NORMAL);
        EXPECT(info != base);
        EXPECT_EQ(info->size, base->size);
        EXPECT_EQ(info->images[0].size, base->images[0].size);
        EXPECT(info->images[0].data != base->images[0].data);
        for (u32 state = PLAYER_AVATAR_STATE_MACH_BIKE; state <= PLAYER_AVATAR_STATE_VSSEEKER; state++)
        {
            gPlayerAvatar.gender = FEMALE;
            u16 id = GetPlayerAvatarGraphicsIdByStateId(state);
            if (TrioPlayerHat_BaseGraphics(id) != OBJ_EVENT_GFX_MAY_NORMAL)
                EXPECT_EQ(id, TrioPlayerHat_BaseGraphics(id));
        }
        EXPECT_EQ(TrioPlayerHat_Graphics(OBJ_EVENT_GFX_MAY_MACH_BIKE, FEMALE), OBJ_EVENT_GFX_MAY_MACH_BIKE);
        EXPECT_EQ(TrioPlayerHat_Graphics(OBJ_EVENT_GFX_MAY_FISHING, FEMALE), OBJ_EVENT_GFX_MAY_FISHING);
        EXPECT_EQ(TrioPlayerHat_FrontPic(FEMALE), TRAINER_PIC_FRONT_MAY);
        EXPECT_EQ(TrioPlayerHat_BackPic(FEMALE), TRAINER_PIC_BACK_MAY);
        EXPECT_EQ(VarGet(VAR_TRIO_PLAYER_HAT), hat);
        EXPECT_EQ(TrioPlayerHat_Graphics(OBJ_EVENT_GFX_MAY_NORMAL, FEMALE), walking);
    }
}
