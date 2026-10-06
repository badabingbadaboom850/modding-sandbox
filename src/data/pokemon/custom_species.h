// Custom species assets and level-up learnsets for Riko and Bijuu.
#if P_FAMILY_RIKO
const u32 gMonFrontPic_Riko[] = INCBIN_U32("graphics/pokemon/riko/front.4bpp.smol");
const u32 gMonBackPic_Riko[] = INCBIN_U32("graphics/pokemon/riko/back.4bpp.smol");
const u16 gMonPalette_Riko[] = INCBIN_U16("graphics/pokemon/riko/normal.gbapal");
const u16 gMonShinyPalette_Riko[] = INCBIN_U16("graphics/pokemon/riko/shiny.gbapal");
const u8 gMonIcon_Riko[] = INCBIN_U8("graphics/pokemon/riko/icon.4bpp");
const u16 gMonIconPalette_Riko[] = INCBIN_U16("graphics/pokemon/riko/icon_normal.gbapal");
const u16 gMonShinyIconPalette_Riko[] = INCBIN_U16("graphics/pokemon/riko/icon_shiny.gbapal");
static const struct LevelUpMove sRikoLevelUpLearnset[] = {
    LEVEL_UP_MOVE(1, MOVE_TACKLE), LEVEL_UP_MOVE(1, MOVE_TAIL_WHIP),
    LEVEL_UP_MOVE(5, MOVE_BABY_DOLL_EYES), LEVEL_UP_MOVE(9, MOVE_CHARM),
    LEVEL_UP_MOVE(13, MOVE_QUICK_ATTACK), LEVEL_UP_MOVE(17, MOVE_DRAINING_KISS),
    LEVEL_UP_MOVE(22, MOVE_PLAY_ROUGH), LEVEL_UP_MOVE(27, MOVE_TAKE_DOWN),
    LEVEL_UP_MOVE(32, MOVE_DAZZLING_GLEAM), LEVEL_UP_MOVE(37, MOVE_AGILITY),
    LEVEL_UP_MOVE(42, MOVE_MOONBLAST), LEVEL_UP_MOVE(47, MOVE_LAST_RESORT),
    LEVEL_UP_MOVE(52, MOVE_FLOOF_FURY), LEVEL_UP_MOVE(60, MOVE_MEGA_RIKO), LEVEL_UP_END
};
#endif
#if P_FAMILY_BIJUU
const u32 gMonFrontPic_Bijuu[] = INCBIN_U32("graphics/pokemon/bijuu/front.4bpp.smol");
const u32 gMonBackPic_Bijuu[] = INCBIN_U32("graphics/pokemon/bijuu/back.4bpp.smol");
const u16 gMonPalette_Bijuu[] = INCBIN_U16("graphics/pokemon/bijuu/normal.gbapal");
const u16 gMonShinyPalette_Bijuu[] = INCBIN_U16("graphics/pokemon/bijuu/shiny.gbapal");
const u8 gMonIcon_Bijuu[] = INCBIN_U8("graphics/pokemon/bijuu/icon.4bpp");
const u16 gMonIconPalette_Bijuu[] = INCBIN_U16("graphics/pokemon/bijuu/icon_normal.gbapal");
const u16 gMonShinyIconPalette_Bijuu[] = INCBIN_U16("graphics/pokemon/bijuu/icon_shiny.gbapal");
#endif

