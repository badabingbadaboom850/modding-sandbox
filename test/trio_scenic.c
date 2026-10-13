#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "string_util.h"
#include "trio_scenic.h"
#include "test/test.h"
#include "constants/species.h"
#include "constants/vars.h"
#include "constants/weather.h"

TEST("Scenic photos preserve exact costume stages and independent historical photos")
{
    ZeroPlayerPartyMons();
    VarSet(VAR_TRIO_SCENIC_PHOTOS, 0);
    VarSet(VAR_TRIO_OUTFIT_PHOTOS, 0xAAAA);
    VarSet(VAR_TRIO_SEASONAL_PHOTOS, 0x0555);
    CreateMon(&gPlayerParty[0], SPECIES_RIKO_RAINCOAT, 30, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_PENNY_SWEATER_DACHSBUN, 30, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[2], SPECIES_BIJUU_ASTRONAUT, 30, 0, OTID_STRUCT_PLAYER_ID);
    gSpecialVar_0x8004 = 0;
    EXPECT(TakeTrioScenicPhoto());
    EXPECT(ReadTrioScenicPhoto());
    EXPECT_EQ(gSpecialVar_0x8005, SPECIES_RIKO_RAINCOAT);
    EXPECT_EQ(gSpecialVar_0x8006, SPECIES_BIJUU_ASTRONAUT);
    EXPECT_EQ(gSpecialVar_0x8007, SPECIES_PENNY_SWEATER_DACHSBUN);
    CreateMon(&gPlayerParty[0], SPECIES_RIKO_FLOWER, 30, 0, OTID_STRUCT_PLAYER_ID);
    gSpecialVar_0x8004 = 1;
    EXPECT(TakeTrioScenicPhoto());
    EXPECT_EQ(VarGet(VAR_TRIO_SCENIC_PHOTOS), 3);
    ZeroPlayerPartyMons();
    gSpecialVar_0x8004 = 0;
    EXPECT(ReadTrioScenicPhoto());
    EXPECT_EQ(gSpecialVar_0x8005, SPECIES_RIKO_RAINCOAT);
    gSpecialVar_0x8004 = 1;
    EXPECT(ReadTrioScenicPhoto());
    EXPECT_EQ(gSpecialVar_0x8005, SPECIES_RIKO_FLOWER);
    EXPECT_EQ(VarGet(VAR_TRIO_OUTFIT_PHOTOS), 0xAAAA);
    EXPECT_EQ(VarGet(VAR_TRIO_SEASONAL_PHOTOS), 0x0555);
}

TEST("Scenic missing eggs bosses and invalid saved identities never erase a keepsake")
{
    ZeroPlayerPartyMons();
    VarSet(VAR_TRIO_SCENIC_PHOTOS, 7);
    VarSet(VAR_TRIO_SCENIC_ICE_RIKO, SPECIES_RIKO);
    VarSet(VAR_TRIO_SCENIC_ICE_BIJUU, SPECIES_BIJUU);
    VarSet(VAR_TRIO_SCENIC_ICE_PENNY, SPECIES_FIDOUGH);
    gSpecialVar_0x8004 = 2;
    EXPECT_EQ(TakeTrioScenicPhoto(), FALSE);
    EXPECT(ReadTrioScenicPhoto());
    CreateMon(&gPlayerParty[0], SPECIES_RIKO_SPIRIT, 30, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_BIJUU, 30, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[2], SPECIES_FIDOUGH, 30, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(TakeTrioScenicPhoto(), FALSE);
    CreateMon(&gPlayerParty[0], SPECIES_RIKO, 30, 0, OTID_STRUCT_PLAYER_ID);
    bool32 egg = TRUE;
    SetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, &egg);
    EXPECT_EQ(TakeTrioScenicPhoto(), FALSE);
    EXPECT_EQ(VarGet(VAR_TRIO_SCENIC_ICE_RIKO), SPECIES_RIKO);
    EXPECT_EQ(VarGet(VAR_TRIO_SCENIC_PHOTOS), 7);
    gSpecialVar_0x8004 = 3;
    EXPECT_EQ(TakeTrioScenicPhoto(), FALSE);
    EXPECT_EQ(ReadTrioScenicPhoto(), FALSE);
    gSpecialVar_0x8004 = 0xFFFF;
    EXPECT_EQ(TakeTrioScenicPhoto(), FALSE);
    EXPECT_EQ(ReadTrioScenicPhoto(), FALSE);
    gSpecialVar_0x8004 = 2;
    VarSet(VAR_TRIO_SCENIC_ICE_RIKO, 0xFFFF);
    EXPECT_EQ(ReadTrioScenicPhoto(), FALSE);
    EXPECT_EQ(gSpecialVar_0x8005, SPECIES_NONE);
    VarSet(VAR_TRIO_SCENIC_ICE_RIKO, SPECIES_BIJUU);
    EXPECT_EQ(ReadTrioScenicPhoto(), FALSE);
}

TEST("Weather reactions cover personal forms and only recognized current weather")
{
    static const u16 girls[] = {SPECIES_RIKO, SPECIES_RIKO_LEAVES, SPECIES_RIKO_FLOWER, SPECIES_BIJUU, SPECIES_BIJUU_GALA, SPECIES_BIJUU_ICE, SPECIES_FIDOUGH, SPECIES_DACHSBUN, SPECIES_PENNY_STARS_DACHSBUN, SPECIES_PENNY_GUARDIAN};
    static const u8 weather[] = {WEATHER_RAIN, WEATHER_RAIN_THUNDERSTORM, WEATHER_DOWNPOUR, WEATHER_SNOW, WEATHER_SUNNY, WEATHER_SUNNY_CLOUDS, WEATHER_DROUGHT, WEATHER_FOG_HORIZONTAL, WEATHER_FOG_DIAGONAL, WEATHER_SANDSTORM, WEATHER_VOLCANIC_ASH};
    for (u32 i = 0; i < ARRAY_COUNT(girls); i++)
    {
        EXPECT_EQ(TrioWeatherReaction(girls[i], WEATHER_NONE), NULL);
        EXPECT_EQ(TrioWeatherReaction(girls[i], WEATHER_ABNORMAL), NULL);
        for (u32 j = 0; j < ARRAY_COUNT(weather); j++) EXPECT(TrioWeatherReaction(girls[i], weather[j]) != NULL);
    }
    EXPECT(TrioWeatherReaction(SPECIES_RIKO_RAINCOAT, WEATHER_RAIN) != TrioWeatherReaction(SPECIES_RIKO, WEATHER_RAIN));
    for (u32 i = 0; i < WEATHER_COUNT; i++)
    {
        EXPECT_EQ(TrioWeatherReaction(SPECIES_PIKACHU, i), NULL);
        EXPECT_EQ(TrioWeatherReaction(SPECIES_RIKO_SPIRIT, i), NULL);
        EXPECT_EQ(TrioWeatherReaction(SPECIES_NONE, i), NULL);
    }
}
