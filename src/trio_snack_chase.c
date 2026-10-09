#include "global.h"
#include "battle.h"
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
    u16 phase = VarGet(VAR_TRIO_GANG_PHASE);
    u16 wave = VarGet(VAR_TRIO_GANG_ACTIVE_WAVE);
    if (VarGet(VAR_TRIO_SNACK_CHASE_STATE) != 3 && phase != 2)
        return;
    if (item != ITEM_NONE && !AddBagItem(item, 1))
        return;
    VarSet(VAR_TRIO_SNACK_STOLEN_ITEM, ITEM_NONE);
    if (VarGet(VAR_TRIO_SNACK_CHASE_STATE) == 3)
    {
        VarSet(VAR_TRIO_SNACK_CHASE_STATE, 4);
        VarSet(VAR_TRIO_GANG_WINS, 1);
    }
    else if (phase == 2 && wave >= 2 && wave <= 6)
        VarSet(VAR_TRIO_GANG_WINS, wave);
    VarSet(VAR_TRIO_GANG_PHASE, 0);
    VarSet(VAR_TRIO_GANG_ACTIVE_WAVE, 0);
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


static const struct { u8 group, num; u16 badge; u8 hideout; } sGangStops[] = {
    {MAP_GROUP(MAP_ROUTE37), MAP_NUM(MAP_ROUTE37), FLAG_BADGE03_GET, 15},
    {MAP_GROUP(MAP_ROUTE38), MAP_NUM(MAP_ROUTE38), FLAG_BADGE04_GET, 11},
    {MAP_GROUP(MAP_ROUTE42), MAP_NUM(MAP_ROUTE42), FLAG_BADGE06_GET, 20},
    {MAP_GROUP(MAP_ROUTE44), MAP_NUM(MAP_ROUTE44), FLAG_BADGE07_GET, 28},
    {MAP_GROUP(MAP_ROUTE26), MAP_NUM(MAP_ROUTE26), FLAG_BADGE08_GET, 14},
    {MAP_GROUP(MAP_ROUTE6), MAP_NUM(MAP_ROUTE6), FLAG_IS_CHAMPION, 11},
};

static u16 GangWaveForCurrentMap(void)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sGangStops); i++)
        if (gSaveBlock1Ptr->location.mapGroup == sGangStops[i].group
         && gSaveBlock1Ptr->location.mapNum == sGangStops[i].num
         && FlagGet(sGangStops[i].badge))
            return i + 1;
    return 0;
}

void TrioGang_PrepareAmbush(void)
{
    u16 wins = VarGet(VAR_TRIO_GANG_WINS);
    u16 wave = GangWaveForCurrentMap();
    // Migrate an already completed one-thief chase; never re-steal its item.
    if (wins == 0 && VarGet(VAR_TRIO_SNACK_CHASE_STATE) == 4)
    {
        wins = 1;
        VarSet(VAR_TRIO_GANG_WINS, wins);
    }
    VarSet(VAR_TEMP_B, 0);
    FlagSet(FLAG_HIDE_TRIO_GANG_HIDEOUT);
    if (wave >= 2 && VarGet(VAR_TRIO_GANG_ACTIVE_WAVE) == wave
     && VarGet(VAR_TRIO_GANG_PHASE) != 0)
        FlagClear(FLAG_HIDE_TRIO_GANG_HIDEOUT);
    if (!wave || wave != wins + 1)
        return;
    if (VarGet(VAR_TRIO_SNACK_CHASE_STATE) == 3
     || VarGet(VAR_TRIO_GANG_PHASE) == 2)
        VarSet(VAR_TEMP_B, 7); // Reclaim pending item without another fight.
    else if (wave == 1)
    {
        // First encounter keeps the optional pursuit. No exit gate.
        // Persistent state prevents another entry scene after a loss.
        if (VarGet(VAR_TRIO_SNACK_CHASE_STATE) == 0)
            VarSet(VAR_TEMP_B, 8);
    }
    else if (VarGet(VAR_TRIO_GANG_PHASE) == 0)
        VarSet(VAR_TEMP_B, wave); // New theft only; pending fights are optional.
}

void TrioGang_BeginAmbush(void)
{
    u16 wave = GangWaveForCurrentMap();
    u16 item;
    gSpecialVar_Result = FALSE;
    gSpecialVar_0x8005 = FALSE; // TRUE means a new theft, FALSE means a retry.
    if (!wave || wave != VarGet(VAR_TRIO_GANG_WINS) + 1
     || VarGet(VAR_TRIO_GANG_PHASE) == 2)
        return;
    if (wave == 1)
    {
        if (VarGet(VAR_TRIO_SNACK_CHASE_STATE) == 0)
        {
            TrioSnack_BeginTheft();
            if (!gSpecialVar_Result)
                return;
            gSpecialVar_0x8005 = TRUE;
        }
        if (VarGet(VAR_TRIO_SNACK_CHASE_STATE) != 1
         && VarGet(VAR_TRIO_SNACK_CHASE_STATE) != 2)
            return;
    }
    else if (VarGet(VAR_TRIO_GANG_PHASE) == 0)
    {
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
        gSpecialVar_0x8005 = TRUE;
    }
    else if (VarGet(VAR_TRIO_GANG_ACTIVE_WAVE) != wave)
        return;
    VarSet(VAR_TRIO_GANG_ACTIVE_WAVE, wave);
    VarSet(VAR_TRIO_GANG_PHASE, 1);
    gSpecialVar_0x8004 = wave;
    gSpecialVar_0x8006 = sGangStops[wave - 1].hideout;
    ConvertIntToDecimalStringN(gStringVar2, wave, STR_CONV_MODE_LEFT_ALIGN, 1);
    gSpecialVar_Result = TRUE;
}

void TrioGang_RecordVictory(void)
{
    u16 wave = VarGet(VAR_TRIO_GANG_ACTIVE_WAVE);
    if (gBattleOutcome != B_OUTCOME_WON || wave < 1 || wave > 6
     || VarGet(VAR_TRIO_GANG_PHASE) != 1)
        return;
    if (wave == 1)
        VarSet(VAR_TRIO_SNACK_CHASE_STATE, 3);
    VarSet(VAR_TRIO_GANG_PHASE, 2);
}

// These trainer slots have reclaimed puzzle flags. Gang progress must never
// read or write trainerId + TRAINER_FLAGS_START for them.
u16 TrioGang_WaveForTrainer(u16 trainer)
{
    if (trainer == TRAINER_ROUTE37_SNACK_THIEF)
        return 1;
    if (trainer >= TRAINER_GREEDENT_GANG_2 && trainer <= TRAINER_GREEDENT_GANG_6)
        return trainer - TRAINER_GREEDENT_GANG_2 + 2;
    return 0;
}
