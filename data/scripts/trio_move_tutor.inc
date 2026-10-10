@ Free repeatable family tutor. New Bark placement is the authorized test encounter.
TrioMoveTutor_Scott::
	lock
	faceplayer
	msgbox TrioMoveTutor_Intro, MSGBOX_DEFAULT
TrioMoveTutor_ChooseService:
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, TrioMoveTutor_SignatureName, TrioMoveTutor_ElementalName, TrioMoveTutor_ExitName
	goto_if_eq VAR_RESULT, 0, TrioMoveTutor_ChooseGirl
	goto_if_eq VAR_RESULT, 1, TrioMoveTutor_Elemental
	goto TrioMoveTutor_End
TrioMoveTutor_Elemental:
	msgbox TrioMoveTutor_ElementalIntro, MSGBOX_DEFAULT
	special BeginTrioElementalLessons
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, TrioMoveTutor_ElementalDone
	special HasMovesToRelearn
	goto_if_eq VAR_RESULT, FALSE, TrioMoveTutor_ElementalNone
	special TeachMoveRelearnerMove
	waitstate
	goto TrioMoveTutor_ElementalDone
TrioMoveTutor_ElementalNone:
	msgbox TrioMoveTutor_ElementalNoMoves, MSGBOX_DEFAULT
TrioMoveTutor_ElementalDone:
	special EndTrioElementalLessons
	goto TrioMoveTutor_ChooseService
TrioMoveTutor_ChooseGirl:
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrioMoveTutor_RikoName, TrioMoveTutor_PennyName, TrioMoveTutor_BijuuName, TrioMoveTutor_ExitName
	goto_if_eq VAR_RESULT, 0, TrioMoveTutor_Riko
	goto_if_eq VAR_RESULT, 1, TrioMoveTutor_Penny
	goto_if_eq VAR_RESULT, 2, TrioMoveTutor_Bijuu
	goto_if_eq VAR_RESULT, 127, TrioMoveTutor_ChooseService
	goto TrioMoveTutor_End
TrioMoveTutor_Riko:
	msgbox TrioMoveTutor_RikoIntro, MSGBOX_DEFAULT
TrioMoveTutor_RikoMenu:
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, TrioMoveTutor_Name_POM_TANTRUM, TrioMoveTutor_Name_EXCUSE_YOU, TrioMoveTutor_Name_SIDE_EYE, TrioMoveTutor_Name_MAIN_CHARACTER, TrioMoveTutor_Name_LAST_WORD, TrioMoveTutor_Name_DRAMA_QUEEN, TrioMoveTutor_Name_FLOOF_FURY, TrioMoveTutor_Name_MEGA_RIKO, TrioMoveTutor_BackName
	goto_if_eq VAR_RESULT, 0, TrioMoveTutor_Lesson_POM_TANTRUM
	goto_if_eq VAR_RESULT, 1, TrioMoveTutor_Lesson_EXCUSE_YOU
	goto_if_eq VAR_RESULT, 2, TrioMoveTutor_Lesson_SIDE_EYE
	goto_if_eq VAR_RESULT, 3, TrioMoveTutor_Lesson_MAIN_CHARACTER
	goto_if_eq VAR_RESULT, 4, TrioMoveTutor_Lesson_LAST_WORD
	goto_if_eq VAR_RESULT, 5, TrioMoveTutor_Lesson_DRAMA_QUEEN
	goto_if_eq VAR_RESULT, 6, TrioMoveTutor_Lesson_FLOOF_FURY
	goto_if_eq VAR_RESULT, 7, TrioMoveTutor_Lesson_MEGA_RIKO
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Penny:
	msgbox TrioMoveTutor_PennyIntro, MSGBOX_DEFAULT
