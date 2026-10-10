






@ Independent first Rift chapter. All progression is saved; no on-frame battles.
TrioLanternTrail_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, TrioLantern_Load
	map_script MAP_SCRIPT_ON_TRANSITION, TrioLantern_Lights
	.byte 0
TrioLantern_Load:
	call TrioLantern_Paths
	end
TrioLantern_Paths:
	call_if_ge VAR_TRIO_RIFT_PENNY_STATE, 1, TrioLantern_Open1
	call_if_ge VAR_TRIO_RIFT_PENNY_STATE, 2, TrioLantern_Open2
	call_if_ge VAR_TRIO_RIFT_PENNY_STATE, 3, TrioLantern_Open3
	return
TrioLantern_Entrance::
	lockall
	faceplayer
	goto_if_unset FLAG_TRIO_RIFT_FIRE_RECEIVED, TrioLantern_NotReady
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioLantern_Missing
	msgbox TrioLantern_OfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioLantern_End
	closemessage
	warp MAP_TRIO_LANTERN_TRAIL, 12, 27
	waitstate
	goto TrioLantern_End
TrioLantern_NotReady:
	msgbox TrioLantern_NotReadyText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_Missing:
	msgbox TrioLantern_MissingText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_Exit::
	lockall
	faceplayer
	msgbox TrioLantern_ExitText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioLantern_End
	closemessage
	setflashlevel 0
	warp MAP_GOLDENROD_CITY_POKEMON_CENTER, 7, 6
	waitstate
	goto TrioLantern_End
TrioLantern_Riko::
	lockall
	faceplayer
	checkspecies SPECIES_RIKO_ECHO
	goto_if_eq VAR_RESULT, TRUE, TrioLantern_EchoForm
	checkspecies SPECIES_RIKO_WING
	goto_if_eq VAR_RESULT, TRUE, TrioLantern_Wing
	msgbox TrioLantern_RikoText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_Wing:
	msgbox TrioLantern_WingText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_Bijuu::
	lockall
	faceplayer
	checkspecies SPECIES_BIJUU_EMBER
	goto_if_eq VAR_RESULT, TRUE, TrioLantern_Ember
	checkspecies SPECIES_BIJUU_PSYCHIC
	goto_if_eq VAR_RESULT, TRUE, TrioLantern_Psychic
	msgbox TrioLantern_BijuuText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_Psychic:
	msgbox TrioLantern_PsychicText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_Penny::
	lockall
	faceplayer
	checkspecies SPECIES_PENNY_BRAVE
	goto_if_eq VAR_RESULT, TRUE, TrioLantern_BravePenny
	checkspecies SPECIES_PENNY_GUARDIAN
	goto_if_eq VAR_RESULT, TRUE, TrioLantern_Armor
	msgbox TrioLantern_PennyText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_Armor:
	msgbox TrioLantern_ArmorText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_Light1::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_RIFT_PENNY_STATE, 1, TrioLantern_Already
	goto_if_ne VAR_TRIO_RIFT_PENNY_STATE, 0, TrioLantern_Order
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioLantern_Missing
	msgbox TrioLantern_Light1Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioLantern_End
	playmoncry SPECIES_RIKO, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioLantern_Answer1Text, MSGBOX_DEFAULT
	setvar VAR_TRIO_RIFT_PENNY_STATE, 1
	call TrioLantern_Open1
	special DrawWholeMapView
	animateflash 3
	setflashlevel 3
	goto TrioLantern_End
TrioLantern_Light2::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_RIFT_PENNY_STATE, 2, TrioLantern_Already
	goto_if_ne VAR_TRIO_RIFT_PENNY_STATE, 1, TrioLantern_Order
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioLantern_Missing
	msgbox TrioLantern_Light2Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioLantern_End
	playmoncry SPECIES_RIKO, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioLantern_Answer2Text, MSGBOX_DEFAULT
	setvar VAR_TRIO_RIFT_PENNY_STATE, 2
	call TrioLantern_Open2
	special DrawWholeMapView
	animateflash 2
	setflashlevel 2
	goto TrioLantern_End
