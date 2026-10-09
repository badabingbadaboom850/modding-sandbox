#ifndef GUARD_TRIO_CAMP_H
#define GUARD_TRIO_CAMP_H

void TrioCamp_EnsureStatsInitialized(void);
void TrioCamp_RecordMedicineUse(u16 item);
void TrioCamp_RecordEvolution(u16 before, u16 after, u16 item);
void TrioCamp_RecordVisit(void);
void TrioCamp_RecordGame(void);
void TrioCamp_RecordPet(void);
bool32 TrioCamp_UseFavorite(void);
void TrioCamp_BufferStats(void);

#endif
