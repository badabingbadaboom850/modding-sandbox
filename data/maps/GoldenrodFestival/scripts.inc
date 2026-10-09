@ Goldenrod's family festival. Save flags track achievements, not map-local games.
GoldenrodFestival_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TrioFestival_Transition
	.byte 0
TrioFestival_Transition:
	setvar VAR_TEMP_B, 0
	setvar VAR_TEMP_C, 0
	setvar VAR_TEMP_D, 0
	setvar VAR_TEMP_E, 0
	end

@ Helpers called by already-locked interactions must return on decline.
TrioFestival_Invitation::
	goto_if_unset FLAG_BADGE04_GET, TrioFestival_Return
	goto_if_set FLAG_TRIO_FESTIVAL_PICNIC, TrioFestival_Return
	msgbox TrioFestival_InvitationText, MSGBOX_DEFAULT
TrioFestival_Return:
	return
TrioFestival_TestShuttle::
#if TRIO_FESTIVAL_TEST_MODE
	msgbox TrioFestival_TestOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioFestival_Return
	closemessage
	warp MAP_GOLDENROD_CITY_POKEMON_CENTER, 7, 6
	waitstate
	releaseall
	end
#else
	return
#endif
TrioFestival_Entrance::
	lockall
	faceplayer
	goto_if_unset FLAG_BADGE04_GET, TrioFestival_NotReady
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioFestival_MissingGirls
	msgbox TrioFestival_EntranceText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioFestival_End
	setflag FLAG_TRIO_FESTIVAL_STARTED
	closemessage
	warp MAP_GOLDENROD_FESTIVAL, 14, 47
	waitstate
	goto TrioFestival_End
TrioFestival_NotReady:
	msgbox TrioFestival_NotReadyText, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_MissingGirls:
	msgbox TrioFestival_MissingGirlsText, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_CheckParty:
	call TrioSisters_CheckAll
	return

TrioFestival_Host::
	lockall
	faceplayer
	msgbox TrioFestival_Welcome, MSGBOX_DEFAULT
	call TrioRift_FestivalOffer
TrioFestival_HostMenu:
	closemessage
	multichoice 0, 0, MULTI_TRIO_FESTIVAL_HOST, FALSE
	goto_if_eq VAR_RESULT, 0, TrioFestival_Itinerary
	goto_if_eq VAR_RESULT, 1, TrioFestival_Rest
	goto_if_eq VAR_RESULT, 2, TrioFestival_Leave
#if TRIO_FESTIVAL_TEST_MODE
	msgbox TrioFestival_TestToolsOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TrioFestival_TestTools
#endif
	goto TrioFestival_End
TrioFestival_Itinerary:
	msgbox TrioFestival_Directions, MSGBOX_DEFAULT
	call_if_set FLAG_TRIO_FESTIVAL_RIKO, TrioFestival_RikoSchedule
	call_if_set FLAG_TRIO_FESTIVAL_BIJUU, TrioFestival_BijuuSchedule
	call_if_set FLAG_TRIO_FESTIVAL_PENNY, TrioFestival_PennySchedule
	call_if_set FLAG_TRIO_FESTIVAL_SNACK_B, TrioFestival_SnackSchedule
	call TrioFestival_ReadRibbons
	goto TrioFestival_HostMenu
TrioFestival_RikoSchedule:
	msgbox TrioFestival_RikoScheduleText, MSGBOX_DEFAULT
	return
TrioFestival_BijuuSchedule:
	msgbox TrioFestival_BijuuScheduleText, MSGBOX_DEFAULT
	return
TrioFestival_PennySchedule:
	msgbox TrioFestival_PennyScheduleText, MSGBOX_DEFAULT
	return
TrioFestival_SnackSchedule:
	msgbox TrioFestival_SnackScheduleText, MSGBOX_DEFAULT
	return
TrioFestival_Rest:
	call Common_EventScript_OutOfCenterPartyHeal
	goto TrioFestival_HostMenu
