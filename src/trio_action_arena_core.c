#include "global.h"
#include "trio_action_arena.h"

static s16 Abs(s16 v) { return v < 0 ? -v : v; }
static s16 Clamp(s16 v, s16 low, s16 high) { return v < low ? low : v > high ? high : v; }
static bool32 Near(s16 x, s16 y, s16 xx, s16 yy, u16 radius)
{
    s32 dx = (x - xx) / 16, dy = (y - yy) / 16;
    return dx * dx + dy * dy <= radius * radius;
}

// Integer normalization avoids floating point and keeps diagonal speed bounded.
static void Velocity(s16 dx, s16 dy, s16 speed, s16 *vx, s16 *vy)
{
    s16 major = max(Abs(dx), Abs(dy));
    s16 minor = min(Abs(dx), Abs(dy));
    s16 length = major + minor * 3 / 8;
    *vx = length ? (s32)dx * speed / length : speed;
    *vy = length ? (s32)dy * speed / length : 0;
}

static void HurtPlayer(struct TrioArenaState *a, u8 damage)
{
    if (a->invincible || a->status != ARENA_FIGHT) return;
    a->hp = a->hp > damage ? a->hp - damage : 0;
    a->invincible = 48;
    a->hitFlash = 12;
    if (!a->hp) a->status = ARENA_LOST;
}

static void HurtEnemy(struct TrioArenaState *a, u8 damage, bool32 frost)
{
    if (a->status != ARENA_FIGHT) return;
    a->enemyHp = a->enemyHp > damage ? a->enemyHp - damage : 0;
    a->enemyFlash = 8;
    if (frost) a->slow = 120;
    if (!a->enemyHp)
    {
        a->status = a->round + 1 >= a->rounds ? ARENA_WON : ARENA_ROUND_CLEAR;
        memset(a->shots, 0, sizeof(a->shots));
    }
}

static bool32 Shoot(struct TrioArenaState *a, bool32 friendly, s16 dx, s16 dy, u8 damage, u8 life, bool32 frost)
{
    // Separate pools guarantee that enemy volleys cannot consume player slots.
    for (u32 i = friendly ? 0 : 4; i < (friendly ? 4 : TRIO_ARENA_SHOTS); i++)
    {
        struct TrioArenaShot *s = &a->shots[i];
        if (s->life) continue;
        s->x = friendly ? a->x : a->ex;
        s->y = friendly ? a->y : a->ey;
        Velocity(dx, dy, friendly ? 52 : a->challenge ? 38 + a->challenge * 2 : 32, &s->vx, &s->vy);
        s->life = life;
        s->damage = damage;
        s->friendly = friendly;
        s->frost = frost;
        return TRUE;
    }
    return FALSE;
}

static void ResetRound(struct TrioArenaState *a)
{
    a->x = 56 * 16; a->y = 80 * 16;
    a->ex = 184 * 16; a->ey = 80 * 16;
    a->aimX = 16; a->aimY = 0;
    a->enemyMaxHp = a->challenge ? 138 + a->challenge * 13 : 90 + a->round * 35;
    a->enemyHp = a->enemyMaxHp;
    a->enemyMode = ARENA_SEEK; a->enemyTimer = a->challenge ? 65 : 90;
    a->turns = 0; a->pattern = 0; a->status = ARENA_FIGHT;
    a->primaryCd = a->secondaryCd = a->dodgeCd = 0;
    a->invincible = 60; a->slow = a->dash = a->rush = a->rushHit = 0;
    a->hitFlash = a->enemyFlash = 0;
    memset(a->shots, 0, sizeof(a->shots));
}

void TrioArena_Init(struct TrioArenaState *a, u8 girl)
{
    memset(a, 0, sizeof(*a));
    a->girl = girl < ARENA_GIRLS ? girl : ARENA_RIKO;
    a->hp = 100;
    a->rounds = 3;
    ResetRound(a);
}

bool32 TrioArena_InitChallenge(struct TrioArenaState *a, u8 girl, u8 id)
{
    if (id >= TRIO_ARENA_CHALLENGES || girl >= ARENA_GIRLS) return FALSE;
    TrioArena_Init(a, girl);
    a->challenge = id + 1;
    a->rounds = 1;
    ResetRound(a);
    return TRUE;
}

