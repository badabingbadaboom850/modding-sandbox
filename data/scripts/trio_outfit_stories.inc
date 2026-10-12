@ Optional outfit stories. Callers own locks for shared menus/reactions.
TrioOutfit_React::
	setvar VAR_0x8004, 3
	specialvar VAR_RESULT, GetTrioOutfitReaction
	goto_if_eq VAR_RESULT, 1, TrioOutfit_React0
	goto_if_eq VAR_RESULT, 2, TrioOutfit_React1
	goto_if_eq VAR_RESULT, 3, TrioOutfit_React2
	goto_if_eq VAR_RESULT, 4, TrioOutfit_React3
	goto_if_eq VAR_RESULT, 5, TrioOutfit_React4
	goto_if_eq VAR_RESULT, 6, TrioOutfit_React5
	goto_if_eq VAR_RESULT, 7, TrioOutfit_React6
	goto_if_eq VAR_RESULT, 8, TrioOutfit_React7
	goto_if_eq VAR_RESULT, 9, TrioOutfit_React8
	goto_if_eq VAR_RESULT, 10, TrioOutfit_React9
	goto_if_eq VAR_RESULT, 13, TrioOutfit_React12
	goto_if_eq VAR_RESULT, 14, TrioOutfit_React13
	goto_if_eq VAR_RESULT, 15, TrioOutfit_React14
	goto_if_eq VAR_RESULT, 16, TrioOutfit_React15
	goto_if_eq VAR_RESULT, 12, TrioOutfit_React11
	goto_if_eq VAR_RESULT, 11, TrioOutfit_React10
	return
TrioOutfit_React0:
	msgbox TrioOutfit_ReactText0, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText0:
	.string "Riko has a balloon!\nEvery day is her birthday.$"
TrioOutfit_React1:
	msgbox TrioOutfit_ReactText1, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText1:
	.string "Your Majesty!\nPlease spare my snacks.$"
TrioOutfit_React2:
	msgbox TrioOutfit_ReactText2, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText2:
	.string "Riko has a raincoat.\nThe forecast is attitude.$"
TrioOutfit_React3:
	msgbox TrioOutfit_ReactText3, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText3:
	.string "That box contains a cat.\nPremium cargo. No refunds.$"
TrioOutfit_React4:
	msgbox TrioOutfit_ReactText4, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText4:
	.string "Is that cat wearing toast?\nBreakfast has blue eyes.$"
TrioOutfit_React5:
	msgbox TrioOutfit_ReactText5, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText5:
	.string "Detective Bijuu!\nMy missing fish is\pevidence.$"
TrioOutfit_React6:
	msgbox TrioOutfit_ReactText6, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText6:
	.string "Penny is a hot dog!\nThe cutest special today.$"
TrioOutfit_React7:
	msgbox TrioOutfit_ReactText7, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText7:
	.string "Penny looks so cozy.\nShe deserves every soft\pday.$"
TrioOutfit_React8:
	msgbox TrioOutfit_ReactText8, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText8:
	.string "No running by the water!\nPenny takes rules\pseriously.$"
TrioOutfit_React9:
	msgbox TrioOutfit_ReactText9, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText9:
	.string "Purple bubbles? Nasty\nbite?\pThat cocoa means business.$"
TrioOutfit_Scott::
	setvar VAR_0x8004, 0
	call TrioOutfit_ScottOne
	setvar VAR_0x8004, 1
	call TrioOutfit_ScottOne
	setvar VAR_0x8004, 2
	call TrioOutfit_ScottOne
	return
TrioOutfit_ScottOne:
	specialvar VAR_RESULT, GetTrioOutfitReaction
	goto_if_eq VAR_RESULT, 1, TrioOutfit_Scott0
	goto_if_eq VAR_RESULT, 2, TrioOutfit_Scott1
	goto_if_eq VAR_RESULT, 3, TrioOutfit_Scott2
	goto_if_eq VAR_RESULT, 4, TrioOutfit_Scott3
	goto_if_eq VAR_RESULT, 5, TrioOutfit_Scott4
	goto_if_eq VAR_RESULT, 6, TrioOutfit_Scott5
	goto_if_eq VAR_RESULT, 7, TrioOutfit_Scott6
	goto_if_eq VAR_RESULT, 8, TrioOutfit_Scott7
	goto_if_eq VAR_RESULT, 9, TrioOutfit_Scott8
	goto_if_eq VAR_RESULT, 10, TrioOutfit_Scott9
	goto_if_eq VAR_RESULT, 13, TrioOutfit_Scott12
	goto_if_eq VAR_RESULT, 14, TrioOutfit_Scott13
	goto_if_eq VAR_RESULT, 15, TrioOutfit_Scott14
	goto_if_eq VAR_RESULT, 16, TrioOutfit_Scott15
	goto_if_eq VAR_RESULT, 12, TrioOutfit_Scott11
	goto_if_eq VAR_RESULT, 11, TrioOutfit_Scott10
	return
