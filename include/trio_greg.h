#ifndef GUARD_TRIO_GREG_H
#define GUARD_TRIO_GREG_H
bool32 TrioGreg_IsTrainer(u16 trainerId);
bool32 TrioGreg_HasWon(u16 trainerId);
void TrioGreg_SetWon(u16 trainerId, bool32 won);
#endif
