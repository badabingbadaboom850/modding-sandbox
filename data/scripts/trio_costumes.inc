@ Optional cosmetic gifts. Bag possession records receipt; courier uses audited trainer flag.
TrioCostume_Balloon::
	lock
	faceplayer
	checkitem ITEM_RIKOS_BALLOON
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_BalloonAgain
	call TrioParty_CheckRiko
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_BringRiko
	msgbox TrioCostume_BalloonOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_Close
	giveitem ITEM_RIKOS_BALLOON
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_FullBag
	msgbox TrioCostume_BalloonReady, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_BalloonAgain:
	msgbox TrioCostume_BalloonReady, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_BringRiko:
	msgbox TrioCostume_RikoHint, MSGBOX_DEFAULT
	goto TrioCostume_Close

TrioCostume_Box::
	lock
	faceplayer
	checkitem ITEM_BIJUUS_BOX
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_BoxAgain
	checktrainerflag TRAINER_COSTUME_COURIER
	goto_if TRUE, TrioCostume_BoxClaim
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_BringBijuu
	msgbox TrioCostume_BoxOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_Close
	trainerbattle_no_intro TRAINER_COSTUME_COURIER, TrioCostume_CourierDefeat
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioCostume_Close
TrioCostume_BoxClaim:
	msgbox TrioCostume_BoxChoice, MSGBOX_DEFAULT
	giveitem ITEM_BIJUUS_BOX
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_FullBag
TrioCostume_BoxAgain:
	msgbox TrioCostume_BoxReady, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_BringBijuu:
	msgbox TrioCostume_BijuuHint, MSGBOX_DEFAULT
	goto TrioCostume_Close

TrioCostume_Hotdog::
	lock
	faceplayer
	checkitem ITEM_PENNYS_HOTDOG_BUN
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_HotdogAgain
	call TrioParty_CheckPenny
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_BringPenny
	msgbox TrioCostume_HotdogOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_Close
	giveitem ITEM_PENNYS_HOTDOG_BUN
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_FullBag
TrioCostume_HotdogAgain:
	msgbox TrioCostume_HotdogReady, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_BringPenny:
	msgbox TrioCostume_PennyHint, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_FullBag:
	msgbox TrioCostume_BagText, MSGBOX_DEFAULT
TrioCostume_Close:
	release
	end

TrioCostume_BalloonOffer:
	.string "I sell party balloons!\nRiko picked the pink one.\pShe is clearly the\nbirthday girl. Always.\pWant a balloon costume\nfor your little diva?$"
TrioCostume_BalloonReady:
	.string "Use Riko Balloon on\nregular Riko to dress up.\pUse it again to return.\nSame Riko, more drama!$"
TrioCostume_RikoHint:
	.string "Bring Riko! I have a\npink balloon just for her.$"
TrioCostume_BoxOffer:
	.string "I'm Morgan, a courier!\nBijuu likes my parcels.\pWin a friendly battle and\nI'll give her a fancy toy.\pWant to battle? My pair\nare both level 12.$"
TrioCostume_CourierDefeat:
	.string "Special delivery:\nOne very bruised ego!$"
TrioCostume_BoxChoice:
	.string "Here is the fancy toy!\nWait... Bijuu chose a box?\pOf course she did.\nThe box is hers!$"
TrioCostume_BoxReady:
	.string "Use Bijuu Box on regular\nBijuu to wear her box.\pUse it again to return.\nPremium cardboard, free!$"
TrioCostume_BijuuHint:
	.string "Bring Bijuu! I have a toy\nfor a very curious cocoa.$"
TrioCostume_HotdogOffer:
	.string "My hot dog stand needs\na very cute mascot.\pPenny is blonde, long,\nand absolutely perfect.\pMay I give her a little\nhot dog bun costume?$"
TrioCostume_HotdogReady:
	.string "Use Penny Hot Dog on\nregular Penny to dress up.\pUse it again to return.\nAll dog. Extra ketchup.$"
TrioCostume_PennyHint:
	.string "Bring Penny! My food stand\ncould use a golden mascot.$"
TrioCostume_BagText:
	.string "Your Bag is full!\nCome back with some room.\pYour gift is safe with me.\nNo extra battle needed.$"
