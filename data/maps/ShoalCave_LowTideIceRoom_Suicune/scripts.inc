
.set LOCALID_RIKO_SPIRIT_1, 7
.set LOCALID_RIKO_SPIRIT_2, 8

ShoalCave_LowTideIceRoom_Suicune_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ShoalCave_LowTideIceRoom_Suicune_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

ShoalCave_LowTideIceRoom_Suicune_OnTransition::
	callnative SetTimeBasedEncounters
	end

@@Trigger at the start

ShoalCave_LowTideIceRoom_Suicune_EntranceTrigger::
	lock
	playmoncry SPECIES_RIKO_SPIRIT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_SUICUNE_EVENT, 1
	applymovement OBJ_EVENT_ID_PLAYER, ShoalCave_LowTideIceRoom_Suicune_EntranceTriggerMovement
	waitmovement 0
	msgbox ShoalCave_LowTideIceRoom_Suicune_EntranceTrigger_Text, MSGBOX_DEFAULT
	waitmessage
	release
	end

ShoalCave_LowTideIceRoom_Suicune_EntranceTrigger_Text:
	.string "A three-headed howl echoes\n"
	.string "through Shoal Cave.\p"
	.string "A warm, protective presence\n"
	.string "stirs deeper within...$"

ShoalCave_LowTideIceRoom_Suicune_EntranceTriggerMovement:
	face_right
	delay_16
	emote_question_mark
	step_end

@@First encounter with the Spirit of Riko. Level 90, cannot be caught

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle1::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_RIKO_SPIRIT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_RIKO_SPIRIT, 90
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_RG_VS_LEGEND
	call_if_set FLAG_GARBAGEFLAG, ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle1_Stats
	dowildbattle
	clearflag FLAG_GARBAGEFLAG
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle1_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ShoalCave_LowTideIceRoom_Suicune_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ShoalCave_LowTideIceRoom_Suicune_Ran
	releaseall
	end

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle1_Stats::
	setvar VAR_0x8002, 450 @DEF
	setvar VAR_0x8006, 450 @SP. DEF
	@@special SetDefStat
	@special SetSpDefStat
	return

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle1_Won::
	applymovement LOCALID_RIKO_SPIRIT_1, ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle1_Movement
	waitmovement 0
	msgbox ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle1_Text, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SUICUNE_BATTLE_1
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle1_Movement:
	face_down
	delay_16
	walk_fast_down
	walk_fast_down
	jump_2_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	step_end

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle1_Text:
	.string "The Spirit of Riko leaps back,\n"
	.string "shielding the cave with all\n"
	.string "three heads. It vanishes into\n"
	.string "the mist!$"

@@Second encounter with the Spirit of Riko. Level 80, cannot be caught

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle2::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_RIKO_SPIRIT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_RIKO_SPIRIT, 80
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_C_VS_LEGEND_BEAST
	call_if_set FLAG_GARBAGEFLAG, ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle2_Stats
	dowildbattle
	clearflag FLAG_GARBAGEFLAG
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle2_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ShoalCave_LowTideIceRoom_Suicune_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ShoalCave_LowTideIceRoom_Suicune_Ran
	releaseall
	end

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle2_Stats::
	setvar VAR_0x8002, 550 @DEF
	setvar VAR_0x8006, 550 @SP. DEF
	@@special SetDefStat
	@special SetSpDefStat
	return

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle2_Won::
	applymovement LOCALID_RIKO_SPIRIT_2, ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle2_Movement
	waitmovement 0
	msgbox ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle2_Text, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SUICUNE_BATTLE_2
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle2_Movement:
	face_up
	delay_16
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	step_end

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle2_Text:
	.string "The Spirit of Riko circles you,\n"
	.string "then fades from sight again!$"

@@Final encounter with the Spirit of Riko. Level 70, catchable

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritFinalBattle::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_RIKO_SPIRIT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox ShoalCave_LowTideIceRoom_Suicune_RikoSpiritFinalBattle_Text, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_RIKO_SPIRIT, 70, ITEM_CHARCOAL
	setflag FLAG_GARBAGEFLAG
	call_if_set FLAG_GARBAGEFLAG, ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle3_Stats
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_GARBAGEFLAG
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, ShoalCave_LowTideIceRoom_Suicune_RikoSpiritFinalBattle_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, ShoalCave_LowTideIceRoom_Suicune_RikoSpiritFinalBattle_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ShoalCave_LowTideIceRoom_Suicune_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ShoalCave_LowTideIceRoom_Suicune_Ran
	releaseall
	end

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritBattle3_Stats::
	setvar VAR_0x8002, 700 @DEF
	setvar VAR_0x8006, 700 @SP. DEF
	@@special SetDefStat
	@special SetSpDefStat
	return

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritFinalBattle_Text:
	.string "The Spirit of Riko stands its\n"
	.string "ground. Its three heads lower.\p"
	.string "The guardian challenge is over.\p"
	.string "Will it join your family?$"

ShoalCave_LowTideIceRoom_Suicune_RikoSpiritFinalBattle_Won::
	setflag FLAG_DEFEATED_SUICUNE
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

ShoalCave_LowTideIceRoom_Suicune_Ran::
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_SYS_NO_CATCHING
	releaseall
	end
