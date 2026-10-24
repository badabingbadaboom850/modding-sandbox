#include "global.h"
#include "pokemon.h"
#include "constants/party_menu.h"
#include "party_menu.h"
#include "item.h"
#include "item_use.h"
#include "text.h"
#include "caps.h"
#include "test/test.h"
#include "constants/items.h"
#include "constants/species.h"

TEST("Riko Puffs give five levels across different species and safely cap at 100")
{
    const u16 species[] = {SPECIES_RIKO, SPECIES_BIJUU, SPECIES_FIDOUGH, SPECIES_DRATINI, SPECIES_NINCADA, SPECIES_SHROOMISH};
    const u8 levels[] = {1, 14, 49, 95, 96, 99};
    u32 i, j;
    u8 oldCaps = gSaveBlock2Ptr->optionsLevelCaps;
    struct Pokemon mon;
    gSaveBlock2Ptr->optionsLevelCaps = EXP_CAP_NONE;
    for (i = 0; i < ARRAY_COUNT(species); i++)
        for (j = 0; j < ARRAY_COUNT(levels); j++)
        {
            CreateMon(&mon, species[i], levels[j], 0, OTID_STRUCT_PLAYER_ID);
            EXPECT(!ExecuteTableBasedItemEffect(&mon, ITEM_RIKO_PUFFS, 0, 0, 1, 1));
            EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), min(levels[j] + 5, 100));
            EXPECT_EQ(GetMonData(&mon, MON_DATA_EXP), gExperienceTables[gSpeciesInfo[species[i]].growthRate][min(levels[j] + 5, 100)]);
            EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), species[i]);
        }
    gSaveBlock2Ptr->optionsLevelCaps = oldCaps;
}

TEST("Riko Puffs preview and unusable eggs level100 empty slots or zero quantity do not alter experience")
{
    struct Pokemon mon;
    u32 exp, egg = TRUE;
    u8 oldCaps = gSaveBlock2Ptr->optionsLevelCaps;
    gSaveBlock2Ptr->optionsLevelCaps = EXP_CAP_NONE;
    CreateMon(&mon, SPECIES_RIKO, 20, 0, OTID_STRUCT_PLAYER_ID);
    exp = GetMonData(&mon, MON_DATA_EXP);
    EXPECT(!ExecuteTableBasedItemEffect(&mon, ITEM_RIKO_PUFFS, 0, 0, 0, 1));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_EXP), exp);
    EXPECT(ExecuteTableBasedItemEffect(&mon, ITEM_RIKO_PUFFS, 0, 0, 1, 0));
    SetMonData(&mon, MON_DATA_IS_EGG, &egg);
    EXPECT(ExecuteTableBasedItemEffect(&mon, ITEM_RIKO_PUFFS, 0, 0, 1, 1));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_EXP), exp);
    CreateMon(&mon, SPECIES_RIKO, 100, 0, OTID_STRUCT_PLAYER_ID);
    exp = GetMonData(&mon, MON_DATA_EXP);
    EXPECT(ExecuteTableBasedItemEffect(&mon, ITEM_RIKO_PUFFS, 0, 0, 1, 1));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_EXP), exp);
    ZeroMonData(&mon);
    EXPECT(ExecuteTableBasedItemEffect(&mon, ITEM_RIKO_PUFFS, 0, 0, 1, 1));
    gSaveBlock2Ptr->optionsLevelCaps = oldCaps;
}

TEST("Riko Puffs bulk uses gain five each without changing ordinary Rare Candy")
{
    struct Pokemon mon;
    u8 oldCaps = gSaveBlock2Ptr->optionsLevelCaps;
    gSaveBlock2Ptr->optionsLevelCaps = EXP_CAP_NONE;
    CreateMon(&mon, SPECIES_DRATINI, 25, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(!ExecuteTableBasedItemEffect(&mon, ITEM_RIKO_PUFFS, 0, 0, 1, 1));
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_DRAGONAIR);
    EXPECT(!ExecuteTableBasedItemEffect(&mon, ITEM_RIKO_PUFFS, 0, 0, 1, 3));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 45);
    EXPECT(!ExecuteTableBasedItemEffect(&mon, ITEM_RARE_CANDY, 0, 0, 1, 1));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 46);
    EXPECT(!ExecuteTableBasedItemEffect(&mon, ITEM_RIKO_PUFFS, 0, 0, 1, 999));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 100);
    gSaveBlock2Ptr->optionsLevelCaps = oldCaps;
}

