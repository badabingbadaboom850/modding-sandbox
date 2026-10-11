#include "global.h"
#include "test/battle.h"
#include "battle_util.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "constants/flags.h"

static void UnlockSpiritMegas(void)
{
    FlagSet(FLAG_RIKO_CAVERN_COMPLETE);
    FlagSet(FLAG_TRIO_PENNY_SPIRIT_COMPLETE);
    FlagSet(FLAG_TRIO_BIJUU_SPIRIT_COMPLETE);
}

SINGLE_BATTLE_TEST("Spirit keepsakes Mega Evolve every personal form and restore its exact starting form")
{
    u32 species, target, item;
    PARAMETRIZE { species = SPECIES_RIKO; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_FLOWER; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_PRINCESS; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_FIGHTING; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_RAINCOAT; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_BIJUU_BREAD; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_DETECTIVE; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_PENNY_BLANKET; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_BLANKET_DACHSBUN; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_LIFEGUARD; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_LIFEGUARD_DACHSBUN; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_RIKO_BALLOON; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_ECHO; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_WING; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_FIRE; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_WATER; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_GRASS; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_ELECTRIC; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_ICE; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_PSYCHIC; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_FLYING; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_DRAGON; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_FIDOUGH; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_DACHSBUN; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_GUARDIAN; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_WATER; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_GRASS; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_BRAVE; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_HOTDOG; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_HOTDOG_DACHSBUN; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_BIJUU; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_FIGHTING; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_POISON; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_GROUND; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_ROCK; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_BUG; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_GHOST; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_DARK; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_STEEL; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_PSYCHIC; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_ICE; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_EMBER; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_BOX; target = SPECIES_MEGA_BIJUU_SPIRIT; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_RIKO_BUG; target = SPECIES_MEGA_RIKO_SPIRIT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_PENNY_GROUND; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_STEEL; target = SPECIES_MEGA_PENNY_SPIRIT; item = ITEM_PENNYS_SHIELD; }
    GIVEN {
        UnlockSpiritMegas();
        AddBagItem(item, 1);
        PLAYER(species) { Item(ITEM_LEFTOVERS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, player);
    } THEN {
        EXPECT_EQ(player->species, target);
        EXPECT(gSpeciesInfo[target].isMegaEvolution);
        EXPECT(CheckBagHasItem(item, 1));
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), species);
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    }
}

SINGLE_BATTLE_TEST("Spirit Mega eligibility requires the own keepsake and actual final victories")
{
    GIVEN {
        PLAYER(SPECIES_RIKO);
        OPPONENT(SPECIES_RIKO);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        u32 mask;
        UnlockSpiritMegas();
        RemoveBagItem(ITEM_RIKOS_SPARK, CountTotalItemQuantityInBag(ITEM_RIKOS_SPARK));
        EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), SPECIES_NONE);
        AddBagItem(ITEM_RIKOS_SPARK, 1);
        for (mask = 0; mask < 8; mask++)
        {
            FlagClear(FLAG_RIKO_CAVERN_COMPLETE);
            FlagClear(FLAG_TRIO_PENNY_SPIRIT_COMPLETE);
            FlagClear(FLAG_TRIO_BIJUU_SPIRIT_COMPLETE);
            FlagSet(FLAG_DEFEATED_SUICUNE);
            FlagSet(FLAG_TRIO_PENNY_HOME_WIN);
            FlagSet(FLAG_TRIO_BIJUU_HOME_WIN);
            if (mask & 1) FlagSet(FLAG_RIKO_CAVERN_COMPLETE);
            if (mask & 2) FlagSet(FLAG_TRIO_PENNY_SPIRIT_COMPLETE);
            if (mask & 4) FlagSet(FLAG_TRIO_BIJUU_SPIRIT_COMPLETE);
            EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), mask == 7 ? SPECIES_MEGA_RIKO_SPIRIT : SPECIES_NONE);
        }
        EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)), SPECIES_NONE);
        gBattleMons[B_POSITION_PLAYER_LEFT].species = SPECIES_PENNY_SPIRIT;
        EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), SPECIES_NONE);
        gBattleMons[B_POSITION_PLAYER_LEFT].species = SPECIES_FIDOUGH;
        RemoveBagItem(ITEM_PENNYS_SHIELD, CountTotalItemQuantityInBag(ITEM_PENNYS_SHIELD));
        EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), SPECIES_NONE);
        AddBagItem(ITEM_PENNYS_SHIELD, 1);
        EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), SPECIES_MEGA_PENNY_SPIRIT);
        FlagClear(FLAG_TRIO_PENNY_SPIRIT_COMPLETE);
        EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), SPECIES_NONE);
        gBattleMons[B_POSITION_PLAYER_LEFT].species = SPECIES_BIJUU;
        RemoveBagItem(ITEM_BIJUUS_LIGHT, CountTotalItemQuantityInBag(ITEM_BIJUUS_LIGHT));
        EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), SPECIES_NONE);
        AddBagItem(ITEM_BIJUUS_LIGHT, 1);
        EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), SPECIES_MEGA_BIJUU_SPIRIT);
        FlagClear(FLAG_TRIO_BIJUU_SPIRIT_COMPLETE);
        EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), SPECIES_NONE);
    }
}

