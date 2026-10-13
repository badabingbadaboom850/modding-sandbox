#include "global.h"
#include "test/test.h"
#include "test/battle.h"
#include "battle_controllers.h"
#include "battle_script_commands.h"
#include "battle_ai_util.h"
#include "trio_runoff.h"
#include "constants/items.h"
#include "constants/battle_string_ids.h"
#include "sprite.h"
#include "random.h"

extern bool32 IsValidForBattleButDead(struct Pokemon *mon);
extern bool32 BattleIntro_ShouldWaitForHealthbox(enum BattlerId battler);

static void MakeParty(u16 girl, u32 size)
{
    TrioRunoff_Clear();
    ZeroPlayerPartyMons();
    for (u32 i = 0; i < size; i++)
        CreateMonWithIVs(&gPlayerParty[i], i == 0 ? girl : SPECIES_PIKACHU, 20, i + 100, OTID_STRUCT_PLAYER_ID, 31);
    gBattleTypeFlags = 0;
}

TEST("Runoff masks one girl without modifying party bytes and follows her through reordered slots")
{
    MakeParty(SPECIES_BIJUU, 6);
    struct Pokemon before[PARTY_SIZE];
    memcpy(before, gPlayerParty, sizeof(before));
    TrioRunoff_Begin(100);
    EXPECT(TrioRunoff_IsAway(&gPlayerParty[0]));
    EXPECT(!IsValidForBattle(&gPlayerParty[0]));
    EXPECT(!IsValidForBattleButDead(&gPlayerParty[0]));
    for (u32 i = 1; i < PARTY_SIZE; i++) EXPECT(IsValidForBattle(&gPlayerParty[i]));
    EXPECT_EQ(memcmp(before, gPlayerParty, sizeof(before)), 0);
    EXPECT_EQ(TrioRunoff_TakeDepartureString(), STRINGID_TRIO_BIJUU_RUNOFF);
    EXPECT_EQ(TrioRunoff_TakeDepartureString(), 0);
    struct Pokemon temp = gPlayerParty[0];
    gPlayerParty[0] = gPlayerParty[4]; gPlayerParty[4] = temp;
    EXPECT(!TrioRunoff_IsAway(&gPlayerParty[0]));
    EXPECT(TrioRunoff_IsAway(&gPlayerParty[4]));
    EXPECT(!TrioRunoff_IsAway(&temp));
    TrioRunoff_Clear();
    EXPECT(IsValidForBattle(&gPlayerParty[4]));
}

TEST("Runoff protects the sole usable mon and the two required double battle starters")
{
    MakeParty(SPECIES_RIKO, 1); TrioRunoff_Begin(100);
    EXPECT(IsValidForBattle(&gPlayerParty[0]));
    MakeParty(SPECIES_FIDOUGH, 2); gBattleTypeFlags = BATTLE_TYPE_DOUBLE;
    TrioRunoff_Begin(100); EXPECT(IsValidForBattle(&gPlayerParty[0]));
    MakeParty(SPECIES_FIDOUGH, 3); gBattleTypeFlags = BATTLE_TYPE_DOUBLE;
    TrioRunoff_Begin(100); EXPECT(!IsValidForBattle(&gPlayerParty[0]));
    EXPECT(IsValidForBattle(&gPlayerParty[1])); EXPECT(IsValidForBattle(&gPlayerParty[2]));
    TrioRunoff_Clear();
}

TEST("Runoff eligibility includes personal forms and excludes eggs bosses fainted and cloned identities")
{
    u16 forms[] = {SPECIES_RIKO_BUG, SPECIES_RIKO_FIGHTING, SPECIES_BIJUU_DARK,
        SPECIES_BIJUU_ROCK, SPECIES_PENNY_GROUND, SPECIES_PENNY_STEEL, SPECIES_DACHSBUN};
    for (u32 i = 0; i < ARRAY_COUNT(forms); i++)
    {
        MakeParty(forms[i], 2); TrioRunoff_Begin(100);
        EXPECT(TrioRunoff_IsAway(&gPlayerParty[0]));
    }
    MakeParty(SPECIES_RIKO_SPIRIT, 2); TrioRunoff_Begin(100);
    EXPECT(!TrioRunoff_IsAway(&gPlayerParty[0]));
    MakeParty(SPECIES_BIJUU, 2); u32 egg = TRUE;
    SetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, &egg); TrioRunoff_Begin(100);
    EXPECT(!TrioRunoff_IsAway(&gPlayerParty[0]));
    MakeParty(SPECIES_BIJUU, 2); u32 hp = 0;
    SetMonData(&gPlayerParty[0], MON_DATA_HP, &hp); TrioRunoff_Begin(100);
    EXPECT(!TrioRunoff_IsAway(&gPlayerParty[0]));
    MakeParty(SPECIES_BIJUU, 3); gPlayerParty[1] = gPlayerParty[0];
    TrioRunoff_Begin(100); EXPECT(!TrioRunoff_IsAway(&gPlayerParty[0]));
    TrioRunoff_Clear();
}

