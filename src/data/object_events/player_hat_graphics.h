// Generated registration: preserve native frame order and animation metadata.


const u32 gObjectEventPic_MayBowNormalRunning[] = INCBIN_U32("graphics/player_hats/bow/walking.4bpp", "graphics/player_hats/bow/running.4bpp");

static const struct SpriteFrameImage sPicTable_MayBowNormal[] = {
    overworld_ascending_frames(gObjectEventPic_MayBowNormalRunning, 2, 4),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MayBowNormal = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = sOamTables_16x32,
    .anims = sAnimTable_BrendanMayNormal,
    .images = sPicTable_MayBowNormal,
};

const u32 gObjectEventPic_MayBowMachBike[] = INCBIN_U32("graphics/player_hats/bow/mach_bike.4bpp");

static const struct SpriteFrameImage sPicTable_MayBowMachBike[] = {
    overworld_ascending_frames(gObjectEventPic_MayBowMachBike, 4, 4),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MayBowMachBike = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_MayBowMachBike,
};

const u32 gObjectEventPic_MayBowAcroBike[] = INCBIN_U32("graphics/player_hats/bow/acro_bike.4bpp");

static const struct SpriteFrameImage sPicTable_MayBowAcroBike[] = {
    overworld_ascending_frames(gObjectEventPic_MayBowAcroBike, 4, 4),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MayBowAcroBike = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_AcroBike,
    .images = sPicTable_MayBowAcroBike,
};

const u32 gObjectEventPic_MayBowSurfing[] = INCBIN_U32("graphics/player_hats/bow/surfing.4bpp");

static const struct SpriteFrameImage sPicTable_MayBowSurfing[] = {
    overworld_frame(gObjectEventPic_MayBowSurfing, 4, 4, 0),
    overworld_frame(gObjectEventPic_MayBowSurfing, 4, 4, 2),
    overworld_frame(gObjectEventPic_MayBowSurfing, 4, 4, 4),
    overworld_frame(gObjectEventPic_MayBowSurfing, 4, 4, 0),
    overworld_frame(gObjectEventPic_MayBowSurfing, 4, 4, 0),
    overworld_frame(gObjectEventPic_MayBowSurfing, 4, 4, 2),
    overworld_frame(gObjectEventPic_MayBowSurfing, 4, 4, 2),
    overworld_frame(gObjectEventPic_MayBowSurfing, 4, 4, 4),
    overworld_frame(gObjectEventPic_MayBowSurfing, 4, 4, 4),
    overworld_frame(gObjectEventPic_MayBowSurfing, 4, 4, 1),
    overworld_frame(gObjectEventPic_MayBowSurfing, 4, 4, 3),
    overworld_frame(gObjectEventPic_MayBowSurfing, 4, 4, 5),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MayBowSurfing = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Surfing,
    .images = sPicTable_MayBowSurfing,
};

const u32 gObjectEventPic_MayBowFieldMove[] = INCBIN_U32("graphics/player_hats/bow/field_move.4bpp");

static const struct SpriteFrameImage sPicTable_MayBowFieldMove[] = {
    overworld_ascending_frames(gObjectEventPic_MayBowFieldMove, 4, 4),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MayBowFieldMove = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_FieldMove,
    .images = sPicTable_MayBowFieldMove,
};

const u32 gObjectEventPic_MayBowUnderwater[] = INCBIN_U32("graphics/player_hats/bow/underwater.4bpp");

static const struct SpriteFrameImage sPicTable_MayBowUnderwater[] = {
    overworld_frame(gObjectEventPic_MayBowUnderwater, 4, 4, 0),
    overworld_frame(gObjectEventPic_MayBowUnderwater, 4, 4, 1),
    overworld_frame(gObjectEventPic_MayBowUnderwater, 4, 4, 2),
    overworld_frame(gObjectEventPic_MayBowUnderwater, 4, 4, 0),
    overworld_frame(gObjectEventPic_MayBowUnderwater, 4, 4, 0),
    overworld_frame(gObjectEventPic_MayBowUnderwater, 4, 4, 1),
    overworld_frame(gObjectEventPic_MayBowUnderwater, 4, 4, 1),
    overworld_frame(gObjectEventPic_MayBowUnderwater, 4, 4, 2),
    overworld_frame(gObjectEventPic_MayBowUnderwater, 4, 4, 2),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MayBowUnderwater = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_UNDERWATER,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_MayBowUnderwater,
};

const u32 gObjectEventPic_MayBowFishing[] = INCBIN_U32("graphics/player_hats/bow/fishing.4bpp");

static const struct SpriteFrameImage sPicTable_MayBowFishing[] = {
    overworld_ascending_frames(gObjectEventPic_MayBowFishing, 4, 4),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MayBowFishing = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Fishing,
    .images = sPicTable_MayBowFishing,
};

