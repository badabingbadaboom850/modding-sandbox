#include "global.h"
#include "event_data.h"
#include "pokemon.h"
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
    default: return 0;
    }
}

void TrioOutfits_RecordPhoto(u16 species)
{
    u16 index = OutfitIndex(species);
    if (index) VarSet(VAR_TRIO_OUTFIT_PHOTOS, VarGet(VAR_TRIO_OUTFIT_PHOTOS) | (1u << (index - 1)));
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
        u16 family = (index <= 3 || index == 11) ? 0 : (index <= 6 || index == 10 || index == 12) ? 1 : 2;
        if (gSpecialVar_0x8004 == 3 || gSpecialVar_0x8004 == family) return index;
    }
    return 0;
}

u16 HasTrioOutfitPhoto(void)
{
    if (gSpecialVar_0x8004 >= 13) return FALSE;
    return (VarGet(VAR_TRIO_OUTFIT_PHOTOS) & (1u << gSpecialVar_0x8004)) != 0;
}

void BufferTrioOutfitPhotoCount(void)
{
    u16 mask = VarGet(VAR_TRIO_OUTFIT_PHOTOS) & 0x1DFF;
    u16 count = 0;
    for (u32 i = 0; i < 13; i++) count += (mask >> i) & 1;
    ConvertIntToDecimalStringN(gStringVar1, count, STR_CONV_MODE_LEFT_ALIGN, 2);
}