TrioFestival_Leave:
	closemessage
	warp MAP_GOLDENROD_CITY_POKEMON_CENTER, 7, 6
	waitstate
	goto TrioFestival_End
TrioFestival_TestTools:
	closemessage
	multichoice 0, 0, MULTI_TRIO_FESTIVAL_TEST, FALSE
	goto_if_eq VAR_RESULT, 0, TrioFestival_Leave
	goto_if_eq VAR_RESULT, 1, TrioFestival_TestHome
	goto_if_eq VAR_RESULT, 2, TrioFestival_TestReset
	goto TrioFestival_End
TrioFestival_TestHome:
	closemessage
	warp MAP_NEW_BARK_TOWN_HOUSE1, 4, 7
	waitstate
	goto TrioFestival_End
TrioFestival_TestReset:
	msgbox TrioFestival_ResetOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioFestival_End
	clearflag FLAG_TRIO_FESTIVAL_RIKO
	clearflag FLAG_TRIO_FESTIVAL_CLUE_A
	clearflag FLAG_TRIO_FESTIVAL_CLUE_B
	clearflag FLAG_TRIO_FESTIVAL_BIJUU
	clearflag FLAG_TRIO_FESTIVAL_PENNY
	clearflag FLAG_TRIO_FESTIVAL_SNACK_A
	clearflag FLAG_TRIO_FESTIVAL_SNACK_B
	clearflag FLAG_TRIO_FESTIVAL_PICNIC
	clearflag FLAG_TRIO_FESTIVAL_SCOTT_WIN
	setvar VAR_TEMP_B, 0
	setvar VAR_TEMP_C, 0
	setvar VAR_TEMP_D, 0
	setvar VAR_TEMP_E, 0
	msgbox TrioFestival_ResetText, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_Nurse::
	lockall
	faceplayer
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox TrioFestival_NurseText, MSGBOX_DEFAULT
	goto TrioFestival_End

@ Three visual imitation rounds. Wrong answers gently retry the current round.
TrioFestival_Riko::
	lockall
	faceplayer
	call TrioFestival_CheckParty
	goto_if_eq VAR_RESULT, FALSE, TrioFestival_MissingGirls
	msgbox TrioFestival_RikoOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioFestival_End
	setvar VAR_TEMP_B, 0
TrioFestival_RikoRound:
	msgbox TrioFestival_WatchRiko, MSGBOX_DEFAULT
	closemessage
	random 3
	copyvar VAR_TEMP_C, VAR_RESULT
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	goto_if_eq VAR_TEMP_C, 0, TrioFestival_RikoLeft
	goto_if_eq VAR_TEMP_C, 1, TrioFestival_RikoRight
	applymovement 3, TrioFestival_Jump
	goto TrioFestival_RikoWait
TrioFestival_RikoLeft:
	applymovement 3, TrioFestival_Left
	goto TrioFestival_RikoWait
TrioFestival_RikoRight:
	applymovement 3, TrioFestival_Right
TrioFestival_RikoWait:
	waitmovement 0
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	msgbox TrioFestival_RikoQuestion, MSGBOX_DEFAULT
	closemessage
	multichoice 0, 0, MULTI_TRIO_FESTIVAL_RIKO, FALSE
	goto_if_ge VAR_RESULT, 3, TrioFestival_End
	goto_if_ne VAR_RESULT, VAR_TEMP_C, TrioFestival_RikoWrong
	addvar VAR_TEMP_B, 1
	goto_if_eq VAR_TEMP_B, 3, TrioFestival_RikoWin
	msgbox TrioFestival_RikoCorrect, MSGBOX_DEFAULT
	goto TrioFestival_RikoRound
TrioFestival_RikoWrong:
	msgbox TrioFestival_RikoWrongText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TrioFestival_RikoRound
	goto TrioFestival_End
TrioFestival_RikoWin:
	playmoncry SPECIES_RIKO, CRY_MODE_NORMAL
	waitmoncry
	setflag FLAG_TRIO_FESTIVAL_RIKO
	msgbox TrioFestival_RikoWinText, MSGBOX_DEFAULT
	goto TrioFestival_End

