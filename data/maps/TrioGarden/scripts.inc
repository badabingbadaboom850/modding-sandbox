
@ Persistent three-visit garden; on-load reconstructs scenery without rewards.
TrioGarden_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, TrioGarden_Load
	.byte 0
TrioGarden_Load:
	setflag FLAG_TEMP_2
	clearflag FLAG_TEMP_1
	call_if_ge VAR_TRIO_GARDEN_STATE, 5, TrioGarden_FlowerVisible
	call TrioGarden_Scenery
	end
TrioGarden_FlowerVisible:
	setflag FLAG_TEMP_1
	clearflag FLAG_TEMP_2
	return
TrioGarden_OnReturn::
	goto_if_eq VAR_TRIO_GARDEN_STATE, 1, TrioGarden_ReadyWarmth
	goto_if_eq VAR_TRIO_GARDEN_STATE, 3, TrioGarden_ReadyShelter
	return
TrioGarden_ReadyWarmth:
	setvar VAR_TRIO_GARDEN_STATE, 2
	return
TrioGarden_ReadyShelter:
	setvar VAR_TRIO_GARDEN_STATE, 4
	return
TrioGarden_Offer::
	goto_if_unset FLAG_BADGE05_GET, TrioGarden_Return
	msgbox TrioGarden_OfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGarden_Return
	closemessage
	warp MAP_TRIO_GARDEN, 12, 15
	waitstate
	releaseall
	end
TrioGarden_Return:
	return
TrioGarden_Riko::
	lockall
	faceplayer
	goto_if_ne VAR_TRIO_GARDEN_STATE, 0, TrioGarden_RikoLater
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioGarden_Missing
	msgbox TrioGarden_SeedsText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGarden_End
	setvar VAR_TRIO_GARDEN_STATE, 1
	msgbox TrioGarden_PlantedText, MSGBOX_DEFAULT
	call TrioGarden_Scenery
	special DrawWholeMapView
	goto TrioGarden_End
TrioGarden_RikoLater:
	goto_if_ge VAR_TRIO_GARDEN_STATE, 5, TrioGarden_RikoFlowers
	msgbox TrioGarden_RikoLaterText, MSGBOX_DEFAULT
	goto TrioGarden_End
TrioGarden_RikoFlowers:
	msgbox TrioGarden_RikoFlowersText, MSGBOX_DEFAULT
	goto TrioGarden_End
TrioGarden_Bijuu::
	lockall
	faceplayer
	goto_if_ne VAR_TRIO_GARDEN_STATE, 2, TrioGarden_BijuuLater
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioGarden_Missing
	msgbox TrioGarden_WarmText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGarden_End
	setvar VAR_TRIO_GARDEN_STATE, 3
	msgbox TrioGarden_WarmedText, MSGBOX_DEFAULT
	call TrioGarden_Scenery
	special DrawWholeMapView
	goto TrioGarden_End
TrioGarden_BijuuLater:
	msgbox TrioGarden_BijuuLaterText, MSGBOX_DEFAULT
	goto TrioGarden_End
TrioGarden_Penny::
	lockall
	faceplayer
	goto_if_ne VAR_TRIO_GARDEN_STATE, 4, TrioGarden_PennyLater
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioGarden_Missing
	msgbox TrioGarden_ShelterText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGarden_End
	setvar VAR_TRIO_GARDEN_STATE, 5
	call TrioGarden_FlowerVisible
	removeobject 2
	addobject 6
	call TrioGarden_Scenery
	special DrawWholeMapView
	msgbox TrioGarden_BloomText, MSGBOX_DEFAULT
	goto TrioGarden_End
TrioGarden_PennyLater:
	msgbox TrioGarden_PennyLaterText, MSGBOX_DEFAULT
	goto TrioGarden_End
TrioGarden_Missing:
	msgbox TrioGarden_MissingText, MSGBOX_DEFAULT
	goto TrioGarden_End
TrioGarden_Caretaker::
	lockall
	faceplayer
	call TrioGarden_TryBloom
	msgbox TrioGarden_ExitText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGarden_End
	closemessage
	warp MAP_OLIVINE_CITY, 33, 57
	waitstate
	goto TrioGarden_End
