
AzaleaTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AzaleaTown_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, AzaleaTown_OnLoad
	.byte 0

AzaleaTown_OnLoad::
	setrespawn HEAL_LOCATION_AZALEA_TOWN
	end

AzaleaTown_OnTransition::
	goto_if_eq VAR_AZALEA_TOWN_STATE, 5, AzaleaTown_MapScript_Hide_Silver
	end
	
AzaleaTown_OnFrame::
	map_script_2 VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_EventScript_GSBall
	.2byte 0

AzaleaTown_MapScript_Hide_Silver:
	setflag FLAG_HIDE_AZALEA_TOWN_SILVER
	removeobject LOCALID_AZALEA_TOWN_SILVER
	end

AzaleaTown_EventScript_Trigger:: @flagheap
	setflag FLAG_VISITED_AZALEA_TOWN
	setflag FLAG_HIDE_AZALEA_TOWN_SLOWPOKE
	setflag FLAG_HIDE_AZALEA_TOWN_SILVER
	setflag FLAG_HIDE_KURT_2
	setflag FLAG_HIDE_ILEX_FOREST_APPRENTICE
	setflag FLAG_HIDE_ILEX_FOREST_MASTER
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_4
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_3
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_2
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_1
	setflag FLAG_HIDE_CELEBI
	setflag FLAG_HIDE_ILEX_FOREST_KURT
	setflag FLAG_HIDE_AZALEA_TOWN_KURT
	setflag FLAG_HIDE_AZALEA_ARIADOS_LEFT
	setflag FLAG_HIDE_AZALEA_ARIADOS_MID
	setflag FLAG_HIDE_AZALEA_ARIADOS_RIGHT
	

	clearflag FLAG_HIDE_ILEX_FOREST_KIMONO
	clearflag FLAG_ITEM_SLOWPOKE_WELL_RAIN_DANCE
	clearflag FLAG_HIDE_AZALEA_TOWN_ROCKETS
	clearflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
	clearflag FLAG_HIDE_KURT_1
	clearflag FLAG_GOT_CHARCOAL
	clearflag FLAG_HIDE_AZALEA_TOWN_FARFETCHD
	clearflag FLAG_HIDE_AZALEA_TOWN_CUT_MASTER
	clearflag FLAG_MOVE_TUTOR_TAUGHT_HEADBUTT

	setvar VAR_AZALEA_TOWN_STATE, 1
	end

AzaleaTown_EventScript_Rocket1::
	lock
	faceplayer
	msgbox AzaleaTown_Text_Rocket1, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Rocket2::
	lock
	faceplayer
	msgbox AzaleaTown_Text_Rocket2, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Gramps::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_AZALEA_TOWN_ROCKETS, AzaleaTown_EventScript_Gramps2
	msgbox AzaleaTown_Text_GrampsBefore, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Gramps2::
	call TrioRift_CheckAtmosphere
	goto_if_eq VAR_RESULT, TRUE, AzaleaTown_RiftAtmosphere
	msgbox AzaleaTown_Text_GrampsAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_BADGE02_GET, AzaleaTown_Text_Teacher_TrioWorld1_After
	msgbox AzaleaTown_Text_Teacher, MSGBOX_DEFAULT
	goto AzaleaTown_Text_Teacher_TrioWorld1_Resume
AzaleaTown_Text_Teacher_TrioWorld1_After:
	msgbox AzaleaTown_Text_Teacher_TrioWorldAfter, MSGBOX_DEFAULT
AzaleaTown_Text_Teacher_TrioWorld1_Resume:
	call_if_ge VAR_TRIO_RESEARCH_STATE, 5, AzaleaTown_EventScript_ScrapbookNeighbor
	closemessage
	release
	end

AzaleaTown_EventScript_Youngster::
	lock
	faceplayer
	msgbox AzaleaTown_Text_Youngster, MSGBOX_DEFAULT
	call AzaleaTown_EventScript_ScrapbookVisit
	closemessage
	release
	end

AzaleaTown_EventScript_Slowpoke::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
	msgbox AzaleaTown_Text_Slowpoke1, MSGBOX_DEFAULT
	waitmoncry
	release
	end


