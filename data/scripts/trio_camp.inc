@ Camp game state is map-local: B=game (0/1/2), C=basket/answer,
@ D=round count, E=selected girl (0/1/2). Leaving cancels unfinished games.
TrioCamp_OnTransition::
	setvar VAR_TEMP_B, 0
	setvar VAR_TEMP_C, 0
	setvar VAR_TEMP_D, 0
	setflag FLAG_HIDE_TRIO_CAMP_RIKO
	setflag FLAG_HIDE_TRIO_CAMP_BIJUU
	setflag FLAG_HIDE_TRIO_CAMP_PENNY
	call TrioParty_CheckRiko
	call_if_eq VAR_RESULT, TRUE, TrioCamp_ShowRiko
	call TrioParty_CheckBijuu
	call_if_eq VAR_RESULT, TRUE, TrioCamp_ShowBijuu
	call TrioParty_CheckPenny
	call_if_eq VAR_RESULT, TRUE, TrioCamp_ShowPenny
	special TrioCamp_RecordVisit
	end
TrioCamp_ShowRiko:
	clearflag FLAG_HIDE_TRIO_CAMP_RIKO
	return
TrioCamp_ShowBijuu:
	clearflag FLAG_HIDE_TRIO_CAMP_BIJUU
	return
TrioCamp_ShowPenny:
	clearflag FLAG_HIDE_TRIO_CAMP_PENNY
	return

@ Called by the existing host; caller owns the conversation lock.
TrioCamp_Host::
	msgbox TrioCamp_Welcome, MSGBOX_DEFAULT
TrioCamp_HostMenu:
	closemessage
	multichoice 0, 0, MULTI_TRIO_CAMP_HOST, FALSE
	goto_if_eq VAR_RESULT, 0, TrioCamp_Rest
	goto_if_eq VAR_RESULT, 1, TrioCamp_Help
	goto_if_eq VAR_RESULT, 2, TrioCamp_HostStats
	return
TrioCamp_Help:
	msgbox TrioCamp_HelpText, MSGBOX_DEFAULT
	goto TrioCamp_HostMenu
TrioCamp_HostStats:
	call TrioCamp_ReadStats
	goto TrioCamp_HostMenu
TrioCamp_Rest:
	call Common_EventScript_OutOfCenterPartyHeal
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioCamp_RestAlone
	goto_if_set FLAG_IS_CHAMPION, TrioCamp_RestChampion
	goto_if_set FLAG_BADGE04_GET, TrioCamp_RestMidgame
	msgbox TrioCamp_RestEarlyText, MSGBOX_DEFAULT
	goto TrioCamp_RecordMemory
TrioCamp_RestMidgame:
	msgbox TrioCamp_RestMidgameText, MSGBOX_DEFAULT
	goto TrioCamp_RecordMemory
TrioCamp_RestChampion:
	msgbox TrioCamp_RestChampionText, MSGBOX_DEFAULT
TrioCamp_RecordMemory:
	goto_if_set FLAG_TRIO_CAMP_MEMORY, TrioCamp_HostMenu
	setflag FLAG_TRIO_CAMP_MEMORY
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	goto TrioCamp_HostMenu
TrioCamp_RestAlone:
	msgbox TrioCamp_RestAloneText, MSGBOX_DEFAULT
	goto TrioCamp_HostMenu

TrioCamp_Riko::
	lockall
	faceplayer
	setvar VAR_TEMP_E, 0
	msgbox TrioCamp_RikoHello, MSGBOX_DEFAULT
	goto TrioCamp_GirlMenu
TrioCamp_Bijuu::
	lockall
	faceplayer
	setvar VAR_TEMP_E, 1
	msgbox TrioCamp_BijuuHello, MSGBOX_DEFAULT
	goto TrioCamp_GirlMenu
TrioCamp_Penny::
	lockall
	faceplayer
	setvar VAR_TEMP_E, 2
	msgbox TrioCamp_PennyHello, MSGBOX_DEFAULT
TrioCamp_GirlMenu:
	closemessage
	multichoice 0, 0, MULTI_TRIO_CAMP_GIRL, FALSE
	goto_if_eq VAR_RESULT, 0, TrioCamp_Pet
	goto_if_eq VAR_RESULT, 1, TrioCamp_Favorite
	goto_if_eq VAR_RESULT, 2, TrioCamp_Play
	goto TrioCamp_End