TrioGarden_Rest::
	lockall
	msgbox TrioGarden_RestText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGarden_End
	special HealPlayerParty
	msgbox TrioGarden_RestedText, MSGBOX_DEFAULT
TrioGarden_End:
	releaseall
	end
TrioGarden_TryBloom::
	goto_if_lt VAR_TRIO_GARDEN_STATE, 5, TrioGarden_NoGift
	goto_if_set FLAG_TRIO_GARDEN_BLOOM_RECEIVED, TrioGarden_NoGift
	giveitem ITEM_RIKOS_BLOOM, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGarden_FullBag
	setflag FLAG_TRIO_GARDEN_BLOOM_RECEIVED
	setvar VAR_TRIO_GARDEN_STATE, 6
	msgbox TrioGarden_CharmText, MSGBOX_DEFAULT
TrioGarden_NoGift:
	setvar VAR_RESULT, TRUE
	return
TrioGarden_FullBag:
	msgbox TrioGarden_FullBagText, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	return
TrioGarden_DecorateCamp::
	setmetatile 8, 1, 0x114, TRUE
	return
TrioGarden_CampFlower::
	lockall
	goto_if_lt VAR_TRIO_GARDEN_STATE, 5, TrioGarden_EmptyFrame
	call TrioGarden_ReadCampFlower
	goto TrioGarden_End
TrioGarden_EmptyFrame:
	msgbox TrioGarden_EmptyFrameText, MSGBOX_DEFAULT
	goto TrioGarden_End
TrioGarden_ReadCampFlower::
	msgbox TrioGarden_CampFlowerText, MSGBOX_DEFAULT
	return
TrioGarden_ReadMemory::
	msgbox TrioGarden_MemoryText, MSGBOX_DEFAULT
	return
TrioGarden_Scenery:
	goto_if_ge VAR_TRIO_GARDEN_STATE, 5, TrioGarden_Flowers
	goto_if_ge VAR_TRIO_GARDEN_STATE, 3, TrioGarden_Shoots
	goto_if_ge VAR_TRIO_GARDEN_STATE, 1, TrioGarden_Soil
	return
TrioGarden_Flowers:
	setmetatile 4, 4, 0x410, TRUE
	setmetatile 5, 4, 0x411, TRUE
	setmetatile 6, 4, 0x410, TRUE
	setmetatile 7, 4, 0x411, TRUE
	setmetatile 8, 4, 0x410, TRUE
	setmetatile 4, 5, 0x411, TRUE
	setmetatile 5, 5, 0x410, TRUE
	setmetatile 6, 5, 0x411, TRUE
	setmetatile 7, 5, 0x410, TRUE
	setmetatile 8, 5, 0x411, TRUE
	setmetatile 4, 6, 0x410, TRUE
	setmetatile 5, 6, 0x411, TRUE
	setmetatile 6, 6, 0x410, TRUE
	setmetatile 7, 6, 0x411, TRUE
	setmetatile 8, 6, 0x410, TRUE
	setmetatile 4, 7, 0x411, TRUE
	setmetatile 5, 7, 0x410, TRUE
	setmetatile 6, 7, 0x411, TRUE
	setmetatile 7, 7, 0x410, TRUE
	setmetatile 8, 7, 0x411, TRUE
	setmetatile 15, 4, 0x411, TRUE
	setmetatile 16, 4, 0x410, TRUE
	setmetatile 17, 4, 0x411, TRUE
	setmetatile 18, 4, 0x410, TRUE
	setmetatile 19, 4, 0x411, TRUE
	setmetatile 15, 5, 0x410, TRUE
	setmetatile 16, 5, 0x411, TRUE
	setmetatile 17, 5, 0x410, TRUE
	setmetatile 18, 5, 0x411, TRUE
	setmetatile 19, 5, 0x410, TRUE
	setmetatile 15, 6, 0x411, TRUE
	setmetatile 16, 6, 0x410, TRUE
	setmetatile 17, 6, 0x411, TRUE
	setmetatile 18, 6, 0x410, TRUE
	setmetatile 19, 6, 0x411, TRUE
	setmetatile 15, 7, 0x410, TRUE
	setmetatile 16, 7, 0x411, TRUE
	setmetatile 17, 7, 0x410, TRUE
	setmetatile 18, 7, 0x411, TRUE
	setmetatile 19, 7, 0x410, TRUE
	setmetatile 4, 12, 0x410, TRUE
	setmetatile 5, 12, 0x411, TRUE
	setmetatile 6, 12, 0x410, TRUE
	setmetatile 7, 12, 0x411, TRUE
	setmetatile 8, 12, 0x410, TRUE
	setmetatile 4, 13, 0x411, TRUE
	setmetatile 5, 13, 0x410, TRUE
	setmetatile 6, 13, 0x411, TRUE
	setmetatile 7, 13, 0x410, TRUE
	setmetatile 8, 13, 0x411, TRUE
	setmetatile 4, 14, 0x410, TRUE
	setmetatile 5, 14, 0x411, TRUE
	setmetatile 6, 14, 0x410, TRUE
	setmetatile 7, 14, 0x411, TRUE
	setmetatile 8, 14, 0x410, TRUE
	setmetatile 15, 12, 0x411, TRUE
	setmetatile 16, 12, 0x410, TRUE
	setmetatile 17, 12, 0x411, TRUE
	setmetatile 18, 12, 0x410, TRUE
	setmetatile 19, 12, 0x411, TRUE
	setmetatile 15, 13, 0x410, TRUE
	setmetatile 16, 13, 0x411, TRUE
	setmetatile 17, 13, 0x410, TRUE
	setmetatile 18, 13, 0x411, TRUE
	setmetatile 19, 13, 0x410, TRUE
	setmetatile 15, 14, 0x411, TRUE
	setmetatile 16, 14, 0x410, TRUE
	setmetatile 17, 14, 0x411, TRUE
	setmetatile 18, 14, 0x410, TRUE
	setmetatile 19, 14, 0x411, TRUE
	return