const u32 gObjectEventPic_MayBowWatering[] = INCBIN_U32("graphics/player_hats/bow/watering.4bpp");

static const struct SpriteFrameImage sPicTable_MayBowWatering[] = {
    overworld_frame(gObjectEventPic_MayBowWatering, 4, 4, 0),
    overworld_frame(gObjectEventPic_MayBowWatering, 4, 4, 2),
    overworld_frame(gObjectEventPic_MayBowWatering, 4, 4, 4),
    overworld_frame(gObjectEventPic_MayBowWatering, 4, 4, 1),
    overworld_frame(gObjectEventPic_MayBowWatering, 4, 4, 1),
    overworld_frame(gObjectEventPic_MayBowWatering, 4, 4, 3),
    overworld_frame(gObjectEventPic_MayBowWatering, 4, 4, 3),
    overworld_frame(gObjectEventPic_MayBowWatering, 4, 4, 5),
    overworld_frame(gObjectEventPic_MayBowWatering, 4, 4, 5),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MayBowWatering = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_MayBowWatering,
};

const u32 gObjectEventPic_MayBowDecorating[] = INCBIN_U32("graphics/player_hats/bow/decorating.4bpp");

static const struct SpriteFrameImage sPicTable_MayBowDecorating[] = {
    obj_frame_tiles(gObjectEventPic_MayBowDecorating),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MayBowDecorating = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = TRUE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = sOamTables_16x32,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MayBowDecorating,
};

const u32 gObjectEventPic_MaySunhatNormalRunning[] = INCBIN_U32("graphics/player_hats/sunhat/walking.4bpp", "graphics/player_hats/sunhat/running.4bpp");

static const struct SpriteFrameImage sPicTable_MaySunhatNormal[] = {
    overworld_ascending_frames(gObjectEventPic_MaySunhatNormalRunning, 2, 4),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MaySunhatNormal = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = sOamTables_16x32,
    .anims = sAnimTable_BrendanMayNormal,
    .images = sPicTable_MaySunhatNormal,
};

const u32 gObjectEventPic_MaySunhatMachBike[] = INCBIN_U32("graphics/player_hats/sunhat/mach_bike.4bpp");

static const struct SpriteFrameImage sPicTable_MaySunhatMachBike[] = {
    overworld_ascending_frames(gObjectEventPic_MaySunhatMachBike, 4, 4),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MaySunhatMachBike = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_MaySunhatMachBike,
};

const u32 gObjectEventPic_MaySunhatAcroBike[] = INCBIN_U32("graphics/player_hats/sunhat/acro_bike.4bpp");

static const struct SpriteFrameImage sPicTable_MaySunhatAcroBike[] = {
    overworld_ascending_frames(gObjectEventPic_MaySunhatAcroBike, 4, 4),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MaySunhatAcroBike = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_BIKE_TIRE,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_AcroBike,
    .images = sPicTable_MaySunhatAcroBike,
};

const u32 gObjectEventPic_MaySunhatSurfing[] = INCBIN_U32("graphics/player_hats/sunhat/surfing.4bpp");

static const struct SpriteFrameImage sPicTable_MaySunhatSurfing[] = {
    overworld_frame(gObjectEventPic_MaySunhatSurfing, 4, 4, 0),
    overworld_frame(gObjectEventPic_MaySunhatSurfing, 4, 4, 2),
    overworld_frame(gObjectEventPic_MaySunhatSurfing, 4, 4, 4),
    overworld_frame(gObjectEventPic_MaySunhatSurfing, 4, 4, 0),
    overworld_frame(gObjectEventPic_MaySunhatSurfing, 4, 4, 0),
    overworld_frame(gObjectEventPic_MaySunhatSurfing, 4, 4, 2),
    overworld_frame(gObjectEventPic_MaySunhatSurfing, 4, 4, 2),
    overworld_frame(gObjectEventPic_MaySunhatSurfing, 4, 4, 4),
    overworld_frame(gObjectEventPic_MaySunhatSurfing, 4, 4, 4),
    overworld_frame(gObjectEventPic_MaySunhatSurfing, 4, 4, 1),
    overworld_frame(gObjectEventPic_MaySunhatSurfing, 4, 4, 3),
    overworld_frame(gObjectEventPic_MaySunhatSurfing, 4, 4, 5),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MaySunhatSurfing = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Surfing,
    .images = sPicTable_MaySunhatSurfing,
};

const u32 gObjectEventPic_MaySunhatFieldMove[] = INCBIN_U32("graphics/player_hats/sunhat/field_move.4bpp");

static const struct SpriteFrameImage sPicTable_MaySunhatFieldMove[] = {
    overworld_ascending_frames(gObjectEventPic_MaySunhatFieldMove, 4, 4),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MaySunhatFieldMove = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_FieldMove,
    .images = sPicTable_MaySunhatFieldMove,
};