TrioCamp_Pet:
	special TrioCamp_RecordPet
	applymovement LOCALID_LAST_TALKED, TrioCamp_HappyMovement
	waitmovement 0
	faceplayer
	call TrioCamp_Cry
	goto_if_eq VAR_TEMP_E, 0, TrioCamp_PetRiko
	goto_if_eq VAR_TEMP_E, 1, TrioCamp_PetBijuu
	msgbox TrioCamp_PetPennyText, MSGBOX_DEFAULT
	goto TrioCamp_End
TrioCamp_PetRiko:
	msgbox TrioCamp_PetRikoText, MSGBOX_DEFAULT
	goto TrioCamp_End
TrioCamp_PetBijuu:
	msgbox TrioCamp_PetBijuuText, MSGBOX_DEFAULT
	goto TrioCamp_End
TrioCamp_Cry:
	goto_if_eq VAR_TEMP_E, 0, TrioCamp_CryRiko
	goto_if_eq VAR_TEMP_E, 1, TrioCamp_CryBijuu
	playmoncry SPECIES_FIDOUGH, CRY_MODE_NORMAL
	goto TrioCamp_CryWait
TrioCamp_CryRiko:
	playmoncry SPECIES_RIKO, CRY_MODE_NORMAL
	goto TrioCamp_CryWait
TrioCamp_CryBijuu:
	playmoncry SPECIES_BIJUU, CRY_MODE_NORMAL
TrioCamp_CryWait:
	waitmoncry
	return
TrioCamp_Favorite:
	goto_if_eq VAR_TEMP_E, 0, TrioCamp_FavoriteRiko
	goto_if_eq VAR_TEMP_E, 1, TrioCamp_FavoriteBijuu
	msgbox TrioCamp_PupCupOffer, MSGBOX_YESNO
	goto TrioCamp_FavoriteCheck
TrioCamp_FavoriteRiko:
	msgbox TrioCamp_ChickyOffer, MSGBOX_YESNO
	goto TrioCamp_FavoriteCheck
TrioCamp_FavoriteBijuu:
	msgbox TrioCamp_SpringsOffer, MSGBOX_YESNO
TrioCamp_FavoriteCheck:
	goto_if_eq VAR_RESULT, NO, TrioCamp_End
	copyvar VAR_0x8004, VAR_TEMP_E
	specialvar VAR_RESULT, TrioCamp_UseFavorite
	goto_if_eq VAR_RESULT, FALSE, TrioCamp_NoFavorite
	call TrioCamp_Cry
	msgbox TrioCamp_FavoriteHappy, MSGBOX_DEFAULT
	goto TrioCamp_End
TrioCamp_NoFavorite:
	msgbox TrioCamp_NoFavoriteText, MSGBOX_DEFAULT
	goto TrioCamp_End

TrioCamp_Play:
	setvar VAR_TEMP_B, 0
	goto_if_eq VAR_TEMP_E, 0, TrioCamp_RikoGame
	goto_if_eq VAR_TEMP_E, 1, TrioCamp_BijuuGame
	msgbox TrioCamp_PennyGameOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCamp_End
	setvar VAR_TEMP_B, 2
	setvar VAR_TEMP_D, 0
	goto TrioCamp_PickBasket
TrioCamp_BijuuGame:
	msgbox TrioCamp_BijuuGameOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCamp_End
	setvar VAR_TEMP_B, 1
TrioCamp_PickBasket:
	random 3
	copyvar VAR_TEMP_C, VAR_RESULT
	addvar VAR_TEMP_C, 1
	call TrioCamp_BasketHint
	goto TrioCamp_End
TrioCamp_BasketHint:
	goto_if_eq VAR_TEMP_C, 1, TrioCamp_HintLeft
	goto_if_eq VAR_TEMP_C, 2, TrioCamp_HintMiddle
	msgbox TrioCamp_HintRightText, MSGBOX_DEFAULT
	return
TrioCamp_HintLeft:
	msgbox TrioCamp_HintLeftText, MSGBOX_DEFAULT
	return
TrioCamp_HintMiddle:
	msgbox TrioCamp_HintMiddleText, MSGBOX_DEFAULT
	return
TrioCamp_RikoGame:
	msgbox TrioCamp_RikoGameOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCamp_End
	setvar VAR_TEMP_D, 0