TrioOutfit_Scott0:
	msgbox TrioOutfit_ScottText0, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText0:
	.string "Riko got a balloon?\nI got the prettiest\ptrainer.$"
TrioOutfit_Scott1:
	msgbox TrioOutfit_ScottText1, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText1:
	.string "Riko is royalty now?\nYou were already my queen.$"
TrioOutfit_Scott2:
	msgbox TrioOutfit_ScottText2, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText2:
	.string "Riko looks ready for rain.\nI am ready to hold your\phand.$"
TrioOutfit_Scott3:
	msgbox TrioOutfit_ScottText3, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText3:
	.string "Bijuu chose the box.\nI would choose you.\pAlways.$"
TrioOutfit_Scott4:
	msgbox TrioOutfit_ScottText4, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText4:
	.string "Bijuu is wearing toast.\nYou still look more\pdelicious.$"
TrioOutfit_Scott5:
	msgbox TrioOutfit_ScottText5, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText5:
	.string "Detective Bijuu solved it.\nI am guilty of loving you.$"
TrioOutfit_Scott6:
	msgbox TrioOutfit_ScottText6, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText6:
	.string "Penny wins best hot dog.\nYou win best everything.$"
TrioOutfit_Scott7:
	msgbox TrioOutfit_ScottText7, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText7:
	.string "Penny has her blanket.\nCome here. I will be\pyours.$"
TrioOutfit_Scott8:
	msgbox TrioOutfit_ScottText8, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText8:
	.string "You and Penny look cute.\nOnly one has a whistle.\pShe already fined me\nfor looking at you too\plong.$"
TrioOutfit_Scott9:
	msgbox TrioOutfit_ScottText9, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText9:
	.string "Bijuu deals Poison damage.\nYour smile deals worse.\pI have no resistance.\nPlease be gentle with me.$"
TrioOutfit_AlbumFromBook::
	call TrioOutfit_Album
	goto TrioScrapbook_Menu
TrioOutfit_Album::
	special TrioOutfits_RecordPartyPhotos
	special BufferTrioOutfitPhotoCount
	msgbox TrioOutfit_AlbumIntro, MSGBOX_DEFAULT
TrioOutfit_AlbumMenu:
	closemessage
	dynmultichoice 0, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, TrioOutfit_RikoName, TrioOutfit_BijuuName, TrioOutfit_PennyName, TrioOutfit_BonusName, TrioOutfit_BackName
	goto_if_eq VAR_RESULT, 0, TrioOutfit_AlbumRiko
	goto_if_eq VAR_RESULT, 1, TrioOutfit_AlbumBijuu
	goto_if_eq VAR_RESULT, 2, TrioOutfit_AlbumPenny
	goto_if_eq VAR_RESULT, 3, TrioOutfit_AlbumBonus
	return
TrioOutfit_AlbumIntro:
	.string "Photos: {STR_VAR_1}/15\nPoison has a bonus page!\pWear each costume once.\nIts photo stays forever.$"
TrioOutfit_RikoName:
	.string "Riko$"
TrioOutfit_BijuuName:
	.string "Bijuu$"
TrioOutfit_PennyName:
	.string "Penny$"
TrioOutfit_BonusName:
	.string "Poison bonus$"
TrioOutfit_BackName:
	.string "Back$"
TrioOutfit_AlbumRiko:
	closemessage
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrioOutfit_PageName0, TrioOutfit_PageName1, TrioOutfit_PageName2, TrioOutfit_PageName10, TrioOutfit_PageName13, TrioOutfit_BackName
	goto_if_eq VAR_RESULT, 0, TrioOutfit_Page0
	goto_if_eq VAR_RESULT, 1, TrioOutfit_Page1
	goto_if_eq VAR_RESULT, 2, TrioOutfit_Page2
	goto_if_eq VAR_RESULT, 3, TrioOutfit_Page10
	goto_if_eq VAR_RESULT, 4, TrioOutfit_Page13
	goto TrioOutfit_AlbumMenu