static void ExpectQuantity(struct Pokemon *mon, enum Item item, u16 bagQuantity, u16 expected)
{
#if PARTY_MENU_STYLE_OPTION
    EXPECT_EQ(BwPartyMenu_TestLevelUpItemQuantity(mon, item, bagQuantity), expected);
    EXPECT_EQ(HgssPartyMenu_TestLevelUpItemQuantity(mon, item, bagQuantity), expected);
#elif !SWSH_PARTY_MENU
    EXPECT_EQ(PartyMenu_TestLevelUpItemQuantity(mon, item, bagQuantity), expected);
#endif
#if SWSH_PARTY_MENU || PARTY_MENU_STYLE_OPTION
    EXPECT_EQ(SwShPartyMenu_TestLevelUpItemQuantity(mon, item, bagQuantity), expected);
#endif
}

TEST("Riko Puffs all party styles limit bulk consumption to the number needed")
{
    struct Pokemon mon;
    u8 oldCaps = gSaveBlock2Ptr->optionsLevelCaps;
    gSaveBlock2Ptr->optionsLevelCaps = EXP_CAP_NONE;
    CreateMon(&mon, SPECIES_RIKO, 1, 0, OTID_STRUCT_PLAYER_ID);
    ExpectQuantity(&mon, ITEM_RIKO_PUFFS, 999, 20);
    ExpectQuantity(&mon, ITEM_RIKO_PUFFS, 3, 3);
    ExpectQuantity(&mon, ITEM_RARE_CANDY, 999, 99);
    CreateMon(&mon, SPECIES_RIKO, 95, 0, OTID_STRUCT_PLAYER_ID);
    ExpectQuantity(&mon, ITEM_RIKO_PUFFS, 999, 1);
    CreateMon(&mon, SPECIES_RIKO, 96, 0, OTID_STRUCT_PLAYER_ID);
    ExpectQuantity(&mon, ITEM_RIKO_PUFFS, 999, 1);
    ExpectQuantity(&mon, ITEM_RIKO_PUFFS, 0, 0);
    CreateMon(&mon, SPECIES_RIKO, 100, 0, OTID_STRUCT_PLAYER_ID);
    ExpectQuantity(&mon, ITEM_RIKO_PUFFS, 999, 0);
    gSaveBlock2Ptr->optionsLevelCaps = oldCaps;
}

TEST("Riko Puffs respect enabled candy level caps in both preview and actual use")
{
    struct Pokemon mon;
    u32 cap, exp;
    u8 oldCaps = gSaveBlock2Ptr->optionsLevelCaps;
    gSaveBlock2Ptr->optionsLevelCaps = EXP_CAP_SOFT;
    cap = GetCurrentLevelCap();
    CreateMon(&mon, SPECIES_RIKO, cap - 2, 0, OTID_STRUCT_PLAYER_ID);
    ExpectQuantity(&mon, ITEM_RIKO_PUFFS, 999, 1);
    EXPECT(!ExecuteTableBasedItemEffect(&mon, ITEM_RIKO_PUFFS, 0, 0, 1, 1));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), cap);
    exp = GetMonData(&mon, MON_DATA_EXP);
    ExpectQuantity(&mon, ITEM_RIKO_PUFFS, 999, 0);
    EXPECT(ExecuteTableBasedItemEffect(&mon, ITEM_RIKO_PUFFS, 0, 0, 1, 1));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_EXP), exp);
    gSaveBlock2Ptr->optionsLevelCaps = oldCaps;
}

TEST("Riko Puffs are affordable consumable kibble with readable text and stable save ABI")
{
    ClearBag();
    EXPECT_EQ(GetItemPrice(ITEM_RIKO_PUFFS), 500);
    EXPECT_EQ(GetItemPocket(ITEM_RIKO_PUFFS), POCKET_ITEMS);
    EXPECT(!GetItemImportance(ITEM_RIKO_PUFFS));
    EXPECT_EQ(GetItemFieldFunc(ITEM_RIKO_PUFFS), ItemUseOutOfBattle_RareCandy);
    EXPECT(AddBagItem(ITEM_RIKO_PUFFS, 3));
    EXPECT(RemoveBagItem(ITEM_RIKO_PUFFS, 1));
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_RIKO_PUFFS), 2);
    EXPECT(gItemsInfo[ITEM_RIKO_PUFFS].iconPic != NULL && gItemsInfo[ITEM_RIKO_PUFFS].iconPalette != NULL);
    EXPECT_LE(GetStringWidth(FONT_NARROW, gItemsInfo[ITEM_RIKO_PUFFS].description, 0), 102);
    EXPECT_LE(GetStringWidth(FONT_NARROWER, gItemsInfo[ITEM_RIKO_PUFFS].name, 0), 88);
    EXPECT_EQ(sizeof(struct SaveBlock1), 15444);
    EXPECT_EQ(sizeof(struct SaveBlock2), 2864);
    EXPECT_EQ(sizeof(struct SaveBlock3), 100);
}