@ Two independent witness clues, then inspect actual baskets. Persistent across visits.
TrioFestival_Bijuu::
	lockall
	faceplayer
	call TrioFestival_CheckParty
	goto_if_eq VAR_RESULT, FALSE, TrioFestival_MissingGirls
	goto_if_set FLAG_TRIO_FESTIVAL_BIJUU, TrioFestival_BijuuRemember
	msgbox TrioFestival_BijuuOffer, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_BijuuRemember:
	msgbox TrioFestival_BijuuWinText, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_WitnessA::
	lockall
	faceplayer
	goto_if_set FLAG_TRIO_FESTIVAL_BIJUU, TrioFestival_WitnessAfter
	setflag FLAG_TRIO_FESTIVAL_CLUE_A
	msgbox TrioFestival_ClueA, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_WitnessB::
	lockall
	faceplayer
	goto_if_set FLAG_TRIO_FESTIVAL_BIJUU, TrioFestival_WitnessAfter
	setflag FLAG_TRIO_FESTIVAL_CLUE_B
	msgbox TrioFestival_ClueB, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_WitnessAfter:
	msgbox TrioFestival_WitnessAfterText, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_BasketLeft::
	lockall
	msgbox TrioFestival_WrongBasket, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_BasketRight::
	lockall
	msgbox TrioFestival_WrongBasket, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_BasketMiddle::
	lockall
	goto_if_set FLAG_TRIO_FESTIVAL_BIJUU, TrioFestival_BijuuRemember
	call TrioFestival_CheckParty
	goto_if_eq VAR_RESULT, FALSE, TrioFestival_MissingGirls
	goto_if_unset FLAG_TRIO_FESTIVAL_CLUE_A, TrioFestival_NeedClues
	goto_if_unset FLAG_TRIO_FESTIVAL_CLUE_B, TrioFestival_NeedClues
	setflag FLAG_TRIO_FESTIVAL_BIJUU
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	applymovement 4, TrioFestival_Jump
	waitmovement 0
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	playmoncry SPECIES_BIJUU, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioFestival_BijuuWinText, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_NeedClues:
	msgbox TrioFestival_NeedCluesText, MSGBOX_DEFAULT
	goto TrioFestival_End

@ Walk to three physical course markers in order. Support choices always succeed.
TrioFestival_Penny::
	lockall
	faceplayer
	call TrioFestival_CheckParty
	goto_if_eq VAR_RESULT, FALSE, TrioFestival_MissingGirls
	msgbox TrioFestival_PennyOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioFestival_End
	setvar VAR_TEMP_D, 0
	setvar VAR_TEMP_E, 1
	msgbox TrioFestival_CourseDirections, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_PennyArch::
	lockall
	setvar VAR_0x8005, 0
	goto TrioFestival_CourseMarker
TrioFestival_PennyBridge::
	lockall
	setvar VAR_0x8005, 1
	goto TrioFestival_CourseMarker
TrioFestival_PennyBell::
	lockall
	setvar VAR_0x8005, 2
TrioFestival_CourseMarker:
	call TrioFestival_CheckParty
	goto_if_eq VAR_RESULT, FALSE, TrioFestival_MissingGirls
	goto_if_ne VAR_TEMP_E, 1, TrioFestival_CourseIdle
	goto_if_ne VAR_TEMP_D, VAR_0x8005, TrioFestival_CourseOrder
	goto_if_eq VAR_TEMP_D, 0, TrioFestival_CourseArch
	goto_if_eq VAR_TEMP_D, 1, TrioFestival_CourseBridge
	msgbox TrioFestival_PennyBellText, MSGBOX_DEFAULT
	goto TrioFestival_PennyChoice
TrioFestival_CourseArch:
	msgbox TrioFestival_PennyArchText, MSGBOX_DEFAULT
	goto TrioFestival_PennyChoice
