@ Temporary mailbox triggers share battle setup with the real Spirit cave.

TrioSpiritTrials_StartRiko1::
	waitse
	playmoncry SPECIES_RIKO_SPIRIT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_RIKO_SPIRIT, 90
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_RG_VS_LEGEND
	call ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle1_Stats
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	clearflag FLAG_SYS_NO_CATCHING
	return

TrioSpiritTrials_StartRiko2::
	waitse
	playmoncry SPECIES_RIKO_SPIRIT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_RIKO_SPIRIT, 80
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_C_VS_LEGEND_BEAST
	call ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle2_Stats
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	clearflag FLAG_SYS_NO_CATCHING
	return

TrioSpiritTrials_StartFinal::
	waitse
	playmoncry SPECIES_RIKO_SPIRIT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox ShoalCave_LowTideIceRoom_Suicune_RikoSpiritFinalBattle_Text, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_RIKO_SPIRIT, 70, ITEM_CHARCOAL
	call ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle3_Stats
	special BattleSetup_StartLegendaryBattle
	waitstate
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	return

TrioSpiritTrials_PlayersMailbox::
	lockall
	goto_if_set FLAG_SUICUNE_BATTLE_1, TrioSpiritTrials_AlreadyComplete
	msgbox TrioSpiritTrials_PlayersMailbox_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TrioSpiritTrials_PlayersMailbox_Begin
	goto TrioSpiritTrials_Finish

TrioSpiritTrials_PlayersMailbox_Begin::
	closemessage
	call TrioSpiritTrials_StartRiko1
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, TrioSpiritTrials_PlayersMailbox_Complete
	goto TrioSpiritTrials_Finish

TrioSpiritTrials_PlayersMailbox_Complete::
	setflag FLAG_SUICUNE_BATTLE_1
	msgbox TrioSpiritTrials_Complete_Text, MSGBOX_DEFAULT
	goto TrioSpiritTrials_Finish

TrioSpiritTrials_PlayersMailbox_Text:
	.string "Spirit trial one. Level 90.\n"
	.string "This spirit cannot be caught.\p"
	.string "Test wins change cave progress.\n"
	.string "Begin the test?$"

TrioSpiritTrials_ElmMailbox::
	lockall
	goto_if_set FLAG_SUICUNE_BATTLE_2, TrioSpiritTrials_AlreadyComplete
	msgbox TrioSpiritTrials_ElmMailbox_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TrioSpiritTrials_ElmMailbox_Begin
	goto TrioSpiritTrials_Finish

TrioSpiritTrials_ElmMailbox_Begin::
	closemessage
	call TrioSpiritTrials_StartRiko2
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, TrioSpiritTrials_ElmMailbox_Complete
	goto TrioSpiritTrials_Finish

TrioSpiritTrials_ElmMailbox_Complete::
	setflag FLAG_SUICUNE_BATTLE_2
	msgbox TrioSpiritTrials_Complete_Text, MSGBOX_DEFAULT
	goto TrioSpiritTrials_Finish

TrioSpiritTrials_ElmMailbox_Text:
	.string "Spirit trial two. Level 80.\n"
	.string "This spirit cannot be caught.\p"
	.string "Test wins change cave progress.\n"
	.string "Begin the test?$"

TrioSpiritTrials_RivalsMailbox::
	lockall
	goto_if_set FLAG_DEFEATED_SUICUNE, TrioSpiritTrials_AlreadyComplete
	msgbox TrioSpiritTrials_RivalsMailbox_Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TrioSpiritTrials_RivalsMailbox_Begin
	goto TrioSpiritTrials_Finish

TrioSpiritTrials_RivalsMailbox_Begin::
	closemessage
	call TrioSpiritTrials_StartFinal
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, TrioSpiritTrials_RivalsMailbox_Complete
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, TrioSpiritTrials_RivalsMailbox_Complete
	goto TrioSpiritTrials_Finish

TrioSpiritTrials_RivalsMailbox_Complete::
	setflag FLAG_DEFEATED_SUICUNE
	msgbox TrioSpiritTrials_Complete_Text, MSGBOX_DEFAULT
	goto TrioSpiritTrials_Finish

TrioSpiritTrials_RivalsMailbox_Text:
	.string "Final spirit trial. Level 70.\n"
	.string "This spirit can be caught.\p"
	.string "Wins or catches complete it.\n"
	.string "Begin the test?$"

TrioSpiritTrials_AlreadyComplete::
	msgbox TrioSpiritTrials_AlreadyComplete_Text, MSGBOX_DEFAULT
	goto TrioSpiritTrials_Finish

TrioSpiritTrials_Finish::
	clearflag FLAG_SYS_NO_CATCHING
	clearflag FLAG_SYS_SET_BATTLE_BGM
	closemessage
	releaseall
	end

TrioSpiritTrials_Complete_Text:
	.string "Spirit trial complete!\n"
	.string "Cave progress was updated.$"

TrioSpiritTrials_AlreadyComplete_Text:
	.string "This spirit trial is complete.\n"
	.string "The guardian remembers you.$"

@ Repeatable test-save restock: keep one of each form item in the Items pocket.
TrioTestItems_Restock::
	checkitem ITEM_RIKOS_WAND
	goto_if_eq VAR_RESULT, TRUE, TrioTestItems_CheckBrush
	giveitem ITEM_RIKOS_WAND
	goto_if_eq VAR_RESULT, FALSE, TrioTestItems_BagFull
TrioTestItems_CheckBrush::
	checkitem ITEM_BLUE_BRUSH
	goto_if_eq VAR_RESULT, TRUE, TrioTestItems_Done
	giveitem ITEM_BLUE_BRUSH
	goto_if_eq VAR_RESULT, FALSE, TrioTestItems_BagFull
TrioTestItems_Done::
	msgbox TrioTestItems_Ready_Text, MSGBOX_DEFAULT
	return

TrioTestItems_BagFull::
	msgbox TrioTestItems_BagFull_Text, MSGBOX_DEFAULT
	return

TrioTestItems_Ready_Text:
	.string "Your Riko form items are ready.\n"
	.string "Check the Bag's Items pocket.\p"
	.string "Wand: Riko becomes RikoWing.\n"
	.string "Brush: RikoWing becomes Riko.$"

TrioTestItems_BagFull_Text:
	.string "Your Bag has no room.\n"
	.string "Make space, then speak to me.$"
