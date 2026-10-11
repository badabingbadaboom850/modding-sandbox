@ Three optional family chapters; no startup grants or story bypasses.
FamilyDays_End::
	closemessage
	releaseall
	end
FamilyDinner_Entrance::
	lockall
	faceplayer
	goto_if_unset FLAG_BADGE04_GET, FamilyDinner_NotReady
	goto_if_set FLAG_HIDE_GOLDENROD_NPCS, FamilyDinner_Busy
	call TrioOutfit_Scott
	msgbox FamilyDinner_OfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	goto_if_ge VAR_TRIO_DINNER_STATE, 1, FamilyDinner_Travel
	setvar VAR_TRIO_DINNER_STATE, 1
FamilyDinner_Travel:
	closemessage
	warp MAP_TRIO_DINNER_DATE, 3, 7
	waitstate
	goto FamilyDays_End
FamilyDinner_NotReady::
	msgbox FamilyDinner_NotReadyText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyDinner_Busy::
	msgbox FamilyDinner_BusyText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyDinner_Scott::
	lockall
	faceplayer
	call TrioOutfit_Scott
	goto_if_ge VAR_TRIO_DINNER_STATE, 5, FamilyDinner_Replay
	goto_if_lt VAR_TRIO_DINNER_STATE, 4, FamilyDinner_Help
	msgbox FamilyDinner_TakeoutOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	msgbox FamilyDinner_FinalText, MSGBOX_DEFAULT
	call Common_EventScript_OutOfCenterPartyHeal
	setvar VAR_TRIO_DINNER_STATE, 5
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	goto FamilyDinner_Reward
FamilyDinner_Replay:
	msgbox FamilyDinner_ReplayOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDinner_Reward
	msgbox FamilyDinner_FinalText, MSGBOX_DEFAULT
FamilyDinner_Reward:
	goto_if_eq VAR_TRIO_DINNER_REWARD, 1, FamilyDays_End
	msgbox FamilyDinner_RewardOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	giveitem ITEM_POTION, 3
	goto_if_eq VAR_RESULT, FALSE, FamilyDays_FullBag
	setvar VAR_TRIO_DINNER_REWARD, 1
	goto FamilyDays_End
FamilyDinner_Help:
	msgbox FamilyDinner_HelpText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyDinner_Riko::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_DINNER_STATE, 2, FamilyDinner_RikoDone
	msgbox FamilyDinner_RikoText, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, FamilyDinner_Fancy, FamilyDinner_Chicken, FamilyDays_Back
	goto_if_ne VAR_RESULT, 1, FamilyDinner_RikoWrong
	msgbox FamilyDinner_RikoSolvedText, MSGBOX_DEFAULT
	setvar VAR_TRIO_DINNER_STATE, 2
	goto FamilyDays_End
FamilyDinner_RikoWrong:
	goto_if_eq VAR_RESULT, 127, FamilyDays_End
	goto_if_eq VAR_RESULT, 2, FamilyDays_End
	msgbox FamilyDinner_RikoWrongText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyDinner_RikoDone:
	msgbox FamilyDinner_RikoSolvedText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyDinner_Bijuu::
	lockall
	faceplayer
	goto_if_lt VAR_TRIO_DINNER_STATE, 2, FamilyDinner_Order
	goto_if_ge VAR_TRIO_DINNER_STATE, 3, FamilyDinner_BijuuDone
	msgbox FamilyDinner_BijuuOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	msgbox FamilyDinner_BijuuText, MSGBOX_DEFAULT
	setvar VAR_TRIO_DINNER_STATE, 3
	goto FamilyDays_End
FamilyDinner_BijuuDone:
	msgbox FamilyDinner_BijuuAgainText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyDinner_Penny::
	lockall
	faceplayer
	goto_if_lt VAR_TRIO_DINNER_STATE, 3, FamilyDinner_Order
	goto_if_ge VAR_TRIO_DINNER_STATE, 4, FamilyDinner_PennyDone
	msgbox FamilyDinner_PennyOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	msgbox FamilyDinner_PennyText, MSGBOX_DEFAULT
	setvar VAR_TRIO_DINNER_STATE, 4
	goto FamilyDays_End
