@ Permanent optional seasonal chapters. Saved rounds and pending rewards survive visits/reloads.
TrioSeasonFall_Offer::
	lockall
	faceplayer
	goto_if_unset FLAG_BADGE06_GET, TrioSeasonFall_NotReady
	msgbox TrioSeasonFall_OfferText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSeasonFall_End
	closemessage
	warp MAP_TRIO_SEASON_FALL, 12, 15
	waitstate
	goto TrioSeasonFall_End
TrioSeasonFall_NotReady::
	msgbox TrioSeasonFall_GateText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Exit::
	lockall
	faceplayer
	msgbox TrioSeasonFall_ExitText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSeasonFall_End
	goto TrioSeasonFall_Return
TrioSeasonFall_WalkExit::
	lockall
	goto TrioSeasonFall_Return
TrioSeasonFall_Return::
	closemessage
	warp MAP_MAHOGANY_TOWN_POKEMON_CENTER, 7, 7
	waitstate
	goto TrioSeasonFall_End
TrioSeasonFall_End::
	releaseall
	end
TrioSeasonFall_Host::
	lockall
	faceplayer
	goto_if_eq VAR_TRIO_FALL_STATE, 2, TrioSeasonFall_Prize
	goto_if_eq VAR_TRIO_FALL_STATE, 1, TrioSeasonFall_Hint
	msgbox TrioSeasonFall_StartText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSeasonFall_End
	random 3
	copyvar VAR_TRIO_FALL_ROUND, VAR_RESULT
	setvar VAR_TRIO_FALL_PROGRESS, 0
	setvar VAR_TRIO_FALL_SNACK, 0
	setvar VAR_TRIO_FALL_STATE, 1
	goto TrioSeasonFall_Hint
TrioSeasonFall_Hint::
	goto_if_eq VAR_TRIO_FALL_ROUND, 0, TrioSeasonFall_Hint0
	goto_if_eq VAR_TRIO_FALL_ROUND, 1, TrioSeasonFall_Hint1
	goto_if_eq VAR_TRIO_FALL_ROUND, 2, TrioSeasonFall_Hint2
	goto TrioSeasonFall_End
TrioSeasonFall_Hint0::
	msgbox TrioSeasonFall_Pattern0, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Hint1::
	msgbox TrioSeasonFall_Pattern1, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Hint2::
	msgbox TrioSeasonFall_Pattern2, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Choice0::
	lockall
	faceplayer
	msgbox TrioSeasonFall_LeafText0, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	goto TrioSeasonFall_Check
TrioSeasonFall_Choice1::
	lockall
	faceplayer
	msgbox TrioSeasonFall_LeafText1, MSGBOX_DEFAULT
	setvar VAR_0x8004, 1
	goto TrioSeasonFall_Check
TrioSeasonFall_Choice2::
	lockall
	faceplayer
	msgbox TrioSeasonFall_LeafText2, MSGBOX_DEFAULT
	setvar VAR_0x8004, 2
	goto TrioSeasonFall_Check
TrioSeasonFall_Check::
	goto_if_ne VAR_TRIO_FALL_STATE, 1, TrioSeasonFall_Idle
	goto_if_eq VAR_TRIO_FALL_ROUND, 0, TrioSeasonFall_Round0
	goto_if_eq VAR_TRIO_FALL_ROUND, 1, TrioSeasonFall_Round1
	goto_if_eq VAR_TRIO_FALL_ROUND, 2, TrioSeasonFall_Round2
	goto TrioSeasonFall_End
TrioSeasonFall_Round0::
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 0, TrioSeasonFall_Round0Step0
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 1, TrioSeasonFall_Round0Step1
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 2, TrioSeasonFall_Round0Step2
	goto TrioSeasonFall_End
TrioSeasonFall_Round0Step0::
	goto_if_ne VAR_0x8004, 0, TrioSeasonFall_Wrong
	addvar VAR_TRIO_FALL_PROGRESS, 1
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 3, TrioSeasonFall_Win
	msgbox TrioSeasonFall_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Round0Step1::
	goto_if_ne VAR_0x8004, 1, TrioSeasonFall_Wrong
	addvar VAR_TRIO_FALL_PROGRESS, 1
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 3, TrioSeasonFall_Win
	msgbox TrioSeasonFall_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Round0Step2::
	goto_if_ne VAR_0x8004, 2, TrioSeasonFall_Wrong
	addvar VAR_TRIO_FALL_PROGRESS, 1
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 3, TrioSeasonFall_Win
	msgbox TrioSeasonFall_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Round1::
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 0, TrioSeasonFall_Round1Step0
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 1, TrioSeasonFall_Round1Step1
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 2, TrioSeasonFall_Round1Step2
	goto TrioSeasonFall_End
TrioSeasonFall_Round1Step0::
	goto_if_ne VAR_0x8004, 2, TrioSeasonFall_Wrong
	addvar VAR_TRIO_FALL_PROGRESS, 1
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 3, TrioSeasonFall_Win
	msgbox TrioSeasonFall_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Round1Step1::
	goto_if_ne VAR_0x8004, 0, TrioSeasonFall_Wrong
	addvar VAR_TRIO_FALL_PROGRESS, 1
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 3, TrioSeasonFall_Win
	msgbox TrioSeasonFall_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Round1Step2::
	goto_if_ne VAR_0x8004, 1, TrioSeasonFall_Wrong
	addvar VAR_TRIO_FALL_PROGRESS, 1
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 3, TrioSeasonFall_Win
	msgbox TrioSeasonFall_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Round2::
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 0, TrioSeasonFall_Round2Step0
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 1, TrioSeasonFall_Round2Step1
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 2, TrioSeasonFall_Round2Step2
	goto TrioSeasonFall_End
