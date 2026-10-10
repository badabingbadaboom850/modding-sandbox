#include "global.h"
#include "pokemon.h"
#include "item.h"
#include "move_relearner.h"
#include "test/test.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/pokemon.h"

TEST("Toxic Mouse toggles Bijuu and rejects unrelated or other elemental forms")
{
    struct Pokemon mon;
    static const u16 from[] = {SPECIES_BIJUU, SPECIES_BIJUU_BOX, SPECIES_BIJUU_POISON, SPECIES_BIJUU_ICE, SPECIES_BIJUU_GHOST, SPECIES_FIDOUGH, SPECIES_RIKO};
    static const u16 to[] = {SPECIES_BIJUU_POISON, SPECIES_BIJUU_POISON, SPECIES_BIJUU, SPECIES_NONE, SPECIES_NONE, SPECIES_NONE, SPECIES_NONE};
    for (u32 i = 0; i < ARRAY_COUNT(from); i++)
    {
        CreateMon(&mon, from[i], 20, 0, OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, ITEM_TOXIC_MOUSE, NULL, NULL, CHECK_EVO), to[i]);
        EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), from[i]);
    }
    EXPECT_EQ(gSpeciesInfo[SPECIES_BIJUU_POISON].types[0], TYPE_POISON);
    EXPECT_EQ(gSpeciesInfo[SPECIES_BIJUU_POISON].genderRatio, MON_FEMALE);
    EXPECT_EQ(GetItemPrice(ITEM_TOXIC_MOUSE), 500);
}

TEST("Poison Bijuu lessons respect level and already equipped moves")
{
    struct Pokemon mon;
    u16 moves[MAX_RELEARNER_MOVES];
    CreateMon(&mon, SPECIES_BIJUU_POISON, 5, 0, OTID_STRUCT_PLAYER_ID);
    for (u32 i = 0; i < MAX_MON_MOVES; i++) SetMonMoveSlot(&mon, MOVE_NONE, i);
    EXPECT_EQ(GetTrioElementalMoves(&mon.box, moves), 1);
    EXPECT_EQ(moves[0], MOVE_POISON_FANG);
    SetMonMoveSlot(&mon, MOVE_POISON_FANG, 0);
    EXPECT_EQ(GetTrioElementalMoves(&mon.box, moves), 0);
    CreateMon(&mon, SPECIES_BIJUU_POISON, 32, 0, OTID_STRUCT_PLAYER_ID);
    for (u32 i = 0; i < MAX_MON_MOVES; i++) SetMonMoveSlot(&mon, MOVE_NONE, i);
    u32 count = GetTrioElementalMoves(&mon.box, moves);
    EXPECT_EQ(count, 5);
    bool32 sludge = FALSE;
    for (u32 i = 0; i < count; i++) if (moves[i] == MOVE_SLUDGE_BOMB) sludge = TRUE;
    EXPECT(sludge);
}
