#include "global.h"
#include "event_data.h"
#include "item.h"
#include "trio_snack_chase.h"
#include "test/test.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/opponents.h"
#include "constants/vars.h"

static void ResetChase(void)
{
    ClearBag();
    FlagSet(FLAG_BADGE03_GET);
    VarSet(VAR_TRIO_SNACK_CHASE_STATE, 0);
    VarSet(VAR_TRIO_SNACK_STOLEN_ITEM, ITEM_NONE);
    VarSet(VAR_TRIO_GANG_WINS, 0);
    VarSet(VAR_TRIO_GANG_ACTIVE_WAVE, 0);
    VarSet(VAR_TRIO_GANG_PHASE, 0);
}

TEST("Snack thief removes one real Berry and cannot steal twice")
{
    ResetChase();
    EXPECT(AddBagItem(ITEM_ORAN_BERRY, 2));
    EXPECT(AddBagItem(ITEM_CHERI_BERRY, 3));
    EXPECT(AddBagItem(ITEM_POTION, 4));
    EXPECT(AddBagItem(ITEM_DADS_KEYS, 1));
    TrioSnack_BeginTheft();
    EXPECT(gSpecialVar_Result);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_CHASE_STATE), 1);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_STOLEN_ITEM), ITEM_ORAN_BERRY);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ORAN_BERRY), 1);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_CHERI_BERRY), 3);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_POTION), 4);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_DADS_KEYS), 1);
    TrioSnack_BeginTheft();
    EXPECT(!gSpecialVar_Result);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ORAN_BERRY), 1);
    TrioSnack_UpdateObjects(); // A map reload only derives visibility.
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_STOLEN_ITEM), ITEM_ORAN_BERRY);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_CHASE_STATE), 1);
}

TEST("Snack theft requires Whitney and handles another Berry or an empty Bag")
{
    ResetChase();
    EXPECT(AddBagItem(ITEM_CHERI_BERRY, 2));
    FlagClear(FLAG_BADGE03_GET);
    TrioSnack_BeginTheft();
    EXPECT(!gSpecialVar_Result);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_CHASE_STATE), 0);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_CHERI_BERRY), 2);
    FlagSet(FLAG_BADGE03_GET);
    TrioSnack_BeginTheft();
    EXPECT(gSpecialVar_Result);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_STOLEN_ITEM), ITEM_CHERI_BERRY);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_CHERI_BERRY), 1);
    ResetChase();
    EXPECT(AddBagItem(ITEM_POTION, 3));
    TrioSnack_BeginTheft();
    EXPECT(gSpecialVar_Result);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_STOLEN_ITEM), ITEM_NONE);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_CHASE_STATE), 1);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_POTION), 3);
    VarSet(VAR_TRIO_SNACK_CHASE_STATE, 3);
    TrioSnack_ReturnItem();
    EXPECT(gSpecialVar_Result);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_CHASE_STATE), 4);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_POTION), 3);
}

TEST("Snack return requires victory and restores exactly once")
{
    ResetChase();
    EXPECT(AddBagItem(ITEM_PECHA_BERRY, 3));
    TrioSnack_BeginTheft();
    VarSet(VAR_TRIO_SNACK_CHASE_STATE, 2);
    TrioSnack_ReturnItem();
    EXPECT(!gSpecialVar_Result);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_PECHA_BERRY), 2);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_STOLEN_ITEM), ITEM_PECHA_BERRY);
    VarSet(VAR_TRIO_SNACK_CHASE_STATE, 3);
    TrioSnack_ReturnItem();
    EXPECT(gSpecialVar_Result);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_PECHA_BERRY), 3);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_STOLEN_ITEM), ITEM_NONE);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_CHASE_STATE), 4);
    TrioSnack_ReturnItem();
    EXPECT(!gSpecialVar_Result);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_PECHA_BERRY), 3);
    TrioSnack_BeginTheft();
    EXPECT(!gSpecialVar_Result);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_PECHA_BERRY), 3);
}

TEST("A filled Berry stack retains escrow and lets the winner retry without a fight")
{
    ResetChase();
    EXPECT(AddBagItem(ITEM_ORAN_BERRY, 1));
    TrioSnack_BeginTheft();
    EXPECT(AddBagItem(ITEM_ORAN_BERRY, MAX_BAG_ITEM_CAPACITY));
    VarSet(VAR_TRIO_SNACK_CHASE_STATE, 3);
    TrioSnack_ReturnItem();
    EXPECT(!gSpecialVar_Result);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_CHASE_STATE), 3);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_STOLEN_ITEM), ITEM_ORAN_BERRY);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ORAN_BERRY), MAX_BAG_ITEM_CAPACITY);
    TrioSnack_UpdateObjects();
    EXPECT(!FlagGet(FLAG_HIDE_TRIO_SNACK_GROVE));
    EXPECT(RemoveBagItem(ITEM_ORAN_BERRY, 1));
    TrioSnack_ReturnItem();
    EXPECT(gSpecialVar_Result);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_ORAN_BERRY), MAX_BAG_ITEM_CAPACITY);
    EXPECT_EQ(VarGet(VAR_TRIO_SNACK_CHASE_STATE), 4);
    TrioSnack_ReturnItem();
    EXPECT(!gSpecialVar_Result);
}

TEST("Legacy chase visibility survives every saved stage")
{
    u32 state;
    ResetChase();
    for (state = 0; state <= 4; state++)
    {
        VarSet(VAR_TRIO_SNACK_CHASE_STATE, state);
        TrioSnack_UpdateObjects();
        EXPECT_EQ(FlagGet(FLAG_HIDE_TRIO_SNACK_START), state != 0);
        EXPECT_EQ(FlagGet(FLAG_HIDE_TRIO_SNACK_GRASS), state != 1);
        EXPECT_EQ(FlagGet(FLAG_HIDE_TRIO_SNACK_GROVE), state != 2 && state != 3);
        EXPECT_EQ(VarGet(VAR_TRIO_SNACK_CHASE_STATE), state);
    }
    FlagClear(FLAG_BADGE03_GET);
    VarSet(VAR_TRIO_SNACK_CHASE_STATE, 0);
    TrioSnack_UpdateObjects();
    EXPECT(FlagGet(FLAG_HIDE_TRIO_SNACK_START));
    EXPECT(FlagGet(FLAG_HIDE_TRIO_SNACK_GRASS));
    EXPECT(FlagGet(FLAG_HIDE_TRIO_SNACK_GROVE));
}