TrioSeasonFall_Round2Step0::
	goto_if_ne VAR_0x8004, 1, TrioSeasonFall_Wrong
	addvar VAR_TRIO_FALL_PROGRESS, 1
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 3, TrioSeasonFall_Win
	msgbox TrioSeasonFall_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Round2Step1::
	goto_if_ne VAR_0x8004, 2, TrioSeasonFall_Wrong
	addvar VAR_TRIO_FALL_PROGRESS, 1
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 3, TrioSeasonFall_Win
	msgbox TrioSeasonFall_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Round2Step2::
	goto_if_ne VAR_0x8004, 0, TrioSeasonFall_Wrong
	addvar VAR_TRIO_FALL_PROGRESS, 1
	goto_if_eq VAR_TRIO_FALL_PROGRESS, 3, TrioSeasonFall_Win
	msgbox TrioSeasonFall_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Wrong::
	msgbox TrioSeasonFall_WrongText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Idle::
	msgbox TrioSeasonFall_IdleText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Win::
	setvar VAR_TRIO_FALL_STATE, 2
	msgbox TrioSeasonFall_WinText, MSGBOX_DEFAULT
	goto TrioSeasonFall_Prize
TrioSeasonFall_Prize::
	goto_if_eq VAR_TRIO_FALL_GIFTS, 0, TrioSeasonFall_Gift0
	goto_if_eq VAR_TRIO_FALL_GIFTS, 1, TrioSeasonFall_Gift1
	goto_if_eq VAR_TRIO_FALL_GIFTS, 2, TrioSeasonFall_Gift2
	goto TrioSeasonFall_Snack
TrioSeasonFall_Gift0::
	checkitem ITEM_RIKOS_LEAF_BUNDLE
	goto_if_eq VAR_RESULT, TRUE, TrioSeasonFall_Gift0Owned
	giveitem ITEM_RIKOS_LEAF_BUNDLE
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonFall_Full
TrioSeasonFall_Gift0Owned::
	setvar VAR_TRIO_FALL_GIFTS, 1
	goto TrioSeasonFall_Prize
TrioSeasonFall_Gift1::
	checkitem ITEM_COCOAS_KNIT_SET
	goto_if_eq VAR_RESULT, TRUE, TrioSeasonFall_Gift1Owned
	giveitem ITEM_COCOAS_KNIT_SET
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonFall_Full
TrioSeasonFall_Gift1Owned::
	setvar VAR_TRIO_FALL_GIFTS, 2
	goto TrioSeasonFall_Prize
TrioSeasonFall_Gift2::
	checkitem ITEM_PENNYS_CARDIGAN
	goto_if_eq VAR_RESULT, TRUE, TrioSeasonFall_Gift2Owned
	giveitem ITEM_PENNYS_CARDIGAN
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonFall_Full
TrioSeasonFall_Gift2Owned::
	setvar VAR_TRIO_FALL_GIFTS, 3
	goto TrioSeasonFall_Prize
TrioSeasonFall_Snack::
	goto_if_eq VAR_TRIO_FALL_SNACK, 1, TrioSeasonFall_Claimed
	giveitem ITEM_POTION, 1
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonFall_Full
	setvar VAR_TRIO_FALL_SNACK, 1
TrioSeasonFall_Claimed::
	setvar VAR_TRIO_FALL_STATE, 0
	msgbox TrioSeasonFall_ClaimedText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Full::
	msgbox TrioSeasonFall_FullText, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Girl0::
	lockall
	faceplayer
	playmoncry SPECIES_RIKO, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSeasonFall_GirlText0, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Girl1::
	lockall
	faceplayer
	playmoncry SPECIES_BIJUU, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSeasonFall_GirlText1, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_Girl2::
	lockall
	faceplayer
	playmoncry SPECIES_FIDOUGH, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSeasonFall_GirlText2, MSGBOX_DEFAULT
	goto TrioSeasonFall_End
TrioSeasonFall_OfferText:
	.string "Leaf-Pile Picnic waits!\nWould you like to visit?$"
TrioSeasonFall_GateText:
	.string "Jasmine first. Then come\nshare a leaf-pile picnic.$"
TrioSeasonFall_ExitText:
	.string "Head back to the Center?\nYour round will wait here.$"
TrioSeasonFall_StartText:
	.string "Search the leaf piles.\pWin outfits once, then\nsnacks. Play a round?$"
TrioSeasonFall_CorrectText:
	.string "A perfect little choice!\nOne step closer to smiles.$"
TrioSeasonFall_WrongText:
	.string "That is not the next one.\nYour progress is safe.$"
TrioSeasonFall_IdleText:
	.string "Ask the host for a round.\nYour sisters are waiting!$"
TrioSeasonFall_WinText:
	.string "Three happy sisters!\nYou finished this round.$"
TrioSeasonFall_ClaimedText:
	.string "Gifts are yours forever.\nReturn for a varied round!$"
TrioSeasonFall_FullText:
	.string "Your Bag is full.\nYour gifts will wait.$"
TrioSeasonFall_Back:
	.string "Later$"
TrioSeasonFall_GirlText0:
	.string "Riko rustles every leaf.\nFall needs a royal pom!$"
TrioSeasonFall_GirlText1:
	.string "Bijuu tucks in her scarf.\nCozy cocoa, cozy company.$"
TrioSeasonFall_GirlText2:
	.string "Penny loves her sweater.\nGolden ears, golden fall.$"
TrioSeasonFall_Pattern0:
	.string "Find leaves in this order:\nMaple, Oak, Gold.$"
TrioSeasonFall_Pattern1:
	.string "Find leaves in this order:\nGold, Maple, Oak.$"
TrioSeasonFall_Pattern2:
	.string "Find leaves in this order:\nOak, Gold, Maple.$"
TrioSeasonFall_Word0:
	.string "Maple$"
TrioSeasonFall_Word1:
	.string "Oak$"
TrioSeasonFall_Word2:
	.string "Gold$"
TrioSeasonThanksgiving_Offer::
	lockall
	faceplayer
	goto_if_unset FLAG_BADGE01_GET, TrioSeasonThanksgiving_NotReady
	goto_if_unset FLAG_BADGE02_GET, TrioSeasonThanksgiving_NotReady
	goto_if_unset FLAG_BADGE03_GET, TrioSeasonThanksgiving_NotReady
	goto_if_unset FLAG_BADGE04_GET, TrioSeasonThanksgiving_NotReady
	goto_if_unset FLAG_BADGE05_GET, TrioSeasonThanksgiving_NotReady
	goto_if_unset FLAG_BADGE06_GET, TrioSeasonThanksgiving_NotReady
	goto_if_unset FLAG_BADGE07_GET, TrioSeasonThanksgiving_NotReady
	goto_if_unset FLAG_BADGE08_GET, TrioSeasonThanksgiving_NotReady
	msgbox TrioSeasonThanksgiving_OfferText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSeasonThanksgiving_End
	closemessage
	warp MAP_TRIO_SEASON_THANKSGIVING, 12, 15
	waitstate
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_NotReady::
	msgbox TrioSeasonThanksgiving_GateText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_Exit::
	lockall
	faceplayer
	msgbox TrioSeasonThanksgiving_ExitText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSeasonThanksgiving_End
	goto TrioSeasonThanksgiving_Return