TrioOutfit_AlbumBijuu:
	closemessage
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrioOutfit_PageName3, TrioOutfit_PageName4, TrioOutfit_PageName5, TrioOutfit_PageName11, TrioOutfit_PageName14, TrioOutfit_BackName
	goto_if_eq VAR_RESULT, 0, TrioOutfit_Page3
	goto_if_eq VAR_RESULT, 1, TrioOutfit_Page4
	goto_if_eq VAR_RESULT, 2, TrioOutfit_Page5
	goto_if_eq VAR_RESULT, 3, TrioOutfit_Page11
	goto_if_eq VAR_RESULT, 4, TrioOutfit_Page14
	goto TrioOutfit_AlbumMenu
TrioOutfit_AlbumPenny:
	closemessage
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrioOutfit_PageName6, TrioOutfit_PageName7, TrioOutfit_PageName8, TrioOutfit_PageName12, TrioOutfit_PageName15, TrioOutfit_BackName
	goto_if_eq VAR_RESULT, 0, TrioOutfit_Page6
	goto_if_eq VAR_RESULT, 1, TrioOutfit_Page7
	goto_if_eq VAR_RESULT, 2, TrioOutfit_Page8
	goto_if_eq VAR_RESULT, 3, TrioOutfit_Page12
	goto_if_eq VAR_RESULT, 4, TrioOutfit_Page15
	goto TrioOutfit_AlbumMenu
TrioOutfit_AlbumBonus:
	closemessage
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrioOutfit_PageName9, TrioOutfit_BackName
	goto_if_eq VAR_RESULT, 0, TrioOutfit_Page9
	goto TrioOutfit_AlbumMenu
TrioOutfit_Page0:
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_RIKO_BALLOON, 10, 3
	msgbox TrioOutfit_Caption0, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName0:
	.string "Balloon$"
TrioOutfit_Caption0:
	.string "The birthday girl.\nEvery day. No exceptions.$"
TrioOutfit_Page1:
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_RIKO_PRINCESS, 10, 3
	msgbox TrioOutfit_Caption1, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName1:
	.string "Princess$"
TrioOutfit_Caption1:
	.string "All hail the tiny queen.\nHer tax is chicken.$"
TrioOutfit_Page2:
	setvar VAR_0x8004, 2
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_RIKO_RAINCOAT, 10, 3
	msgbox TrioOutfit_Caption2, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName2:
	.string "Raincoat$"
TrioOutfit_Caption2:
	.string "Dry floof. Wet pavement.\nStill deeply offended.$"
TrioOutfit_Page3:
	setvar VAR_0x8004, 3
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_BIJUU_BOX, 10, 3
	msgbox TrioOutfit_Caption3, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName3:
	.string "Box$"
TrioOutfit_Caption3:
	.string "The gift cost a fortune.\nShe chose its packaging.$"
TrioOutfit_Page4:
	setvar VAR_0x8004, 4
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_BIJUU_BREAD, 10, 3
	msgbox TrioOutfit_Caption4, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName4:
	.string "Bread$"
TrioOutfit_Caption4:
	.string "One slice. Two blue eyes.\nZero explanation.$"
TrioOutfit_Page5:
	setvar VAR_0x8004, 5
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_BIJUU_DETECTIVE, 10, 3
	msgbox TrioOutfit_Caption5, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName5:
	.string "Detective$"
TrioOutfit_Caption5:
	.string "The fish was missing.\nThe detective was chewing.$"
TrioOutfit_Page6:
	setvar VAR_0x8004, 6
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_PENNY_HOTDOG, 10, 3
	msgbox TrioOutfit_Caption6, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName6:
	.string "Hot dog$"
TrioOutfit_Caption6:
	.string "All dog. Extra ketchup.\nThe sweetest special.$"
TrioOutfit_Page7:
	setvar VAR_0x8004, 7
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_PENNY_BLANKET, 10, 3
	msgbox TrioOutfit_Caption7, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName7:
	.string "Blankey$"
TrioOutfit_Caption7:
	.string "A soft place for Penny.\nShe is safe. She is home.$"
TrioOutfit_Page8:
	setvar VAR_0x8004, 8
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_PENNY_LIFEGUARD, 10, 3
	msgbox TrioOutfit_Caption8, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName8:
	.string "Lifeguard$"
TrioOutfit_Caption8:
	.string "No running. No splashing.\nPenny has a whistle.$"
TrioOutfit_Page9:
	setvar VAR_0x8004, 9
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_BIJUU_POISON, 10, 3
	msgbox TrioOutfit_Caption9, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName9:
	.string "Poison$"
