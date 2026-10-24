@ Optional midgame island, persistent old-save-safe progress.
TrioRoad_Weather::
	goto_if_eq VAR_TRIO_ROAD_PENNY, 1, TrioRoad_Rain
	goto_if_eq VAR_TRIO_ROAD_PENNY, 2, TrioRoad_Rain
	setweather WEATHER_NONE
	end
TrioRoad_Rain::
	setweather WEATHER_RAIN
	end
@ User-authorized temporary New Bark mailbox preview; no Badge grants/reset.
TrioRoad_TestOffer::
	msgbox TrioRoad_TestOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_TestDecline
	special TrioRoad_RecordDeparture
	setvar VAR_TRIO_ROAD_RETURN, 2
	closemessage
	warp MAP_TRIO_ROAD_ISLAND, 18, 24
	waitstate
TrioRoad_TestDecline::
	return
TrioRoad_TestOfferText:
	.string "Scott left a ferry ticket.\pTEST the island road trip?\nNo Badge is needed.\pThe island ferry will\nbring you back home.$"

TrioRoad_Entrance::
	lockall
	faceplayer
	goto_if_unset FLAG_BADGE05_GET, TrioRoad_NotReady
	call TrioOutfit_Scott
	msgbox TrioRoad_FerryOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	special TrioRoad_RecordDeparture
	goto_if_ge VAR_TRIO_ROAD_VISITS, 2, TrioRoad_ReturnWelcome
	msgbox TrioRoad_FirstWelcome, MSGBOX_DEFAULT
TrioRoad_FerryWarp::
	closemessage
	warp MAP_TRIO_ROAD_ISLAND, 18, 24
	waitstate
	goto TrioRoad_End
TrioRoad_ReturnWelcome::
	msgbox TrioRoad_ReturnWelcomeText, MSGBOX_DEFAULT
	goto TrioRoad_FerryWarp
TrioRoad_NotReady::
	msgbox TrioRoad_NotReadyText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_Return::
	lockall
	faceplayer
	msgbox TrioRoad_ReturnOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	closemessage
	goto_if_eq VAR_TRIO_ROAD_RETURN, 2, TrioRoad_ReturnNewBark
	goto_if_eq VAR_TRIO_ROAD_RETURN, 1, TrioRoad_ReturnOlivine
	warp MAP_CIANWOOD_CITY, 23, 48
	waitstate
	goto TrioRoad_End
TrioRoad_ReturnNewBark::
	warp MAP_NEW_BARK_TOWN, 18, 12
	waitstate
	goto TrioRoad_End
TrioRoad_ReturnOlivine::
	warp MAP_OLIVINE_CITY_PORT_OUTSIDE, 17, 6
	waitstate
	goto TrioRoad_End
TrioRoad_ToWoods::
	lockall
	faceplayer
	msgbox TrioRoad_ToWoodsOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	closemessage
	warp MAP_TRIO_ROAD_WOODS, 14, 24
	waitstate
	goto TrioRoad_End
TrioRoad_ToCove::
	lockall
	faceplayer
	msgbox TrioRoad_ToCoveOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	closemessage
	warp MAP_TRIO_ROAD_COVE, 12, 16
	waitstate
	goto TrioRoad_End
TrioRoad_WoodsExit::
	lockall
	faceplayer
	msgbox TrioRoad_WoodsExitOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	closemessage
	warp MAP_TRIO_ROAD_ISLAND, 6, 11
	waitstate
	goto TrioRoad_End
TrioRoad_CoveExit::
	lockall
	faceplayer
	msgbox TrioRoad_CoveExitOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	closemessage
	warp MAP_TRIO_ROAD_ISLAND, 28, 15
	waitstate
	goto TrioRoad_End
TrioRoad_Resident::
	lockall
	faceplayer
	msgbox TrioRoad_ResidentText, MSGBOX_DEFAULT
	call TrioOutfit_ReactTown
	goto TrioRoad_End
TrioRoad_Tour::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_ROAD_RIKO, 4, TrioRoad_TourDone
	goto_if_ge VAR_TRIO_ROAD_RIKO, 1, TrioRoad_TourHint
	msgbox TrioRoad_TourOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	setvar VAR_TRIO_ROAD_RIKO, 1
	applymovement 2, TrioRoad_Hop
	waitmovement 0
TrioRoad_TourHint::
	msgbox TrioRoad_TourHintText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_TourDone::
	msgbox TrioRoad_TourDoneText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_TrailOne::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_ROAD_RIKO, 2, TrioRoad_TrailOneDone
	goto_if_ne VAR_TRIO_ROAD_RIKO, 1, TrioRoad_TourNotStarted
	msgbox TrioRoad_TrailOneText, MSGBOX_DEFAULT
	closemessage
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, TrioRoad_LeftName, TrioRoad_EastName, TrioRoad_BackName
	goto_if_eq VAR_RESULT, 1, TrioRoad_FirstRight
	goto_if_eq VAR_RESULT, 0, TrioRoad_FirstWrong
	goto TrioRoad_End