TrioSeasonThanksgiving_WalkExit::
	lockall
	goto TrioSeasonThanksgiving_Return
TrioSeasonThanksgiving_Return::
	closemessage
	warp MAP_BLACKTHORN_CITY_POKEMON_CENTER, 7, 7
	waitstate
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_End::
	releaseall
	end
TrioSeasonThanksgiving_Host::
	lockall
	faceplayer
	goto_if_eq VAR_TRIO_THANKSGIVING_STATE, 2, TrioSeasonThanksgiving_Prize
	goto_if_eq VAR_TRIO_THANKSGIVING_STATE, 1, TrioSeasonThanksgiving_Hint
	msgbox TrioSeasonThanksgiving_StartText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSeasonThanksgiving_End
	random 3
	copyvar VAR_TRIO_THANKSGIVING_ROUND, VAR_RESULT
	setvar VAR_TRIO_THANKSGIVING_PROGRESS, 0
	setvar VAR_TRIO_THANKSGIVING_SNACK, 0
	setvar VAR_TRIO_THANKSGIVING_STATE, 1
	goto TrioSeasonThanksgiving_Hint
TrioSeasonThanksgiving_Hint::
	goto_if_eq VAR_TRIO_THANKSGIVING_ROUND, 0, TrioSeasonThanksgiving_Hint0
	goto_if_eq VAR_TRIO_THANKSGIVING_ROUND, 1, TrioSeasonThanksgiving_Hint1
	goto_if_eq VAR_TRIO_THANKSGIVING_ROUND, 2, TrioSeasonThanksgiving_Hint2
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_Hint0::
	msgbox TrioSeasonThanksgiving_Pattern0, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Play
TrioSeasonThanksgiving_Hint1::
	msgbox TrioSeasonThanksgiving_Pattern1, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Play
TrioSeasonThanksgiving_Hint2::
	msgbox TrioSeasonThanksgiving_Pattern2, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Play
TrioSeasonThanksgiving_Play::
	closemessage
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrioSeasonThanksgiving_Word0, TrioSeasonThanksgiving_Word1, TrioSeasonThanksgiving_Word2, TrioSeasonThanksgiving_Back
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, TrioSeasonThanksgiving_End
	goto_if_eq VAR_RESULT, 3, TrioSeasonThanksgiving_End
	copyvar VAR_0x8004, VAR_RESULT
	goto TrioSeasonThanksgiving_Check
TrioSeasonThanksgiving_Check::
	goto_if_ne VAR_TRIO_THANKSGIVING_STATE, 1, TrioSeasonThanksgiving_Idle
	goto_if_eq VAR_TRIO_THANKSGIVING_ROUND, 0, TrioSeasonThanksgiving_Round0
	goto_if_eq VAR_TRIO_THANKSGIVING_ROUND, 1, TrioSeasonThanksgiving_Round1
	goto_if_eq VAR_TRIO_THANKSGIVING_ROUND, 2, TrioSeasonThanksgiving_Round2
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_Round0::
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 0, TrioSeasonThanksgiving_Round0Step0
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 1, TrioSeasonThanksgiving_Round0Step1
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 2, TrioSeasonThanksgiving_Round0Step2
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_Round0Step0::
	goto_if_ne VAR_0x8004, 0, TrioSeasonThanksgiving_Wrong
	addvar VAR_TRIO_THANKSGIVING_PROGRESS, 1
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 3, TrioSeasonThanksgiving_Win
	msgbox TrioSeasonThanksgiving_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Play
TrioSeasonThanksgiving_Round0Step1::
	goto_if_ne VAR_0x8004, 1, TrioSeasonThanksgiving_Wrong
	addvar VAR_TRIO_THANKSGIVING_PROGRESS, 1
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 3, TrioSeasonThanksgiving_Win
	msgbox TrioSeasonThanksgiving_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Play
TrioSeasonThanksgiving_Round0Step2::
	goto_if_ne VAR_0x8004, 2, TrioSeasonThanksgiving_Wrong
	addvar VAR_TRIO_THANKSGIVING_PROGRESS, 1
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 3, TrioSeasonThanksgiving_Win
	msgbox TrioSeasonThanksgiving_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Play
TrioSeasonThanksgiving_Round1::
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 0, TrioSeasonThanksgiving_Round1Step0
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 1, TrioSeasonThanksgiving_Round1Step1
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 2, TrioSeasonThanksgiving_Round1Step2
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_Round1Step0::
	goto_if_ne VAR_0x8004, 2, TrioSeasonThanksgiving_Wrong
	addvar VAR_TRIO_THANKSGIVING_PROGRESS, 1
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 3, TrioSeasonThanksgiving_Win
	msgbox TrioSeasonThanksgiving_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Play
TrioSeasonThanksgiving_Round1Step1::
	goto_if_ne VAR_0x8004, 0, TrioSeasonThanksgiving_Wrong
	addvar VAR_TRIO_THANKSGIVING_PROGRESS, 1
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 3, TrioSeasonThanksgiving_Win
	msgbox TrioSeasonThanksgiving_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Play
TrioSeasonThanksgiving_Round1Step2::
	goto_if_ne VAR_0x8004, 1, TrioSeasonThanksgiving_Wrong
	addvar VAR_TRIO_THANKSGIVING_PROGRESS, 1
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 3, TrioSeasonThanksgiving_Win
	msgbox TrioSeasonThanksgiving_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Play
TrioSeasonThanksgiving_Round2::
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 0, TrioSeasonThanksgiving_Round2Step0
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 1, TrioSeasonThanksgiving_Round2Step1
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 2, TrioSeasonThanksgiving_Round2Step2
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_Round2Step0::
	goto_if_ne VAR_0x8004, 1, TrioSeasonThanksgiving_Wrong
	addvar VAR_TRIO_THANKSGIVING_PROGRESS, 1
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 3, TrioSeasonThanksgiving_Win
	msgbox TrioSeasonThanksgiving_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Play