FamilyDinner_PennyDone:
	msgbox FamilyDinner_PennyAgainText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyDinner_Order::
	msgbox FamilyDinner_OrderText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyDinner_Waiter::
	lockall
	faceplayer
	msgbox FamilyDinner_WaiterText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyRadio_Offer::
	goto_if_unset FLAG_ENABLE_RADIO, FamilyRadio_Return
	goto_if_unset FLAG_BADGE03_GET, FamilyRadio_Return
	goto_if_set FLAG_HIDE_GOLDENROD_NPCS, FamilyRadio_Return
	msgbox FamilyRadio_OfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyRadio_Return
	closemessage
	warp MAP_TRIO_RADIO_STUDIO, 4, 7
	waitstate
	releaseall
	end
FamilyRadio_Return:
	return
FamilyRadio_Host::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_RADIO_STATE, 4, FamilyRadio_Listen
	goto_if_ne VAR_TRIO_RADIO_STATE, 3, FamilyRadio_Help
	msgbox FamilyRadio_RecordOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	msgbox FamilyRadio_RecordText, MSGBOX_DEFAULT
	setvar VAR_TRIO_RADIO_STATE, 4
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
FamilyRadio_Listen:
	msgbox FamilyRadio_TuneText, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, FamilyRadio_RikoName, FamilyRadio_BijuuName, FamilyRadio_PennyName, FamilyRadio_ScottName, FamilyDays_Back
	goto_if_ge VAR_RESULT, 4, FamilyDays_End
	copyvar VAR_0x8004, VAR_RESULT
	special BufferTrioFamilyRadio
	msgbox gStringVar4, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyRadio_Help:
	msgbox FamilyRadio_HelpText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyRadio_Riko::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_RADIO_STATE, 1, FamilyRadio_RikoDone
	goto_if_ne VAR_TRIO_RADIO_STATE, 0, FamilyRadio_Wait
	msgbox FamilyRadio_RikoOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	msgbox FamilyRadio_RikoText, MSGBOX_DEFAULT
	setvar VAR_TRIO_RADIO_STATE, 1
	goto FamilyDays_End
FamilyRadio_RikoDone:
	msgbox FamilyRadio_RikoAgainText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyRadio_Bijuu::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_RADIO_STATE, 2, FamilyRadio_BijuuDone
	goto_if_ne VAR_TRIO_RADIO_STATE, 1, FamilyRadio_Wait
	msgbox FamilyRadio_BijuuOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	msgbox FamilyRadio_BijuuText, MSGBOX_DEFAULT
	setvar VAR_TRIO_RADIO_STATE, 2
	goto FamilyDays_End
FamilyRadio_BijuuDone:
	msgbox FamilyRadio_BijuuAgainText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyRadio_Penny::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_RADIO_STATE, 3, FamilyRadio_PennyDone
	goto_if_ne VAR_TRIO_RADIO_STATE, 2, FamilyRadio_Wait
	msgbox FamilyRadio_PennyOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	msgbox FamilyRadio_PennyText, MSGBOX_DEFAULT
	setvar VAR_TRIO_RADIO_STATE, 3
	goto FamilyDays_End
FamilyRadio_PennyDone:
	msgbox FamilyRadio_PennyAgainText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyRadio_Wait::
	msgbox FamilyRadio_WaitText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyHome_Offer::
	goto_if_unset FLAG_BADGE07_GET, FamilyHome_Return
	msgbox FamilyHome_OfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyHome_Return
	closemessage
	warp MAP_TRIO_HOMECOMING, 9, 7
	waitstate
	releaseall
	end
FamilyHome_Return:
	return
