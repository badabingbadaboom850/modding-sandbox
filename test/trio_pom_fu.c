#include "global.h"
#include "pokemon.h"
#include "item.h"
#include "battle_util.h"
#include "move_relearner.h"
#include "test/test.h"
#include "constants/items.h"
#include "constants/species.h"

TEST("Pom Fu belt transforms ordinary and dressed Riko and reverses without mutating other forms")
{
    struct Pokemon mon;
    static const u16 entries[]={SPECIES_RIKO,SPECIES_RIKO_BALLOON,SPECIES_RIKO_PRINCESS,SPECIES_RIKO_RAINCOAT};
    for(u32 i=0;i<ARRAY_COUNT(entries);i++) {
        CreateMon(&mon,entries[i],20,0,OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_RIKOS_BLACK_BELT,NULL,NULL,CHECK_EVO),SPECIES_RIKO_FIGHTING);
        EXPECT_EQ(GetMonData(&mon,MON_DATA_SPECIES),entries[i]);
    }
    CreateMon(&mon,SPECIES_RIKO_FIGHTING,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_RIKOS_BLACK_BELT,NULL,NULL,CHECK_EVO),SPECIES_RIKO);
    EXPECT_EQ(GetItemPocket(ITEM_RIKOS_BLACK_BELT),POCKET_KEY_ITEMS);
    EXPECT_EQ(GetItemImportance(ITEM_RIKOS_BLACK_BELT),1);
    static const u16 others[]={SPECIES_RIKO_FIRE,SPECIES_BIJUU,SPECIES_FIDOUGH,SPECIES_RIKO_SPIRIT,SPECIES_RIKO_FLOWER};
    for(u32 i=0;i<ARRAY_COUNT(others);i++) {
        CreateMon(&mon,others[i],20,0,OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_RIKOS_BLACK_BELT,NULL,NULL,CHECK_EVO),SPECIES_NONE);
    }
}

TEST("Pom Fu is a female physical Fighting form with complete art and Riko family eligibility")
{
    const struct SpeciesInfo *s=&gSpeciesInfo[SPECIES_RIKO_FIGHTING];
    EXPECT_EQ(s->types[0],TYPE_NORMAL);EXPECT_EQ(s->types[1],TYPE_FIGHTING);
    EXPECT_EQ(s->baseHP+s->baseAttack+s->baseDefense+s->baseSpeed+s->baseSpAttack+s->baseSpDefense,560);
    EXPECT_EQ(s->baseAttack,110);EXPECT_EQ(s->genderRatio,MON_FEMALE);
    EXPECT_EQ((u32)s->natDexNum,(u32)gSpeciesInfo[SPECIES_RIKO].natDexNum);
    EXPECT_EQ((u32)s->growthRate,(u32)gSpeciesInfo[SPECIES_RIKO].growthRate);
    EXPECT_EQ(s->formSpeciesIdTable,gSpeciesInfo[SPECIES_RIKO].formSpeciesIdTable);
    EXPECT(s->frontPic && s->backPic && s->iconSprite && s->overworldData.images);
    EXPECT(s->frontPic!=gSpeciesInfo[SPECIES_RIKO].frontPic);
    EXPECT_EQ(GetTrioSpiritKeepsakeForSpecies(SPECIES_RIKO_FIGHTING),ITEM_RIKOS_SPARK);
    EXPECT(CanLearnTeachableMove(SPECIES_RIKO_FIGHTING,MOVE_FLOOF_FURY));
    EXPECT(!CanLearnTeachableMove(SPECIES_RIKO_FIGHTING,MOVE_BLANKEY_TIME));
}

TEST("Scott offers Pom Fu attacks only at the actual level and skips known moves")
{
    struct Pokemon mon;
    u16 moves[MAX_RELEARNER_MOVES];
    static const u8 levels[]={5,12,20,44};
    for(u32 i=0;i<ARRAY_COUNT(levels);i++) {
        CreateMon(&mon,SPECIES_RIKO_FIGHTING,levels[i],0,OTID_STRUCT_PLAYER_ID);
        for(u32 slot=0;slot<4;slot++)SetMonMoveSlot(&mon,MOVE_TACKLE,slot);
        u32 count=GetTrioElementalMoves(&mon.box,moves);
        bool32 force=FALSE,brick=FALSE,close=FALSE;
        for(u32 j=0;j<count;j++) {
            if(moves[j]==MOVE_FORCE_PALM)force=TRUE;
            if(moves[j]==MOVE_BRICK_BREAK)brick=TRUE;
            if(moves[j]==MOVE_CLOSE_COMBAT)close=TRUE;
        }
        EXPECT(force);EXPECT_EQ(brick,levels[i]>=20);EXPECT_EQ(close,levels[i]>=44);
        SetMonMoveSlot(&mon,MOVE_FORCE_PALM,0);
        count=GetTrioElementalMoves(&mon.box,moves);
        for(u32 j=0;j<count;j++)EXPECT(moves[j]!=MOVE_FORCE_PALM);
    }
}

TEST("Pom Fu storage and reversion preserve personality learned attacks and historical save sizes")
{
    struct Pokemon mon,copy;
    CreateMon(&mon,SPECIES_RIKO,30,0,OTID_STRUCT_PLAYER_ID);
    u32 personality=GetMonData(&mon,MON_DATA_PERSONALITY),ot=GetMonData(&mon,MON_DATA_OT_ID);
    u16 species=SPECIES_RIKO_FIGHTING;
    SetMonData(&mon,MON_DATA_SPECIES,&species);CalculateMonStats(&mon);
    SetMonMoveSlot(&mon,MOVE_BRICK_BREAK,0);memcpy(&copy,&mon,sizeof(mon));
    EXPECT_EQ(GetMonData(&copy,MON_DATA_SPECIES),SPECIES_RIKO_FIGHTING);
    species=SPECIES_RIKO;SetMonData(&copy,MON_DATA_SPECIES,&species);CalculateMonStats(&copy);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_PERSONALITY),personality);EXPECT_EQ(GetMonData(&copy,MON_DATA_OT_ID),ot);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_MOVE1),MOVE_BRICK_BREAK);
    EXPECT_EQ(sizeof(struct SaveBlock1),15444);EXPECT_EQ(sizeof(struct SaveBlock2),2864);EXPECT_EQ(sizeof(struct SaveBlock3),100);
    EXPECT_EQ(SPECIES_PENNY_LIFEGUARD_DACHSBUN,1628);EXPECT_EQ(ITEM_PENNYS_BEACH_VEST,964);
}
