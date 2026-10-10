#include "global.h"
#include "battle_setup.h"
#include "battle.h"
#include "constants/map_groups.h"
#include "constants/songs.h"
#include "event_data.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/vars.h"
#include "constants/flags.h"

TEST("Riko cavern creates four distinct healthy female bosses without changing saved progression")
{
    static const u16 species[] = {SPECIES_RIKO_ASPECT_MIND, SPECIES_RIKO_ASPECT_BODY, SPECIES_RIKO_ASPECT_SOUL, SPECIES_RIKO_SPIRIT};
    static const u16 moves[] = {MOVE_PSYCHIC, MOVE_BODY_SLAM, MOVE_DRAINING_KISS, MOVE_FLAMETHROWER};
    u32 phase;
    u32 hp = 0;
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_RIKO, 35, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_FIDOUGH, 45, 0, OTID_STRUCT_PLAYER_ID);
    VarSet(VAR_RIKO_CAVERN_STATE, 2);
    VarSet(VAR_TRIO_RIFT_RIKO_STATE, 5);
    FlagClear(FLAG_DEFEATED_SUICUNE);
    for (phase = 0; phase < ARRAY_COUNT(species); phase++)
    {
        SetMonData(&gPlayerParty[0], MON_DATA_HP, &hp);
        gSpecialVar_0x8004 = phase;
        EXPECT(PrepareRikoCavernBattle());
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_SPECIES), species[phase]);
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 55);
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE1), moves[phase]);
        EXPECT_EQ(GetMonGender(&gEnemyParty[0]), MON_FEMALE);
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_HP), GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP));
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP), GetMonData(&gPlayerParty[0], MON_DATA_MAX_HP));
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_RIKO);
        EXPECT_EQ(VarGet(VAR_RIKO_CAVERN_STATE), 2);
        EXPECT_EQ(VarGet(VAR_TRIO_RIFT_RIKO_STATE), 5);
        EXPECT(!FlagGet(FLAG_DEFEATED_SUICUNE));
    }
}

TEST("Riko cavern rejects empty egg only and invalid phase without mutating parties")
{
    struct Pokemon enemy;
    u32 egg = TRUE;
    ZeroPlayerPartyMons();
    CreateMon(&gEnemyParty[0], SPECIES_CLEFAIRY, 12, 0, OTID_STRUCT_PLAYER_ID);
    enemy = gEnemyParty[0];
    gSpecialVar_0x8004 = 0;
    EXPECT(!PrepareRikoCavernBattle());
    EXPECT_EQ(memcmp(&enemy, &gEnemyParty[0], sizeof(enemy)), 0);
    CreateMon(&gPlayerParty[0], SPECIES_RIKO, 100, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, &egg);
    EXPECT(!PrepareRikoCavernBattle());
    EXPECT_EQ(memcmp(&enemy, &gEnemyParty[0], sizeof(enemy)), 0);
    egg = FALSE;
    SetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, &egg);
    gSpecialVar_0x8004 = 4;
    EXPECT(!PrepareRikoCavernBattle());
    EXPECT_EQ(memcmp(&enemy, &gEnemyParty[0], sizeof(enemy)), 0);
}

TEST("Riko cavern ignores high level Eggs caps levels and provides early starter moves")
{
    static const u16 early[] = {MOVE_CONFUSION, MOVE_TACKLE, MOVE_FAIRY_WIND, MOVE_EMBER};
    u32 phase;
    u32 egg = TRUE;
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_RIKO, 5, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_FIDOUGH, 100, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[1], MON_DATA_IS_EGG, &egg);
    for (phase = 0; phase < 4; phase++)
    {
        gSpecialVar_0x8004 = phase;
        EXPECT(PrepareRikoCavernBattle());
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 15);
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE1), early[phase]);
    }
    CreateMon(&gPlayerParty[0], SPECIES_RIKO, 96, 0, OTID_STRUCT_PLAYER_ID);
    for (phase = 0; phase < 4; phase++)
    {
        gSpecialVar_0x8004 = phase;
        EXPECT(PrepareRikoCavernBattle());
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 100);
    }
}

TEST("Riko cavern aspects register all assets and preserve save ABI")
{
    u32 species;
    for (species = SPECIES_RIKO_ASPECT_MIND; species <= SPECIES_RIKO_ASPECT_SOUL; species++)
    {
        const struct SpeciesInfo *info = &gSpeciesInfo[species];
        EXPECT(info->frontPic && info->backPic && info->palette && info->iconSprite);
        EXPECT(info->overworldData.images != NULL);
        EXPECT_EQ(info->genderRatio, MON_FEMALE);
        EXPECT(!info->evolutions);
        EXPECT(!info->formChangeTable);
    }
    EXPECT_EQ(sizeof(struct SaveBlock1), 15444);
    EXPECT_EQ(sizeof(struct SaveBlock2), 2864);
    EXPECT_EQ(sizeof(struct SaveBlock3), 100);
}

TEST("Riko cavern music is scoped to exact map species and wild battle")
{
    static const u16 species[] = {SPECIES_RIKO_ASPECT_MIND, SPECIES_RIKO_ASPECT_BODY, SPECIES_RIKO_ASPECT_SOUL, SPECIES_RIKO_SPIRIT};
    static const u16 songs[] = {MUS_HG_VS_LUGIA, MUS_HG_VS_ENTEI, MUS_HG_VS_HO_OH, MUS_HG_VS_CHAMPION};
    u32 oldFlags = gBattleTypeFlags;
    u8 oldGroup = gSaveBlock1Ptr->location.mapGroup;
    u8 oldNum = gSaveBlock1Ptr->location.mapNum;
    u32 i;
    gBattleTypeFlags = 0;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_RIKO_SPIRIT_CAVERN);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_RIKO_SPIRIT_CAVERN);
    for (i = 0; i < ARRAY_COUNT(species); i++)
    {
        CreateMon(&gEnemyParty[0], species[i], 50, 0, OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetBattleBGM(), songs[i]);
    }
    CreateMon(&gEnemyParty[0], SPECIES_CLEFAIRY, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetBattleBGM(), MUS_HG_VS_WILD);
    gBattleTypeFlags = BATTLE_TYPE_TRAINER;
    EXPECT_NE(GetBattleBGM(), MUS_HG_VS_CHAMPION);
    gBattleTypeFlags = 0;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_NEW_BARK_TOWN);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_NEW_BARK_TOWN);
    EXPECT_EQ(GetBattleBGM(), MUS_HG_VS_WILD);
    gSaveBlock1Ptr->location.mapGroup = oldGroup;
    gSaveBlock1Ptr->location.mapNum = oldNum;
    gBattleTypeFlags = oldFlags;
}