AzaleaTown_EventScript_GymSign::
	lock
	msgbox AzaleaTown_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_KurtSign::
	lock
	msgbox AzaleaTown_Text_KurtsHouseSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_KilnSign::
	lock
	msgbox AzaleaTown_Text_CharcoalKilnSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_IlexSign::
	lock
	msgbox AzaleaTown_Text_IlexForestSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_WellSign::
	lock
	msgbox AzaleaTown_Text_SlowpokeWellSign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_AzaleaSign::
	lock
	msgbox AzaleaTown_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

AzaleaTown_EventScript_SilverTriggerTop::
	lock
	clearflag FLAG_HIDE_AZALEA_TOWN_SILVER
	addobject LOCALID_AZALEA_TOWN_SILVER
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	applymovement LOCALID_AZALEA_TOWN_SILVER, AzaleaTown_Movement_Silver_EnterTop
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	createfieldmugshot MUGSHOT_SILVER
	msgbox AzaleaTown_Text_RivalBefore, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_STARTER_MON, 0, AzaleaTown_Silver_Battle_Cyndaquil
	call_if_eq VAR_STARTER_MON, 1, AzaleaTown_Silver_Battle_Totodile
	call_if_eq VAR_STARTER_MON, 2, AzaleaTown_Silver_Battle_Chikorita
	playbgm MUS_HG_RIVAL_EXIT, TRUE
	createfieldmugshot MUGSHOT_SILVER
	msgbox AzaleaTown_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Movement_Player_LeaveTop
	waitmovement 0
	applymovement LOCALID_AZALEA_TOWN_SILVER, AzaleaTown_Movement_Silver_LeaveTop
	waitmovement 0
	playse SE_EXIT
	setflag FLAG_HIDE_AZALEA_TOWN_SILVER
	removeobject LOCALID_AZALEA_TOWN_SILVER
	setvar VAR_AZALEA_TOWN_STATE, 6
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

AzaleaTown_EventScript_SilverTriggerBot::
	lock
	clearflag FLAG_HIDE_AZALEA_TOWN_SILVER
	addobject LOCALID_AZALEA_TOWN_SILVER
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	applymovement LOCALID_AZALEA_TOWN_SILVER, AzaleaTown_Movement_Silver_EnterBot
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	createfieldmugshot MUGSHOT_SILVER
	msgbox AzaleaTown_Text_RivalBefore, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_STARTER_MON, 0, AzaleaTown_Silver_Battle_Cyndaquil
	call_if_eq VAR_STARTER_MON, 1, AzaleaTown_Silver_Battle_Totodile
	call_if_eq VAR_STARTER_MON, 2, AzaleaTown_Silver_Battle_Chikorita
	playbgm MUS_HG_RIVAL_EXIT, TRUE
	createfieldmugshot MUGSHOT_SILVER
	msgbox AzaleaTown_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Movement_Player_LeaveBot
	waitmovement 0
	applymovement LOCALID_AZALEA_TOWN_SILVER, AzaleaTown_Movement_Silver_LeaveBot
	waitmovement 0
	playse SE_EXIT
	setflag FLAG_HIDE_AZALEA_TOWN_SILVER
	removeobject LOCALID_AZALEA_TOWN_SILVER
	setvar VAR_AZALEA_TOWN_STATE, 6
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

AzaleaTown_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_2, AzaleaTown_Text_RivalWin
	return

AzaleaTown_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_2, AzaleaTown_Text_RivalWin
	return

AzaleaTown_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_2, AzaleaTown_Text_RivalWin
	return


AzaleaTown_EventScript_GSBall::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_Movement_PlayerGSBall
	waitmovement 0
	clearflag FLAG_HIDE_AZALEA_TOWN_KURT
	addobject LOCALID_AZALEA_TOWN_KURT_GS
	opendoor 19, 11
	waitdooranim
	waitmovement 0
	closedoor 19, 11
	waitdooranim
	applymovement LOCALID_AZALEA_TOWN_KURT_GS, AzaleaTown_Movement_Kurt2
	playse SE_M_PETAL_DANCE
	waitmovement 0
	msgbox AzaleaTown_Text_Kurt1, MSGBOX_DEFAULT
	closemessage
	playse SE_M_PETAL_DANCE
	msgbox AzaleaTown_Text_Kurt2, MSGBOX_DEFAULT
	giveitem ITEM_GS_BALL
	waitse
	playse SE_M_PETAL_DANCE
	turnobject LOCALID_AZALEA_TOWN_KURT_GS, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_M_PETAL_DANCE
	waitse
	turnobject LOCALID_AZALEA_TOWN_KURT_GS, DIR_SOUTH
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox AzaleaTown_Text_Kurt3, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_AZALEA_TOWN_KURT_GS, AzaleaTown_Movement_KurtLeave
	delay 60
	opendoor 19, 11
	waitdooranim
	waitmovement 0
	setflag FLAG_HIDE_AZALEA_TOWN_KURT
	removeobject LOCALID_AZALEA_TOWN_KURT_GS
	closedoor 19, 11
	waitdooranim
	setvar VAR_AZALEA_TOWN_STATE, 9
	release
	end