TEST("Runoff excludes borrowed parties recorded battles and special formats and clears prior state")
{
    u32 flags[] = {BATTLE_TYPE_LINK, BATTLE_TYPE_RECORDED, BATTLE_TYPE_RECORDED_LINK,
        BATTLE_TYPE_MULTI, BATTLE_TYPE_INGAME_PARTNER, BATTLE_TYPE_SAFARI,
        BATTLE_TYPE_FIRST_BATTLE, BATTLE_TYPE_WALLY_TUTORIAL, BATTLE_TYPE_BATTLE_TOWER};
    for (u32 i = 0; i < ARRAY_COUNT(flags); i++)
    {
        MakeParty(SPECIES_RIKO, 2); TrioRunoff_Begin(100);
        EXPECT(TrioRunoff_IsAway(&gPlayerParty[0]));
        gBattleTypeFlags = flags[i]; TrioRunoff_Begin(100);
        EXPECT(!TrioRunoff_IsAway(&gPlayerParty[0]));
    }
    MakeParty(SPECIES_RIKO, 2); TrioRunoff_Begin(0);
    EXPECT(!TrioRunoff_IsAway(&gPlayerParty[0]));
}

TEST("An absent girl cannot be healed by items or keep an exhausted team in battle")
{
    MakeParty(SPECIES_FIDOUGH, 2);
    u32 hp = 10; SetMonData(&gPlayerParty[0], MON_DATA_HP, &hp);
    TrioRunoff_Begin(100);
    EXPECT(PokemonUseItemEffects(&gPlayerParty[0], ITEM_POTION, 0, 0, FALSE, 0, 1));
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP), 10);
    EXPECT(!NoAliveMonsForPlayer());
    hp = 0; SetMonData(&gPlayerParty[1], MON_DATA_HP, &hp);
    EXPECT(NoAliveMonsForPlayer());
    TrioRunoff_Clear(); EXPECT(!NoAliveMonsForPlayer());
    EXPECT_EQ(sizeof(struct SaveBlock1), 15444);
    EXPECT_EQ(sizeof(struct SaveBlock2), 2864);
    EXPECT_EQ(sizeof(struct SaveBlock3), 100);
}

SINGLE_BATTLE_TEST("Runoff prevents bench switching and counts only available reserves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
        PLAYER(SPECIES_BIJUU);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
        TrioRunoff_EnableBattleTest();
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("Bijuu spotted a mouse!\nWait, no! Come back!\pShe will return after\nthis battle.");
    } THEN {
        EXPECT(TrioRunoff_IsAway(&gPlayerParty[1]));
        EXPECT(!CanBattlerSwitch(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)));
        EXPECT_EQ(CountUsablePartyMons(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), 0);
        EXPECT_EQ(gBattlerPartyIndexes[B_POSITION_PLAYER_LEFT], 0);
    }
}

DOUBLE_BATTLE_TEST("Runoff leaves both doubles starters available while a third girl runs off")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
        PLAYER(SPECIES_WYNAUT) { Moves(MOVE_CELEBRATE); }
        PLAYER(SPECIES_RIKO);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WYNAUT) { Moves(MOVE_CELEBRATE); }
        TrioRunoff_EnableBattleTest();
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_CELEBRATE); MOVE(playerRight, MOVE_CELEBRATE);
            MOVE(opponentLeft, MOVE_CELEBRATE); MOVE(opponentRight, MOVE_CELEBRATE); }
    } THEN {
        EXPECT(TrioRunoff_IsAway(&gPlayerParty[2]));
        EXPECT(!CanBattlerSwitch(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)));
        EXPECT_EQ(CountUsablePartyMons(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), 0);
    }
}

