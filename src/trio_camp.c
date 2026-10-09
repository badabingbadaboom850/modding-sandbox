#include "global.h"
#include "event_data.h"
#include "item.h"
#include "overworld.h"
#include "string_util.h"
#include "trio_camp.h"
#include "constants/flags.h"
#include "constants/game_stat.h"
#include "constants/items.h"
#include "constants/species.h"

// Older saves never initialized the unused encrypted game-stat slots.
// Clear only our ten slots once; standard adventure totals remain intact.
void TrioCamp_EnsureStatsInitialized(void)
{
    u32 i;
    if (FlagGet(FLAG_TRIO_CAMP_STATS_READY))
        return;
    for (i = GAME_STAT_TRIO_WAWA_S; i < NUM_GAME_STATS; i++)
        SetGameStat(i, 0);
    FlagSet(FLAG_TRIO_CAMP_STATS_READY);
}

void TrioCamp_RecordMedicineUse(u16 item)
{
    u32 stat;
    switch (item)
    {
    case ITEM_POTION: stat = GAME_STAT_TRIO_WAWA_S; break;
    case ITEM_SUPER_POTION: stat = GAME_STAT_TRIO_WAWA_M; break;
    case ITEM_HYPER_POTION: stat = GAME_STAT_TRIO_WAWA_L; break;
    case ITEM_ORAN_BERRY: stat = GAME_STAT_TRIO_CHICKY; break;
    case ITEM_CHERI_BERRY: stat = GAME_STAT_TRIO_SPRINGS; break;
    case ITEM_PECHA_BERRY: stat = GAME_STAT_TRIO_PUP_CUP; break;
    default: return;
    }
    TrioCamp_EnsureStatsInitialized();
    IncrementGameStat(stat);
}

void TrioCamp_RecordEvolution(u16 before, u16 after, u16 item)
{
    static const struct { u16 before, after, item; } swaps[] =
    {
        {SPECIES_RIKO, SPECIES_RIKO_WING, ITEM_RIKOS_WAND},
        {SPECIES_RIKO_WING, SPECIES_RIKO, ITEM_BLUE_BRUSH},
        {SPECIES_BIJUU, SPECIES_BIJUU_PSYCHIC, ITEM_BIJUUS_FISH_TOY},
        {SPECIES_BIJUU_PSYCHIC, SPECIES_BIJUU, ITEM_BIJUUS_CAT_NIP},
        {SPECIES_FIDOUGH, SPECIES_PENNY_GUARDIAN, ITEM_DADS_KEYS},
        {SPECIES_PENNY_GUARDIAN, SPECIES_FIDOUGH, ITEM_PIECE_OF_CHICKEN},
        {SPECIES_RIKO, SPECIES_RIKO_FIRE, ITEM_GREEN_PEPPER},
        {SPECIES_RIKO_FIRE, SPECIES_RIKO, ITEM_GREEN_PEPPER},
        {SPECIES_RIKO, SPECIES_RIKO_ELECTRIC, ITEM_EEL_SUSHI},
        {SPECIES_RIKO_ELECTRIC, SPECIES_RIKO, ITEM_EEL_SUSHI},
        {SPECIES_BIJUU, SPECIES_BIJUU_ICE, ITEM_FROZEN_FISH},
        {SPECIES_BIJUU_ICE, SPECIES_BIJUU, ITEM_FROZEN_FISH},
        {SPECIES_BIJUU, SPECIES_BIJUU_GHOST, ITEM_MOUSE_TOY},
        {SPECIES_BIJUU_GHOST, SPECIES_BIJUU, ITEM_MOUSE_TOY},
        {SPECIES_PENNY_GUARDIAN, SPECIES_PENNY_WATER, ITEM_DOG_BOWL},
        {SPECIES_PENNY_WATER, SPECIES_PENNY_GUARDIAN, ITEM_DOG_BOWL},
        {SPECIES_PENNY_GUARDIAN, SPECIES_PENNY_GRASS, ITEM_FETCHING_STICK},
        {SPECIES_PENNY_GRASS, SPECIES_PENNY_GUARDIAN, ITEM_FETCHING_STICK},
    };
    u32 i;
    for (i = 0; i < ARRAY_COUNT(swaps); i++)
    {
        if (swaps[i].before == before && swaps[i].after == after && swaps[i].item == item)
        {
            TrioCamp_EnsureStatsInitialized();
            IncrementGameStat(GAME_STAT_TRIO_FORM_SWAPS);
            return;
        }
    }
}

