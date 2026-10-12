#include "global.h"
#include "test/test.h"
#include "decompress.h"
#include "item.h"
#include "item_icon.h"
#include "sprite.h"
#include "malloc.h"
#include "window.h"
#include "bg.h"
#include "constants/items.h"

static const u32 sWandRaw[] = INCBIN_U32("graphics/items/icons/rikos_wand.4bpp");

TEST("Rikos Wand icon decompresses within the exact Bag buffer and matches the source tiles")
{
    struct {
        u32 before;
        u32 tiles[0x120 / 4];
        u32 after;
    } buffer;
    buffer.before = 0xDEADBEEF;
    buffer.after = 0xDEADBEEF;
    EXPECT_EQ(GetDecompressedDataSize(GetItemIconPic(ITEM_RIKOS_WAND)), 0x120);
    DecompressDataWithHeaderWram(GetItemIconPic(ITEM_RIKOS_WAND), buffer.tiles);
    EXPECT_EQ(buffer.before, 0xDEADBEEF);
    EXPECT_EQ(buffer.after, 0xDEADBEEF);
    for (u32 i = 0; i < ARRAY_COUNT(buffer.tiles); i++)
        EXPECT_EQ(buffer.tiles[i], sWandRaw[i]);
}

TEST("Rikos Wand survives repeated native Bag icon creation and destruction")
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    for (u32 i = 0; i < 20; i++)
    {
        u8 spriteId = AddItemIconSprite(0xCAFE, 0xCAFE, ITEM_RIKOS_WAND);
        EXPECT_NE(spriteId, MAX_SPRITES);
        EXPECT(gSprites[spriteId].inUse);
        DestroySpriteAndFreeResources(&gSprites[spriteId]);
    }
}

TEST("Bag icon decompression allocation fits the two 32x32 Bijuu icons")
{
    EXPECT(AllocItemIconTemporaryBuffers());
    struct MemBlock *block = (struct MemBlock *)(gItemIconDecompressionBuffer - sizeof(struct MemBlock));
    EXPECT_GE((u32)block->size, GetDecompressedDataSize(GetItemIconPic(ITEM_BIJUUS_FISH_TOY)));
    EXPECT_GE((u32)block->size, GetDecompressedDataSize(GetItemIconPic(ITEM_BIJUUS_CAT_NIP)));
    FreeItemIconTemporaryBuffers();
}

static const u32 sFishToyRaw[] = INCBIN_U32("graphics/items/icons/bijuus_fish_toy.4bpp");
static const u32 sCatNipRaw[] = INCBIN_U32("graphics/items/icons/bijuus_cat_nip.4bpp");

TEST("Both 32x32 Bijuu Bag icons reach VRAM intact with repeatable heap allocation and intact guard data")
{
    const u16 items[] = {ITEM_BIJUUS_FISH_TOY, ITEM_BIJUUS_CAT_NIP};
    const u32 *raw[] = {sFishToyRaw, sCatNipRaw};
    ResetSpriteData();
    FreeAllSpritePalettes();
    for (u32 repeat = 0; repeat < 10; repeat++)
        for (u32 i = 0; i < ARRAY_COUNT(items); i++)
        {
            u32 *guard = Alloc(32);
            EXPECT(guard != NULL);
            for (u32 b = 0; b < 8; b++)
                guard[b] = 0xDEADBEEF;
            u8 spriteId = AddItemIconSprite(0xCAFE, 0xCAFE, items[i]);
            EXPECT_NE(spriteId, MAX_SPRITES);
            u16 start = GetSpriteTileStartByTag(0xCAFE);
            EXPECT_NE(start, 0xffff);
            const volatile u32 *actual = (const volatile u32 *)(OBJ_VRAM0 + start * 32);
            for (u32 b = 0; b < 0x200 / 4; b++)
                EXPECT_EQ(actual[b], raw[i][b]);
            for (u32 b = 0; b < 8; b++)
                EXPECT_EQ(guard[b], 0xDEADBEEF);
            DestroySpriteAndFreeResources(&gSprites[spriteId]);
            Free(guard);
        }
}

TEST("Registered item icons fit supported Bag source dimensions including every family item")
{
    u32 large = 0;
    for (u32 item = 0; item < ITEMS_COUNT; item++)
    {
        const u32 *pic = GetItemIconPic(item);
        if (pic == NULL)
            continue;
        u32 size = GetDecompressedDataSize(pic);
        EXPECT(size == 0x120 || size == 0x200);
        large += size == 0x200;
    }
    EXPECT_EQ(large, 2);
}

TEST("Rikos Wand evolution selection preserves actual party data")
{
    struct Pokemon mon;
    CreateMon(&mon, SPECIES_RIKO, 20, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, ITEM_RIKOS_WAND, NULL, NULL, CHECK_EVO), SPECIES_RIKO_WING);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_RIKO);
    CreateMon(&mon, SPECIES_BIJUU, 20, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, ITEM_RIKOS_WAND, NULL, NULL, CHECK_EVO), SPECIES_NONE);
}

TEST("Custom-template item sprites also preserve full 32x32 Bijuu art")
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    u8 spriteId = AddCustomItemIconSprite(&gItemIconSpriteTemplate, 0xCAFE, 0xCAFE, ITEM_BIJUUS_FISH_TOY);
    EXPECT_NE(spriteId, MAX_SPRITES);
    u16 start = GetSpriteTileStartByTag(0xCAFE);
    const volatile u32 *actual = (const volatile u32 *)(OBJ_VRAM0 + start * 32);
    for (u32 b = 0; b < 0x200 / 4; b++)
        EXPECT_EQ(actual[b], sFishToyRaw[b]);
    DestroySpriteAndFreeResources(&gSprites[spriteId]);
}

TEST("Window item icons preserve full 32x32 Bijuu art and its palette")
{
    const struct BgTemplate bg = {.bg = 0};
    const struct WindowTemplate windows[] = {
        {.bg = 0, .width = 4, .height = 4, .paletteNum = 1},
        DUMMY_WIN_TEMPLATE,
    };
    u16 palette[16];
    InitBgsFromTemplates(0, &bg, 1);
    EXPECT(InitWindows(windows));
    EXPECT_EQ(BlitItemIconToWindow(ITEM_BIJUUS_CAT_NIP, 0, 0, 0, palette), 0);
    const u32 *actual = (const u32 *)GetWindowAttribute(0, WINDOW_TILE_DATA);
    for (u32 b = 0; b < 0x200 / 4; b++)
        EXPECT_EQ(actual[b], sCatNipRaw[b]);
    const u16 *expectedPalette = GetItemIconPalette(ITEM_BIJUUS_CAT_NIP);
    for (u32 i = 0; i < 16; i++)
        EXPECT_EQ(palette[i], expectedPalette[i]);
    FreeAllWindowBuffers();
}