TrioOutfit_Caption9:
	.string "A very dangerous cocoa.\nStill our sweet girl.$"
TrioOutfit_Locked:
	msgbox TrioOutfit_LockedText, MSGBOX_DEFAULT
	goto TrioOutfit_AlbumMenu
TrioOutfit_LockedText:
	.string "This page is waiting.\nWear this outfit first!$"
TrioHunt_RikoHost::
	goto_if_eq VAR_TRIO_HUNT_RIKO, 3, TrioHunt_RikoDone
	goto_if_eq VAR_TRIO_HUNT_RIKO, 2, TrioHunt_RikoClaim
	goto_if_eq VAR_TRIO_HUNT_RIKO, 1, TrioHunt_RikoHint
	call TrioParty_CheckRiko
	goto_if_eq VAR_RESULT, FALSE, TrioStories_Return
	msgbox TrioHunt_RikoOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioStories_Return
	setvar VAR_TRIO_HUNT_RIKO, 1
TrioHunt_RikoHint:
	msgbox TrioHunt_RikoHintText, MSGBOX_DEFAULT
	return
TrioHunt_RikoClaim:
	msgbox TrioHunt_RikoThanks, MSGBOX_DEFAULT
	giveitem ITEM_ORAN_BERRY, 3
	goto_if_eq VAR_RESULT, FALSE, TrioStories_FullBag
	setvar VAR_TRIO_HUNT_RIKO, 3
	msgbox TrioStories_MemoryAdded, MSGBOX_DEFAULT
	return
TrioHunt_RikoDone:
	msgbox TrioHunt_RikoDoneText, MSGBOX_DEFAULT
	return
TrioHunt_RikoSearch::
	lock
	faceplayer
	goto_if_eq VAR_TRIO_HUNT_RIKO, 0, TrioHunt_RikoUnasked
	goto_if_ge VAR_TRIO_HUNT_RIKO, 2, TrioHunt_RikoFoundAgain
	call TrioParty_CheckRiko
	goto_if_eq VAR_RESULT, FALSE, TrioHunt_RikoMissing
	msgbox TrioHunt_RikoFound, MSGBOX_DEFAULT
	setvar VAR_TRIO_HUNT_RIKO, 2
	goto TrioStories_End
TrioHunt_RikoUnasked:
	msgbox TrioHunt_RikoUnaskedText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioHunt_RikoFoundAgain:
	msgbox TrioHunt_RikoDoneText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioHunt_RikoMissing:
	msgbox TrioHunt_RikoMissingText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioHunt_RikoOffer:
	.string "My picnic basket vanished.\nRiko can smell the snacks.\pLook for the item ball\nsouth of the Mart.\pWant to help find it?$"
TrioHunt_RikoFound:
	.string "Riko sniffs the basket.\nChicken crumbs! Success.\pShe demands a finder fee.\nReturn to the balloon\pgirl.$"
TrioHunt_RikoThanks:
	.string "My basket! Thank you.\nRiko earned some chicken!$"
TrioHunt_RikoHintText:
	.string "Check the item ball\nsouth of the Mart.$"
TrioHunt_RikoMissingText:
	.string "Bring Riko along.\nShe can help search this.$"
TrioHunt_RikoUnaskedText:
	.string "Someone left this here.\nAsk the costume giver.$"
TrioHunt_RikoDoneText:
	.string "Our little mystery is safe\nin the family scrapbook.$"
TrioHunt_BijuuHost::
	goto_if_eq VAR_TRIO_HUNT_BIJUU, 3, TrioHunt_BijuuDone
	goto_if_eq VAR_TRIO_HUNT_BIJUU, 2, TrioHunt_BijuuClaim
	goto_if_eq VAR_TRIO_HUNT_BIJUU, 1, TrioHunt_BijuuHint
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, TrioStories_Return
	msgbox TrioHunt_BijuuOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioStories_Return
	setvar VAR_TRIO_HUNT_BIJUU, 1
TrioHunt_BijuuHint:
	msgbox TrioHunt_BijuuHintText, MSGBOX_DEFAULT
	return
TrioHunt_BijuuClaim:
	msgbox TrioHunt_BijuuThanks, MSGBOX_DEFAULT
	giveitem ITEM_POTION, 3
	goto_if_eq VAR_RESULT, FALSE, TrioStories_FullBag
	setvar VAR_TRIO_HUNT_BIJUU, 3
	msgbox TrioStories_MemoryAdded, MSGBOX_DEFAULT
	return