TrioRoad_FirstWrong::
	msgbox TrioRoad_FirstWrongText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_FirstRight::
	setvar VAR_TRIO_ROAD_RIKO, 2
	msgbox TrioRoad_FirstRightText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_TrailOneDone::
	msgbox TrioRoad_TrailOneDoneText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_TourNotStarted::
	msgbox TrioRoad_TourNotStartedText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_TrailTwo::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_ROAD_RIKO, 3, TrioRoad_TrailTwoDone
	goto_if_ne VAR_TRIO_ROAD_RIKO, 2, TrioRoad_TrailOrder
	msgbox TrioRoad_TrailTwoText, MSGBOX_DEFAULT
	closemessage
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, TrioRoad_CrumbsName, TrioRoad_NorthName, TrioRoad_BackName
	goto_if_eq VAR_RESULT, 1, TrioRoad_SecondRight
	goto_if_eq VAR_RESULT, 0, TrioRoad_SecondWrong
	goto TrioRoad_End
TrioRoad_SecondWrong::
	msgbox TrioRoad_SecondWrongText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_SecondRight::
	setvar VAR_TRIO_ROAD_RIKO, 3
	msgbox TrioRoad_SecondRightText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_TrailTwoDone::
	msgbox TrioRoad_TrailTwoDoneText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_TrailOrder::
	msgbox TrioRoad_TrailOrderText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_Lookout::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_ROAD_RIKO, 4, TrioRoad_LookoutReplay
	goto_if_ne VAR_TRIO_ROAD_RIKO, 3, TrioRoad_TrailOrder
	msgbox TrioRoad_LookoutOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	msgbox TrioRoad_LookoutText, MSGBOX_DEFAULT
	setvar VAR_TRIO_ROAD_RIKO, 4
	goto TrioRoad_End
TrioRoad_LookoutReplay::
	msgbox TrioRoad_LookoutReplayText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_WoodsBijuu::
	lockall
	faceplayer
	msgbox TrioRoad_WoodsBijuuText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_WoodsPenny::
	lockall
	faceplayer
	msgbox TrioRoad_WoodsPennyText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_GuardianRumor::
	lockall
	faceplayer
	call TrioOutfit_ReactTown
	goto_if_ge VAR_TRIO_ROAD_BIJUU, 4, TrioRoad_GuardianAfter
	goto_if_ge VAR_TRIO_ROAD_BIJUU, 1, TrioRoad_CaseHint
	msgbox TrioRoad_GuardianOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	setvar VAR_TRIO_ROAD_BIJUU, 1
TrioRoad_CaseHint::
	msgbox TrioRoad_CaseHintText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_GuardianAfter::
	msgbox TrioRoad_GuardianAfterText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_FisherClue::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_ROAD_BIJUU, 2, TrioRoad_FisherAgain
	goto_if_ne VAR_TRIO_ROAD_BIJUU, 1, TrioRoad_CaseNotStarted
	msgbox TrioRoad_FisherClueText, MSGBOX_DEFAULT
	setvar VAR_TRIO_ROAD_BIJUU, 2
	goto TrioRoad_End
TrioRoad_FisherAgain::
	msgbox TrioRoad_FisherAgainText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_CaseNotStarted::
	msgbox TrioRoad_CaseNotStartedText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_Pawprints::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_ROAD_BIJUU, 3, TrioRoad_PawprintsAgain
	goto_if_ne VAR_TRIO_ROAD_BIJUU, 2, TrioRoad_NeedFisher
	msgbox TrioRoad_PawprintsText, MSGBOX_DEFAULT
	setvar VAR_TRIO_ROAD_BIJUU, 3
	goto TrioRoad_End
TrioRoad_PawprintsAgain::
	msgbox TrioRoad_PawprintsAgainText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_NeedFisher::
	msgbox TrioRoad_NeedFisherText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_Windchime::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_ROAD_BIJUU, 4, TrioRoad_WindchimeAgain
	goto_if_ne VAR_TRIO_ROAD_BIJUU, 3, TrioRoad_NeedFisher
	msgbox TrioRoad_WindchimeOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	applymovement 6, TrioRoad_Hop
	waitmovement 0
	msgbox TrioRoad_WindchimeText, MSGBOX_DEFAULT
	setvar VAR_TRIO_ROAD_BIJUU, 4
	goto TrioRoad_End
TrioRoad_WindchimeAgain::
	msgbox TrioRoad_WindchimeAgainText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_CoveBijuu::
	lockall
	faceplayer
	msgbox TrioRoad_CoveBijuuText, MSGBOX_DEFAULT
	call TrioOutfit_ReactTown
	goto TrioRoad_End
TrioRoad_CoveResident::
	lockall
	faceplayer
	msgbox TrioRoad_CoveResidentText, MSGBOX_DEFAULT
	call TrioOutfit_ReactTown
	goto TrioRoad_End
