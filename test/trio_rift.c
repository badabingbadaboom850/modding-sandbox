#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/vars.h"

TEST("Rift guardian scales and heals without changing Riko or saved progress")
{
    u32 hp = 0;
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_RIKO_WING, 30, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_FIDOUGH, 40, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_HP, &hp);
    VarSet(VAR_TRIO_RIFT_RIKO_STATE, 3);
    gSpecialVar_0x8004 = SPECIES_RIKO_SPIRIT;
    EXPECT(PrepareTrioSpiritTrial());
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_SPECIES), SPECIES_RIKO_SPIRIT);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 49);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE1), MOVE_FLAMETHROWER);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE2), MOVE_SNARL);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_RIKO_WING);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP), GetMonData(&gPlayerParty[0], MON_DATA_MAX_HP));
    EXPECT_EQ(VarGet(VAR_TRIO_RIFT_RIKO_STATE), 3);
}

TEST("Rift guardian rejects empty party and caps existing high level saves")
{
    ZeroPlayerPartyMons();
    gSpecialVar_0x8004 = SPECIES_RIKO_SPIRIT;
    EXPECT(!PrepareTrioSpiritTrial());
    CreateMon(&gPlayerParty[0], SPECIES_RIKO, 100, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(PrepareTrioSpiritTrial());
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_RIKO);
}