const u32 gObjectEventPic_MaySunhatUnderwater[] = INCBIN_U32("graphics/player_hats/sunhat/underwater.4bpp");

static const struct SpriteFrameImage sPicTable_MaySunhatUnderwater[] = {
    overworld_frame(gObjectEventPic_MaySunhatUnderwater, 4, 4, 0),
    overworld_frame(gObjectEventPic_MaySunhatUnderwater, 4, 4, 1),
    overworld_frame(gObjectEventPic_MaySunhatUnderwater, 4, 4, 2),
    overworld_frame(gObjectEventPic_MaySunhatUnderwater, 4, 4, 0),
    overworld_frame(gObjectEventPic_MaySunhatUnderwater, 4, 4, 0),
    overworld_frame(gObjectEventPic_MaySunhatUnderwater, 4, 4, 1),
    overworld_frame(gObjectEventPic_MaySunhatUnderwater, 4, 4, 1),
    overworld_frame(gObjectEventPic_MaySunhatUnderwater, 4, 4, 2),
    overworld_frame(gObjectEventPic_MaySunhatUnderwater, 4, 4, 2),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MaySunhatUnderwater = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_PLAYER_UNDERWATER,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_MaySunhatUnderwater,
};

const u32 gObjectEventPic_MaySunhatFishing[] = INCBIN_U32("graphics/player_hats/sunhat/fishing.4bpp");

static const struct SpriteFrameImage sPicTable_MaySunhatFishing[] = {
    overworld_ascending_frames(gObjectEventPic_MaySunhatFishing, 4, 4),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MaySunhatFishing = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Fishing,
    .images = sPicTable_MaySunhatFishing,
};

const u32 gObjectEventPic_MaySunhatWatering[] = INCBIN_U32("graphics/player_hats/sunhat/watering.4bpp");

static const struct SpriteFrameImage sPicTable_MaySunhatWatering[] = {
    overworld_frame(gObjectEventPic_MaySunhatWatering, 4, 4, 0),
    overworld_frame(gObjectEventPic_MaySunhatWatering, 4, 4, 2),
    overworld_frame(gObjectEventPic_MaySunhatWatering, 4, 4, 4),
    overworld_frame(gObjectEventPic_MaySunhatWatering, 4, 4, 1),
    overworld_frame(gObjectEventPic_MaySunhatWatering, 4, 4, 1),
    overworld_frame(gObjectEventPic_MaySunhatWatering, 4, 4, 3),
    overworld_frame(gObjectEventPic_MaySunhatWatering, 4, 4, 3),
    overworld_frame(gObjectEventPic_MaySunhatWatering, 4, 4, 5),
    overworld_frame(gObjectEventPic_MaySunhatWatering, 4, 4, 5),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MaySunhatWatering = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_PLAYER,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sPicTable_MaySunhatWatering,
};

const u32 gObjectEventPic_MaySunhatDecorating[] = INCBIN_U32("graphics/player_hats/sunhat/decorating.4bpp");

static const struct SpriteFrameImage sPicTable_MaySunhatDecorating[] = {
    obj_frame_tiles(gObjectEventPic_MaySunhatDecorating),
};

const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_MaySunhatDecorating = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_MAY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_BRIDGE_REFLECTION,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_SPECIAL,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = TRUE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = sOamTables_16x32,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MaySunhatDecorating,
};

static const struct ObjectEventGraphicsInfo *const sPlayerHatGraphics[] = {

    &gObjectEventGraphicsInfo_MayBowNormal,

    &gObjectEventGraphicsInfo_MayBowMachBike,

    &gObjectEventGraphicsInfo_MayBowAcroBike,

    &gObjectEventGraphicsInfo_MayBowSurfing,

    &gObjectEventGraphicsInfo_MayBowFieldMove,

    &gObjectEventGraphicsInfo_MayBowUnderwater,

    &gObjectEventGraphicsInfo_MayBowFishing,

    &gObjectEventGraphicsInfo_MayBowWatering,

    &gObjectEventGraphicsInfo_MayBowDecorating,

    &gObjectEventGraphicsInfo_MaySunhatNormal,

    &gObjectEventGraphicsInfo_MaySunhatMachBike,

    &gObjectEventGraphicsInfo_MaySunhatAcroBike,

    &gObjectEventGraphicsInfo_MaySunhatSurfing,

    &gObjectEventGraphicsInfo_MaySunhatFieldMove,

    &gObjectEventGraphicsInfo_MaySunhatUnderwater,

    &gObjectEventGraphicsInfo_MaySunhatFishing,

    &gObjectEventGraphicsInfo_MaySunhatWatering,

    &gObjectEventGraphicsInfo_MaySunhatDecorating,

};