TrioMoveTutor_PennyMenu:
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, TrioMoveTutor_Name_BLANKEY_TIME, TrioMoveTutor_Name_GOOD_GIRL_GUARD, TrioMoveTutor_Name_PENNY_PATIENCE, TrioMoveTutor_Name_TINY_NIBBLES, TrioMoveTutor_Name_LONG_GAME, TrioMoveTutor_Name_SAFE_WITH_YOU, TrioMoveTutor_BackName
	goto_if_eq VAR_RESULT, 0, TrioMoveTutor_Lesson_BLANKEY_TIME
	goto_if_eq VAR_RESULT, 1, TrioMoveTutor_Lesson_GOOD_GIRL_GUARD
	goto_if_eq VAR_RESULT, 2, TrioMoveTutor_Lesson_PENNY_PATIENCE
	goto_if_eq VAR_RESULT, 3, TrioMoveTutor_Lesson_TINY_NIBBLES
	goto_if_eq VAR_RESULT, 4, TrioMoveTutor_Lesson_LONG_GAME
	goto_if_eq VAR_RESULT, 5, TrioMoveTutor_Lesson_SAFE_WITH_YOU
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Bijuu:
	msgbox TrioMoveTutor_BijuuIntro, MSGBOX_DEFAULT
TrioMoveTutor_BijuuMenu:
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, TrioMoveTutor_Name_COCOA_POUNCE, TrioMoveTutor_Name_BACKYARD_BLITZ, TrioMoveTutor_Name_MIDNIGHT_ZOOM, TrioMoveTutor_Name_CLAW_ENFORCEMENT, TrioMoveTutor_Name_COCOA_CHAOS, TrioMoveTutor_Name_ABSOLUTELY_FERAL, TrioMoveTutor_BackName
	goto_if_eq VAR_RESULT, 0, TrioMoveTutor_Lesson_COCOA_POUNCE
	goto_if_eq VAR_RESULT, 1, TrioMoveTutor_Lesson_BACKYARD_BLITZ
	goto_if_eq VAR_RESULT, 2, TrioMoveTutor_Lesson_MIDNIGHT_ZOOM
	goto_if_eq VAR_RESULT, 3, TrioMoveTutor_Lesson_CLAW_ENFORCEMENT
	goto_if_eq VAR_RESULT, 4, TrioMoveTutor_Lesson_COCOA_CHAOS
	goto_if_eq VAR_RESULT, 5, TrioMoveTutor_Lesson_ABSOLUTELY_FERAL
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_BLANKEY_TIME:
	msgbox TrioMoveTutor_Desc_BLANKEY_TIME, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_BLANKEY_TIME
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_GOOD_GIRL_GUARD:
	msgbox TrioMoveTutor_Desc_GOOD_GIRL_GUARD, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_GOOD_GIRL_GUARD
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_PENNY_PATIENCE:
	msgbox TrioMoveTutor_Desc_PENNY_PATIENCE, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_PENNY_PATIENCE
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_TINY_NIBBLES:
	msgbox TrioMoveTutor_Desc_TINY_NIBBLES, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_TINY_NIBBLES
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_LONG_GAME:
	msgbox TrioMoveTutor_Desc_LONG_GAME, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_LONG_GAME
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_SAFE_WITH_YOU:
	msgbox TrioMoveTutor_Desc_SAFE_WITH_YOU, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_SAFE_WITH_YOU
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_COCOA_POUNCE:
	msgbox TrioMoveTutor_Desc_COCOA_POUNCE, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_COCOA_POUNCE
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_BACKYARD_BLITZ:
	msgbox TrioMoveTutor_Desc_BACKYARD_BLITZ, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_BACKYARD_BLITZ
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_MIDNIGHT_ZOOM:
	msgbox TrioMoveTutor_Desc_MIDNIGHT_ZOOM, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_MIDNIGHT_ZOOM
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_CLAW_ENFORCEMENT:
	msgbox TrioMoveTutor_Desc_CLAW_ENFORCEMENT, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_CLAW_ENFORCEMENT
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_COCOA_CHAOS:
	msgbox TrioMoveTutor_Desc_COCOA_CHAOS, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_COCOA_CHAOS
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_ABSOLUTELY_FERAL:
	msgbox TrioMoveTutor_Desc_ABSOLUTELY_FERAL, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_ABSOLUTELY_FERAL
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_POM_TANTRUM:
	msgbox TrioMoveTutor_Desc_POM_TANTRUM, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_POM_TANTRUM
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_EXCUSE_YOU:
	msgbox TrioMoveTutor_Desc_EXCUSE_YOU, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_EXCUSE_YOU
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_SIDE_EYE:
	msgbox TrioMoveTutor_Desc_SIDE_EYE, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_SIDE_EYE
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_MAIN_CHARACTER:
	msgbox TrioMoveTutor_Desc_MAIN_CHARACTER, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_MAIN_CHARACTER
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_LAST_WORD:
	msgbox TrioMoveTutor_Desc_LAST_WORD, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_LAST_WORD
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_DRAMA_QUEEN:
	msgbox TrioMoveTutor_Desc_DRAMA_QUEEN, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_DRAMA_QUEEN
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_FLOOF_FURY:
	msgbox TrioMoveTutor_Desc_FLOOF_FURY, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_FLOOF_FURY
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_Lesson_MEGA_RIKO:
	msgbox TrioMoveTutor_Desc_MEGA_RIKO, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMoveTutor_ChooseGirl
	setvar VAR_0x8005, MOVE_MEGA_RIKO
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	msgbox TrioMoveTutor_Again, MSGBOX_DEFAULT
	goto TrioMoveTutor_ChooseGirl