TrioSeasonThanksgiving_Round2Step1::
	goto_if_ne VAR_0x8004, 2, TrioSeasonThanksgiving_Wrong
	addvar VAR_TRIO_THANKSGIVING_PROGRESS, 1
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 3, TrioSeasonThanksgiving_Win
	msgbox TrioSeasonThanksgiving_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Play
TrioSeasonThanksgiving_Round2Step2::
	goto_if_ne VAR_0x8004, 0, TrioSeasonThanksgiving_Wrong
	addvar VAR_TRIO_THANKSGIVING_PROGRESS, 1
	goto_if_eq VAR_TRIO_THANKSGIVING_PROGRESS, 3, TrioSeasonThanksgiving_Win
	msgbox TrioSeasonThanksgiving_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Play
TrioSeasonThanksgiving_Wrong::
	msgbox TrioSeasonThanksgiving_WrongText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_Idle::
	msgbox TrioSeasonThanksgiving_IdleText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_Win::
	setvar VAR_TRIO_THANKSGIVING_STATE, 2
	msgbox TrioSeasonThanksgiving_WinText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_Prize
TrioSeasonThanksgiving_Prize::
	goto_if_eq VAR_TRIO_THANKSGIVING_GIFTS, 0, TrioSeasonThanksgiving_Gift0
	goto_if_eq VAR_TRIO_THANKSGIVING_GIFTS, 1, TrioSeasonThanksgiving_Gift1
	goto_if_eq VAR_TRIO_THANKSGIVING_GIFTS, 2, TrioSeasonThanksgiving_Gift2
	goto TrioSeasonThanksgiving_Snack
TrioSeasonThanksgiving_Gift0::
	checkitem ITEM_RIKOS_FEATHER_FAN
	goto_if_eq VAR_RESULT, TRUE, TrioSeasonThanksgiving_Gift0Owned
	giveitem ITEM_RIKOS_FEATHER_FAN
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonThanksgiving_Full
TrioSeasonThanksgiving_Gift0Owned::
	setvar VAR_TRIO_THANKSGIVING_GIFTS, 1
	goto TrioSeasonThanksgiving_Prize
TrioSeasonThanksgiving_Gift1::
	checkitem ITEM_COCOAS_CHEF_HAT
	goto_if_eq VAR_RESULT, TRUE, TrioSeasonThanksgiving_Gift1Owned
	giveitem ITEM_COCOAS_CHEF_HAT
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonThanksgiving_Full
TrioSeasonThanksgiving_Gift1Owned::
	setvar VAR_TRIO_THANKSGIVING_GIFTS, 2
	goto TrioSeasonThanksgiving_Prize
TrioSeasonThanksgiving_Gift2::
	checkitem ITEM_PENNYS_YAM_WRAP
	goto_if_eq VAR_RESULT, TRUE, TrioSeasonThanksgiving_Gift2Owned
	giveitem ITEM_PENNYS_YAM_WRAP
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonThanksgiving_Full
TrioSeasonThanksgiving_Gift2Owned::
	setvar VAR_TRIO_THANKSGIVING_GIFTS, 3
	goto TrioSeasonThanksgiving_Prize
TrioSeasonThanksgiving_Snack::
	goto_if_eq VAR_TRIO_THANKSGIVING_SNACK, 1, TrioSeasonThanksgiving_Claimed
	giveitem ITEM_SUPER_POTION, 1
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonThanksgiving_Full
	setvar VAR_TRIO_THANKSGIVING_SNACK, 1
TrioSeasonThanksgiving_Claimed::
	setvar VAR_TRIO_THANKSGIVING_STATE, 0
	msgbox TrioSeasonThanksgiving_ClaimedText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_Full::
	msgbox TrioSeasonThanksgiving_FullText, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_Girl0::
	lockall
	faceplayer
	playmoncry SPECIES_RIKO, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSeasonThanksgiving_GirlText0, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_Girl1::
	lockall
	faceplayer
	playmoncry SPECIES_BIJUU, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSeasonThanksgiving_GirlText1, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_Girl2::
	lockall
	faceplayer
	playmoncry SPECIES_FIDOUGH, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSeasonThanksgiving_GirlText2, MSGBOX_DEFAULT
	goto TrioSeasonThanksgiving_End
TrioSeasonThanksgiving_OfferText:
	.string "Thankful Table waits!\nWould you like to visit?$"
TrioSeasonThanksgiving_GateText:
	.string "Earn eight Johto Badges.\nOur thankful table waits.$"
TrioSeasonThanksgiving_ExitText:
	.string "Head back to the Center?\nYour round will wait here.$"
TrioSeasonThanksgiving_StartText:
	.string "Choose each recipe prop.\pWin outfits once, then\nsnacks. Play a round?$"
TrioSeasonThanksgiving_CorrectText:
	.string "A perfect little choice!\nOne step closer to smiles.$"
TrioSeasonThanksgiving_WrongText:
	.string "That is not the next one.\nYour progress is safe.$"
TrioSeasonThanksgiving_IdleText:
	.string "Ask the host for a round.\nYour sisters are waiting!$"
TrioSeasonThanksgiving_WinText:
	.string "Three happy sisters!\nYou finished this round.$"
TrioSeasonThanksgiving_ClaimedText:
	.string "Gifts are yours forever.\nReturn for a varied round!$"
TrioSeasonThanksgiving_FullText:
	.string "Your Bag is full.\nYour gifts will wait.$"
TrioSeasonThanksgiving_Back:
	.string "Later$"
TrioSeasonThanksgiving_GirlText0:
	.string "Riko fans her feathers.\nShe is thankful for you.$"
TrioSeasonThanksgiving_GirlText1:
	.string "Bijuu checks the props.\nFish is her specialty.$"
TrioSeasonThanksgiving_GirlText2:
	.string "Penny is our sweet potato.\nA feast of tiny smiles.$"
TrioSeasonThanksgiving_Pattern0:
	.string "Serve these recipe props:\nCorn, Fish, Yam.$"
TrioSeasonThanksgiving_Pattern1:
	.string "Serve these recipe props:\nYam, Corn, Fish.$"
TrioSeasonThanksgiving_Pattern2:
	.string "Serve these recipe props:\nFish, Yam, Corn.$"
