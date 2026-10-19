#include "global.h"
#include "bg.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "gpu_regs.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "overworld.h"
#include "palette.h"
#include "pokemon.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "trio_action_arena.h"
#include "window.h"
#include "constants/event_objects.h"
#include "constants/event_object_movement.h"
#include "constants/map_groups.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define ARENA_NEW(keys) (gMain.newKeysRaw & (keys))
#define ARENA_HELD(keys) (gMain.heldKeysRaw & (keys))

enum { SCREEN_CHOOSE, SCREEN_PLAY, SCREEN_PAUSE, SCREEN_ROUND, SCREEN_RESULT, SCREEN_EXIT };
struct ArenaScreen
{
    struct TrioArenaState game;
    u16 timer, tick;
    u8 mode, girls[ARENA_GIRLS], foe, shots[TRIO_ARENA_SHOTS];
    u8 selected, oldHp, oldEnemyHp;
    u8 challenge, outcome;
    u8 *backdrop;
};
static EWRAM_DATA struct ArenaScreen *sArena = NULL;

static void InitArenaScreen(void);
static void ArenaMain(void);
static void FadeToArena(u8 taskId);
static const struct BgTemplate sBg[] = {
    {.bg = 0, .charBaseIndex = 0, .mapBaseIndex = 31, .screenSize = 0, .paletteMode = 0, .priority = 2, .baseTile = 0},
};
static const struct WindowTemplate sWindows[] = {
    {.bg = 0, .tilemapLeft = 0, .tilemapTop = 0, .width = 30, .height = 20, .paletteNum = 15, .baseBlock = 1},
    DUMMY_WIN_TEMPLATE,
};
static const u16 sPalette[] = {
    RGB(5, 4, 10), RGB(30, 29, 26), RGB(10, 8, 17), RGB(9, 18, 14),
    RGB(11, 20, 15), RGB(6, 12, 10), RGB(18, 14, 21), RGB(26, 20, 13),
    RGB(30, 12, 15), RGB(16, 28, 24), RGB(23, 15, 31), RGB(30, 26, 13),
    RGB(14, 24, 17), RGB(4, 9, 8), RGB(19, 29, 31), RGB(29, 18, 29),
};
static const u8 sTextColors[] = {0, 1, 2};
static const u8 sGoldColors[] = {0, 11, 2};
static const u8 sTitle[] = _("TRIO ACTION ARENA");
static const u8 sChoose[] = _("LEFT / RIGHT: choose   A: play   B: leave");
static const u8 sPractice[] = _("Three rounds. Training HP only!");
static const u8 sNames[3][8] = {_("Riko"), _("Bijuu"), _("Penny")};
static const u8 sMoves[3][32] = {_("A Bark       B Pom Boom"), _("A Moon Orb   B Frost Fans"), _("A Paw Swipe  B Brave Charge")};
static const u8 sStyles[3][40] = {_("Bark blasts + a close-range boom"), _("Long-range orbs + slowing frost"), _("Close attacks + a brave dash")};
static const u8 sControls[] = _("R: dodge  L: aim lock  START: pause");
static const u8 sGreedent[] = _("Greedent  Round ");
static const u8 sPaused[] = _("PAUSED");
static const u8 sPauseControls[] = _("A / START: resume    B: leave arena");
static const u8 sWin[] = _("THREE ROUNDS! POM SUPREMACY!");
static const u8 sLoss[] = _("Good practice! The girls are safe.");
static const u8 sAgain[] = _("A: retry   B: lobby   LEFT/RIGHT: girl");
static const u8 sClear[] = _("ROUND CLEAR! +25 TRAINING HP");
static const u8 sCharge[] = _("CHARGE! Leave the marked line!");
static const u8 sVolley[] = _("VOLLEY! Keep moving!");
static const u8 sStomp[] = _("STOMP! Get outside the ring!");
static const u8 sReady[] = _("Move to aim. Hold L to aim at foe.");
static const u8 sChallengePractice[] = _("One tough duel. First win: a Riko Puff!");
static const u8 sChallengeWin[] = _("CHALLENGE CLEARED!");
static const u8 sClaimControls[] = _("A / B: return to your challenger");
static const u16 sFloorColors[TRIO_ARENA_CHALLENGES][2] = {
    {RGB(12,10,20),RGB(15,12,23)}, {RGB(20,15,10),RGB(22,17,12)},
    {RGB(7,16,21),RGB(9,18,23)}, {RGB(17,23,25),RGB(20,25,27)},
    {RGB(13,13,22),RGB(16,16,25)}, {RGB(7,8,15),RGB(10,11,18)},
    {RGB(17,10,21),RGB(20,12,24)}, {RGB(18,10,10),RGB(22,13,12)},
};

