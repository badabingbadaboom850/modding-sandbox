.set LOCALID_MOMS_FRIEND, 2

NewBarkTown_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_PlayersHouse_1F_OnTransition
	.byte 0

NewBarkTown_PlayersHouse_1F_OnTransition::
	call_if_eq VAR_NEWBARK_TOWN_STATE, 1, NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable
	call_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable
	call_if_eq VAR_NEWBARK_TOWN_STATE, 3, NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable
	end

NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable::
	setobjectxyperm LOCALID_MOM, 8, 4
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_LEFT

	@add to newgame later
	clearflag FLAG_HIDE_MOMS_FRIEND
	clearflag FLAG_MOM_VISITED
	return

NewBarkTown_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	call TrioMemories_Mom
	goto_if_set FLAG_MOM_VISITED, NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular
	goto_if_set FLAG_ADVENTURE_STARTED, NewBarkTown_PlayersHouse_1F_MomEventScript_GoodLuck
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomHurryUpElmIsWaiting, MSGBOX_DEFAULT
	applymovement LOCALID_MOM, NewBarkTown_PlayersHouse_1F_MovementFaceLeft
	waitmovement 0
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend::
	lock
	faceplayer
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomsFriend, MSGBOX_DEFAULT
	msgbox NewBarkTown_PlayersHouse_1F_Text_PennyTestSupplies, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend_Finish
	giveitem ITEM_DADS_KEYS, 5
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend_BagFull
	giveitem ITEM_PIECE_OF_CHICKEN, 5
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend_BagFull
	giveitem ITEM_GREEN_PEPPER, 1
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend_BagFull
	giveitem ITEM_EEL_SUSHI, 1
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend_BagFull
	giveitem ITEM_FROZEN_FISH, 1
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend_BagFull
	giveitem ITEM_MOUSE_TOY, 1
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend_BagFull
	giveitem ITEM_DOG_BOWL, 1
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend_BagFull
	giveitem ITEM_FETCHING_STICK, 1
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend_BagFull
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend_Finish

NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend_BagFull::
	msgbox NewBarkTown_PlayersHouse_1F_Text_TestSuppliesBagFull, MSGBOX_DEFAULT
NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend_Finish::
	applymovement LOCALID_MOMS_FRIEND, NewBarkTown_PlayersHouse_1F_MovementFaceRight
	waitmovement 0
	release
	end

NewBarkTown_PlayersHouse_1F_MomEventScript_GoodLuck::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomLeaving, MSGBOX_DEFAULT
	setflag FLAG_MOM_VISITED
	clearflag FLAG_HIDE_ROUTE_30_NPCS
	setvar VAR_NEWBARK_TOWN_STATE, 5
	release
	end


NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular::
	call TrioParty_CheckPenny
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular_Heal
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomComfortPenny, MSGBOX_DEFAULT
	call NewBarkTown_PlayersHouse_1F_EventScript_PennyConfidence
NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular_Heal::
	call NewBarkTown_PlayersHouse_1F_EventScript_FamilyBanter
	call PlayersHouse_1F_EventScript_MomHealsParty
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_PennyConfidence::
	goto_if_eq VAR_PENNY_CONFIDENCE_STATE, 0, NewBarkTown_PlayersHouse_1F_EventScript_PennyFirstStep
	goto_if_eq VAR_PENNY_CONFIDENCE_STATE, 1, NewBarkTown_PlayersHouse_1F_EventScript_PennyCheckFinal
	goto_if_eq VAR_PENNY_CONFIDENCE_STATE, 2, NewBarkTown_PlayersHouse_1F_EventScript_PennyRewardRetry
	return

NewBarkTown_PlayersHouse_1F_EventScript_PennyFirstStep::
	goto_if_unset FLAG_BADGE01_GET, NewBarkTown_PlayersHouse_1F_EventScript_PennyConfidence_Return
	msgbox NewBarkTown_PlayersHouse_1F_Text_PennyFirstStep, MSGBOX_DEFAULT
	setvar VAR_PENNY_CONFIDENCE_STATE, 1
	return

NewBarkTown_PlayersHouse_1F_EventScript_PennyCheckFinal::
	goto_if_unset FLAG_BADGE02_GET, NewBarkTown_PlayersHouse_1F_EventScript_PennyConfidence_Return
	call TrioParty_CheckRiko
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_PennyConfidence_Return
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_PennyConfidence_Return
	msgbox NewBarkTown_PlayersHouse_1F_Text_PennyFinalStep, MSGBOX_DEFAULT
	setvar VAR_PENNY_CONFIDENCE_STATE, 2
	goto NewBarkTown_PlayersHouse_1F_EventScript_PennyRewardRetry