TrioSeasonThanksgiving_Word0:
	.string "Corn$"
TrioSeasonThanksgiving_Word1:
	.string "Fish$"
TrioSeasonThanksgiving_Word2:
	.string "Yam$"
TrioSeasonChristmas_Offer::
	lockall
	faceplayer
	goto_if_unset FLAG_IS_CHAMPION, TrioSeasonChristmas_NotReady
	msgbox TrioSeasonChristmas_OfferText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSeasonChristmas_End
	closemessage
	warp MAP_TRIO_SEASON_CHRISTMAS, 12, 15
	waitstate
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_NotReady::
	msgbox TrioSeasonChristmas_GateText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Exit::
	lockall
	faceplayer
	msgbox TrioSeasonChristmas_ExitText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSeasonChristmas_End
	goto TrioSeasonChristmas_Return
TrioSeasonChristmas_WalkExit::
	lockall
	goto TrioSeasonChristmas_Return
TrioSeasonChristmas_Return::
	closemessage
	warp MAP_CELADON_CITY_POKEMON_CENTER, 7, 7
	waitstate
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_End::
	releaseall
	end
TrioSeasonChristmas_Host::
	lockall
	faceplayer
	goto_if_eq VAR_TRIO_CHRISTMAS_STATE, 2, TrioSeasonChristmas_Prize
	goto_if_eq VAR_TRIO_CHRISTMAS_STATE, 1, TrioSeasonChristmas_Hint
	msgbox TrioSeasonChristmas_StartText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSeasonChristmas_End
	random 3
	copyvar VAR_TRIO_CHRISTMAS_ROUND, VAR_RESULT
	setvar VAR_TRIO_CHRISTMAS_PROGRESS, 0
	setvar VAR_TRIO_CHRISTMAS_SNACK, 0
	setvar VAR_TRIO_CHRISTMAS_STATE, 1
	goto TrioSeasonChristmas_Hint
TrioSeasonChristmas_Hint::
	goto_if_eq VAR_TRIO_CHRISTMAS_ROUND, 0, TrioSeasonChristmas_Hint0
	goto_if_eq VAR_TRIO_CHRISTMAS_ROUND, 1, TrioSeasonChristmas_Hint1
	goto_if_eq VAR_TRIO_CHRISTMAS_ROUND, 2, TrioSeasonChristmas_Hint2
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Hint0::
	msgbox TrioSeasonChristmas_Pattern0, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Hint1::
	msgbox TrioSeasonChristmas_Pattern1, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Hint2::
	msgbox TrioSeasonChristmas_Pattern2, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Choice0::
	lockall
	faceplayer
	setvar VAR_0x8004, 0
	goto TrioSeasonChristmas_Check
TrioSeasonChristmas_Choice1::
	lockall
	faceplayer
	setvar VAR_0x8004, 1
	goto TrioSeasonChristmas_Check
TrioSeasonChristmas_Choice2::
	lockall
	faceplayer
	setvar VAR_0x8004, 2
	goto TrioSeasonChristmas_Check
TrioSeasonChristmas_Check::
	goto_if_ne VAR_TRIO_CHRISTMAS_STATE, 1, TrioSeasonChristmas_Idle
	goto_if_eq VAR_TRIO_CHRISTMAS_ROUND, 0, TrioSeasonChristmas_Round0
	goto_if_eq VAR_TRIO_CHRISTMAS_ROUND, 1, TrioSeasonChristmas_Round1
	goto_if_eq VAR_TRIO_CHRISTMAS_ROUND, 2, TrioSeasonChristmas_Round2
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Round0::
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 0, TrioSeasonChristmas_Round0Step0
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 1, TrioSeasonChristmas_Round0Step1
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 2, TrioSeasonChristmas_Round0Step2
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Round0Step0::
	goto_if_ne VAR_0x8004, 0, TrioSeasonChristmas_Wrong
	addvar VAR_TRIO_CHRISTMAS_PROGRESS, 1
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 3, TrioSeasonChristmas_Win
	msgbox TrioSeasonChristmas_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Round0Step1::
	goto_if_ne VAR_0x8004, 1, TrioSeasonChristmas_Wrong
	addvar VAR_TRIO_CHRISTMAS_PROGRESS, 1
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 3, TrioSeasonChristmas_Win
	msgbox TrioSeasonChristmas_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Round0Step2::
	goto_if_ne VAR_0x8004, 2, TrioSeasonChristmas_Wrong
	addvar VAR_TRIO_CHRISTMAS_PROGRESS, 1
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 3, TrioSeasonChristmas_Win
	msgbox TrioSeasonChristmas_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Round1::
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 0, TrioSeasonChristmas_Round1Step0
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 1, TrioSeasonChristmas_Round1Step1
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 2, TrioSeasonChristmas_Round1Step2
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Round1Step0::
	goto_if_ne VAR_0x8004, 2, TrioSeasonChristmas_Wrong
	addvar VAR_TRIO_CHRISTMAS_PROGRESS, 1
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 3, TrioSeasonChristmas_Win
	msgbox TrioSeasonChristmas_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Round1Step1::
	goto_if_ne VAR_0x8004, 0, TrioSeasonChristmas_Wrong
	addvar VAR_TRIO_CHRISTMAS_PROGRESS, 1
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 3, TrioSeasonChristmas_Win
	msgbox TrioSeasonChristmas_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Round1Step2::
	goto_if_ne VAR_0x8004, 1, TrioSeasonChristmas_Wrong
	addvar VAR_TRIO_CHRISTMAS_PROGRESS, 1
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 3, TrioSeasonChristmas_Win
	msgbox TrioSeasonChristmas_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Round2::
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 0, TrioSeasonChristmas_Round2Step0
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 1, TrioSeasonChristmas_Round2Step1
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 2, TrioSeasonChristmas_Round2Step2
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Round2Step0::
	goto_if_ne VAR_0x8004, 1, TrioSeasonChristmas_Wrong
	addvar VAR_TRIO_CHRISTMAS_PROGRESS, 1
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 3, TrioSeasonChristmas_Win
	msgbox TrioSeasonChristmas_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Round2Step1::
	goto_if_ne VAR_0x8004, 2, TrioSeasonChristmas_Wrong
	addvar VAR_TRIO_CHRISTMAS_PROGRESS, 1
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 3, TrioSeasonChristmas_Win
	msgbox TrioSeasonChristmas_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Round2Step2::
	goto_if_ne VAR_0x8004, 0, TrioSeasonChristmas_Wrong
	addvar VAR_TRIO_CHRISTMAS_PROGRESS, 1
	goto_if_eq VAR_TRIO_CHRISTMAS_PROGRESS, 3, TrioSeasonChristmas_Win
	msgbox TrioSeasonChristmas_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Wrong::
	msgbox TrioSeasonChristmas_WrongText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Idle::
	msgbox TrioSeasonChristmas_IdleText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Win::
	setvar VAR_TRIO_CHRISTMAS_STATE, 2
	msgbox TrioSeasonChristmas_WinText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_Prize
