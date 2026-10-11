@ Optional city parade. No items, battles, badges, party mutations or camera scroll.
TrioParade_Offer::
	goto_if_set FLAG_HIDE_GOLDENROD_NPCS, TrioParade_OfferReturn
	msgbox TrioParade_OfferText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioParade_OfferReturn
	closemessage
	warp MAP_TRIO_POM_PARADE, 30, 23
	waitstate
	releaseall
	end
TrioParade_OfferReturn:
	return

TrioParade_Run::
	lockall
	setvar VAR_TEMP_A, 0
	special PrepareTrioParadeActors
	goto_if_eq VAR_RESULT, FALSE, TrioParade_NotReady
	applymovement LOCALID_PLAYER, TrioParade_FaceRoad
	waitmovement 0
	msgbox TrioParade_OpeningText, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PARADE_POM_1, TrioParade_March
	applymovement LOCALID_PARADE_POM_2, TrioParade_March
	applymovement LOCALID_PARADE_POM_3, TrioParade_March
	applymovement LOCALID_PARADE_POM_4, TrioParade_March
	applymovement LOCALID_PARADE_POM_5, TrioParade_March
	applymovement LOCALID_PARADE_POM_6, TrioParade_March
	applymovement LOCALID_PARADE_POM_7, TrioParade_March
	applymovement LOCALID_PARADE_POM_8, TrioParade_March
	applymovement LOCALID_PARADE_POM_9, TrioParade_March
	waitmovementall
	msgbox TrioParade_FloofText, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PARADE_POM_4, TrioParade_Spin
	applymovement LOCALID_PARADE_POM_6, TrioParade_Sniff
	applymovement LOCALID_PARADE_POM_1, TrioParade_LeadBark
	waitmovementall
	playmoncry SPECIES_RIKO, CRY_MODE_NORMAL
	delay 45
	msgbox TrioParade_QuirksText, MSGBOX_DEFAULT
	msgbox TrioParade_ScottText, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PARADE_POM_1, TrioParade_March
	applymovement LOCALID_PARADE_POM_2, TrioParade_March
	applymovement LOCALID_PARADE_POM_3, TrioParade_March
	applymovement LOCALID_PARADE_POM_4, TrioParade_March
	applymovement LOCALID_PARADE_POM_5, TrioParade_March
	applymovement LOCALID_PARADE_POM_6, TrioParade_March
	applymovement LOCALID_PARADE_POM_7, TrioParade_March
	applymovement LOCALID_PARADE_POM_8, TrioParade_March
	applymovement LOCALID_PARADE_POM_9, TrioParade_LatePom
	waitmovementall
	msgbox TrioParade_CatchupText, MSGBOX_DEFAULT
	closemessage
	removeobject LOCALID_PARADE_POM_1
	removeobject LOCALID_PARADE_POM_2
	removeobject LOCALID_PARADE_POM_3
	removeobject LOCALID_PARADE_POM_4
	removeobject LOCALID_PARADE_POM_5
	removeobject LOCALID_PARADE_POM_6
	removeobject LOCALID_PARADE_POM_7
	removeobject LOCALID_PARADE_POM_8
	removeobject LOCALID_PARADE_POM_9
	applymovement LOCALID_PARADE_SCOTT, TrioParade_Cheer
	applymovement LOCALID_PARADE_FAN, TrioParade_Cheer
	applymovement LOCALID_PARADE_GRANDMA, TrioParade_Cheer
	applymovement LOCALID_PARADE_PENNY, TrioParade_Cheer
	applymovement LOCALID_PARADE_BIJUU, TrioParade_Cheer
	waitmovementall
	msgbox TrioParade_FinaleText, MSGBOX_DEFAULT
	goto_if_eq VAR_TRIO_POM_PARADE, 1, TrioParade_Return
	setvar VAR_TRIO_POM_PARADE, 1
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
TrioParade_Return::
	closemessage
	clearflag FLAG_TEMP_HIDE_FOLLOWER
	warp MAP_GOLDENROD_CITY, 30, 24
	waitstate
	releaseall
	end
TrioParade_NotReady:
	msgbox TrioParade_NotReadyText, MSGBOX_DEFAULT
	goto TrioParade_Return
TrioParade_ReadMemory::
	msgbox TrioParade_MemoryText, MSGBOX_DEFAULT
	return
TrioParade_FaceRoad:
	face_right
	step_end
TrioParade_March:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
TrioParade_Spin:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_up
	step_end
TrioParade_Sniff:
	walk_right
	face_down
	delay_16
	delay_16
	walk_left
	face_up
	step_end
TrioParade_LeadBark:
	jump_in_place_up
	step_end
TrioParade_LatePom:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
TrioParade_Cheer:
	jump_in_place_right
	delay_8
	jump_in_place_right
	step_end

TrioParade_OfferText:
	.string "I organize the Pom Parade!\nNine Poms. One road.\pAbsolutely no volume\ncontrol. Want a front-row\pspot with Scott and the\ngirls?$"

TrioParade_OpeningText:
	.string "The side street fills with\nspectators. Penny sits\pbeside you. Bijuu claims\nthe best view. Riko leads\pnine proud Poms into\nGoldenrod!$"

TrioParade_FloofText:
	.string "Two neat columns of fluff\nmarch up the road. The\pcrowd cheers! For three\nwhole seconds, everyone\pfollows the plan.$"

TrioParade_QuirksText:
	.string "One Pom spins for\napplause. Another\pinvestigates a suspicious\nsnack smell. Riko barks\pthe official marching\ninstructions. Nobody\punderstands them.$"

TrioParade_ScottText:
	.string "Scott: Nine Poms, and\nyours is still the\ploudest. Penny is handling\nsecurity. Bijuu is judging\pthe choreography. You are\nmy favorite view.$"

TrioParade_CatchupText:
	.string "The last Pom remembers she\nis in a parade! Tiny legs.\pMaximum urgency. She\ncatches the others just\pbefore the finish.$"

TrioParade_FinaleText:
	.string "Nine Poms take a final bow\naround the next corner.\pThe crowd erupts! Penny\naccepts her security\preview. Bijuu awards one\npolite blink.$"

TrioParade_NotReadyText:
	.string "A few Poms missed roll\ncall. Back to the\porganizer! We can try\nagain.$"

TrioParade_MemoryText:
	.string "Pom Parade, Goldenrod.\nNine Poms borrowed a road.\pRiko led. Penny kept\nwatch. Bijuu judged. Scott\pwatched you smile. The\nlast Pom arrived at full\pspeed.$"
