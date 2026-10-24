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
#define TRIO_ARENA_CHALLENGES 8
#define TRIO_ARENA_PRACTICE 255

enum { ARENA_RIKO, ARENA_BIJUU, ARENA_PENNY, ARENA_GIRLS };
enum { ARENA_FIGHT, ARENA_ROUND_CLEAR, ARENA_WON, ARENA_LOST };
enum { ARENA_SEEK, ARENA_WARN, ARENA_CHARGE, ARENA_RECOVER };
enum { ARENA_RESULT_CANCEL, ARENA_RESULT_LOST, ARENA_RESULT_WON, ARENA_RESULT_ERROR };
enum { ARENA_CHALLENGE_LOCKED, ARENA_CHALLENGE_READY, ARENA_CHALLENGE_PENDING, ARENA_CHALLENGE_CLAIMED, ARENA_CHALLENGE_INVALID };

struct TrioArenaChallenge
{
    u16 map, species;
    u8 localId, badges, champion, patterns[3];
    const u8 *title;
};
extern const struct TrioArenaChallenge gTrioArenaChallenges[TRIO_ARENA_CHALLENGES];

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
    u8 challenge, rounds; // zero challenge = original free practice; otherwise id+1
    struct TrioArenaShot shots[TRIO_ARENA_SHOTS];
};

void TrioArena_Init(struct TrioArenaState *arena, u8 girl);
void TrioArena_NextRound(struct TrioArenaState *arena);
void TrioArena_Step(struct TrioArenaState *arena, u16 input);
void StartTrioActionArena(void);
bool32 TrioArena_InitChallenge(struct TrioArenaState *arena, u8 girl, u8 challenge);
u8 TrioArena_CurrentChallenge(void);
bool32 TrioArena_CanStartChallenge(u8 challenge);
u16 GetTrioArenaChallengeState(void);
void RecordTrioArenaChallengeWin(void);
u16 ClaimTrioArenaChallengeReward(void);
void StartTrioActionChallenge(void);

#endif