TrioSeasonChristmas_Prize::
	goto_if_eq VAR_TRIO_CHRISTMAS_GIFTS, 0, TrioSeasonChristmas_Gift0
	goto_if_eq VAR_TRIO_CHRISTMAS_GIFTS, 1, TrioSeasonChristmas_Gift1
	goto_if_eq VAR_TRIO_CHRISTMAS_GIFTS, 2, TrioSeasonChristmas_Gift2
	goto TrioSeasonChristmas_Snack
TrioSeasonChristmas_Gift0::
	checkitem ITEM_POM_SANTA_HAT
	goto_if_eq VAR_RESULT, TRUE, TrioSeasonChristmas_Gift0Owned
	giveitem ITEM_POM_SANTA_HAT
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonChristmas_Full
TrioSeasonChristmas_Gift0Owned::
	setvar VAR_TRIO_CHRISTMAS_GIFTS, 1
	goto TrioSeasonChristmas_Prize
TrioSeasonChristmas_Gift1::
	checkitem ITEM_COCOA_GIFT_BOX
	goto_if_eq VAR_RESULT, TRUE, TrioSeasonChristmas_Gift1Owned
	giveitem ITEM_COCOA_GIFT_BOX
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonChristmas_Full
TrioSeasonChristmas_Gift1Owned::
	setvar VAR_TRIO_CHRISTMAS_GIFTS, 2
	goto TrioSeasonChristmas_Prize
TrioSeasonChristmas_Gift2::
	checkitem ITEM_PENNYS_ANTLERS
	goto_if_eq VAR_RESULT, TRUE, TrioSeasonChristmas_Gift2Owned
	giveitem ITEM_PENNYS_ANTLERS
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonChristmas_Full
TrioSeasonChristmas_Gift2Owned::
	setvar VAR_TRIO_CHRISTMAS_GIFTS, 3
	goto TrioSeasonChristmas_Prize
TrioSeasonChristmas_Snack::
	goto_if_eq VAR_TRIO_CHRISTMAS_SNACK, 1, TrioSeasonChristmas_Claimed
	giveitem ITEM_SUPER_POTION, 1
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonChristmas_Full
	setvar VAR_TRIO_CHRISTMAS_SNACK, 1
TrioSeasonChristmas_Claimed::
	setvar VAR_TRIO_CHRISTMAS_STATE, 0
	msgbox TrioSeasonChristmas_ClaimedText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Full::
	msgbox TrioSeasonChristmas_FullText, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Girl0::
	lockall
	faceplayer
	playmoncry SPECIES_RIKO, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSeasonChristmas_GirlText0, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Girl1::
	lockall
	faceplayer
	playmoncry SPECIES_BIJUU, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSeasonChristmas_GirlText1, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_Girl2::
	lockall
	faceplayer
	playmoncry SPECIES_FIDOUGH, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSeasonChristmas_GirlText2, MSGBOX_DEFAULT
	goto TrioSeasonChristmas_End
TrioSeasonChristmas_OfferText:
	.string "Our gift crew is waiting!\nWould you like to visit?$"
TrioSeasonChristmas_GateText:
	.string "Become League Champion.\nThen help our gift crew.$"
TrioSeasonChristmas_ExitText:
	.string "Head back to the Center?\nYour round will wait here.$"
TrioSeasonChristmas_StartText:
	.string "Deliver in the gift order.\pWin outfits once, then\nsnacks. Play a round?$"
TrioSeasonChristmas_CorrectText:
	.string "A perfect little choice!\nOne step closer to smiles.$"
TrioSeasonChristmas_WrongText:
	.string "That is not the next one.\nYour progress is safe.$"
TrioSeasonChristmas_IdleText:
	.string "Ask the host for a round.\nYour sisters are waiting!$"
TrioSeasonChristmas_WinText:
	.string "Three happy sisters!\nYou finished this round.$"
TrioSeasonChristmas_ClaimedText:
	.string "Gifts are yours forever.\nReturn for a varied round!$"
TrioSeasonChristmas_FullText:
	.string "Your Bag is full.\nYour gifts will wait.$"
TrioSeasonChristmas_Back:
	.string "Later$"
TrioSeasonChristmas_GirlText0:
	.string "Santa Pom checks her list.\nEveryone deserves a smile.$"
TrioSeasonChristmas_GirlText1:
	.string "Bijuu curls into her box.\nShe says she is the gift.$"
TrioSeasonChristmas_GirlText2:
	.string "Penny jingles her antlers.\nSmall paws, big gifts.$"
TrioSeasonChristmas_Pattern0:
	.string "Deliver in this order:\nRiko, Bijuu, Penny.$"
TrioSeasonChristmas_Pattern1:
	.string "Deliver in this order:\nPenny, Riko, Bijuu.$"
TrioSeasonChristmas_Pattern2:
	.string "Deliver in this order:\nBijuu, Penny, Riko.$"
TrioSeasonChristmas_Word0:
	.string "Riko$"
TrioSeasonChristmas_Word1:
	.string "Bijuu$"
TrioSeasonChristmas_Word2:
	.string "Penny$"
