#include "global.h"
#include "pokemon.h"
#include "item.h"
#include "battle_util.h"
#include "move_relearner.h"
#include "test/test.h"
#include "constants/items.h"
#include "constants/species.h"

TEST("RikoDragon reusable keepsake transforms its entry forms and reverses safely")
{
    struct Pokemon mon;
    static const u16 entries[]={SPECIES_RIKO,SPECIES_RIKO_BALLOON,SPECIES_RIKO_PRINCESS,SPECIES_RIKO_RAINCOAT};
    for(u32 i=0;i<ARRAY_COUNT(entries);i++) {
        CreateMon(&mon,entries[i],20,0,OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_POM_DRAGON_PLUSH,NULL,NULL,CHECK_EVO),SPECIES_RIKO_DRAGON);
        EXPECT_EQ(GetMonData(&mon,MON_DATA_SPECIES),entries[i]);
    }
    CreateMon(&mon,SPECIES_RIKO_DRAGON,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_POM_DRAGON_PLUSH,NULL,NULL,CHECK_EVO),SPECIES_RIKO);
    EXPECT_EQ(GetItemPocket(ITEM_POM_DRAGON_PLUSH),POCKET_KEY_ITEMS);EXPECT_EQ(GetItemImportance(ITEM_POM_DRAGON_PLUSH),1);
    CreateMon(&mon,SPECIES_PIKACHU,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_POM_DRAGON_PLUSH,NULL,NULL,CHECK_EVO),SPECIES_NONE);
}
TEST("RikoDragon retains female family identity signatures and distinct complete art")
{
    const struct SpeciesInfo *s=&gSpeciesInfo[SPECIES_RIKO_DRAGON];
    EXPECT_EQ(s->types[0],TYPE_DRAGON);EXPECT_EQ(s->types[1],TYPE_FAIRY);
    EXPECT_EQ(s->genderRatio,MON_FEMALE);
    EXPECT_EQ((u32)s->natDexNum,(u32)gSpeciesInfo[SPECIES_RIKO].natDexNum);
    EXPECT_EQ((u32)s->growthRate,(u32)gSpeciesInfo[SPECIES_RIKO].growthRate);
    EXPECT_EQ(s->formSpeciesIdTable,gSpeciesInfo[SPECIES_RIKO].formSpeciesIdTable);
    EXPECT(s->frontPic && s->backPic && s->iconSprite && s->overworldData.images);
    EXPECT(s->frontPic!=gSpeciesInfo[SPECIES_RIKO].frontPic);
    EXPECT_EQ(GetTrioSpiritKeepsakeForSpecies(SPECIES_RIKO_DRAGON),ITEM_RIKOS_SPARK);
    EXPECT(CanLearnTeachableMove(SPECIES_RIKO_DRAGON,MOVE_FLOOF_FURY));
}
TEST("RikoDragon Scott lessons honor actual levels known attacks and later unlocks")
{
    struct Pokemon mon;u16 moves[MAX_RELEARNER_MOVES];
    static const u8 levels[]={5,20,40};
    for(u32 i=0;i<ARRAY_COUNT(levels);i++) {
        CreateMon(&mon,SPECIES_RIKO_DRAGON,levels[i],0,OTID_STRUCT_PLAYER_ID);
        for(u32 slot=0;slot<4;slot++)SetMonMoveSlot(&mon,MOVE_TACKLE,slot);
        u32 count=GetTrioElementalMoves(&mon.box,moves);bool32 first=FALSE,last=FALSE;
        for(u32 j=0;j<count;j++) {
            if(moves[j]==MOVE_DRAGON_BREATH)first=TRUE;
            if(moves[j]==MOVE_OUTRAGE)last=TRUE;
        }
        EXPECT(first);EXPECT_EQ(last,levels[i]>=40);
        SetMonMoveSlot(&mon,MOVE_DRAGON_BREATH,0);count=GetTrioElementalMoves(&mon.box,moves);
        for(u32 j=0;j<count;j++)EXPECT(moves[j]!=MOVE_DRAGON_BREATH);
    }
}
TEST("RikoDragon stored identity and learned attacks survive reversion")
{
    struct Pokemon mon,copy;
    CreateMon(&mon,SPECIES_RIKO_DRAGON,30,0,OTID_STRUCT_PLAYER_ID);
    u32 personality=GetMonData(&mon,MON_DATA_PERSONALITY),ot=GetMonData(&mon,MON_DATA_OT_ID);
    SetMonMoveSlot(&mon,MOVE_DRAGON_BREATH,0);memcpy(&copy,&mon,sizeof(mon));
    u16 species=SPECIES_RIKO;SetMonData(&copy,MON_DATA_SPECIES,&species);CalculateMonStats(&copy);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_PERSONALITY),personality);EXPECT_EQ(GetMonData(&copy,MON_DATA_OT_ID),ot);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_MOVE1),MOVE_DRAGON_BREATH);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_SANITY_IS_BAD_EGG),FALSE);
    EXPECT_EQ(sizeof(struct SaveBlock1),15444);EXPECT_EQ(sizeof(struct SaveBlock2),2864);EXPECT_EQ(sizeof(struct SaveBlock3),100);
}

