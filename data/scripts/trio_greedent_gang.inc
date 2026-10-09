@ Mandatory route ambushes. Persistent custody is recorded BEFORE battle;
@ ordinary trainer defeat/forfeit performs the engine's normal blackout.
TrioGang_OnFrame::
	map_script_2 VAR_TEMP_B, 1, TrioGang_Ambush
	map_script_2 VAR_TEMP_B, 2, TrioGang_Ambush
	map_script_2 VAR_TEMP_B, 3, TrioGang_Ambush
	map_script_2 VAR_TEMP_B, 4, TrioGang_Ambush
	map_script_2 VAR_TEMP_B, 5, TrioGang_Ambush
	map_script_2 VAR_TEMP_B, 6, TrioGang_Ambush
	map_script_2 VAR_TEMP_B, 7, TrioGang_ReclaimOnEntry
	map_script_2 VAR_TEMP_B, 8, TrioGang_FirstTheft
	.2byte 0

TrioGang_FirstTheft::
	lockall
	setvar VAR_TEMP_B, 0
	special TrioGang_BeginAmbush
	goto_if_eq VAR_RESULT, FALSE, TrioSnack_Close
	special TrioSnack_BufferItem
	playmoncry SPECIES_GREEDENT, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSnack_StolenText, MSGBOX_DEFAULT
	special TrioSnack_UpdateObjects
	removeobject 13, MAP_ROUTE37
	addobject 14, MAP_ROUTE37
	msgbox TrioSnack_GrassHintText, MSGBOX_DEFAULT
	goto TrioSnack_Close

TrioGang_FirstGate::
	goto_if_unset FLAG_BADGE03_GET, TrioSnack_End
	lockall
	setvar VAR_0x8004, 1
	setvar VAR_TEMP_B, 0
	goto TrioGang_StartBattle

TrioGang_Ambush::
	lockall
	copyvar VAR_0x8004, VAR_TEMP_B
	setvar VAR_TEMP_B, 0
TrioGang_StartBattle:
	special TrioGang_BeginAmbush
	goto_if_eq VAR_RESULT, FALSE, TrioSnack_Close
	special TrioSnack_BufferItem
	goto_if_eq VAR_0x8005, FALSE, TrioGang_Intro
	msgbox TrioGang_StolenText, MSGBOX_DEFAULT
TrioGang_Intro:
	playmoncry SPECIES_GREEDENT, CRY_MODE_NORMAL
	waitmoncry
	goto_if_eq VAR_0x8004, 1, TrioGang_Battle1
	goto_if_eq VAR_0x8004, 2, TrioGang_Battle2
	goto_if_eq VAR_0x8004, 3, TrioGang_Battle3
	goto_if_eq VAR_0x8004, 4, TrioGang_Battle4
	goto_if_eq VAR_0x8004, 5, TrioGang_Battle5
	msgbox TrioGang_Intro6, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GREEDENT_GANG_6, TrioSnack_DefeatText
	goto TrioGang_AfterBattle
TrioGang_Battle1:
	setvar VAR_TRIO_SNACK_CHASE_STATE, 2
	msgbox TrioGang_Intro1, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ROUTE37_SNACK_THIEF, TrioSnack_DefeatText
	goto TrioGang_AfterBattle
TrioGang_Battle2:
	msgbox TrioGang_Intro2, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GREEDENT_GANG_2, TrioSnack_DefeatText
	goto TrioGang_AfterBattle
TrioGang_Battle3:
	msgbox TrioGang_Intro3, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GREEDENT_GANG_3, TrioSnack_DefeatText
	goto TrioGang_AfterBattle
TrioGang_Battle4:
	msgbox TrioGang_Intro4, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GREEDENT_GANG_4, TrioSnack_DefeatText
	goto TrioGang_AfterBattle
TrioGang_Battle5:
	msgbox TrioGang_Intro5, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GREEDENT_GANG_5, TrioSnack_DefeatText
TrioGang_AfterBattle:
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioSnack_Close
	special TrioGang_RecordVictory
	call TrioGang_TryReclaim
	setflag FLAG_HIDE_TRIO_SNACK_START
	setflag FLAG_HIDE_TRIO_SNACK_GRASS
	setflag FLAG_HIDE_TRIO_SNACK_GROVE
	removeobject 13, MAP_ROUTE37
	removeobject 14, MAP_ROUTE37
	removeobject 15, MAP_ROUTE37
	goto TrioSnack_Close

TrioGang_ReclaimOnEntry::
	lockall
	setvar VAR_TEMP_B, 0
	call TrioGang_TryReclaim
	goto TrioSnack_Close
TrioGang_TryReclaim::
	goto_if_eq VAR_TRIO_SNACK_CHASE_STATE, 3, TrioGang_DoReclaim
	goto_if_ne VAR_TRIO_GANG_PHASE, 2, TrioGang_Return
TrioGang_DoReclaim:
	special TrioSnack_BufferItem
	special TrioSnack_ReturnItem
	goto_if_eq VAR_RESULT, FALSE, TrioGang_FullBag
	msgbox TrioSnack_ReturnedText, MSGBOX_DEFAULT
	goto_if_eq VAR_TRIO_GANG_WINS, 6, TrioGang_Finale
	msgbox TrioGang_NextText, MSGBOX_DEFAULT
	goto TrioGang_Return
