#ifndef GUARD_TRIO_PLAYER_HATS_H
#define GUARD_TRIO_PLAYER_HATS_H

// Explicit reserved graphics IDs: historical and dynamic IDs stay unchanged.
#define TRIO_PLAYER_HAT_GFX_BASE 0x180
#define TRIO_PLAYER_HAT_GFX_STATES 9
#define TRIO_PLAYER_HAT_COUNT 6
#define TRIO_PLAYER_FAMILY_HAT_GFX_BASE (TRIO_PLAYER_HAT_GFX_BASE + 2 * TRIO_PLAYER_HAT_GFX_STATES)

u32 TrioPlayerHat_GetStyle(void);
u16 TrioPlayerHat_BaseGraphics(u16 graphicsId);
u16 TrioPlayerHat_Graphics(u16 graphicsId, u32 gender);
u16 TrioPlayerHat_FrontPic(u32 gender);
u16 TrioPlayerHat_BackPic(u32 gender);
void ApplyTrioPlayerHat(void);

#endif