static const u8 *Title(void)
{
    return sArena->challenge < TRIO_ARENA_CHALLENGES ? gTrioArenaChallenges[sArena->challenge].title : sTitle;
}

// A tiny native orb, shared by the two bounded projectile pools.
static const u32 sOrb[] = {0x00000000, 0x00222200, 0x02211220, 0x02111120, 0x02111120, 0x02211220, 0x00222200, 0x00000000};
static const u16 sOrbPalettes[3][16] = {
    {0, RGB_WHITE, RGB(24, 15, 31)},
    {0, RGB(31, 28, 17), RGB(31, 10, 12)},
    {0, RGB_WHITE, RGB(8, 27, 31)},
};
static const struct OamData sOrbOam = {
    .shape = SPRITE_SHAPE(8x8), .size = SPRITE_SIZE(8x8), .priority = 0,
};
static const struct SpriteTemplate sOrbTemplate = {
    .tileTag = 0x7A00, .paletteTag = 0x7A00, .oam = &sOrbOam,
    .anims = gDummySpriteAnimTable, .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable, .callback = SpriteCallbackDummy,
};

static void Text(u16 x, u16 y, const u8 *str, const u8 *colors)
{
    AddTextPrinterParameterized4(0, FONT_SMALL, x, y, 0, 0, colors, TEXT_SKIP_DRAW, str);
}

static void Center(u16 y, const u8 *str)
{
    Text(max(0, (240 - GetStringWidth(FONT_SMALL, str, 0)) / 2), y, str, sTextColors);
}

static void Rect(s16 x, s16 y, s16 w, s16 h, u8 color)
{
    s16 right = min(240, x + w), bottom = min(128, y + h);
    x = max(0, x); y = max(24, y);
    if (right > x && bottom > y) FillWindowPixelRect(0, PIXEL_FILL(color), x, y, right - x, bottom - y);
}

static void Ring(s16 x, s16 y, s16 r, u8 color)
{
    for (s16 dx = -r; dx <= r; dx += 3)
        for (s16 dy = -r; dy <= r; dy += 3)
        {
            s32 d = dx * dx + dy * dy;
            if (d >= (r - 3) * (r - 3) && d <= r * r) Rect(x + dx, y + dy, 3, 3, color);
        }
}

static void Floor(void)
{
    if (sArena->backdrop)
    {
        // Whole tile rows: avoid redrawing 25,000 pixels through the slow
        // general-purpose bitmap rasterizer on each effects update.
        memcpy(gWindows[0].tileData + 3 * 30 * 32, sArena->backdrop + 3 * 30 * 32, 13 * 30 * 32);
    }
    else
    {
        FillWindowPixelRect(0, PIXEL_FILL(3), 0, 24, 240, 104);
        for (u32 y = 24; y < 128; y += 8)
            for (u32 x = 0; x < 240; x += 8)
            {
                if (((x + y) / 8) & 1) Rect(x, y, 8, 8, 4);
                if ((x * 7 + y * 3) % 40 == 0) { Rect(x + 2, y + 3, 1, 3, 12); Rect(x + 3, y + 4, 2, 1, 12); }
            }
        Rect(4, 28, 232, 3, 7); Rect(4, 125, 232, 3, 7);
        Rect(4, 28, 3, 100, 7); Rect(233, 28, 3, 100, 7);
        for (u32 x = 12; x < 232; x += 16) { Rect(x, 26, 4, 8, 6); Rect(x, 122, 4, 6, 6); }
        for (u32 x = 12; x < 232; x += 40) { Rect(x, 34, 3, 3, 15); Rect(x + 3, 35, 2, 2, 11); }
        Ring(120, 80, 29, 12);
    }
    if (sArena->mode == SCREEN_PLAY)
    {
        struct TrioArenaState *a = &sArena->game;
        if (a->enemyMode == ARENA_WARN)
        {
            if (a->pattern == 2) Ring(a->ex / 16, a->ey / 16, 42, (sArena->tick / 6) & 1 ? 8 : 11);
            else
            {
                s16 tx = a->targetX / 16, ty = a->targetY / 16;
                for (u32 i = 0; i <= 16; i++)
                    Rect(a->ex / 16 + (tx - a->ex / 16) * (s16)i / 16 - 1,
                         a->ey / 16 + (ty - a->ey / 16) * (s16)i / 16 - 1, 3, 3, 8);
                Ring(tx, ty, 9, 11);
            }
        }
        if (a->girl == ARENA_RIKO && a->rush) Ring(a->x / 16, a->y / 16, 46 - a->rush * 2, 10);
        if (a->dash) Ring(a->x / 16, a->y / 16, 12, 14);
    }
}

