#ifndef GUARD_TRIO_RUNOFF_H
#define GUARD_TRIO_RUNOFF_H

#include "pokemon.h"

// User-authorized testing rate. Change to 5 after the rendered test is approved.
#define TRIO_RUNOFF_CHANCE 100
void TrioRunoff_Begin(u32 chance);
void TrioRunoff_BeginBattle(void);
void TrioRunoff_Clear(void);
bool32 TrioRunoff_IsAway(struct Pokemon *mon);
u32 TrioRunoff_TakeDepartureString(void);
bool32 TrioRunoff_DepartureAnnounced(void);
#if TESTING
void TrioRunoff_EnableBattleTest(void);
#endif

#endif