TEST("RikoBug reusable keepsake transforms its entry forms and reverses safely")
{
    struct Pokemon mon;
    static const u16 entries[]={SPECIES_RIKO,SPECIES_RIKO_BALLOON,SPECIES_RIKO_PRINCESS,SPECIES_RIKO_RAINCOAT};
    for(u32 i=0;i<ARRAY_COUNT(entries);i++) {
        CreateMon(&mon,entries[i],20,0,OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_RIKOS_HONEYCOMB,NULL,NULL,CHECK_EVO),SPECIES_RIKO_BUG);
        EXPECT_EQ(GetMonData(&mon,MON_DATA_SPECIES),entries[i]);
    }
    CreateMon(&mon,SPECIES_RIKO_BUG,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_RIKOS_HONEYCOMB,NULL,NULL,CHECK_EVO),SPECIES_RIKO);
    EXPECT_EQ(GetItemPocket(ITEM_RIKOS_HONEYCOMB),POCKET_KEY_ITEMS);EXPECT_EQ(GetItemImportance(ITEM_RIKOS_HONEYCOMB),1);
    CreateMon(&mon,SPECIES_PIKACHU,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_RIKOS_HONEYCOMB,NULL,NULL,CHECK_EVO),SPECIES_NONE);
}
TEST("RikoBug retains female family identity signatures and distinct complete art")
{
    const struct SpeciesInfo *s=&gSpeciesInfo[SPECIES_RIKO_BUG];
    EXPECT_EQ(s->types[0],TYPE_BUG);EXPECT_EQ(s->types[1],TYPE_FAIRY);
    EXPECT_EQ(s->genderRatio,MON_FEMALE);
    EXPECT_EQ((u32)s->natDexNum,(u32)gSpeciesInfo[SPECIES_RIKO].natDexNum);
    EXPECT_EQ((u32)s->growthRate,(u32)gSpeciesInfo[SPECIES_RIKO].growthRate);
    EXPECT_EQ(s->formSpeciesIdTable,gSpeciesInfo[SPECIES_RIKO].formSpeciesIdTable);
    EXPECT(s->frontPic && s->backPic && s->iconSprite && s->overworldData.images);
    EXPECT(s->frontPic!=gSpeciesInfo[SPECIES_RIKO].frontPic);
    EXPECT_EQ(GetTrioSpiritKeepsakeForSpecies(SPECIES_RIKO_BUG),ITEM_RIKOS_SPARK);
    EXPECT(CanLearnTeachableMove(SPECIES_RIKO_BUG,MOVE_FLOOF_FURY));
}
TEST("RikoBug Scott lessons honor actual levels known attacks and later unlocks")
{
    struct Pokemon mon;u16 moves[MAX_RELEARNER_MOVES];
    static const u8 levels[]={5,20,40};
    for(u32 i=0;i<ARRAY_COUNT(levels);i++) {
        CreateMon(&mon,SPECIES_RIKO_BUG,levels[i],0,OTID_STRUCT_PLAYER_ID);
        for(u32 slot=0;slot<4;slot++)SetMonMoveSlot(&mon,MOVE_TACKLE,slot);
        u32 count=GetTrioElementalMoves(&mon.box,moves);bool32 first=FALSE,last=FALSE;
        for(u32 j=0;j<count;j++) {
            if(moves[j]==MOVE_STRUGGLE_BUG)first=TRUE;
            if(moves[j]==MOVE_BUG_BUZZ)last=TRUE;
        }
        EXPECT(first);EXPECT_EQ(last,levels[i]>=40);
        SetMonMoveSlot(&mon,MOVE_STRUGGLE_BUG,0);count=GetTrioElementalMoves(&mon.box,moves);
        for(u32 j=0;j<count;j++)EXPECT(moves[j]!=MOVE_STRUGGLE_BUG);
    }
}
TEST("RikoBug stored identity and learned attacks survive reversion")
{
    struct Pokemon mon,copy;
    CreateMon(&mon,SPECIES_RIKO_BUG,30,0,OTID_STRUCT_PLAYER_ID);
    u32 personality=GetMonData(&mon,MON_DATA_PERSONALITY),ot=GetMonData(&mon,MON_DATA_OT_ID);
    SetMonMoveSlot(&mon,MOVE_STRUGGLE_BUG,0);memcpy(&copy,&mon,sizeof(mon));
    u16 species=SPECIES_RIKO;SetMonData(&copy,MON_DATA_SPECIES,&species);CalculateMonStats(&copy);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_PERSONALITY),personality);EXPECT_EQ(GetMonData(&copy,MON_DATA_OT_ID),ot);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_MOVE1),MOVE_STRUGGLE_BUG);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_SANITY_IS_BAD_EGG),FALSE);
    EXPECT_EQ(sizeof(struct SaveBlock1),15444);EXPECT_EQ(sizeof(struct SaveBlock2),2864);EXPECT_EQ(sizeof(struct SaveBlock3),100);
}