FamilyHome_Mom::
	lockall
	faceplayer
	goto_if_eq VAR_TRIO_HOMECOMING_STATE, 1, FamilyHome_Replay
	goto_if_lt VAR_TRIO_HOME_GIFTS, 3, FamilyHome_Clues
	msgbox FamilyHome_FinaleOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	msgbox FamilyHome_FinaleText, MSGBOX_DEFAULT
	call FamilyHome_Callbacks
	call Common_EventScript_OutOfCenterPartyHeal
	setvar VAR_TRIO_HOMECOMING_STATE, 1
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	goto FamilyHome_Reward
FamilyHome_Replay:
	msgbox FamilyHome_ReplayOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyHome_Reward
	msgbox FamilyHome_FinaleText, MSGBOX_DEFAULT
	call FamilyHome_Callbacks
FamilyHome_Reward:
	goto_if_eq VAR_TRIO_HOME_REWARD, 1, FamilyDays_End
	msgbox FamilyHome_RewardOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	giveitem ITEM_ORAN_BERRY, 3
	goto_if_eq VAR_RESULT, FALSE, FamilyDays_FullBag
	setvar VAR_TRIO_HOME_REWARD, 1
	goto FamilyDays_End
FamilyHome_Clues:
	msgbox FamilyHome_CluesText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyHome_Callbacks::
	call_if_set FLAG_TRIO_FESTIVAL_PICNIC, FamilyHome_Festival
	call_if_ge VAR_TRIO_GARDEN_STATE, 5, FamilyHome_Garden
	call_if_eq VAR_TRIO_ROAD_COMPLETE, 1, FamilyHome_Road
	call_if_eq VAR_TRIO_DINNER_STATE, 5, FamilyHome_Dinner
	call_if_eq VAR_TRIO_RADIO_STATE, 4, FamilyHome_Radio
	return
FamilyHome_Festival::
	msgbox FamilyHome_FestivalText, MSGBOX_DEFAULT
	return
FamilyHome_Garden::
	msgbox FamilyHome_GardenText, MSGBOX_DEFAULT
	return
FamilyHome_Road::
	msgbox FamilyHome_RoadText, MSGBOX_DEFAULT
	return
FamilyHome_Dinner::
	msgbox FamilyHome_DinnerText, MSGBOX_DEFAULT
	return
FamilyHome_Radio::
	msgbox FamilyHome_RadioText, MSGBOX_DEFAULT
	return
FamilyHome_GiftRiko::
	lockall
	goto_if_ge VAR_TRIO_HOME_GIFTS, 1, FamilyHome_GiftRikoDone
	goto_if_ne VAR_TRIO_HOME_GIFTS, 0, FamilyHome_GiftWait
	msgbox FamilyHome_GiftRikoOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	msgbox FamilyHome_GiftRikoText, MSGBOX_DEFAULT
	setvar VAR_TRIO_HOME_GIFTS, 1
	goto FamilyDays_End
FamilyHome_GiftRikoDone:
	msgbox FamilyHome_GiftRikoText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyHome_GiftBijuu::
	lockall
	goto_if_ge VAR_TRIO_HOME_GIFTS, 2, FamilyHome_GiftBijuuDone
	goto_if_ne VAR_TRIO_HOME_GIFTS, 1, FamilyHome_GiftWait
	msgbox FamilyHome_GiftBijuuOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	msgbox FamilyHome_GiftBijuuText, MSGBOX_DEFAULT
	setvar VAR_TRIO_HOME_GIFTS, 2
	goto FamilyDays_End
FamilyHome_GiftBijuuDone:
	msgbox FamilyHome_GiftBijuuText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyHome_GiftPenny::
	lockall
	goto_if_ge VAR_TRIO_HOME_GIFTS, 3, FamilyHome_GiftPennyDone
	goto_if_ne VAR_TRIO_HOME_GIFTS, 2, FamilyHome_GiftWait
	msgbox FamilyHome_GiftPennyOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FamilyDays_End
	msgbox FamilyHome_GiftPennyText, MSGBOX_DEFAULT
	setvar VAR_TRIO_HOME_GIFTS, 3
	goto FamilyDays_End
