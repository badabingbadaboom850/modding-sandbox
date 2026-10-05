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
static const struct LevelUpMove sBijuuLevelUpLearnset[] = {
    LEVEL_UP_MOVE(1, MOVE_SCRATCH), LEVEL_UP_MOVE(1, MOVE_GROWL),
    LEVEL_UP_MOVE(5, MOVE_FAKE_OUT), LEVEL_UP_MOVE(9, MOVE_FURY_SWIPES),
    LEVEL_UP_MOVE(13, MOVE_BITE), LEVEL_UP_MOVE(17, MOVE_PAY_DAY),
    LEVEL_UP_MOVE(21, MOVE_TAUNT), LEVEL_UP_MOVE(25, MOVE_SWIFT),
    LEVEL_UP_MOVE(29, MOVE_NASTY_PLOT), LEVEL_UP_MOVE(34, MOVE_SLASH),
    LEVEL_UP_MOVE(39, MOVE_U_TURN), LEVEL_UP_MOVE(44, MOVE_COPYCAT),
    LEVEL_UP_MOVE(49, MOVE_DOUBLE_EDGE), LEVEL_UP_MOVE(55, MOVE_MEOWTH_MIMIC), LEVEL_UP_END
};
#endif