TrioGang_Finale:
	msgbox TrioGang_MemoryText, MSGBOX_DEFAULT
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	goto TrioGang_Return
TrioGang_FullBag:
	msgbox TrioGang_FullBagText, MSGBOX_DEFAULT
TrioGang_Return:
	return

TrioGang_Checklist::
	goto_if_eq VAR_TRIO_GANG_WINS, 6, TrioGang_Saved
	msgbox TrioGang_ChecklistIntro, MSGBOX_DEFAULT
	goto_if_eq VAR_TRIO_GANG_WINS, 0, TrioGang_Hint1
	goto_if_eq VAR_TRIO_GANG_WINS, 1, TrioGang_Hint2
	goto_if_eq VAR_TRIO_GANG_WINS, 2, TrioGang_Hint3
	goto_if_eq VAR_TRIO_GANG_WINS, 3, TrioGang_Hint4
	goto_if_eq VAR_TRIO_GANG_WINS, 4, TrioGang_Hint5
	msgbox TrioGang_Hint6Text, MSGBOX_DEFAULT
	return
TrioGang_Hint1:
	msgbox TrioGang_Hint1Text, MSGBOX_DEFAULT
	return
TrioGang_Hint2:
	msgbox TrioGang_Hint2Text, MSGBOX_DEFAULT
	return
TrioGang_Hint3:
	msgbox TrioGang_Hint3Text, MSGBOX_DEFAULT
	return
TrioGang_Hint4:
	msgbox TrioGang_Hint4Text, MSGBOX_DEFAULT
	return
TrioGang_Hint5:
	msgbox TrioGang_Hint5Text, MSGBOX_DEFAULT
	return
TrioGang_Saved:
	msgbox TrioGang_SavedText, MSGBOX_DEFAULT
	return
TrioGang_ReadMemory::
	msgbox TrioGang_MemoryText, MSGBOX_DEFAULT
	return

TrioGang_StolenText:
	.string "A bushy tail snatches your\nsnack:\p{STR_VAR_1}!\pIn broad daylight. Again.$"

TrioGang_Intro1:
	.string "One Greedent blocks the\nroad.\pRiko demands the snack\nback. It demands a battle.$"

TrioGang_Intro2:
	.string "The thief brought a\nfriend.\pTwo level-35 Greedents.\nApparently this is now a\pfamily business.$"

TrioGang_Intro3:
	.string "Three level-48 Greedents\nsurround the snack.\pOne is wearing an\nimaginary manager badge.\pBijuu would like to speak\nto the manager. With\pclaws.$"

TrioGang_Intro4:
	.string "Four level-62 Greedents\ndemand a road snack tax.\pThey have no paperwork.\nThey have very large\pcheeks.\pPenny refuses to recognize\ntheir authority.$"

TrioGang_Intro5:
	.string "Five level-78 Greedents.\nOn the road to the League.\pTheir snack protection\nracket has gone regional.\pRiko is considering\norganized barking.$"

TrioGang_Intro6:
	.string "Six level-100 Greedents\nmug you in broad daylight.\pYou became Champion. They\nbecame a snack cartel.\pThey brought perfect IVs,\ntrained stats and held\pitems.\pBijuu looks offended.\nPenny looks furious. Riko\plooks hungry.\pThis is absurd. They\nattack anyway.$"

TrioGang_NextText:
	.string "The snack is back. The\ngang retreats.\pUnfortunately, they appear\nto be recruiting.$"

TrioGang_FullBagText:
	.string "You won, but your Bag\ncannot fit the snack.\pMake room, then revisit\nthis route or talk to Mom.\pNo second battle needed.$"

TrioGang_ChecklistIntro:
	.string "Every gang defeat brings\nanother hungry recruit.\pEach ambush adds another\nthief. Defeat them in\porder.$"

TrioGang_Hint1Text:
	.string "One thief: Route 37 after\nWhitney.$"

TrioGang_Hint2Text:
	.string "Two thieves: Route 38\nafter Morty.$"

TrioGang_Hint3Text:
	.string "Three thieves: Route 42\nafter Jasmine.$"

TrioGang_Hint4Text:
	.string "Four thieves: Route 44\nafter Pryce.$"

TrioGang_Hint5Text:
	.string "Five thieves: Route 26\nafter all eight Badges.$"

TrioGang_Hint6Text:
	.string "Six thieves: Route 6 in\nKanto after becoming\pChampion.$"

TrioGang_SavedText:
	.string "Snack cartel defeated!\nSaved in Sister moments.$"

TrioGang_MemoryText:
	.string "The Broad-Daylight Snack\nCartel:\pIt started with one greedy\ntail. It ended with six.\pYou defeated the entire\nsnack criminal\porganization.\pPenny guarded lunch. Bijuu\ntook statements.\pRiko ate the evidence.\pScott: That was\nridiculous. You looked\pcute doing it.$"
