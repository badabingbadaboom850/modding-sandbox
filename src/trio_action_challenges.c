#include "global.h"
#include "event_data.h"
#include "item.h"
#include "trio_action_arena.h"
#include "constants/map_groups.h"
#include "constants/map_event_ids.h"

static const u8 sEcho[] = _("Echo Duel");
static const u8 sPomFu[] = _("Pom Fu Trial");
static const u8 sHarbor[] = _("Harbor Sparks");
static const u8 sFrost[] = _("Frost Footwork");
static const u8 sDragon[] = _("Dragon Dance");
static const u8 sMoon[] = _("Moonlight Duel");
static const u8 sMind[] = _("Psychic Crossfire");
static const u8 sFinal[] = _("Final Roar");

const struct TrioArenaChallenge gTrioArenaChallenges[TRIO_ARENA_CHALLENGES] =
{
    {MAP_ECRUTEAK_CITY, SPECIES_HAUNTER, LOCALID_ARENA_ECRUTEAKCITY, 4, FALSE, {1, 1, 0}, sEcho},
    {MAP_CIANWOOD_CITY, SPECIES_MACHOKE, LOCALID_ARENA_CIANWOODCITY, 5, FALSE, {0, 2, 0}, sPomFu},
    {MAP_OLIVINE_CITY, SPECIES_MAGNETON, LOCALID_ARENA_OLIVINECITY, 6, FALSE, {1, 0, 1}, sHarbor},
    {MAP_MAHOGANYTOWN, SPECIES_PILOSWINE, LOCALID_ARENA_MAHOGANYTOWN, 7, FALSE, {2, 0, 2}, sFrost},
    {MAP_BLACKTHORN_CITY, SPECIES_DRAGONAIR, LOCALID_ARENA_BLACKTHORNCITY, 8, FALSE, {0, 1, 2}, sDragon},
    {MAP_PEWTER_CITY, SPECIES_UMBREON, LOCALID_ARENA_PEWTERCITY, 8, TRUE, {1, 2, 0}, sMoon},
    {MAP_CELADON_CITY, SPECIES_ALAKAZAM, LOCALID_ARENA_CELADONCITY, 12, TRUE, {1, 1, 2}, sMind},
    {MAP_SAFFRON_CITY, SPECIES_TYRANITAR, LOCALID_ARENA_SAFFRONCITY, 16, TRUE, {2, 1, 0}, sFinal},
};

u8 TrioArena_CurrentChallenge(void)
{
    for (u32 i = 0; i < TRIO_ARENA_CHALLENGES; i++)
    {
        const struct TrioArenaChallenge *c = &gTrioArenaChallenges[i];
        if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(c->map)
            && gSaveBlock1Ptr->location.mapNum == MAP_NUM(c->map)
            && gSpecialVar_LastTalked == c->localId) return i;
    }
    return TRIO_ARENA_PRACTICE;
}

bool32 TrioArena_CanStartChallenge(u8 id)
{
    u32 badges = 0;
    static const u16 flags[] = {FLAG_BADGE01_GET, FLAG_BADGE02_GET, FLAG_BADGE03_GET, FLAG_BADGE04_GET,
        FLAG_BADGE05_GET, FLAG_BADGE06_GET, FLAG_BADGE07_GET, FLAG_BADGE08_GET, FLAG_BADGE09_GET,
        FLAG_BADGE10_GET, FLAG_BADGE11_GET, FLAG_BADGE12_GET, FLAG_BADGE13_GET, FLAG_BADGE14_GET,
        FLAG_BADGE15_GET, FLAG_BADGE16_GET};
    if (id >= TRIO_ARENA_CHALLENGES || TrioArena_CurrentChallenge() != id) return FALSE;
    for (u32 i = 0; i < ARRAY_COUNT(flags); i++) badges += !!FlagGet(flags[i]);
    return badges >= gTrioArenaChallenges[id].badges
        && (!gTrioArenaChallenges[id].champion || FlagGet(FLAG_IS_CHAMPION));
}

u16 GetTrioArenaChallengeState(void)
{
    u8 id = TrioArena_CurrentChallenge();
    if (id >= TRIO_ARENA_CHALLENGES) return ARENA_CHALLENGE_INVALID;
    if (VarGet(VAR_TRIO_ARENA_REWARDS) & (1u << id)) return ARENA_CHALLENGE_CLAIMED;
    if (VarGet(VAR_TRIO_ARENA_WINS) & (1u << id)) return ARENA_CHALLENGE_PENDING;
    return TrioArena_CanStartChallenge(id) ? ARENA_CHALLENGE_READY : ARENA_CHALLENGE_LOCKED;
}

void RecordTrioArenaChallengeWin(void)
{
    u8 id = TrioArena_CurrentChallenge();
    bool32 won = gSpecialVar_Result == ARENA_RESULT_WON;
    gSpecialVar_Result = FALSE;
    if (!won || !TrioArena_CanStartChallenge(id)) return;
    VarSet(VAR_TRIO_ARENA_WINS, VarGet(VAR_TRIO_ARENA_WINS) | (1u << id));
    gSpecialVar_Result = TRUE;
}

// 0 = full Bag, 1 = received, 2 = already received, 3 = no earned prize.
// Atomic item delivery: write the claim only after the real Bag accepts one.
u16 ClaimTrioArenaChallengeReward(void)
{
    u8 id = TrioArena_CurrentChallenge();
    u16 state = GetTrioArenaChallengeState();
    if (state == ARENA_CHALLENGE_CLAIMED) return 2;
    if (state != ARENA_CHALLENGE_PENDING) return 3;
    if (!AddBagItem(ITEM_RIKO_PUFFS, 1)) return 0;
    VarSet(VAR_TRIO_ARENA_REWARDS, VarGet(VAR_TRIO_ARENA_REWARDS) | (1u << id));
    return 1;
}