FamilyHome_GiftPennyDone:
	msgbox FamilyHome_GiftPennyText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyHome_GiftWait::
	msgbox FamilyHome_GiftWaitText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyHome_Scott::
	lockall
	faceplayer
	msgbox FamilyHome_ScottText, MSGBOX_DEFAULT
	call TrioOutfit_Scott
	goto FamilyDays_End
FamilyHome_Riko::
	lockall
	faceplayer
	msgbox FamilyHome_RikoText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyHome_Bijuu::
	lockall
	faceplayer
	msgbox FamilyHome_BijuuText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyHome_Penny::
	lockall
	faceplayer
	msgbox FamilyHome_PennyText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyHome_Rest::
	lockall
	faceplayer
	msgbox FamilyHome_RestText, MSGBOX_DEFAULT
	call Common_EventScript_OutOfCenterPartyHeal
	goto FamilyDays_End
FamilyDays_FullBag::
	msgbox FamilyDays_FullBagText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyDays_ReadMemories::
	call_if_eq VAR_TRIO_DINNER_STATE, 5, FamilyDinner_ReadMemory
	call_if_eq VAR_TRIO_RADIO_STATE, 4, FamilyRadio_ReadMemory
	call_if_eq VAR_TRIO_HOMECOMING_STATE, 1, FamilyHome_ReadMemory
	return
FamilyDinner_ReadMemory::
	msgbox FamilyDinner_ReadMemoryText, MSGBOX_DEFAULT
	return
FamilyRadio_ReadMemory::
	msgbox FamilyRadio_ReadMemoryText, MSGBOX_DEFAULT
	return
FamilyHome_ReadMemory::
	msgbox FamilyHome_ReadMemoryText, MSGBOX_DEFAULT
	return
FamilyDays_Checklist::
    call FamilyDinner_Checklist
    call FamilyRadio_Checklist
    call FamilyHome_Checklist
    return
FamilyDinner_Checklist:
    goto_if_ge VAR_TRIO_DINNER_STATE, 5, FamilyDinner_ChecklistDone
    msgbox FamilyDinner_ChecklistHint, MSGBOX_DEFAULT
    return
FamilyDinner_ChecklistDone:
    msgbox FamilyDinner_ChecklistSaved, MSGBOX_DEFAULT
    return
FamilyRadio_Checklist:
    goto_if_ge VAR_TRIO_RADIO_STATE, 4, FamilyRadio_ChecklistDone
    msgbox FamilyRadio_ChecklistHint, MSGBOX_DEFAULT
    return
FamilyRadio_ChecklistDone:
    msgbox FamilyRadio_ChecklistSaved, MSGBOX_DEFAULT
    return
FamilyHome_Checklist:
    goto_if_eq VAR_TRIO_HOMECOMING_STATE, 1, FamilyHome_ChecklistDone
    msgbox FamilyHome_ChecklistHint, MSGBOX_DEFAULT
    return
FamilyHome_ChecklistDone:
    msgbox FamilyHome_ChecklistSaved, MSGBOX_DEFAULT
    return
FamilyDinner_OfferText:
	.string "Scott: I booked us a fancy\ndinner. Just you, me...\pAnd three girls with\nabsolutely no restaurant\pexperience.\pCome on a dinner date? My\ntreat. No battles.$"

FamilyDinner_NotReadyText:
	.string "Scott: After Morty's\nBadge, let me take you\pout.\pI am learning which fork\nis for Penny's pup cup.$"

FamilyDinner_BusyText:
	.string "Scott: With those Rockets\naround, our reservation\pcan wait.\pYou and the girls deserve\na peaceful evening.$"

FamilyDinner_HelpText:
	.string "Scott: I had a plan.\pRiko is arguing with the\nmenu. Start with her.\pThen check Bijuu by the\nkitchen and Penny beside\pthe table.\pI will keep our seats.\nProbably.$"