TrioMoveTutor_End:
	msgbox TrioMoveTutor_Bye, MSGBOX_DEFAULT
	release
	end
TrioMoveTutor_Intro:
	.string "Hey, gorgeous!\nPrivate lessons? For you?\pAlways free. Pick a girl,\nthen her next little\ptrick.$"
TrioMoveTutor_RikoName:
	.string "Riko$"
TrioMoveTutor_PennyName:
	.string "Penny$"
TrioMoveTutor_BijuuName:
	.string "Bijuu$"
TrioMoveTutor_ExitName:
	.string "All done$"
TrioMoveTutor_BackName:
	.string "Back$"
TrioMoveTutor_RikoIntro:
	.string "Riko has opinions.\nLet's make them dangerous.$"
TrioMoveTutor_PennyIntro:
	.string "My favorite student!\nPenny wins at her own\ppace.$"
TrioMoveTutor_BijuuIntro:
	.string "Bijuu heard 'go faster.'\nShe was already gone.$"
TrioMoveTutor_Again:
	.string "Another lesson, cutie?\nWe can try any of these.$"
TrioMoveTutor_Bye:
	.string "Go make me proud, girls.\nYou already do, gorgeous.$"
TrioMoveTutor_Name_BLANKEY_TIME:
	.string "Blankey Time$"
TrioMoveTutor_Desc_BLANKEY_TIME:
	.string "Restores half the user's\nHP.\pStatus move\n5 PP. Teach this move?$"
TrioMoveTutor_Name_GOOD_GIRL_GUARD:
	.string "Good Girl Guard$"
TrioMoveTutor_Desc_GOOD_GIRL_GUARD:
	.string "Protects for a turn.\nRepeated use may fail.\pStatus move\n10 PP. Teach this move?$"
TrioMoveTutor_Name_PENNY_PATIENCE:
	.string "Penny Patience$"
TrioMoveTutor_Desc_PENNY_PATIENCE:
	.string "Raises Defense and\nSp. Def by one stage.\pStatus move\n15 PP. Teach this move?$"
TrioMoveTutor_Name_TINY_NIBBLES:
	.string "Tiny Nibbles$"
TrioMoveTutor_Desc_TINY_NIBBLES:
	.string "Little bites restore HP\nequal to half the damage.\p60 power / 100% hit\n15 PP. Teach this move?$"
TrioMoveTutor_Name_LONG_GAME:
	.string "Long Game$"
TrioMoveTutor_Desc_LONG_GAME:
	.string "Traps and chips away at\nthe foe for several turns.\p35 power / 100% hit\n15 PP. Teach this move?$"
TrioMoveTutor_Name_SAFE_WITH_YOU:
	.string "Safe With You$"
TrioMoveTutor_Desc_SAFE_WITH_YOU:
	.string "Cures the user's status\nand raises Sp. Def.\pStatus move\n10 PP. Teach this move?$"
TrioMoveTutor_Name_COCOA_POUNCE:
	.string "Cocoa Pounce$"
TrioMoveTutor_Desc_COCOA_POUNCE:
	.string "Pounces on the foe and\nlowers its Attack.\p75 power / 100% hit\n15 PP. Teach this move?$"
TrioMoveTutor_Name_BACKYARD_BLITZ:
	.string "Backyard Blitz$"
