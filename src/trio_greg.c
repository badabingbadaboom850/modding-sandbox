#include "global.h"
#include "event_data.h"
#include "trio_greg.h"
#include "constants/opponents.h"
#include "constants/vars.h"

// Slots1080-1091 overlap unrelated replay/story flags. Never read/write those
// flags for Greg: older saves may already have any combination of them set.
static u16 GregBit(u16 trainerId)
{
    if (trainerId < TRAINER_GREG_GOLDENROD_CITY || trainerId > TRAINER_GREG_SAFFRON_CITY)
        return 0;
    return 1u << (trainerId - TRAINER_GREG_GOLDENROD_CITY);
}

bool32 TrioGreg_IsTrainer(u16 trainerId)
{
    return GregBit(trainerId) != 0;
}

bool32 TrioGreg_HasWon(u16 trainerId)
{
    u16 bit = GregBit(trainerId);
    return bit != 0 && (VarGet(VAR_TRIO_GREG_WINS) & bit) != 0;
}

void TrioGreg_SetWon(u16 trainerId, bool32 won)
{
    u16 bit = GregBit(trainerId);
    if (bit != 0)
    {
        u16 wins = VarGet(VAR_TRIO_GREG_WINS);
        VarSet(VAR_TRIO_GREG_WINS, won ? wins | bit : wins & ~bit);
    }
}