AzaleaTown_Movement_Silver_EnterTop:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

AzaleaTown_Movement_Silver_EnterBot:
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

AzaleaTown_Movement_Silver_LeaveTop:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

AzaleaTown_Movement_Silver_LeaveBot:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_left
	step_end

AzaleaTown_Movement_Player_LeaveTop:
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	face_up
	step_end

AzaleaTown_Movement_Player_LeaveBot:
	lock_facing_direction
	walk_fast_up
	unlock_facing_direction
	face_down
	step_end

AzaleaTown_Movement_Kurt1:
	walk_down
	step_end

AzaleaTown_Movement_Kurt2:
	walk_down
	walk_down
	walk_down
	face_right
	delay_8
	face_left
	delay_8
	face_down
	step_end

AzaleaTown_Movement_PlayerGSBall:
	walk_down
	walk_down
	walk_down
	face_left
	face_right
	face_down
	delay_8
	face_up
	step_end

AzaleaTown_Movement_KurtLeave:
	walk_up
	walk_up
	walk_up
	step_end

AzaleaTown_Text_RivalBefore:
	.string "…Tell me something.\p"
	.string "Is it true that Team Rocket\n"
	.string "has returned?\p"
	.string "What? You beat them? Hah! Quit\n"
	.string "lying.\p"
	.string "You're not joking?\n"
	.string "Then let's see how good you are.$"

AzaleaTown_Text_RivalWin:
	.string "…Humph! Useless Pokémon!\p"
	.string "Listen, you. You only won because\n"
	.string "my Pokémon were weak.$"

AzaleaTown_Text_RivalAfter:
	.string "I hate the weak.\p"
	.string "Pokémon, trainers. It doesn't\n"
	.string "matter who or what.\p"
	.string "I'm going to be strong and wipe\n"
	.string "out the weak.\p"
	.string "That goes for Team Rocket too.\p"
	.string "They act big and tough in a group.\p"
	.string "But get them alone, and they're weak.\n"
	.string "I hate them all.\p"
	.string "You stay out of my way. A weakling\n"
	.string "like you is only a distraction.$"

AzaleaTown_Text_RivalLoss:
	.string "…Humph! I knew you were lying.$"

AzaleaTown_Text_Rocket1:
	.string "It's unsafe to go in there,\n"
	.string "so I'm standing guard.\p"
	.string "Aren't I a good Samaritan?$"

AzaleaTown_Text_Rocket2:
	.string "Do you know about Slowpoketail?\n"
	.string "I heard it's tasty!\p"
	.string "Aren't you glad I told you that?$"

AzaleaTown_Text_GrampsBefore:
	.string "The Slowpoke have disappeared\n"
	.string "from town…\p"
	.string "I heard their Tails are being\n"
	.string "sold somewhere.\p"
	.string "I like Penny. She can sit\n"
	.string "beside a Slowpoke without\p"
	.string "trying to hurry it. We\n"
	.string "could all learn that.$"

AzaleaTown_Text_GrampsAfter:
	.string "The Slowpoke have returned.\p"
	.string "Knowing them, they could've just\n"
	.string "been goofing off somewhere.\p"
	.string "The trio passed the well\n"
	.string "with their trainer. Penny\p"
	.string "looked back twice to check\n"
	.string "the others were coming.$"

