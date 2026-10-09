@ Milestone-gated story arenas. Home trials remain independent test encounters.
@ Refresh visibility before map objects spawn, including on existing saves.
TrioStorySpirit_PennyVisibility::
	setvar VAR_0x8004, SPECIES_PENNY_SPIRIT
	specialvar VAR_RESULT, CheckTrioSpiritMilestone
	goto_if_eq VAR_RESULT, FALSE, TrioStorySpirit_PennyHide
	clearflag FLAG_HIDE_TRIO_PENNY_SPIRIT
	return
TrioStorySpirit_PennyHide:
	setflag FLAG_HIDE_TRIO_PENNY_SPIRIT
	return

TrioStorySpirit_PennyEncounter::
	lock
	faceplayer
	setvar VAR_0x8004, SPECIES_PENNY_SPIRIT
	specialvar VAR_RESULT, CheckTrioSpiritMilestone
	goto_if_eq VAR_RESULT, FALSE, TrioStorySpirit_NotReady
	goto_if_set FLAG_TRIO_PENNY_SPIRIT_COMPLETE, TrioStorySpirit_PennyRemember
	msgbox TrioStorySpirit_PennyOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioHomeSpirit_Decline
	setvar VAR_0x8004, SPECIES_PENNY_SPIRIT
	specialvar VAR_RESULT, PrepareTrioSpiritTrial
	goto_if_eq VAR_RESULT, FALSE, TrioHomeSpirit_NoParty
	msgbox TrioHomeSpirit_Ready, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_PENNY_SPIRIT, CRY_MODE_ENCOUNTER
	waitmoncry
	special BattleSetup_StartTrioSpiritTrial
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioHomeSpirit_Retry
	setflag FLAG_TRIO_PENNY_SPIRIT_COMPLETE
TrioStorySpirit_PennyRemember:
	msgbox TrioHomeSpirit_PennyVictory, MSGBOX_DEFAULT
	release
	end

TrioStorySpirit_BijuuVisibility::
	setvar VAR_0x8004, SPECIES_BIJUU_SPIRIT
	specialvar VAR_RESULT, CheckTrioSpiritMilestone
	goto_if_eq VAR_RESULT, FALSE, TrioStorySpirit_BijuuHide
	clearflag FLAG_HIDE_TRIO_BIJUU_SPIRIT
	return
TrioStorySpirit_BijuuHide:
	setflag FLAG_HIDE_TRIO_BIJUU_SPIRIT
	return

TrioStorySpirit_BijuuEncounter::
	lock
	faceplayer
	setvar VAR_0x8004, SPECIES_BIJUU_SPIRIT
	specialvar VAR_RESULT, CheckTrioSpiritMilestone
	goto_if_eq VAR_RESULT, FALSE, TrioStorySpirit_NotReady
	goto_if_set FLAG_TRIO_BIJUU_SPIRIT_COMPLETE, TrioStorySpirit_BijuuRemember
	msgbox TrioStorySpirit_BijuuOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioHomeSpirit_Decline
	setvar VAR_0x8004, SPECIES_BIJUU_SPIRIT
	specialvar VAR_RESULT, PrepareTrioSpiritTrial
	goto_if_eq VAR_RESULT, FALSE, TrioHomeSpirit_NoParty
	msgbox TrioHomeSpirit_Ready, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_BIJUU_SPIRIT, CRY_MODE_ENCOUNTER
	waitmoncry
	special BattleSetup_StartTrioSpiritTrial
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioHomeSpirit_Retry
	setflag FLAG_TRIO_BIJUU_SPIRIT_COMPLETE
TrioStorySpirit_BijuuRemember:
	msgbox TrioHomeSpirit_BijuuVictory, MSGBOX_DEFAULT
	release
	end

TrioStorySpirit_NotReady:
	msgbox TrioStorySpirit_NotReadyText, MSGBOX_DEFAULT
	release
	end

@ Existing permanent neighbor in New Bark. Both pending clues can be reread.
TrioStorySpirit_Rumors::
	goto_if_set FLAG_TRIO_PENNY_SPIRIT_COMPLETE, TrioStorySpirit_BijuuRumor
	setvar VAR_0x8004, SPECIES_PENNY_SPIRIT
	specialvar VAR_RESULT, CheckTrioSpiritMilestone
	call_if_eq VAR_RESULT, TRUE, TrioStorySpirit_PennyRumor
