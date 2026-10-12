@ Optional cosmetic gifts. Bag possession records receipt; courier uses audited trainer flag.
TrioCostume_Balloon::
	lock
	faceplayer
	call TrioOutfit_React
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
	call TrioHunt_RikoHost
	msgbox TrioCostume_BalloonReady, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_BringRiko:
	msgbox TrioCostume_RikoHint, MSGBOX_DEFAULT
	goto TrioCostume_Close

TrioCostume_Box::
	lock
	faceplayer
	call TrioOutfit_React
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
	call TrioHunt_BijuuHost
	msgbox TrioCostume_BoxReady, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_BringBijuu:
	msgbox TrioCostume_BijuuHint, MSGBOX_DEFAULT
	goto TrioCostume_Close

TrioCostume_Hotdog::
	lock
	faceplayer
	call TrioOutfit_React
	checkitem ITEM_PENNYS_HOTDOG_BUN
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_HotdogAgain
	call TrioParty_CheckPenny
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_BringPenny
	msgbox TrioCostume_HotdogOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_Close
	giveitem ITEM_PENNYS_HOTDOG_BUN
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_FullBag
TrioCostume_HotdogAgain:
	call TrioHunt_PennyHost
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

@ Explicitly authorized temporary New Bark testing supplies; no victory flags.
TrioCostume_TestSupplies::
	msgbox TrioCostume_TestOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_TestReturn
TrioCostume_TestItem0:
	checkitem ITEM_RIKOS_BALLOON
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_TestItem1
	giveitem ITEM_RIKOS_BALLOON
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_TestFullBag
TrioCostume_TestItem1:
	checkitem ITEM_BIJUUS_BOX
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_TestItem2
	giveitem ITEM_BIJUUS_BOX
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_TestFullBag
TrioCostume_TestItem2:
	checkitem ITEM_PENNYS_HOTDOG_BUN
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_TestItem3
	giveitem ITEM_PENNYS_HOTDOG_BUN
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_TestFullBag
TrioCostume_TestItem3:
	checkitem ITEM_TOXIC_MOUSE
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_TestItem4
	giveitem ITEM_TOXIC_MOUSE
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_TestFullBag
TrioCostume_TestItem4:
	checkitem ITEM_POM_TIARA
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_TestItem5
	giveitem ITEM_POM_TIARA
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_TestFullBag
TrioCostume_TestItem5:
	checkitem ITEM_RIKOS_RAINCOAT
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_TestItem6
	giveitem ITEM_RIKOS_RAINCOAT
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_TestFullBag
TrioCostume_TestItem6:
	checkitem ITEM_COCOA_TOAST
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_TestItem7
	giveitem ITEM_COCOA_TOAST
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_TestFullBag
TrioCostume_TestItem7:
	checkitem ITEM_COCOAS_DETECTIVE_KIT
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_TestItem8
	giveitem ITEM_COCOAS_DETECTIVE_KIT
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_TestFullBag
TrioCostume_TestItem8:
	checkitem ITEM_PENNYS_COZY_WRAP
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_TestItem9
	giveitem ITEM_PENNYS_COZY_WRAP
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_TestFullBag
TrioCostume_TestItem9:
	checkitem ITEM_PENNYS_BEACH_VEST
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_TestReady
	giveitem ITEM_PENNYS_BEACH_VEST
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_TestFullBag
TrioCostume_TestReady:
	msgbox TrioCostume_TestReadyText, MSGBOX_DEFAULT
	return
TrioCostume_TestFullBag:
	msgbox TrioCostume_TestBagText, MSGBOX_DEFAULT
TrioCostume_TestReturn:
	return
TrioCostume_TestOffer:
	.string "Want all nine costumes\nand Bijuu's Poison item?\pThese are testing gifts.\nWant the missing ones?$"
TrioCostume_TestReadyText:
	.string "The gifts are ready!\nUse them from your Bag.\pUse again to change back.\nHave fun with the girls!$"
TrioCostume_TestBagText:
	.string "Make some room and return.\nI'll give missing gifts.$"

TrioCostume_RikoPrincessGift::
	lock
	faceplayer
	call TrioOutfit_React
	checkitem ITEM_POM_TIARA
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_RikoPrincessReady
	call TrioParty_CheckRiko
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_RikoPrincessMissing
	msgbox TrioCostume_RikoPrincessOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_Close
	giveitem ITEM_POM_TIARA
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_FullBag
TrioCostume_RikoPrincessReady:
	msgbox TrioCostume_RikoPrincessReadyText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_RikoPrincessMissing:
	msgbox TrioCostume_RikoPrincessMissingText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_RikoPrincessOffer:
	.string "Riko needs a crown.\nShe already acts royal!\pMay I give your princess\na tiny golden tiara?$"