TrioRoad_Picnic::
	lockall
	faceplayer
	goto_if_eq VAR_TRIO_ROAD_COMPLETE, 1, TrioRoad_SunsetReplay
	goto_if_eq VAR_TRIO_ROAD_PENNY, 0, TrioRoad_StormOffer
	goto_if_lt VAR_TRIO_ROAD_PENNY, 4, TrioRoad_StormHint
	goto_if_lt VAR_TRIO_ROAD_RIKO, 4, TrioRoad_FinaleWaiting
	goto_if_lt VAR_TRIO_ROAD_BIJUU, 4, TrioRoad_FinaleWaiting
	msgbox TrioRoad_SunsetOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	call TrioRoad_SunsetScene
	setvar VAR_TRIO_ROAD_COMPLETE, 1
	msgbox TrioRoad_SunsetSaved, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_StormOffer::
	msgbox TrioRoad_StormOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	setvar VAR_TRIO_ROAD_PENNY, 1
	setweather WEATHER_RAIN
	doweather
	msgbox TrioRoad_StormText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_StormHint::
	msgbox TrioRoad_StormHintText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_FinaleWaiting::
	msgbox TrioRoad_FinaleWaitingText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_SunsetReplay::
	call TrioRoad_SunsetScene
	goto TrioRoad_End
TrioRoad_SunsetScene::
	applymovement 3, TrioRoad_Settle
	waitmovement 0
	applymovement 4, TrioRoad_Hop
	waitmovement 0
	applymovement 5, TrioRoad_Settle
	waitmovement 0
	msgbox TrioRoad_SunsetText, MSGBOX_DEFAULT
	return
TrioRoad_Penny::
	lockall
	faceplayer
	goto_if_eq VAR_TRIO_ROAD_PENNY, 1, TrioRoad_PennyLead
	goto_if_eq VAR_TRIO_ROAD_PENNY, 2, TrioRoad_PennyCabin
	goto_if_ge VAR_TRIO_ROAD_PENNY, 3, TrioRoad_PennyProud
	msgbox TrioRoad_PennyBefore, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_PennyLead::
	msgbox TrioRoad_PennyLeadText, MSGBOX_DEFAULT
	closemessage
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrioRoad_TrustName, TrioRoad_SistersName, TrioRoad_BreatheName, TrioRoad_BackName
	goto_if_ge VAR_RESULT, 3, TrioRoad_End
	applymovement 5, TrioRoad_Hop
	waitmovement 0
	setvar VAR_TRIO_ROAD_PENNY, 2
	msgbox TrioRoad_PennyLeadResult, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_PennyCabin::
	msgbox TrioRoad_PennyCabinText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_PennyProud::
	msgbox TrioRoad_PennyProudText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_Riko::
	lockall
	faceplayer
	msgbox TrioRoad_RikoText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_Bijuu::
	lockall
	faceplayer
	msgbox TrioRoad_BijuuText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_Shelter::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_ROAD_PENNY, 3, TrioRoad_ShelterAgain
	goto_if_ne VAR_TRIO_ROAD_PENNY, 2, TrioRoad_ShelterIdle
	msgbox TrioRoad_ShelterOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	setvar VAR_TRIO_ROAD_PENNY, 3
	msgbox TrioRoad_RescueText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_ShelterAgain::
	msgbox TrioRoad_ShelterAgainText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_ShelterIdle::
	msgbox TrioRoad_ShelterIdleText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_Rest::
	lockall
	faceplayer
	msgbox TrioRoad_RestOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	call Common_EventScript_OutOfCenterPartyHeal
	goto_if_eq VAR_TRIO_ROAD_PENNY, 3, TrioRoad_RestRescue
	msgbox TrioRoad_RestText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_RestRescue::
	setvar VAR_TRIO_ROAD_PENNY, 4
	msgbox TrioRoad_RestRescueText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_CabinScott::
	lockall
	faceplayer
	call TrioOutfit_Scott
	goto_if_eq VAR_TRIO_ROAD_COMPLETE, 1, TrioRoad_CabinAfter
	goto_if_ge VAR_TRIO_ROAD_PENNY, 1, TrioRoad_CabinRainTalk
	msgbox TrioRoad_CabinScottText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_CabinRainTalk::
	msgbox TrioRoad_CabinRainTalkText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_CabinAfter::
	msgbox TrioRoad_CabinAfterText, MSGBOX_DEFAULT
	call TrioRoad_TrySouvenir
	goto TrioRoad_End
TrioRoad_TrySouvenir::
	goto_if_eq VAR_TRIO_ROAD_SOUVENIR, 1, TrioRoad_SouvenirReturn
	msgbox TrioRoad_SouvenirOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_SouvenirReturn
	giveitem ITEM_LEFTOVERS, 1
	goto_if_eq VAR_RESULT, FALSE, TrioRoad_SouvenirFull
	setvar VAR_TRIO_ROAD_SOUVENIR, 1
	msgbox TrioRoad_SouvenirThanks, MSGBOX_DEFAULT
	return
