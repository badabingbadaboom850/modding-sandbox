@ These local copies avoid cross-map references in shared battle setup.
TrioSpiritTrials_Riko1Stats::
	setvar VAR_0x8002, 450 @DEF
	setvar VAR_0x8006, 450 @SP. DEF
	@@special SetDefStat
	@special SetSpDefStat
	return

TrioSpiritTrials_Riko2Stats::
	setvar VAR_0x8002, 550 @DEF
	setvar VAR_0x8006, 550 @SP. DEF
	@@special SetDefStat
	@special SetSpDefStat
	return

TrioSpiritTrials_FinalStats::
	setvar VAR_0x8002, 700 @DEF
	setvar VAR_0x8006, 700 @SP. DEF
	@@special SetDefStat
	@special SetSpDefStat
	return

TrioSpiritTrials_FinalIntro_Text:
	.string "The Spirit of Riko stands its\n"
	.string "ground. Its three heads lower.\p"
	.string "The guardian challenge is over.\p"
	.string "Will it join your family?$"

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
	call TrioSpiritTrials_Riko1Stats
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
	call TrioSpiritTrials_Riko2Stats
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	clearflag FLAG_SYS_NO_CATCHING
	return

TrioSpiritTrials_StartFinal::
	waitse
	playmoncry SPECIES_RIKO_SPIRIT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox TrioSpiritTrials_FinalIntro_Text, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_RIKO_SPIRIT, 70, ITEM_CHARCOAL
	call TrioSpiritTrials_FinalStats
	special BattleSetup_StartLegendaryBattle
	waitstate
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	return