TrioFestival_CourseBridge:
	msgbox TrioFestival_PennyBridgeText, MSGBOX_DEFAULT
TrioFestival_PennyChoice:
	closemessage
	multichoice 0, 0, MULTI_TRIO_FESTIVAL_PENNY, FALSE
	goto_if_ge VAR_RESULT, 3, TrioFestival_CourseCancel
	goto_if_eq VAR_RESULT, 0, TrioFestival_PennyEncourage
	goto_if_eq VAR_RESULT, 1, TrioFestival_PennyDemonstrate
	msgbox TrioFestival_PennySisterText, MSGBOX_DEFAULT
	goto TrioFestival_PennyMove
TrioFestival_PennyEncourage:
	msgbox TrioFestival_PennyEncourageText, MSGBOX_DEFAULT
	goto TrioFestival_PennyMove
TrioFestival_PennyDemonstrate:
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	applymovement LOCALID_PLAYER, TrioFestival_Jump
	waitmovement 0
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	msgbox TrioFestival_PennyDemonstrateText, MSGBOX_DEFAULT
TrioFestival_PennyMove:
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	applymovement 5, TrioFestival_Jump
	waitmovement 0
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	addvar VAR_TEMP_D, 1
	goto_if_ne VAR_TEMP_D, 3, TrioFestival_CourseNext
	setvar VAR_TEMP_E, 0
	setflag FLAG_TRIO_FESTIVAL_PENNY
	playmoncry SPECIES_FIDOUGH, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioFestival_PennyWinText, MSGBOX_DEFAULT
	goto TrioFestival_End

TrioFestival_CourseNext:
	msgbox TrioFestival_CourseNextText, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_CourseCancel:
	setvar VAR_TEMP_E, 0
	msgbox TrioFestival_CourseCancelText, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_CourseIdle:
	msgbox TrioFestival_CourseIdleText, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_CourseOrder:
	msgbox TrioFestival_CourseOrderText, MSGBOX_DEFAULT
	goto TrioFestival_End

@ Optional-friendly snack battles: only actual victories finish the hunt.
TrioFestival_SnackA::
	lockall
	faceplayer
	call TrioFestival_CheckParty
	goto_if_eq VAR_RESULT, FALSE, TrioFestival_MissingGirls
	goto_if_set FLAG_TRIO_FESTIVAL_SNACK_A, TrioFestival_SnackADone
	msgbox TrioFestival_SnackAOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioFestival_End
	trainerbattle_no_intro TRAINER_FESTIVAL_SNACK_A, TrioFestival_SnackDefeatText
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioFestival_SnackRetry
	setflag FLAG_TRIO_FESTIVAL_SNACK_A
TrioFestival_SnackADone:
	msgbox TrioFestival_SnackAClue, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_SnackB::
	lockall
	faceplayer
	call TrioFestival_CheckParty
	goto_if_eq VAR_RESULT, FALSE, TrioFestival_MissingGirls
	goto_if_set FLAG_TRIO_FESTIVAL_SNACK_B, TrioFestival_SnackBDone
	goto_if_unset FLAG_TRIO_FESTIVAL_SNACK_A, TrioFestival_SnackNeedScout
	msgbox TrioFestival_SnackBOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioFestival_End
	trainerbattle_no_intro TRAINER_FESTIVAL_SNACK_B, TrioFestival_SnackDefeatText
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioFestival_SnackRetry
	setflag FLAG_TRIO_FESTIVAL_SNACK_B
TrioFestival_SnackBDone:
	msgbox TrioFestival_SnackWinText, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_SnackNeedScout:
	msgbox TrioFestival_SnackNeedScoutText, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_SnackRetry:
	msgbox TrioFestival_SnackRetryText, MSGBOX_DEFAULT
	goto TrioFestival_End

