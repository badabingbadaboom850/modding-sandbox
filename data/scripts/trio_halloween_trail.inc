@ Optional saved Halloween puzzles. No battles, real-time gates or forced party edits.
TrioHalloween_Offer::
	lockall
	faceplayer
	playmoncry SPECIES_GASTLY, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioHalloween_OfferText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioHalloween_End
	setvar VAR_TRIO_HALLOWEEN_RETURN, 0
	closemessage
	warp MAP_TRIO_HALLOWEEN_TRAIL, 12, 15
	waitstate
	goto TrioHalloween_End
TrioHalloween_Exit::
	lockall
	faceplayer
	msgbox TrioHalloween_ExitText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioHalloween_End
	goto TrioHalloween_Return
TrioHalloween_End:
	releaseall
	end
TrioHalloween_Memory::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_HALLOWEEN_RIKO, 3, TrioHalloween_RikoPrize
	msgbox TrioHalloween_MemoryOffer, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioHalloween_End
	msgbox TrioHalloween_MemoryPattern, MSGBOX_DEFAULT
	msgbox TrioHalloween_MemoryAsk0, MSGBOX_DEFAULT
	closemessage
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrioHalloween_PomWord, TrioHalloween_BooWord, TrioHalloween_TreatWord, TrioHalloween_BackWord
	goto_if_eq VAR_RESULT, 3, TrioHalloween_End
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, TrioHalloween_End
	goto_if_ne VAR_RESULT, 1, TrioHalloween_MemoryWrong
	msgbox TrioHalloween_MemoryAsk1, MSGBOX_DEFAULT
	closemessage
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrioHalloween_PomWord, TrioHalloween_BooWord, TrioHalloween_TreatWord, TrioHalloween_BackWord
	goto_if_eq VAR_RESULT, 3, TrioHalloween_End
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, TrioHalloween_End
	goto_if_ne VAR_RESULT, 0, TrioHalloween_MemoryWrong
	msgbox TrioHalloween_MemoryAsk2, MSGBOX_DEFAULT
	closemessage
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrioHalloween_PomWord, TrioHalloween_BooWord, TrioHalloween_TreatWord, TrioHalloween_BackWord
	goto_if_eq VAR_RESULT, 3, TrioHalloween_End
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, TrioHalloween_End
	goto_if_ne VAR_RESULT, 2, TrioHalloween_MemoryWrong
	setvar VAR_TRIO_HALLOWEEN_RIKO, 3
	msgbox TrioHalloween_MemoryWin, MSGBOX_DEFAULT
	goto TrioHalloween_RikoPrize
TrioHalloween_MemoryWrong:
	msgbox TrioHalloween_MemoryWrongText, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_CandyHost::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_HALLOWEEN_BIJUU, 3, TrioHalloween_BijuuPrize
	msgbox TrioHalloween_CandyHint, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_Fish::
	lockall
	msgbox TrioHalloween_FishText, MSGBOX_DEFAULT
	goto_if_gt VAR_TRIO_HALLOWEEN_BIJUU, 0, TrioHalloween_AlreadyFound
	goto_if_ne VAR_TRIO_HALLOWEEN_BIJUU, 0, TrioHalloween_WrongOrder
	setvar VAR_TRIO_HALLOWEEN_BIJUU, 1
	msgbox TrioHalloween_CandyFound, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_Moon::
	lockall
	msgbox TrioHalloween_MoonText, MSGBOX_DEFAULT
	goto_if_gt VAR_TRIO_HALLOWEEN_BIJUU, 1, TrioHalloween_AlreadyFound
	goto_if_ne VAR_TRIO_HALLOWEEN_BIJUU, 1, TrioHalloween_WrongOrder
	setvar VAR_TRIO_HALLOWEEN_BIJUU, 2
	msgbox TrioHalloween_CandyFound, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_Star::
	lockall
	msgbox TrioHalloween_StarText, MSGBOX_DEFAULT
	goto_if_gt VAR_TRIO_HALLOWEEN_BIJUU, 2, TrioHalloween_AlreadyFound
	goto_if_ne VAR_TRIO_HALLOWEEN_BIJUU, 2, TrioHalloween_WrongOrder
	setvar VAR_TRIO_HALLOWEEN_BIJUU, 3
	msgbox TrioHalloween_CandyFound, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_PumpkinHost::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_HALLOWEEN_PENNY, 3, TrioHalloween_PennyPrize
	msgbox TrioHalloween_PumpkinHint, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_Left::
	lockall
	faceplayer
	playmoncry SPECIES_PUMPKABOO, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioHalloween_LeftText, MSGBOX_DEFAULT
	goto_if_gt VAR_TRIO_HALLOWEEN_PENNY, 0, TrioHalloween_AlreadyFound
	goto_if_ne VAR_TRIO_HALLOWEEN_PENNY, 0, TrioHalloween_WrongOrder
	setvar VAR_TRIO_HALLOWEEN_PENNY, 1
	msgbox TrioHalloween_PumpkinFound, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_Right::
	lockall
	faceplayer
	playmoncry SPECIES_PUMPKABOO, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioHalloween_RightText, MSGBOX_DEFAULT
	goto_if_gt VAR_TRIO_HALLOWEEN_PENNY, 1, TrioHalloween_AlreadyFound
	goto_if_ne VAR_TRIO_HALLOWEEN_PENNY, 1, TrioHalloween_WrongOrder
	setvar VAR_TRIO_HALLOWEEN_PENNY, 2
	msgbox TrioHalloween_PumpkinFound, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_Middle::
	lockall
	faceplayer
	playmoncry SPECIES_PUMPKABOO, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioHalloween_MiddleText, MSGBOX_DEFAULT
	goto_if_gt VAR_TRIO_HALLOWEEN_PENNY, 2, TrioHalloween_AlreadyFound
	goto_if_ne VAR_TRIO_HALLOWEEN_PENNY, 2, TrioHalloween_WrongOrder
	setvar VAR_TRIO_HALLOWEEN_PENNY, 3
	msgbox TrioHalloween_PumpkinFound, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_WrongOrder:
	msgbox TrioHalloween_WrongOrderText, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_AlreadyFound:
	msgbox TrioHalloween_AlreadyFoundText, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_RikoPrize:
	checkitem ITEM_RIKOS_WITCH_HAT
	goto_if_eq VAR_RESULT, TRUE, TrioHalloween_RikoOwned
	giveitem ITEM_RIKOS_WITCH_HAT
	goto_if_eq VAR_RESULT, FALSE, TrioHalloween_FullBag
