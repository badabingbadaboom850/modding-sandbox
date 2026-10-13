#ifndef GUARD_TRIO_SNACK_CHASE_H
#define GUARD_TRIO_SNACK_CHASE_H

void TrioSnack_BeginTheft(void);
void TrioSnack_BufferItem(void);
void TrioSnack_ReturnItem(void);
void TrioSnack_UpdateObjects(void);
void TrioGang_PrepareAmbush(void);
void TrioGang_BeginAmbush(void);
void TrioGang_RecordVictory(void);
u16 TrioGang_WaveForTrainer(u16 trainer);

#endif
