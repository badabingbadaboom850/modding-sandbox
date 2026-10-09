#include "global.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/species.h"

TEST("Festival Pokemon have enabled battle and overworld species data")
{
    static const u16 species[] = {
        SPECIES_AIPOM, SPECIES_PACHIRISU, SPECIES_GREEDENT,
        SPECIES_RIKO, SPECIES_FIDOUGH, SPECIES_BIJUU,
        SPECIES_PENNY_GUARDIAN, SPECIES_BIJUU_PSYCHIC, SPECIES_RIKO_WING,
    };
    u32 i;
    for (i = 0; i < ARRAY_COUNT(species); i++)
    {
        const struct SpeciesInfo *info = &gSpeciesInfo[species[i]];
        EXPECT(info->baseHP > 0);
        EXPECT(info->frontPic != NULL);
        EXPECT(info->backPic != NULL);
        EXPECT(info->palette != NULL);
        EXPECT(info->levelUpLearnset != NULL);
        EXPECT(info->overworldData.images != NULL);
    }
}

TEST("Festival snack boss can create a healthy level 29 Greedent")
{
    struct Pokemon mon;
    CreateMon(&mon, SPECIES_GREEDENT, 29, 25, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_GREEDENT);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 29);
    EXPECT(GetMonData(&mon, MON_DATA_MAX_HP) > 29);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP), GetMonData(&mon, MON_DATA_MAX_HP));
}