NewBarkTown_PlayersHouse_1F_EventScript_PennyRewardRetry::
	giveitem ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_PennyBagFull
	setvar VAR_PENNY_CONFIDENCE_STATE, 3
	msgbox NewBarkTown_PlayersHouse_1F_Text_PennyThanks, MSGBOX_DEFAULT
	return

NewBarkTown_PlayersHouse_1F_EventScript_PennyBagFull::
	msgbox NewBarkTown_PlayersHouse_1F_Text_PennyBagFull, MSGBOX_DEFAULT
	return

NewBarkTown_PlayersHouse_1F_EventScript_PennyConfidence_Return::
	return

NewBarkTown_PlayersHouse_1F_Text_MomComfortPenny:
	.string "Mom: Penny, you are safe here.\n"
	.string "Your family is right here.$"

NewBarkTown_PlayersHouse_1F_Text_PennyFirstStep:
	.string "Mom: After your rescue, taking\n"
	.string "your time around new people is\p"
	.string "okay. After earning a Badge,\n"
	.string "you came to the doorway with\p"
	.string "us. That is a brave step.\p"
	.string "Your sisters can stay close\n"
	.string "when you're ready for another.$"

NewBarkTown_PlayersHouse_1F_Text_PennyFinalStep:
	.string "Mom: Penny chose to greet our\n"
	.string "visitor today. Riko stayed\p"
	.string "nearby, while Bijuu waited for\n"
	.string "Penny's cue. She said hello,\p"
	.string "then came back when she was\n"
	.string "ready. A small step, on her\p"
	.string "terms.$"

NewBarkTown_PlayersHouse_1F_Text_PennyThanks:
	.string "Mom: Penny, you did this at\n"
	.string "your own pace. I am proud of\p"
	.string "you. Whenever you need to\n"
	.string "pause, you can come home.$"

NewBarkTown_PlayersHouse_1F_Text_PennyBagFull:
	.string "Mom: Your Bag is full. Make\n"
	.string "room and come back for Penny's\p"
	.string "small thank-you.$"

NewBarkTown_PlayersHouse_1F_EventScript_MomsIntroTrigger1::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_PlayersHouse_1F_PlayerIntroMovement1
	waitmovement 0
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomsIntro
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomsIntroTrigger2::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_PlayersHouse_1F_PlayerIntroMovement2
	waitmovement 0
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomsIntro
	end


NewBarkTown_PlayersHouse_1F_EventScript_MomsIntro::
	playse SE_PIN
	applymovement LOCALID_MOM, Common_Movement_ExclamationMark
	delay 60
	applymovement LOCALID_MOM, NewBarkTown_PlayersHouse_1F_MomMovement_1
	waitmovement 0
	createfieldmugshot MUGSHOT_MOM
	msgbox NewBarkTown_PlayersHouse_1F_Text_ElmsLookingForYou, MSGBOX_DEFAULT
	call NewBarkTown_PlayersHouse_1F_EventScript_GivePokeGear
	call NewBarkTown_PlayersHouse_1F_EventScript_GiveRunningShoes
	removefieldmugshot
	applymovement LOCALID_MOM, NewBarkTown_PlayersHouse_1F_MomMovement_2
	waitmovement 0
	setvar VAR_NEWBARK_TOWN_STATE, 2
	setvar VAR_NEWBARKTOWN_LABSTATE, 0
	setflag FLAG_HIDE_LAB_POLICEMAN
	setflag FLAG_VISITED_NEWBARK_TOWN

	@former flagheap location

	releaseall
	end



NewBarkTown_PlayersHouse_1F_EventScript_GivePokeGear::
	playfanfare MUS_OBTAIN_ITEM
	removefieldmugshot
	message NewBarkTown_PlayersHouse_1F_Text_ObtainedPokeGear
	waitfanfare
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_RECEIVED_POKENAV
	setflag FLAG_ADDED_MATCH_CALL_TO_POKENAV
	setflag FLAG_REGISTER_RIVAL_POKENAV
	createfieldmugshot MUGSHOT_MOM
	msgbox NewBarkTown_PlayersHouse_1F_Text_ExplainPokeGear, MSGBOX_DEFAULT
	closemessage
	delay 30
	return
	