TrioGarden_Shoots:
	setmetatile 4, 4, 0x417, TRUE
	setmetatile 5, 4, 0x417, TRUE
	setmetatile 6, 4, 0x417, TRUE
	setmetatile 7, 4, 0x417, TRUE
	setmetatile 8, 4, 0x417, TRUE
	setmetatile 4, 5, 0x417, TRUE
	setmetatile 5, 5, 0x417, TRUE
	setmetatile 6, 5, 0x417, TRUE
	setmetatile 7, 5, 0x417, TRUE
	setmetatile 8, 5, 0x417, TRUE
	setmetatile 4, 6, 0x417, TRUE
	setmetatile 5, 6, 0x417, TRUE
	setmetatile 6, 6, 0x417, TRUE
	setmetatile 7, 6, 0x417, TRUE
	setmetatile 8, 6, 0x417, TRUE
	setmetatile 4, 7, 0x417, TRUE
	setmetatile 5, 7, 0x417, TRUE
	setmetatile 6, 7, 0x417, TRUE
	setmetatile 7, 7, 0x417, TRUE
	setmetatile 8, 7, 0x417, TRUE
	setmetatile 15, 4, 0x417, TRUE
	setmetatile 16, 4, 0x417, TRUE
	setmetatile 17, 4, 0x417, TRUE
	setmetatile 18, 4, 0x417, TRUE
	setmetatile 19, 4, 0x417, TRUE
	setmetatile 15, 5, 0x417, TRUE
	setmetatile 16, 5, 0x417, TRUE
	setmetatile 17, 5, 0x417, TRUE
	setmetatile 18, 5, 0x417, TRUE
	setmetatile 19, 5, 0x417, TRUE
	setmetatile 15, 6, 0x417, TRUE
	setmetatile 16, 6, 0x417, TRUE
	setmetatile 17, 6, 0x417, TRUE
	setmetatile 18, 6, 0x417, TRUE
	setmetatile 19, 6, 0x417, TRUE
	setmetatile 15, 7, 0x417, TRUE
	setmetatile 16, 7, 0x417, TRUE
	setmetatile 17, 7, 0x417, TRUE
	setmetatile 18, 7, 0x417, TRUE
	setmetatile 19, 7, 0x417, TRUE
	setmetatile 4, 12, 0x417, TRUE
	setmetatile 5, 12, 0x417, TRUE
	setmetatile 6, 12, 0x417, TRUE
	setmetatile 7, 12, 0x417, TRUE
	setmetatile 8, 12, 0x417, TRUE
	setmetatile 4, 13, 0x417, TRUE
	setmetatile 5, 13, 0x417, TRUE
	setmetatile 6, 13, 0x417, TRUE
	setmetatile 7, 13, 0x417, TRUE
	setmetatile 8, 13, 0x417, TRUE
	setmetatile 4, 14, 0x417, TRUE
	setmetatile 5, 14, 0x417, TRUE
	setmetatile 6, 14, 0x417, TRUE
	setmetatile 7, 14, 0x417, TRUE
	setmetatile 8, 14, 0x417, TRUE
	setmetatile 15, 12, 0x417, TRUE
	setmetatile 16, 12, 0x417, TRUE
	setmetatile 17, 12, 0x417, TRUE
	setmetatile 18, 12, 0x417, TRUE
	setmetatile 19, 12, 0x417, TRUE
	setmetatile 15, 13, 0x417, TRUE
	setmetatile 16, 13, 0x417, TRUE
	setmetatile 17, 13, 0x417, TRUE
	setmetatile 18, 13, 0x417, TRUE
	setmetatile 19, 13, 0x417, TRUE
	setmetatile 15, 14, 0x417, TRUE
	setmetatile 16, 14, 0x417, TRUE
	setmetatile 17, 14, 0x417, TRUE
	setmetatile 18, 14, 0x417, TRUE
	setmetatile 19, 14, 0x417, TRUE
	return