TrioRoad_SouvenirFull::
	msgbox TrioRoad_SouvenirFullText, MSGBOX_DEFAULT
	return
TrioRoad_SouvenirReturn::
	return
TrioRoad_CabinRiko::
	lockall
	faceplayer
	msgbox TrioRoad_CabinRikoText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_CabinBijuu::
	lockall
	faceplayer
	msgbox TrioRoad_CabinBijuuText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_CabinPenny::
	lockall
	faceplayer
	msgbox TrioRoad_CabinPennyText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_Photos::
	lockall
	faceplayer
	call TrioRoad_PhotoPages
	goto_if_ne VAR_TRIO_ROAD_COMPLETE, 1, TrioRoad_PhotoAlbumOffer
	call TrioRoad_ReadLetter
TrioRoad_PhotoAlbumOffer::
	msgbox TrioRoad_PhotoAlbumOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	call TrioOutfit_Album
	goto TrioRoad_End
TrioRoad_PhotoPages::
	msgbox TrioRoad_PhotoIntro, MSGBOX_DEFAULT
	call_if_ge VAR_TRIO_ROAD_RIKO, 4, TrioRoad_PhotoWoodland
	call_if_ge VAR_TRIO_ROAD_BIJUU, 4, TrioRoad_PhotoGuardian
	call_if_ge VAR_TRIO_ROAD_PENNY, 4, TrioRoad_PhotoRescue
	return
TrioRoad_PhotoWoodland::
	showmonpic SPECIES_RIKO, 10, 3
	msgbox TrioRoad_PhotoWoodlandText, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	return
TrioRoad_PhotoGuardian::
	showmonpic SPECIES_BIJUU, 10, 3
	msgbox TrioRoad_PhotoGuardianText, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	return
TrioRoad_PhotoRescue::
	showmonpic SPECIES_FIDOUGH, 10, 3
	msgbox TrioRoad_PhotoRescueText, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	return
TrioRoad_ReadLetter::
	msgbox TrioRoad_LetterText, MSGBOX_DEFAULT
	return
TrioRoad_ReadMemory::
	msgbox TrioRoad_MemoryText, MSGBOX_DEFAULT
	call TrioRoad_ReadLetter
	return
TrioRoad_Checklist::
	goto_if_eq VAR_TRIO_ROAD_COMPLETE, 1, TrioRoad_ChecklistDone
	msgbox TrioRoad_ChecklistText, MSGBOX_DEFAULT
	return
TrioRoad_ChecklistDone::
	msgbox TrioRoad_ChecklistDoneText, MSGBOX_DEFAULT
	return
TrioRoad_BattleBeach::
	lockall
	faceplayer
	msgbox TrioRoad_BattleBeachOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	call Common_EventScript_OutOfCenterPartyHeal
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_lt VAR_RESULT, 2, TrioRoad_NeedTwo
	trainerbattle_no_intro TRAINER_ROAD_BEACH, TrioRoad_ExhibitionDefeat
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioRoad_ExhibitionRetry
	setvar VAR_0x8004, TRAINER_ROAD_BEACH
	special TrioRoad_RecordBattleWin
	msgbox TrioRoad_BattleBeachWinText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_BattleForest::
	lockall
	faceplayer
	msgbox TrioRoad_BattleForestOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	call Common_EventScript_OutOfCenterPartyHeal
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_lt VAR_RESULT, 2, TrioRoad_NeedTwo
	trainerbattle_no_intro TRAINER_ROAD_FOREST, TrioRoad_ExhibitionDefeat
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioRoad_ExhibitionRetry
	setvar VAR_0x8004, TRAINER_ROAD_FOREST
	special TrioRoad_RecordBattleWin
	msgbox TrioRoad_BattleForestWinText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_Scott::
	lockall
	faceplayer
	call TrioOutfit_Scott
	msgbox TrioRoad_ScottOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioRoad_End
	call Common_EventScript_OutOfCenterPartyHeal
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_lt VAR_RESULT, 2, TrioRoad_NeedTwo
	trainerbattle_no_intro TRAINER_ROAD_SCOTT, TrioRoad_ExhibitionDefeat
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioRoad_ExhibitionRetry
	setvar VAR_0x8004, TRAINER_ROAD_SCOTT
	special TrioRoad_RecordBattleWin
	msgbox TrioRoad_ScottWinText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_NeedTwo::
	msgbox TrioRoad_NeedTwoText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_ExhibitionRetry::
	msgbox TrioRoad_ExhibitionRetryText, MSGBOX_DEFAULT
	goto TrioRoad_End
TrioRoad_End::
	closemessage
	releaseall
	end
TrioRoad_Hop::
	jump_in_place_down
	step_end
TrioRoad_Settle::
	walk_in_place_down
	delay_16
	step_end