TrioCamp_RikoRound:
	msgbox TrioCamp_ListenText, MSGBOX_DEFAULT
	closemessage
	random 3
	copyvar VAR_TEMP_C, VAR_RESULT
	call TrioCamp_CryRiko
	delay 20
	call_if_ge VAR_TEMP_C, 1, TrioCamp_CryRiko
	delay 20
	call_if_eq VAR_TEMP_C, 2, TrioCamp_CryRiko
	msgbox TrioCamp_HowManyText, MSGBOX_DEFAULT
	closemessage
	multichoice 0, 0, MULTI_TRIO_CAMP_BARKS, FALSE
	goto_if_ge VAR_RESULT, 3, TrioCamp_End
	goto_if_ne VAR_RESULT, VAR_TEMP_C, TrioCamp_RikoWrong
	addvar VAR_TEMP_D, 1
	goto_if_eq VAR_TEMP_D, 3, TrioCamp_RikoWin
	msgbox TrioCamp_RikoCorrectText, MSGBOX_DEFAULT
	goto TrioCamp_RikoRound
TrioCamp_RikoWrong:
	msgbox TrioCamp_RikoWrongText, MSGBOX_DEFAULT
	goto TrioCamp_End
TrioCamp_RikoWin:
	special TrioCamp_RecordGame
	msgbox TrioCamp_RikoWinText, MSGBOX_DEFAULT
	goto TrioCamp_End

TrioCamp_BasketLeft::
	lockall
	setvar VAR_0x8005, 1
	goto TrioCamp_Basket
TrioCamp_BasketMiddle::
	lockall
	setvar VAR_0x8005, 2
	goto TrioCamp_Basket
TrioCamp_BasketRight::
	lockall
	setvar VAR_0x8005, 3
TrioCamp_Basket:
	goto_if_eq VAR_TEMP_B, 0, TrioCamp_BasketIdle
	goto_if_ne VAR_TEMP_C, VAR_0x8005, TrioCamp_BasketWrong
	goto_if_eq VAR_TEMP_B, 2, TrioCamp_PennyFetch
	setvar VAR_TEMP_B, 0
	special TrioCamp_RecordGame
	playmoncry SPECIES_BIJUU, CRY_MODE_NORMAL
	msgbox TrioCamp_BijuuWinText, MSGBOX_DEFAULT
	waitmoncry
	goto TrioCamp_End
TrioCamp_PennyFetch:
	applymovement 5, TrioCamp_HappyMovement
	waitmovement 0
	playmoncry SPECIES_FIDOUGH, CRY_MODE_NORMAL
	msgbox TrioCamp_PennyFetchText, MSGBOX_DEFAULT
	waitmoncry
	addvar VAR_TEMP_D, 1
	goto_if_eq VAR_TEMP_D, 2, TrioCamp_PennyWin
	addvar VAR_TEMP_C, 1
	goto_if_ne VAR_TEMP_C, 4, TrioCamp_PennyNext
	setvar VAR_TEMP_C, 1
TrioCamp_PennyNext:
	call TrioCamp_BasketHint
	goto TrioCamp_End
TrioCamp_PennyWin:
	setvar VAR_TEMP_B, 0
	special TrioCamp_RecordGame
	msgbox TrioCamp_PennyWinText, MSGBOX_DEFAULT
	goto TrioCamp_End
TrioCamp_BasketWrong:
	msgbox TrioCamp_BasketWrongText, MSGBOX_DEFAULT
	call TrioCamp_BasketHint
	goto TrioCamp_End
TrioCamp_BasketIdle:
	msgbox TrioCamp_BasketIdleText, MSGBOX_DEFAULT
TrioCamp_End:
	closemessage
	releaseall
	end

TrioCamp_StatsBoard::
	lockall
	call TrioCamp_ReadStats
	goto TrioCamp_End
TrioCamp_ReadStats::
	msgbox TrioCamp_StatsIntro, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	special TrioCamp_BufferStats
	msgbox TrioCamp_StatsAdventure, MSGBOX_DEFAULT
	setvar VAR_0x8004, 1
	special TrioCamp_BufferStats
	msgbox TrioCamp_StatsRests, MSGBOX_DEFAULT
	setvar VAR_0x8004, 2
	special TrioCamp_BufferStats
	msgbox TrioCamp_StatsWawa, MSGBOX_DEFAULT
	setvar VAR_0x8004, 3
	special TrioCamp_BufferStats
	msgbox TrioCamp_StatsFavorites, MSGBOX_DEFAULT
	setvar VAR_0x8004, 4
	special TrioCamp_BufferStats
	msgbox TrioCamp_StatsCamp, MSGBOX_DEFAULT
	setvar VAR_0x8004, 5
	special TrioCamp_BufferStats
	msgbox TrioCamp_StatsPets, MSGBOX_DEFAULT
	return
TrioCamp_ReadMemory::
	msgbox TrioCamp_MemoryText, MSGBOX_DEFAULT
	return