TrioGarden_Soil:
	setmetatile 4, 4, 0x9, TRUE
	setmetatile 5, 4, 0x9, TRUE
	setmetatile 6, 4, 0x9, TRUE
	setmetatile 7, 4, 0x9, TRUE
	setmetatile 8, 4, 0x9, TRUE
	setmetatile 4, 5, 0x9, TRUE
	setmetatile 5, 5, 0x9, TRUE
	setmetatile 6, 5, 0x9, TRUE
	setmetatile 7, 5, 0x9, TRUE
	setmetatile 8, 5, 0x9, TRUE
	setmetatile 4, 6, 0x9, TRUE
	setmetatile 5, 6, 0x9, TRUE
	setmetatile 6, 6, 0x9, TRUE
	setmetatile 7, 6, 0x9, TRUE
	setmetatile 8, 6, 0x9, TRUE
	setmetatile 4, 7, 0x9, TRUE
	setmetatile 5, 7, 0x9, TRUE
	setmetatile 6, 7, 0x9, TRUE
	setmetatile 7, 7, 0x9, TRUE
	setmetatile 8, 7, 0x9, TRUE
	setmetatile 15, 4, 0x9, TRUE
	setmetatile 16, 4, 0x9, TRUE
	setmetatile 17, 4, 0x9, TRUE
	setmetatile 18, 4, 0x9, TRUE
	setmetatile 19, 4, 0x9, TRUE
	setmetatile 15, 5, 0x9, TRUE
	setmetatile 16, 5, 0x9, TRUE
	setmetatile 17, 5, 0x9, TRUE
	setmetatile 18, 5, 0x9, TRUE
	setmetatile 19, 5, 0x9, TRUE
	setmetatile 15, 6, 0x9, TRUE
	setmetatile 16, 6, 0x9, TRUE
	setmetatile 17, 6, 0x9, TRUE
	setmetatile 18, 6, 0x9, TRUE
	setmetatile 19, 6, 0x9, TRUE
	setmetatile 15, 7, 0x9, TRUE
	setmetatile 16, 7, 0x9, TRUE
	setmetatile 17, 7, 0x9, TRUE
	setmetatile 18, 7, 0x9, TRUE
	setmetatile 19, 7, 0x9, TRUE
	setmetatile 4, 12, 0x9, TRUE
	setmetatile 5, 12, 0x9, TRUE
	setmetatile 6, 12, 0x9, TRUE
	setmetatile 7, 12, 0x9, TRUE
	setmetatile 8, 12, 0x9, TRUE
	setmetatile 4, 13, 0x9, TRUE
	setmetatile 5, 13, 0x9, TRUE
	setmetatile 6, 13, 0x9, TRUE
	setmetatile 7, 13, 0x9, TRUE
	setmetatile 8, 13, 0x9, TRUE
	setmetatile 4, 14, 0x9, TRUE
	setmetatile 5, 14, 0x9, TRUE
	setmetatile 6, 14, 0x9, TRUE
	setmetatile 7, 14, 0x9, TRUE
	setmetatile 8, 14, 0x9, TRUE
	setmetatile 15, 12, 0x9, TRUE
	setmetatile 16, 12, 0x9, TRUE
	setmetatile 17, 12, 0x9, TRUE
	setmetatile 18, 12, 0x9, TRUE
	setmetatile 19, 12, 0x9, TRUE
	setmetatile 15, 13, 0x9, TRUE
	setmetatile 16, 13, 0x9, TRUE
	setmetatile 17, 13, 0x9, TRUE
	setmetatile 18, 13, 0x9, TRUE
	setmetatile 19, 13, 0x9, TRUE
	setmetatile 15, 14, 0x9, TRUE
	setmetatile 16, 14, 0x9, TRUE
	setmetatile 17, 14, 0x9, TRUE
	setmetatile 18, 14, 0x9, TRUE
	setmetatile 19, 14, 0x9, TRUE
	return
