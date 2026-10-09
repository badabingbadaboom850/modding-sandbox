#ifndef GUARD_TRIO_SNACK_CHASE_H
#define GUARD_TRIO_SNACK_CHASE_H

void TrioSnack_BeginTheft(void);
void TrioSnack_BufferItem(void);
void TrioSnack_ReturnItem(void);
void TrioSnack_UpdateObjects(void);
bool32 TrioSnack_IsFriendlyBattle(u8 mapGroup, u8 mapNum, u16 trainer);

#endif