TrioHunt_BijuuDone:
	msgbox TrioHunt_BijuuDoneText, MSGBOX_DEFAULT
	return
TrioHunt_BijuuSearch::
	lock
	faceplayer
	goto_if_eq VAR_TRIO_HUNT_BIJUU, 0, TrioHunt_BijuuUnasked
	goto_if_ge VAR_TRIO_HUNT_BIJUU, 2, TrioHunt_BijuuFoundAgain
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, TrioHunt_BijuuMissing
	msgbox TrioHunt_BijuuFound, MSGBOX_DEFAULT
	setvar VAR_TRIO_HUNT_BIJUU, 2
	goto TrioStories_End
TrioHunt_BijuuUnasked:
	msgbox TrioHunt_BijuuUnaskedText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioHunt_BijuuFoundAgain:
	msgbox TrioHunt_BijuuDoneText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioHunt_BijuuMissing:
	msgbox TrioHunt_BijuuMissingText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioHunt_BijuuOffer:
	.string "A parcel went missing.\nBijuu loves suspicious\pboxes.\pLook for the item ball\nsouth-east of the Mart.\pWant to investigate?$"
TrioHunt_BijuuFound:
	.string "Bijuu inspects the parcel.\nAll evidence points to\pnaps.\pThe courier needs this.\nReturn to him by the\pCenter.$"
TrioHunt_BijuuThanks:
	.string "The parcel is safe!\nHere is some small Wawa.$"
TrioHunt_BijuuHintText:
	.string "Check the item ball\nsouth-east of the Mart.$"
TrioHunt_BijuuMissingText:
	.string "Bring Bijuu along.\nShe can help search this.$"
TrioHunt_BijuuUnaskedText:
	.string "Someone left this here.\nAsk the costume giver.$"
TrioHunt_BijuuDoneText:
	.string "Our little mystery is safe\nin the family scrapbook.$"
TrioHunt_PennyHost::
	goto_if_eq VAR_TRIO_HUNT_PENNY, 3, TrioHunt_PennyDone
	goto_if_eq VAR_TRIO_HUNT_PENNY, 2, TrioHunt_PennyClaim
	goto_if_eq VAR_TRIO_HUNT_PENNY, 1, TrioHunt_PennyHint
	call TrioParty_CheckPenny
	goto_if_eq VAR_RESULT, FALSE, TrioStories_Return
	msgbox TrioHunt_PennyOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioStories_Return
	setvar VAR_TRIO_HUNT_PENNY, 1
TrioHunt_PennyHint:
	msgbox TrioHunt_PennyHintText, MSGBOX_DEFAULT
	return
TrioHunt_PennyClaim:
	msgbox TrioHunt_PennyThanks, MSGBOX_DEFAULT
	giveitem ITEM_PECHA_BERRY, 3
	goto_if_eq VAR_RESULT, FALSE, TrioStories_FullBag
	setvar VAR_TRIO_HUNT_PENNY, 3
	msgbox TrioStories_MemoryAdded, MSGBOX_DEFAULT
	return
TrioHunt_PennyDone:
	msgbox TrioHunt_PennyDoneText, MSGBOX_DEFAULT
	return
TrioHunt_PennySearch::
	lock
	faceplayer
	goto_if_eq VAR_TRIO_HUNT_PENNY, 0, TrioHunt_PennyUnasked
	goto_if_ge VAR_TRIO_HUNT_PENNY, 2, TrioHunt_PennyFoundAgain
	call TrioParty_CheckPenny
	goto_if_eq VAR_RESULT, FALSE, TrioHunt_PennyMissing
	msgbox TrioHunt_PennyFound, MSGBOX_DEFAULT
	setvar VAR_TRIO_HUNT_PENNY, 2
	goto TrioStories_End
TrioHunt_PennyUnasked:
	msgbox TrioHunt_PennyUnaskedText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioHunt_PennyFoundAgain:
	msgbox TrioHunt_PennyDoneText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioHunt_PennyMissing:
	msgbox TrioHunt_PennyMissingText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioHunt_PennyOffer:
	.string "I lost my favorite mitten.\nPenny is a careful helper.\pLook for the item ball\nsouth-east of the Mart.\pWant to help find it?$"
TrioHunt_PennyFound:
	.string "Penny finds the mitten.\nShe carries it so gently.\pReturn to the bun vendor.\nShe knows the way!$"
TrioHunt_PennyThanks:
	.string "You found my mitten!\nPup cups for our good\pgirl.$"
TrioHunt_PennyHintText:
	.string "Check the item ball\nsouth-east of the Mart.$"