TrioMoveTutor_Desc_BACKYARD_BLITZ:
	.string "A backyard dash that\nstrikes with priority.\p40 power / 100% hit\n20 PP. Teach this move?$"
TrioMoveTutor_Name_MIDNIGHT_ZOOM:
	.string "Midnight Zoom$"
TrioMoveTutor_Desc_MIDNIGHT_ZOOM:
	.string "Attacks, then switches\nwith another party member.\p70 power / 100% hit\n15 PP. Teach this move?$"
TrioMoveTutor_Name_CLAW_ENFORCEMENT:
	.string "Claw Enforcement$"
TrioMoveTutor_Desc_CLAW_ENFORCEMENT:
	.string "Breaks protective screens\nbefore striking the foe.\p85 power / 100% hit\n10 PP. Teach this move?$"
TrioMoveTutor_Name_COCOA_CHAOS:
	.string "Cocoa Chaos$"
TrioMoveTutor_Desc_COCOA_CHAOS:
	.string "Raises Attack and Speed\nby one stage.\pStatus move\n15 PP. Teach this move?$"
TrioMoveTutor_Name_ABSOLUTELY_FERAL:
	.string "Absolutely Feral$"
TrioMoveTutor_Desc_ABSOLUTELY_FERAL:
	.string "A wild attack with recoil\nof one-third the damage.\p120 power / 100% hit\n10 PP. Teach this move?$"
TrioMoveTutor_Name_POM_TANTRUM:
	.string "Pom Tantrum$"
TrioMoveTutor_Desc_POM_TANTRUM:
	.string "A dramatic blast that may\nlower the foe's Sp. Def.\p80 power / 100% hit\n15 PP. Teach this move?$"
TrioMoveTutor_Name_EXCUSE_YOU:
	.string "Excuse You$"
TrioMoveTutor_Desc_EXCUSE_YOU:
	.string "Hits twice as hard if hurt\nby the target this turn.\p60 power / 100% hit\n10 PP. Teach this move?$"
TrioMoveTutor_Name_SIDE_EYE:
	.string "Side Eye$"
TrioMoveTutor_Desc_SIDE_EYE:
	.string "Lowers the foe's Attack\nand Sp. Atk by one stage.\pStatus move\n15 PP. Teach this move?$"
TrioMoveTutor_Name_MAIN_CHARACTER:
	.string "Main Character$"
TrioMoveTutor_Desc_MAIN_CHARACTER:
	.string "Raises Sp. Atk and Sp. Def\nby one stage.\pStatus move\n15 PP. Teach this move?$"
TrioMoveTutor_Name_LAST_WORD:
	.string "Last Word$"
TrioMoveTutor_Desc_LAST_WORD:
	.string "A sharp comeback that\nstrikes with priority.\p40 power / 100% hit\n20 PP. Teach this move?$"
TrioMoveTutor_Name_DRAMA_QUEEN:
	.string "Drama Queen$"
TrioMoveTutor_Desc_DRAMA_QUEEN:
	.string "A huge blast that lowers\nthe user's Sp. Atk by two.\p130 power / 90% hit\n5 PP. Teach this move?$"
TrioMoveTutor_Name_FLOOF_FURY:
	.string "Floof Fury$"
TrioMoveTutor_Desc_FLOOF_FURY:
	.string "Fairy blast: 100 power.\nMay lower the foe's Speed.\p100% accuracy / 10 PP.\nTeach this move?$"
TrioMoveTutor_Name_MEGA_RIKO:
	.string "Pom Supremacy$"
TrioMoveTutor_Desc_MEGA_RIKO:
	.string "Raises Sp. Atk, Sp. Def\nand Speed by one stage.\pStatus move / 5 PP.\nTeach this move?$"

TrioMoveTutor_SignatureName:
	.string "Signature moves$"
TrioMoveTutor_ElementalName:
	.string "Elemental moves$"
TrioMoveTutor_ElementalIntro:
	.string "Pick a girl! Her current\nform sets these lessons.\pMoves unlock with levels.\nAlready known ones hide.$"
TrioMoveTutor_ElementalNoMoves:
	.string "No new elemental attacks\nfor this form and level.\pTry changing her form or\nleveling up, cutie!$"
