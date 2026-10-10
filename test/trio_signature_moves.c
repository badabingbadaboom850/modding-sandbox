#include "global.h"
#include "test/battle.h"
#include "pokemon.h"
#include "move_relearner.h"

TEST("Family signatures preserve saved structures and historical move boundaries")
{
    EXPECT_EQ(sizeof(struct SaveBlock1), 15444);
    EXPECT_EQ(sizeof(struct SaveBlock2), 2864);
    EXPECT_EQ(sizeof(struct SaveBlock3), 100);
    EXPECT_EQ(MOVE_FLOOF_FURY, 849);
    EXPECT_EQ(MOVE_MEGA_RIKO, 850);
    EXPECT_EQ(FIRST_Z_MOVE, 851);
    EXPECT_EQ(MOVE_BLANKEY_TIME, MOVES_COUNT_DYNAMAX);
    EXPECT(MOVES_COUNT_ALL < 2048);
}

TEST("Family signatures reject unrelated species Eggs and boss Spirits")
{
    u32 move, species;
    static const u16 others[] = { SPECIES_NONE, SPECIES_EGG, SPECIES_PIKACHU, SPECIES_WOBBUFFET,
        SPECIES_RIKO_SPIRIT, SPECIES_PENNY_SPIRIT, SPECIES_BIJUU_SPIRIT };
    for (move = MOVE_BLANKEY_TIME; move <= MOVE_DRAMA_QUEEN; move++)
        for (species = 0; species < ARRAY_COUNT(others); species++)
            EXPECT_EQ(CanLearnTeachableMove(others[species], move), FALSE);
}

TEST("Family signatures survive encrypted Pokemon storage without touching adjacent moves")
{
    struct Pokemon mon, restored;
    u32 move = MOVE_NONE;
    for (move = MOVE_BLANKEY_TIME; move <= MOVE_DRAMA_QUEEN; move++)
    {
        CreateMon(&mon, SPECIES_RIKO, 50, 0, OTID_STRUCT_PLAYER_ID);
        SetMonMoveSlot(&mon, MOVE_TACKLE, 0);
        SetMonMoveSlot(&mon, move, 1);
        SetMonMoveSlot(&mon, MOVE_FLOOF_FURY, 2);
        SetMonMoveSlot(&mon, MOVE_MEGA_RIKO, 3);
        memcpy(&restored, &mon, sizeof(mon));
        EXPECT_EQ(GetMonData(&restored, MON_DATA_MOVE1), MOVE_TACKLE);
        EXPECT_EQ(GetMonData(&restored, MON_DATA_MOVE2), move);
        EXPECT_EQ(GetMonData(&restored, MON_DATA_MOVE3), MOVE_FLOOF_FURY);
        EXPECT_EQ(GetMonData(&restored, MON_DATA_MOVE4), MOVE_MEGA_RIKO);
        EXPECT_EQ(GetMonData(&restored, MON_DATA_SANITY_IS_BAD_EGG), FALSE);
    }
}

SINGLE_BATTLE_TEST("Family signature moves execute every registered effect without stalling")
{
    u32 move = MOVE_NONE;
    for (u32 j = MOVE_BLANKEY_TIME; j <= MOVE_DRAMA_QUEEN; j++)
        PARAMETRIZE { move = j; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(100); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); if (move == MOVE_MIDNIGHT_ZOOM) SEND_OUT(player, 1); }
    }
}

SINGLE_BATTLE_TEST("Family Safe With You cures status and raises only Special Defense including at cap")
{
    u32 stage, status;
    PARAMETRIZE { stage = DEFAULT_STAT_STAGE; status = STATUS1_BURN; }
    PARAMETRIZE { stage = DEFAULT_STAT_STAGE; status = STATUS1_POISON; }
    PARAMETRIZE { stage = DEFAULT_STAT_STAGE; status = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { stage = DEFAULT_STAT_STAGE; status = STATUS1_NONE; }
    PARAMETRIZE { stage = MAX_STAT_STAGE; status = STATUS1_BURN; }
    PARAMETRIZE { stage = MAX_STAT_STAGE; status = STATUS1_NONE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Status1(status); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        if (stage == MAX_STAT_STAGE) {
            TURN { MOVE(player, MOVE_AMNESIA); }
            TURN { MOVE(player, MOVE_AMNESIA); }
            TURN { MOVE(player, MOVE_AMNESIA); }
        }
        TURN { MOVE(player, MOVE_SAFE_WITH_YOU); }
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE);
        EXPECT_EQ(player->statStages[STAT_SPDEF], stage == MAX_STAT_STAGE ? MAX_STAT_STAGE : stage + 1);
    }
}