TrioHunt_PennyMissingText:
	.string "Bring Penny along.\nShe can help search this.$"
TrioHunt_PennyUnaskedText:
	.string "Someone left this here.\nAsk the costume giver.$"
TrioHunt_PennyDoneText:
	.string "Our little mystery is safe\nin the family scrapbook.$"
TrioBread_Rumor::
	lock
	faceplayer
	goto_if_eq VAR_TRIO_BREAD_MYSTERY, 4, TrioBread_Done
	goto_if_eq VAR_TRIO_BREAD_MYSTERY, 3, TrioBread_Claim
	goto_if_eq VAR_TRIO_BREAD_MYSTERY, 2, TrioBread_KitchenHint
	goto_if_eq VAR_TRIO_BREAD_MYSTERY, 1, TrioBread_StreetHint
	msgbox TrioBread_RumorText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioStories_End
	setvar VAR_TRIO_BREAD_MYSTERY, 1
TrioBread_StreetHint:
	msgbox TrioBread_StreetText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioBread_KitchenHint:
	msgbox TrioBread_KitchenText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioBread_Claim:
	msgbox TrioBread_Thanks, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_POTION, 2
	goto_if_eq VAR_RESULT, FALSE, TrioBread_FullBag
	setvar VAR_TRIO_BREAD_MYSTERY, 4
	msgbox TrioStories_MemoryAdded, MSGBOX_DEFAULT
	goto TrioStories_End
TrioBread_FullBag:
	msgbox TrioStories_BagText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioBread_Done:
	msgbox TrioBread_DoneText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioBread_Clue::
	lock
	faceplayer
	goto_if_eq VAR_TRIO_BREAD_MYSTERY, 0, TrioBread_ClueUnasked
	goto_if_ge VAR_TRIO_BREAD_MYSTERY, 3, TrioBread_Done
	setvar VAR_TRIO_BREAD_MYSTERY, 2
	msgbox TrioBread_ClueText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioBread_ClueUnasked:
	msgbox TrioBread_ClueUnaskedText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioBread_Reveal::
	lock
	faceplayer
	goto_if_lt VAR_TRIO_BREAD_MYSTERY, 2, TrioBread_NotYet
	goto_if_ge VAR_TRIO_BREAD_MYSTERY, 3, TrioBread_Replay
	msgbox TrioBread_RevealText, MSGBOX_DEFAULT
	setvar VAR_TRIO_BREAD_MYSTERY, 3
	goto TrioStories_End
TrioBread_Replay:
	msgbox TrioBread_RevealText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioBread_NotYet:
	msgbox TrioBread_NotYetText, MSGBOX_DEFAULT
	goto TrioStories_End
TrioStories_FullBag:
	msgbox TrioStories_BagText, MSGBOX_DEFAULT
TrioStories_Return:
	return
TrioStories_End:
	release
	end
TrioBread_RumorText:
	.string "A terrible beast appeared!\nTwo blue eyes. Golden\parmor.\pIt waits in perfect\nsilence.\pThe streets smell of\ntoast!\pWill you investigate?$"
TrioBread_StreetText:
	.string "Ask the woman by the\neastern apartment\pbuilding.$"
TrioBread_KitchenText:
	.string "Check the eastern house.\nDoor at the far-right\pedge.$"
TrioBread_ClueText:
	.string "The golden armor has\ncrust.\pThe beast smells\ndelicious.\pIt went into the far-right\nhouse, east of the\papartment.$"
TrioBread_ClueUnaskedText:
	.string "People fear the strangest\nthings around here.$"
TrioBread_RevealText:
	.string "The legendary beast...\nis a cocoa wearing bread.\pBijuu stares through\ntoast.\pNo prophecy. Just\nbreakfast.\pRiko demands a royal\nslice.\pPenny checks for crumbs.\pTell the frightened man.\nGoldenrod can relax now!$"
TrioBread_NotYetText:
	.string "A suspiciously familiar\ncat\psits inside a slice of\ntoast.$"
TrioBread_DoneText:
	.string "The prophecy was\nbreakfast.\pI may never live this\ndown.$"
TrioBread_Thanks:
	.string "It was Bread Bijuu?!\nPlease take this Wawa.\pMy nerves need a moment.\nKeep this between us.$"
TrioStories_BagText:
	.string "Your Bag is full.\nYour reward can wait.$"
TrioStories_MemoryAdded:
	.string "A little family adventure\nwas added to the\pscrapbook.$"
