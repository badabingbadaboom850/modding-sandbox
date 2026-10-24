#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "item.h"
#include "string_util.h"
#include "constants/characters.h"
#include "trio_camp.h"
#include "trio_outfits.h"
#include "test/test.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/vars.h"

TEST("Outfit portraits record each costume and Poison once without duplicate Penny stage pages")
{
    static const u16 outfits[] = {SPECIES_RIKO_BALLOON, SPECIES_RIKO_PRINCESS, SPECIES_RIKO_RAINCOAT, SPECIES_BIJUU_BOX, SPECIES_BIJUU_BREAD, SPECIES_BIJUU_DETECTIVE, SPECIES_PENNY_HOTDOG, SPECIES_PENNY_BLANKET, SPECIES_PENNY_LIFEGUARD, SPECIES_BIJUU_POISON};
    VarSet(VAR_TRIO_SEASONAL_PHOTOS, 0);
    VarSet(VAR_TRIO_OUTFIT_PHOTOS, 0);
    for (u32 i = 0; i < ARRAY_COUNT(outfits); i++)
    {
        TrioOutfits_RecordPhoto(outfits[i]);
        EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), (1u << (i + 1)) - 1);
        gSpecialVar_0x8004 = i;
        EXPECT(HasTrioOutfitPhoto());
    }
    TrioOutfits_RecordPhoto(SPECIES_PENNY_HOTDOG_DACHSBUN);
    TrioOutfits_RecordPhoto(SPECIES_PENNY_BLANKET_DACHSBUN);
    TrioOutfits_RecordPhoto(SPECIES_PENNY_LIFEGUARD_DACHSBUN);
    TrioOutfits_RecordPhoto(SPECIES_RIKO);
    TrioOutfits_RecordPhoto(SPECIES_PIKACHU);
    EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), 0x3FF);
    gSpecialVar_0x8004 = 28;
    EXPECT_EQ(HasTrioOutfitPhoto(), FALSE);
    gSpecialVar_0x8004 = 0xFFFF;
    EXPECT_EQ(HasTrioOutfitPhoto(), FALSE);
}

TEST("Outfit reactions match each girl and ignore eggs and empty party slots")
{
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_RIKO_PRINCESS, 5, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_BIJUU_POISON, 5, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[2], SPECIES_PENNY_BLANKET_DACHSBUN, 30, 0, OTID_STRUCT_PLAYER_ID);
    static const u16 expected[] = {2,10,8,2};
    for (u32 i = 0; i < ARRAY_COUNT(expected); i++)
    {
        gSpecialVar_0x8004 = i;
        EXPECT_EQ(GetTrioOutfitReaction(), expected[i]);
    }
    bool32 egg = TRUE;
    SetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, &egg);
    gSpecialVar_0x8004 = 0;
    EXPECT_EQ(GetTrioOutfitReaction(), 0);
    gSpecialVar_0x8004 = 3;
    EXPECT_EQ(GetTrioOutfitReaction(), 10);
    VarSet(VAR_TRIO_SEASONAL_PHOTOS, 0);
    VarSet(VAR_TRIO_OUTFIT_PHOTOS, 0);
    TrioOutfits_RecordPartyPhotos();
    EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), (1u << 9) | (1u << 7));
    ZeroPlayerPartyMons();
    EXPECT_EQ(GetTrioOutfitReaction(), 0);
}

TEST("Existing dressed saves and evolution hooks earn permanent album portraits")
{
    ZeroPlayerPartyMons();
    VarSet(VAR_TRIO_SEASONAL_PHOTOS, 0);
    VarSet(VAR_TRIO_OUTFIT_PHOTOS, 1);
    CreateMon(&gPlayerParty[0], SPECIES_BIJUU_DETECTIVE, 20, 0, OTID_STRUCT_PLAYER_ID);
    TrioOutfits_RecordPartyPhotos();
    EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), 1 | (1u << 5));
    TrioCamp_RecordEvolution(SPECIES_FIDOUGH, SPECIES_PENNY_LIFEGUARD, ITEM_PENNYS_BEACH_VEST);
    EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), 1 | (1u << 5) | (1u << 8));
    TrioCamp_RecordEvolution(SPECIES_PENNY_LIFEGUARD, SPECIES_FIDOUGH, ITEM_PENNYS_BEACH_VEST);
    EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), 1 | (1u << 5) | (1u << 8));
    BufferTrioOutfitPhotoCount();
    EXPECT_EQ(gStringVar1[0], CHAR_0 + 3);
}