TrioCamp_Checklist::
	goto_if_set FLAG_TRIO_CAMP_MEMORY, TrioCamp_ChecklistSaved
	msgbox TrioCamp_ChecklistHint, MSGBOX_DEFAULT
	return
TrioCamp_ChecklistSaved:
	msgbox TrioCamp_ChecklistSavedText, MSGBOX_DEFAULT
	return
TrioCamp_HappyMovement:
	walk_in_place_fast_down
	walk_in_place_fast_up
	walk_in_place_fast_down
	step_end

TrioCamp_Welcome:
	.string "Welcome to Trio Camp!\p"
	.string "A little room for Mom and\nher girls to just be\p"
	.string "together.\p"
	.string "The shelf at the back\nkeeps our family totals.$"

TrioCamp_HelpText:
	.string "Bring a girl in your party\nand she'll wander here.\p"
	.string "Supported forms count,\ntoo.\p"
	.string "Talk to her to pet, play,\nor offer her favorite.\p"
	.string "Riko: count three rounds\nof barks.\p"
	.string "Bijuu: find her toy in one\nof the three floor\p"
	.string "baskets.\p"
	.string "Penny: find the camp keys\ntwice and call her over.\p"
	.string "The keys are play props.\nDad's Keys stay in your\p"
	.string "Bag.\p"
	.string "Starting another game or\nleaving cancels a game.\p"
	.string "Rest with all three girls\nto save a scrapbook page.$"

TrioCamp_RestAloneText:
	.string "Your party feels rested.\p"
	.string "Bring Riko, Bijuu, and\nPenny together for a\p"
	.string "family moment.$"

TrioCamp_RestEarlyText:
	.string "Riko takes the biggest\ncushion. Bijuu takes\p"
	.string "Riko's tail.\p"
	.string "Penny chooses the spot\nwhere she can touch Mom\p"
	.string "and both sisters.\p"
	.string "Nobody needs to be brave\nright now.$"

TrioCamp_RestMidgameText:
	.string "Penny stretches out first.\nBijuu curls into her side.\p"
	.string "Riko checks the doorway,\nthen decides Mom has\p"
	.string "everything handled.\p"
	.string "The whole room breathes a\nlittle slower.$"

TrioCamp_RestChampionText:
	.string "Three very famous girls\nhave fallen asleep on Mom.\p"
	.string "Riko still gives a tiny\nbark in her dreams.\p"
	.string "Bijuu's paws twitch.\nPenny's chin rests on\p"
	.string "Mom's hand.\p"
	.string "Champion can wait. This is\ntheir favorite title:\p"
	.string "Mom's girls.$"

TrioCamp_RikoHello:
	.string "Riko has inspected camp\nand approved the\p"
	.string "acoustics.\p"
	.string "BARK!$"

TrioCamp_BijuuHello:
	.string "Bijuu watches a basket as\nif it has personally\p"
	.string "offended her.$"

TrioCamp_PennyHello:
	.string "Penny comes closer on her\nown. Her tail says this\p"
	.string "room feels safe.$"

TrioCamp_PetRikoText:
	.string "Riko leans into Mom's\nhand.\p"
	.string "She would like everyone to\nknow this was her idea.$"

TrioCamp_PetBijuuText:
	.string "Bijuu pushes her forehead\ninto Mom's palm.\p"
	.string "Then she pretends she was\njust passing through.$"

TrioCamp_PetPennyText:
	.string "Penny settles against\nMom's knee with a long,\p"
	.string "happy sigh.\p"
	.string "No rush. No noise. Just\nher favorite person.$"

TrioCamp_ChickyOffer:
	.string "Give Riko one Chicky Fil-A\nfrom your Bag?\p"
	.string "Camp will use it up.$"

TrioCamp_SpringsOffer:
	.string "Play with one of Bijuu's\nSprings from your Bag?\p"
	.string "Camp will use it up.$"

TrioCamp_PupCupOffer:
	.string "Give Penny one Pup Cup\nfrom your Bag?\p"
	.string "Camp will use it up.$"

TrioCamp_FavoriteHappy:
	.string "Her favorite! Mom is\nclearly the best person in\p"
	.string "this entire room.\p"
	.string "The family counter goes up\nby one.$"

TrioCamp_NoFavoriteText:
	.string "You don't have that\nfavorite in your Bag.\p"
	.string "She still has Mom. Petting\nand games are always free.$"

TrioCamp_RikoGameOffer:
	.string "Riko's important barking\ntest!\p"
	.string "Count her barks in three\nrounds. Want to play?$"