TrioLantern_Light3::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_RIFT_PENNY_STATE, 3, TrioLantern_Already
	goto_if_ne VAR_TRIO_RIFT_PENNY_STATE, 2, TrioLantern_Order
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioLantern_Missing
	msgbox TrioLantern_Light3Text, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioLantern_End
	playmoncry SPECIES_RIKO, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioLantern_Answer3Text, MSGBOX_DEFAULT
	setvar VAR_TRIO_RIFT_PENNY_STATE, 3
	call TrioLantern_Open3
	special DrawWholeMapView
	animateflash 0
	setflashlevel 0
	goto TrioLantern_End
TrioLantern_Open1:
	setmetatile 11, 24, 0x40C, FALSE
	setmetatile 12, 24, 0x40C, FALSE
	setmetatile 11, 25, 0x40C, FALSE
	setmetatile 12, 25, 0x40C, FALSE
	return
TrioLantern_Open2:
	setmetatile 11, 16, 0x40C, FALSE
	setmetatile 12, 16, 0x40C, FALSE
	setmetatile 11, 17, 0x40C, FALSE
	setmetatile 12, 17, 0x40C, FALSE
	return
TrioLantern_Open3:
	setmetatile 11, 8, 0x40C, FALSE
	setmetatile 12, 8, 0x40C, FALSE
	setmetatile 11, 9, 0x40C, FALSE
	setmetatile 12, 9, 0x40C, FALSE
	return
TrioLantern_Already:
	msgbox TrioLantern_AlreadyText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_Order:
	msgbox TrioLantern_OrderText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_Guardian::
	lockall
	faceplayer
	goto_if_ge VAR_TRIO_RIFT_PENNY_STATE, 4, TrioLantern_Victory
	goto_if_ne VAR_TRIO_RIFT_PENNY_STATE, 3, TrioLantern_Order
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioLantern_Missing
	msgbox TrioLantern_GuardianText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioLantern_End
	setvar VAR_0x8004, SPECIES_PENNY_BRAVE
	specialvar VAR_RESULT, PrepareTrioSpiritTrial
	goto_if_eq VAR_RESULT, FALSE, TrioLantern_Missing
	closemessage
	playmoncry SPECIES_PENNY_BRAVE, CRY_MODE_ENCOUNTER
	waitmoncry
	special BattleSetup_StartTrioSpiritTrial
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioLantern_Retry
	setvar VAR_TRIO_RIFT_PENNY_STATE, 4
TrioLantern_Victory:
	msgbox TrioLantern_VictoryText, MSGBOX_DEFAULT
	goto_if_set FLAG_TRIO_RIFT_BRAVERY_RECEIVED, TrioLantern_End
	giveitem ITEM_PENNYS_BRAVERY
	goto_if_eq VAR_RESULT, FALSE, TrioLantern_Pending
	setflag FLAG_TRIO_RIFT_BRAVERY_RECEIVED
	setvar VAR_TRIO_RIFT_PENNY_STATE, 5
	msgbox TrioLantern_GiftText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_Pending:
	msgbox TrioLantern_PendingText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_Retry:
	msgbox TrioLantern_RetryText, MSGBOX_DEFAULT
TrioLantern_End:
	releaseall
	end
TrioLantern_OfferText:
	.string "Penny's lanterns are\nwaiting. Visit the Lantern\pTrail? You can return any\ntime.$"
TrioLantern_NotReadyText:
	.string "Earn Bijuu's Fire in the\nMirror House first. A\plittle light goes a long\nway.$"
TrioLantern_MissingText:
	.string "Bring Riko, Bijuu and\nPenny to explore together.$"
TrioLantern_ExitText:
	.string "Return to Goldenrod?\nOpened paths stay open.$"
TrioLantern_RikoText:
	.string "Riko stays beside Penny. A\nbark can find a path.\pTaking a step is Penny's\nchoice.$"
TrioLantern_WingText:
	.string "Riko folds her wings. She\nwill walk with Penny. No\psister gets left behind.$"
TrioLantern_BijuuText:
	.string "Bijuu waits by the next\nlight. She will not rush\pPenny. The trail is safe\ntogether.$"
