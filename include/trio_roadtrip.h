#ifndef GUARD_TRIO_ROADTRIP_H
#define GUARD_TRIO_ROADTRIP_H
bool32 TrioRoad_IsTrainer(u16 trainerId);
bool32 TrioRoad_IsFriendlyBattle(u8 mapGroup, u8 mapNum, u16 trainerId);
bool32 TrioRoad_HasWon(u16 trainerId);
void TrioRoad_RecordBattleWin(void);
void TrioRoad_RecordDeparture(void);
#endif
