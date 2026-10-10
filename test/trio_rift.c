#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/vars.h"

TEST("Rift guardian stays ten levels ahead and heals without changing Riko or saved progress")
{
    u32 hp = 0;
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_RIKO_WING, 30, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_FIDOUGH, 40, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_HP, &hp);
    VarSet(VAR_TRIO_RIFT_RIKO_STATE, 3);
    gSpecialVar_0x8004 = SPECIES_RIKO_ECHO;
    EXPECT(PrepareTrioSpiritTrial());
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_SPECIES), SPECIES_RIKO_ECHO);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 50);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE1), MOVE_MOONBLAST);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_MOVE2), MOVE_ECHOED_VOICE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_RIKO_WING);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP), GetMonData(&gPlayerParty[0], MON_DATA_MAX_HP));
    EXPECT_EQ(VarGet(VAR_TRIO_RIFT_RIKO_STATE), 3);
}

TEST("Rift guardian rejects empty party and caps at level 100 on high level saves")
{
    ZeroPlayerPartyMons();
    gSpecialVar_0x8004 = SPECIES_RIKO_ECHO;
    EXPECT(!PrepareTrioSpiritTrial());
    CreateMon(&gPlayerParty[0], SPECIES_RIKO, 100, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(PrepareTrioSpiritTrial());
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_RIKO);
}
