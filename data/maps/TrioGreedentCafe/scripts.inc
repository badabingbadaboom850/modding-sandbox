
@ Reformed cartel cafe. Opens after the final cartel victory.
TrioGreedentCafe_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TrioCafe_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrioCafe_OnFrame
	.byte 0
TrioCafe_OnTransition:
	setvar VAR_TEMP_A, 0
	goto_if_set FLAG_TRIO_CAFE_VISITED, TrioCafe_TransitionEnd
	setvar VAR_TEMP_A, 1
TrioCafe_TransitionEnd:
	end
TrioCafe_OnFrame:
	map_script_2 VAR_TEMP_A, 1, TrioCafe_Introduction
	.2byte 0
TrioCafe_Introduction:
	lockall
	setvar VAR_TEMP_A, 0
	msgbox TrioCafe_ApologyText, MSGBOX_DEFAULT
	setflag FLAG_TRIO_CAFE_VISITED
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	goto TrioCafe_End

@ Called on Vermilion entry, so a reload inside never readies a parcel.
TrioCafe_AfterExit::
	goto_if_eq VAR_TRIO_CAFE_DELIVERY_STATE, 1, TrioCafe_ReadySecond
	goto_if_eq VAR_TRIO_CAFE_DELIVERY_STATE, 3, TrioCafe_ReadyThird
	return
TrioCafe_ReadySecond:
	setvar VAR_TRIO_CAFE_DELIVERY_STATE, 2
	return
TrioCafe_ReadyThird:
	setvar VAR_TRIO_CAFE_DELIVERY_STATE, 4
	return

TrioCafe_Shop::
	lockall
	faceplayer
	msgbox TrioCafe_ShopText, MSGBOX_DEFAULT
	pokemart TrioCafe_Stock
	goto TrioCafe_End
	.align 2
TrioCafe_Stock:
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_ORAN_BERRY
	.2byte ITEM_RIKO_PUFFS
	.2byte ITEM_NONE

TrioCafe_Courier::
	lockall
	faceplayer
	goto_if_eq VAR_TRIO_CAFE_DELIVERY_STATE, 0, TrioCafe_FirstParcel
	goto_if_eq VAR_TRIO_CAFE_DELIVERY_STATE, 2, TrioCafe_SecondParcel
	goto_if_eq VAR_TRIO_CAFE_DELIVERY_STATE, 4, TrioCafe_ThirdParcel
	goto_if_eq VAR_TRIO_CAFE_DELIVERY_STATE, 5, TrioCafe_DeliveryDone
	msgbox TrioCafe_NextVisitText, MSGBOX_DEFAULT
	goto TrioCafe_End
TrioCafe_FirstParcel:
	msgbox TrioCafe_FirstParcelText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCafe_End
	giveitem ITEM_POTION, 3
	goto_if_eq VAR_RESULT, FALSE, TrioCafe_FullBag
	setvar VAR_TRIO_CAFE_DELIVERY_STATE, 1
	goto TrioCafe_ParcelThanks
TrioCafe_SecondParcel:
	msgbox TrioCafe_SecondParcelText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCafe_End
	giveitem ITEM_RIKO_PUFFS, 3
	goto_if_eq VAR_RESULT, FALSE, TrioCafe_FullBag
	setvar VAR_TRIO_CAFE_DELIVERY_STATE, 3
	goto TrioCafe_ParcelThanks
TrioCafe_ThirdParcel:
	msgbox TrioCafe_ThirdParcelText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCafe_End
	giveitem ITEM_LEFTOVERS, 1
	goto_if_eq VAR_RESULT, FALSE, TrioCafe_FullBag
	setvar VAR_TRIO_CAFE_DELIVERY_STATE, 5
TrioCafe_ParcelThanks:
	msgbox TrioCafe_ParcelThanksText, MSGBOX_DEFAULT
	goto TrioCafe_End
TrioCafe_FullBag:
	msgbox TrioCafe_FullBagText, MSGBOX_DEFAULT
	goto TrioCafe_End
TrioCafe_DeliveryDone:
	msgbox TrioCafe_DeliveryDoneText, MSGBOX_DEFAULT
	goto TrioCafe_End

TrioCafe_Boss::
	lockall
	faceplayer
	msgbox TrioCafe_BossText, MSGBOX_DEFAULT
	goto TrioCafe_End
TrioCafe_Accountant::
	lockall
	faceplayer
	msgbox TrioCafe_AccountantText, MSGBOX_DEFAULT
	goto TrioCafe_End
TrioCafe_Dishwasher::
	lockall
	faceplayer
	msgbox TrioCafe_DishwasherText, MSGBOX_DEFAULT
	goto TrioCafe_End