static void ClearHud(void)
{
    memset(gWindows[0].tileData, 0, 3 * 30 * 32);
    memset(gWindows[0].tileData + 16 * 30 * 32, 0, 4 * 30 * 32);
}

static void Bar(u16 x, u16 y, u16 width, u16 value, u16 maximum, u8 color)
{
    FillWindowPixelRect(0, PIXEL_FILL(2), x, y, width, 5);
    if (value) FillWindowPixelRect(0, PIXEL_FILL(color), x, y, max(1, width * value / maximum), 5);
}

static void Hud(void)
{
    struct TrioArenaState *a = &sArena->game;
    u8 label[32];
    ClearHud();
    Text(8, 1, sNames[a->girl], sTextColors);
    if (sArena->challenge < TRIO_ARENA_CHALLENGES)
        StringCopy(label, gSpeciesInfo[gTrioArenaChallenges[sArena->challenge].species].speciesName);
    else
    {
        StringCopy(label, sGreedent);
        ConvertIntToDecimalStringN(label + StringLength(label), a->round + 1, STR_CONV_MODE_LEFT_ALIGN, 1);
    }
    Text(124, 1, label, sGoldColors);
    Bar(8, 17, 100, a->hp, 100, a->hp > 30 ? 9 : 8);
    Bar(130, 17, 100, a->enemyHp, a->enemyMaxHp, 8);
    Text(8, 128, sMoves[a->girl], sTextColors);
    Bar(8, 141, 60, 24 - min(24, a->primaryCd), 24, 10);
    Bar(100, 141, 72, 150 - min(150, a->secondaryCd), 150, 14);
    Text(8, 146, sControls, sTextColors);
    if (a->enemyMode == ARENA_WARN)
        Center(25, a->pattern == 2 ? sStomp : a->pattern == 1 ? sVolley : sCharge);
}

static void AllInvisible(void)
{
    for (u32 i = 0; i < ARENA_GIRLS; i++) gSprites[sArena->girls[i]].invisible = TRUE;
    gSprites[sArena->foe].invisible = TRUE;
    for (u32 i = 0; i < TRIO_ARENA_SHOTS; i++) gSprites[sArena->shots[i]].invisible = TRUE;
}

static void Choose(void)
{
    sArena->mode = SCREEN_CHOOSE;
    AllInvisible(); Floor();
    ClearHud();
    Center(3, Title()); Center(31, sArena->challenge < TRIO_ARENA_CHALLENGES ? sChallengePractice : sPractice);
    for (u32 i = 0; i < ARENA_GIRLS; i++)
    {
        struct Sprite *sprite = &gSprites[sArena->girls[i]];
        sprite->invisible = FALSE; sprite->x = 50 + i * 70; sprite->y = 75;
        sprite->x2 = sprite->y2 = 0;
        StartSpriteAnim(sprite, ANIM_STD_FACE_SOUTH);
        Text(36 + i * 70, 91, sNames[i], i == sArena->selected ? sGoldColors : sTextColors);
        if (i == sArena->selected) Ring(50 + i * 70, 76, 22, 11);
    }
    Center(111, sStyles[sArena->selected]);
    Center(130, sChoose); Center(145, sMoves[sArena->selected]);
    CopyWindowToVram(0, COPYWIN_FULL);
}