TrioStories_ReadMemories::
	call_if_eq VAR_TRIO_HUNT_RIKO, 3, TrioStories_MemoryRiko
	call_if_eq VAR_TRIO_HUNT_BIJUU, 3, TrioStories_MemoryBijuu
	call_if_eq VAR_TRIO_HUNT_PENNY, 3, TrioStories_MemoryPenny
	call_if_ge VAR_TRIO_BREAD_MYSTERY, 3, TrioStories_MemoryBread
	return
TrioStories_MemoryRiko:
	msgbox TrioStories_MemoryTextRiko, MSGBOX_DEFAULT
	return
TrioStories_MemoryTextRiko:
	.string "Riko found the picnic\nbasket.\pHer finder fee was\nchicken.$"
TrioStories_MemoryBijuu:
	msgbox TrioStories_MemoryTextBijuu, MSGBOX_DEFAULT
	return
TrioStories_MemoryTextBijuu:
	.string "Bijuu solved the parcel\ncase.\pThe box was her best clue.$"
TrioStories_MemoryPenny:
	msgbox TrioStories_MemoryTextPenny, MSGBOX_DEFAULT
	return
TrioStories_MemoryTextPenny:
	.string "Penny carried a lost\nmitten.\pCareful paws. A proud\nsmile.$"
TrioStories_MemoryBread:
	msgbox TrioStories_MemoryTextBread, MSGBOX_DEFAULT
	return
TrioStories_MemoryTextBread:
	.string "Goldenrod feared a\nprophecy.\pBijuu wore a slice of\ntoast.$"

TrioOutfit_ReactTown::
	setvar VAR_0x8004, 3
	specialvar VAR_RESULT, GetTrioOutfitReaction
	goto_if_eq VAR_RESULT, 1, TrioOutfit_Town0
	goto_if_eq VAR_RESULT, 2, TrioOutfit_Town1
	goto_if_eq VAR_RESULT, 3, TrioOutfit_Town2
	goto_if_eq VAR_RESULT, 4, TrioOutfit_Town3
	goto_if_eq VAR_RESULT, 5, TrioOutfit_Town4
	goto_if_eq VAR_RESULT, 6, TrioOutfit_Town5
	goto_if_eq VAR_RESULT, 7, TrioOutfit_Town6
	goto_if_eq VAR_RESULT, 8, TrioOutfit_Town7
	goto_if_eq VAR_RESULT, 9, TrioOutfit_Town8
	goto_if_eq VAR_RESULT, 10, TrioOutfit_Town9
	return
TrioOutfit_Town0:
	msgbox TrioOutfit_TownText0, MSGBOX_DEFAULT
	return
TrioOutfit_TownText0:
	.string "A balloon follows your\nPom.\pShe brought her own\nparade.$"
TrioOutfit_Town1:
	msgbox TrioOutfit_TownText1, MSGBOX_DEFAULT
	return
TrioOutfit_TownText1:
	.string "I was told to bow to Riko.\nHonestly, fair enough.$"
TrioOutfit_Town2:
	msgbox TrioOutfit_TownText2, MSGBOX_DEFAULT
	return
TrioOutfit_TownText2:
	.string "Riko prepared for puddles.\nShe still blames the\pweather.$"
TrioOutfit_Town3:
	msgbox TrioOutfit_TownText3, MSGBOX_DEFAULT
	return
TrioOutfit_TownText3:
	.string "Bijuu found luxury\nhousing.\pIt used to contain\nparcels.$"
TrioOutfit_Town4:
	msgbox TrioOutfit_TownText4, MSGBOX_DEFAULT
	return
TrioOutfit_TownText4:
	.string "I cannot explain your cat.\nI can only admire the\ptoast.$"
TrioOutfit_Town5:
	msgbox TrioOutfit_TownText5, MSGBOX_DEFAULT
	return
TrioOutfit_TownText5:
	.string "Please tell your detective\nmy fish was already\pmissing.$"
TrioOutfit_Town6:
	msgbox TrioOutfit_TownText6, MSGBOX_DEFAULT
	return
TrioOutfit_TownText6:
	.string "That little golden hot dog\nhas made my whole day.$"
TrioOutfit_Town7:
	msgbox TrioOutfit_TownText7, MSGBOX_DEFAULT
	return
TrioOutfit_TownText7:
	.string "Penny looks warm and safe.\nYou take good care of her.$"
TrioOutfit_Town8:
	msgbox TrioOutfit_TownText8, MSGBOX_DEFAULT
	return
TrioOutfit_TownText8:
	.string "Penny is watching the\nwater.\pI suddenly feel\nsupervised.$"