TrioRoad_FerryOffer:
	.string "Scott: Five Badges, a\nferry, and a weekend with\pmy favorite girl.\pThe little island has a\ncabin, a woodland trail,\pand absolutely no\nschedule.\pI tried a schedule. Riko\nate the corner.\pShall we take the girls?\nTravel is free.$"

TrioRoad_FirstWelcome:
	.string "Scott checks five tickets.\nOne has a tiny bite.\pRiko appoints herself tour\nguide. Bijuu sits on the\pluggage.\pPenny chooses the seat\nbeside you. Scott saves\pthe other.\pOur cabin is the northeast\nhouse. We can come back\pwhenever we want.$"

TrioRoad_ReturnWelcomeText:
	.string "Scott: I hoped you would\ncome back. The cabin still\psmells like our picnic.\pI packed extra snacks.\nRiko packed extra\popinions.\pYour spot beside me is\nstill reserved.$"

TrioRoad_NotReadyText:
	.string "Scott: I booked us a\nlittle island getaway.\pAfter Chuck's Badge, meet\nme here. A weekend with\pyou is worth the wait.$"

TrioRoad_ReturnOffer:
	.string "The little ferry is ready.\nGo back to the mainland?\pYour cabin and every\nisland discovery stay here\pfor another visit.$"

TrioRoad_ToWoodsOffer:
	.string "The western woodland trail\nis open.\pYour Pom has already\nannounced that she knows a\pshortcut.\pFollow her into the woods?$"

TrioRoad_ToCoveOffer:
	.string "The eastern cove has a\ncurious local guardian\pstory.\pApparently its guardian\nhas blue eyes and likes\pfish.\pWalk down to the cove?$"

TrioRoad_WoodsExitOffer:
	.string "The path leads back to our\ncabin and ferry.\pReturn to the island\nshore?$"

TrioRoad_CoveExitOffer:
	.string "The shore path is clear,\neven in the rain.\pReturn to the cabin\nclearing?$"

TrioRoad_ResidentText:
	.string "Scott rented the cabin for\na weekend. Then he asked\pif you could keep using\nit.\pWe said yes. He looked\nmore excited than the\pPomeranian.\pThat is saying something.$"

TrioRoad_TourOffer:
	.string "Riko stands beside a map.\nIt is upside down.\pScott: Should we let our\nvery qualified tour guide\plead?\pFollow the low west\nmarker, the east snack\ptin, then the north\nlookout.$"

TrioRoad_TourHintText:
	.string "Riko points very firmly\nwest.\pScott quietly turns her\nmap around.\pFirst the west marker,\nthen the east snack tin,\pthen the north lookout.$"

TrioRoad_TourDoneText:
	.string "Riko insists the scenic\ndetour was intentional.\pHer map now has a sticker:\nOFFICIAL TOUR GUIDE.\pScott wrote SNACK DIVISION\nunderneath.$"

TrioRoad_TrailOneText:
	.string "Riko: Bark!\pHer nose says LEFT. The\ntrail marker says SNACK\pTIN - EAST.\pScott: I admire her\nconfidence. Which clue\pshall we follow?$"

TrioRoad_FirstWrongText:
	.string "A short dead end. Riko\nfinds a leaf and declares\pvictory.\pScott: Excellent leaf.\nShall we read the marker\pagain?$"

TrioRoad_FirstRightText:
	.string "East it is. Riko nods as\nif that was her plan.\pA crumb trail leads to a\ntin beside the east path.$"

TrioRoad_TrailOneDoneText:
	.string "SNACK TIN - EAST.\pThe tiny paw-written arrow\npoints west. Scott has\pcrossed it out.$"

TrioRoad_TourNotStartedText:
	.string "A woodland trail marker.\pAsk Riko by the southern\npath to start the tour.$"

TrioRoad_TrailTwoText:
	.string "The tin holds picnic\ncrumbs and an old lookout\psketch.\pRiko wants to follow the\ncrumbs south. The sketch\pshows the lookout north.\pWhat shall we follow?$"

TrioRoad_SecondWrongText:
	.string "Riko eats the final crumb.\pThe trail has disappeared.\pBijuu looks at the sketch.\nPenny waits patiently.$"

TrioRoad_SecondRightText:
	.string "Penny checks the north\npath. Bijuu carries the\psketch.\pRiko marches ahead. She\nannounces that everyone\phas passed her test.$"

TrioRoad_TrailTwoDoneText:
	.string "The empty snack tin now\nholds Riko's leaf.\pThe old sketch points\nnorth to the lookout.$"

TrioRoad_TrailOrderText:
	.string "A sealed picnic tin.\pStart Riko's tour, then\nread the west trail\pmarker.$"

TrioRoad_LookoutOffer:
	.string "The trees open onto an old\nlookout. The whole sea is\pbelow you.\pRiko has found a place the\nisland forgot.\pTake a family photo?$"

TrioRoad_LookoutText:
	.string "Scott sets the camera.\nRiko poses before he is\pready.\pBijuu blinks at the exact\nwrong moment. Penny leans\pagainst your leg.\pScott: Perfect. Every\nsingle part.\pA woodland photo is saved\nat the cabin.$"

