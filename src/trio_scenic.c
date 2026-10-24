#include "global.h"
#include "battle_util.h"
#include "event_data.h"
#include "pokemon.h"
#include "trio_scenic.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/vars.h"
#include "constants/weather.h"

// Family order is Riko, Bijuu, Penny. Reuse the audited personal-form classifier.
static const u16 sFamilies[] = {ITEM_RIKOS_SPARK, ITEM_BIJUUS_LIGHT, ITEM_PENNYS_SHIELD};
static const u16 sPhotoVars[3][3] = {
    {VAR_TRIO_SCENIC_LIGHTHOUSE_RIKO, VAR_TRIO_SCENIC_LIGHTHOUSE_BIJUU, VAR_TRIO_SCENIC_LIGHTHOUSE_PENNY},
    {VAR_TRIO_SCENIC_LAKE_RIKO, VAR_TRIO_SCENIC_LAKE_BIJUU, VAR_TRIO_SCENIC_LAKE_PENNY},
    {VAR_TRIO_SCENIC_ICE_RIKO, VAR_TRIO_SCENIC_ICE_BIJUU, VAR_TRIO_SCENIC_ICE_PENNY},
};

// Input8004: spot0-2. No writes until all three non-egg girls are found.
u16 TakeTrioScenicPhoto(void)
{
    u16 spot = gSpecialVar_0x8004;
    u16 species[3] = {0};
    if (spot >= ARRAY_COUNT(sPhotoVars)) return FALSE;
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        if (GetMonData(mon, MON_DATA_IS_EGG)) continue;
        u16 current = GetMonData(mon, MON_DATA_SPECIES);
        u16 family = GetTrioSpiritKeepsakeForSpecies(current);
        for (u32 j = 0; j < ARRAY_COUNT(sFamilies); j++)
            if (!species[j] && family == sFamilies[j]) species[j] = current;
    }
    if (!species[0] || !species[1] || !species[2]) return FALSE;
    for (u32 j = 0; j < ARRAY_COUNT(sFamilies); j++) VarSet(sPhotoVars[spot][j], species[j]);
    VarSet(VAR_TRIO_SCENIC_PHOTOS, VarGet(VAR_TRIO_SCENIC_PHOTOS) | (1u << spot));
    return TRUE;
}

// Read-only: validate saved identity before using it as a sprite/table index.
// Input8004: spot. Outputs8005-7: exact forms captured (Riko/Bijuu/Penny).
u16 ReadTrioScenicPhoto(void)
{
    u16 spot = gSpecialVar_0x8004;
    gSpecialVar_0x8005 = gSpecialVar_0x8006 = gSpecialVar_0x8007 = SPECIES_NONE;
    if (spot >= ARRAY_COUNT(sPhotoVars) || !(VarGet(VAR_TRIO_SCENIC_PHOTOS) & (1u << spot))) return FALSE;
    u16 species[3];
    for (u32 j = 0; j < ARRAY_COUNT(sFamilies); j++)
    {
        species[j] = VarGet(sPhotoVars[spot][j]);
        if (species[j] >= NUM_SPECIES || GetTrioSpiritKeepsakeForSpecies(species[j]) != sFamilies[j]) return FALSE;
    }
    gSpecialVar_0x8005 = species[0];
    gSpecialVar_0x8006 = species[1];
    gSpecialVar_0x8007 = species[2];
    return TRUE;
}

static const u8 sRikoRaincoat[] = _("Riko struts in a raincoat.\nEvery puddle is a runway!");
static const u8 sRikoRain[] = _("Riko barks at the rain.\nThe sky has been warned.");
static const u8 sBijuuRain[] = _("Bijuu avoids the puddles.\nWet paws? Absolutely not.");
static const u8 sPennyRain[] = _("Penny leans close to you.\nCozy is wherever you are.");
static const u8 sRikoSnow[] = _("Riko inspects the snow.\nTiny queen. White realm.");
static const u8 sBijuuSnow[] = _("Bijuu watches snowflakes.\nOne lands on her nose.");
static const u8 sPennySnow[] = _("Penny nestles beside you.\nHer sisters keep her cozy.");
static const u8 sRikoSun[] = _("Riko shows off her floof.\nThe sun is her spotlight.");
static const u8 sBijuuSun[] = _("Bijuu finds a sunny patch.\nThis spot belongs to her.");
static const u8 sPennySun[] = _("Penny soaks up the sun.\nA warm little hot dog.");
static const u8 sRikoFog[] = _("Riko barks into the fog.\nShe expects it to answer.");
static const u8 sBijuuFog[] = _("Bijuu peers into the mist.\nHer whiskers lead the way.");
static const u8 sPennyFog[] = _("Penny stays at your side.\nTogether feels safe.");
static const u8 sRikoDust[] = _("Riko shakes out her floof.\nDust cannot dim her crown.");
static const u8 sBijuuDust[] = _("Bijuu squints at the dust.\nShe requests cleaner air.");
static const u8 sPennyDust[] = _("Penny tucks close to you.\nYou shield her soft ears.");

const u8 *TrioWeatherReaction(u16 species, u8 weather)
{
    u16 family = GetTrioSpiritKeepsakeForSpecies(species);
    if (family == ITEM_NONE) return NULL;
    switch (weather)
    {
    case WEATHER_RAIN:
    case WEATHER_RAIN_THUNDERSTORM:
    case WEATHER_DOWNPOUR:
        if (species == SPECIES_RIKO_RAINCOAT) return sRikoRaincoat;
        return family == ITEM_RIKOS_SPARK ? sRikoRain : family == ITEM_BIJUUS_LIGHT ? sBijuuRain : sPennyRain;
    case WEATHER_SNOW:
        return family == ITEM_RIKOS_SPARK ? sRikoSnow : family == ITEM_BIJUUS_LIGHT ? sBijuuSnow : sPennySnow;
    case WEATHER_SUNNY:
    case WEATHER_SUNNY_CLOUDS:
    case WEATHER_DROUGHT:
        return family == ITEM_RIKOS_SPARK ? sRikoSun : family == ITEM_BIJUUS_LIGHT ? sBijuuSun : sPennySun;
    case WEATHER_FOG_HORIZONTAL:
    case WEATHER_FOG_DIAGONAL:
        return family == ITEM_RIKOS_SPARK ? sRikoFog : family == ITEM_BIJUUS_LIGHT ? sBijuuFog : sPennyFog;
    case WEATHER_SANDSTORM:
    case WEATHER_VOLCANIC_ASH:
        return family == ITEM_RIKOS_SPARK ? sRikoDust : family == ITEM_BIJUUS_LIGHT ? sBijuuDust : sPennyDust;
    default: return NULL;
    }
}
