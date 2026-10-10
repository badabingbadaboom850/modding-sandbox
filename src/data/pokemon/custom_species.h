// Custom species assets and level-up learnsets for Riko and Bijuu.
#if P_FAMILY_RIKO
const u32 gMonFrontPic_Riko[] = INCBIN_U32("graphics/pokemon/riko/front.4bpp.smol");
const u32 gMonBackPic_Riko[] = INCBIN_U32("graphics/pokemon/riko/back.4bpp.smol");
const u16 gMonPalette_Riko[] = INCBIN_U16("graphics/pokemon/riko/normal.gbapal");
const u16 gMonShinyPalette_Riko[] = INCBIN_U16("graphics/pokemon/riko/shiny.gbapal");
const u8 gMonIcon_Riko[] = INCBIN_U8("graphics/pokemon/riko/icon.4bpp");
const u16 gMonIconPalette_Riko[] = INCBIN_U16("graphics/pokemon/riko/icon_normal.gbapal");
const u16 gMonShinyIconPalette_Riko[] = INCBIN_U16("graphics/pokemon/riko/icon_shiny.gbapal");
const u32 gObjectEventPic_Riko[] = INCBIN_U32("graphics/pokemon/riko/overworld.4bpp");
const u16 gOverworldPalette_Riko[] = INCBIN_U16("graphics/pokemon/riko/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_Riko[] = INCBIN_U16("graphics/pokemon/riko/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_Riko[] = {
    overworld_ascending_frames(gObjectEventPic_Riko, 4, 4),
};
const u32 gMonFrontPic_RikoWing[] = INCBIN_U32("graphics/pokemon/riko_wing/front.4bpp.smol");
const u32 gMonBackPic_RikoWing[] = INCBIN_U32("graphics/pokemon/riko_wing/back.4bpp.smol");
const u16 gMonPalette_RikoWing[] = INCBIN_U16("graphics/pokemon/riko_wing/normal.gbapal");
const u16 gMonShinyPalette_RikoWing[] = INCBIN_U16("graphics/pokemon/riko_wing/shiny.gbapal");
const u8 gMonIcon_RikoWing[] = INCBIN_U8("graphics/pokemon/riko_wing/icon.4bpp");
const u16 gMonIconPalette_RikoWing[] = INCBIN_U16("graphics/pokemon/riko_wing/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoWing[] = INCBIN_U16("graphics/pokemon/riko_wing/icon_shiny.gbapal");
const u32 gObjectEventPic_RikoWing[] = INCBIN_U32("graphics/pokemon/riko_wing/overworld.4bpp");
const u16 gOverworldPalette_RikoWing[] = INCBIN_U16("graphics/pokemon/riko_wing/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_RikoWing[] = INCBIN_U16("graphics/pokemon/riko_wing/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_RikoWing[] = {
    overworld_ascending_frames(gObjectEventPic_RikoWing, 4, 4),
};
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
const u32 gObjectEventPic_Bijuu[] = INCBIN_U32("graphics/pokemon/bijuu/overworld.4bpp");
const u16 gOverworldPalette_Bijuu[] = INCBIN_U16("graphics/pokemon/bijuu/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_Bijuu[] = INCBIN_U16("graphics/pokemon/bijuu/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_Bijuu[] = {
    overworld_ascending_frames(gObjectEventPic_Bijuu, 4, 4),
};
#endif

#if P_FAMILY_RIKO
const u32 gMonFrontPic_RikoFire[] = INCBIN_U32("graphics/pokemon/riko_fire/front.4bpp.smol");
const u32 gMonBackPic_RikoFire[] = INCBIN_U32("graphics/pokemon/riko_fire/back.4bpp.smol");
const u16 gMonPalette_RikoFire[] = INCBIN_U16("graphics/pokemon/riko_fire/normal.gbapal");
const u16 gMonShinyPalette_RikoFire[] = INCBIN_U16("graphics/pokemon/riko_fire/shiny.gbapal");
const u8 gMonIcon_RikoFire[] = INCBIN_U8("graphics/pokemon/riko_fire/icon.4bpp");
const u16 gMonIconPalette_RikoFire[] = INCBIN_U16("graphics/pokemon/riko_fire/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoFire[] = INCBIN_U16("graphics/pokemon/riko_fire/icon_shiny.gbapal");
const u32 gObjectEventPic_RikoFire[] = INCBIN_U32("graphics/pokemon/riko_fire/overworld.4bpp");
const u16 gOverworldPalette_RikoFire[] = INCBIN_U16("graphics/pokemon/riko_fire/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_RikoFire[] = INCBIN_U16("graphics/pokemon/riko_fire/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_RikoFire[] = {
    overworld_ascending_frames(gObjectEventPic_RikoFire, 4, 4),
};
const u32 gMonFrontPic_RikoWater[] = INCBIN_U32("graphics/pokemon/riko_water/front.4bpp.smol");
const u32 gMonBackPic_RikoWater[] = INCBIN_U32("graphics/pokemon/riko_water/back.4bpp.smol");
const u16 gMonPalette_RikoWater[] = INCBIN_U16("graphics/pokemon/riko_water/normal.gbapal");
const u16 gMonShinyPalette_RikoWater[] = INCBIN_U16("graphics/pokemon/riko_water/shiny.gbapal");
const u8 gMonIcon_RikoWater[] = INCBIN_U8("graphics/pokemon/riko_water/icon.4bpp");
const u16 gMonIconPalette_RikoWater[] = INCBIN_U16("graphics/pokemon/riko_water/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoWater[] = INCBIN_U16("graphics/pokemon/riko_water/icon_shiny.gbapal");
const u32 gObjectEventPic_RikoWater[] = INCBIN_U32("graphics/pokemon/riko_water/overworld.4bpp");
const u16 gOverworldPalette_RikoWater[] = INCBIN_U16("graphics/pokemon/riko_water/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_RikoWater[] = INCBIN_U16("graphics/pokemon/riko_water/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_RikoWater[] = {
    overworld_ascending_frames(gObjectEventPic_RikoWater, 4, 4),
};
const u32 gMonFrontPic_RikoGrass[] = INCBIN_U32("graphics/pokemon/riko_grass/front.4bpp.smol");
const u32 gMonBackPic_RikoGrass[] = INCBIN_U32("graphics/pokemon/riko_grass/back.4bpp.smol");
const u16 gMonPalette_RikoGrass[] = INCBIN_U16("graphics/pokemon/riko_grass/normal.gbapal");
const u16 gMonShinyPalette_RikoGrass[] = INCBIN_U16("graphics/pokemon/riko_grass/shiny.gbapal");
const u8 gMonIcon_RikoGrass[] = INCBIN_U8("graphics/pokemon/riko_grass/icon.4bpp");
const u16 gMonIconPalette_RikoGrass[] = INCBIN_U16("graphics/pokemon/riko_grass/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoGrass[] = INCBIN_U16("graphics/pokemon/riko_grass/icon_shiny.gbapal");
const u32 gObjectEventPic_RikoGrass[] = INCBIN_U32("graphics/pokemon/riko_grass/overworld.4bpp");
const u16 gOverworldPalette_RikoGrass[] = INCBIN_U16("graphics/pokemon/riko_grass/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_RikoGrass[] = INCBIN_U16("graphics/pokemon/riko_grass/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_RikoGrass[] = {
    overworld_ascending_frames(gObjectEventPic_RikoGrass, 4, 4),
};
const u32 gMonFrontPic_RikoElectric[] = INCBIN_U32("graphics/pokemon/riko_electric/front.4bpp.smol");
const u32 gMonBackPic_RikoElectric[] = INCBIN_U32("graphics/pokemon/riko_electric/back.4bpp.smol");
const u16 gMonPalette_RikoElectric[] = INCBIN_U16("graphics/pokemon/riko_electric/normal.gbapal");
const u16 gMonShinyPalette_RikoElectric[] = INCBIN_U16("graphics/pokemon/riko_electric/shiny.gbapal");
const u8 gMonIcon_RikoElectric[] = INCBIN_U8("graphics/pokemon/riko_electric/icon.4bpp");
const u16 gMonIconPalette_RikoElectric[] = INCBIN_U16("graphics/pokemon/riko_electric/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoElectric[] = INCBIN_U16("graphics/pokemon/riko_electric/icon_shiny.gbapal");
const u32 gObjectEventPic_RikoElectric[] = INCBIN_U32("graphics/pokemon/riko_electric/overworld.4bpp");
const u16 gOverworldPalette_RikoElectric[] = INCBIN_U16("graphics/pokemon/riko_electric/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_RikoElectric[] = INCBIN_U16("graphics/pokemon/riko_electric/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_RikoElectric[] = {
    overworld_ascending_frames(gObjectEventPic_RikoElectric, 4, 4),
};
const u32 gMonFrontPic_RikoIce[] = INCBIN_U32("graphics/pokemon/riko_ice/front.4bpp.smol");
const u32 gMonBackPic_RikoIce[] = INCBIN_U32("graphics/pokemon/riko_ice/back.4bpp.smol");
const u16 gMonPalette_RikoIce[] = INCBIN_U16("graphics/pokemon/riko_ice/normal.gbapal");
const u16 gMonShinyPalette_RikoIce[] = INCBIN_U16("graphics/pokemon/riko_ice/shiny.gbapal");
const u8 gMonIcon_RikoIce[] = INCBIN_U8("graphics/pokemon/riko_ice/icon.4bpp");
const u16 gMonIconPalette_RikoIce[] = INCBIN_U16("graphics/pokemon/riko_ice/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoIce[] = INCBIN_U16("graphics/pokemon/riko_ice/icon_shiny.gbapal");
const u32 gObjectEventPic_RikoIce[] = INCBIN_U32("graphics/pokemon/riko_ice/overworld.4bpp");
const u16 gOverworldPalette_RikoIce[] = INCBIN_U16("graphics/pokemon/riko_ice/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_RikoIce[] = INCBIN_U16("graphics/pokemon/riko_ice/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_RikoIce[] = {
    overworld_ascending_frames(gObjectEventPic_RikoIce, 4, 4),
};
const u32 gMonFrontPic_RikoPsychic[] = INCBIN_U32("graphics/pokemon/riko_psychic/front.4bpp.smol");
const u32 gMonBackPic_RikoPsychic[] = INCBIN_U32("graphics/pokemon/riko_psychic/back.4bpp.smol");
const u16 gMonPalette_RikoPsychic[] = INCBIN_U16("graphics/pokemon/riko_psychic/normal.gbapal");
const u16 gMonShinyPalette_RikoPsychic[] = INCBIN_U16("graphics/pokemon/riko_psychic/shiny.gbapal");
const u8 gMonIcon_RikoPsychic[] = INCBIN_U8("graphics/pokemon/riko_psychic/icon.4bpp");
const u16 gMonIconPalette_RikoPsychic[] = INCBIN_U16("graphics/pokemon/riko_psychic/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoPsychic[] = INCBIN_U16("graphics/pokemon/riko_psychic/icon_shiny.gbapal");
const u32 gObjectEventPic_RikoPsychic[] = INCBIN_U32("graphics/pokemon/riko_psychic/overworld.4bpp");
const u16 gOverworldPalette_RikoPsychic[] = INCBIN_U16("graphics/pokemon/riko_psychic/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_RikoPsychic[] = INCBIN_U16("graphics/pokemon/riko_psychic/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_RikoPsychic[] = {
    overworld_ascending_frames(gObjectEventPic_RikoPsychic, 4, 4),
};
const u32 gMonFrontPic_RikoFlying[] = INCBIN_U32("graphics/pokemon/riko_flying/front.4bpp.smol");
const u32 gMonBackPic_RikoFlying[] = INCBIN_U32("graphics/pokemon/riko_flying/back.4bpp.smol");
const u16 gMonPalette_RikoFlying[] = INCBIN_U16("graphics/pokemon/riko_flying/normal.gbapal");
const u16 gMonShinyPalette_RikoFlying[] = INCBIN_U16("graphics/pokemon/riko_flying/shiny.gbapal");
const u8 gMonIcon_RikoFlying[] = INCBIN_U8("graphics/pokemon/riko_flying/icon.4bpp");
const u16 gMonIconPalette_RikoFlying[] = INCBIN_U16("graphics/pokemon/riko_flying/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoFlying[] = INCBIN_U16("graphics/pokemon/riko_flying/icon_shiny.gbapal");
const u32 gObjectEventPic_RikoFlying[] = INCBIN_U32("graphics/pokemon/riko_flying/overworld.4bpp");
const u16 gOverworldPalette_RikoFlying[] = INCBIN_U16("graphics/pokemon/riko_flying/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_RikoFlying[] = INCBIN_U16("graphics/pokemon/riko_flying/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_RikoFlying[] = {
    overworld_ascending_frames(gObjectEventPic_RikoFlying, 4, 4),
};
const u32 gMonFrontPic_RikoDragon[] = INCBIN_U32("graphics/pokemon/riko_dragon/front.4bpp.smol");
const u32 gMonBackPic_RikoDragon[] = INCBIN_U32("graphics/pokemon/riko_dragon/back.4bpp.smol");
const u16 gMonPalette_RikoDragon[] = INCBIN_U16("graphics/pokemon/riko_dragon/normal.gbapal");
const u16 gMonShinyPalette_RikoDragon[] = INCBIN_U16("graphics/pokemon/riko_dragon/shiny.gbapal");
const u8 gMonIcon_RikoDragon[] = INCBIN_U8("graphics/pokemon/riko_dragon/icon.4bpp");
const u16 gMonIconPalette_RikoDragon[] = INCBIN_U16("graphics/pokemon/riko_dragon/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoDragon[] = INCBIN_U16("graphics/pokemon/riko_dragon/icon_shiny.gbapal");
const u32 gObjectEventPic_RikoDragon[] = INCBIN_U32("graphics/pokemon/riko_dragon/overworld.4bpp");
const u16 gOverworldPalette_RikoDragon[] = INCBIN_U16("graphics/pokemon/riko_dragon/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_RikoDragon[] = INCBIN_U16("graphics/pokemon/riko_dragon/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_RikoDragon[] = {
    overworld_ascending_frames(gObjectEventPic_RikoDragon, 4, 4),
};
#endif
#if P_FAMILY_BIJUU
const u32 gMonFrontPic_BijuuFighting[] = INCBIN_U32("graphics/pokemon/bijuu_fighting/front.4bpp.smol");
const u32 gMonBackPic_BijuuFighting[] = INCBIN_U32("graphics/pokemon/bijuu_fighting/back.4bpp.smol");
const u16 gMonPalette_BijuuFighting[] = INCBIN_U16("graphics/pokemon/bijuu_fighting/normal.gbapal");
const u16 gMonShinyPalette_BijuuFighting[] = INCBIN_U16("graphics/pokemon/bijuu_fighting/shiny.gbapal");
const u8 gMonIcon_BijuuFighting[] = INCBIN_U8("graphics/pokemon/bijuu_fighting/icon.4bpp");
const u16 gMonIconPalette_BijuuFighting[] = INCBIN_U16("graphics/pokemon/bijuu_fighting/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuFighting[] = INCBIN_U16("graphics/pokemon/bijuu_fighting/icon_shiny.gbapal");
const u32 gObjectEventPic_BijuuFighting[] = INCBIN_U32("graphics/pokemon/bijuu_fighting/overworld.4bpp");
const u16 gOverworldPalette_BijuuFighting[] = INCBIN_U16("graphics/pokemon/bijuu_fighting/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_BijuuFighting[] = INCBIN_U16("graphics/pokemon/bijuu_fighting/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_BijuuFighting[] = {
    overworld_ascending_frames(gObjectEventPic_BijuuFighting, 4, 4),
};
const u32 gMonFrontPic_BijuuPoison[] = INCBIN_U32("graphics/pokemon/bijuu_poison/front.4bpp.smol");
const u32 gMonBackPic_BijuuPoison[] = INCBIN_U32("graphics/pokemon/bijuu_poison/back.4bpp.smol");
const u16 gMonPalette_BijuuPoison[] = INCBIN_U16("graphics/pokemon/bijuu_poison/normal.gbapal");
const u16 gMonShinyPalette_BijuuPoison[] = INCBIN_U16("graphics/pokemon/bijuu_poison/shiny.gbapal");
const u8 gMonIcon_BijuuPoison[] = INCBIN_U8("graphics/pokemon/bijuu_poison/icon.4bpp");
const u16 gMonIconPalette_BijuuPoison[] = INCBIN_U16("graphics/pokemon/bijuu_poison/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuPoison[] = INCBIN_U16("graphics/pokemon/bijuu_poison/icon_shiny.gbapal");
const u32 gObjectEventPic_BijuuPoison[] = INCBIN_U32("graphics/pokemon/bijuu_poison/overworld.4bpp");
const u16 gOverworldPalette_BijuuPoison[] = INCBIN_U16("graphics/pokemon/bijuu_poison/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_BijuuPoison[] = INCBIN_U16("graphics/pokemon/bijuu_poison/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_BijuuPoison[] = {
    overworld_ascending_frames(gObjectEventPic_BijuuPoison, 4, 4),
};
const u32 gMonFrontPic_BijuuGround[] = INCBIN_U32("graphics/pokemon/bijuu_ground/front.4bpp.smol");
const u32 gMonBackPic_BijuuGround[] = INCBIN_U32("graphics/pokemon/bijuu_ground/back.4bpp.smol");
const u16 gMonPalette_BijuuGround[] = INCBIN_U16("graphics/pokemon/bijuu_ground/normal.gbapal");
const u16 gMonShinyPalette_BijuuGround[] = INCBIN_U16("graphics/pokemon/bijuu_ground/shiny.gbapal");
const u8 gMonIcon_BijuuGround[] = INCBIN_U8("graphics/pokemon/bijuu_ground/icon.4bpp");
const u16 gMonIconPalette_BijuuGround[] = INCBIN_U16("graphics/pokemon/bijuu_ground/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuGround[] = INCBIN_U16("graphics/pokemon/bijuu_ground/icon_shiny.gbapal");
const u32 gObjectEventPic_BijuuGround[] = INCBIN_U32("graphics/pokemon/bijuu_ground/overworld.4bpp");
const u16 gOverworldPalette_BijuuGround[] = INCBIN_U16("graphics/pokemon/bijuu_ground/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_BijuuGround[] = INCBIN_U16("graphics/pokemon/bijuu_ground/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_BijuuGround[] = {
    overworld_ascending_frames(gObjectEventPic_BijuuGround, 4, 4),
};
const u32 gMonFrontPic_BijuuRock[] = INCBIN_U32("graphics/pokemon/bijuu_rock/front.4bpp.smol");
const u32 gMonBackPic_BijuuRock[] = INCBIN_U32("graphics/pokemon/bijuu_rock/back.4bpp.smol");
const u16 gMonPalette_BijuuRock[] = INCBIN_U16("graphics/pokemon/bijuu_rock/normal.gbapal");
const u16 gMonShinyPalette_BijuuRock[] = INCBIN_U16("graphics/pokemon/bijuu_rock/shiny.gbapal");
const u8 gMonIcon_BijuuRock[] = INCBIN_U8("graphics/pokemon/bijuu_rock/icon.4bpp");
const u16 gMonIconPalette_BijuuRock[] = INCBIN_U16("graphics/pokemon/bijuu_rock/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuRock[] = INCBIN_U16("graphics/pokemon/bijuu_rock/icon_shiny.gbapal");
const u32 gObjectEventPic_BijuuRock[] = INCBIN_U32("graphics/pokemon/bijuu_rock/overworld.4bpp");
const u16 gOverworldPalette_BijuuRock[] = INCBIN_U16("graphics/pokemon/bijuu_rock/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_BijuuRock[] = INCBIN_U16("graphics/pokemon/bijuu_rock/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_BijuuRock[] = {
    overworld_ascending_frames(gObjectEventPic_BijuuRock, 4, 4),
};
const u32 gMonFrontPic_BijuuBug[] = INCBIN_U32("graphics/pokemon/bijuu_bug/front.4bpp.smol");
const u32 gMonBackPic_BijuuBug[] = INCBIN_U32("graphics/pokemon/bijuu_bug/back.4bpp.smol");
const u16 gMonPalette_BijuuBug[] = INCBIN_U16("graphics/pokemon/bijuu_bug/normal.gbapal");
const u16 gMonShinyPalette_BijuuBug[] = INCBIN_U16("graphics/pokemon/bijuu_bug/shiny.gbapal");
const u8 gMonIcon_BijuuBug[] = INCBIN_U8("graphics/pokemon/bijuu_bug/icon.4bpp");
const u16 gMonIconPalette_BijuuBug[] = INCBIN_U16("graphics/pokemon/bijuu_bug/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuBug[] = INCBIN_U16("graphics/pokemon/bijuu_bug/icon_shiny.gbapal");
const u32 gObjectEventPic_BijuuBug[] = INCBIN_U32("graphics/pokemon/bijuu_bug/overworld.4bpp");
const u16 gOverworldPalette_BijuuBug[] = INCBIN_U16("graphics/pokemon/bijuu_bug/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_BijuuBug[] = INCBIN_U16("graphics/pokemon/bijuu_bug/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_BijuuBug[] = {
    overworld_ascending_frames(gObjectEventPic_BijuuBug, 4, 4),
};
const u32 gMonFrontPic_BijuuGhost[] = INCBIN_U32("graphics/pokemon/bijuu_ghost/front.4bpp.smol");
const u32 gMonBackPic_BijuuGhost[] = INCBIN_U32("graphics/pokemon/bijuu_ghost/back.4bpp.smol");
const u16 gMonPalette_BijuuGhost[] = INCBIN_U16("graphics/pokemon/bijuu_ghost/normal.gbapal");
const u16 gMonShinyPalette_BijuuGhost[] = INCBIN_U16("graphics/pokemon/bijuu_ghost/shiny.gbapal");
const u8 gMonIcon_BijuuGhost[] = INCBIN_U8("graphics/pokemon/bijuu_ghost/icon.4bpp");
const u16 gMonIconPalette_BijuuGhost[] = INCBIN_U16("graphics/pokemon/bijuu_ghost/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuGhost[] = INCBIN_U16("graphics/pokemon/bijuu_ghost/icon_shiny.gbapal");
const u32 gObjectEventPic_BijuuGhost[] = INCBIN_U32("graphics/pokemon/bijuu_ghost/overworld.4bpp");
const u16 gOverworldPalette_BijuuGhost[] = INCBIN_U16("graphics/pokemon/bijuu_ghost/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_BijuuGhost[] = INCBIN_U16("graphics/pokemon/bijuu_ghost/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_BijuuGhost[] = {
    overworld_ascending_frames(gObjectEventPic_BijuuGhost, 4, 4),
};
const u32 gMonFrontPic_BijuuDark[] = INCBIN_U32("graphics/pokemon/bijuu_dark/front.4bpp.smol");
const u32 gMonBackPic_BijuuDark[] = INCBIN_U32("graphics/pokemon/bijuu_dark/back.4bpp.smol");
const u16 gMonPalette_BijuuDark[] = INCBIN_U16("graphics/pokemon/bijuu_dark/normal.gbapal");
const u16 gMonShinyPalette_BijuuDark[] = INCBIN_U16("graphics/pokemon/bijuu_dark/shiny.gbapal");
const u8 gMonIcon_BijuuDark[] = INCBIN_U8("graphics/pokemon/bijuu_dark/icon.4bpp");
const u16 gMonIconPalette_BijuuDark[] = INCBIN_U16("graphics/pokemon/bijuu_dark/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuDark[] = INCBIN_U16("graphics/pokemon/bijuu_dark/icon_shiny.gbapal");
const u32 gObjectEventPic_BijuuDark[] = INCBIN_U32("graphics/pokemon/bijuu_dark/overworld.4bpp");
const u16 gOverworldPalette_BijuuDark[] = INCBIN_U16("graphics/pokemon/bijuu_dark/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_BijuuDark[] = INCBIN_U16("graphics/pokemon/bijuu_dark/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_BijuuDark[] = {
    overworld_ascending_frames(gObjectEventPic_BijuuDark, 4, 4),
};
const u32 gMonFrontPic_BijuuSteel[] = INCBIN_U32("graphics/pokemon/bijuu_steel/front.4bpp.smol");
const u32 gMonBackPic_BijuuSteel[] = INCBIN_U32("graphics/pokemon/bijuu_steel/back.4bpp.smol");
const u16 gMonPalette_BijuuSteel[] = INCBIN_U16("graphics/pokemon/bijuu_steel/normal.gbapal");
const u16 gMonShinyPalette_BijuuSteel[] = INCBIN_U16("graphics/pokemon/bijuu_steel/shiny.gbapal");
const u8 gMonIcon_BijuuSteel[] = INCBIN_U8("graphics/pokemon/bijuu_steel/icon.4bpp");
const u16 gMonIconPalette_BijuuSteel[] = INCBIN_U16("graphics/pokemon/bijuu_steel/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuSteel[] = INCBIN_U16("graphics/pokemon/bijuu_steel/icon_shiny.gbapal");
const u32 gObjectEventPic_BijuuSteel[] = INCBIN_U32("graphics/pokemon/bijuu_steel/overworld.4bpp");
const u16 gOverworldPalette_BijuuSteel[] = INCBIN_U16("graphics/pokemon/bijuu_steel/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_BijuuSteel[] = INCBIN_U16("graphics/pokemon/bijuu_steel/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_BijuuSteel[] = {
    overworld_ascending_frames(gObjectEventPic_BijuuSteel, 4, 4),
};
const u32 gMonFrontPic_BijuuPsychic[] = INCBIN_U32("graphics/pokemon/bijuu_psychic/front.4bpp.smol");
const u32 gMonBackPic_BijuuPsychic[] = INCBIN_U32("graphics/pokemon/bijuu_psychic/back.4bpp.smol");
const u16 gMonPalette_BijuuPsychic[] = INCBIN_U16("graphics/pokemon/bijuu_psychic/normal.gbapal");
const u16 gMonShinyPalette_BijuuPsychic[] = INCBIN_U16("graphics/pokemon/bijuu_psychic/shiny.gbapal");
const u8 gMonIcon_BijuuPsychic[] = INCBIN_U8("graphics/pokemon/bijuu_psychic/icon.4bpp");
const u16 gMonIconPalette_BijuuPsychic[] = INCBIN_U16("graphics/pokemon/bijuu_psychic/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuPsychic[] = INCBIN_U16("graphics/pokemon/bijuu_psychic/icon_shiny.gbapal");
const u32 gObjectEventPic_BijuuPsychic[] = INCBIN_U32("graphics/pokemon/bijuu_psychic/overworld.4bpp");
const u16 gOverworldPalette_BijuuPsychic[] = INCBIN_U16("graphics/pokemon/bijuu_psychic/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_BijuuPsychic[] = INCBIN_U16("graphics/pokemon/bijuu_psychic/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_BijuuPsychic[] = {
    overworld_ascending_frames(gObjectEventPic_BijuuPsychic, 4, 4),
};
#endif
#if P_FAMILY_RIKO
const u32 gMonFrontPic_RikoMega[] = INCBIN_U32("graphics/pokemon/riko/mega/front.4bpp.smol");
const u32 gMonBackPic_RikoMega[] = INCBIN_U32("graphics/pokemon/riko/mega/back.4bpp.smol");
const u16 gMonPalette_RikoMega[] = INCBIN_U16("graphics/pokemon/riko/mega/normal.gbapal");
const u16 gMonShinyPalette_RikoMega[] = INCBIN_U16("graphics/pokemon/riko/mega/shiny.gbapal");
#endif

#if P_FAMILY_RIKO
const u32 gMonFrontPic_RikoSpirit[] = INCBIN_U32("graphics/pokemon/riko_spirit/front.4bpp.smol");
const u32 gMonBackPic_RikoSpirit[] = INCBIN_U32("graphics/pokemon/riko_spirit/back.4bpp.smol");
const u16 gMonPalette_RikoSpirit[] = INCBIN_U16("graphics/pokemon/riko_spirit/normal.gbapal");
const u16 gMonShinyPalette_RikoSpirit[] = INCBIN_U16("graphics/pokemon/riko_spirit/shiny.gbapal");
const u8 gMonIcon_RikoSpirit[] = INCBIN_U8("graphics/pokemon/riko_spirit/icon.4bpp");
const u16 gMonIconPalette_RikoSpirit[] = INCBIN_U16("graphics/pokemon/riko_spirit/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoSpirit[] = INCBIN_U16("graphics/pokemon/riko_spirit/icon_shiny.gbapal");
const u32 gObjectEventPic_RikoSpirit[] = INCBIN_U32("graphics/pokemon/riko_spirit/overworld.4bpp");
const u16 gOverworldPalette_RikoSpirit[] = INCBIN_U16("graphics/pokemon/riko_spirit/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_RikoSpirit[] = INCBIN_U16("graphics/pokemon/riko_spirit/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_RikoSpirit[] = {
    overworld_ascending_frames(gObjectEventPic_RikoSpirit, 4, 4),
};
static const struct LevelUpMove sRikoSpiritLevelUpLearnset[] = {
    LEVEL_UP_MOVE( 1, MOVE_BITE),
    LEVEL_UP_MOVE( 1, MOVE_LEER),
    LEVEL_UP_MOVE(11, MOVE_EMBER),
    LEVEL_UP_MOVE(21, MOVE_ROAR),
    LEVEL_UP_MOVE(31, MOVE_FIRE_SPIN),
    LEVEL_UP_MOVE(41, MOVE_STOMP),
    LEVEL_UP_MOVE(51, MOVE_FLAMETHROWER),
    LEVEL_UP_MOVE(61, MOVE_SWAGGER),
    LEVEL_UP_MOVE(71, MOVE_FIRE_BLAST),
    LEVEL_UP_END
};
#endif


#if P_FAMILY_FIDOUGH
const u32 gMonFrontPic_PennyGuardian[] = INCBIN_U32("graphics/pokemon/penny_guardian/front.4bpp.smol");
const u32 gMonBackPic_PennyGuardian[] = INCBIN_U32("graphics/pokemon/penny_guardian/back.4bpp.smol");
const u16 gMonPalette_PennyGuardian[] = INCBIN_U16("graphics/pokemon/penny_guardian/normal.gbapal");
const u16 gMonShinyPalette_PennyGuardian[] = INCBIN_U16("graphics/pokemon/penny_guardian/shiny.gbapal");
const u8 gMonIcon_PennyGuardian[] = INCBIN_U8("graphics/pokemon/penny_guardian/icon.4bpp");
const u16 gMonIconPalette_PennyGuardian[] = INCBIN_U16("graphics/pokemon/penny_guardian/icon_normal.gbapal");
const u16 gMonShinyIconPalette_PennyGuardian[] = INCBIN_U16("graphics/pokemon/penny_guardian/icon_shiny.gbapal");
const u32 gObjectEventPic_PennyGuardian[] = INCBIN_U32("graphics/pokemon/penny_guardian/overworld.4bpp");
const u16 gOverworldPalette_PennyGuardian[] = INCBIN_U16("graphics/pokemon/penny_guardian/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_PennyGuardian[] = INCBIN_U16("graphics/pokemon/penny_guardian/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_PennyGuardian[] = {
    overworld_ascending_frames(gObjectEventPic_PennyGuardian, 4, 4),
};
#endif


#if P_FAMILY_BIJUU
const u32 gMonFrontPic_BijuuIce[] = INCBIN_U32("graphics/pokemon/bijuu_ice/front.4bpp.smol");
const u32 gMonBackPic_BijuuIce[] = INCBIN_U32("graphics/pokemon/bijuu_ice/back.4bpp.smol");
const u16 gMonPalette_BijuuIce[] = INCBIN_U16("graphics/pokemon/bijuu_ice/normal.gbapal");
const u16 gMonShinyPalette_BijuuIce[] = INCBIN_U16("graphics/pokemon/bijuu_ice/shiny.gbapal");
const u8 gMonIcon_BijuuIce[] = INCBIN_U8("graphics/pokemon/bijuu_ice/icon.4bpp");
const u16 gMonIconPalette_BijuuIce[] = INCBIN_U16("graphics/pokemon/bijuu_ice/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuIce[] = INCBIN_U16("graphics/pokemon/bijuu_ice/icon_shiny.gbapal");
const u32 gObjectEventPic_BijuuIce[] = INCBIN_U32("graphics/pokemon/bijuu_ice/overworld.4bpp");
const u16 gOverworldPalette_BijuuIce[] = INCBIN_U16("graphics/pokemon/bijuu_ice/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_BijuuIce[] = INCBIN_U16("graphics/pokemon/bijuu_ice/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_BijuuIce[] = {
    overworld_ascending_frames(gObjectEventPic_BijuuIce, 4, 4),
};

#endif

#if P_FAMILY_FIDOUGH
const u32 gMonFrontPic_PennyWater[] = INCBIN_U32("graphics/pokemon/penny_water/front.4bpp.smol");
const u32 gMonBackPic_PennyWater[] = INCBIN_U32("graphics/pokemon/penny_water/back.4bpp.smol");
const u16 gMonPalette_PennyWater[] = INCBIN_U16("graphics/pokemon/penny_water/normal.gbapal");
const u16 gMonShinyPalette_PennyWater[] = INCBIN_U16("graphics/pokemon/penny_water/shiny.gbapal");
const u8 gMonIcon_PennyWater[] = INCBIN_U8("graphics/pokemon/penny_water/icon.4bpp");
const u16 gMonIconPalette_PennyWater[] = INCBIN_U16("graphics/pokemon/penny_water/icon_normal.gbapal");
const u16 gMonShinyIconPalette_PennyWater[] = INCBIN_U16("graphics/pokemon/penny_water/icon_shiny.gbapal");
const u32 gObjectEventPic_PennyWater[] = INCBIN_U32("graphics/pokemon/penny_water/overworld.4bpp");
const u16 gOverworldPalette_PennyWater[] = INCBIN_U16("graphics/pokemon/penny_water/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_PennyWater[] = INCBIN_U16("graphics/pokemon/penny_water/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_PennyWater[] = {
    overworld_ascending_frames(gObjectEventPic_PennyWater, 4, 4),
};

const u32 gMonFrontPic_PennyGrass[] = INCBIN_U32("graphics/pokemon/penny_grass/front.4bpp.smol");
const u32 gMonBackPic_PennyGrass[] = INCBIN_U32("graphics/pokemon/penny_grass/back.4bpp.smol");
const u16 gMonPalette_PennyGrass[] = INCBIN_U16("graphics/pokemon/penny_grass/normal.gbapal");
const u16 gMonShinyPalette_PennyGrass[] = INCBIN_U16("graphics/pokemon/penny_grass/shiny.gbapal");
const u8 gMonIcon_PennyGrass[] = INCBIN_U8("graphics/pokemon/penny_grass/icon.4bpp");
const u16 gMonIconPalette_PennyGrass[] = INCBIN_U16("graphics/pokemon/penny_grass/icon_normal.gbapal");
const u16 gMonShinyIconPalette_PennyGrass[] = INCBIN_U16("graphics/pokemon/penny_grass/icon_shiny.gbapal");
const u32 gObjectEventPic_PennyGrass[] = INCBIN_U32("graphics/pokemon/penny_grass/overworld.4bpp");
const u16 gOverworldPalette_PennyGrass[] = INCBIN_U16("graphics/pokemon/penny_grass/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_PennyGrass[] = INCBIN_U16("graphics/pokemon/penny_grass/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_PennyGrass[] = {
    overworld_ascending_frames(gObjectEventPic_PennyGrass, 4, 4),
};

#endif

#if P_FAMILY_FIDOUGH
const u32 gMonFrontPic_PennySpirit[] = INCBIN_U32("graphics/pokemon/penny_spirit/front.4bpp.smol");
const u32 gMonBackPic_PennySpirit[] = INCBIN_U32("graphics/pokemon/penny_spirit/back.4bpp.smol");
const u16 gMonPalette_PennySpirit[] = INCBIN_U16("graphics/pokemon/penny_spirit/normal.gbapal");
const u16 gMonShinyPalette_PennySpirit[] = INCBIN_U16("graphics/pokemon/penny_spirit/shiny.gbapal");
const u8 gMonIcon_PennySpirit[] = INCBIN_U8("graphics/pokemon/penny_spirit/icon.4bpp");
const u16 gMonIconPalette_PennySpirit[] = INCBIN_U16("graphics/pokemon/penny_spirit/icon_normal.gbapal");
const u16 gMonShinyIconPalette_PennySpirit[] = INCBIN_U16("graphics/pokemon/penny_spirit/icon_shiny.gbapal");
const u32 gObjectEventPic_PennySpirit[] = INCBIN_U32("graphics/pokemon/penny_spirit/overworld.4bpp");
const u16 gOverworldPalette_PennySpirit[] = INCBIN_U16("graphics/pokemon/penny_spirit/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_PennySpirit[] = INCBIN_U16("graphics/pokemon/penny_spirit/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_PennySpirit[] = {
    overworld_ascending_frames(gObjectEventPic_PennySpirit, 4, 4),
};
static const struct LevelUpMove sPennySpiritLevelUpLearnset[] = {
    LEVEL_UP_MOVE(1, MOVE_TACKLE),
    LEVEL_UP_MOVE(1, MOVE_FAIRY_WIND),
    LEVEL_UP_MOVE(1, MOVE_METAL_CLAW),
    LEVEL_UP_MOVE(1, MOVE_CHARM),
    LEVEL_UP_MOVE(20, MOVE_IRON_HEAD),
    LEVEL_UP_MOVE(20, MOVE_PLAY_ROUGH),
    LEVEL_UP_MOVE(20, MOVE_BABY_DOLL_EYES),
    LEVEL_UP_MOVE(20, MOVE_PROTECT),
    LEVEL_UP_END
};
#endif

#if P_FAMILY_BIJUU
const u32 gMonFrontPic_BijuuSpirit[] = INCBIN_U32("graphics/pokemon/bijuu_spirit/front.4bpp.smol");
const u32 gMonBackPic_BijuuSpirit[] = INCBIN_U32("graphics/pokemon/bijuu_spirit/back.4bpp.smol");
const u16 gMonPalette_BijuuSpirit[] = INCBIN_U16("graphics/pokemon/bijuu_spirit/normal.gbapal");
const u16 gMonShinyPalette_BijuuSpirit[] = INCBIN_U16("graphics/pokemon/bijuu_spirit/shiny.gbapal");
const u8 gMonIcon_BijuuSpirit[] = INCBIN_U8("graphics/pokemon/bijuu_spirit/icon.4bpp");
const u16 gMonIconPalette_BijuuSpirit[] = INCBIN_U16("graphics/pokemon/bijuu_spirit/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuSpirit[] = INCBIN_U16("graphics/pokemon/bijuu_spirit/icon_shiny.gbapal");
const u32 gObjectEventPic_BijuuSpirit[] = INCBIN_U32("graphics/pokemon/bijuu_spirit/overworld.4bpp");
const u16 gOverworldPalette_BijuuSpirit[] = INCBIN_U16("graphics/pokemon/bijuu_spirit/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_BijuuSpirit[] = INCBIN_U16("graphics/pokemon/bijuu_spirit/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_BijuuSpirit[] = {
    overworld_ascending_frames(gObjectEventPic_BijuuSpirit, 4, 4),
};
static const struct LevelUpMove sBijuuSpiritLevelUpLearnset[] = {
    LEVEL_UP_MOVE(1, MOVE_CONFUSION),
    LEVEL_UP_MOVE(1, MOVE_ASTONISH),
    LEVEL_UP_MOVE(1, MOVE_DISABLE),
    LEVEL_UP_MOVE(1, MOVE_QUICK_ATTACK),
    LEVEL_UP_MOVE(20, MOVE_SHADOW_BALL),
    LEVEL_UP_MOVE(20, MOVE_PSYBEAM),
    LEVEL_UP_MOVE(20, MOVE_CONFUSE_RAY),
    LEVEL_UP_MOVE(20, MOVE_SWIFT),
    LEVEL_UP_END
};
#endif

#if P_FAMILY_RIKO
const u32 gMonFrontPic_RikoEcho[] = INCBIN_U32("graphics/pokemon/riko_echo/front.4bpp.smol");
const u32 gMonBackPic_RikoEcho[] = INCBIN_U32("graphics/pokemon/riko_echo/back.4bpp.smol");
const u16 gMonPalette_RikoEcho[] = INCBIN_U16("graphics/pokemon/riko_echo/normal.gbapal");
const u16 gMonShinyPalette_RikoEcho[] = INCBIN_U16("graphics/pokemon/riko_echo/shiny.gbapal");
const u8 gMonIcon_RikoEcho[] = INCBIN_U8("graphics/pokemon/riko_echo/icon.4bpp");
const u16 gMonIconPalette_RikoEcho[] = INCBIN_U16("graphics/pokemon/riko_echo/icon_normal.gbapal");
const u16 gMonShinyIconPalette_RikoEcho[] = INCBIN_U16("graphics/pokemon/riko_echo/icon_shiny.gbapal");
const u32 gObjectEventPic_RikoEcho[] = INCBIN_U32("graphics/pokemon/riko_echo/overworld.4bpp");
const u16 gOverworldPalette_RikoEcho[] = INCBIN_U16("graphics/pokemon/riko_echo/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_RikoEcho[] = INCBIN_U16("graphics/pokemon/riko_echo/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_RikoEcho[] = {
    overworld_ascending_frames(gObjectEventPic_RikoEcho, 4, 4),
};
static const struct LevelUpMove sRikoEchoLevelUpLearnset[] = {
    LEVEL_UP_MOVE(0, MOVE_ECHOED_VOICE),
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
const u32 gMonFrontPic_BijuuEmber[] = INCBIN_U32("graphics/pokemon/bijuu_ember/front.4bpp.smol");
const u32 gMonBackPic_BijuuEmber[] = INCBIN_U32("graphics/pokemon/bijuu_ember/back.4bpp.smol");
const u16 gMonPalette_BijuuEmber[] = INCBIN_U16("graphics/pokemon/bijuu_ember/normal.gbapal");
const u16 gMonShinyPalette_BijuuEmber[] = INCBIN_U16("graphics/pokemon/bijuu_ember/shiny.gbapal");
const u8 gMonIcon_BijuuEmber[] = INCBIN_U8("graphics/pokemon/bijuu_ember/icon.4bpp");
const u16 gMonIconPalette_BijuuEmber[] = INCBIN_U16("graphics/pokemon/bijuu_ember/icon_normal.gbapal");
const u16 gMonShinyIconPalette_BijuuEmber[] = INCBIN_U16("graphics/pokemon/bijuu_ember/icon_shiny.gbapal");
const u32 gObjectEventPic_BijuuEmber[] = INCBIN_U32("graphics/pokemon/bijuu_ember/overworld.4bpp");
const u16 gOverworldPalette_BijuuEmber[] = INCBIN_U16("graphics/pokemon/bijuu_ember/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_BijuuEmber[] = INCBIN_U16("graphics/pokemon/bijuu_ember/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_BijuuEmber[] = {
    overworld_ascending_frames(gObjectEventPic_BijuuEmber, 4, 4),
};
static const struct LevelUpMove sBijuuEmberLevelUpLearnset[] = {
    LEVEL_UP_MOVE(0, MOVE_EMBER),
    LEVEL_UP_MOVE(1, MOVE_SCRATCH),
    LEVEL_UP_MOVE(1, MOVE_GROWL),
    LEVEL_UP_MOVE(6, MOVE_BITE),
    LEVEL_UP_MOVE(9, MOVE_FAKE_OUT),
    LEVEL_UP_MOVE(14, MOVE_FLAME_CHARGE),
    LEVEL_UP_MOVE(17, MOVE_SCREECH),
    LEVEL_UP_MOVE(22, MOVE_FEINT_ATTACK),
    LEVEL_UP_MOVE(27, MOVE_FIRE_FANG),
    LEVEL_UP_MOVE(32, MOVE_FLAMETHROWER),
    LEVEL_UP_MOVE(38, MOVE_NASTY_PLOT),
    LEVEL_UP_MOVE(45, MOVE_HEAT_WAVE),
    LEVEL_UP_END
};
#endif

#if P_FAMILY_FIDOUGH
const u32 gMonFrontPic_PennyBrave[] = INCBIN_U32("graphics/pokemon/penny_brave/front.4bpp.smol");
const u32 gMonBackPic_PennyBrave[] = INCBIN_U32("graphics/pokemon/penny_brave/back.4bpp.smol");
const u16 gMonPalette_PennyBrave[] = INCBIN_U16("graphics/pokemon/penny_brave/normal.gbapal");
const u16 gMonShinyPalette_PennyBrave[] = INCBIN_U16("graphics/pokemon/penny_brave/shiny.gbapal");
const u8 gMonIcon_PennyBrave[] = INCBIN_U8("graphics/pokemon/penny_brave/icon.4bpp");
const u16 gMonIconPalette_PennyBrave[] = INCBIN_U16("graphics/pokemon/penny_brave/icon_normal.gbapal");
const u16 gMonShinyIconPalette_PennyBrave[] = INCBIN_U16("graphics/pokemon/penny_brave/icon_shiny.gbapal");
const u32 gObjectEventPic_PennyBrave[] = INCBIN_U32("graphics/pokemon/penny_brave/overworld.4bpp");
const u16 gOverworldPalette_PennyBrave[] = INCBIN_U16("graphics/pokemon/penny_brave/overworld_normal.gbapal");
const u16 gShinyOverworldPalette_PennyBrave[] = INCBIN_U16("graphics/pokemon/penny_brave/overworld_shiny.gbapal");
static const struct SpriteFrameImage sPicTable_PennyBrave[] = {
    overworld_ascending_frames(gObjectEventPic_PennyBrave, 4, 4),
};
static const struct LevelUpMove sPennyBraveLevelUpLearnset[] = {
    LEVEL_UP_MOVE(0, MOVE_HELPING_HAND),
    LEVEL_UP_MOVE(1, MOVE_TACKLE),
    LEVEL_UP_MOVE(1, MOVE_GROWL),
    LEVEL_UP_MOVE(5, MOVE_LICK),
    LEVEL_UP_MOVE(8, MOVE_TAIL_WHIP),
    LEVEL_UP_MOVE(12, MOVE_BITE),
    LEVEL_UP_MOVE(16, MOVE_BABY_DOLL_EYES),
    LEVEL_UP_MOVE(22, MOVE_DRAINING_KISS),
    LEVEL_UP_MOVE(28, MOVE_CRUNCH),
    LEVEL_UP_MOVE(34, MOVE_PLAY_ROUGH),
    LEVEL_UP_MOVE(40, MOVE_YAWN),
    LEVEL_UP_MOVE(46, MOVE_LAST_RESORT),
    LEVEL_UP_END
};
#endif