TEST("BijuuDark reusable keepsake transforms its entry forms and reverses safely")
{
    struct Pokemon mon;
    static const u16 entries[]={SPECIES_BIJUU,SPECIES_BIJUU_BOX,SPECIES_BIJUU_BREAD,SPECIES_BIJUU_DETECTIVE};
    for(u32 i=0;i<ARRAY_COUNT(entries);i++) {
        CreateMon(&mon,entries[i],20,0,OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_COCOAS_SNEAKY_CAPE,NULL,NULL,CHECK_EVO),SPECIES_BIJUU_DARK);
        EXPECT_EQ(GetMonData(&mon,MON_DATA_SPECIES),entries[i]);
    }
    CreateMon(&mon,SPECIES_BIJUU_DARK,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_COCOAS_SNEAKY_CAPE,NULL,NULL,CHECK_EVO),SPECIES_BIJUU);
    EXPECT_EQ(GetItemPocket(ITEM_COCOAS_SNEAKY_CAPE),POCKET_KEY_ITEMS);EXPECT_EQ(GetItemImportance(ITEM_COCOAS_SNEAKY_CAPE),1);
    CreateMon(&mon,SPECIES_PIKACHU,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_COCOAS_SNEAKY_CAPE,NULL,NULL,CHECK_EVO),SPECIES_NONE);
}
TEST("BijuuDark retains female family identity signatures and distinct complete art")
{
    const struct SpeciesInfo *s=&gSpeciesInfo[SPECIES_BIJUU_DARK];
    EXPECT_EQ(s->types[0],TYPE_NORMAL);EXPECT_EQ(s->types[1],TYPE_DARK);
    EXPECT_EQ(s->genderRatio,MON_FEMALE);
    EXPECT_EQ((u32)s->natDexNum,(u32)gSpeciesInfo[SPECIES_BIJUU].natDexNum);
    EXPECT_EQ((u32)s->growthRate,(u32)gSpeciesInfo[SPECIES_BIJUU].growthRate);
    EXPECT_EQ(s->formSpeciesIdTable,gSpeciesInfo[SPECIES_BIJUU].formSpeciesIdTable);
    EXPECT(s->frontPic && s->backPic && s->iconSprite && s->overworldData.images);
    EXPECT(s->frontPic!=gSpeciesInfo[SPECIES_BIJUU].frontPic);
    EXPECT_EQ(GetTrioSpiritKeepsakeForSpecies(SPECIES_BIJUU_DARK),ITEM_BIJUUS_LIGHT);
    EXPECT(CanLearnTeachableMove(SPECIES_BIJUU_DARK,MOVE_MIDNIGHT_ZOOM));
}
TEST("BijuuDark Scott lessons honor actual levels known attacks and later unlocks")
{
    struct Pokemon mon;u16 moves[MAX_RELEARNER_MOVES];
    static const u8 levels[]={5,20,40};
    for(u32 i=0;i<ARRAY_COUNT(levels);i++) {
        CreateMon(&mon,SPECIES_BIJUU_DARK,levels[i],0,OTID_STRUCT_PLAYER_ID);
        for(u32 slot=0;slot<4;slot++)SetMonMoveSlot(&mon,MOVE_TACKLE,slot);
        u32 count=GetTrioElementalMoves(&mon.box,moves);bool32 first=FALSE,last=FALSE;
        for(u32 j=0;j<count;j++) {
            if(moves[j]==MOVE_BITE)first=TRUE;
            if(moves[j]==MOVE_CRUNCH)last=TRUE;
        }
        EXPECT(first);EXPECT_EQ(last,levels[i]>=40);
        SetMonMoveSlot(&mon,MOVE_BITE,0);count=GetTrioElementalMoves(&mon.box,moves);
        for(u32 j=0;j<count;j++)EXPECT(moves[j]!=MOVE_BITE);
    }
}
TEST("BijuuDark stored identity and learned attacks survive reversion")
{
    struct Pokemon mon,copy;
    CreateMon(&mon,SPECIES_BIJUU_DARK,30,0,OTID_STRUCT_PLAYER_ID);
    u32 personality=GetMonData(&mon,MON_DATA_PERSONALITY),ot=GetMonData(&mon,MON_DATA_OT_ID);
    SetMonMoveSlot(&mon,MOVE_BITE,0);memcpy(&copy,&mon,sizeof(mon));
    u16 species=SPECIES_BIJUU;SetMonData(&copy,MON_DATA_SPECIES,&species);CalculateMonStats(&copy);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_PERSONALITY),personality);EXPECT_EQ(GetMonData(&copy,MON_DATA_OT_ID),ot);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_MOVE1),MOVE_BITE);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_SANITY_IS_BAD_EGG),FALSE);
    EXPECT_EQ(sizeof(struct SaveBlock1),15444);EXPECT_EQ(sizeof(struct SaveBlock2),2864);EXPECT_EQ(sizeof(struct SaveBlock3),100);
}