TrioGarden_OfferText:
	.string "There's a forgotten garden\nnear the sea.\pWould you like to visit?$"
TrioGarden_SeedsText:
	.string "Riko finds dry seed pods.\nBijuu nudges a pot closer.\pPenny paws the soil loose.\nPlant them together?$"
TrioGarden_PlantedText:
	.string "You tuck the seeds in.\nRiko pats each bed softly.\pLet them settle awhile.\nCome back another visit.$"
TrioGarden_RikoLaterText:
	.string "Riko sniffs each bed.\nHer tail brushes your leg.$"
TrioGarden_RikoFlowersText:
	.string "Flowers catch in her fur.\nRiko keeps them in place.\pBijuu noses one straight.\nPenny gives a happy yip.$"
TrioGarden_WarmText:
	.string "Tiny shoots lean toward\nthe morning sun.\pBijuu curls around them.\nHelp her warm the soil?$"
TrioGarden_WarmedText:
	.string "Warmth fills the soil.\nRiko brings dry leaves.\pPenny tucks them close.\nLet the shoots rest a bit.$"
TrioGarden_BijuuLaterText:
	.string "Bijuu watches a sunbeam\ncrawl across the beds.$"
TrioGarden_ShelterText:
	.string "The sea breeze bends\nthe tender stems.\pPenny braces the fence.\nHelp her shelter them?$"
TrioGarden_BloomText:
	.string "Riko holds the last slat.\nBijuu curls by Penny.\pThe breeze turns gentle.\nPetals open in the sun.\pThree noses meet a flower.\nNobody wants to leave.\pThe caretaker saved\na little flower for Riko.$"
TrioGarden_PennyLaterText:
	.string "Penny checks the fence,\nthen sits by her sisters.$"
TrioGarden_MissingText:
	.string "Bring all three sisters.\nBring the sisters along.\pThe garden can wait.$"
TrioGarden_ExitText:
	.string "There is no hurry here.\nVisit whenever you like.\pHead back to town?$"
TrioGarden_RestText:
	.string "A warm cushion in the sun.\nRest with the girls?$"
TrioGarden_RestedText:
	.string "You all rest for a while.\nEveryone feels refreshed.$"
TrioGarden_CharmText:
	.string "Riko's Bloom holds a tiny\nflower from this garden.\pUse it on ordinary Riko\nto become Flower Riko.\pUse it again to return.\nThe charm stays with you.$"
TrioGarden_FullBagText:
	.string "Your Bag is full.\nThe flower is safe here.\pMake room and visit me,\nor ask Mom to bring it.$"
TrioGarden_EmptyFrameText:
	.string "A little empty frame.\nRoom for something lovely.$"
TrioGarden_CampFlowerText:
	.string "A pressed seaside flower.\nThree pawprints beside it.$"
TrioGarden_MemoryText:
	.string "Seeds under Riko's paws.\nWarm soil beside Bijuu.\pPenny holds the fence.\nA breeze carries petals.\pYou stay until sunset.\nFlowers in Riko's fur.$"
