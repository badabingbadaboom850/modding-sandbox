#include "global.h"
#include "field_effect.h"
#include "field_weather.h"
#include "sprite.h"
#include "test/test.h"

TEST("Field effect cleanup keeps the weather palette after the last shadow disappears")
{
    u32 paletteNum;

    ResetSpriteData();
    FreeAllSpritePalettes();
    paletteNum = AllocSpritePalette(PALTAG_WEATHER);
    EXPECT(paletteNum < 16);

    FieldEffectFreePaletteIfUnused(paletteNum);

    EXPECT_EQ(IndexOfSpritePaletteTag(PALTAG_WEATHER), paletteNum);
    EXPECT(AllocSpritePalette(1234) != paletteNum);
    FreeAllSpritePalettes();
}

TEST("Field effect cleanup still frees unused effect palettes")
{
    u32 paletteNum;

    ResetSpriteData();
    FreeAllSpritePalettes();
    paletteNum = AllocSpritePalette(1234);
    EXPECT(paletteNum < 16);

    FieldEffectFreePaletteIfUnused(paletteNum);

    EXPECT_EQ(IndexOfSpritePaletteTag(1234), 0xFF);
    FreeAllSpritePalettes();
}

#include "field_effect_helpers.h"
#include "constants/field_effects.h"

extern u32 FldEff_SandFootprints(void);
extern u32 FldEff_DeepSandFootprints(void);
extern u32 FldEff_TracksBug(void);
extern u32 FldEff_TracksSpot(void);
extern u32 FldEff_BikeTireTracks(void);
extern u32 FldEff_TracksSlither(void);
extern void UpdateFootprintsTireTracksFieldEffect(struct Sprite *);

TEST("Cosmetic tracks tolerate full sprite pools and preserve actor headroom")
{
    u32 (*const effects[])(void) = {FldEff_SandFootprints, FldEff_DeepSandFootprints,
        FldEff_TracksBug, FldEff_TracksSpot, FldEff_BikeTireTracks, FldEff_TracksSlither};
    for (u32 count = MAX_SPRITES - 8; count <= MAX_SPRITES; count++)
    {
        ResetSpriteData();
        for (u32 i = 0; i < count; i++)
            gSprites[i].inUse = TRUE;
        for (u32 effect = 0; effect < ARRAY_COUNT(effects); effect++)
        {
            memset(gFieldEffectArguments, 0, sizeof(gFieldEffectArguments));
            effects[effect]();
            u32 used = 0;
            for (u32 i = 0; i < MAX_SPRITES; i++) used += gSprites[i].inUse;
            EXPECT_EQ(used, count);
        }
    }
    ResetSpriteData();
}

TEST("All footprint families share one bounded cosmetic pool")
{
    ResetSpriteData();
    for (u32 i = 0; i < 12; i++)
    {
        gSprites[i].inUse = TRUE;
        gSprites[i].callback = UpdateFootprintsTireTracksFieldEffect;
    }
    memset(gFieldEffectArguments, 0, sizeof(gFieldEffectArguments));
    FldEff_SandFootprints();
    FldEff_TracksSpot();
    u32 used = 0;
    for (u32 i = 0; i < MAX_SPRITES; i++) used += gSprites[i].inUse;
    EXPECT_EQ(used, 12);
    ResetSpriteData();
}