AzaleaTown_Text_Teacher:
	.string "Did you come to get Kurt to make\n"
	.string "some Balls?\p"
	.string "A lot of people do just that.\p"
	.string "Bugsy wants to study the\n"
	.string "trio. I hope his notebook\p"
	.string "has a page for Riko\n"
	.string "demanding attention.\p"
	.string "A woodcutter swears\n"
	.string "Penny's tail grew leaves.\p"
	.string "His friend saw Riko\n"
	.string "breathe fire. Could the\p"
	.string "girls master every type?$"


AzaleaTown_Text_Teacher_TrioWorldAfter:
	.string "Did you come to get Kurt to make\n"
	.string "some Balls?\p"
	.string "A lot of people do just that.\p"
	.string "Bugsy stood his ground\n"
	.string "against all three girls.\p"
	.string "He says battling them\n"
	.string "taught him more than\p"
	.string "watching ever could.\p"
	.string "Bugsy is collecting\n"
	.string "stories of the girls'\p"
	.string "unseen elements. Most\n"
	.string "witnesses remember the\p"
	.string "snacks better than the\n"
	.string "battle.$"

AzaleaTown_Text_Youngster:
	.string "Cut through Azalea to reach\n"
	.string "Ilex Forest.\p"
	.string "But these trees are hard to get\n"
	.string "through.\p"
	.string "Only the Charcoal Man can cut\n"
	.string "them down.\p"
	.string "Cutters saw three rare Pokemon\n"
	.string "pass through Ilex Forest.\p"
	.string "A shy cat was with them.\n"
	.string "They vanished fast.\p"
	.string "Riko sniffed every\n"
	.string "Apricorn. Bijuu sorted\p"
	.string "them by copying Kurt.\n"
	.string "Penny found the patch of\p"
	.string "sun and stayed there.$"

AzaleaTown_Text_Slowpoke1:
	.string "Slowpoke:..........\p"
	.string "...............Yawn?$"

AzaleaTown_Text_Kurt1:
	.string "Ilex Forest is restless!\p"
	.string "What is going on?$"

AzaleaTown_Text_Kurt2:
	.string "{PLAYER}, here's your GS Ball back!$"

AzaleaTown_Text_Kurt3:
	.string "Could you go see why Ilex Forest\n"
	.string "is so restless?$"

AzaleaTown_Text_Sign:
	.string "Azalea Town\n"
	.string "Where People and Pokémon Live in\l"
	.string "Happy Harmony.$"

AzaleaTown_Text_KurtsHouseSign:
	.string "Kurt's House$"

AzaleaTown_Text_GymSign:
	.string "Azalea Town\n"
	.string "Pokémon Gym\p"
	.string "Leader: Bugsy\p"
	.string "The Walking Bug Pokémon\n"
	.string "Encyclopedia$"

AzaleaTown_Text_SlowpokeWellSign:
	.string "Slowpoke Well\p"
	.string "Also known as the Rainmaker Well.\p"
	.string "Locals believe that a Slowpoke's\n"
	.string "yawn summons rain.\p"
	.string "Records show that a Slowpoke's\n"
	.string "yawn ended a drought 400 years ago.$"

AzaleaTown_Text_CharcoalKilnSign:
	.string "Charcoal Kiln$"

AzaleaTown_Text_IlexForestSign:
	.string "Ilex Forest\p"
	.string "Enter through the gate.$"

AzaleaTownKid::
	msgbox AzaleaTownKid_Text_0, MSGBOX_NPC
	return


AzaleaTownVulpix::
	lock
	faceplayer
	playmoncry SPECIES_VULPIX, CRY_MODE_NORMAL
	msgbox AzaleaTownVulpix_Text_0
	waitmessage
	release
	end


AzaleaTownKid_Text_0:
	.string "That Vulpix keeps taunting me from up\n"
	.string "there... If only I could use Rock Climb.$"

AzaleaTownVulpix_Text_0:
	.string "Vulpix: Vul!$"