SINGLE_BATTLE_TEST("Family Safe With You respects Contrary and Simple")
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_CONTRARY; }
    PARAMETRIZE { ability = ABILITY_SIMPLE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); Status1(STATUS1_BURN); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SAFE_WITH_YOU); }
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + (ability == ABILITY_CONTRARY ? -1 : 2));
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Family Cocoa Pounce lowers Attack and Drama Queen lowers the user's Special Attack")
{
    u32 move = MOVE_NONE;
    PARAMETRIZE { move = MOVE_COCOA_POUNCE; }
    PARAMETRIZE { move = MOVE_DRAMA_QUEEN; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } THEN {
        if (move == MOVE_COCOA_POUNCE)
            EXPECT_EQ(opponent->statStages[STAT_ATK], DEFAULT_STAT_STAGE - 1);
        else
            EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE - 2);
    }
}

SINGLE_BATTLE_TEST("Family Tiny Nibbles restores half damage rather than Draining Kiss's three quarters")
{
    s16 damage, healed;
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TINY_NIBBLES); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &damage);
        HP_BAR(player, captureDamage: &healed);
    } THEN {
        EXPECT_MUL_EQ(damage, Q_4_12(-0.5), healed);
    }
}

SINGLE_BATTLE_TEST("Family Penny Patience Main Character and Cocoa Chaos raise their own intended stats")
{
    u32 move = MOVE_NONE;
    PARAMETRIZE { move = MOVE_PENNY_PATIENCE; }
    PARAMETRIZE { move = MOVE_MAIN_CHARACTER; }
    PARAMETRIZE { move = MOVE_COCOA_CHAOS; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } THEN {
        if (move == MOVE_PENNY_PATIENCE) {
            EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE + 1);
            EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 1);
        } else if (move == MOVE_MAIN_CHARACTER) {
            EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 1);
            EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 1);
        } else {
            EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
            EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
        }
    }
}

TEST("Family signatures teach only their girl across all registered personal forms and Megas")
{
    u32 move, species;
    static const u16 penny[] = { SPECIES_FIDOUGH, SPECIES_DACHSBUN, SPECIES_PENNY_GUARDIAN, SPECIES_PENNY_WATER, SPECIES_PENNY_GRASS, SPECIES_PENNY_BRAVE, SPECIES_MEGA_PENNY_SPIRIT };
    for (species = 0; species < ARRAY_COUNT(penny); species++)
        for (move = MOVE_BLANKEY_TIME; move <= MOVE_DRAMA_QUEEN; move++)
            EXPECT_EQ(CanLearnTeachableMove(penny[species], move), move >= MOVE_BLANKEY_TIME && move <= MOVE_SAFE_WITH_YOU);
    static const u16 bijuu[] = { SPECIES_BIJUU, SPECIES_MEGA_BIJUU, SPECIES_MEGA_BIJUU_SPIRIT, SPECIES_BIJUU_FIGHTING, SPECIES_BIJUU_POISON, SPECIES_BIJUU_GROUND, SPECIES_BIJUU_ROCK, SPECIES_BIJUU_BUG, SPECIES_BIJUU_GHOST, SPECIES_BIJUU_DARK, SPECIES_BIJUU_STEEL, SPECIES_BIJUU_PSYCHIC, SPECIES_BIJUU_ICE, SPECIES_BIJUU_EMBER };
    for (species = 0; species < ARRAY_COUNT(bijuu); species++)
        for (move = MOVE_BLANKEY_TIME; move <= MOVE_DRAMA_QUEEN; move++)
            EXPECT_EQ(CanLearnTeachableMove(bijuu[species], move), move >= MOVE_COCOA_POUNCE && move <= MOVE_ABSOLUTELY_FERAL);
    static const u16 riko[] = { SPECIES_RIKO, SPECIES_MEGA_RIKO, SPECIES_MEGA_RIKO_SPIRIT, SPECIES_RIKO_FLOWER, SPECIES_RIKO_ECHO, SPECIES_RIKO_WING, SPECIES_RIKO_FIRE, SPECIES_RIKO_WATER, SPECIES_RIKO_GRASS, SPECIES_RIKO_ELECTRIC, SPECIES_RIKO_ICE, SPECIES_RIKO_PSYCHIC, SPECIES_RIKO_FLYING, SPECIES_RIKO_DRAGON };
    for (species = 0; species < ARRAY_COUNT(riko); species++)
        for (move = MOVE_BLANKEY_TIME; move <= MOVE_DRAMA_QUEEN; move++)
            EXPECT_EQ(CanLearnTeachableMove(riko[species], move), move >= MOVE_POM_TANTRUM && move <= MOVE_DRAMA_QUEEN);
}

TEST("Family appended signatures are ordinary moves while saved Z and Max IDs remain special")
{
    u32 move;
    for (move = MOVE_BLANKEY_TIME; move <= MOVE_DRAMA_QUEEN; move++)
        EXPECT(IS_STANDARD_MOVE(move));
    for (move = FIRST_Z_MOVE; move <= LAST_Z_MOVE; move++)
        EXPECT(!IS_STANDARD_MOVE(move));
    for (move = FIRST_MAX_MOVE; move <= LAST_MAX_MOVE; move++)
        EXPECT(!IS_STANDARD_MOVE(move));
    EXPECT(!IS_STANDARD_MOVE(MOVE_UNAVAILABLE));
}