TrioRoad_LookoutReplayText:
	.string "The sea still shines below\nthe trees.\pScott: Our official tour\nguide found my second\pfavorite view.\pHe looks at you. Riko\ndemands credit anyway.$"

TrioRoad_WoodsBijuuText:
	.string "Bijuu studies the lookout\nsketch.\pShe could have read it all\nalong. She wanted to see\phow this played out.$"

TrioRoad_WoodsPennyText:
	.string "Penny checks that the path\nis safe, then turns back\pfor Mom.\pShe never leaves anyone\nbehind.$"

TrioRoad_GuardianOffer:
	.string "A blue-eyed guardian rings\nour cove bell whenever the\ptide brings gifts.\pThat cat beside you has\nthe very same eyes!\pBijuu sits taller.\pInvestigate the little\nguardian mystery?$"

TrioRoad_CaseHintText:
	.string "Ask the fisherman in the\nsoutheast. Then inspect\pthe little cushion by the\ntide marks.\pThe old windchime is in\nthe northeast corner.$"

TrioRoad_GuardianAfterText:
	.string "Yes, yes, wind and a\ndelivery bell.\pBut the guardian is\nclearly a very good cat.\pBijuu accepts the title.\nShe has not corrected\panyone.$"

TrioRoad_FisherClueText:
	.string "The tide brings our fish\ndelivery boat. The bell\prings when the rope pulls.\pBut I found tiny paw marks\nby the resting cushion.\pBijuu seems suspiciously\ninterested in the fish.$"

TrioRoad_FisherAgainText:
	.string "The cushion by the tide\nmarks has little paw\pprints.\pOur delivery rope reaches\nthe northeast windchime.$"

TrioRoad_CaseNotStartedText:
	.string "The west-side caretaker\nhas a story about a\pblue-eyed guardian.\pBijuu would like you to\nhear it.$"

TrioRoad_PawprintsText:
	.string "Small cat prints circle a\nwarm cushion. A fish\pwrapper is tucked\nunderneath.\pThe bell rope has a toy\nmouse tied to its end.\pThis is a very comfortable\nguardian station.$"

TrioRoad_PawprintsAgainText:
	.string "Fish wrappers, a warm\ncushion, and a rope\pleading northeast.\pBijuu has excellent\nworking conditions.$"

TrioRoad_NeedFisherText:
	.string "Bijuu nudges the cushion.\pAsk the caretaker about\nthe guardian, then the\pfisherman about the bell.$"

TrioRoad_WindchimeOffer:
	.string "A sea breeze pulls the toy\nmouse. Ding!\pRiko startles. Penny\nchecks on her. Bijuu\pimmediately pounces.\pShow the caretaker the\nordinary explanation?$"

TrioRoad_WindchimeText:
	.string "Scott: Wind, a boat rope,\nand a cat who loves a toy.\pThe caretaker laughs, then\nthanks her new guardian\panyway.\pBijuu poses beside the\nbell. She has negotiated\pfish privileges.\pA guardian photo is saved\nat the cabin.$"

TrioRoad_WindchimeAgainText:
	.string "Ding! The windchime greets\nthe tide.\pBijuu accepts another\ncompliment for controlling\pthe sea.$"

TrioRoad_CoveBijuuText:
	.string "Bijuu sits beside the bell\nlike an ancient island\pguardian.\pHer tail gives away that\nshe is playing with the\pmouse.$"

TrioRoad_CoveResidentText:
	.string "The guardian needs a warm\ncushion, fresh fish, and a\pkind girl.\pWe have most of those. You\nbrought the kind girl.$"

TrioRoad_SunsetOffer:
	.string "All three girls had their\nown adventure. The sea is\pquiet again.\pScott: No battle. No\nplans. Just sunset with my\pfavorite family.\pSit on the blanket\ntogether?$"

TrioRoad_SunsetSaved:
	.string "The Great Trio Road Trip\nis saved in Mom's\pscrapbook.\pYour cabin has three trip\nphotos and a letter from\pScott.\pCome back whenever you\nwant.$"

TrioRoad_StormOfferText:
	.string "Scott opens the picnic\nbasket. Riko is already\pinside it.\pBijuu claims the sunny\nseat. Penny noses her\pblanket.\pStart your seaside picnic?$"

TrioRoad_StormText:
	.string "A shower rolls in from the\nsea. Scott grabs the\pbasket.\pRiko protests the weather.\nBijuu protests wet paws.\pPenny lifts her nose. She\nhas found somewhere safe.\pTalk to Penny beside the\npicnic blanket.$"

TrioRoad_StormHintText:
	.string "The picnic is safely\npacked. The ferry still\pruns.\pFollow Penny, then check\nthe dry blanket in the\pnortheast cabin.\pYou can leave and resume\nany time.$"