AzaleaTown_EventScript_ScrapbookVisit::
	goto_if_ge VAR_TRIO_RESEARCH_STATE, 5, AzaleaTown_EventScript_ScrapbookRemember
	goto_if_ne VAR_TRIO_RESEARCH_STATE, 4, AzaleaTown_EventScript_ScrapbookReturn
	goto_if_unset FLAG_BADGE02_GET, AzaleaTown_EventScript_ScrapbookNotReady
	call TrioStory_CheckAll
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_EventScript_ScrapbookNeedGirls
	msgbox AzaleaTown_Text_ScrapbookOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AzaleaTown_EventScript_ScrapbookDeclined
	msgbox AzaleaTown_Text_ScrapbookScene1, MSGBOX_DEFAULT
	msgbox AzaleaTown_Text_ScrapbookScene2, MSGBOX_DEFAULT
	msgbox AzaleaTown_Text_ScrapbookScene3, MSGBOX_DEFAULT
	setvar VAR_TRIO_RESEARCH_STATE, 5
	msgbox AzaleaTown_Text_ScrapbookReport, MSGBOX_DEFAULT
	return

AzaleaTown_EventScript_ScrapbookRemember::
	msgbox AzaleaTown_Text_ScrapbookRemember, MSGBOX_DEFAULT
	return

AzaleaTown_EventScript_ScrapbookNotReady::
	msgbox AzaleaTown_Text_ScrapbookNotReady, MSGBOX_DEFAULT
	return

AzaleaTown_EventScript_ScrapbookNeedGirls::
	msgbox CherryGroveCity_Text_ScrapbookNeedGirls, MSGBOX_DEFAULT
	return

AzaleaTown_EventScript_ScrapbookDeclined::
	msgbox AzaleaTown_Text_ScrapbookDeclined, MSGBOX_DEFAULT
AzaleaTown_EventScript_ScrapbookReturn::
	return

AzaleaTown_Text_ScrapbookOffer:
	.string "My Hoothoot is shy around\n"
	.string "new people. Want to take a\p"
	.string "quiet minute with the\n"
	.string "girls?$"

AzaleaTown_Text_ScrapbookScene1:
	.string "You sit with the girls.\n"
	.string "Penny stays close to you.\p"
	.string "Hoothoot watches from his\n"
	.string "trainer's shoulder.\p"
	.string "Riko starts to step\n"
	.string "forward. You ask her to\p"
	.string "wait. She settles beside\n"
	.string "Penny.$"

AzaleaTown_Text_ScrapbookScene2:
	.string "Bijuu tilts her head like\n"
	.string "Hoothoot. He copies her\p"
	.string "in return.\p"
	.string "Penny waits. Nobody calls\n"
	.string "him over. After a while,\p"
	.string "Hoothoot hops a little\n"
	.string "closer.$"

AzaleaTown_Text_ScrapbookScene3:
	.string "Hoothoot settles beside\n"
	.string "Penny. Her tail gives a\p"
	.string "tiny wag.\p"
	.string "The youngster smiles. I\n"
	.string "thought a legendary visit\p"
	.string "would be louder than this!$"

AzaleaTown_Text_ScrapbookReport:
	.string "Tell the scrapbook boy in\n"
	.string "Cherrygrove about today.\p"
	.string "Penny's quiet kindness is\n"
	.string "worth a page.$"

AzaleaTown_Text_ScrapbookRemember:
	.string "Hoothoot still looks for\n"
	.string "Penny when we walk here. I\p"
	.string "tell people the girls are\n"
	.string "good company.\p"
	.string "They always ask who won. I\n"
	.string "tell them nobody needed\p"
	.string "to.$"

AzaleaTown_Text_ScrapbookNotReady:
	.string "Let us meet after your Gym\n"
	.string "challenge. I will have\p"
	.string "time for a quiet visit\n"
	.string "then.$"

AzaleaTown_Text_ScrapbookDeclined:
	.string "Another time is fine. A\n"
	.string "quiet visit should never\p"
	.string "be a chore.$"


AzaleaTown_EventScript_ScrapbookNeighbor::
	msgbox AzaleaTown_Text_ScrapbookNeighbor, MSGBOX_DEFAULT
	return

AzaleaTown_Text_ScrapbookNeighbor:
	.string "That boy's Hoothoot has\n"
	.string "been coming closer lately.\p"
	.string "He says Penny gave him\n"
	.string "time instead of a command.\p"
	.string "I like that sort of\n"
	.string "legend.$"


AzaleaTown_RiftAtmosphere::
	msgbox AzaleaTown_RiftAtmosphereText, MSGBOX_DEFAULT
	closemessage
	release
	end
AzaleaTown_RiftAtmosphereText:
	.string "The woods feel different.\nEven the leaves fall slow.\pI took a wrong turn today.\nSomehow, I felt safe.$"