TrioSeasonNewYear_Offer::
	lockall
	faceplayer
	goto_if_unset FLAG_BADGE01_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE02_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE03_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE04_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE05_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE06_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE07_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE08_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE09_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE10_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE11_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE12_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE13_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE14_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE15_GET, TrioSeasonNewYear_NotReady
	goto_if_unset FLAG_BADGE16_GET, TrioSeasonNewYear_NotReady
	msgbox TrioSeasonNewYear_OfferText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSeasonNewYear_End
	closemessage
	warp MAP_TRIO_SEASON_NEW_YEAR, 12, 15
	waitstate
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_NotReady::
	msgbox TrioSeasonNewYear_GateText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_Exit::
	lockall
	faceplayer
	msgbox TrioSeasonNewYear_ExitText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSeasonNewYear_End
	goto TrioSeasonNewYear_Return
TrioSeasonNewYear_WalkExit::
	lockall
	goto TrioSeasonNewYear_Return
TrioSeasonNewYear_Return::
	closemessage
	warp MAP_SAFFRON_CITY_POKEMON_CENTER, 7, 7
	waitstate
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_End::
	releaseall
	end
TrioSeasonNewYear_Host::
	lockall
	faceplayer
	goto_if_eq VAR_TRIO_NEW_YEAR_STATE, 2, TrioSeasonNewYear_Prize
	goto_if_eq VAR_TRIO_NEW_YEAR_STATE, 1, TrioSeasonNewYear_Hint
	msgbox TrioSeasonNewYear_StartText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSeasonNewYear_End
	random 3
	copyvar VAR_TRIO_NEW_YEAR_ROUND, VAR_RESULT
	setvar VAR_TRIO_NEW_YEAR_PROGRESS, 0
	setvar VAR_TRIO_NEW_YEAR_SNACK, 0
	setvar VAR_TRIO_NEW_YEAR_STATE, 1
	goto TrioSeasonNewYear_Hint
TrioSeasonNewYear_Hint::
	goto_if_eq VAR_TRIO_NEW_YEAR_ROUND, 0, TrioSeasonNewYear_Hint0
	goto_if_eq VAR_TRIO_NEW_YEAR_ROUND, 1, TrioSeasonNewYear_Hint1
	goto_if_eq VAR_TRIO_NEW_YEAR_ROUND, 2, TrioSeasonNewYear_Hint2
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_Hint0::
	msgbox TrioSeasonNewYear_Pattern0, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Play
TrioSeasonNewYear_Hint1::
	msgbox TrioSeasonNewYear_Pattern1, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Play
TrioSeasonNewYear_Hint2::
	msgbox TrioSeasonNewYear_Pattern2, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Play
TrioSeasonNewYear_Play::
	closemessage
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrioSeasonNewYear_Word0, TrioSeasonNewYear_Word1, TrioSeasonNewYear_Word2, TrioSeasonNewYear_Back
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, TrioSeasonNewYear_End
	goto_if_eq VAR_RESULT, 3, TrioSeasonNewYear_End
	copyvar VAR_0x8004, VAR_RESULT
	goto TrioSeasonNewYear_Check
TrioSeasonNewYear_Check::
	goto_if_ne VAR_TRIO_NEW_YEAR_STATE, 1, TrioSeasonNewYear_Idle
	goto_if_eq VAR_TRIO_NEW_YEAR_ROUND, 0, TrioSeasonNewYear_Round0
	goto_if_eq VAR_TRIO_NEW_YEAR_ROUND, 1, TrioSeasonNewYear_Round1
	goto_if_eq VAR_TRIO_NEW_YEAR_ROUND, 2, TrioSeasonNewYear_Round2
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_Round0::
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 0, TrioSeasonNewYear_Round0Step0
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 1, TrioSeasonNewYear_Round0Step1
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 2, TrioSeasonNewYear_Round0Step2
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_Round0Step0::
	goto_if_ne VAR_0x8004, 0, TrioSeasonNewYear_Wrong
	addvar VAR_TRIO_NEW_YEAR_PROGRESS, 1
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 3, TrioSeasonNewYear_Win
	msgbox TrioSeasonNewYear_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Play
TrioSeasonNewYear_Round0Step1::
	goto_if_ne VAR_0x8004, 1, TrioSeasonNewYear_Wrong
	addvar VAR_TRIO_NEW_YEAR_PROGRESS, 1
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 3, TrioSeasonNewYear_Win
	msgbox TrioSeasonNewYear_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Play
TrioSeasonNewYear_Round0Step2::
	goto_if_ne VAR_0x8004, 2, TrioSeasonNewYear_Wrong
	addvar VAR_TRIO_NEW_YEAR_PROGRESS, 1
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 3, TrioSeasonNewYear_Win
	msgbox TrioSeasonNewYear_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Play
TrioSeasonNewYear_Round1::
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 0, TrioSeasonNewYear_Round1Step0
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 1, TrioSeasonNewYear_Round1Step1
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 2, TrioSeasonNewYear_Round1Step2
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_Round1Step0::
	goto_if_ne VAR_0x8004, 2, TrioSeasonNewYear_Wrong
	addvar VAR_TRIO_NEW_YEAR_PROGRESS, 1
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 3, TrioSeasonNewYear_Win
	msgbox TrioSeasonNewYear_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Play
TrioSeasonNewYear_Round1Step1::
	goto_if_ne VAR_0x8004, 0, TrioSeasonNewYear_Wrong
	addvar VAR_TRIO_NEW_YEAR_PROGRESS, 1
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 3, TrioSeasonNewYear_Win
	msgbox TrioSeasonNewYear_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Play
TrioSeasonNewYear_Round1Step2::
	goto_if_ne VAR_0x8004, 1, TrioSeasonNewYear_Wrong
	addvar VAR_TRIO_NEW_YEAR_PROGRESS, 1
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 3, TrioSeasonNewYear_Win
	msgbox TrioSeasonNewYear_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Play
TrioSeasonNewYear_Round2::
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 0, TrioSeasonNewYear_Round2Step0
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 1, TrioSeasonNewYear_Round2Step1
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 2, TrioSeasonNewYear_Round2Step2
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_Round2Step0::
	goto_if_ne VAR_0x8004, 1, TrioSeasonNewYear_Wrong
	addvar VAR_TRIO_NEW_YEAR_PROGRESS, 1
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 3, TrioSeasonNewYear_Win
	msgbox TrioSeasonNewYear_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Play
TrioSeasonNewYear_Round2Step1::
	goto_if_ne VAR_0x8004, 2, TrioSeasonNewYear_Wrong
	addvar VAR_TRIO_NEW_YEAR_PROGRESS, 1
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 3, TrioSeasonNewYear_Win
	msgbox TrioSeasonNewYear_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Play