TrioCostume_RikoPrincessMissingText:
	.string "Bring Riko along!\nI have a gift for her.$"
TrioCostume_RikoPrincessReadyText:
	.string "Use Pom Tiara\non regular Riko.\pUse it again to return.\nHer moves stay with her!$"

TrioCostume_RikoRaincoatGift::
	lock
	faceplayer
	call TrioCostume_RikoWitchGift
	call TrioCostume_RikoButterflyGift
	call TrioOutfit_React
	checkitem ITEM_RIKOS_RAINCOAT
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_RikoRaincoatReady
	call TrioParty_CheckRiko
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_RikoRaincoatMissing
	msgbox TrioCostume_RikoRaincoatOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_Close
	giveitem ITEM_RIKOS_RAINCOAT
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_FullBag
TrioCostume_RikoRaincoatReady:
	msgbox TrioCostume_RikoRaincoatReadyText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_RikoRaincoatMissing:
	msgbox TrioCostume_RikoRaincoatMissingText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_RikoRaincoatOffer:
	.string "Ecruteak can get damp.\nRiko deserves dry floof!\pWant a yellow raincoat\nfor your little diva?$"
TrioCostume_RikoRaincoatMissingText:
	.string "Bring Riko along!\nI have a gift for her.$"
TrioCostume_RikoRaincoatReadyText:
	.string "Use Riko Raincoat\non regular Riko.\pUse it again to return.\nHer moves stay with her!$"

TrioCostume_BijuuBreadGift::
	lock
	faceplayer
	call TrioOutfit_React
	checkitem ITEM_COCOA_TOAST
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_BijuuBreadReady
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_BijuuBreadMissing
	msgbox TrioCostume_BijuuBreadOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_Close
	giveitem ITEM_COCOA_TOAST
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_FullBag
TrioCostume_BijuuBreadReady:
	msgbox TrioCostume_BijuuBreadReadyText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_BijuuBreadMissing:
	msgbox TrioCostume_BijuuBreadMissingText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_BijuuBreadOffer:
	.string "Bijuu inspected my toast.\nThen put her face in it.\pWant a bread costume\nfor your curious cocoa?$"
TrioCostume_BijuuBreadMissingText:
	.string "Bring Bijuu along!\nI have a gift for her.$"
TrioCostume_BijuuBreadReadyText:
	.string "Use Cocoa Toast\non regular Bijuu.\pUse it again to return.\nHer moves stay with her!$"

TrioCostume_BijuuDetectiveGift::
	lock
	faceplayer
	call TrioCostume_BijuuVampireGift
	call TrioCostume_BijuuAstronautGift
	call TrioOutfit_React
	checkitem ITEM_COCOAS_DETECTIVE_KIT
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_BijuuDetectiveReady
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_BijuuDetectiveMissing
	msgbox TrioCostume_BijuuDetectiveOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_Close
	giveitem ITEM_COCOAS_DETECTIVE_KIT
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_FullBag
TrioCostume_BijuuDetectiveReady:
	msgbox TrioCostume_BijuuDetectiveReadyText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_BijuuDetectiveMissing:
	msgbox TrioCostume_BijuuDetectiveMissingText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_BijuuDetectiveOffer:
	.string "Footprints. Missing fish.\nOne very suspicious cat.\pWant a detective outfit\nfor your little sleuth?$"
TrioCostume_BijuuDetectiveMissingText:
	.string "Bring Bijuu along!\nI have a gift for her.$"
TrioCostume_BijuuDetectiveReadyText:
	.string "Use Detective Kit\non regular Bijuu.\pUse it again to return.\nHer moves stay with her!$"

TrioCostume_PennyBlanketGift::
	lock
	faceplayer
	call TrioOutfit_React
	checkitem ITEM_PENNYS_COZY_WRAP
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_PennyBlanketReady
	call TrioParty_CheckPenny
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_PennyBlanketMissing
	msgbox TrioCostume_PennyBlanketOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_Close
	giveitem ITEM_PENNYS_COZY_WRAP
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_FullBag
TrioCostume_PennyBlanketReady:
	msgbox TrioCostume_PennyBlanketReadyText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_PennyBlanketMissing:
	msgbox TrioCostume_PennyBlanketMissingText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_PennyBlanketOffer:
	.string "Penny deserves soft days\nand a safe place to rest.\pMay I give her a cozy\nlavender blanket?$"