TEST("BijuuRock reusable keepsake transforms its entry forms and reverses safely")
{
    struct Pokemon mon;
    static const u16 entries[]={SPECIES_BIJUU,SPECIES_BIJUU_BOX,SPECIES_BIJUU_BREAD,SPECIES_BIJUU_DETECTIVE};
    for(u32 i=0;i<ARRAY_COUNT(entries);i++) {
        CreateMon(&mon,entries[i],20,0,OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_COCOAS_SHINY_PEBBLE,NULL,NULL,CHECK_EVO),SPECIES_BIJUU_ROCK);
        EXPECT_EQ(GetMonData(&mon,MON_DATA_SPECIES),entries[i]);
    }
    CreateMon(&mon,SPECIES_BIJUU_ROCK,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_COCOAS_SHINY_PEBBLE,NULL,NULL,CHECK_EVO),SPECIES_BIJUU);
    EXPECT_EQ(GetItemPocket(ITEM_COCOAS_SHINY_PEBBLE),POCKET_KEY_ITEMS);EXPECT_EQ(GetItemImportance(ITEM_COCOAS_SHINY_PEBBLE),1);
    CreateMon(&mon,SPECIES_PIKACHU,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_COCOAS_SHINY_PEBBLE,NULL,NULL,CHECK_EVO),SPECIES_NONE);
}
TEST("BijuuRock retains female family identity signatures and distinct complete art")
{
    const struct SpeciesInfo *s=&gSpeciesInfo[SPECIES_BIJUU_ROCK];
    EXPECT_EQ(s->types[0],TYPE_NORMAL);EXPECT_EQ(s->types[1],TYPE_ROCK);
    EXPECT_EQ(s->genderRatio,MON_FEMALE);
    EXPECT_EQ((u32)s->natDexNum,(u32)gSpeciesInfo[SPECIES_BIJUU].natDexNum);
    EXPECT_EQ((u32)s->growthRate,(u32)gSpeciesInfo[SPECIES_BIJUU].growthRate);
    EXPECT_EQ(s->formSpeciesIdTable,gSpeciesInfo[SPECIES_BIJUU].formSpeciesIdTable);
    EXPECT(s->frontPic && s->backPic && s->iconSprite && s->overworldData.images);
    EXPECT(s->frontPic!=gSpeciesInfo[SPECIES_BIJUU].frontPic);
    EXPECT_EQ(GetTrioSpiritKeepsakeForSpecies(SPECIES_BIJUU_ROCK),ITEM_BIJUUS_LIGHT);
    EXPECT(CanLearnTeachableMove(SPECIES_BIJUU_ROCK,MOVE_MIDNIGHT_ZOOM));
}
TEST("BijuuRock Scott lessons honor actual levels known attacks and later unlocks")
{
    struct Pokemon mon;u16 moves[MAX_RELEARNER_MOVES];
    static const u8 levels[]={5,20,40};
    for(u32 i=0;i<ARRAY_COUNT(levels);i++) {
        CreateMon(&mon,SPECIES_BIJUU_ROCK,levels[i],0,OTID_STRUCT_PLAYER_ID);
        for(u32 slot=0;slot<4;slot++)SetMonMoveSlot(&mon,MOVE_TACKLE,slot);
        u32 count=GetTrioElementalMoves(&mon.box,moves);bool32 first=FALSE,last=FALSE;
        for(u32 j=0;j<count;j++) {
            if(moves[j]==MOVE_ROCK_THROW)first=TRUE;
            if(moves[j]==MOVE_STONE_EDGE)last=TRUE;
        }
        EXPECT(first);EXPECT_EQ(last,levels[i]>=40);
        SetMonMoveSlot(&mon,MOVE_ROCK_THROW,0);count=GetTrioElementalMoves(&mon.box,moves);
        for(u32 j=0;j<count;j++)EXPECT(moves[j]!=MOVE_ROCK_THROW);
    }
}
TEST("BijuuRock stored identity and learned attacks survive reversion")
{
    struct Pokemon mon,copy;
    CreateMon(&mon,SPECIES_BIJUU_ROCK,30,0,OTID_STRUCT_PLAYER_ID);
    u32 personality=GetMonData(&mon,MON_DATA_PERSONALITY),ot=GetMonData(&mon,MON_DATA_OT_ID);
    SetMonMoveSlot(&mon,MOVE_ROCK_THROW,0);memcpy(&copy,&mon,sizeof(mon));
    u16 species=SPECIES_BIJUU;SetMonData(&copy,MON_DATA_SPECIES,&species);CalculateMonStats(&copy);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_PERSONALITY),personality);EXPECT_EQ(GetMonData(&copy,MON_DATA_OT_ID),ot);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_MOVE1),MOVE_ROCK_THROW);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_SANITY_IS_BAD_EGG),FALSE);
    EXPECT_EQ(sizeof(struct SaveBlock1),15444);EXPECT_EQ(sizeof(struct SaveBlock2),2864);EXPECT_EQ(sizeof(struct SaveBlock3),100);
}