void TrioArena_NextRound(struct TrioArenaState *a)
{
    if (a->status != ARENA_ROUND_CLEAR || a->round + 1 >= a->rounds) return;
    a->round++;
    a->hp = min(100, a->hp + 25);
    ResetRound(a);
}

static void Player(struct TrioArenaState *a, u16 input)
{
    s16 dx = !!(input & TRIO_ARENA_MOVE_RIGHT) - !!(input & TRIO_ARENA_MOVE_LEFT);
    s16 dy = !!(input & TRIO_ARENA_MOVE_DOWN) - !!(input & TRIO_ARENA_MOVE_UP);
    s16 vx = 0, vy = 0;
    if (dx || dy)
    {
        Velocity(dx, dy, 24, &vx, &vy);
        if (!(input & TRIO_ARENA_LOCK)) { a->aimX = dx * 16; a->aimY = dy * 16; }
    }
    if (input & TRIO_ARENA_LOCK)
        Velocity(a->ex - a->x, a->ey - a->y, 16, &a->aimX, &a->aimY);
    if ((input & TRIO_ARENA_DODGE) && !a->dodgeCd && !a->rush)
    {
        a->dash = 9; a->dodgeCd = 50; a->invincible = max(a->invincible, 14);
        Velocity((dx || dy) ? dx : a->aimX, (dx || dy) ? dy : a->aimY, 70, &a->chargeX, &a->chargeY);
    }
    if ((input & TRIO_ARENA_PRIMARY) && !a->primaryCd)
    {
        if (Shoot(a, TRUE, a->aimX, a->aimY, a->girl == ARENA_PENNY ? 17 : 11,
                  a->girl == ARENA_PENNY ? 8 : a->girl == ARENA_RIKO ? 23 : 42, FALSE))
            a->primaryCd = a->girl == ARENA_PENNY ? 24 : 20;
    }
    if ((input & TRIO_ARENA_SECONDARY) && !a->secondaryCd && !a->rush && !a->dash)
    {
        if (a->girl == ARENA_RIKO)
        {
            if (Near(a->x, a->y, a->ex, a->ey, 46)) HurtEnemy(a, 32, FALSE);
            // A visible expanding bark, whether or not the opponent is in range.
            a->rush = 12; a->rushHit = 1;
            a->secondaryCd = 150;
        }
        else if (a->girl == ARENA_BIJUU)
        {
            s16 ax = a->aimX, ay = a->aimY;
            bool32 fired = Shoot(a, TRUE, ax, ay, 18, 42, TRUE);
            if (fired)
            {
                Shoot(a, TRUE, ax * 2 - ay, ay * 2 + ax, 14, 35, TRUE);
                Shoot(a, TRUE, ax * 2 + ay, ay * 2 - ax, 14, 35, TRUE);
                a->secondaryCd = 130;
            }
        }
        else
        {
            a->rush = 14; a->rushHit = 0;
            a->invincible = max(a->invincible, 18);
            Velocity(a->aimX, a->aimY, 64, &a->chargeX, &a->chargeY);
            a->secondaryCd = 140;
        }
    }
    if (a->dash || (a->rush && a->girl == ARENA_PENNY))
    {
        vx = a->chargeX; vy = a->chargeY;
        if (a->dash) a->dash--;
    }
    a->x = Clamp(a->x + vx, TRIO_ARENA_LEFT * 16, TRIO_ARENA_RIGHT * 16);
    a->y = Clamp(a->y + vy, TRIO_ARENA_TOP * 16, TRIO_ARENA_BOTTOM * 16);
    if (a->rush)
    {
        if (a->girl == ARENA_PENNY && !a->rushHit && Near(a->x, a->y, a->ex, a->ey, 22))
        {
            a->rushHit = 1;
            HurtEnemy(a, 36, FALSE);
        }
        a->rush--;
    }
}

