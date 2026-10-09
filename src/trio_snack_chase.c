#include "global.h"
#include "event_data.h"
#include "item.h"
#include "string_util.h"
#include "trio_snack_chase.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/opponents.h"
#include "constants/vars.h"

// States: 0 untouched; 1 north grass; 2 berry grove; 3 won/return pending;
// 4 complete. Item escrow uses a persistent var, never a temporary script var.
void TrioSnack_BeginTheft(void)
{
    u16 item;
    gSpecialVar_Result = FALSE;
    if (!FlagGet(FLAG_BADGE03_GET) || VarGet(VAR_TRIO_SNACK_CHASE_STATE) != 0)
        return;

    // Prefer the girls' Chicky (Oran Berry); otherwise take one Bag Berry.
    // Held items, medicine, evolution items and key items are never examined.
    item = ITEM_ORAN_BERRY;
    if (!CheckBagHasItem(item, 1))
    {
        for (item = FIRST_BERRY_INDEX; item <= LAST_BERRY_INDEX; item++)
            if (CheckBagHasItem(item, 1))
                break;
        if (item > LAST_BERRY_INDEX)
            item = ITEM_NONE;
    }
    if (item != ITEM_NONE && !RemoveBagItem(item, 1))
        return;
    VarSet(VAR_TRIO_SNACK_STOLEN_ITEM, item);
    VarSet(VAR_TRIO_SNACK_CHASE_STATE, 1);
    gSpecialVar_Result = TRUE;
}

void TrioSnack_BufferItem(void)
{
    u16 item = VarGet(VAR_TRIO_SNACK_STOLEN_ITEM);
    if (item == ITEM_NONE)
        StringCopy(gStringVar1, COMPOUND_STRING("picnic snack"));
    else
        CopyItemName(item, gStringVar1);
}

void TrioSnack_ReturnItem(void)
{
    u16 item = VarGet(VAR_TRIO_SNACK_STOLEN_ITEM);
    gSpecialVar_Result = FALSE;
    if (VarGet(VAR_TRIO_SNACK_CHASE_STATE) != 3)
        return;
    // Add exactly once. If the pocket/stack fills during the chase, retain
    // both the exact item and the won state until the player makes room.
    if (item != ITEM_NONE && !AddBagItem(item, 1))
        return;
    VarSet(VAR_TRIO_SNACK_STOLEN_ITEM, ITEM_NONE);
    VarSet(VAR_TRIO_SNACK_CHASE_STATE, 4);
    gSpecialVar_Result = TRUE;
}

void TrioSnack_UpdateObjects(void)
{
    u16 state = VarGet(VAR_TRIO_SNACK_CHASE_STATE);
    FlagSet(FLAG_HIDE_TRIO_SNACK_START);
    FlagSet(FLAG_HIDE_TRIO_SNACK_GRASS);
    FlagSet(FLAG_HIDE_TRIO_SNACK_GROVE);
    if (!FlagGet(FLAG_BADGE03_GET))
        return;
    if (state == 0)
        FlagClear(FLAG_HIDE_TRIO_SNACK_START);
    else if (state == 1)
        FlagClear(FLAG_HIDE_TRIO_SNACK_GRASS);
    else if (state == 2 || state == 3)
        FlagClear(FLAG_HIDE_TRIO_SNACK_GROVE);
}

bool32 TrioSnack_IsFriendlyBattle(u8 mapGroup, u8 mapNum, u16 trainer)
{
    return mapGroup == MAP_GROUP(MAP_ROUTE37)
        && mapNum == MAP_NUM(MAP_ROUTE37)
        && trainer == TRAINER_ROUTE37_SNACK_THIEF;
}