TEST("PennyGround reusable keepsake transforms its entry forms and reverses safely")
{
    struct Pokemon mon;
    static const u16 entries[]={SPECIES_PENNY_GUARDIAN};
    for(u32 i=0;i<ARRAY_COUNT(entries);i++) {
        CreateMon(&mon,entries[i],20,0,OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_PENNYS_GARDEN_TROWEL,NULL,NULL,CHECK_EVO),SPECIES_PENNY_GROUND);
        EXPECT_EQ(GetMonData(&mon,MON_DATA_SPECIES),entries[i]);
    }
    CreateMon(&mon,SPECIES_PENNY_GROUND,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_PENNYS_GARDEN_TROWEL,NULL,NULL,CHECK_EVO),SPECIES_PENNY_GUARDIAN);
    EXPECT_EQ(GetItemPocket(ITEM_PENNYS_GARDEN_TROWEL),POCKET_KEY_ITEMS);EXPECT_EQ(GetItemImportance(ITEM_PENNYS_GARDEN_TROWEL),1);
    CreateMon(&mon,SPECIES_PIKACHU,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_PENNYS_GARDEN_TROWEL,NULL,NULL,CHECK_EVO),SPECIES_NONE);
}
TEST("PennyGround retains female family identity signatures and distinct complete art")
{
    const struct SpeciesInfo *s=&gSpeciesInfo[SPECIES_PENNY_GROUND];
    EXPECT_EQ(s->types[0],TYPE_FAIRY);EXPECT_EQ(s->types[1],TYPE_GROUND);
    EXPECT_EQ(s->genderRatio,MON_FEMALE);
    EXPECT_EQ((u32)s->natDexNum,(u32)gSpeciesInfo[SPECIES_PENNY_GUARDIAN].natDexNum);
    EXPECT_EQ((u32)s->growthRate,(u32)gSpeciesInfo[SPECIES_PENNY_GUARDIAN].growthRate);
    EXPECT_EQ(s->formSpeciesIdTable,gSpeciesInfo[SPECIES_PENNY_GUARDIAN].formSpeciesIdTable);
    EXPECT(s->frontPic && s->backPic && s->iconSprite && s->overworldData.images);
    EXPECT(s->frontPic!=gSpeciesInfo[SPECIES_PENNY_GUARDIAN].frontPic);
    EXPECT_EQ(GetTrioSpiritKeepsakeForSpecies(SPECIES_PENNY_GROUND),ITEM_PENNYS_SHIELD);
    EXPECT(CanLearnTeachableMove(SPECIES_PENNY_GROUND,MOVE_BLANKEY_TIME));
}
TEST("PennyGround Scott lessons honor actual levels known attacks and later unlocks")
{
    struct Pokemon mon;u16 moves[MAX_RELEARNER_MOVES];
    static const u8 levels[]={5,20,40};
    for(u32 i=0;i<ARRAY_COUNT(levels);i++) {
        CreateMon(&mon,SPECIES_PENNY_GROUND,levels[i],0,OTID_STRUCT_PLAYER_ID);
        for(u32 slot=0;slot<4;slot++)SetMonMoveSlot(&mon,MOVE_TACKLE,slot);
        u32 count=GetTrioElementalMoves(&mon.box,moves);bool32 first=FALSE,last=FALSE;
        for(u32 j=0;j<count;j++) {
            if(moves[j]==MOVE_MUD_SLAP)first=TRUE;
            if(moves[j]==MOVE_EARTHQUAKE)last=TRUE;
        }
        EXPECT(first);EXPECT_EQ(last,levels[i]>=40);
        SetMonMoveSlot(&mon,MOVE_MUD_SLAP,0);count=GetTrioElementalMoves(&mon.box,moves);
        for(u32 j=0;j<count;j++)EXPECT(moves[j]!=MOVE_MUD_SLAP);
    }
}
TEST("PennyGround stored identity and learned attacks survive reversion")
{
    struct Pokemon mon,copy;
    CreateMon(&mon,SPECIES_PENNY_GROUND,30,0,OTID_STRUCT_PLAYER_ID);
    u32 personality=GetMonData(&mon,MON_DATA_PERSONALITY),ot=GetMonData(&mon,MON_DATA_OT_ID);
    SetMonMoveSlot(&mon,MOVE_MUD_SLAP,0);memcpy(&copy,&mon,sizeof(mon));
    u16 species=SPECIES_PENNY_GUARDIAN;SetMonData(&copy,MON_DATA_SPECIES,&species);CalculateMonStats(&copy);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_PERSONALITY),personality);EXPECT_EQ(GetMonData(&copy,MON_DATA_OT_ID),ot);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_MOVE1),MOVE_MUD_SLAP);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_SANITY_IS_BAD_EGG),FALSE);
    EXPECT_EQ(sizeof(struct SaveBlock1),15444);EXPECT_EQ(sizeof(struct SaveBlock2),2864);EXPECT_EQ(sizeof(struct SaveBlock3),100);
}