TEST("New cosmetic portraits append without altering earned old photos")
{
    static const u16 forms[] = {SPECIES_RIKO_BUTTERFLY, SPECIES_BIJUU_ASTRONAUT, SPECIES_PENNY_BALLERINA};
    VarSet(VAR_TRIO_SEASONAL_PHOTOS, 0);
    VarSet(VAR_TRIO_OUTFIT_PHOTOS, 0x3FF);
    ZeroPlayerPartyMons();
    for (u32 i = 0; i < ARRAY_COUNT(forms); i++)
    {
        CreateMon(&gPlayerParty[i], forms[i], 30, 0, OTID_STRUCT_PLAYER_ID);
        TrioOutfits_RecordPhoto(forms[i]);
        gSpecialVar_0x8004 = i;
        EXPECT_EQ(GetTrioOutfitReaction(), 11 + i);
        gSpecialVar_0x8004 = 10 + i;
        EXPECT(HasTrioOutfitPhoto());
    }
    EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), 0x1FFF);
    TrioOutfits_RecordPhoto(SPECIES_PENNY_BALLERINA_DACHSBUN);
    EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), 0x1FFF);
    BufferTrioOutfitPhotoCount();
    EXPECT_EQ(gStringVar1[0], CHAR_0 + 1);
    EXPECT_EQ(gStringVar1[1], CHAR_0 + 2);
    gSpecialVar_0x8004 = 28;
    EXPECT_EQ(HasTrioOutfitPhoto(), FALSE);
}

TEST("Halloween portraits fill final mask bits without erasing historical photos")
{
    static const u16 forms[] = {SPECIES_RIKO_WITCH, SPECIES_BIJUU_VAMPIRE, SPECIES_PENNY_PUMPKIN};
    VarSet(VAR_TRIO_SEASONAL_PHOTOS, 0);
    VarSet(VAR_TRIO_OUTFIT_PHOTOS, 0x1FFF);
    ZeroPlayerPartyMons();
    for (u32 i = 0; i < ARRAY_COUNT(forms); i++)
    {
        CreateMon(&gPlayerParty[i], forms[i], 30, 0, OTID_STRUCT_PLAYER_ID);
        TrioOutfits_RecordPhoto(forms[i]);
        gSpecialVar_0x8004 = i;
        EXPECT_EQ(GetTrioOutfitReaction(), 14 + i);
        gSpecialVar_0x8004 = 13 + i;
        EXPECT(HasTrioOutfitPhoto());
    }
    EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), 0xFFFF);
    TrioOutfits_RecordPhoto(SPECIES_PENNY_PUMPKIN_DACHSBUN);
    EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), 0xFFFF);
    BufferTrioOutfitPhotoCount();
    EXPECT_EQ(gStringVar1[0], CHAR_0 + 1);
    EXPECT_EQ(gStringVar1[1], CHAR_0 + 5);
    gSpecialVar_0x8004 = 28;
    EXPECT_EQ(HasTrioOutfitPhoto(), FALSE);
}

