#include "global.h"
#include "data.h"
const u32 sGangLayout[] = {sizeof(struct Trainer), offsetof(struct Trainer,party), offsetof(struct Trainer,partySize), sizeof(struct TrainerMon), offsetof(struct TrainerMon,ev), offsetof(struct TrainerMon,iv), offsetof(struct TrainerMon,species), offsetof(struct TrainerMon,lvl), offsetof(struct TrainerMon,heldItem)};