TEST("PennySteel reusable keepsake transforms its entry forms and reverses safely")
{
    struct Pokemon mon;
    static const u16 entries[]={SPECIES_PENNY_GUARDIAN};
    for(u32 i=0;i<ARRAY_COUNT(entries);i++) {
        CreateMon(&mon,entries[i],20,0,OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_DADS_TOOLBOX,NULL,NULL,CHECK_EVO),SPECIES_PENNY_STEEL);
        EXPECT_EQ(GetMonData(&mon,MON_DATA_SPECIES),entries[i]);
    }
    CreateMon(&mon,SPECIES_PENNY_STEEL,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_DADS_TOOLBOX,NULL,NULL,CHECK_EVO),SPECIES_PENNY_GUARDIAN);
    EXPECT_EQ(GetItemPocket(ITEM_DADS_TOOLBOX),POCKET_KEY_ITEMS);EXPECT_EQ(GetItemImportance(ITEM_DADS_TOOLBOX),1);
    CreateMon(&mon,SPECIES_PIKACHU,20,0,OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_DADS_TOOLBOX,NULL,NULL,CHECK_EVO),SPECIES_NONE);
}
TEST("PennySteel retains female family identity signatures and distinct complete art")
{
    const struct SpeciesInfo *s=&gSpeciesInfo[SPECIES_PENNY_STEEL];
    EXPECT_EQ(s->types[0],TYPE_FAIRY);EXPECT_EQ(s->types[1],TYPE_STEEL);
    EXPECT_EQ(s->genderRatio,MON_FEMALE);
    EXPECT_EQ((u32)s->natDexNum,(u32)gSpeciesInfo[SPECIES_PENNY_GUARDIAN].natDexNum);
    EXPECT_EQ((u32)s->growthRate,(u32)gSpeciesInfo[SPECIES_PENNY_GUARDIAN].growthRate);
    EXPECT_EQ(s->formSpeciesIdTable,gSpeciesInfo[SPECIES_PENNY_GUARDIAN].formSpeciesIdTable);
    EXPECT(s->frontPic && s->backPic && s->iconSprite && s->overworldData.images);
    EXPECT(s->frontPic!=gSpeciesInfo[SPECIES_PENNY_GUARDIAN].frontPic);
    EXPECT_EQ(GetTrioSpiritKeepsakeForSpecies(SPECIES_PENNY_STEEL),ITEM_PENNYS_SHIELD);
    EXPECT(CanLearnTeachableMove(SPECIES_PENNY_STEEL,MOVE_BLANKEY_TIME));
}
TEST("PennySteel Scott lessons honor actual levels known attacks and later unlocks")
{
    struct Pokemon mon;u16 moves[MAX_RELEARNER_MOVES];
    static const u8 levels[]={5,20,40};
    for(u32 i=0;i<ARRAY_COUNT(levels);i++) {
        CreateMon(&mon,SPECIES_PENNY_STEEL,levels[i],0,OTID_STRUCT_PLAYER_ID);
        for(u32 slot=0;slot<4;slot++)SetMonMoveSlot(&mon,MOVE_TACKLE,slot);
        u32 count=GetTrioElementalMoves(&mon.box,moves);bool32 first=FALSE,last=FALSE;
        for(u32 j=0;j<count;j++) {
            if(moves[j]==MOVE_METAL_CLAW)first=TRUE;
            if(moves[j]==MOVE_HEAVY_SLAM)last=TRUE;
        }
        EXPECT(first);EXPECT_EQ(last,levels[i]>=40);
        SetMonMoveSlot(&mon,MOVE_METAL_CLAW,0);count=GetTrioElementalMoves(&mon.box,moves);
        for(u32 j=0;j<count;j++)EXPECT(moves[j]!=MOVE_METAL_CLAW);
    }
}
TEST("PennySteel stored identity and learned attacks survive reversion")
{
    struct Pokemon mon,copy;
    CreateMon(&mon,SPECIES_PENNY_STEEL,30,0,OTID_STRUCT_PLAYER_ID);
    u32 personality=GetMonData(&mon,MON_DATA_PERSONALITY),ot=GetMonData(&mon,MON_DATA_OT_ID);
    SetMonMoveSlot(&mon,MOVE_METAL_CLAW,0);memcpy(&copy,&mon,sizeof(mon));
    u16 species=SPECIES_PENNY_GUARDIAN;SetMonData(&copy,MON_DATA_SPECIES,&species);CalculateMonStats(&copy);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_PERSONALITY),personality);EXPECT_EQ(GetMonData(&copy,MON_DATA_OT_ID),ot);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_MOVE1),MOVE_METAL_CLAW);
    EXPECT_EQ(GetMonData(&copy,MON_DATA_SANITY_IS_BAD_EGG),FALSE);
    EXPECT_EQ(sizeof(struct SaveBlock1),15444);EXPECT_EQ(sizeof(struct SaveBlock2),2864);EXPECT_EQ(sizeof(struct SaveBlock3),100);
}

