#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "item.h"
#include "constants/items.h"
#include "string_util.h"
#include "trio_outfits.h"
#include "constants/species.h"
#include "constants/vars.h"

// One portrait per outfit; both ordinary and Dachsbun Penny use the same page.
static u16 OutfitIndex(u16 species)
{
    switch (species)
    {
    case SPECIES_RIKO_BALLOON: return 1;
    case SPECIES_RIKO_PRINCESS: return 2;
    case SPECIES_RIKO_RAINCOAT: return 3;
    case SPECIES_BIJUU_BOX: return 4;
    case SPECIES_BIJUU_BREAD: return 5;
    case SPECIES_BIJUU_DETECTIVE: return 6;
    case SPECIES_PENNY_HOTDOG:
    case SPECIES_PENNY_HOTDOG_DACHSBUN: return 7;
    case SPECIES_PENNY_BLANKET:
    case SPECIES_PENNY_BLANKET_DACHSBUN: return 8;
    case SPECIES_PENNY_LIFEGUARD:
    case SPECIES_PENNY_LIFEGUARD_DACHSBUN: return 9;
    case SPECIES_BIJUU_POISON: return 10;
    case SPECIES_RIKO_BUTTERFLY: return 11;
    case SPECIES_BIJUU_ASTRONAUT: return 12;
    case SPECIES_PENNY_BALLERINA:
    case SPECIES_PENNY_BALLERINA_DACHSBUN: return 13;
    case SPECIES_RIKO_WITCH: return 14;
    case SPECIES_BIJUU_VAMPIRE: return 15;
    case SPECIES_PENNY_PUMPKIN:
    case SPECIES_PENNY_PUMPKIN_DACHSBUN: return 16;
    case SPECIES_RIKO_LEAVES: return 17;
    case SPECIES_BIJUU_SWEATER: return 18;
    case SPECIES_PENNY_SWEATER:
    case SPECIES_PENNY_SWEATER_DACHSBUN: return 19;
    case SPECIES_RIKO_TURKEY: return 20;
    case SPECIES_BIJUU_CHEF: return 21;
    case SPECIES_PENNY_YAM:
    case SPECIES_PENNY_YAM_DACHSBUN: return 22;
    case SPECIES_RIKO_SANTA: return 23;
    case SPECIES_BIJUU_PRESENT: return 24;
    case SPECIES_PENNY_REINDEER:
    case SPECIES_PENNY_REINDEER_DACHSBUN: return 25;
    case SPECIES_RIKO_PARTY: return 26;
    case SPECIES_BIJUU_GALA: return 27;
    case SPECIES_PENNY_STARS:
    case SPECIES_PENNY_STARS_DACHSBUN: return 28;
    default: return 0;
    }
}

void TrioOutfits_RecordPhoto(u16 species)
{
    u16 index = OutfitIndex(species);
    if (index > 16)
        VarSet(VAR_TRIO_SEASONAL_PHOTOS, VarGet(VAR_TRIO_SEASONAL_PHOTOS) | (1u << (index - 17)));
    else if (index) VarSet(VAR_TRIO_OUTFIT_PHOTOS, VarGet(VAR_TRIO_OUTFIT_PHOTOS) | (1u << (index - 1)));
}

void TrioOutfits_RecordPartyPhotos(void)
{
    for (u32 i = 0; i < PARTY_SIZE; i++)
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
            TrioOutfits_RecordPhoto(GetMonData(&gPlayerParty[i], MON_DATA_SPECIES));
}

// Input family:0 Riko,1 Bijuu,2 Penny,3 any. Party order picks the first match.
u16 GetTrioOutfitReaction(void)
{
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG)) continue;
        u16 index = OutfitIndex(GetMonData(&gPlayerParty[i], MON_DATA_SPECIES));
        if (!index) continue;
        u16 family = index > 16 ? (index - 17) % 3 : (index <= 3 || index == 11 || index == 14) ? 0 : (index <= 6 || index == 10 || index == 12 || index == 15) ? 1 : 2;
        if (gSpecialVar_0x8004 == 3 || gSpecialVar_0x8004 == family) return index;
    }
    return 0;
}

u16 HasTrioOutfitPhoto(void)
{
    if (gSpecialVar_0x8004 >= 28) return FALSE;
    if (gSpecialVar_0x8004 >= 16)
        return (VarGet(VAR_TRIO_SEASONAL_PHOTOS) & (1u << (gSpecialVar_0x8004 - 16))) != 0;
    return (VarGet(VAR_TRIO_OUTFIT_PHOTOS) & (1u << gSpecialVar_0x8004)) != 0;
}

void BufferTrioOutfitPhotoCount(void)
{
    u16 mask = VarGet(VAR_TRIO_OUTFIT_PHOTOS) & 0xFDFF;
    u16 count = 0;
    for (u32 i = 0; i < 16; i++) count += (mask >> i) & 1;
    mask = VarGet(VAR_TRIO_SEASONAL_PHOTOS) & 0x0FFF;
    for (u32 i = 0; i < 12; i++) count += (mask >> i) & 1;
    ConvertIntToDecimalStringN(gStringVar1, count, STR_CONV_MODE_LEFT_ALIGN, 2);
}

// Explicit wardrobe transfer, never consumption. Saved ownership stays intact.
// Input8004: costume0-11. Input8005:0store,1take. Result:0unavailable,1success,2full.
u16 ExchangeTrioSeasonalCostume(void)
{
    static const u16 items[] = {ITEM_RIKOS_LEAF_BUNDLE, ITEM_COCOAS_KNIT_SET, ITEM_PENNYS_CARDIGAN, ITEM_RIKOS_FEATHER_FAN, ITEM_COCOAS_CHEF_HAT, ITEM_PENNYS_YAM_WRAP, ITEM_POM_SANTA_HAT, ITEM_COCOA_GIFT_BOX, ITEM_PENNYS_ANTLERS, ITEM_POM_PARTY_HAT, ITEM_COCOA_SILVER_BOW, ITEM_PENNYS_STAR_DRESS};
    static const u16 claims[] = {VAR_TRIO_FALL_GIFTS, VAR_TRIO_THANKSGIVING_GIFTS, VAR_TRIO_CHRISTMAS_GIFTS, VAR_TRIO_NEW_YEAR_GIFTS};
    u16 index = gSpecialVar_0x8004;
    u16 mode = gSpecialVar_0x8005;
    if (index >= ARRAY_COUNT(items) || mode > 1)
        return 0;
    u16 bit = 1u << index;
    u16 stored = VarGet(VAR_TRIO_SEASONAL_WARDROBE);
    if (mode == 0)
    {
        // Only already claimed gifts may leave the Bag; pending claims cannot duplicate.
        if ((stored & bit) || VarGet(claims[index / 3]) <= index % 3
            || !CheckBagHasItem(items[index], 1) || !RemoveBagItem(items[index], 1))
            return 0;
        VarSet(VAR_TRIO_SEASONAL_WARDROBE, stored | bit);
    }
    else
    {
        if (!(stored & bit))
            return 0;
        if (!AddBagItem(items[index], 1))
            return 2;
        // Clear saved storage only after the Bag accepted the real protected key.
        VarSet(VAR_TRIO_SEASONAL_WARDROBE, stored & ~bit);
    }
    return 1;
}