TrioStorySpirit_BijuuRumor:
	goto_if_set FLAG_TRIO_BIJUU_SPIRIT_COMPLETE, TrioStorySpirit_RumorsEnd
	setvar VAR_0x8004, SPECIES_BIJUU_SPIRIT
	specialvar VAR_RESULT, CheckTrioSpiritMilestone
	call_if_eq VAR_RESULT, TRUE, TrioStorySpirit_BijuuRumorText
TrioStorySpirit_RumorsEnd:
	return
TrioStorySpirit_PennyRumor:
	msgbox TrioStorySpirit_PennyClue, MSGBOX_DEFAULT
	return
TrioStorySpirit_BijuuRumorText:
	msgbox TrioStorySpirit_BijuuClue, MSGBOX_DEFAULT
	return

TrioStorySpirit_PennySightingCallText:
	.string "Neighbor: Hi, {PLAYER}!\p"
TrioStorySpirit_PennyClue:
	.string "Eight Johto Badges!\n"
	.string "Your girls must be proud.\p"
	.string "I heard Penny was spotted\n"
	.string "in Blackthorn City.\p"
	.string "But she's right here?\n"
	.string "You should investigate!\p"
	.string "They saw shining armor\n"
	.string "north of the Poke Center.$"

TrioStorySpirit_BijuuSightingCallText:
	.string "Neighbor: Hi, {PLAYER}!\p"
TrioStorySpirit_BijuuClue:
	.string "Our very own Champion!\n"
	.string "And now another mystery...\p"
	.string "Someone saw Bijuu in\n"
	.string "Ecruteak City.\p"
	.string "Two tails. Blue flames.\n"
	.string "But she's beside you?\p"
	.string "Look near Burned Tower,\n"
	.string "just east of its entrance.$"

TrioStorySpirit_PennyOffer:
	.string "Penny looks at the armor.\n"
	.string "The spirit looks at Mom.\p"
	.string "Not a stranger. A glimpse\n"
	.string "of who love helped her be.\p"
	.string "Will you face her\n"
	.string "guardian spirit?$"

TrioStorySpirit_BijuuOffer:
	.string "Bijuu watches the flames.\n"
	.string "Both tilt their heads.\p"
	.string "The same little cocoa.\n"
	.string "A love too big to hide.\p"
	.string "Will you face her\n"
	.string "shining spirit?$"

TrioStorySpirit_NotReadyText:
	.string "Her light is still quiet.\n"
	.string "Keep growing together.$"

@ VAR_TEMP_9 is a map-local dispatch latch, recomputed on every entry to
@ Blackthorn / New Bark. Original Elm and rival on-frame scripts take priority.
TrioStorySpirit_PreparePennySighting::
	setvar VAR_TEMP_9, FALSE
	goto_if_set FLAG_TRIO_PENNY_SPIRIT_COMPLETE, TrioStorySpirit_SightingPrepareEnd
	goto_if_set FLAG_TRIO_PENNY_SIGHTING_SHOWN, TrioStorySpirit_SightingPrepareEnd
	setvar VAR_0x8004, SPECIES_PENNY_SPIRIT
	specialvar VAR_RESULT, CheckTrioSpiritMilestone
	goto_if_eq VAR_RESULT, FALSE, TrioStorySpirit_SightingPrepareEnd
	setvar VAR_TEMP_9, TRUE
	return

TrioStorySpirit_PennySightingCall::
	lockall
	setvar VAR_TEMP_9, FALSE
	pokenavcall TrioStorySpirit_PennySightingCallText
	waitmessage
	delay 30
	setflag FLAG_TRIO_PENNY_SIGHTING_SHOWN
	releaseall
	end

TrioStorySpirit_PrepareBijuuSighting::
	setvar VAR_TEMP_9, FALSE
	goto_if_set FLAG_TRIO_BIJUU_SPIRIT_COMPLETE, TrioStorySpirit_SightingPrepareEnd
	goto_if_set FLAG_TRIO_BIJUU_SIGHTING_SHOWN, TrioStorySpirit_SightingPrepareEnd
	setvar VAR_0x8004, SPECIES_BIJUU_SPIRIT
	specialvar VAR_RESULT, CheckTrioSpiritMilestone
	goto_if_eq VAR_RESULT, FALSE, TrioStorySpirit_SightingPrepareEnd
	setvar VAR_TEMP_9, TRUE
	return

TrioStorySpirit_BijuuSightingCall::
	lockall
	setvar VAR_TEMP_9, FALSE
	pokenavcall TrioStorySpirit_BijuuSightingCallText
	waitmessage
	delay 30
	setflag FLAG_TRIO_BIJUU_SIGHTING_SHOWN
	releaseall
	end

TrioStorySpirit_SightingPrepareEnd:
	return