TrioFestival_Scott::
	lockall
	faceplayer
	call TrioFestival_CheckParty
	goto_if_eq VAR_RESULT, FALSE, TrioFestival_MissingGirls
	goto_if_unset FLAG_TRIO_FESTIVAL_RIKO, TrioFestival_ScottWaiting
	goto_if_unset FLAG_TRIO_FESTIVAL_BIJUU, TrioFestival_ScottWaiting
	goto_if_unset FLAG_TRIO_FESTIVAL_PENNY, TrioFestival_ScottWaiting
	goto_if_unset FLAG_TRIO_FESTIVAL_SNACK_B, TrioFestival_ScottWaiting
	msgbox TrioFestival_ScottOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioFestival_End
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox TrioFestival_ScottIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_FESTIVAL_SCOTT, TrioFestival_ScottDefeat
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioFestival_ScottLost
	setflag FLAG_TRIO_FESTIVAL_SCOTT_WIN
	msgbox TrioFestival_ScottWonText, MSGBOX_DEFAULT
	goto TrioFestival_Picnic
TrioFestival_ScottLost:
	msgbox TrioFestival_ScottLostText, MSGBOX_DEFAULT
TrioFestival_Picnic:
	goto_if_set FLAG_TRIO_FESTIVAL_PICNIC, TrioFestival_PicnicReplay
	msgbox TrioFestival_PicnicText, MSGBOX_DEFAULT
	msgbox TrioFestival_LetterText, MSGBOX_DEFAULT
	setflag FLAG_TRIO_FESTIVAL_PICNIC
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	call TrioRift_FestivalOffer
	goto TrioFestival_End
TrioFestival_PicnicReplay:
	msgbox TrioFestival_PicnicAgain, MSGBOX_DEFAULT
	goto TrioFestival_End
TrioFestival_ScottWaiting:
	msgbox TrioFestival_ScottWaitingText, MSGBOX_DEFAULT
	call_if_set FLAG_TRIO_FESTIVAL_RIKO, TrioFestival_RikoSchedule
	call_if_set FLAG_TRIO_FESTIVAL_BIJUU, TrioFestival_BijuuSchedule
	call_if_set FLAG_TRIO_FESTIVAL_PENNY, TrioFestival_PennySchedule
	goto TrioFestival_End

TrioFestival_Visitor::
	lockall
	faceplayer
	msgbox TrioFestival_VisitorText, MSGBOX_DEFAULT
	call_if_set FLAG_TRIO_FESTIVAL_RIKO, TrioFestival_VisitorRiko
	call_if_set FLAG_TRIO_FESTIVAL_BIJUU, TrioFestival_VisitorBijuu
	call_if_set FLAG_TRIO_FESTIVAL_PENNY, TrioFestival_VisitorPenny
	goto TrioFestival_End
TrioFestival_VisitorRiko:
	msgbox TrioFestival_VisitorRikoText, MSGBOX_DEFAULT
	return
TrioFestival_VisitorBijuu:
	msgbox TrioFestival_VisitorBijuuText, MSGBOX_DEFAULT
	return
TrioFestival_VisitorPenny:
	msgbox TrioFestival_VisitorPennyText, MSGBOX_DEFAULT
	return
TrioFestival_ReadRibbons::
	msgbox TrioFestival_RibbonsIntro, MSGBOX_DEFAULT
	call_if_set FLAG_TRIO_FESTIVAL_RIKO, TrioFestival_RibbonRiko
	call_if_set FLAG_TRIO_FESTIVAL_BIJUU, TrioFestival_RibbonBijuu
	call_if_set FLAG_TRIO_FESTIVAL_PENNY, TrioFestival_RibbonPenny
	return
TrioFestival_RibbonRiko:
	msgbox TrioFestival_RibbonRikoText, MSGBOX_DEFAULT
	return
TrioFestival_RibbonBijuu:
	msgbox TrioFestival_RibbonBijuuText, MSGBOX_DEFAULT
	return
TrioFestival_RibbonPenny:
	msgbox TrioFestival_RibbonPennyText, MSGBOX_DEFAULT
	return
TrioFestival_ReadMemory::
	msgbox TrioFestival_MemoryText, MSGBOX_DEFAULT
	msgbox TrioFestival_LetterText, MSGBOX_DEFAULT
	return