FamilyDinner_TakeoutOfferText:
	.string "Scott: Our food inspector\nhas rejected the plates.\pOur cat is in the kitchen.\nPenny has three admirers.\pTake dinner to go and eat\ntogether right here?$"

FamilyDinner_FinalText:
	.string "The waiter packs dinner in\npaper boxes.\pRiko's grand review: The\nchicken is excellent. The\pbox is better.\pBijuu sits on Scott's\ncoat. It is hers now.\pPenny waits until everyone\nhas a portion, then\psettles beside you.\pScott trades his fancy\nnapkin for a takeout bag.\pScott: This is how our\ndates always go, isn't it?\pHe kisses your cheek.\pI keep booking a table. I\nkeep falling for the whole\pfamily.\pFive happy customers. Zero\ncorrect forks.$"

FamilyDinner_ReplayOfferText:
	.string "Scott: Our usual table?\nFancy plans, paper boxes,\pall three girls.\pRemember our dinner date?$"

FamilyDinner_RewardOfferText:
	.string "Scott saved three small\nWawa for the road.\pAccept them? If your Bag\nis full, I will keep them\phere.$"

FamilyDinner_RikoText:
	.string "Riko is the food\ninspector.\pThe menu says smoked foam,\ntiny leaves, and one\penormous price.\pHer review is one bark.\nFind the sensible option.$"

FamilyDinner_RikoWrongText:
	.string "Riko stares at the fancy\ntasting menu.\pScott: She says the foam\nhas no chicken\pcredentials.\pTry the other option.$"

FamilyDinner_RikoSolvedText:
	.string "You find plain chicken on\nthe little family menu.\pRiko approves. She will\nallow the restaurant to\premain open.\pBijuu has slipped toward\nthe kitchen. Check on her\pnext.$"

FamilyDinner_BijuuOfferText:
	.string "Bijuu is by the kitchen\npass.\pThe cook thinks she is the\nnew supervisor.\pCall her back with her toy\nmouse?$"

FamilyDinner_BijuuText:
	.string "You wiggle the toy Scott\npacked. Bijuu follows with\ptremendous dignity.\pThe cook: Good inspection,\nma'am?\pBijuu accepts this review\nof her work.\pPenny is beside the table.\nShe seems to have made\pfriends.$"

FamilyDinner_BijuuAgainText:
	.string "Bijuu has given the\nkitchen four paws out of\pfive.\pShe deducted one because\nScott took his coat back.$"

FamilyDinner_PennyOfferText:
	.string "The waiter has brought\nPenny a bowl of water and\pa quiet spot.\pSit beside her for a\nmoment?$"

FamilyDinner_PennyText:
	.string "Penny leans against you.\nThen she nudges a napkin\ptoward her sisters.\pThe waiter: Best customer\nall evening.\pScott: Finally, someone\nwho appreciates Penny's\pmanagement skills.\pEveryone is comfortable.\nTell Scott dinner can be\psaved.$"

FamilyDinner_PennyAgainText:
	.string "Penny keeps the quiet\ntable ready.\pThe staff already knows\nher name. Scott looks\pproud.$"

FamilyDinner_OrderText:
	.string "Scott: Let's find Riko's\nchicken first, then call\pBijuu from the kitchen.\pPenny gets our quiet table\nafter that. No rush.$"

FamilyDinner_WaiterText:
	.string "Welcome to the finest\ndining room in Goldenrod.\pOur new policy is one\nsensible meal and three\pvery good girls.\pScott paid already. Take\nall the time you need.$"

FamilyDinner_Fancy:
	.string "Fancy tasting menu$"

FamilyDinner_Chicken:
	.string "Plain chicken$"

FamilyDays_Back:
	.string "Back$"

FamilyRadio_OfferText:
	.string "The tower wants a family\nshow. The girls already\phave opinions.\pHelp record Tails of the\nTrio in our little studio?$"