static void BeginFight(void)
{
    TrioArena_Init(&sArena->game, sArena->selected);
    if (sArena->challenge < TRIO_ARENA_CHALLENGES)
        TrioArena_InitChallenge(&sArena->game, sArena->selected, sArena->challenge);
    sArena->outcome = ARENA_RESULT_CANCEL;
    sArena->mode = SCREEN_PLAY;
    sArena->oldHp = sArena->oldEnemyHp = 255;
    AllInvisible(); Floor(); Hud();
    Center(25, sReady);
    CopyWindowToVram(0, COPYWIN_FULL);
}

static void RenderSprites(void)
{
    struct TrioArenaState *a = &sArena->game;
    struct Sprite *p = &gSprites[sArena->girls[a->girl]], *e = &gSprites[sArena->foe];
    s16 dx = a->aimX, dy = a->aimY;
    u8 direction = abs(dx) >= abs(dy) ? (dx < 0 ? ANIM_STD_FACE_WEST : ANIM_STD_FACE_EAST)
                                          : (dy < 0 ? ANIM_STD_FACE_NORTH : ANIM_STD_FACE_SOUTH);
    p->x = a->x / 16; p->y = a->y / 16; p->y2 = (a->frames / 10) & 1 ? -1 : 0;
    p->invisible = a->invincible && ((a->frames / 4) & 1);
    if (p->animNum != direction) StartSpriteAnim(p, direction);
    e->x = a->ex / 16; e->y = a->ey / 16; e->y2 = (a->frames / 12) & 1 ? -1 : 0;
    e->invisible = a->enemyFlash && (a->frames & 1);
    direction = a->x < a->ex ? ANIM_STD_FACE_WEST : ANIM_STD_FACE_EAST;
    if (e->animNum != direction) StartSpriteAnim(e, direction);
    for (u32 i = 0; i < TRIO_ARENA_SHOTS; i++)
    {
        struct TrioArenaShot *shot = &a->shots[i];
        struct Sprite *sp = &gSprites[sArena->shots[i]];
        sp->invisible = !shot->life; sp->x = shot->x / 16; sp->y = shot->y / 16;
        sp->oam.paletteNum = IndexOfSpritePaletteTag(0x7A00 + (!shot->friendly ? 1 : shot->frost ? 2 : 0));
    }
}

static void Panel(const u8 *heading, const u8 *controls)
{
    AllInvisible(); Floor();
    ClearHud();
    Center(3, Title()); Center(62, heading); Center(91, controls);
    CopyWindowToVram(0, COPYWIN_FULL);
}

static void StartExit(void)
{
    sArena->mode = SCREEN_EXIT;
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
}