NewBarkTown_PlayersHouse_1F_EventScript_GiveRunningShoes::
	createfieldmugshot MUGSHOT_MOM
	msgbox NewBarkTown_PlayersHouse_1F_Text_WearTheseRunningShoes, MSGBOX_DEFAULT
	waitmessage
	closemessage
	playfanfare MUS_OBTAIN_ITEM
	msgbox NewBarkTown_PlayersHouse_1F_Text_SwitchShoesWithRunningShoes, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	special EnableAutorun
	createfieldmugshot MUGSHOT_MOM
	msgbox NewBarkTown_PlayersHouse_1F_Text_ExplainRunningShoes, MSGBOX_DEFAULT
	closemessage
	delay 30
	return

NewBarkTown_PlayersHouse_1F_PlayerIntroMovement1:
	delay_8
	walk_down
	walk_right
	walk_down
	face_left
	delay_8
	step_end

NewBarkTown_PlayersHouse_1F_PlayerIntroMovement2:
	delay_8
	walk_down
	face_left
	delay_8
	step_end

NewBarkTown_PlayersHouse_1F_MomMovement_1:
	face_right
	walk_right
	step_end

NewBarkTown_PlayersHouse_1F_MomMovement_2:
	face_left
	walk_left
	delay_8
	step_end

NewBarkTown_PlayersHouse_1F_MovementFaceRight:
	face_right
	step_end

NewBarkTown_PlayersHouse_1F_MovementFaceLeft:
	face_left
	step_end

NewBarkTown_PlayersHouse_1F_Text_ElmsLookingForYou:
	.string "Oh, {PLAYER}…! Our neighbor,\n"
	.string "Prof. Elm, was looking for you.\p"
	.string "He said he wanted you to do\n"
	.string "something for him.\p"
	.string "Oh! I almost forgot! Your Pokégear\n"
	.string "is back from the repair shop.\p"
	.string "Here you go!$"

NewBarkTown_PlayersHouse_1F_Text_ObtainedPokeGear:
	.string "{PLAYER} obtained the Pokégear.$"

NewBarkTown_PlayersHouse_1F_Text_ExplainPokeGear:
	.string "Mom: Phone numbers are stored\n"
	.string "in memory.\p"
	.string "Just choose a name you want to call.\p"
	.string "Gee, isn't that convenient?$"

NewBarkTown_PlayersHouse_1F_Text_WearTheseRunningShoes:
	.string "Oh, and don't forget your\n"
	.string "Running Shoes!$"

NewBarkTown_PlayersHouse_1F_Text_SwitchShoesWithRunningShoes:
	.string "{PLAYER} switched shoes with the\n"
	.string "Running Shoes.$"

NewBarkTown_PlayersHouse_1F_Text_ExplainRunningShoes:
	.string "Mom: You'll get everywhere faster\n"
	.string "with them!$"

NewBarkTown_PlayersHouse_1F_Text_MomHurryUpElmIsWaiting:
	.string "Mom: Prof. Elm is waiting for you.\p"
	.string "Hurry up, baby!$"

NewBarkTown_PlayersHouse_1F_Text_MomsFriend:
	.string "Hi, {PLAYER}!\p"
	.string "I'm visiting!\p"
	.string "Have you heard?\p"
	.string "My daughter is adamant about\n"
	.string "becoming Prof. Elm's assistant.\p"
	.string "She really loves Pokémon!$"

NewBarkTown_PlayersHouse_1F_Text_MomLeaving:
	.string "Mom: Wow, that's a cute Pokémon.\n"
	.string "Where did you get it?\p"
	.string "…\p"
	.string "So, you're leaving on an adventure...\n"
	.string "That does sound challenging...\p"
	.string "Just be careful.\p"
	.string "Pokémon are your friends.\n"
	.string "You need to work as a team.\p"
	.string "Now, go on!\n"
	.string "I'm behind you all the way!$"

NewBarkTown_PlayersHouse_1F_EventScript_FamilyBanter::
	call_if_ge VAR_ECRUTEAK_BIJUU_MYSTERY, 6, NewBarkTown_PlayersHouse_1F_EventScript_CelestialFamily
	goto_if_set FLAG_IS_CHAMPION, NewBarkTown_PlayersHouse_1F_Family_Champion
	goto_if_set FLAG_BADGE08_GET, NewBarkTown_PlayersHouse_1F_Family_EightBadges
	goto_if_ge VAR_TRIO_RESEARCH_STATE, 9, NewBarkTown_PlayersHouse_1F_Family_Scrapbook
	goto_if_ge VAR_TRIO_RESEARCH_STATE, 6, NewBarkTown_PlayersHouse_1F_Family_Azalea
	goto_if_set FLAG_BADGE03_GET, NewBarkTown_PlayersHouse_1F_Family_Goldenrod
	goto_if_set FLAG_BADGE01_GET, NewBarkTown_PlayersHouse_1F_Family_Violet
	goto NewBarkTown_PlayersHouse_1F_Family_Early