FamilyRadio_HelpText:
	.string "Producer: Riko needs a\nmicrophone check.\pThen Bijuu needs her cue\ncard, and Penny a soft\precording cushion.\pTalk to each girl. We can\nstop and resume whenever\pyou like.$"

FamilyRadio_RecordOfferText:
	.string "The microphone is ready.\nBijuu knows her cue. Penny\pfeels safe.\pRecord our first show?$"

FamilyRadio_RecordText:
	.string "Riko gives the weather:\nChicken with a chance of\pmore chicken.\pBijuu answers a caller by\nsitting on the cue card.\pPenny says goodnight to\nanyone having a difficult\pday.\pScott: This song is for\nthe cutest trainer in\pJohto. Yes, I mean you.\pThe producer keeps every\ntake. Especially the\ppurring.\pTails of the Trio is on\nair!$"

FamilyRadio_TuneText:
	.string "On your Pokegear radio,\ntune near the right end\puntil Tails of the Trio\nappears.\pRetune to hear a different\nsegment. Stories change as\pyou adventure.\pListen to a segment here?$"

FamilyRadio_RikoName:
	.string "Riko's segment$"

FamilyRadio_BijuuName:
	.string "Bijuu's segment$"

FamilyRadio_PennyName:
	.string "Penny's segment$"

FamilyRadio_ScottName:
	.string "Scott's dedication$"

FamilyRadio_RikoText:
	.string "The microphone makes\nRiko's tiny bark sound\penormous.\pYou lower its stand. Scott\nholds her steady.\pRiko now believes she is\nthe tower director.\pBijuu is next. She has\neaten half the cue card.$"

FamilyRadio_RikoOfferText:
	.string "Help Riko check her\nmicrophone?$"

FamilyRadio_RikoAgainText:
	.string "Riko is practising her\nsign-off: More chicken,\pless nonsense.$"

FamilyRadio_BijuuText:
	.string "You turn the cue card into\na simple picture: cat,\ppause, purr.\pBijuu checks the\ninstructions, then purrs\pexactly once.\pProfessional work. Penny\nneeds a comfortable place\pnext.$"

FamilyRadio_BijuuOfferText:
	.string "Help Bijuu read her cue\ncard?$"

FamilyRadio_BijuuAgainText:
	.string "Bijuu requires royalties\npaid in fish. The producer\pis considering it.$"

FamilyRadio_PennyText:
	.string "You place the soft cushion\nby the microphone. Her\psisters settle nearby.\pPenny takes her time.\nNobody counts down.\pThen she gives one gentle\ngreeting.\pThe producer smiles. Talk\nto her to record the show.$"

FamilyRadio_PennyOfferText:
	.string "Make Penny's recording\nspot comfortable?$"

FamilyRadio_PennyAgainText:
	.string "Penny's cushion stays\nhere. Every return visit\phas a safe place for her.$"

FamilyRadio_WaitText:
	.string "Start with Riko's\nmicrophone, then Bijuu's\pcue card, then Penny's\ncushion.\pThe producer can remind\nyou. Nothing needs to be\prushed.$"

FamilyHome_OfferText:
	.string "Mom: Seven Badges! Come\nsit down for once.\pScott and the girls have\nmade a little welcome-home\pevening.\pJoin us? Your journey can\nwait a moment.$"

FamilyHome_CluesText:
	.string "Mom: The girls each picked\na little gift. Find Riko's\pleft parcel first.\pThen Bijuu's parcel by the\nstairs, then Penny's lower\pblanket.\pThey left clues just for\nyou. Nothing is hiding in\pyour Bag.$"

FamilyHome_FinaleOfferText:
	.string "All three gifts are found.\nScott has saved you a\pplace.\pSettle in for our welcome-\nhome evening?$"

