#include "global.h"
#include "data.h"
// Built with exactly the engine's ARM ABI. Bitfield byte precedes partySize.
const u32 sRoadLayout[] = {sizeof(struct Trainer), offsetof(struct Trainer, party), offsetof(struct Trainer, partySize), sizeof(struct TrainerMon), offsetof(struct TrainerMon, species), offsetof(struct TrainerMon, lvl), offsetof(struct TrainerMon, moves), sizeof(enum Move)};
