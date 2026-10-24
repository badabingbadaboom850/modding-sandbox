#include "global.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "trio_action_arena.h"
#include "test/test.h"
#include "constants/map_groups.h"

static void Context(u32 id, u32 badges, bool32 champion)
{
    static const u16 flags[] = {FLAG_BADGE01_GET, FLAG_BADGE02_GET, FLAG_BADGE03_GET, FLAG_BADGE04_GET,
        FLAG_BADGE05_GET, FLAG_BADGE06_GET, FLAG_BADGE07_GET, FLAG_BADGE08_GET, FLAG_BADGE09_GET,
        FLAG_BADGE10_GET, FLAG_BADGE11_GET, FLAG_BADGE12_GET, FLAG_BADGE13_GET, FLAG_BADGE14_GET,
        FLAG_BADGE15_GET, FLAG_BADGE16_GET};
    const struct TrioArenaChallenge *c = &gTrioArenaChallenges[id];
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(c->map);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(c->map);
    gSpecialVar_LastTalked = c->localId;
    for (u32 i = 0; i < ARRAY_COUNT(flags); i++)
        if (i < badges) FlagSet(flags[i]); else FlagClear(flags[i]);
    if (champion) FlagSet(FLAG_IS_CHAMPION); else FlagClear(FLAG_IS_CHAMPION);
}

TEST("Arena circuit gates all eight actual NPC contexts and rejects forged outcomes")
{
    VarSet(VAR_TRIO_ARENA_WINS, 0); VarSet(VAR_TRIO_ARENA_REWARDS, 0);
    for (u32 id = 0; id < TRIO_ARENA_CHALLENGES; id++)
    {
        const struct TrioArenaChallenge *c = &gTrioArenaChallenges[id];
        Context(id, c->badges - 1, TRUE);
        EXPECT_EQ(GetTrioArenaChallengeState(), ARENA_CHALLENGE_LOCKED);
        EXPECT(!TrioArena_CanStartChallenge(id));
        Context(id, c->badges, !c->champion);
        EXPECT_EQ(GetTrioArenaChallengeState(), c->champion ? ARENA_CHALLENGE_LOCKED : ARENA_CHALLENGE_READY);
        Context(id, c->badges, TRUE);
        EXPECT_EQ(GetTrioArenaChallengeState(), ARENA_CHALLENGE_READY);
        EXPECT(TrioArena_CanStartChallenge(id));
        EXPECT(gSpeciesInfo[c->species].overworldData.images != NULL);
        for (u32 result = 0; result <= 3; result++)
        {
            if (result == ARENA_RESULT_WON) continue;
            gSpecialVar_Result = result; RecordTrioArenaChallengeWin();
            EXPECT_EQ(VarGet(VAR_TRIO_ARENA_WINS), 0);
        }
        gSpecialVar_LastTalked = 0;
        EXPECT_EQ(GetTrioArenaChallengeState(), ARENA_CHALLENGE_INVALID);
        gSpecialVar_Result = ARENA_RESULT_WON; RecordTrioArenaChallengeWin();
        EXPECT_EQ(VarGet(VAR_TRIO_ARENA_WINS), 0);
        EXPECT_EQ(ClaimTrioArenaChallengeReward(), 3);
    }
}