TEST("New elemental keepsakes reject other girls and Penny's ordinary stages")
{
    struct Pokemon mon;
    static const u16 species[]={SPECIES_RIKO_BUG,SPECIES_RIKO_DRAGON,SPECIES_BIJUU_DARK,SPECIES_BIJUU_ROCK,SPECIES_PENNY_GROUND,SPECIES_PENNY_STEEL};
    static const u16 items[]={ITEM_RIKOS_HONEYCOMB,ITEM_POM_DRAGON_PLUSH,ITEM_COCOAS_SNEAKY_CAPE,ITEM_COCOAS_SHINY_PEBBLE,ITEM_PENNYS_GARDEN_TROWEL,ITEM_DADS_TOOLBOX};
    for(u32 i=0;i<ARRAY_COUNT(species);i++) {
        CreateMon(&mon,species[i],20,0,OTID_STRUCT_PLAYER_ID);
        for(u32 j=0;j<ARRAY_COUNT(items);j++)
            if(i!=j)EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,items[j],NULL,NULL,CHECK_EVO),SPECIES_NONE);
    }
    static const u16 pennyStages[]={SPECIES_FIDOUGH,SPECIES_DACHSBUN,SPECIES_PENNY_HOTDOG,SPECIES_PENNY_HOTDOG_DACHSBUN};
    for(u32 i=0;i<ARRAY_COUNT(pennyStages);i++) {
        CreateMon(&mon,pennyStages[i],20,0,OTID_STRUCT_PLAYER_ID);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_PENNYS_GARDEN_TROWEL,NULL,NULL,CHECK_EVO),SPECIES_NONE);
        EXPECT_EQ(GetEvolutionTargetSpecies(&mon,EVO_MODE_ITEM_CHECK,ITEM_DADS_TOOLBOX,NULL,NULL,CHECK_EVO),SPECIES_NONE);
    }
}
