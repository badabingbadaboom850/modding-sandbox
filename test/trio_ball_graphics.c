#include "global.h"
#include "test/test.h"
#include "decompress.h"
#include "pokeball.h"
#include "sprite.h"
#include "constants/items.h"

static const u8 sCustomBalls[] = {BALL_GREAT, BALL_ULTRA, BALL_MOON, BALL_LOVE};
static const u16 sCustomItems[] = {ITEM_GREAT_BALL, ITEM_ULTRA_BALL, ITEM_MOON_BALL, ITEM_LOVE_BALL};

TEST("Custom ball graphics preserve historical item and capture ball IDs")
{
    for (u32 i = 0; i < ARRAY_COUNT(sCustomBalls); i++)
    {
        const struct PokeBallSprite *ball = &gPokeBalls[sCustomBalls[i]];
        EXPECT_EQ(ball->itemId, sCustomItems[i]);
        EXPECT_EQ(ball->pic.size, 384);
        EXPECT_EQ(ball->spriteTemplate.tileTag, ball->pic.tag);
        EXPECT_EQ(ball->spriteTemplate.paletteTag, ball->palette.tag);
    }
}

TEST("Custom ball closed and opening frames survive the actual VRAM loader")
{
    u8 expected[384] __attribute__((aligned(4)));
    ResetSpriteData();
    FreeAllSpritePalettes();
    for (u32 i = 0; i < ARRAY_COUNT(sCustomBalls); i++)
    {
        const struct PokeBallSprite *ball = &gPokeBalls[sCustomBalls[i]];
        DecompressDataWithHeaderWram(ball->pic.data, expected);
        LoadBallGfx(sCustomBalls[i]);
        u16 start = GetSpriteTileStartByTag(ball->pic.tag);
        EXPECT_NE(start, 0xffff);
        const volatile u8 *actual = (const volatile u8 *)(OBJ_VRAM0 + start * 32);
        for (u32 b = 0; b < sizeof(expected); b++)
            EXPECT_EQ(actual[b], expected[b]);
        FreeBallGfx(sCustomBalls[i]);
    }
}