static void FinishExit(void)
{
    if (sArena->challenge < TRIO_ARENA_CHALLENGES)
        gSpecialVar_Result = sArena->mode == SCREEN_EXIT ? sArena->outcome : ARENA_RESULT_ERROR;
    else
        gSpecialVar_Result = sArena->mode == SCREEN_EXIT;
    SetVBlankCallback(NULL);
    ResetSpriteData(); FreeAllSpritePalettes();
    FreeAllWindowBuffers(); UnsetBgTilemapBuffer(0);
    if (sArena->backdrop) Free(sArena->backdrop);
    FREE_AND_SET_NULL(sArena);
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static void ArenaVBlank(void)
{
    LoadOam(); ProcessSpriteCopyRequests(); TransferPlttBuffer();
}

static void ArenaMain(void)
{
    u16 input = 0;
    struct TrioArenaState *a = &sArena->game;
    sArena->tick++;
    if (gPaletteFade.active) { UpdatePaletteFade(); BuildOamBuffer(); return; }
    switch (sArena->mode)
    {
    case SCREEN_CHOOSE:
        if (ARENA_NEW(B_BUTTON)) StartExit();
        else if (ARENA_NEW(A_BUTTON)) BeginFight();
        else if (ARENA_NEW(DPAD_LEFT | DPAD_RIGHT))
        {
            sArena->selected = (sArena->selected + (ARENA_NEW(DPAD_LEFT) ? 2 : 1)) % ARENA_GIRLS;
            Choose();
        }
        break;
    case SCREEN_PLAY:
        if (ARENA_NEW(START_BUTTON | SELECT_BUTTON))
        {
            sArena->mode = SCREEN_PAUSE; Panel(sPaused, sPauseControls); break;
        }
        if (ARENA_HELD(DPAD_UP)) input |= TRIO_ARENA_MOVE_UP;
        if (ARENA_HELD(DPAD_DOWN)) input |= TRIO_ARENA_MOVE_DOWN;
        if (ARENA_HELD(DPAD_LEFT)) input |= TRIO_ARENA_MOVE_LEFT;
        if (ARENA_HELD(DPAD_RIGHT)) input |= TRIO_ARENA_MOVE_RIGHT;
        if (ARENA_HELD(A_BUTTON)) input |= TRIO_ARENA_PRIMARY;
        if (ARENA_NEW(B_BUTTON)) input |= TRIO_ARENA_SECONDARY;
        if (ARENA_NEW(R_BUTTON)) input |= TRIO_ARENA_DODGE;
        if (ARENA_HELD(L_BUTTON)) input |= TRIO_ARENA_LOCK;
        TrioArena_Step(a, input);
        if (a->hp < sArena->oldHp && sArena->oldHp != 255) PlaySE(SE_WALL_HIT);
        if (a->enemyHp < sArena->oldEnemyHp && sArena->oldEnemyHp != 255) PlaySE(SE_BALL_BOUNCE_1);
        sArena->oldHp = a->hp; sArena->oldEnemyHp = a->enemyHp;
        RenderSprites();
        if (a->status == ARENA_ROUND_CLEAR)
        {
            sArena->mode = SCREEN_ROUND; sArena->timer = 100; Panel(sClear, sPractice);
        }
        else if (a->status == ARENA_WON || a->status == ARENA_LOST)
        {
            sArena->outcome = a->status == ARENA_WON ? ARENA_RESULT_WON : ARENA_RESULT_LOST;
            sArena->mode = SCREEN_RESULT;
            Panel(a->status == ARENA_WON ? (sArena->challenge < TRIO_ARENA_CHALLENGES ? sChallengeWin : sWin) : sLoss,
                  sArena->challenge < TRIO_ARENA_CHALLENGES && a->status == ARENA_WON ? sClaimControls : sAgain);
        }
        else if (!(sArena->tick & 7)) { Floor(); Hud(); CopyWindowToVram(0, COPYWIN_GFX); }
        break;
    case SCREEN_PAUSE:
        if (ARENA_NEW(B_BUTTON)) StartExit();
        else if (ARENA_NEW(A_BUTTON | START_BUTTON | SELECT_BUTTON))
        {
            sArena->mode = SCREEN_PLAY; Floor(); Hud(); RenderSprites(); CopyWindowToVram(0, COPYWIN_FULL);
        }
        break;
    case SCREEN_ROUND:
        if (ARENA_NEW(B_BUTTON)) StartExit();
        else if (!--sArena->timer)
        {
            TrioArena_NextRound(a); sArena->mode = SCREEN_PLAY;
            sArena->oldHp = sArena->oldEnemyHp = 255;
            Floor(); Hud(); RenderSprites(); CopyWindowToVram(0, COPYWIN_FULL);
        }
        break;
    case SCREEN_RESULT:
        if (sArena->challenge < TRIO_ARENA_CHALLENGES && a->status == ARENA_WON && ARENA_NEW(A_BUTTON | B_BUTTON)) StartExit();
        else if (ARENA_NEW(B_BUTTON)) StartExit();
        else if (ARENA_NEW(A_BUTTON)) BeginFight();
        else if (ARENA_NEW(DPAD_LEFT | DPAD_RIGHT)) Choose();
        break;
    case SCREEN_EXIT:
        FinishExit(); return;
    }
    AnimateSprites(); BuildOamBuffer(); UpdatePaletteFade();
}

static void InitArenaScreen(void)
{
    static const u16 graphics[ARENA_GIRLS] = {OBJ_EVENT_GFX_SPECIES(RIKO), OBJ_EVENT_GFX_SPECIES(BIJUU), OBJ_EVENT_GFX_SPECIES(FIDOUGH)};
    const struct SpriteSheet sheet = {sOrb, sizeof(sOrb), 0x7A00};
    SetVBlankCallback(NULL); SetHBlankCallback(NULL);
    DeactivateAllTextPrinters(); ResetTasks();
    ResetAllBgsCoordinates(); ResetVramOamAndBgCntRegs();
    ResetBgsAndClearDma3BusyFlags(0); InitBgsFromTemplates(0, sBg, ARRAY_COUNT(sBg));
    ResetPaletteFade(); ResetSpriteData(); FreeAllSpritePalettes();
    if (!InitWindows(sWindows)) { FinishExit(); return; }
    Floor();
    sArena->backdrop = Alloc(30 * 20 * 32);
    if (!sArena->backdrop) { FinishExit(); return; }
    memcpy(sArena->backdrop, gWindows[0].tileData, 30 * 20 * 32);
    LoadPalette(sPalette, BG_PLTT_ID(15), sizeof(sPalette));
    if (sArena->challenge < TRIO_ARENA_CHALLENGES)
        LoadPalette(sFloorColors[sArena->challenge], BG_PLTT_ID(15) + 3, sizeof(sFloorColors[0]));
    for (u32 i = 0; i < ARENA_GIRLS; i++)
    {
        sArena->girls[i] = CreateObjectGraphicsSprite(graphics[i], SpriteCallbackDummy, 0, 0, 0);
        if (sArena->girls[i] == MAX_SPRITES) { FinishExit(); return; }
        gSprites[sArena->girls[i]].oam.priority = 0;
    }
    sArena->foe = CreateObjectGraphicsSprite(OBJ_EVENT_MON + (sArena->challenge < TRIO_ARENA_CHALLENGES
        ? gTrioArenaChallenges[sArena->challenge].species : SPECIES_GREEDENT), SpriteCallbackDummy, 0, 0, 0);
    if (sArena->foe == MAX_SPRITES) { FinishExit(); return; }
    gSprites[sArena->foe].oam.priority = 0;
    if (LoadSpriteSheet(&sheet) == 0xFFFF) { FinishExit(); return; }
    for (u32 i = 0; i < 3; i++)
    {
        const struct SpritePalette pal = {sOrbPalettes[i], 0x7A00 + i};
        if (LoadSpritePalette(&pal) == 0xFF) { FinishExit(); return; }
    }
    for (u32 i = 0; i < TRIO_ARENA_SHOTS; i++)
    {
        sArena->shots[i] = CreateSprite(&sOrbTemplate, 0, 0, 0);
        if (sArena->shots[i] == MAX_SPRITES) { FinishExit(); return; }
    }
    PutWindowTilemap(0); Choose();
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    ShowBg(0); BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    SetVBlankCallback(ArenaVBlank); SetMainCallback2(ArenaMain);
}

static void StartArena(u8 challenge)
{
    u8 taskId;
    gSpecialVar_Result = FALSE;
    if (sArena) return;
    sArena = AllocZeroed(sizeof(*sArena));
    if (!sArena) return;
    sArena->challenge = challenge;
    taskId = CreateTask(FadeToArena, 0);
    if (taskId == TASK_NONE) { FREE_AND_SET_NULL(sArena); return; }
    gSpecialVar_Result = TRUE;
}

void StartTrioActionArena(void)
{
    gSpecialVar_Result = FALSE;
    if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(MAP_TRIO_ACTION_ARENA)
        || gSaveBlock1Ptr->location.mapNum != MAP_NUM(MAP_TRIO_ACTION_ARENA)) return;
    StartArena(TRIO_ARENA_PRACTICE);
}

void StartTrioActionChallenge(void)
{
    u8 id = TrioArena_CurrentChallenge();
    gSpecialVar_Result = FALSE;
    if (!TrioArena_CanStartChallenge(id)) return;
    StartArena(id);
}

static void FadeToArena(u8 taskId)
{
    if (!gTasks[taskId].data[0])
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].data[0] = 1;
    }
    else if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        SetMainCallback2(InitArenaScreen); DestroyTask(taskId);
    }
}