TrioFestival_Checklist::
	goto_if_set FLAG_TRIO_FESTIVAL_PICNIC, TrioFestival_ChecklistDone
	msgbox TrioFestival_ChecklistHint, MSGBOX_DEFAULT
	return
TrioFestival_ChecklistDone:
	msgbox TrioFestival_ChecklistSaved, MSGBOX_DEFAULT
	return
TrioFestival_End:
	closemessage
	releaseall
	end
TrioFestival_Left:
	walk_in_place_fast_left
	delay_16
	step_end
TrioFestival_Right:
	walk_in_place_fast_right
	delay_16
	step_end
TrioFestival_Jump:
	jump_in_place_down
	step_end

TrioFestival_InvitationText:
	.string "Scott planned a day out\nfor you and the girls!\pThe guide in Goldenrod's\nPokemon Center has your\pinvitation. Four Badges\nopen the festival.$"

TrioFestival_TestOffer:
	.string "FESTIVAL TEST SHUTTLE\pVisit Goldenrod's Center?\nTalk to the guide at the\pright of the lobby.\pThis skips travel only. It\ndoes not finish story\pevents.$"

TrioFestival_EntranceText:
	.string "The Girls' Day Out!\pScott booked a little\ngarden for Mom and her\pgirls. Shall we go?$"

TrioFestival_NotReadyText:
	.string "Scott is still decorating.\nCome back after your\pfourth Johto Badge.$"

TrioFestival_MissingGirlsText:
	.string "Bring Riko, Bijuu and\nPenny together. Their\psupported forms count too.$"

TrioFestival_Welcome:
	.string "Welcome to your day out!\pScott has a schedule. The\ngirls have other plans.$"

TrioFestival_TestToolsOffer:
	.string "Open temporary festival\ntest tools?$"

TrioFestival_Directions:
	.string "Riko: northwest stage.\nBijuu: north lawn. Penny:\peast lawn.\pAsk the Lass beside Bijuu\nand the kid by the\psoutheast benches for\nclues.\pThree toy baskets stand\nalong the south path. Look\pbetween the benches.\pSnack scout: west lawn.\nSnack boss: southeast\plawn.\pScott waits near the\nentrance. Finish the three\pactivities and recover the\nsnacks.$"

TrioFestival_RikoScheduleText:
	.string "11:06 - Apologize on\nRiko's behalf. Her concert\pwas heard in Violet.$"

TrioFestival_BijuuScheduleText:
	.string "11:03 - Find Bijuu. 11:04\n- Ask Bijuu why the prize\psmells like Bijuu.$"

TrioFestival_PennyScheduleText:
	.string "11:09 - Penny is doing\ngreat. Leave this part\palone.$"

TrioFestival_SnackScheduleText:
	.string "11:00 - Quiet lunch. 12:00\n- Negotiate snack custody\pwith a squirrel.$"

TrioFestival_ResetOffer:
	.string "Reset only this festival's\ngames, ribbons and picnic\ppage? Other progress stays\nsaved.$"

TrioFestival_ResetText:
	.string "Festival reset. Try a\ndifferent choice or test\panother ending!$"

TrioFestival_NurseText:
	.string "All rested! Take your\ntime. A day out should\pfeel like a day off.$"

TrioFestival_RikoOffer:
	.string "Riko's Grand Performance!\pWatch her move, then name\nthe move. Three correct\prounds earn her ribbon.\nReady?$"

TrioFestival_WatchRiko:
	.string "Watch Riko closely! Left,\nright, or a little jump?$"

TrioFestival_RikoQuestion:
	.string "Which move did she do?$"

TrioFestival_RikoCorrect:
	.string "Perfect! Riko bows to an\naudience she assumes is\penormous.$"

TrioFestival_RikoWrongText:
	.string "Riko calls that artistic\ninterpretation. Try this\pround again?$"

TrioFestival_RikoWinText:
	.string "Three perfect rounds! Riko\nearns the Big Voice\pRibbon.\pShe demands an encore. You\ncan play again anytime.$"