SINGLE_BATTLE_TEST("Family signatures print their personalized battle names")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_COCOA_POUNCE); }
    } SCENE {
        MESSAGE("Wobbuffet used Cocoa Pounce!");
        HP_BAR(opponent);
    }
}


TEST("Elemental lessons follow current form actual level and known attacks")
{
    struct Pokemon mon;
    u16 moves[MAX_RELEARNER_MOVES];
    u32 count, j;
    bool32 found;
    CreateMon(&mon, SPECIES_RIKO_ELECTRIC, 5, 0, OTID_STRUCT_PLAYER_ID);
    for (j = 0; j < MAX_MON_MOVES; j++)
        SetMonMoveSlot(&mon, MOVE_NONE, j);
    count = GetTrioElementalMoves(&mon.box, moves);
    EXPECT_EQ(count, 1); // Level-zero and level-three Thunder Shock deduplicate.
    EXPECT_EQ(moves[0], MOVE_THUNDER_SHOCK);
    SetMonMoveSlot(&mon, MOVE_THUNDER_SHOCK, 0);
    EXPECT_EQ(GetTrioElementalMoves(&mon.box, moves), 0);

    CreateMon(&mon, SPECIES_RIKO_ELECTRIC, 40, 0, OTID_STRUCT_PLAYER_ID);
    for (j = 0; j < MAX_MON_MOVES; j++)
        SetMonMoveSlot(&mon, MOVE_NONE, j);
    count = GetTrioElementalMoves(&mon.box, moves);
    found = FALSE;
    for (j = 0; j < count; j++)
    {
        if (moves[j] == MOVE_DISCHARGE) found = TRUE;
        EXPECT_NE(moves[j], MOVE_WILD_CHARGE); // Level 44 remains locked.
        EXPECT_NE(moves[j], MOVE_CHARGE); // Status moves are not elemental attacks.
        EXPECT_NE(moves[j], MOVE_QUICK_ATTACK);
    }
    EXPECT(found);
    u16 species = SPECIES_RIKO_FIRE;
    SetMonData(&mon, MON_DATA_SPECIES, &species);
    count = GetTrioElementalMoves(&mon.box, moves);
    found = FALSE;
    for (j = 0; j < count; j++)
    {
        if (moves[j] == MOVE_FLAMETHROWER) found = TRUE;
        EXPECT_NE(moves[j], MOVE_THUNDER_SHOCK);
        EXPECT_NE(moves[j], MOVE_DISCHARGE);
    }
    EXPECT(found);
    // Equipped moves survive a form change, but cannot be re-taught in this form.
    SetMonMoveSlot(&mon, MOVE_THUNDER_SHOCK, 0);
    species = SPECIES_RIKO;
    SetMonData(&mon, MON_DATA_SPECIES, &species);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MOVE1), MOVE_THUNDER_SHOCK);
}

TEST("Elemental lessons include transformation attacks and reject other Pokemon")
{
    struct Pokemon mon;
    u16 moves[MAX_RELEARNER_MOVES];
    static const u16 species[] = {SPECIES_PENNY_WATER, SPECIES_PENNY_GRASS, SPECIES_BIJUU_ICE, SPECIES_BIJUU_GHOST, SPECIES_BIJUU_POISON};
    static const u16 attack[] = {MOVE_WATER_PULSE, MOVE_RAZOR_LEAF, MOVE_ICY_WIND, MOVE_HEX, MOVE_POISON_FANG};
    for (u32 j = 0; j < ARRAY_COUNT(species); j++)
    {
        CreateMon(&mon, species[j], 5, 0, OTID_STRUCT_PLAYER_ID);
        for (u32 k = 0; k < MAX_MON_MOVES; k++) SetMonMoveSlot(&mon, MOVE_NONE, k);
        EXPECT_EQ(GetTrioElementalMoves(&mon.box, moves), 1);
        EXPECT_EQ(moves[0], attack[j]);
    }
    static const u16 excluded[] = {SPECIES_PIKACHU, SPECIES_EGG, SPECIES_RIKO_SPIRIT, SPECIES_BIJUU_SPIRIT, SPECIES_PENNY_SPIRIT};
    for (u32 j = 0; j < ARRAY_COUNT(excluded); j++)
    {
        CreateMon(&mon, SPECIES_PIKACHU, 50, 0, OTID_STRUCT_PLAYER_ID);
        SetMonData(&mon, MON_DATA_SPECIES, &excluded[j]);
        EXPECT_EQ(GetTrioElementalMoves(&mon.box, moves), 0);
    }
    BeginTrioElementalLessons();
    EXPECT_EQ(gMoveRelearnerState, MOVE_RELEARNER_TRIO_ELEMENTAL_MOVES);
    EndTrioElementalLessons();
    EXPECT_EQ(gMoveRelearnerState, MOVE_RELEARNER_LEVEL_UP_MOVES);
}