TrioHalloween_RikoOwned:
	setvar VAR_TRIO_HALLOWEEN_RIKO, 4
	msgbox TrioHalloween_RikoReady, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_BijuuPrize:
	checkitem ITEM_BIJUUS_VAMPIRE_CAPE
	goto_if_eq VAR_RESULT, TRUE, TrioHalloween_BijuuOwned
	giveitem ITEM_BIJUUS_VAMPIRE_CAPE
	goto_if_eq VAR_RESULT, FALSE, TrioHalloween_FullBag
TrioHalloween_BijuuOwned:
	setvar VAR_TRIO_HALLOWEEN_BIJUU, 4
	msgbox TrioHalloween_BijuuReady, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_PennyPrize:
	checkitem ITEM_PENNYS_PUMPKIN_SUIT
	goto_if_eq VAR_RESULT, TRUE, TrioHalloween_PennyOwned
	giveitem ITEM_PENNYS_PUMPKIN_SUIT
	goto_if_eq VAR_RESULT, FALSE, TrioHalloween_FullBag
TrioHalloween_PennyOwned:
	setvar VAR_TRIO_HALLOWEEN_PENNY, 4
	msgbox TrioHalloween_PennyReady, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_FullBag:
	msgbox TrioHalloween_FullBagText, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_Riko::
	lockall
	faceplayer
	msgbox TrioHalloween_RikoText, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_Bijuu::
	lockall
	faceplayer
	msgbox TrioHalloween_BijuuText, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_Penny::
	lockall
	faceplayer
	msgbox TrioHalloween_PennyText, MSGBOX_DEFAULT
	goto TrioHalloween_End
TrioHalloween_OfferText:
	.string "Gastly: Boo! A friendly\nboo.\pVisit our Trick-or-Treat\nTrail?\pThree little games. Three\ncostumes. No scary\pbattles!\pYou can leave anytime.\nYour progress stays saved.$"
TrioHalloween_ExitText:
	.string "Gastly: Ready to go home?\pThe ghosts will keep your\nprogress. Come back\panytime!$"
TrioHalloween_MemoryOffer:
	.string "Gastly: Riko wants a witch\nhat!\pRemember my three spooky\nwords? Wrong guesses are\pfine.$"
TrioHalloween_MemoryPattern:
	.string "BOO! POM! TREAT!\pRemember that order. Riko\nis already thinking of\psnacks.$"
TrioHalloween_MemoryAsk0:
	.string "What was the first word?$"
TrioHalloween_MemoryAsk1:
	.string "What was the second word?$"
TrioHalloween_MemoryAsk2:
	.string "What was the last word?$"
TrioHalloween_MemoryWin:
	.string "Gastly: BOO-tiful!\pRiko has earned her witch\nhat. Her snack spell is\pready.$"