TEST("Eight arena wins grant exactly eight Puffs and never repeat after reload or replay")
{
    ClearBag(); VarSet(VAR_TRIO_ARENA_WINS, 0xA500); VarSet(VAR_TRIO_ARENA_REWARDS, 0x5A00);
    for (u32 id = 0; id < TRIO_ARENA_CHALLENGES; id++)
    {
        Context(id, 16, TRUE);
        EXPECT_EQ(ClaimTrioArenaChallengeReward(), 3);
        gSpecialVar_Result = ARENA_RESULT_WON; RecordTrioArenaChallengeWin();
        EXPECT_EQ(GetTrioArenaChallengeState(), ARENA_CHALLENGE_PENDING);
        EXPECT_EQ(ClaimTrioArenaChallengeReward(), 1);
        EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_RIKO_PUFFS), id + 1);
        // Reconstruct NPC context, as on a map reload; only saved bits carry progress.
        gSpecialVar_LastTalked = 0; Context(id, 16, TRUE);
        EXPECT_EQ(GetTrioArenaChallengeState(), ARENA_CHALLENGE_CLAIMED);
        gSpecialVar_Result = ARENA_RESULT_WON; RecordTrioArenaChallengeWin();
        EXPECT_EQ(ClaimTrioArenaChallengeReward(), 2);
        EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_RIKO_PUFFS), id + 1);
    }
    EXPECT_EQ(VarGet(VAR_TRIO_ARENA_WINS), 0xA5FF);
    EXPECT_EQ(VarGet(VAR_TRIO_ARENA_REWARDS), 0x5AFF);
    EXPECT_EQ(sizeof(struct SaveBlock1), 15444);
    EXPECT_EQ(sizeof(struct SaveBlock2), 2864);
    EXPECT_EQ(sizeof(struct Pokemon), 96);
}

TEST("Full Bag keeps earned Puff pending until real item delivery succeeds")
{
    ClearBag(); VarSet(VAR_TRIO_ARENA_WINS, 1); VarSet(VAR_TRIO_ARENA_REWARDS, 0);
    Context(0, 16, TRUE);
    enum Pocket pocket = GetItemPocket(ITEM_RIKO_PUFFS);
    u32 filled = 0; u16 first = 0;
    for (u32 item = 1; item < ITEMS_COUNT && filled < BAG_ITEMS_COUNT; item++)
        if (item != ITEM_RIKO_PUFFS && GetItemPocket(item) == pocket && AddBagItem(item, 1))
        { if (!first) first = item; filled++; }
    EXPECT_EQ(filled, BAG_ITEMS_COUNT);
    EXPECT_EQ(ClaimTrioArenaChallengeReward(), 0);
    EXPECT_EQ(VarGet(VAR_TRIO_ARENA_REWARDS), 0);
    Context(0, 0, FALSE);
    EXPECT_EQ(GetTrioArenaChallengeState(), ARENA_CHALLENGE_PENDING);
    EXPECT(RemoveBagItem(first, 1));
    EXPECT_EQ(ClaimTrioArenaChallengeReward(), 1);
    EXPECT_EQ(CountTotalItemQuantityInBag(ITEM_RIKO_PUFFS), 1);
    EXPECT_EQ(ClaimTrioArenaChallengeReward(), 2);
}

TEST("Circuit bosses scale, telegraph, and end after one duel for every girl")
{
    struct TrioArenaState a, frozen;
    for (u32 id = 0; id < TRIO_ARENA_CHALLENGES; id++)
        for (u32 girl = 0; girl < ARENA_GIRLS; girl++)
        {
            EXPECT(TrioArena_InitChallenge(&a, girl, id));
            EXPECT_EQ(a.rounds, 1);
            EXPECT_EQ(a.enemyHp, 138 + (id + 1) * 13);
            a.enemyTimer = 1;
            TrioArena_Step(&a, 0);
            EXPECT_EQ(a.enemyMode, ARENA_WARN);
            EXPECT_EQ(a.pattern, gTrioArenaChallenges[id].patterns[0]);
            EXPECT_GT(a.enemyTimer, 30);
            a.ex = a.x + 16 * 16; a.ey = a.y;
            a.enemyHp = 1; a.secondaryCd = 0;
            for (u32 frame = 0; frame < 20 && a.status == ARENA_FIGHT; frame++)
                TrioArena_Step(&a, TRIO_ARENA_SECONDARY);
            EXPECT_EQ(a.status, ARENA_WON);
            frozen = a; TrioArena_NextRound(&a); TrioArena_Step(&a, 0xFFFF);
            EXPECT_EQ(memcmp(&a, &frozen, sizeof(a)), 0);
        }
    frozen = a;
    EXPECT(!TrioArena_InitChallenge(&a, 0, 255));
    EXPECT(!TrioArena_InitChallenge(&a, 255, 0));
    EXPECT_EQ(memcmp(&a, &frozen, sizeof(a)), 0);
}