static void Enemy(struct TrioArenaState *a)
{
    s16 vx, vy;
    if (a->enemyTimer) a->enemyTimer--;
    switch (a->enemyMode)
    {
    case ARENA_SEEK:
        Velocity(a->x - a->ex, a->y - a->ey, a->slow ? 5 : a->challenge ? 13 + a->challenge : 10 + a->round * 2, &vx, &vy);
        if (!Near(a->x, a->y, a->ex, a->ey, a->challenge ? 17 : 36)) { a->ex += vx; a->ey += vy; }
        if (a->challenge && Near(a->x, a->y, a->ex, a->ey, 18)) HurtPlayer(a, 16 + a->challenge);
        if (!a->enemyTimer)
        {
            a->enemyMode = ARENA_WARN;
            a->pattern = a->challenge ? gTrioArenaChallenges[a->challenge - 1].patterns[a->turns++ % 3] : a->turns++ % (a->round + 1);
            a->enemyTimer = a->challenge ? (a->pattern == 2 ? 54 : 46) - a->challenge : a->pattern == 2 ? 60 : 45;
            a->targetX = a->x; a->targetY = a->y;
        }
        break;
    case ARENA_WARN:
        if (!a->enemyTimer)
        {
            if (a->pattern == 0)
            {
                Velocity(a->targetX - a->ex, a->targetY - a->ey, a->challenge ? 62 + a->challenge * 2 : 62, &a->targetX, &a->targetY);
                a->enemyMode = ARENA_CHARGE; a->enemyTimer = 24;
            }
            else
            {
                if (a->pattern == 1)
                {
                    s16 dx = a->targetX - a->ex, dy = a->targetY - a->ey;
                    u8 damage = a->challenge ? 24 + a->challenge * 2 : 12;
                    Shoot(a, FALSE, dx, dy, damage, 90, FALSE);
                    Shoot(a, FALSE, dx * 2 - dy, dy * 2 + dx, damage, 90, FALSE);
                    Shoot(a, FALSE, dx * 2 + dy, dy * 2 - dx, damage, 90, FALSE);
                    if (a->challenge >= 3)
                    {
                        Shoot(a, FALSE, dx - dy, dy + dx, damage, 80, FALSE);
                        Shoot(a, FALSE, dx + dy, dy - dx, damage, 80, FALSE);
                    }
                }
                else if (Near(a->x, a->y, a->ex, a->ey, 42)) HurtPlayer(a, a->challenge ? 26 + a->challenge : 22);
                a->enemyMode = ARENA_RECOVER; a->enemyTimer = a->challenge ? 44 - a->challenge * 2 : 60;
            }
        }
        break;
    case ARENA_CHARGE:
        a->ex += a->targetX; a->ey += a->targetY;
        if (Near(a->x, a->y, a->ex, a->ey, 20)) HurtPlayer(a, a->challenge ? 24 + a->challenge : 18);
        if (!a->enemyTimer) { a->enemyMode = ARENA_RECOVER; a->enemyTimer = a->challenge ? 44 - a->challenge * 2 : 65; }
        break;
    case ARENA_RECOVER:
        if (!a->enemyTimer) { a->enemyMode = ARENA_SEEK; a->enemyTimer = a->challenge ? 46 - a->challenge * 2 : 60; }
        break;
    }
    a->ex = Clamp(a->ex, TRIO_ARENA_LEFT * 16, TRIO_ARENA_RIGHT * 16);
    a->ey = Clamp(a->ey, TRIO_ARENA_TOP * 16, TRIO_ARENA_BOTTOM * 16);
}

void TrioArena_Step(struct TrioArenaState *a, u16 input)
{
    if (a->status != ARENA_FIGHT) return;
    a->frames++;
    if (a->primaryCd) a->primaryCd--;
    if (a->secondaryCd) a->secondaryCd--;
    if (a->dodgeCd) a->dodgeCd--;
    if (a->invincible) a->invincible--;
    if (a->slow) a->slow--;
    if (a->hitFlash) a->hitFlash--;
    if (a->enemyFlash) a->enemyFlash--;
    Player(a, input);
    if (a->status != ARENA_FIGHT) return;
    Enemy(a);
    if (a->status != ARENA_FIGHT) return;
    for (u32 i = 0; i < TRIO_ARENA_SHOTS; i++)
    {
        struct TrioArenaShot *s = &a->shots[i];
        if (!s->life) continue;
        s->life--; s->x += s->vx; s->y += s->vy;
        if (s->x < 8 * 16 || s->x > 232 * 16 || s->y < 28 * 16 || s->y > 128 * 16)
            s->life = 0;
        else if (s->friendly && Near(s->x, s->y, a->ex, a->ey, 14))
        {
            HurtEnemy(a, s->damage, s->frost); s->life = 0;
        }
        else if (!s->friendly && Near(s->x, s->y, a->x, a->y, 10))
        {
            HurtPlayer(a, s->damage); s->life = 0;
        }
        if (a->status != ARENA_FIGHT) break;
    }
}