TrioCostume_PennyBlanketMissingText:
	.string "Bring Penny along!\nI have a gift for her.$"
TrioCostume_PennyBlanketReadyText:
	.string "Use Penny Cozy Wrap\non regular Penny.\pUse it again to return.\nHer moves stay with her!$"

TrioCostume_PennyLifeguardGift::
	lock
	faceplayer
	call TrioCostume_PennyPumpkinGift
	call TrioCostume_PennyBallerinaGift
	call TrioOutfit_React
	checkitem ITEM_PENNYS_BEACH_VEST
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_PennyLifeguardReady
	call TrioParty_CheckPenny
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_PennyLifeguardMissing
	msgbox TrioCostume_PennyLifeguardOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_Close
	giveitem ITEM_PENNYS_BEACH_VEST
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_FullBag
TrioCostume_PennyLifeguardReady:
	msgbox TrioCostume_PennyLifeguardReadyText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_PennyLifeguardMissing:
	msgbox TrioCostume_PennyLifeguardMissingText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_PennyLifeguardOffer:
	.string "Penny follows every rule.\nA perfect little guard!\pWant a beach vest for\nyour golden lifeguard?$"
TrioCostume_PennyLifeguardMissingText:
	.string "Bring Penny along!\nI have a gift for her.$"
TrioCostume_PennyLifeguardReadyText:
	.string "Use Penny Beach Vest\non regular Penny.\pUse it again to return.\nHer moves stay with her!$"

TrioCostume_BijuuPoisonGift::
	lock
	faceplayer
	call TrioOutfit_React
	checkitem ITEM_TOXIC_MOUSE
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_BijuuPoisonReady
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_BijuuPoisonMissing
	msgbox TrioCostume_BijuuPoisonOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_Close
	giveitem ITEM_TOXIC_MOUSE
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_FullBag
TrioCostume_BijuuPoisonReady:
	msgbox TrioCostume_BijuuPoisonReadyText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_BijuuPoisonMissing:
	msgbox TrioCostume_BijuuPoisonMissingText, MSGBOX_DEFAULT
	goto TrioCostume_Close
TrioCostume_BijuuPoisonOffer:
	.string "Our Gym knows Poison.\nBijuu knows nasty bites!\pWant a Toxic Mouse for\nyour dangerous cocoa?$"
TrioCostume_BijuuPoisonMissingText:
	.string "Bring Bijuu along!\nI have a gift for her.$"
TrioCostume_BijuuPoisonReadyText:
	.string "Use Toxic Mouse\non regular Bijuu.\pUse it again to return.\nHer moves stay with her!$"

TrioCostume_RikoButterflyGift::
	checkitem ITEM_RIKOS_BUTTERFLY_WINGS
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_RikoButterflyReturn
	call TrioParty_CheckRiko
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_RikoButterflyReturn
	msgbox TrioCostume_RikoButterflyOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_RikoButterflyReturn
	giveitem ITEM_RIKOS_BUTTERFLY_WINGS
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_RikoButterflyFull
	msgbox TrioCostume_RikoButterflyReady, MSGBOX_DEFAULT
TrioCostume_RikoButterflyReturn:
	return
TrioCostume_RikoButterflyFull:
	msgbox TrioCostume_BagText, MSGBOX_DEFAULT
	return
TrioCostume_RikoButterflyOffer:
	.string "Riko can float in style!\nWant butterfly wings?$"
TrioCostume_RikoButterflyReady:
	.string "Use Riko Wings\non ordinary Riko.\pUse it again to revert.\nSame moves, new outfit!$"

TrioCostume_BijuuAstronautGift::
	checkitem ITEM_BIJUUS_SPACE_HELMET
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_BijuuAstronautReturn
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_BijuuAstronautReturn
	msgbox TrioCostume_BijuuAstronautOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_BijuuAstronautReturn
	giveitem ITEM_BIJUUS_SPACE_HELMET
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_BijuuAstronautFull
	msgbox TrioCostume_BijuuAstronautReady, MSGBOX_DEFAULT
TrioCostume_BijuuAstronautReturn:
	return
