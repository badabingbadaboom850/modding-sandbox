#include "global.h"
#include "pokemon.h"
#include "battle_util.h"
#include "item.h"
#include "move_relearner.h"
#include "test/test.h"
#include "constants/items.h"
#include "constants/species.h"

static const u16 sBases[] = {SPECIES_RIKO, SPECIES_BIJUU, SPECIES_FIDOUGH, SPECIES_DACHSBUN};
static const u16 sCostumes[] = {SPECIES_RIKO_BALLOON, SPECIES_BIJUU_BOX, SPECIES_PENNY_HOTDOG, SPECIES_PENNY_HOTDOG_DACHSBUN};
static const u16 sItems[] = {ITEM_RIKOS_BALLOON, ITEM_BIJUUS_BOX, ITEM_PENNYS_HOTDOG_BUN, ITEM_PENNYS_HOTDOG_BUN};

TEST("Costumes toggle through normal evolution without affecting other family forms")
{
    struct Pokemon mon;
    for (u32 j = 0; j < ARRAY_COUNT(sBases); j++)
    {
        CreateMon(&mon, sBases[j], 20, 0, OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, sItems[j], NULL, NULL, CHECK_EVO), sCostumes[j]);
        EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), sBases[j]);
        CreateMon(&mon, sCostumes[j], 20, 0, OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, sItems[j], NULL, NULL, CHECK_EVO), sBases[j]);
        EXPECT_EQ(GetItemPocket(sItems[j]), POCKET_KEY_ITEMS);
        EXPECT_EQ(GetItemImportance(sItems[j]), 1);
        for (u32 k = 0; k < ARRAY_COUNT(sBases); k++)
            if (sItems[j] != sItems[k])
                EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, sItems[k], NULL, NULL, CHECK_EVO), SPECIES_NONE);
    }
    CreateMon(&mon, SPECIES_RIKO_ELECTRIC, 20, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, ITEM_RIKOS_BALLOON, NULL, NULL, CHECK_EVO), SPECIES_NONE);
    CreateMon(&mon, SPECIES_RIKO_BALLOON, 20, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, ITEM_EEL_SUSHI, NULL, NULL, CHECK_EVO), SPECIES_RIKO_ELECTRIC);
}

TEST("Costumes match their base stats types abilities growth learnsets and tutor access")
{
    for (u32 j = 0; j < ARRAY_COUNT(sBases); j++)
    {
        const struct SpeciesInfo *base = &gSpeciesInfo[sBases[j]];
        const struct SpeciesInfo *skin = &gSpeciesInfo[sCostumes[j]];
        EXPECT_EQ(skin->baseHP, base->baseHP);
        EXPECT_EQ(skin->baseAttack, base->baseAttack);
        EXPECT_EQ(skin->baseDefense, base->baseDefense);
        EXPECT_EQ(skin->baseSpeed, base->baseSpeed);
        EXPECT_EQ(skin->baseSpAttack, base->baseSpAttack);
        EXPECT_EQ(skin->baseSpDefense, base->baseSpDefense);
        EXPECT_EQ((u32)skin->growthRate, (u32)base->growthRate);
        EXPECT_EQ(skin->genderRatio, MON_FEMALE);
        EXPECT_EQ((u32)skin->natDexNum, (u32)base->natDexNum);
        EXPECT_EQ(skin->levelUpLearnset, base->levelUpLearnset);
        EXPECT_EQ(skin->teachableLearnset, base->teachableLearnset);
        EXPECT_EQ(skin->eggMoveLearnset, base->eggMoveLearnset);
        EXPECT_EQ(skin->formSpeciesIdTable, base->formSpeciesIdTable);
        for (u32 k = 0; k < 2; k++) EXPECT_EQ(skin->types[k], base->types[k]);
        for (u32 k = 0; k < 3; k++) EXPECT_EQ(skin->abilities[k], base->abilities[k]);
        for (u32 k = 0; k < MOVES_COUNT_ALL; k++)
            EXPECT_EQ(CanLearnTeachableMove(sCostumes[j], k), CanLearnTeachableMove(sBases[j], k));
        EXPECT(skin->frontPic != base->frontPic && skin->backPic != base->backPic);
        EXPECT(skin->iconSprite != base->iconSprite);
        EXPECT(skin->overworldData.images != base->overworldData.images);
        EXPECT(!skin->isMegaEvolution);
        EXPECT(!DoesSpeciesHaveFormChangeMethod(sCostumes[j], FORM_CHANGE_END_BATTLE));
        EXPECT(!DoesSpeciesHaveFormChangeMethod(sCostumes[j], FORM_CHANGE_FAINT));
        EXPECT_EQ(GetTrioSpiritKeepsakeForSpecies(sCostumes[j]), GetTrioSpiritKeepsakeForSpecies(sBases[j]));
    }
}

TEST("Costume storage preserves taught moves personality and saved ABI")
{
    struct Pokemon mon, restored;
    u32 personality, trainer;
    for (u32 j = 0; j < ARRAY_COUNT(sBases); j++)
    {
        CreateMon(&mon, sBases[j], 30, 0, OTID_STRUCT_PLAYER_ID);
        SetMonMoveSlot(&mon, MOVE_THUNDER_SHOCK, 0);
        SetMonMoveSlot(&mon, MOVE_TACKLE, 1);
        personality = GetMonData(&mon, MON_DATA_PERSONALITY);
        trainer = GetMonData(&mon, MON_DATA_OT_ID);
        SetMonData(&mon, MON_DATA_SPECIES, &sCostumes[j]);
        CalculateMonStats(&mon);
        memcpy(&restored, &mon, sizeof(mon));
        EXPECT_EQ(GetMonData(&restored, MON_DATA_SPECIES), sCostumes[j]);
        EXPECT_EQ(GetMonData(&restored, MON_DATA_MOVE1), MOVE_THUNDER_SHOCK);
        EXPECT_EQ(GetMonData(&restored, MON_DATA_MOVE2), MOVE_TACKLE);
        EXPECT_EQ(GetMonData(&restored, MON_DATA_PERSONALITY), personality);
        EXPECT_EQ(GetMonData(&restored, MON_DATA_OT_ID), trainer);
        EXPECT_EQ(GetMonData(&restored, MON_DATA_SANITY_IS_BAD_EGG), FALSE);
    }
    EXPECT_EQ(sizeof(struct SaveBlock1), 15444);
    EXPECT_EQ(sizeof(struct SaveBlock2), 2864);
    EXPECT_EQ(sizeof(struct SaveBlock3), 100);
}


TEST("Hot Dog Penny preserves the costume across ordinary level26 evolution")
{
    struct Pokemon mon;
    CreateMon(&mon, SPECIES_PENNY_HOTDOG, 26, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_PENNY_HOTDOG_DACHSBUN);
    CreateMon(&mon, SPECIES_PENNY_HOTDOG_DACHSBUN, 26, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, ITEM_PENNYS_HOTDOG_BUN, NULL, NULL, CHECK_EVO), SPECIES_DACHSBUN);
}