FamilyHome_FinaleText:
	.string "Mom turns down the lights.\nScott pours Wawa into the\pgood cups.\pRiko presents a leaf with\nteeth marks. She calls it\pa bouquet.\pBijuu gives you a toy\nmouse, then borrows it\pback indefinitely.\pPenny has chosen her\nsoftest blanket. She\ppresses it into your\nhands.\pMom: You brought them a\nwhole world. You kept\pgiving them a home.\pScott: And you made room\nfor me in it.\pHe takes your hand. Riko\nclimbs between you. Bijuu\psteals his cushion.\pPenny rests against your\nknee, comfortable enough\pto fall asleep.\pSeven Badges outside. All\nyour favorite girls\pinside.\pTonight, being here is\nenough.$"

FamilyHome_ReplayOfferText:
	.string "Mom kept the cups and all\nthree little gifts.\pRemember our welcome-home\nevening?$"

FamilyHome_RewardOfferText:
	.string "Mom saved three Chicky\nFil-A snacks for the\pgirls.\pAccept them? A full Bag\ncan wait until next time.$"

FamilyHome_FestivalText:
	.string "The festival ribbon hangs\nby the cups.\pMom remembers three girls\nfinding their own ways to\pshine.$"

FamilyHome_GardenText:
	.string "Pressed flowers from the\nseaside garden sit beside\pPenny's blanket.\pRiko looks personally\nresponsible for spring.$"

FamilyHome_RoadText:
	.string "The island photo is\npropped beside Scott's\pcup.\pPenny found the shelter.\nBijuu found a title. Riko\pfound the snacks.$"

FamilyHome_DinnerText:
	.string "Scott brought paper boxes,\njust in case.\pMom: Your fancy dinner\nsounded very much like a\pfamily dinner.$"

FamilyHome_RadioText:
	.string "The little radio plays\nTails of the Trio.\pRiko recognises her own\nbark. She demands an\pencore.$"

FamilyHome_GiftRikoOfferText:
	.string "Look at Riko's little\ngift?$"

FamilyHome_GiftRikoText:
	.string "The left parcel smells\nlike chicken, but holds a\plittle leaf bouquet.\pA note says: For Mom.\nInspected by Riko.\pFind Bijuu's parcel near\nthe stairs next.$"

FamilyHome_GiftBijuuOfferText:
	.string "Look at Bijuu's little\ngift?$"

FamilyHome_GiftBijuuText:
	.string "The parcel near the stairs\nholds a toy mouse wrapped\pin ribbon.\pBijuu watches you open it,\nthen takes the mouse back.\pShared custody. Find\nPenny's blanket below.$"

FamilyHome_GiftPennyOfferText:
	.string "Look at Penny's little\ngift?$"

FamilyHome_GiftPennyText:
	.string "Penny's lower blanket has\na little patch sewn onto\pits corner.\pIt says: Home is wherever\nyou are.\pPenny presses close while\nyou smooth it.\pTell Mom all three gifts\nare ready.$"

FamilyHome_GiftWaitText:
	.string "The note points to Riko's\nleft parcel, Bijuu's\pparcel by the stairs, then\nPenny's lower blanket.\pMom can repeat the clues.$"

FamilyHome_ScottText:
	.string "Scott: I wanted to help\nMom cook. Penny appointed\pme cushion manager.\pI set one beside mine for\nyou. Riko has already\pchallenged the seating\nplan.\pCome sit with me after the\ngirls show you their\pgifts.$"

FamilyHome_RikoText:
	.string "Riko is showing Mom her\nleaf bouquet.\pShe would like it recorded\nthat chicken was\pconsidered, but eaten.$"

FamilyHome_BijuuText:
	.string "Bijuu watches the ribbon\non her borrowed gift.\pShe would like it recorded\nthat the mouse is still\phers.$"

FamilyHome_PennyText:
	.string "Penny knows every corner\nof this room.\pShe checks on her sisters,\nthen comes back to you.\pShe would like it recorded\nthat everybody is home.$"