NewBarkTown_PlayersHouse_1F_Family_Champion:
	msgbox NewBarkTown_PlayersHouse_1F_Text_Family_Champion, MSGBOX_DEFAULT
	return

NewBarkTown_PlayersHouse_1F_Text_Family_Champion:
	.string "Mom: Champion! Come here,\n"
	.string "all of you. Riko, Penny,\p"
	.string "Bijuu, and my wonderful\n"
	.string "girl.\p"
	.string "The world can call you\n"
	.string "legends. There is still\p"
	.string "room for all of you right\n"
	.string "here.$"

NewBarkTown_PlayersHouse_1F_Family_EightBadges:
	msgbox NewBarkTown_PlayersHouse_1F_Text_Family_EightBadges, MSGBOX_DEFAULT
	return

NewBarkTown_PlayersHouse_1F_Text_Family_EightBadges:
	.string "Mom: The League can wait\n"
	.string "until you have rested.\p"
	.string "Eight Badges do not make\n"
	.string "the babies any less my\p"
	.string "babies.$"

NewBarkTown_PlayersHouse_1F_Family_Scrapbook:
	msgbox NewBarkTown_PlayersHouse_1F_Text_Family_Scrapbook, MSGBOX_DEFAULT
	return

NewBarkTown_PlayersHouse_1F_Text_Family_Scrapbook:
	.string "Mom: Susan loved your\n"
	.string "purse story. She says\p"
	.string "Bijuu is the family\n"
	.string "detective. Greg has\p"
	.string "requested a recount.$"

NewBarkTown_PlayersHouse_1F_Family_Azalea:
	msgbox NewBarkTown_PlayersHouse_1F_Text_Family_Azalea, MSGBOX_DEFAULT
	return

NewBarkTown_PlayersHouse_1F_Text_Family_Azalea:
	.string "Mom: Your notebook says\n"
	.string "Penny made a new friend in\p"
	.string "Azalea. A quiet afternoon\n"
	.string "deserves remembering too.$"

NewBarkTown_PlayersHouse_1F_Family_Goldenrod:
	msgbox NewBarkTown_PlayersHouse_1F_Text_Family_Goldenrod, MSGBOX_DEFAULT
	return

NewBarkTown_PlayersHouse_1F_Text_Family_Goldenrod:
	.string "Mom: Chelsea is planning a\n"
	.string "shopping trip with Riko. I\p"
	.string "told her to count the bags\n"
	.string "before they leave.$"

NewBarkTown_PlayersHouse_1F_Family_Violet:
	msgbox NewBarkTown_PlayersHouse_1F_Text_Family_Violet, MSGBOX_DEFAULT
	return

NewBarkTown_PlayersHouse_1F_Text_Family_Violet:
	.string "Mom: Caleb says nothing\n"
	.string "beats that beach. Chelsea\p"
	.string "disagrees. The girls are\n"
	.string "welcome to settle it on\p"
	.string "the couch.$"

NewBarkTown_PlayersHouse_1F_Family_Early:
	msgbox NewBarkTown_PlayersHouse_1F_Text_Family_Early, MSGBOX_DEFAULT
	return

NewBarkTown_PlayersHouse_1F_Text_Family_Early:
	.string "Mom: Susan says Greg has\n"
	.string "been hiding behind doors\p"
	.string "again. Tell him Penny gets\n"
	.string "the sunny spot, not him.$"



NewBarkTown_PlayersHouse_1F_EventScript_CelestialFamily::
	msgbox NewBarkTown_PlayersHouse_1F_Text_CelestialFamily, MSGBOX_DEFAULT
	return

NewBarkTown_PlayersHouse_1F_Text_CelestialFamily:
	.string "Mom: Susan heard about the\n"
	.string "celestial visitor. Greg\p"
	.string "says he knew it was Bijuu.\p"
	.string "Chelsea says a psychic cat\n"
	.string "should predict the best\p"
	.string "shopping deals. Riko\n"
	.string "agrees.$"


NewBarkTown_PlayersHouse_1F_Text_PennyTestSupplies:
	.string "Want some form supplies?\p"
	.string "Keys, chicken, and all six\n"
	.string "elemental keepsakes!$"

NewBarkTown_PlayersHouse_1F_Text_TestSuppliesBagFull:
	.string "Some supplies did not fit.\n"
	.string "Make room and ask again.$"