TrioRoad_FinaleWaitingText:
	.string "Scott: Penny got us home\ndry. Now we have time for\pthe woods and cove.\pFind Riko's lookout and\nsolve Bijuu's guardian\pstory.\pThen our sunset is all\nours.$"

TrioRoad_SunsetText:
	.string "Riko falls asleep on the\nblanket. One paw guards\pthe snack tin.\pBijuu takes Scott's seat.\nHe accepts his new place\pon the sand.\pPenny settles beside you\nand lets out a long, happy\psigh.\pScott: The ferry was late.\nOur guide got lost. Our\pguardian was a cat.\pWe got rained on. I lost\nmy seat.\pHe takes your hand.\pThat was my perfect date.\nBecause I spent it with\pyou.$"

TrioRoad_PennyBefore:
	.string "Penny tests the picnic\nblanket with one paw.\pThen she tests it with all\nfour paws.\pThis holiday is already\ngoing well.$"

TrioRoad_PennyLeadText:
	.string "Penny noses your hand,\nthen looks toward the\pcabin.\pShe checks on Riko and\nBijuu before taking\panother step.\pHow will Mom support her?$"

TrioRoad_PennyLeadResult:
	.string "Mom stays close. Riko\nwatches the path. Bijuu\pkeeps pace.\pPenny leads everyone to\nthe northeast cabin.\pShe waits at every turn to\ncheck that all her people\pare coming.\pInside, inspect the dry\nblanket at the lower\pright.$"

TrioRoad_PennyCabinText:
	.string "Penny looks at the\nnortheast cabin.\pThe dry blanket inside is\nwaiting. She wants\peveryone settled safely.$"

TrioRoad_PennyProudText:
	.string "Penny has checked every\nmember of her family.\pScott: I knew Pennys were\nthe best.\pRiko objects. Penny\nquietly wags.$"

TrioRoad_RikoText:
	.string "Riko has brought a leaf\nfrom the woodland trail.\pScott calls it a souvenir.\nRiko calls it a navigation\pcertificate.$"

TrioRoad_BijuuText:
	.string "Bijuu watches the tide.\pShe is considering\ncharging the island for\pguardian services.$"

TrioRoad_ShelterOffer:
	.string "A dry blanket waits beside\nthe cabin wall.\pPenny checks the window\nand the door, then noses\pthe blanket toward you.\pSettle everyone in?$"

TrioRoad_RescueText:
	.string "Scott dries Riko's ears.\nBijuu inspects the warmest\pchair.\pPenny makes one last\nround, then rests her chin\pon your knee.\pShe is not waiting to be\nrescued. She has brought\pher family home.\pRest on the left cushion\nto finish her rainy-day\pphoto.$"

TrioRoad_ShelterAgainText:
	.string "Penny's safe little\ncorner.\pA dry blanket, her\nsisters, and Mom close by.\pIt is everything she\nneeds.$"

TrioRoad_ShelterIdleText:
	.string "A soft, dry blanket.\pScott packed it before\nanything else.\pPenny approves his\npriorities.$"

TrioRoad_RestOffer:
	.string "Rest together in the\ncabin? Everyone will be\phealed.\pThere is no checkout time.$"

TrioRoad_RestText:
	.string "The kettle warms. Riko\ndozes. Bijuu chooses a\pchair she knows Scott\nwanted.\pPenny rests with one paw\ntouching you.\pYou have nowhere you need\nto be.$"

TrioRoad_RestRescueText:
	.string "The rain eases outside.\nPenny finally closes her\peyes.\pScott: She got braver\nbecause you made her feel\psafe.\pHe kisses your forehead.\pA rainy-day photo is saved\nat the cabin. The shore is\pclear again.$"

TrioRoad_CabinScottText:
	.string "Scott: I brought one\nblanket for the picnic,\pthree for the girls, and\none for us.\pPenny has voted to keep\nall five.\pFine. I will just have to\nkeep you warm myself.$"

TrioRoad_CabinRainTalkText:
	.string "Scott: We can stay as long\nas we like. There is no\pwrong way to have a\nholiday.\pCheck the lower-right\nblanket after Penny leads\pus here, then rest on the\nleft.\pWhen the girls are done,\nmeet me at the picnic\pcushion for sunset.$"

TrioRoad_CabinAfterText:
	.string "Scott: This is our place\nnow. A little pause in the\pmiddle of everything.\pIf the world gets loud, we\ncan come back.\pYou, me, and the three\nbest girls.\pMy letter is beside the\ncabin photos.$"

TrioRoad_SouvenirOffer:
	.string "Scott packed a picnic tin\nfor the next journey.\pAccept one Leftovers? It\nis a little reminder of\pour weekend.$"

TrioRoad_SouvenirThanks:
	.string "Scott: For the long road\nhome.\pRiko: For the very short\nroad to my mouth.$"

TrioRoad_SouvenirFullText:
	.string "Your Bag is full.\pScott will keep the picnic\ntin here. Come back\pwhenever you have room.$"