TEST("Seasonal photos preserve all old bits and share dressed Penny stages")
{
    static const u16 forms[] = {SPECIES_RIKO_LEAVES, SPECIES_BIJUU_SWEATER, SPECIES_PENNY_SWEATER, SPECIES_RIKO_TURKEY, SPECIES_BIJUU_CHEF, SPECIES_PENNY_YAM, SPECIES_RIKO_SANTA, SPECIES_BIJUU_PRESENT, SPECIES_PENNY_REINDEER, SPECIES_RIKO_PARTY, SPECIES_BIJUU_GALA, SPECIES_PENNY_STARS};
    VarSet(VAR_TRIO_OUTFIT_PHOTOS, 0xFFFF);
    VarSet(VAR_TRIO_SEASONAL_PHOTOS, 0);
    for (u32 i = 0; i < ARRAY_COUNT(forms); i++)
    {
        ZeroPlayerPartyMons();
        CreateMon(&gPlayerParty[0], forms[i], 30, 0, OTID_STRUCT_PLAYER_ID);
        TrioOutfits_RecordPartyPhotos();
        EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), 0xFFFF);
        EXPECT_EQ(VarGet(VAR_TRIO_SEASONAL_PHOTOS), (1u << (i + 1)) - 1);
        gSpecialVar_0x8004 = i % 3;
        EXPECT_EQ(GetTrioOutfitReaction(), 17 + i);
        gSpecialVar_0x8004 = 16 + i;
        EXPECT(HasTrioOutfitPhoto());
    }
    TrioOutfits_RecordPhoto(SPECIES_PENNY_SWEATER_DACHSBUN);
    TrioOutfits_RecordPhoto(SPECIES_PENNY_YAM_DACHSBUN);
    TrioOutfits_RecordPhoto(SPECIES_PENNY_REINDEER_DACHSBUN);
    TrioOutfits_RecordPhoto(SPECIES_PENNY_STARS_DACHSBUN);
    EXPECT_EQ(VarGet(VAR_TRIO_SEASONAL_PHOTOS), 0x0FFF);
    BufferTrioOutfitPhotoCount();
    EXPECT_EQ(gStringVar1[0], CHAR_0 + 2);
    EXPECT_EQ(gStringVar1[1], CHAR_0 + 7);
    gSpecialVar_0x8004 = 28;
    EXPECT_EQ(HasTrioOutfitPhoto(), FALSE);
}

TEST("Seasonal wardrobe preserves earned keys without duplicating or changing outfits")
{
    static const u16 items[] = {ITEM_RIKOS_LEAF_BUNDLE, ITEM_COCOAS_KNIT_SET, ITEM_PENNYS_CARDIGAN, ITEM_RIKOS_FEATHER_FAN, ITEM_COCOAS_CHEF_HAT, ITEM_PENNYS_YAM_WRAP, ITEM_POM_SANTA_HAT, ITEM_COCOA_GIFT_BOX, ITEM_PENNYS_ANTLERS, ITEM_POM_PARTY_HAT, ITEM_COCOA_SILVER_BOW, ITEM_PENNYS_STAR_DRESS};
    static const u16 claims[] = {VAR_TRIO_FALL_GIFTS, VAR_TRIO_THANKSGIVING_GIFTS, VAR_TRIO_CHRISTMAS_GIFTS, VAR_TRIO_NEW_YEAR_GIFTS};
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_PENNY_STARS_DACHSBUN, 30, 0, OTID_STRUCT_PLAYER_ID);
    VarSet(VAR_TRIO_OUTFIT_PHOTOS, 0xFFFF);
    VarSet(VAR_TRIO_SEASONAL_PHOTOS, 0x0FFF);
    for (u32 i = 0; i < ARRAY_COUNT(items); i++)
    {
        ClearBag();
        VarSet(VAR_TRIO_SEASONAL_WARDROBE, 0);
        VarSet(claims[i / 3], 0);
        EXPECT(AddBagItem(items[i], 1));
        gSpecialVar_0x8004 = i;
        gSpecialVar_0x8005 = 0;
        EXPECT_EQ(ExchangeTrioSeasonalCostume(), 0); // Unclaimed imported copies stay in Bag.
        EXPECT(CheckBagHasItem(items[i], 1));
        VarSet(claims[i / 3], i % 3 + 1);
        EXPECT_EQ(ExchangeTrioSeasonalCostume(), 1);
        EXPECT(!CheckBagHasItem(items[i], 1));
        EXPECT_EQ(VarGet(VAR_TRIO_SEASONAL_WARDROBE), 1u << i);
        EXPECT_EQ(ExchangeTrioSeasonalCostume(), 0);
        EXPECT_EQ(VarGet(claims[i / 3]), i % 3 + 1); // Pending later gifts still resume correctly.
        gSpecialVar_0x8005 = 1;
        EXPECT_EQ(ExchangeTrioSeasonalCostume(), 1);
        EXPECT_EQ(VarGet(VAR_TRIO_SEASONAL_WARDROBE), 0);
        EXPECT(CheckBagHasItem(items[i], 1));
        EXPECT(!CheckBagHasItem(items[i], 2));
        EXPECT_EQ(ExchangeTrioSeasonalCostume(), 0);
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_PENNY_STARS_DACHSBUN);
        EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), 0xFFFF);
        EXPECT_EQ(VarGet(VAR_TRIO_SEASONAL_PHOTOS), 0x0FFF);
        VarSet(claims[i / 3], 0);
    }
    ClearBag();
    ZeroPlayerPartyMons();
}