// These are visibility latches, not new achievement/reward flags. Recomputing
// them supports older saves and independent completion order without migration.
void TrioCamp_UpdateKeepsakes(void)
{
    static const struct { u16 hide, earned, legacy; } keepsakes[] =
    {
        {FLAG_HIDE_TRIO_CAMP_PENNY_CORNER, FLAG_BADGE01_GET, 0},
        {FLAG_HIDE_TRIO_CAMP_RIKO_CHICKY, FLAG_BADGE03_GET, 0},
        {FLAG_HIDE_TRIO_CAMP_BIJUU_TOY, FLAG_BADGE04_GET, 0},
        {FLAG_HIDE_TRIO_CAMP_FESTIVAL, FLAG_TRIO_FESTIVAL_PICNIC, 0},
        {FLAG_HIDE_TRIO_CAMP_PENNY_SPIRIT, FLAG_TRIO_PENNY_SPIRIT_COMPLETE, FLAG_TRIO_PENNY_HOME_WIN},
        {FLAG_HIDE_TRIO_CAMP_BIJUU_SPIRIT, FLAG_TRIO_BIJUU_SPIRIT_COMPLETE, FLAG_TRIO_BIJUU_HOME_WIN},
    };
    u32 i;
    for (i = 0; i < ARRAY_COUNT(keepsakes); i++)
    {
        if (FlagGet(keepsakes[i].earned) || (keepsakes[i].legacy != 0 && FlagGet(keepsakes[i].legacy)))
            FlagClear(keepsakes[i].hide);
        else
            FlagSet(keepsakes[i].hide);
    }
}

void TrioCamp_RecordVisit(void)
{
    TrioCamp_EnsureStatsInitialized();
    IncrementGameStat(GAME_STAT_TRIO_CAMP_VISITS);
}

void TrioCamp_RecordGame(void)
{
    TrioCamp_EnsureStatsInitialized();
    IncrementGameStat(GAME_STAT_TRIO_CAMP_GAMES);
}

void TrioCamp_RecordPet(void)
{
    TrioCamp_EnsureStatsInitialized();
    IncrementGameStat(GAME_STAT_TRIO_CAMP_PETS);
}

// Camp favorites consume exactly one explicitly offered consumable.
// Never remove the reusable elemental/guardian items or a keepsake.
bool32 TrioCamp_UseFavorite(void)
{
    static const u16 items[] = {ITEM_ORAN_BERRY, ITEM_CHERI_BERRY, ITEM_PECHA_BERRY};
    u16 item;
    if (gSpecialVar_0x8004 >= ARRAY_COUNT(items))
        return FALSE;
    item = items[gSpecialVar_0x8004];
    if (!RemoveBagItem(item, 1))
        return FALSE;
    TrioCamp_RecordMedicineUse(item);
    return TRUE;
}

void TrioCamp_BufferStats(void)
{
    static const u8 pages[][3] =
    {
        {GAME_STAT_STEPS, GAME_STAT_TOTAL_BATTLES, GAME_STAT_POKEMON_CAPTURES},
        {GAME_STAT_RESTED_AT_HOME, GAME_STAT_USED_POKECENTER, GAME_STAT_EVOLVED_POKEMON},
        {GAME_STAT_TRIO_WAWA_S, GAME_STAT_TRIO_WAWA_M, GAME_STAT_TRIO_WAWA_L},
        {GAME_STAT_TRIO_CHICKY, GAME_STAT_TRIO_SPRINGS, GAME_STAT_TRIO_PUP_CUP},
        {GAME_STAT_TRIO_FORM_SWAPS, GAME_STAT_TRIO_CAMP_VISITS, GAME_STAT_TRIO_CAMP_GAMES},
        {GAME_STAT_TRIO_CAMP_PETS, GAME_STAT_TRIO_CAMP_PETS, GAME_STAT_TRIO_CAMP_PETS},
    };
    u32 page = gSpecialVar_0x8004;
    TrioCamp_EnsureStatsInitialized();
    if (page >= ARRAY_COUNT(pages))
        page = 0;
    ConvertIntToDecimalStringN(gStringVar1, GetGameStat(pages[page][0]), STR_CONV_MODE_LEFT_ALIGN, 8);
    ConvertIntToDecimalStringN(gStringVar2, GetGameStat(pages[page][1]), STR_CONV_MODE_LEFT_ALIGN, 8);
    ConvertIntToDecimalStringN(gStringVar3, GetGameStat(pages[page][2]), STR_CONV_MODE_LEFT_ALIGN, 8);
}