#if P_FAMILY_RIKO
const u32 gMonFrontPic_RikoFire[] = INCBIN_U32("graphics/pokemon/riko_fire/front.4bpp.smol");
const u32 gMonBackPic_RikoFire[] = INCBIN_U32("graphics/pokemon/riko_fire/back.4bpp.smol");
const u16 gMonPalette_RikoFire[] = INCBIN_U16("graphics/pokemon/riko_fire/normal.gbapal");
const u16 gMonShinyPalette_RikoFire[] = INCBIN_U16("graphics/pokemon/riko_fire/shiny.gbapal");
const u8 gMonIcon_RikoFire[] = INCBIN_U8("graphics/pokemon/riko_fire/icon.4bpp");
const u16 gMonIconPalette_RikoFire[] = INCBIN_U16("graphics/pokemon/riko_fire/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoFire[] = INCBIN_U16("graphics/pokemon/riko_fire/icon_shiny.gbapal");
const u32 gMonFrontPic_RikoWater[] = INCBIN_U32("graphics/pokemon/riko_water/front.4bpp.smol");
const u32 gMonBackPic_RikoWater[] = INCBIN_U32("graphics/pokemon/riko_water/back.4bpp.smol");
const u16 gMonPalette_RikoWater[] = INCBIN_U16("graphics/pokemon/riko_water/normal.gbapal");
const u16 gMonShinyPalette_RikoWater[] = INCBIN_U16("graphics/pokemon/riko_water/shiny.gbapal");
const u8 gMonIcon_RikoWater[] = INCBIN_U8("graphics/pokemon/riko_water/icon.4bpp");
const u16 gMonIconPalette_RikoWater[] = INCBIN_U16("graphics/pokemon/riko_water/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoWater[] = INCBIN_U16("graphics/pokemon/riko_water/icon_shiny.gbapal");
const u32 gMonFrontPic_RikoGrass[] = INCBIN_U32("graphics/pokemon/riko_grass/front.4bpp.smol");
const u32 gMonBackPic_RikoGrass[] = INCBIN_U32("graphics/pokemon/riko_grass/back.4bpp.smol");
const u16 gMonPalette_RikoGrass[] = INCBIN_U16("graphics/pokemon/riko_grass/normal.gbapal");
const u16 gMonShinyPalette_RikoGrass[] = INCBIN_U16("graphics/pokemon/riko_grass/shiny.gbapal");
const u8 gMonIcon_RikoGrass[] = INCBIN_U8("graphics/pokemon/riko_grass/icon.4bpp");
const u16 gMonIconPalette_RikoGrass[] = INCBIN_U16("graphics/pokemon/riko_grass/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoGrass[] = INCBIN_U16("graphics/pokemon/riko_grass/icon_shiny.gbapal");
const u32 gMonFrontPic_RikoElectric[] = INCBIN_U32("graphics/pokemon/riko_electric/front.4bpp.smol");
const u32 gMonBackPic_RikoElectric[] = INCBIN_U32("graphics/pokemon/riko_electric/back.4bpp.smol");
const u16 gMonPalette_RikoElectric[] = INCBIN_U16("graphics/pokemon/riko_electric/normal.gbapal");
const u16 gMonShinyPalette_RikoElectric[] = INCBIN_U16("graphics/pokemon/riko_electric/shiny.gbapal");
const u8 gMonIcon_RikoElectric[] = INCBIN_U8("graphics/pokemon/riko_electric/icon.4bpp");
const u16 gMonIconPalette_RikoElectric[] = INCBIN_U16("graphics/pokemon/riko_electric/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoElectric[] = INCBIN_U16("graphics/pokemon/riko_electric/icon_shiny.gbapal");
const u32 gMonFrontPic_RikoIce[] = INCBIN_U32("graphics/pokemon/riko_ice/front.4bpp.smol");
const u32 gMonBackPic_RikoIce[] = INCBIN_U32("graphics/pokemon/riko_ice/back.4bpp.smol");
const u16 gMonPalette_RikoIce[] = INCBIN_U16("graphics/pokemon/riko_ice/normal.gbapal");
const u16 gMonShinyPalette_RikoIce[] = INCBIN_U16("graphics/pokemon/riko_ice/shiny.gbapal");
const u8 gMonIcon_RikoIce[] = INCBIN_U8("graphics/pokemon/riko_ice/icon.4bpp");
const u16 gMonIconPalette_RikoIce[] = INCBIN_U16("graphics/pokemon/riko_ice/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoIce[] = INCBIN_U16("graphics/pokemon/riko_ice/icon_shiny.gbapal");
const u32 gMonFrontPic_RikoPsychic[] = INCBIN_U32("graphics/pokemon/riko_psychic/front.4bpp.smol");
const u32 gMonBackPic_RikoPsychic[] = INCBIN_U32("graphics/pokemon/riko_psychic/back.4bpp.smol");
const u16 gMonPalette_RikoPsychic[] = INCBIN_U16("graphics/pokemon/riko_psychic/normal.gbapal");
const u16 gMonShinyPalette_RikoPsychic[] = INCBIN_U16("graphics/pokemon/riko_psychic/shiny.gbapal");
const u8 gMonIcon_RikoPsychic[] = INCBIN_U8("graphics/pokemon/riko_psychic/icon.4bpp");
const u16 gMonIconPalette_RikoPsychic[] = INCBIN_U16("graphics/pokemon/riko_psychic/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoPsychic[] = INCBIN_U16("graphics/pokemon/riko_psychic/icon_shiny.gbapal");
const u32 gMonFrontPic_RikoFlying[] = INCBIN_U32("graphics/pokemon/riko_flying/front.4bpp.smol");
const u32 gMonBackPic_RikoFlying[] = INCBIN_U32("graphics/pokemon/riko_flying/back.4bpp.smol");
const u16 gMonPalette_RikoFlying[] = INCBIN_U16("graphics/pokemon/riko_flying/normal.gbapal");
const u16 gMonShinyPalette_RikoFlying[] = INCBIN_U16("graphics/pokemon/riko_flying/shiny.gbapal");
const u8 gMonIcon_RikoFlying[] = INCBIN_U8("graphics/pokemon/riko_flying/icon.4bpp");
const u16 gMonIconPalette_RikoFlying[] = INCBIN_U16("graphics/pokemon/riko_flying/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoFlying[] = INCBIN_U16("graphics/pokemon/riko_flying/icon_shiny.gbapal");
const u32 gMonFrontPic_RikoDragon[] = INCBIN_U32("graphics/pokemon/riko_dragon/front.4bpp.smol");
const u32 gMonBackPic_RikoDragon[] = INCBIN_U32("graphics/pokemon/riko_dragon/back.4bpp.smol");
const u16 gMonPalette_RikoDragon[] = INCBIN_U16("graphics/pokemon/riko_dragon/normal.gbapal");
const u16 gMonShinyPalette_RikoDragon[] = INCBIN_U16("graphics/pokemon/riko_dragon/shiny.gbapal");
const u8 gMonIcon_RikoDragon[] = INCBIN_U8("graphics/pokemon/riko_dragon/icon.4bpp");
const u16 gMonIconPalette_RikoDragon[] = INCBIN_U16("graphics/pokemon/riko_dragon/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoDragon[] = INCBIN_U16("graphics/pokemon/riko_dragon/icon_shiny.gbapal");
#endif
#if P_FAMILY_BIJUU
const u32 gMonFrontPic_BijuuFighting[] = INCBIN_U32("graphics/pokemon/bijuu_fighting/front.4bpp.smol");
const u32 gMonBackPic_BijuuFighting[] = INCBIN_U32("graphics/pokemon/bijuu_fighting/back.4bpp.smol");
const u16 gMonPalette_BijuuFighting[] = INCBIN_U16("graphics/pokemon/bijuu_fighting/normal.gbapal");
const u16 gMonShinyPalette_BijuuFighting[] = INCBIN_U16("graphics/pokemon/bijuu_fighting/shiny.gbapal");
const u8 gMonIcon_BijuuFighting[] = INCBIN_U8("graphics/pokemon/bijuu_fighting/icon.4bpp");
const u16 gMonIconPalette_BijuuFighting[] = INCBIN_U16("graphics/pokemon/bijuu_fighting/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuFighting[] = INCBIN_U16("graphics/pokemon/bijuu_fighting/icon_shiny.gbapal");
const u32 gMonFrontPic_BijuuPoison[] = INCBIN_U32("graphics/pokemon/bijuu_poison/front.4bpp.smol");
const u32 gMonBackPic_BijuuPoison[] = INCBIN_U32("graphics/pokemon/bijuu_poison/back.4bpp.smol");
const u16 gMonPalette_BijuuPoison[] = INCBIN_U16("graphics/pokemon/bijuu_poison/normal.gbapal");
const u16 gMonShinyPalette_BijuuPoison[] = INCBIN_U16("graphics/pokemon/bijuu_poison/shiny.gbapal");
const u8 gMonIcon_BijuuPoison[] = INCBIN_U8("graphics/pokemon/bijuu_poison/icon.4bpp");
const u16 gMonIconPalette_BijuuPoison[] = INCBIN_U16("graphics/pokemon/bijuu_poison/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuPoison[] = INCBIN_U16("graphics/pokemon/bijuu_poison/icon_shiny.gbapal");
const u32 gMonFrontPic_BijuuGround[] = INCBIN_U32("graphics/pokemon/bijuu_ground/front.4bpp.smol");
const u32 gMonBackPic_BijuuGround[] = INCBIN_U32("graphics/pokemon/bijuu_ground/back.4bpp.smol");
const u16 gMonPalette_BijuuGround[] = INCBIN_U16("graphics/pokemon/bijuu_ground/normal.gbapal");
const u16 gMonShinyPalette_BijuuGround[] = INCBIN_U16("graphics/pokemon/bijuu_ground/shiny.gbapal");
const u8 gMonIcon_BijuuGround[] = INCBIN_U8("graphics/pokemon/bijuu_ground/icon.4bpp");
const u16 gMonIconPalette_BijuuGround[] = INCBIN_U16("graphics/pokemon/bijuu_ground/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuGround[] = INCBIN_U16("graphics/pokemon/bijuu_ground/icon_shiny.gbapal");
const u32 gMonFrontPic_BijuuRock[] = INCBIN_U32("graphics/pokemon/bijuu_rock/front.4bpp.smol");
const u32 gMonBackPic_BijuuRock[] = INCBIN_U32("graphics/pokemon/bijuu_rock/back.4bpp.smol");
const u16 gMonPalette_BijuuRock[] = INCBIN_U16("graphics/pokemon/bijuu_rock/normal.gbapal");
const u16 gMonShinyPalette_BijuuRock[] = INCBIN_U16("graphics/pokemon/bijuu_rock/shiny.gbapal");
const u8 gMonIcon_BijuuRock[] = INCBIN_U8("graphics/pokemon/bijuu_rock/icon.4bpp");
const u16 gMonIconPalette_BijuuRock[] = INCBIN_U16("graphics/pokemon/bijuu_rock/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuRock[] = INCBIN_U16("graphics/pokemon/bijuu_rock/icon_shiny.gbapal");
const u32 gMonFrontPic_BijuuBug[] = INCBIN_U32("graphics/pokemon/bijuu_bug/front.4bpp.smol");
const u32 gMonBackPic_BijuuBug[] = INCBIN_U32("graphics/pokemon/bijuu_bug/back.4bpp.smol");
const u16 gMonPalette_BijuuBug[] = INCBIN_U16("graphics/pokemon/bijuu_bug/normal.gbapal");
const u16 gMonShinyPalette_BijuuBug[] = INCBIN_U16("graphics/pokemon/bijuu_bug/shiny.gbapal");
const u8 gMonIcon_BijuuBug[] = INCBIN_U8("graphics/pokemon/bijuu_bug/icon.4bpp");
const u16 gMonIconPalette_BijuuBug[] = INCBIN_U16("graphics/pokemon/bijuu_bug/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuBug[] = INCBIN_U16("graphics/pokemon/bijuu_bug/icon_shiny.gbapal");
const u32 gMonFrontPic_BijuuGhost[] = INCBIN_U32("graphics/pokemon/bijuu_ghost/front.4bpp.smol");
const u32 gMonBackPic_BijuuGhost[] = INCBIN_U32("graphics/pokemon/bijuu_ghost/back.4bpp.smol");
const u16 gMonPalette_BijuuGhost[] = INCBIN_U16("graphics/pokemon/bijuu_ghost/normal.gbapal");
const u16 gMonShinyPalette_BijuuGhost[] = INCBIN_U16("graphics/pokemon/bijuu_ghost/shiny.gbapal");
const u8 gMonIcon_BijuuGhost[] = INCBIN_U8("graphics/pokemon/bijuu_ghost/icon.4bpp");
const u16 gMonIconPalette_BijuuGhost[] = INCBIN_U16("graphics/pokemon/bijuu_ghost/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuGhost[] = INCBIN_U16("graphics/pokemon/bijuu_ghost/icon_shiny.gbapal");
const u32 gMonFrontPic_BijuuDark[] = INCBIN_U32("graphics/pokemon/bijuu_dark/front.4bpp.smol");
const u32 gMonBackPic_BijuuDark[] = INCBIN_U32("graphics/pokemon/bijuu_dark/back.4bpp.smol");
const u16 gMonPalette_BijuuDark[] = INCBIN_U16("graphics/pokemon/bijuu_dark/normal.gbapal");
const u16 gMonShinyPalette_BijuuDark[] = INCBIN_U16("graphics/pokemon/bijuu_dark/shiny.gbapal");
const u8 gMonIcon_BijuuDark[] = INCBIN_U8("graphics/pokemon/bijuu_dark/icon.4bpp");
const u16 gMonIconPalette_BijuuDark[] = INCBIN_U16("graphics/pokemon/bijuu_dark/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuDark[] = INCBIN_U16("graphics/pokemon/bijuu_dark/icon_shiny.gbapal");
const u32 gMonFrontPic_BijuuSteel[] = INCBIN_U32("graphics/pokemon/bijuu_steel/front.4bpp.smol");
const u32 gMonBackPic_BijuuSteel[] = INCBIN_U32("graphics/pokemon/bijuu_steel/back.4bpp.smol");
const u16 gMonPalette_BijuuSteel[] = INCBIN_U16("graphics/pokemon/bijuu_steel/normal.gbapal");
const u16 gMonShinyPalette_BijuuSteel[] = INCBIN_U16("graphics/pokemon/bijuu_steel/shiny.gbapal");
const u8 gMonIcon_BijuuSteel[] = INCBIN_U8("graphics/pokemon/bijuu_steel/icon.4bpp");
const u16 gMonIconPalette_BijuuSteel[] = INCBIN_U16("graphics/pokemon/bijuu_steel/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuSteel[] = INCBIN_U16("graphics/pokemon/bijuu_steel/icon_shiny.gbapal");
#endif
#if P_FAMILY_RIKO
const u32 gMonFrontPic_RikoMega[] = INCBIN_U32("graphics/pokemon/riko/mega/front.4bpp.smol");
const u32 gMonBackPic_RikoMega[] = INCBIN_U32("graphics/pokemon/riko/mega/back.4bpp.smol");
const u16 gMonPalette_RikoMega[] = INCBIN_U16("graphics/pokemon/riko/mega/normal.gbapal");
const u16 gMonShinyPalette_RikoMega[] = INCBIN_U16("graphics/pokemon/riko/mega/shiny.gbapal");
#endif