TrioFestival_BijuuOffer:
	.string "The festival prize is\nmissing! Bijuu appoints\pherself detective.\pAsk the Lass beside her\nand the kid by the\psoutheast benches. Then\nsearch the three\psouth-path baskets.$"

TrioFestival_ClueA:
	.string "I saw a tiny paw carry the\nprize south. Not the first\pbasket. That one holds\nbrushes.$"

TrioFestival_ClueB:
	.string "The last basket holds\nspare keys. Someone curled\pup with the prize BETWEEN\nthe other two.$"

TrioFestival_WitnessAfterText:
	.string "Bijuu solved a crime she\ncommitted. Please guard\pyour prizes.$"

TrioFestival_WrongBasket:
	.string "Only festival props here.\nBijuu pretends not to know\pwhere the prize is.$"

TrioFestival_NeedCluesText:
	.string "Bijuu insists on a proper\ninvestigation. Hear BOTH\pwitnesses before searching\nhere.$"

TrioFestival_BijuuWinText:
	.string "The middle basket! The\nprize is under Bijuu's\pfavorite toy.\pShe hid it so Mom would\nplay with her. Case\pclosed.\pBijuu earns the Tiny\nDetective Ribbon. She\paccepts all the credit.$"

TrioFestival_PennyOffer:
	.string "Penny's Little Courage\nCourse!\pA soft arch, a pretend\nbridge and a little bell.\pHelp her in her own time?$"

TrioFestival_PennyArchText:
	.string "First, the ribbon arch.\nPenny pauses beneath the\pfluttering ends. How will\nMom help?$"

TrioFestival_PennyBridgeText:
	.string "Next, the pretend bridge.\nPenny checks that Mom is\pclose. How will you help?$"

TrioFestival_PennyBellText:
	.string "Last, ring the little\nbell. Penny watches its\pshiny ribbon. How will you\nhelp?$"

TrioFestival_PennySisterText:
	.string "Riko checks it first.\nBijuu waits beside her.\pPenny follows her sisters\nwith a wag.$"

TrioFestival_PennyEncourageText:
	.string "Mom speaks softly. Penny\ntakes a breath and chooses\pto try.$"

TrioFestival_PennyDemonstrateText:
	.string "Mom makes it look fun.\nPenny decides she would\plike to try that too.$"

TrioFestival_PennyWinText:
	.string "Ding! Penny finishes in\nher own time. The whole\pgarden cheers gently.\pPenny earns the Brave\nHeart Ribbon. Asking for\phelp was part of being\nbrave.$"

TrioFestival_SnackAOffer:
	.string "Aipom has your picnic\nnapkins! Pachirisu is its\plookout.\pA friendly level 27-28\nbattle for a clue?\pEveryone heals afterward.$"

TrioFestival_SnackDefeatText:
	.string "All right, all right! The\nsnacks belong to the\pgirls!$"

TrioFestival_SnackAClue:
	.string "Aipom points southeast.\nGreedent is guarding the\ppicnic basket on the lawn.$"

TrioFestival_SnackBOffer:
	.string "Greedent has the snacks!\nIt offers a friendly level\p29 match to settle snack\ncustody. Battle?$"

TrioFestival_SnackWinText:
	.string "The snacks are safe! Mom\nleaves one small treat for\pthe hungry thieves.\pPenny checks her Pup Cup.\nBijuu checks her springs.\pRiko checks EVERYTHING.$"

TrioFestival_SnackNeedScoutText:
	.string "Greedent hugs the basket.\nFind Aipom on the west\plawn to learn what\nhappened first.$"

TrioFestival_SnackRetryText:
	.string "Everyone is healed. No\nsnacks lost! Try again\pwhen you feel ready.$"

TrioFestival_ScottOffer:
	.string "You look cute with three\nfestival champions.\pOne sunset match? My team\nis level 32-33. We'll both\pheal, and the picnic\nhappens either way. Ready?$"

