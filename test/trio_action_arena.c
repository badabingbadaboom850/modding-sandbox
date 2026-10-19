#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "trio_action_arena.h"
#include "test/test.h"

TEST("Action arena uses temporary training state and preserves the actual party")
{
    struct TrioArenaState a;
    struct Pokemon saved[PARTY_SIZE];
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_RIKO_RAINCOAT, 37, 0, OTID_STRUCT_PLAYER_ID);
    memcpy(saved, gPlayerParty, sizeof(saved));
    for (u32 girl = 0; girl < ARENA_GIRLS; girl++)
    {
        TrioArena_Init(&a, girl);
        EXPECT_EQ(a.girl, girl);
        EXPECT_EQ(a.hp, 100);
        for (u32 frame = 0; frame < 1200; frame++)
            TrioArena_Step(&a, TRIO_ARENA_PRIMARY | TRIO_ARENA_LOCK | TRIO_ARENA_SECONDARY);
        EXPECT_EQ(memcmp(saved, gPlayerParty, sizeof(saved)), 0);
    }
    TrioArena_Init(&a, 255);
    EXPECT_EQ(a.girl, ARENA_RIKO);
}

TEST("Action arena cooldowns block held attack spam and projectile slots stay bounded")
{
    struct TrioArenaState a;
    TrioArena_Init(&a, ARENA_BIJUU);
    a.enemyMode = ARENA_RECOVER; a.enemyTimer = 60000;
    TrioArena_Step(&a, TRIO_ARENA_PRIMARY);
    EXPECT_EQ(a.primaryCd, 20);
    for (u32 i = 0; i < 19; i++) TrioArena_Step(&a, TRIO_ARENA_PRIMARY);
    EXPECT_EQ(a.primaryCd, 1);
    u32 count = 0;
    for (u32 i = 0; i < 4; i++) count += a.shots[i].life != 0;
    EXPECT_EQ(count, 1);
    TrioArena_Step(&a, TRIO_ARENA_PRIMARY);
    EXPECT_EQ(a.primaryCd, 20);
    count = 0;
    for (u32 i = 0; i < 4; i++) count += a.shots[i].life != 0;
    EXPECT_EQ(count, 2);
    for (u32 i = 0; i < 4; i++) a.shots[i].life = 100;
    a.primaryCd = a.secondaryCd = 0;
    TrioArena_Step(&a, TRIO_ARENA_PRIMARY | TRIO_ARENA_SECONDARY);
    EXPECT_EQ(a.primaryCd, 0);
    EXPECT_EQ(a.secondaryCd, 0);
    for (u32 i = 4; i < TRIO_ARENA_SHOTS; i++) EXPECT_EQ(a.shots[i].life, 0);
}

TEST("Action arena movement clamps at every wall and diagonal dodge keeps its direction")
{
    struct TrioArenaState a;
    static const u16 directions[] = {TRIO_ARENA_MOVE_LEFT, TRIO_ARENA_MOVE_RIGHT, TRIO_ARENA_MOVE_UP, TRIO_ARENA_MOVE_DOWN};
    for (u32 dir = 0; dir < ARRAY_COUNT(directions); dir++)
    {
        TrioArena_Init(&a, ARENA_RIKO);
        a.enemyMode = ARENA_RECOVER; a.enemyTimer = 60000;
        for (u32 i = 0; i < 400; i++) TrioArena_Step(&a, directions[dir] | TRIO_ARENA_DODGE);
        EXPECT_GE(a.x, TRIO_ARENA_LEFT * 16); EXPECT_LE(a.x, TRIO_ARENA_RIGHT * 16);
        EXPECT_GE(a.y, TRIO_ARENA_TOP * 16); EXPECT_LE(a.y, TRIO_ARENA_BOTTOM * 16);
        if (dir == 0) EXPECT_EQ(a.x, TRIO_ARENA_LEFT * 16);
        if (dir == 1) EXPECT_EQ(a.x, TRIO_ARENA_RIGHT * 16);
        if (dir == 2) EXPECT_EQ(a.y, TRIO_ARENA_TOP * 16);
        if (dir == 3) EXPECT_EQ(a.y, TRIO_ARENA_BOTTOM * 16);
    }
    TrioArena_Init(&a, ARENA_RIKO);
    s16 x = a.x;
    TrioArena_Step(&a, TRIO_ARENA_MOVE_UP | TRIO_ARENA_DODGE);
    EXPECT_EQ(a.x, x);
    EXPECT_LT(a.y, 80 * 16);
    EXPECT_GT(a.invincible, 0);
}

