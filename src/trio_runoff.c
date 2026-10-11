#include "global.h"
#include "battle.h"
#include "battle_controllers.h"
#include "battle_util.h"
#include "random.h"
#include "trio_runoff.h"
#include "constants/items.h"
#include "constants/battle_string_ids.h"

// Battle-only identity: party menus may rearrange slots. No Pokemon, saved
// party, HP, species, item, flag or variable is modified by this feature.
static EWRAM_DATA bool8 sAway = FALSE;
static EWRAM_DATA bool8 sAnnounced = FALSE;
static EWRAM_DATA u32 sPersonality = 0;
static EWRAM_DATA u32 sOtId = 0;
static EWRAM_DATA u16 sDepartureString = 0;
static EWRAM_DATA u16 sFamily = ITEM_NONE;
#if TESTING
static EWRAM_DATA bool8 sBattleTest = FALSE;
void TrioRunoff_EnableBattleTest(void) { sBattleTest = TRUE; }
#endif

void TrioRunoff_Clear(void)
{
    sAway = FALSE;
    sAnnounced = FALSE;
    sDepartureString = 0;
#if TESTING
    sBattleTest = FALSE;
#endif
}

bool32 TrioRunoff_IsAway(struct Pokemon *mon)
{
    if (!sAway)
        return FALSE;
    // Only the actual player party qualifies, never an enemy/copy/PC mon.
    for (u32 i = 0; i < PARTY_SIZE; i++)
        if (mon == &gPlayerParty[i])
            return mon->box.personality == sPersonality && mon->box.otId == sOtId
                && GetTrioSpiritKeepsakeForSpecies(GetMonData(mon, MON_DATA_SPECIES)) == sFamily;
    return FALSE;
}

void TrioRunoff_Begin(u32 chance)
{
    u8 candidates[PARTY_SIZE];
    u32 count = 0, usable = 0;
    TrioRunoff_Clear();
    // These formats use borrowed/reordered parties, recorded RNG or special
    // controllers. Ordinary solo singles/doubles, wilds and bosses qualify.
    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED
        | BATTLE_TYPE_RECORDED_LINK | BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER
        | BATTLE_TYPE_FRONTIER | BATTLE_TYPE_SAFARI | BATTLE_TYPE_FIRST_BATTLE
        | BATTLE_TYPE_WALLY_TUTORIAL | BATTLE_TYPE_EREADER_TRAINER
        | BATTLE_TYPE_TRAINER_HILL))
        return;
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        if (!IsValidForBattle(&gPlayerParty[i]))
            continue;
        usable++;
        bool32 unique = TRUE;
        for (u32 j = 0; j < PARTY_SIZE; j++)
            if (i != j && gPlayerParty[i].box.personality == gPlayerParty[j].box.personality
                && gPlayerParty[i].box.otId == gPlayerParty[j].box.otId
                && GetTrioSpiritKeepsakeForSpecies(GetMonData(&gPlayerParty[i], MON_DATA_SPECIES))
                    == GetTrioSpiritKeepsakeForSpecies(GetMonData(&gPlayerParty[j], MON_DATA_SPECIES)))
                unique = FALSE;
        if (unique && GetTrioSpiritKeepsakeForSpecies(GetMonData(&gPlayerParty[i], MON_DATA_SPECIES)) != ITEM_NONE)
            candidates[count++] = i;
    }
    if (chance == 0 || count == 0 || usable <= ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE) ? 2 : 1))
        return;
    if (chance < 100 && Random() % 100 >= chance)
        return;
    struct Pokemon *mon = &gPlayerParty[candidates[Random() % count]];
    sPersonality = mon->box.personality;
    sOtId = mon->box.otId;
    sFamily = GetTrioSpiritKeepsakeForSpecies(GetMonData(mon, MON_DATA_SPECIES));
    switch (sFamily)
    {
    case ITEM_RIKOS_SPARK: sDepartureString = STRINGID_TRIO_RIKO_RUNOFF; break;
    case ITEM_BIJUUS_LIGHT: sDepartureString = STRINGID_TRIO_BIJUU_RUNOFF; break;
    case ITEM_PENNYS_SHIELD: sDepartureString = STRINGID_TRIO_PENNY_RUNOFF; break;
    }
    sAway = TRUE;
}

void TrioRunoff_BeginBattle(void)
{
#if TESTING
    // Other battle fixtures retain their original deterministic behavior.
    bool32 enabled = sBattleTest;
    u32 savedFlags = gBattleTypeFlags;
    if (enabled)
        gBattleTypeFlags &= ~(BATTLE_TYPE_RECORDED | BATTLE_TYPE_RECORDED_LINK);
    TrioRunoff_Begin(enabled ? TRIO_RUNOFF_CHANCE : 0);
    gBattleTypeFlags = savedFlags;
#else
    TrioRunoff_Begin(TRIO_RUNOFF_CHANCE);
#endif
}

u32 TrioRunoff_TakeDepartureString(void)
{
    if (!sAway || sAnnounced)
        return 0;
    sAnnounced = TRUE;
    return sDepartureString;
}

bool32 TrioRunoff_DepartureAnnounced(void)
{
    return sAway && sAnnounced;
}
