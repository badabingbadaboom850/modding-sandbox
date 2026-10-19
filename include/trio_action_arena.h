#ifndef GUARD_TRIO_ACTION_ARENA_H
#define GUARD_TRIO_ACTION_ARENA_H

// Arena-only simulation. No party, inventory, flags, saved variables or RNG.
#define TRIO_ARENA_SHOTS 12
#define TRIO_ARENA_LEFT 20
#define TRIO_ARENA_RIGHT 220
#define TRIO_ARENA_TOP 44
#define TRIO_ARENA_BOTTOM 116
#define TRIO_ARENA_MOVE_UP (1 << 0)
#define TRIO_ARENA_MOVE_DOWN (1 << 1)
#define TRIO_ARENA_MOVE_LEFT (1 << 2)
#define TRIO_ARENA_MOVE_RIGHT (1 << 3)
#define TRIO_ARENA_PRIMARY (1 << 4)
#define TRIO_ARENA_SECONDARY (1 << 5)
#define TRIO_ARENA_DODGE (1 << 6)
#define TRIO_ARENA_LOCK (1 << 7)

enum { ARENA_RIKO, ARENA_BIJUU, ARENA_PENNY, ARENA_GIRLS };
enum { ARENA_FIGHT, ARENA_ROUND_CLEAR, ARENA_WON, ARENA_LOST };
enum { ARENA_SEEK, ARENA_WARN, ARENA_CHARGE, ARENA_RECOVER };

struct TrioArenaShot
{
    s16 x, y, vx, vy; // 1/16 pixel units
    u8 life, damage, friendly, frost;
};

struct TrioArenaState
{
    s16 x, y, ex, ey, aimX, aimY, chargeX, chargeY;
    s16 targetX, targetY;
    u16 primaryCd, secondaryCd, dodgeCd, invincible, slow, enemyTimer, frames;
    u8 girl, round, hp, enemyHp, enemyMaxHp, status, enemyMode, pattern, turns;
    u8 dash, rush, rushHit, hitFlash, enemyFlash;
    struct TrioArenaShot shots[TRIO_ARENA_SHOTS];
};

void TrioArena_Init(struct TrioArenaState *arena, u8 girl);
void TrioArena_NextRound(struct TrioArenaState *arena);
void TrioArena_Step(struct TrioArenaState *arena, u16 input);
void StartTrioActionArena(void);

#endif