FamilyHome_RestText:
	.string "Mom: You can always rest\nhere. No Badge makes you\ptoo grown up for home.$"

FamilyDays_FullBagText:
	.string "Your Bag is full. The\nsnacks are safe here.\pCome back whenever you\nhave room. No need to\prepeat the evening.$"

FamilyDinner_ReadMemoryText:
	.string "Our fancy dinner date:\pRiko approved the chicken.\nBijuu inspected the\pkitchen. Penny won the\nstaff over.\pScott saved the evening\nwith paper boxes and a\pkiss.\pThis is how our dates go.\nAll five of us, together.$"

FamilyRadio_ReadMemoryText:
	.string "Tails of the Trio:\pRiko had opinions. Bijuu\ndemanded fish royalties.\pPenny said a gentle\ngoodnight.\pScott dedicated every love\nsong to Mom.\pOur little family reached\nthe whole of Johto.$"

FamilyHome_ReadMemoryText:
	.string "The family homecoming:\pA leaf bouquet. A borrowed\ntoy mouse. A blanket with\pa little patch.\pMom made the good cups\nready. Scott saved a seat.\pSeven Badges, three girls,\nand a place to come home.$"

FamilyDays_ChecklistText:
	.string "Family evenings:\pDinner: after Morty's\nBadge, meet Scott just\psouth of Goldenrod's Radio\nTower.\pRadio: pass the radio\nquiz, earn Whitney's\pBadge, then talk to the\nlobby woman.\pHomecoming: after Pryce's\nBadge, talk to Mom at\phome.\pAll three are optional.\nCompleted pages appear in\pSister moments.$"


FamilyHome_GardenPhoto::
	lockall
	msgbox FamilyHome_GardenText, MSGBOX_DEFAULT
	showmonpic SPECIES_RIKO_FLOWER, 10, 3
	waitbuttonpress
	hidemonpic
	goto FamilyDays_End
FamilyHome_FestivalCushion::
	lockall
	msgbox FamilyHome_FestivalText, MSGBOX_DEFAULT
	goto FamilyDays_End
FamilyHome_RoadPhoto::
	lockall
	msgbox FamilyHome_RoadText, MSGBOX_DEFAULT
	showmonpic SPECIES_FIDOUGH, 10, 3
	waitbuttonpress
	hidemonpic
	goto FamilyDays_End

FamilyHome_Invitation::
    msgbox FamilyHome_InvitationText, MSGBOX_DEFAULT
    return
FamilyHome_InvitationText:
    .string "A note from Mom:\pSeven Badges! Come home\nwhen you have a moment.\pScott and the girls have\nsomething planned.\pNo rush. Your seat is\nwaiting.$"

FamilyDinner_ChecklistHint:
    .string "Dinner - waiting.\pAfter Morty's Badge, meet\nScott south of Goldenrod's\pRadio Tower. Riko's menu,\nBijuu, Penny, then Scott.$"
FamilyDinner_ChecklistSaved:
    .string "Dinner - saved.\pFancy plans, paper boxes,\nall three girls.\pScott keeps our table and\nany pending Wawa.$"
FamilyRadio_ChecklistHint:
    .string "Radio - waiting.\pAfter the radio quiz and\nWhitney's Badge, talk to\pthe Radio Tower lobby\nwoman.\pRiko, Bijuu, Penny, then\nthe producer.$"
FamilyRadio_ChecklistSaved:
    .string "Radio - saved.\pTails of the Trio is on\nyour Pokegear radio.\pTune near the right end,\nor visit our producer.$"
FamilyHome_ChecklistHint:
    .string "Homecoming - waiting.\pAfter Pryce's Badge, talk\nto Mom at home.\pRiko's parcel, Bijuu's\nparcel, Penny's blanket,\pthen Mom.$"
FamilyHome_ChecklistSaved:
    .string "Homecoming - saved.\pOur gifts and our evening\nare in Sister moments.\pMom keeps our room and any\npending snacks ready.$"