SINGLE_BATTLE_TEST("Runoff replaces a missing lead before the initial send out")
{
    GIVEN {
        PLAYER(SPECIES_RIKO) { Moves(MOVE_CELEBRATE); }
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
        TrioRunoff_EnableBattleTest();
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        EXPECT(TrioRunoff_IsAway(&gPlayerParty[0]));
        EXPECT_EQ(gBattlerPartyIndexes[B_POSITION_PLAYER_LEFT], 1);
        EXPECT_EQ(player->species, SPECIES_WOBBUFFET);
    }
}

WILD_BATTLE_TEST("Runoff cannot force another send out after the available team loses")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(1); MaxHP(20); Speed(1); Moves(MOVE_CELEBRATE); }
        PLAYER(SPECIES_BIJUU) { Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Moves(MOVE_DRAGON_RAGE); }
        TrioRunoff_EnableBattleTest();
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_DRAGON_RAGE); }
    } THEN {
        EXPECT_EQ(gBattleOutcome, B_OUTCOME_LOST);
        EXPECT_GT(GetMonData(&gPlayerParty[1], MON_DATA_HP), 0);
    }
}

TEST("Runoff intro advances with an already completed trainer healthbox slide using production flags")
{
    u16 girls[] = {SPECIES_RIKO, SPECIES_BIJUU, SPECIES_FIDOUGH};
    u8 oldId = gHealthboxSpriteIds[1];
    SpriteCallback oldCallback = gSprites[0].callback;
    gHealthboxSpriteIds[1] = 0;
    gSprites[0].callback = SpriteCallbackDummy;
    for (u32 i = 0; i < ARRAY_COUNT(girls); i++)
    {
        MakeParty(girls[i], 2);
        gBattleTypeFlags = BATTLE_TYPE_TRAINER;
        TrioRunoff_Begin(100);
        EXPECT(!TrioRunoff_DepartureAnnounced());
        EXPECT(BattleIntro_ShouldWaitForHealthbox((enum BattlerId)0));
        EXPECT_NE(TrioRunoff_TakeDepartureString(), 0);
        EXPECT(TrioRunoff_DepartureAnnounced());
        // The opponent's animation has finished while the departure text was
        // printing. The old guard returned forever here with this idle sprite.
        EXPECT(!BattleIntro_ShouldWaitForHealthbox((enum BattlerId)0));
        EXPECT_EQ(TrioRunoff_TakeDepartureString(), 0);
        TrioRunoff_Clear();
        EXPECT(!TrioRunoff_DepartureAnnounced());
        EXPECT(BattleIntro_ShouldWaitForHealthbox((enum BattlerId)0));
        gBattleTypeFlags = 0;
        EXPECT(!BattleIntro_ShouldWaitForHealthbox((enum BattlerId)0));
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_RECORDED;
        EXPECT(!BattleIntro_ShouldWaitForHealthbox((enum BattlerId)0));
    }
    gHealthboxSpriteIds[1] = oldId;
    gSprites[0].callback = oldCallback;
    gBattleTypeFlags = 0;
}

TEST("Runoff normal rate accepts precisely rolls zero through four")
{
    rng_value_t savedRng = gRngValue;
    MakeParty(SPECIES_RIKO, 2);
    EXPECT_EQ(TRIO_RUNOFF_CHANCE, 5);
    u32 seen = 0;
    bool8 rolls[100] = {FALSE};
    for (u32 seed = 0; seed < 10000 && seen < 100; seed++)
    {
        SeedRng(seed);
        u32 roll = Random() % 100;
        if (rolls[roll])
            continue;
        rolls[roll] = TRUE;
        SeedRng(seed);
        TrioRunoff_Begin(TRIO_RUNOFF_CHANCE);
        EXPECT_EQ(TrioRunoff_IsAway(&gPlayerParty[0]), roll < 5);
        seen++;
    }
    EXPECT_EQ(seen, 100);
    TrioRunoff_Clear();
    gRngValue = savedRng;
}