TrioSeasonNewYear_Round2Step2::
	goto_if_ne VAR_0x8004, 0, TrioSeasonNewYear_Wrong
	addvar VAR_TRIO_NEW_YEAR_PROGRESS, 1
	goto_if_eq VAR_TRIO_NEW_YEAR_PROGRESS, 3, TrioSeasonNewYear_Win
	msgbox TrioSeasonNewYear_CorrectText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Play
TrioSeasonNewYear_Wrong::
	msgbox TrioSeasonNewYear_WrongText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_Idle::
	msgbox TrioSeasonNewYear_IdleText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_Win::
	setvar VAR_TRIO_NEW_YEAR_STATE, 2
	msgbox TrioSeasonNewYear_WinText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_Prize
TrioSeasonNewYear_Prize::
	goto_if_eq VAR_TRIO_NEW_YEAR_GIFTS, 0, TrioSeasonNewYear_Gift0
	goto_if_eq VAR_TRIO_NEW_YEAR_GIFTS, 1, TrioSeasonNewYear_Gift1
	goto_if_eq VAR_TRIO_NEW_YEAR_GIFTS, 2, TrioSeasonNewYear_Gift2
	goto TrioSeasonNewYear_Snack
TrioSeasonNewYear_Gift0::
	checkitem ITEM_POM_PARTY_HAT
	goto_if_eq VAR_RESULT, TRUE, TrioSeasonNewYear_Gift0Owned
	giveitem ITEM_POM_PARTY_HAT
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonNewYear_Full
TrioSeasonNewYear_Gift0Owned::
	setvar VAR_TRIO_NEW_YEAR_GIFTS, 1
	goto TrioSeasonNewYear_Prize
TrioSeasonNewYear_Gift1::
	checkitem ITEM_COCOA_SILVER_BOW
	goto_if_eq VAR_RESULT, TRUE, TrioSeasonNewYear_Gift1Owned
	giveitem ITEM_COCOA_SILVER_BOW
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonNewYear_Full
TrioSeasonNewYear_Gift1Owned::
	setvar VAR_TRIO_NEW_YEAR_GIFTS, 2
	goto TrioSeasonNewYear_Prize
TrioSeasonNewYear_Gift2::
	checkitem ITEM_PENNYS_STAR_DRESS
	goto_if_eq VAR_RESULT, TRUE, TrioSeasonNewYear_Gift2Owned
	giveitem ITEM_PENNYS_STAR_DRESS
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonNewYear_Full
TrioSeasonNewYear_Gift2Owned::
	setvar VAR_TRIO_NEW_YEAR_GIFTS, 3
	goto TrioSeasonNewYear_Prize
TrioSeasonNewYear_Snack::
	goto_if_eq VAR_TRIO_NEW_YEAR_SNACK, 1, TrioSeasonNewYear_Claimed
	giveitem ITEM_RIKO_PUFFS, 1
	goto_if_eq VAR_RESULT, FALSE, TrioSeasonNewYear_Full
	setvar VAR_TRIO_NEW_YEAR_SNACK, 1
TrioSeasonNewYear_Claimed::
	setvar VAR_TRIO_NEW_YEAR_STATE, 0
	msgbox TrioSeasonNewYear_ClaimedText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_Full::
	msgbox TrioSeasonNewYear_FullText, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_Girl0::
	lockall
	faceplayer
	playmoncry SPECIES_RIKO, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSeasonNewYear_GirlText0, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_Girl1::
	lockall
	faceplayer
	playmoncry SPECIES_BIJUU, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSeasonNewYear_GirlText1, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_Girl2::
	lockall
	faceplayer
	playmoncry SPECIES_FIDOUGH, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSeasonNewYear_GirlText2, MSGBOX_DEFAULT
	goto TrioSeasonNewYear_End
TrioSeasonNewYear_OfferText:
	.string "Midnight Pawty waits!\nWould you like to visit?$"
TrioSeasonNewYear_GateText:
	.string "Earn all sixteen Badges.\nThen join our pawty.$"
TrioSeasonNewYear_ExitText:
	.string "Head back to the Center?\nYour round will wait here.$"
TrioSeasonNewYear_StartText:
	.string "Repeat the pawty rhythm.\pWin outfits once, then\nsnacks. Play a round?$"
TrioSeasonNewYear_CorrectText:
	.string "A perfect little choice!\nOne step closer to smiles.$"
TrioSeasonNewYear_WrongText:
	.string "That is not the next one.\nYour progress is safe.$"
TrioSeasonNewYear_IdleText:
	.string "Ask the host for a round.\nYour sisters are waiting!$"
TrioSeasonNewYear_WinText:
	.string "Three happy sisters!\nYou finished this round.$"
TrioSeasonNewYear_ClaimedText:
	.string "Gifts are yours forever.\nReturn for a varied round!$"
TrioSeasonNewYear_FullText:
	.string "Your Bag is full.\nYour gifts will wait.$"
TrioSeasonNewYear_Back:
	.string "Later$"
TrioSeasonNewYear_GirlText0:
	.string "Riko has the tallest hat.\nShe counts down with love.$"
TrioSeasonNewYear_GirlText1:
	.string "Bijuu polishes her bow.\nNew year, same cocoa.$"
TrioSeasonNewYear_GirlText2:
	.string "Penny sparkles like stars.\nShe wishes for more hugs.$"
TrioSeasonNewYear_Pattern0:
	.string "Remember these beats:\nPom, Meow, Wag.$"
TrioSeasonNewYear_Pattern1:
	.string "Remember these beats:\nWag, Pom, Meow.$"
TrioSeasonNewYear_Pattern2:
	.string "Remember these beats:\nMeow, Wag, Pom.$"
TrioSeasonNewYear_Word0:
	.string "Pom$"
TrioSeasonNewYear_Word1:
	.string "Meow$"
TrioSeasonNewYear_Word2:
	.string "Wag$"

TrioSeasonFall_LeafText0:
	.string "A pile of maple leaves.\nA tiny rustle from below!$"

TrioSeasonFall_LeafText1:
	.string "A pile of oak leaves.\nA tiny rustle from below!$"

TrioSeasonFall_LeafText2:
	.string "A pile of golden leaves.\nA tiny rustle from below!$"