TrioCamp_BijuuGameOffer:
	.string "Bijuu has hidden her toy\nin a floor basket.\p"
	.string "Find it together?$"

TrioCamp_PennyGameOffer:
	.string "Penny wants to fetch the\ncamp's play keys.\p"
	.string "Find the right basket and\ncall her over. Two turns?$"

TrioCamp_HintLeftText:
	.string "The clue points to the\nleft basket, beside the\p"
	.string "bed.$"

TrioCamp_HintMiddleText:
	.string "The clue points to the\nmiddle basket, nearer the\p"
	.string "table.$"

TrioCamp_HintRightText:
	.string "The clue points to the\nright basket, below the\p"
	.string "shelves.$"

TrioCamp_ListenText:
	.string "Listen to Riko!$"

TrioCamp_HowManyText:
	.string "How many barks?$"

TrioCamp_RikoCorrectText:
	.string "Correct! Riko looks very\nimpressed with her\p"
	.string "student.$"

TrioCamp_RikoWrongText:
	.string "Riko provides one extra\nbark for educational\p"
	.string "reasons.\p"
	.string "Try again whenever you\nlike!$"

TrioCamp_RikoWinText:
	.string "Three perfect answers!\p"
	.string "Riko has promoted Mom to\nOfficial Bark Interpreter.$"

TrioCamp_BijuuWinText:
	.string "There's the toy! Bijuu\npounces before Mom can\p"
	.string "pick it up.\p"
	.string "A flawless investigation.\nBijuu takes all the\p"
	.string "credit.$"

TrioCamp_PennyFetchText:
	.string "Mom calls softly. Penny\nfinds the camp keys and\p"
	.string "beams.\p"
	.string "She brings them back with\na proud little wiggle.$"

TrioCamp_PennyWinText:
	.string "Two happy deliveries!\p"
	.string "Penny knows Mom will\nalways be there when she\p"
	.string "comes back.$"

TrioCamp_BasketWrongText:
	.string "Nothing here this time.\p"
	.string "No hurry. Follow the clue.$"

TrioCamp_BasketIdleText:
	.string "A basket of camp toys.\p"
	.string "Ask Bijuu or Penny to play\na finding game.$"

TrioCamp_StatsIntro:
	.string "Our family, by the\nnumbers.\p"
	.string "Adventure totals were\nalready saved by the game.\p"
	.string "Personal counters begin\nwith this update. Older\p"
	.string "uses can't be recovered.\p"
	.string "They count successful Bag\nuses and camp favorites.\p"
	.string "Held-item effects aren't\ncounted. Form changes\p"
	.string "include turning back.\p"
	.string "Every completed camp game\ncounts once. Visits and\p"
	.string "petting count each time.$"

TrioCamp_StatsAdventure:
	.string "Steps: {STR_VAR_1}\p"
	.string "Battles: {STR_VAR_2}\p"
	.string "Caught: {STR_VAR_3}$"

TrioCamp_StatsRests:
	.string "Home rests: {STR_VAR_1}\p"
	.string "Center visits: {STR_VAR_2}\p"
	.string "Evolutions: {STR_VAR_3}$"

TrioCamp_StatsWawa:
	.string "Wawa S: {STR_VAR_1}\p"
	.string "Wawa M: {STR_VAR_2}\p"
	.string "Wawa L: {STR_VAR_3}$"

TrioCamp_StatsFavorites:
	.string "Chicky Fil-A: {STR_VAR_1}\p"
	.string "Bijuu's Springs: {STR_VAR_2}\p"
	.string "Pup Cups: {STR_VAR_3}$"

TrioCamp_StatsCamp:
	.string "Form changes: {STR_VAR_1}\p"
	.string "Camp visits: {STR_VAR_2}\p"
	.string "Games won: {STR_VAR_3}$"

TrioCamp_StatsPets:
	.string "Petting: {STR_VAR_1}\p"
	.string "Enough love to fill a\nroom. Still room for more.$"

TrioCamp_MemoryText:
	.string "Trio Camp\p"
	.string "Riko claimed the cushion.\nBijuu claimed the tail.\p"
	.string "Penny found a spot beside\nMom, with both sisters\p"
	.string "close.\p"
	.string "No battles to win. Nothing\nto prove.\p"
	.string "Just a little room where\nall three girls fit.$"

TrioCamp_ChecklistHint:
	.string "Camp memory - waiting\p"
	.string "Rest with all three girls\nin New Bark's southwest\p"
	.string "house.$"

TrioCamp_ChecklistSavedText:
	.string "Camp memory - saved\p"
	.string "A quiet room for Mom and\nall three girls.$"