TrioHalloween_MemoryWrongText:
	.string "Gastly: Oops! Riko barked\nover my spooky words.\pNo harm done. Talk to me\nand try again!$"
TrioHalloween_PomWord:
	.string "POM$"
TrioHalloween_BooWord:
	.string "BOO$"
TrioHalloween_TreatWord:
	.string "TREAT$"
TrioHalloween_BackWord:
	.string "Cancel$"
TrioHalloween_CandyHint:
	.string "Haunter: Three treat balls\nare hidden around this\pgarden.\pBijuu follows the ocean\nsmell first: FISH!\pThen the MOON comes out.\nFinish under a STAR.\pFind them in that order.\nReturn to me for her cape!$"
TrioHalloween_FishText:
	.string "FISH treats! A ghost made\npretend sweets for Bijuu.$"
TrioHalloween_MoonText:
	.string "MOON treats! A ghost made\npretend sweets for Bijuu.$"
TrioHalloween_StarText:
	.string "STAR treats! A ghost made\npretend sweets for Bijuu.$"
TrioHalloween_CandyFound:
	.string "Bijuu found the right\ntreat!\pThe ghosts remember it.\nKeep following the clues.$"
TrioHalloween_PumpkinHint:
	.string "Duskull: These Pumpkaboo\nwant to help Penny find\pher outfit.\pStart with the LEFT\npumpkin, where the sun\psets.\pThen visit the RIGHT one,\nwhere the sun rises.\pFinish in the MIDDLE, safe\nbetween her sisters.\pThey only need a hello.\nThen come back for her\psuit!$"
TrioHalloween_LeftText:
	.string "LEFT pumpkin: Boo! A\ngentle little pumpkin\phello.$"
TrioHalloween_RightText:
	.string "RIGHT pumpkin: Boo! A\ngentle little pumpkin\phello.$"
TrioHalloween_MiddleText:
	.string "MIDDLE pumpkin: Boo! A\ngentle little pumpkin\phello.$"
TrioHalloween_PumpkinFound:
	.string "Penny found the right\nfriend!\pOne brave hello at a time.\nHer sisters cheer for her.$"
TrioHalloween_WrongOrderText:
	.string "Not this one just yet.\pYour earlier finds are\nsafe. Ask the host for the\pclue!$"
TrioHalloween_AlreadyFoundText:
	.string "You already found this\none!\pYour progress is safe.\nFollow the next clue.$"
TrioHalloween_RikoReady:
	.string "Riko earned her Halloween\noutfit!\pUse the item on her\nordinary form. Use again\pto revert.\pIt stays reusable forever.\nThe ghosts demand no rent!$"
TrioHalloween_BijuuReady:
	.string "Bijuu earned her Halloween\noutfit!\pUse the item on her\nordinary form. Use again\pto revert.\pIt stays reusable forever.\nThe ghosts demand no rent!$"
TrioHalloween_PennyReady:
	.string "Penny earned her Halloween\noutfit!\pUse the item on her\nordinary form. Use again\pto revert.\pIt stays reusable forever.\nThe ghosts demand no rent!$"
TrioHalloween_FullBagText:
	.string "Your Bag is full. Your\ngame is won and your gift\pis safe.\pMake room and talk to this\nhost. No need to win\pagain!$"
TrioHalloween_RikoText:
	.string "Riko tries to bark BOO. It\nmostly sounds like POM.$"
TrioHalloween_BijuuText:
	.string "Bijuu suspects the treats\nare fake. She investigates\panyway.$"
TrioHalloween_PennyText:
	.string "Penny is safe with her\nsisters. The pumpkins say\phello softly.$"

@ Authorized temporary test entrance; caller already locks the home mailbox.
TrioHalloween_TestOffer::
	msgbox TrioHalloween_TestOfferText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioHalloween_TestDecline
	setvar VAR_TRIO_HALLOWEEN_RETURN, 1
	closemessage
	warp MAP_TRIO_HALLOWEEN_TRAIL, 12, 15
	waitstate
	goto TrioHalloween_End
TrioHalloween_TestDecline:
	return
TrioHalloween_WalkExit::
	lockall
	goto TrioHalloween_Return
TrioHalloween_Return:
	closemessage
	goto_if_eq VAR_TRIO_HALLOWEEN_RETURN, 1, TrioHalloween_ReturnNewBark
	warp MAP_ECRUTEAK_CITY_HOUSE4, 8, 6
	waitstate
	goto TrioHalloween_End
TrioHalloween_ReturnNewBark:
	warp MAP_NEWBARK_TOWN, 18, 12
	waitstate
	goto TrioHalloween_End
TrioHalloween_TestOfferText:
	.string "Halloween test trip?\nPlay three ghost games!\pThis mailbox trip returns\nyou safely to New Bark.$"
