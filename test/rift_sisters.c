#include "global.h"
#include "pokemon.h"
#include "battle_setup.h"
#include "item.h"
#include "item_use.h"
#include "event_data.h"
#include "trio_camp.h"
#include "overworld.h"
#include "test/test.h"
#include "constants/species.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/flags.h"
#include "constants/game_stat.h"

TEST("Sister charms route ordinary and prior forms into midgame forms and back")
{
    struct Pokemon mon;
    static const struct {u16 from, item, to;} cases[] = {
        {SPECIES_BIJUU, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER},
        {SPECIES_BIJUU_PSYCHIC, ITEM_BIJUUS_FIRE, SPECIES_BIJUU_EMBER},
        {SPECIES_BIJUU_EMBER, ITEM_BIJUUS_FIRE, SPECIES_BIJUU},
        {SPECIES_FIDOUGH, ITEM_PENNYS_BRAVERY, SPECIES_PENNY_BRAVE},
        {SPECIES_DACHSBUN, ITEM_PENNYS_BRAVERY, SPECIES_PENNY_BRAVE},
        {SPECIES_PENNY_GUARDIAN, ITEM_PENNYS_BRAVERY, SPECIES_PENNY_BRAVE},
        {SPECIES_PENNY_BRAVE, ITEM_PENNYS_BRAVERY, SPECIES_FIDOUGH},
        {SPECIES_BIJUU_SPIRIT, ITEM_BIJUUS_FIRE, SPECIES_NONE},
        {SPECIES_PENNY_SPIRIT, ITEM_PENNYS_BRAVERY, SPECIES_NONE},
        {SPECIES_RIKO, ITEM_BIJUUS_FIRE, SPECIES_NONE},
        {SPECIES_BIJUU, ITEM_PENNYS_BRAVERY, SPECIES_NONE},
    };
    u32 i;
    for (i = 0; i < ARRAY_COUNT(cases); i++)
    {
        CreateMon(&mon, cases[i].from, 35, 0, OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, cases[i].item, NULL, NULL, CHECK_EVO), cases[i].to);
        EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), cases[i].from);
        EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 35);
    }
}

TEST("New midgame sister guardians are healthy +10 level females and keep the party intact")
{
    u32 i, hp = 0;
    static const u16 species[] = {SPECIES_BIJUU_EMBER, SPECIES_PENNY_BRAVE};
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_RIKO_ECHO, 80, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_HP, &hp);
    for (i = 0; i < ARRAY_COUNT(species); i++)
    {
        gSpecialVar_0x8004 = species[i];
        EXPECT(PrepareTrioSpiritTrial());
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_SPECIES), species[i]);
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 90);
        EXPECT(GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP) > 0);
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_HP), GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP));
        EXPECT_EQ(GetMonGender(&gEnemyParty[0]), MON_FEMALE);
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_RIKO_ECHO);
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 80);
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP), GetMonData(&gPlayerParty[0], MON_DATA_MAX_HP));
    }
    ZeroPlayerPartyMons();
    EXPECT(!PrepareTrioSpiritTrial());
}

TEST("Sister charms are reusable key items and midgame species have complete art, not Mega tables")
{
    static const u16 species[] = {SPECIES_BIJUU_EMBER, SPECIES_PENNY_BRAVE};
    static const u16 items[] = {ITEM_BIJUUS_FIRE, ITEM_PENNYS_BRAVERY};
    static const u16 moves[] = {MOVE_EMBER, MOVE_HELPING_HAND};
    u32 i;
    ClearBag();
    for (i = 0; i < ARRAY_COUNT(items); i++)
    {
        const struct SpeciesInfo *info = &gSpeciesInfo[species[i]];
        EXPECT_EQ(GetItemPocket(items[i]), POCKET_KEY_ITEMS);
        EXPECT(GetItemImportance(items[i]));
        EXPECT_EQ(GetItemFieldFunc(items[i]), ItemUseOutOfBattle_EvolutionStone);
        EXPECT(AddBagItem(items[i], 1));
        EXPECT_EQ(CountTotalItemQuantityInBag(items[i]), 1);
        EXPECT(gItemsInfo[items[i]].iconPic != NULL && gItemsInfo[items[i]].iconPalette != NULL);
        EXPECT(info->frontPic != NULL && info->backPic != NULL && info->iconSprite != NULL);
        EXPECT(info->palette != NULL && info->shinyPalette != NULL && info->overworldData.images != NULL);
        EXPECT(info->formChangeTable == NULL && !info->isMegaEvolution);
        EXPECT_EQ(info->levelUpLearnset[0].move, moves[i]);
        EXPECT_EQ(info->levelUpLearnset[0].level, 0);
    }
    FlagClear(FLAG_TRIO_CAMP_STATS_READY);
    TrioCamp_EnsureStatsInitialized();
    TrioCamp_RecordEvolution(SPECIES_BIJUU, SPECIES_BIJUU_EMBER, ITEM_BIJUUS_FIRE);
    TrioCamp_RecordEvolution(SPECIES_BIJUU_EMBER, SPECIES_BIJUU, ITEM_BIJUUS_FIRE);
    TrioCamp_RecordEvolution(SPECIES_FIDOUGH, SPECIES_PENNY_BRAVE, ITEM_PENNYS_BRAVERY);
    TrioCamp_RecordEvolution(SPECIES_PENNY_BRAVE, SPECIES_FIDOUGH, ITEM_PENNYS_BRAVERY);
    EXPECT_EQ(GetGameStat(GAME_STAT_TRIO_FORM_SWAPS), 4);
}

TEST("All three Rift guardians scale from strongest non-egg party member and cap at 100")
{
    static const u16 species[] = {SPECIES_RIKO_ECHO, SPECIES_BIJUU_EMBER, SPECIES_PENNY_BRAVE};
    static const u8 levels[] = {1, 35, 95, 100};
    u32 i, j;
    bool32 isEgg = TRUE;
    for (i = 0; i < ARRAY_COUNT(species); i++)
    {
        for (j = 0; j < ARRAY_COUNT(levels); j++)
        {
            ZeroPlayerPartyMons();
            CreateMon(&gPlayerParty[0], SPECIES_RIKO, levels[j], 0, OTID_STRUCT_PLAYER_ID);
            CreateMon(&gPlayerParty[1], SPECIES_BIJUU, 1, 0, OTID_STRUCT_PLAYER_ID);
            gSpecialVar_0x8004 = species[i];
            EXPECT(PrepareTrioSpiritTrial());
            EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), levels[j] > 90 ? 100 : levels[j] + 10);
        }
        ZeroPlayerPartyMons();
        CreateMon(&gPlayerParty[0], SPECIES_RIKO, 20, 0, OTID_STRUCT_PLAYER_ID);
        CreateMon(&gPlayerParty[1], SPECIES_BIJUU, 100, 0, OTID_STRUCT_PLAYER_ID);
        SetMonData(&gPlayerParty[1], MON_DATA_IS_EGG, &isEgg);
        gSpecialVar_0x8004 = species[i];
        EXPECT(PrepareTrioSpiritTrial());
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 30);
    }
}