TrioCafe_Host::
	lockall
	faceplayer
	msgbox TrioCafe_HostText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioCafe_End
	closemessage
	warp MAP_VERMILION_CITY, 38, 23
	waitstate
	goto TrioCafe_End
TrioCafe_Riko::
	lockall
	faceplayer
	msgbox TrioCafe_RikoText, MSGBOX_DEFAULT
	goto TrioCafe_End
TrioCafe_Penny::
	lockall
	faceplayer
	msgbox TrioCafe_PennyText, MSGBOX_DEFAULT
	goto TrioCafe_End
TrioCafe_Bijuu::
	lockall
	faceplayer
	msgbox TrioCafe_BijuuText, MSGBOX_DEFAULT
TrioCafe_End:
	closemessage
	releaseall
	end
TrioCafe_ReadMemory::
	msgbox TrioCafe_MemoryText, MSGBOX_DEFAULT
	return
TrioCafe_Hint::
	msgbox TrioCafe_HintText, MSGBOX_DEFAULT
	return

TrioCafe_ApologyText:
	.string "Six Greedents stand tall.\nOne drops a stolen spoon.\pBoss: We are sorry for\nthe daylight snack crimes.\pPenny watches the till.\nBijuu checks the receipts.\pRiko taste-tests a Wawa.\nThere may be hope for us.\pWELCOME TO THE DEFINITELY\nLEGITIMATE SNACK CAFE!$"

TrioCafe_ShopText:
	.string "Perfectly legal snacks!\pSmall, medium, large Wawa.\nBerries. Riko Puffs.\pWe have receipts now.\nBijuu insisted.$"

TrioCafe_BossText:
	.string "We tried six against one.\nYour girls still won.\pNow we have six employees\nand exactly one customer.\pPlease tell your friends.\nThe nice ones.\pOur old landlord knew a\nlot about Diglett tunnels.\pThey lead to a distant\ntown. We kept his advice.$"

TrioCafe_AccountantText:
	.string "Today's stolen snacks: 0.\nToday's sold snacks: ...\pPenny is watching.\nI'll count them properly.$"

TrioCafe_DishwasherText:
	.string "This is my first honest\njob. I wash the cups.\pRiko licks them first.\nQuality control, she says.$"

TrioCafe_HostText:
	.string "No fees. No mugging.\nJust a polite goodbye.\pWould you like to leave?$"

TrioCafe_RikoText:
	.string "Riko gives the Wawa a\nvery serious sniff.\pHer tail approves.\nThe boss looks relieved.$"

TrioCafe_PennyText:
	.string "Penny's blankey has its\nown place at the table.\pShe settles beside you.\nNobody rushes her here.$"

TrioCafe_BijuuText:
	.string "Bijuu has found the one\nsunbeam in the cafe.\pShe also found three\nerrors in the accounts.$"

TrioCafe_FirstParcelText:
	.string "A parcel from Scott!\p'One Wawa for each girl.\nNo sharing arguments.\pAnd a kiss for their mom.\nDelivery is personal.'\pAccept three small Wawa?$"

TrioCafe_SecondParcelText:
	.string "Another parcel from Scott!\p'Riko Puffs for practice.\nYour girls have standards.\pSo do I. Mine is you.'\pAccept three Riko Puffs?$"

TrioCafe_ThirdParcelText:
	.string "Scott sent a picnic tin!\p'Something for the road.\nCome sit beside me soon.\pI saved the best spot.\nIt fits you perfectly.'\pAccept the Leftovers?$"

TrioCafe_ParcelThanksText:
	.string "The courier salutes.\pYour parcel arrived whole.\nHe looks proud of himself.$"

TrioCafe_NextVisitText:
	.string "Scott's next delivery\nisn't here yet.\pGo stretch your legs.\nWe'll watch for it.$"

TrioCafe_FullBagText:
	.string "Your Bag is full.\pWe'll keep Scott's parcel\nsafe until you have room.$"

TrioCafe_DeliveryDoneText:
	.string "Three parcels delivered.\nNot one snack stolen.\pScott: Thanks, tiny guys.\nKeep looking after her.$"

TrioCafe_MemoryText:
	.string "Definitely Legitimate:\pSix former snack bandits\nopened a little cafe.\pPenny guarded the till.\nBijuu checked the books.\pRiko approved the Wawa.\nScott sent you a kiss.\pTheir first honest tip\nwas a wagging tail.$"

TrioCafe_HintText:
	.string "The cartel has gone legit!\pFind their snack cafe in\neast of the Vermilion Gym.\pScott has parcels for you.$"