TEST("Action arena telegraphs before damage and dodge prevents the charge hit")
{
    struct TrioArenaState a;
    TrioArena_Init(&a, ARENA_RIKO);
    a.invincible = 0; a.x = 100 * 16; a.ex = 120 * 16;
    a.enemyTimer = 1;
    TrioArena_Step(&a, 0);
    EXPECT_EQ(a.enemyMode, ARENA_WARN);
    EXPECT_EQ(a.enemyTimer, 45);
    EXPECT_EQ(a.hp, 100);
    for (u32 i = 0; i < 44; i++) TrioArena_Step(&a, 0);
    EXPECT_EQ(a.hp, 100);
    TrioArena_Step(&a, TRIO_ARENA_MOVE_UP | TRIO_ARENA_DODGE);
    EXPECT_EQ(a.enemyMode, ARENA_CHARGE);
    for (u32 i = 0; i < 9; i++) TrioArena_Step(&a, TRIO_ARENA_MOVE_UP);
    EXPECT_EQ(a.hp, 100);
    TrioArena_Init(&a, ARENA_RIKO);
    a.invincible = 0; a.x = 100 * 16; a.ex = 120 * 16;
    a.enemyMode = ARENA_CHARGE; a.enemyTimer = 20; a.targetX = -32; a.targetY = 0;
    TrioArena_Step(&a, 0);
    EXPECT_EQ(a.hp, 82);
    for (u32 i = 0; i < 10; i++) TrioArena_Step(&a, 0);
    EXPECT_EQ(a.hp, 82);
}

TEST("Action arena girls have distinct specials and frost slows the opponent")
{
    struct TrioArenaState a;
    TrioArena_Init(&a, ARENA_RIKO);
    a.ex = a.x + 32 * 16;
    TrioArena_Step(&a, TRIO_ARENA_SECONDARY);
    EXPECT_EQ(a.enemyHp, 58);
    EXPECT_EQ(a.secondaryCd, 150);
    TrioArena_Step(&a, TRIO_ARENA_SECONDARY);
    EXPECT_EQ(a.enemyHp, 58);
    TrioArena_Init(&a, ARENA_BIJUU);
    a.ex = a.x + 20 * 16;
    for (u32 i = 0; i < 6; i++) TrioArena_Step(&a, TRIO_ARENA_SECONDARY);
    EXPECT_GT(a.slow, 0);
    EXPECT_LT(a.enemyHp, 90);
    TrioArena_Init(&a, ARENA_PENNY);
    a.ex = a.x + 20 * 16; a.enemyMode = ARENA_RECOVER; a.enemyTimer = 100;
    for (u32 i = 0; i < 14; i++) TrioArena_Step(&a, TRIO_ARENA_SECONDARY);
    EXPECT_EQ(a.enemyHp, 54);
    EXPECT_EQ(a.rushHit, 1);
}

TEST("Action arena rounds heal once and terminal outcomes cannot keep simulating")
{
    struct TrioArenaState a, frozen;
    TrioArena_Init(&a, ARENA_RIKO);
    for (u32 round = 0; round < 3; round++)
    {
        a.hp = 40;
        a.ex = a.x + 20 * 16; a.enemyHp = 1; a.secondaryCd = 0;
        TrioArena_Step(&a, TRIO_ARENA_SECONDARY);
        EXPECT_EQ(a.status, round == 2 ? ARENA_WON : ARENA_ROUND_CLEAR);
        frozen = a; TrioArena_Step(&a, 0xFFFF);
        EXPECT_EQ(memcmp(&a, &frozen, sizeof(a)), 0);
        TrioArena_NextRound(&a);
        if (round < 2) { EXPECT_EQ(a.round, round + 1); EXPECT_EQ(a.hp, 65); }
    }
    EXPECT_EQ(a.status, ARENA_WON);
    TrioArena_Init(&a, ARENA_RIKO);
    a.hp = 1; a.invincible = 0; a.ex = a.x + 16 * 16;
    a.enemyMode = ARENA_CHARGE; a.enemyTimer = 2; a.targetX = -16; a.targetY = 0;
    TrioArena_Step(&a, 0);
    EXPECT_EQ(a.status, ARENA_LOST);
    EXPECT_EQ(a.hp, 0);
    frozen = a; TrioArena_NextRound(&a); TrioArena_Step(&a, 0xFFFF);
    EXPECT_EQ(memcmp(&a, &frozen, sizeof(a)), 0);
}