TrioFestival_ScottIntro:
	.string "Riko booked a concert.\nBijuu staged a crime.\pPenny stole everyone's\nhearts.\pI trained for a battle.\nApparently I should have\ptrained for babysitting.$"

TrioFestival_ScottDefeat:
	.string "I had a perfect plan. You\nhad three very good girls.$"

TrioFestival_ScottWonText:
	.string "You beat me AND rescued\nlunch. Honestly, that's\ppretty attractive.$"

TrioFestival_ScottLostText:
	.string "I won a battle. You made\nall three girls happy.\pPretty sure you won the\nday.$"

TrioFestival_PicnicText:
	.string "Scott spreads the blanket.\nRiko claims the biggest\pcorner.\pBijuu steals one napkin.\nPenny curls beside Mom and\psighs.\pThe surprise was never the\nfestival. It was a whole\pday with nowhere else to\nbe.$"

TrioFestival_LetterText:
	.string "Scott's festival letter:\pI planned a perfect day.\nThen our girls made it\pbetter.\pMy favorite part was\nwatching you love them.\pThey know how lucky they\nare.\pSo do I. Love, Scott.$"

TrioFestival_PicnicAgain:
	.string "The blanket is still here.\nScott saves your favorite\pspot.$"

TrioFestival_ScottWaitingText:
	.string "My schedule has several\npaw prints on it.\pFinish Riko's show,\nBijuu's case and Penny's\pcourse. Find the snack\nthieves too.\pThen we'll have our sunset\nmatch. No rush. This day\pis yours.$"

TrioFestival_VisitorText:
	.string "I came for a quiet walk. I\nmay have met three local\pcelebrities.$"

TrioFestival_VisitorRikoText:
	.string "Riko's show was amazing!\nShe bowed before we even\pstarted clapping.$"

TrioFestival_VisitorBijuuText:
	.string "Bijuu is our best\ndetective. Also our only\psuspect.$"

TrioFestival_VisitorPennyText:
	.string "That brave little Penny\nasked for help, then rang\pthe bell herself. What a\nsweetheart.$"

TrioFestival_RibbonsIntro:
	.string "Festival ribbon display.\nEarned ribbons are kept\phere and at Trio Camp.$"

TrioFestival_RibbonRikoText:
	.string "Big Voice Ribbon - Riko. A\nvery small girl with a\pvery large audience.$"

TrioFestival_RibbonBijuuText:
	.string "Tiny Detective Ribbon -\nBijuu. Every clue led back\pto her.$"

TrioFestival_RibbonPennyText:
	.string "Brave Heart Ribbon -\nPenny. Bravery can take\pits time.$"

TrioFestival_MemoryText:
	.string "The Girls' Day Out\pRiko performed. Bijuu\ninvestigated herself.\pPenny rang the little\nbell.\pMom rescued lunch. Scott\nsaved a place on the\pblanket.\pNobody followed the\nschedule. Everybody had\ptheir favorite day.$"

TrioFestival_ChecklistHint:
	.string "Festival memory - waiting.\nAfter four Johto Badges,\pask the guide in\nGoldenrod's Pokemon\pCenter.$"

TrioFestival_ChecklistSaved:
	.string "Festival memory - saved. A\nday out, three ribbons and\pScott's picnic letter.$"

TrioFestival_CourseDirections:
	.string "Walk to the three round\nmarkers on the east lawn.\pStart north of Penny. Then\ngo east, then south. Help\pher at each marker.\nLeaving cancels the\pcourse.$"

TrioFestival_CourseNextText:
	.string "One happy step! Walk to\nthe next round marker.\pNorth, east, then south.$"

TrioFestival_CourseCancelText:
	.string "Penny takes a little\nbreak. Ask her to start\pagain whenever you like.$"

TrioFestival_CourseIdleText:
	.string "A festival course marker.\nAsk Penny on the east lawn\pto begin.$"

TrioFestival_CourseOrderText:
	.string "Follow the course in\norder: north of Penny,\pthen east, then south.$"
