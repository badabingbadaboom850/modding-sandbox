.set LOCALID_MOMS_FRIEND, 2

NewBarkTown_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_PlayersHouse_1F_OnTransition
	.byte 0

NewBarkTown_PlayersHouse_1F_OnTransition::
	@ Keep the temporary cave test guide available on existing saves.
	clearflag FLAG_HIDE_MOMS_FRIEND
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
	call TrioTestItems_Restock
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomsFriend, MSGBOX_DEFAULT
	applymovement LOCALID_MOMS_FRIEND, NewBarkTown_PlayersHouse_1F_MovementFaceRight
	waitmovement 0
	msgbox NewBarkTown_PlayersHouse_1F_Text_TestCaveTrip, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_PlayersHouse_1F_EventScript_TestCaveTrip
	msgbox NewBarkTown_PlayersHouse_1F_Text_TestSpiritBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_PlayersHouse_1F_EventScript_TestSpiritBattle
	msgbox NewBarkTown_PlayersHouse_1F_Text_ControlTrip, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_PlayersHouse_1F_EventScript_ControlTrip
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_TestCaveTrip::
	closemessage
	warp MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM_SUICUNE, 4, 5
	waitstate
	release
	end

NewBarkTown_PlayersHouse_1F_Text_TestCaveTrip:
	.string "Want a test trip to the\n"
	.string "Spirit of Riko cave?\p"
	.string "Inspect the entrance there\n"
	.string "to return to New Bark Town.$"

NewBarkTown_PlayersHouse_1F_MomEventScript_GoodLuck::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomLeaving, MSGBOX_DEFAULT
	setflag FLAG_MOM_VISITED
	clearflag FLAG_HIDE_ROUTE_30_NPCS
	setvar VAR_NEWBARK_TOWN_STATE, 5
	release
	end


NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular::
	checkspecies SPECIES_FIDOUGH
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular_Heal
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomComfortPenny, MSGBOX_DEFAULT
NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular_Heal::
	call PlayersHouse_1F_EventScript_MomHealsParty
	release
	end

NewBarkTown_PlayersHouse_1F_Text_MomComfortPenny:
	.string "Mom: Penny, you are safe here.\n"
	.string "Your family is right here.$"

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

NewBarkTown_PlayersHouse_1F_EventScript_TestSpiritBattle::
	closemessage
	setwildbattle SPECIES_RIKO_SPIRIT, 70, ITEM_CHARCOAL
	dowildbattle
	release
	end

NewBarkTown_PlayersHouse_1F_Text_TestSpiritBattle:
	.string "Try a Spirit of Riko battle\n"
	.string "here instead?\p"
	.string "Level 70. You can catch it.\n"
	.string "Cave progress will not change.$"

NewBarkTown_PlayersHouse_1F_EventScript_ControlTrip::
	closemessage
	warp MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F, 4, 4
	waitstate
	release
	end

NewBarkTown_PlayersHouse_1F_Text_ControlTrip:
	.string "Try a control teleport\n"
	.string "to your upstairs bedroom?$"