TrioRoad_CabinRikoText:
	.string "Riko sleeps beside her\nofficial tour-guide leaf.\pShe dreamed of being in\ncharge. Then she woke up\pand continued.$"

TrioRoad_CabinBijuuText:
	.string "Bijuu is on the best\nchair.\pIt was Scott's best chair\nuntil Bijuu arrived.\pThe island guardian has\njurisdiction.$"

TrioRoad_CabinPennyText:
	.string "Penny has made a small\nnest with the blanket\pcorners.\pThere is room for her\nsisters. There is always\proom for Mom.$"

TrioRoad_PhotoAlbumOfferText:
	.string "Look through the outfit\nalbum too?$"

TrioRoad_PhotoIntro:
	.string "Our cabin photo board.\pWoodland lookout. Cove\nguardian. Rainy-day\prescue.\pEach adventure leaves a\nphoto here forever.$"

TrioRoad_PhotoWoodlandText:
	.string "Lost on Purpose:\pRiko poses at the old\nlookout. Her sisters stand\pbeside Mom.\pScott is behind the\ncamera, smiling at all\pfour of you.$"

TrioRoad_PhotoGuardianText:
	.string "Guardian of the Fish:\pBijuu poses beside the\nordinary windchime.\pThe whole cove has decided\nthat she is extraordinary\panyway.$"

TrioRoad_PhotoRescueText:
	.string "Everyone Safe:\pPenny sits beside a dry\nblanket. Riko and Bijuu\pare already asleep.\pMom's hand is on her back.\nShe looks wonderfully sure\pof herself.$"

TrioRoad_LetterText:
	.string "Scott's cabin letter:\pI wanted to give you a\nperfect weekend.\pThen Riko found a better\nview. Bijuu found a new\ptitle. Penny found her\ncourage.\pI found another reason to\nfall in love with you.\pKeep this cabin. Keep\nthese little days. I will\palways save you a place\nbeside me.\pLove, Scott.$"

TrioRoad_MemoryText:
	.string "The Great Trio Road Trip:\pRiko took confident wrong\nturns and found an old\plookout.\pBijuu became the guardian\nof a windchime and a fish\pdelivery.\pPenny led everyone home\nthrough the rain.\pAt sunset, Scott lost his\nseat and held Mom's hand.\pHe called it his perfect\ndate.$"

TrioRoad_ChecklistText:
	.string "Road trip - waiting.\pAfter Chuck's Badge, meet\nScott on Cianwood's beach\por at Olivine's port.\pWoods, cove, rainy picnic,\ncabin rest, then sunset.\pAll battles are optional.$"

TrioRoad_ChecklistDoneText:
	.string "Road trip - saved.\pOur cabin, three photos,\nand Scott's sunset letter.\pThe ferry can take us back\nwhenever we like.$"

TrioRoad_BattleBeachOffer:
	.string "Vacationer Marina: Water\nshoes, sunny smiles, and a\pdoubles team!\pA friendly level 34 beach\nmatch? We heal before and\pafterward.$"

TrioRoad_BattleBeachWinText:
	.string "A lovely match! The girls\nmade quite an impression.\pNo prizes needed. This was\npart of our holiday.$"

TrioRoad_BattleForestOffer:
	.string "Vacationer Fern: The\nforest planned our team.\pWe packed the snacks.\pA friendly level 36\ndoubles match? We heal\pbefore and afterward.$"

TrioRoad_BattleForestWinText:
	.string "A lovely match! The girls\nmade quite an impression.\pNo prizes needed. This was\npart of our holiday.$"

TrioRoad_ScottOffer:
	.string "Scott: You look cute on\nholiday. I trained for\pdoubles. Riko trained for\nlunch.\pA friendly level 38 match?\nEveryone heals. Our sunset\pneeds no battle.$"

TrioRoad_ScottWinText:
	.string "Scott: You keep winning me\nover.\pPenny gets my vote for\nmost valuable girl. Riko\phas filed an appeal.$"

TrioRoad_NeedTwoText:
	.string "Doubles needs two non-Egg\npartners.\pEveryone is healed. You\ncan return with another\ppartner any time.$"

TrioRoad_ExhibitionRetryText:
	.string "Everyone is healed. Your\nholiday continues.\pTry again, take a walk, or\nskip the match entirely.\pScott: I still get my\nperfect date with you.$"

TrioRoad_ExhibitionDefeat:
	.string "Our perfect plan met three\nperfect girls.$"

TrioRoad_LeftName:
	.string "Trust Riko: left$"

TrioRoad_EastName:
	.string "Read marker: east$"

TrioRoad_CrumbsName:
	.string "Follow crumbs south$"

TrioRoad_NorthName:
	.string "Follow sketch north$"

TrioRoad_TrustName:
	.string "Follow Penny$"

TrioRoad_SistersName:
	.string "Stay with her sisters$"

TrioRoad_BreatheName:
	.string "Take a gentle breath$"

TrioRoad_BackName:
	.string "Take a break$"