DOUBLE_BATTLE_TEST("Partner trainers cannot borrow the player's Spirit keepsakes")
{
    GIVEN {
        UnlockSpiritMegas();
        AddBagItem(ITEM_RIKOS_SPARK, 1);
        PLAYER(SPECIES_RIKO);
        PLAYER(SPECIES_RIKO);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_CELEBRATE); MOVE(playerRight, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)), SPECIES_MEGA_RIKO_SPIRIT);
        gBattleTypeFlags |= BATTLE_TYPE_PLAYER_HAS_PARTNER;
        EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)), SPECIES_NONE);
        EXPECT_EQ(GetTrioSpiritMegaTargetSpecies(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), SPECIES_MEGA_RIKO_SPIRIT);
    }
}

SINGLE_BATTLE_TEST("A held Bondstone keeps the existing Riko and Bijuu Mega path")
{
    u32 species, target, item;
    PARAMETRIZE { species = SPECIES_RIKO; target = SPECIES_MEGA_RIKO; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_BIJUU; target = SPECIES_MEGA_BIJUU; item = ITEM_BIJUUS_LIGHT; }
    GIVEN {
        UnlockSpiritMegas();
        AddBagItem(item, 1);
        PLAYER(species) { Item(ITEM_BONDSTONE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, player);
    } THEN {
        EXPECT_EQ(player->species, target);
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), species);
    }
}

SINGLE_BATTLE_TEST("Fainted Spirit Megas return to their original personal form")
{
    u32 species, item;
    PARAMETRIZE { species = SPECIES_RIKO_FLOWER; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_PRINCESS; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_RIKO_RAINCOAT; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_BIJUU_BREAD; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_DETECTIVE; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_PENNY_BLANKET; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_BLANKET_DACHSBUN; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_LIFEGUARD; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_LIFEGUARD_DACHSBUN; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_RIKO_BALLOON; item = ITEM_RIKOS_SPARK; }
    PARAMETRIZE { species = SPECIES_PENNY_BRAVE; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_HOTDOG; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_PENNY_HOTDOG_DACHSBUN; item = ITEM_PENNYS_SHIELD; }
    PARAMETRIZE { species = SPECIES_BIJUU_EMBER; item = ITEM_BIJUUS_LIGHT; }
    PARAMETRIZE { species = SPECIES_BIJUU_BOX; item = ITEM_BIJUUS_LIGHT; }
    GIVEN {
        UnlockSpiritMegas();
        AddBagItem(item, 1);
        PLAYER(species) { Level(5); HP(1); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Level(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); MOVE(opponent, MOVE_NIGHT_SHADE); SEND_OUT(player, 1); }
        TURN { USE_ITEM(player, ITEM_REVIVE, 0); }
        TURN { SWITCH(player, 0); }
    } THEN {
        EXPECT_EQ(player->species, species);
        EXPECT(CheckBagHasItem(item, 1));
    }
}


SINGLE_BATTLE_TEST("Ordinary Bondstone Megas return to their costume starting form")
{
    u32 species, target;
    PARAMETRIZE { species = SPECIES_RIKO_PRINCESS; target = SPECIES_MEGA_RIKO; }
    PARAMETRIZE { species = SPECIES_RIKO_RAINCOAT; target = SPECIES_MEGA_RIKO; }
    PARAMETRIZE { species = SPECIES_BIJUU_BREAD; target = SPECIES_MEGA_BIJUU; }
    PARAMETRIZE { species = SPECIES_BIJUU_DETECTIVE; target = SPECIES_MEGA_BIJUU; }
    PARAMETRIZE { species = SPECIES_RIKO_BALLOON; target = SPECIES_MEGA_RIKO; }
    PARAMETRIZE { species = SPECIES_BIJUU_BOX; target = SPECIES_MEGA_BIJUU; }
    PARAMETRIZE { species = SPECIES_RIKO; target = SPECIES_MEGA_RIKO; }
    PARAMETRIZE { species = SPECIES_BIJUU; target = SPECIES_MEGA_BIJUU; }
    GIVEN {
        PLAYER(species) { Item(ITEM_BONDSTONE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_MEGA_EVOLUTION, player);
    } THEN {
        EXPECT_EQ(player->species, target);
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), species);
    }
}
