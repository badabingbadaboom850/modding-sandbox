#include "global.h"
#include "event_data.h"
#include "string_util.h"
#include "trio_family_days.h"
#include "constants/flags.h"
#include "constants/characters.h"
#include "constants/vars.h"

static const u8 sRikoBase[] = _("Riko's strong opinions:\nChicken is a food group.\nWalks should include\nsnacks.\nSmall dogs deserve big\nbeds.\nThis has been public\nservice barking.");
static const u8 sRikoDinner[] = _("Riko's food review:\nFancy foam: no stars.\nPlain chicken: all stars.\nThe takeout box:\nexcellent.\nScott's fork skills:\npending.");
static const u8 sRikoRoad[] = _("Riko's travel report:\nI was never lost.\nI was finding extra woods.\nThe lookout proves it.\nBring snacks. Trust the\nsigns.");
static const u8 sRikoGarden[] = _("Riko's garden advice:\nFlowers suit my eyebrows.\nWater the seedlings\ngently.\nLet Bijuu warm the soil.\nPenny checks the forecast.");
static const u8 sBijuuBase[] = _("Bijuu's advice line:\nIf a chair is warm, sit.\nIf a toy is yours, keep\nit.\nIf Scott disagrees, purr.\nOur legal team is one cat.");
static const u8 sBijuuRoad[] = _("Guardian Bijuu speaks:\nThe island bell is safe.\nSo are the fish\ndeliveries.\nMy title is entirely real.\nPlease send guardian\nsnacks.");
static const u8 sBijuuBread[] = _("Bijuu's mystery report:\nThe bread legend was me.\nThe toast was also me.\nNo further questions.\nSend butter to my agent.");
static const u8 sBijuuMirror[] = _("Bijuu's identity advice:\nA reflection cannot purr.\nLook for the real little\ncat.\nHer sisters always know\nher.\nAlso, check for toy mice.");
static const u8 sPennyBase[] = _("Penny's goodnight corner:\nIf today felt too big,\nrest.\nYou can take your time.\nYour sisters are beside\nyou.\nYou have a safe place\nhere.");
static const u8 sPennyRoad[] = _("Penny's rainy-day advice:\nFind somewhere warm and\ndry.\nCheck on the ones you\nlove.\nLet them check on you,\ntoo.\nYou do not have to hurry.");
static const u8 sPennyLantern[] = _("Penny's little lantern:\nOne small light is enough.\nThen try the next one.\nIt is okay to ask for\nhelp.\nYou can still lead the\nway.");
static const u8 sPennyHome[] = _("Penny's goodnight corner:\nThe cups are put away.\nMom has folded the\nblanket.\nAll three girls are home.\nKeep a soft place for you.");
static const u8 sScottBase[] = _("Scott's dedication:\nTo the cutest trainer I\nknow:\nYou make ordinary days\ngood.\nPenny helped pick this\nsong.\nRiko requested chicken.");
static const u8 sScottRoad[] = _("Scott's dedication:\nOne ferry. Three detours.\nA cat stole my seat.\nPenny brought us home.\nStill my perfect date.");
static const u8 sScottDinner[] = _("Scott's dedication:\nI booked a fancy table.\nWe ended up with takeout.\nI keep falling for all of\nit.\nSame time next week, love?");
static const u8 sScottHome[] = _("Scott's dedication:\nI saved you a seat at\nhome.\nRiko saved herself two.\nCome back when you need\nrest.\nI will keep the Wawa warm.");
static const u8 sScottChampion[] = _("Scott's dedication:\nOur Champion is listening.\nYou took three girls so\nfar.\nCome sit beside me\nsometime.\nYou still make me nervous.");

// Reads earned story state only; listening never changes saved progress.
bool32 TrioFamilyRadio_IsUnlocked(void)
{
    return FlagGet(FLAG_ENABLE_RADIO) && VarGet(VAR_TRIO_RADIO_STATE) >= 4;
}

const u8 *TrioFamilyRadio_GetTopic(u32 segment)
{
    switch (segment % 4)
    {
    case 0:
        if (VarGet(VAR_TRIO_DINNER_STATE) >= 5) return sRikoDinner;
        if (VarGet(VAR_TRIO_ROAD_COMPLETE)) return sRikoRoad;
        if (VarGet(VAR_TRIO_GARDEN_STATE) >= 5) return sRikoGarden;
        return sRikoBase;
    case 1:
        if (VarGet(VAR_TRIO_BREAD_MYSTERY) >= 3) return sBijuuBread;
        if (VarGet(VAR_TRIO_ROAD_COMPLETE)) return sBijuuRoad;
        if (VarGet(VAR_TRIO_RIFT_BIJUU_STATE) >= 4) return sBijuuMirror;
        return sBijuuBase;
    case 2:
        if (VarGet(VAR_TRIO_HOMECOMING_STATE)) return sPennyHome;
        if (VarGet(VAR_TRIO_ROAD_COMPLETE)) return sPennyRoad;
        if (VarGet(VAR_TRIO_RIFT_PENNY_STATE) >= 4) return sPennyLantern;
        return sPennyBase;
    default:
        if (FlagGet(FLAG_IS_CHAMPION)) return sScottChampion;
        if (VarGet(VAR_TRIO_HOMECOMING_STATE)) return sScottHome;
        if (VarGet(VAR_TRIO_DINNER_STATE) >= 5) return sScottDinner;
        if (VarGet(VAR_TRIO_ROAD_COMPLETE)) return sScottRoad;
        return sScottBase;
    }
}

void BufferTrioFamilyRadio(void)
{
    StringCopy(gStringVar4, TrioFamilyRadio_GetTopic(gSpecialVar_0x8004));
    // The native radio scrolls lines; field dialogue needs two-row pages.
    u32 breaks = 0;
    for (u8 *p = gStringVar4; *p != EOS; p++)
    {
        if (*p == CHAR_NEWLINE && ++breaks % 2 == 0)
            *p = CHAR_PROMPT_CLEAR;
    }
}