TrioLantern_PsychicText:
	.string "Bijuu feels Penny's worry.\nShe settles beside her.\pBeing afraid does not mean\nbeing alone.$"
TrioLantern_PennyText:
	.string "Penny sees a little\nlantern. She takes one\psmall step. Her sisters\ntake it too.$"
TrioLantern_ArmorText:
	.string "Penny lowers her shield\nso Riko can nuzzle her.\pBeing brave means keeping\nyour family close.$"
TrioLantern_Light1Text:
	.string "Riko waits at Penny's\nside. Light the first\plantern together?$"
TrioLantern_Answer1Text:
	.string "Riko gives a tiny bark.\nPenny answers with a wag.\pThe stones shift.\nHer sisters follow her.$"
TrioLantern_Light2Text:
	.string "Bijuu keeps the next spot\nsafe. Penny looks back and\psmiles. Light the second\nlantern?$"
TrioLantern_Answer2Text:
	.string "Riko tries a softer bark.\nBijuu adds a sleepy purr.\pThe lonely echo settles.\nAnother path appears.$"
TrioLantern_Light3Text:
	.string "Her sisters are right\nhere. Penny can see the\pway now. Light the last\nlantern?$"
TrioLantern_Answer3Text:
	.string "Penny leans against Riko.\nBijuu curls beside them.\pOne bark. One safe family.\nThe guardian awakens.$"
TrioLantern_AlreadyText:
	.string "This lantern is already\nlit. Penny pauses for a\pcuddle.$"
TrioLantern_OrderText:
	.string "A nearer lantern is\nwaiting. One small step at\pa time.$"
TrioLantern_GuardianText:
	.string "A lightly armored Penny\nwaits. No shield. No magic\pwall. Just one brave\nlittle heart. Face the\pbrave guardian?$"
TrioLantern_VictoryText:
	.string "The garden fills with\nlight. Penny led her\psisters home. She did not\nstop being scared. She\plearned she could go on.\nHer full Spirit still\psleeps.$"
TrioLantern_GiftText:
	.string "Keep Penny's Bravery. Use\nit from Key Items for her\plightly armored Brave\nform. Use again to return.\pThree sisters, three\nsparks.$"
TrioLantern_PendingText:
	.string "Your Bag has no room.\nPenny's Bravery waits\phere. Return whenever you\nlike. No new battle is\pneeded.$"
TrioLantern_RetryText:
	.string "The guardian waits softly.\nAll the girls are healed.\pEvery lit lantern stays\nlit. Try again whenever\pyou want.$"

TrioLantern_ReadMemory::
	msgbox TrioLantern_VictoryText, MSGBOX_DEFAULT
	return

TrioLantern_EchoForm:
	msgbox TrioLantern_EchoFormText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_EchoFormText:
	.string "Two Riko heads hum softly.\nOne listens ahead. One\plistens to Penny. Both\nwalk at her pace.$"

@ Reconstruct light radius on entry/save reload; normal destinations reset darkness.
TrioLantern_Lights:
	goto_if_ge VAR_TRIO_RIFT_PENNY_STATE, 3, TrioLantern_Bright
	goto_if_eq VAR_TRIO_RIFT_PENNY_STATE, 2, TrioLantern_LightRadius2
	goto_if_eq VAR_TRIO_RIFT_PENNY_STATE, 1, TrioLantern_LightRadius3
	setflashlevel 4
	end
TrioLantern_LightRadius3:
	setflashlevel 3
	end
TrioLantern_LightRadius2:
	setflashlevel 2
	end
TrioLantern_Bright:
	setflashlevel 0
	end

TrioLantern_Ember:
	msgbox TrioLantern_EmberText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_EmberText:
	.string "Bijuu's tail flame glows.\nShe holds it low for\pPenny. Her spark is for\nkeeping a sister warm, not\pshowing off.$"

TrioLantern_BravePenny:
	msgbox TrioLantern_BravePennyText, MSGBOX_DEFAULT
	goto TrioLantern_End
TrioLantern_BravePennyText:
	.string "Penny taps her armor.\nHer sisters nuzzle her.\pNo shield is needed yet.\nSafe with both her girls.$"