TrioOutfit_Town9:
	msgbox TrioOutfit_TownText9, MSGBOX_DEFAULT
	return
TrioOutfit_TownText9:
	.string "Bijuu has purple bubbles.\nI will admire her from\phere.$"

TrioOutfit_React10:
	msgbox TrioOutfit_ReactText10, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText10:
	.string "A butterfly pom!\nThe snacks must be nectar.$"

TrioOutfit_Scott10:
	msgbox TrioOutfit_ScottText10, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText10:
	.string "Riko gives me butterflies.\nYou always did, too.$"

TrioOutfit_Page10:
	setvar VAR_0x8004, 10
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_RIKO_BUTTERFLY, 10, 3
	msgbox TrioOutfit_Caption10, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName10:
	.string "Butterfly$"
TrioOutfit_Caption10:
	.string "Light as a butterfly.\nHeavy on the attitude.$"

TrioOutfit_React11:
	msgbox TrioOutfit_ReactText11, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText11:
	.string "Houston, we have a cocoa.\nShe demands space fish.$"

TrioOutfit_Scott11:
	msgbox TrioOutfit_ScottText11, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText11:
	.string "Bijuu can have the moon.\nYou are my whole world.$"

TrioOutfit_Page11:
	setvar VAR_0x8004, 11
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_BIJUU_ASTRONAUT, 10, 3
	msgbox TrioOutfit_Caption11, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName11:
	.string "Astronaut$"
TrioOutfit_Caption11:
	.string "One small step for cocoa.\nOne giant leap for fish.$"

TrioOutfit_React12:
	msgbox TrioOutfit_ReactText12, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText12:
	.string "Penny takes center stage.\nEvery paw gets applause.$"

TrioOutfit_Scott12:
	msgbox TrioOutfit_ScottText12, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText12:
	.string "Penny gets the spotlight.\nYou get my last dance.$"

TrioOutfit_Page12:
	setvar VAR_0x8004, 12
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_PENNY_BALLERINA, 10, 3
	msgbox TrioOutfit_Caption12, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName12:
	.string "Ballerina$"
TrioOutfit_Caption12:
	.string "Four tiny dancing paws.\nHer sisters cheer loudest.$"

TrioOutfit_React13:
	msgbox TrioOutfit_ReactText13, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText13:
	.string "Riko bewitched the snacks.\nNobody is surprised.$"

TrioOutfit_Scott13:
	msgbox TrioOutfit_ScottText13, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText13:
	.string "Riko has her little spell.\nYou have my whole heart.$"

TrioOutfit_Page13:
	setvar VAR_0x8004, 13
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_RIKO_WITCH, 10, 3
	msgbox TrioOutfit_Caption13, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName13:
	.string "Witch$"
TrioOutfit_Caption13:
	.string "A tiny witch, a big bark.\nHer spell summons snacks.$"

TrioOutfit_React14:
	msgbox TrioOutfit_ReactText14, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText14:
	.string "Count Cocoa is awake!\nHide the fish, not garlic.$"

TrioOutfit_Scott14:
	msgbox TrioOutfit_ScottText14, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText14:
	.string "Bijuu wants midnight fish.\nI want a night with you.$"

TrioOutfit_Page14:
	setvar VAR_0x8004, 14
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_BIJUU_VAMPIRE, 10, 3
	msgbox TrioOutfit_Caption14, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName14:
	.string "Vampire$"
TrioOutfit_Caption14:
	.string "A cape, a cocoa, a fang.\nThe fish had no chance.$"

TrioOutfit_React15:
	msgbox TrioOutfit_ReactText15, MSGBOX_DEFAULT
	return
TrioOutfit_ReactText15:
	.string "That pumpkin has paws!\nPenny makes autumn sweet.$"

TrioOutfit_Scott15:
	msgbox TrioOutfit_ScottText15, MSGBOX_DEFAULT
	return
TrioOutfit_ScottText15:
	.string "Penny is our pumpkin.\nYou are my sweetie pie.$"

TrioOutfit_Page15:
	setvar VAR_0x8004, 15
	specialvar VAR_RESULT, HasTrioOutfitPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioOutfit_Locked
	showmonpic SPECIES_PENNY_PUMPKIN, 10, 3
	msgbox TrioOutfit_Caption15, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	goto TrioOutfit_AlbumMenu
TrioOutfit_PageName15:
	.string "Pumpkin$"
TrioOutfit_Caption15:
	.string "The sweetest little gourd.\nHer sisters picked her.$"