TEST("Full Key Items pocket leaves seasonal wardrobe ownership saved until retrieval succeeds")
{
    ClearBag();
    VarSet(VAR_TRIO_SEASONAL_WARDROBE, 0x0FFF);
    u32 count = 0;
    for (u32 item = 1; item < ITEMS_COUNT && count < BAG_KEYITEMS_COUNT; item++)
    {
        if (GetItemPocket(item) == POCKET_KEY_ITEMS && item < ITEM_RIKOS_LEAF_BUNDLE)
        {
            EXPECT(AddBagItem(item, 1));
            count++;
        }
    }
    EXPECT_EQ(count, BAG_KEYITEMS_COUNT);
    gSpecialVar_0x8004 = 0;
    gSpecialVar_0x8005 = 1;
    EXPECT_EQ(ExchangeTrioSeasonalCostume(), 2);
    EXPECT_EQ(VarGet(VAR_TRIO_SEASONAL_WARDROBE), 0x0FFF);
    EXPECT(!CheckBagHasItem(ITEM_RIKOS_LEAF_BUNDLE, 1));
    ClearBag();
    EXPECT_EQ(ExchangeTrioSeasonalCostume(), 1);
    EXPECT(CheckBagHasItem(ITEM_RIKOS_LEAF_BUNDLE, 1));
    EXPECT_EQ(VarGet(VAR_TRIO_SEASONAL_WARDROBE), 0x0FFE);
    ClearBag();
    VarSet(VAR_TRIO_SEASONAL_WARDROBE, 0);
}

TEST("Invalid seasonal wardrobe inputs preserve saved storage and Bag inventory")
{
    ClearBag();
    EXPECT(AddBagItem(ITEM_RIKOS_LEAF_BUNDLE, 1));
    VarSet(VAR_TRIO_SEASONAL_WARDROBE, 0x0555);
    static const u16 inputs[][2] = {{12,0},{0xFFFF,1},{0,2},{0,0xFFFF}};
    for (u32 i = 0; i < ARRAY_COUNT(inputs); i++)
    {
        gSpecialVar_0x8004 = inputs[i][0];
        gSpecialVar_0x8005 = inputs[i][1];
        EXPECT_EQ(ExchangeTrioSeasonalCostume(), 0);
        EXPECT_EQ(VarGet(VAR_TRIO_SEASONAL_WARDROBE), 0x0555);
        EXPECT(CheckBagHasItem(ITEM_RIKOS_LEAF_BUNDLE, 1));
        EXPECT(!CheckBagHasItem(ITEM_RIKOS_LEAF_BUNDLE, 2));
    }
    ClearBag();
    VarSet(VAR_TRIO_SEASONAL_WARDROBE, 0);
}