TrioCostume_BijuuAstronautFull:
	msgbox TrioCostume_BagText, MSGBOX_DEFAULT
	return
TrioCostume_BijuuAstronautOffer:
	.string "Mission: steal moon fish.\nWant a space helmet?$"
TrioCostume_BijuuAstronautReady:
	.string "Use Space Helmet\non ordinary Bijuu.\pUse it again to revert.\nSame moves, new outfit!$"

TrioCostume_PennyBallerinaGift::
	checkitem ITEM_PENNYS_BALLET_TUTU
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_PennyBallerinaReturn
	call TrioParty_CheckPenny
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_PennyBallerinaReturn
	msgbox TrioCostume_PennyBallerinaOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_PennyBallerinaReturn
	giveitem ITEM_PENNYS_BALLET_TUTU
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_PennyBallerinaFull
	msgbox TrioCostume_PennyBallerinaReady, MSGBOX_DEFAULT
TrioCostume_PennyBallerinaReturn:
	return
TrioCostume_PennyBallerinaFull:
	msgbox TrioCostume_BagText, MSGBOX_DEFAULT
	return
TrioCostume_PennyBallerinaOffer:
	.string "Tiny paws. Big applause.\nWant a tutu for Penny?$"
TrioCostume_PennyBallerinaReady:
	.string "Use Penny Tutu\non ordinary Penny.\pUse it again to revert.\nSame moves, new outfit!$"

TrioCostume_RikoWitchGift::
	checkitem ITEM_RIKOS_WITCH_HAT
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_RikoWitchReturn
	call TrioParty_CheckRiko
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_RikoWitchReturn
	msgbox TrioCostume_RikoWitchOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_RikoWitchReturn
	giveitem ITEM_RIKOS_WITCH_HAT
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_RikoWitchFull
	msgbox TrioCostume_RikoWitchReady, MSGBOX_DEFAULT
TrioCostume_RikoWitchReturn:
	return
TrioCostume_RikoWitchFull:
	msgbox TrioCostume_BagText, MSGBOX_DEFAULT
	return
TrioCostume_RikoWitchOffer:
	.string "Riko casts snack spells!\nWant a witch hat?$"
TrioCostume_RikoWitchReady:
	.string "Use Riko Witch Hat\non ordinary Riko.\pUse it again to revert.\nSame moves, new outfit!$"

TrioCostume_BijuuVampireGift::
	checkitem ITEM_BIJUUS_VAMPIRE_CAPE
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_BijuuVampireReturn
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_BijuuVampireReturn
	msgbox TrioCostume_BijuuVampireOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_BijuuVampireReturn
	giveitem ITEM_BIJUUS_VAMPIRE_CAPE
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_BijuuVampireFull
	msgbox TrioCostume_BijuuVampireReady, MSGBOX_DEFAULT
TrioCostume_BijuuVampireReturn:
	return
TrioCostume_BijuuVampireFull:
	msgbox TrioCostume_BagText, MSGBOX_DEFAULT
	return
TrioCostume_BijuuVampireOffer:
	.string "Count Cocoa wants fish.\nWant a vampire cape?$"
TrioCostume_BijuuVampireReady:
	.string "Use Vampire Cape\non ordinary Bijuu.\pUse it again to revert.\nSame moves, new outfit!$"

TrioCostume_PennyPumpkinGift::
	checkitem ITEM_PENNYS_PUMPKIN_SUIT
	goto_if_eq VAR_RESULT, TRUE, TrioCostume_PennyPumpkinReturn
	call TrioParty_CheckPenny
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_PennyPumpkinReturn
	msgbox TrioCostume_PennyPumpkinOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCostume_PennyPumpkinReturn
	giveitem ITEM_PENNYS_PUMPKIN_SUIT
	goto_if_eq VAR_RESULT, FALSE, TrioCostume_PennyPumpkinFull
	msgbox TrioCostume_PennyPumpkinReady, MSGBOX_DEFAULT
TrioCostume_PennyPumpkinReturn:
	return
TrioCostume_PennyPumpkinFull:
	msgbox TrioCostume_BagText, MSGBOX_DEFAULT
	return
TrioCostume_PennyPumpkinOffer:
	.string "Our sweetest pumpkin!\nWant a suit for Penny?$"
TrioCostume_PennyPumpkinReady:
	.string "Use Pumpkin Suit\non ordinary Penny.\pUse it again to revert.\nSame moves, new outfit!$"
