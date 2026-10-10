
.set LOCALID_LASS, 2
.set LOCALID_SILVER, 3

NewBarkTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_LOAD, NewBarkTown_OnLoad
	.byte 0

NewBarkTown_OnLoad::
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN
	end

NewBarkTown_OnFrame::
	map_script_2 VAR_NEWBARK_TOWN_STATE, 6, NewBarkTown_EventScript_ElmCallAfterLeague
	map_script_2 VAR_NEWBARK_TOWN_STATE, 11, NewBarkTown_EventScript_ArcherArcadeCall
    map_script_2 VAR_RIVAL_STATE, 0, NewBarkTown_EventScript_RivalIntro
    map_script_2 VAR_RIVAL_STATE, 2, NewBarkTown_EventScript_RivalBattle
	map_script_2 VAR_TEMP_9, TRUE, TrioStorySpirit_BijuuSightingCall
	.2byte 0

NewBarkTown_EventScript_ElmCallAfterLeague::
	lock
	pokenavcall BlackthornCity_Text_ElmCall
	waitmessage
	delay 30
	setvar VAR_NEWBARK_TOWN_STATE, 7
	setvar VAR_NEWBARKTOWN_LABSTATE, 10
	release
	end

NewBarkTown_OnTransition::
    call Common_EventScript_SetupRivalGfxId
	call TrioStorySpirit_PrepareBijuuSighting
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_Set_TalkToElm
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_Set_TalkToMom
	end

NewBarkTown_Set_TalkToElm::
	clearflag FLAG_HIDE_SILVER_NEWBARKTOWN
	setobjectxyperm LOCALID_LASS, 0, 11
	callnative SetTimeBasedEncounters
	end

NewBarkTown_Set_TalkToMom::
	setobjectxyperm LOCALID_LASS, 0, 11
	callnative SetTimeBasedEncounters
	end

NewBarkTown_EventScript_LabSign::
	msgbox NewBarkTown_Text_LabSign, MSGBOX_SIGN
	end

NewBarkTown_EventScript_TownSign::
	msgbox NewBarkTown_Text_Sign, MSGBOX_SIGN
	closemessage
	end


NewBarkTown_EventScript_Lass::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LassState2
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 3, NewBarkTown_EventScript_LassState3
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LassState4
	msgbox NewBarkTown_Text_LassState5, MSGBOX_DEFAULT
	closemessage
	release
	end
	
NewBarkTown_EventScript_LassState2::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	waitmovement 0
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_LassState3::
	msgbox NewBarkTown_Text_LassState3, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_LassState4::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	waitmovement 0
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Wooper::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WOOPER, CRY_MODE_NORMAL
	msgbox NewBarkTown_Text_Wooper, MSGBOX_DEFAULT
	waitmoncry
	release
	end

NewBarkTown_EventScript_LeaveTrigger::
	lock
	call_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LeaveTriggersState2
	call_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LeaveTriggersState4
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerStepBack
	waitmovement 0
	release
	end

NewBarkTown_EventScript_LeaveTriggersState2::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
	waitmovement 0
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
	closemessage
	return

NewBarkTown_EventScript_LeaveTriggersState4::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
	waitmovement 0
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
	closemessage
	return 



NewBarkTown_EventScript_FatMan::
	lock
	faceplayer
	call TrioFestival_TestShuttle
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_FatManState2
	goto_if_set FLAG_BADGE01_GET, NewBarkTown_Text_FatManState3_TrioWorld1_After
	msgbox NewBarkTown_Text_FatManState3, MSGBOX_DEFAULT
	goto NewBarkTown_Text_FatManState3_TrioWorld1_Resume
NewBarkTown_Text_FatManState3_TrioWorld1_After:
	msgbox NewBarkTown_Text_FatManState3_TrioWorldAfter, MSGBOX_DEFAULT
NewBarkTown_Text_FatManState3_TrioWorld1_Resume:
	call TrioStorySpirit_Rumors
	closemessage
	release
	end

NewBarkTown_EventScript_FatManState2::
	msgbox NewBarkTown_Text_FatManState2, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Silver::
	lock
	msgbox NewBarkTown_Text_Silver1, MSGBOX_DEFAULT
	delay 60
	playse SE_PIN
	applymovement LOCALID_SILVER, Common_Movement_ExclamationMark
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_Silver2, MSGBOX_DEFAULT
	playse SE_BANG
	applymovement LOCALID_SILVER, NewBarkTown_Movement_SilverPushesPlayer
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerPushedBySilver
	waitmovement 0
	applymovement LOCALID_SILVER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	waitmovement 0
	release
	end


NewBarkTown_EventScript_Door::
	msgbox NewBarkTown_Text_Door, MSGBOX_SIGN
	end

NewBarkTown_EventScript_TestMan1::
	givebp 4
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	end

NewBarkTown_EventScript_TestMan2::
	setvar VAR_NEWBARK_TOWN_STATE, 4
	setflag FLAG_HIDE_MOMS_FRIEND
	setflag FLAG_ADVENTURE_STARTED
	setflag FLAG_HIDE_SILVER_NEWBARKTOWN
	end

NewBarkTown_EventScript_TestMan3::
	setvar VAR_NEWBARK_TOWN_STATE, 5
	
	clearflag FLAG_COMPLETED_AERODACTYL_PUZZLE
	clearflag FLAG_COMPLETED_HOOH_PUZZLE
	clearflag FLAG_COMPLETED_KABUTO_PUZZLE
	clearflag FLAG_COMPLETED_OMANYTE_PUZZLE
	end

NewBarkTown_Movement_SilverPushesPlayer:
	walk_fast_left
	walk_fast_left
	walk_fast_down
	face_down
	lock_facing_direction
	unlock_facing_direction
	walk_fast_up
	walk_fast_right
	walk_fast_right
	step_end


NewBarkTown_Movement_PlayerPushedBySilver:
	walk_fast_left
	face_up
	walk_fast_down
	face_up
	lock_facing_direction
	jump_2_down
	unlock_facing_direction
	face_down
	step_end

	


NewBarkTown_Movement_FaceDown:
	face_down
	step_end

NewBarkTown_Text_LabSign:
	.string "Prof. Elm's Lab$"

NewBarkTown_Text_Door:
	.string "The door is locked.$"

NewBarkTown_Text_Wooper:
	.string "Wooper: Woooooop.$"

NewBarkTown_Text_FatManState2:
	.string "Wow, your Pokégear is impressive!\n"
	.string "Did your mom get it for you?\p"
	.string "A trainer left town with\n"
	.string "Riko, Penny, and Bijuu. I\p"
	.string "packed one sandwich for\n"
	.string "the road. Riko inspected\p"
	.string "all three pockets.$"

NewBarkTown_Text_FatManState3:
	.string "Yo, {PLAYER}!\p"
	.string "I hear Prof Elm found some\n"
	.string "new Pokemon.\p"
	.string "Travelers saw three rare\n"
	.string "Pokemon on Route 31.\p"
	.string "A shy cat was with them.\n"
	.string "She slipped into the grass.\p"
	.string "Riko treats this road like\n"
	.string "a parade. Penny checks\p"
	.string "that nobody falls behind.\n"
	.string "Bijuu copies the marching\p"
	.string "feet.$"


NewBarkTown_Text_FatManState3_TrioWorldAfter:
	.string "Yo, {PLAYER}!\p"
	.string "I hear Prof Elm found some\n"
	.string "new Pokemon.\p"
	.string "Travelers saw three rare\n"
	.string "Pokemon on Route 31.\p"
	.string "A shy cat was with them.\n"
	.string "She slipped into the grass.\p"
	.string "Falkner stood his ground\n"
	.string "against those girls! That\p"
	.string "trainer from our town\n"
	.string "really knows how to bring\p"
	.string "out their best.$"

NewBarkTown_Text_LassState2:
	.string "Wait, {PLAYER}!\p"
	.string "It's dangerous to go out\n"
	.string "without a Pokémon!\p"
	.string "Wild Pokémon jump out of the grass\n"
	.string "on the way to the next town.\p"
	.string "Penny used to keep her\n"
	.string "distance. Now she watches\p"
	.string "the road beside her\n"
	.string "sisters. A quiet change\p"
	.string "can be a big one.$"

NewBarkTown_Text_LassState3:
	.string "Oh! Your Pokémon is adorable!\n"
	.string "I wish I had one!\p"
	.string "The trio has a trainer\n"
	.string "now? I thought Riko would\p"
	.string "insist on being in charge!$"

NewBarkTown_Text_LassState4:
	.string "Hi, {PLAYER}! Leaving again?\p"
	.string "You should tell your mom if\n"
	.string "you are leaving.\p"
	.string "There's a story going around about\n"
	.string "a cat between Cherrygrove and\p"
	.string "Violet. A few trainers say she\n"
	.string "follows them, then slips away.\p"
	.string "I heard a mysterious\n"
	.string "trainer is heading toward\p"
	.string "Violet with three little\n"
	.string "legends. I hope they\p"
	.string "packed extra snacks.$"

NewBarkTown_Text_LassState5:
	.string "Call your mom on your Pokégear\n"
	.string "to let her know how you're doing.$\p"
	.string "Bijuu copies the lab's\n"
	.string "door chime. Riko answers\p"
	.string "every time. Penny knows\n"
	.string "better, but goes along for\p"
	.string "company.$"

NewBarkTown_Text_Silver1:
	.string ". . .\p"
	.string "So this is the famous Elm\n"
	.string "Pokémon Lab…$"

NewBarkTown_Text_Silver2:
	.string "…What are you staring at?$"

NewBarkTown_Text_Sign:
	.string "New Bark Town\p"
	.string "The Town Where the Winds of\n"
	.string "a New Beginning Blow$"

NewBarkTown_EventScript_PlayersHouseMailbox::
	lockall
	msgbox NewBarkTown_Text_PlayersHouse, MSGBOX_SIGN
	call RikoCavern_TestOffer
	releaseall
	end

NewBarkTown_EventScript_ElmsHouseMailbox::
	msgbox NewBarkTown_Text_ElmsHouse, MSGBOX_SIGN
	end

NewBarkTown_Text_PlayersHouse:
	.string "{PLAYER}'s House$"

NewBarkTown_Text_ElmsHouse:
	.string "Prof. Elm's House$"

NewBarkTown_EventScript_RivalIntro::
	lock
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_0
	waitmovement 0
	playse SE_WALL_HIT
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_2
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_3
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_3
	playse SE_LEDGE
	waitmovement 0
	playbgm MUS_HG_LYRA, TRUE
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_4
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, Common_Movement_ExclamationMark
	playse SE_PIN
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_5
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_6
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_7
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_7
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_8
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_9
	waitmovement 0
	setflag FLAG_HIDE_NEWBARK_RIVALMARILL
	removeobject LOCALID_NEWBARK_RIVAL
	removeobject LOCALID_NEWBARK_MARILL
	removeobject LOCALID_NEWBARK_MARILL2
	setvar VAR_RIVAL_STATE, 1
	fadedefaultbgm
	release
	end


NewBarkTown_EventScript_RivalBattle::
	lock
	playbgm MUS_HG_LYRA, TRUE
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_0
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_0
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_1
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalBattle_Movement_2
	waitmovement LOCALID_NEWBARK_MARILL2
	applymovement LOCALID_NEWBARK_RIVAL, Common_Movement_ExclamationMark
	playse SE_PIN
	waitmovement 0
	applymovement LOCALID_PLAYER, NewBarkTown_EventScript_RivalBattle_Movement_3
	waitmovement 0
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_5
	waitmovement 0
	createfieldmugshotrival
	msgbox NewBarkTown_EventScript_RivalBattle_Text_0
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_EventScript_RivalBattle_Movement_4
	playse SE_BALL_OPEN
	waitmovement 0
	bufferleadmonspeciesname STR_VAR_1
	msgbox NewBarkTown_EventScript_RivalBattle_Text_1
	msgbox NewBarkTown_EventScript_RivalBattle_Text_2
	msgbox NewBarkTown_EventScript_RivalBattle_Text_3
	msgbox NewBarkTown_EventScript_RivalBattle_Text_4
	msgbox NewBarkTown_EventScript_RivalBattle_Text_5
	setflag FLAG_NO_WHITEOUT
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq NewBarkTown_EventScript_RivalBattle_2
	trainerbattle_no_intro TRAINER_RIVALGOLD1, NewBarkTown_EventScript_RivalBattle_Text_6
NewBarkTown_EventScript_RivalBattle_1:
	clearflag FLAG_NO_WHITEOUT
	special HealPlayerParty
	createfieldmugshotrival
	msgbox NewBarkTown_EventScript_RivalBattle_Text_7
	msgbox NewBarkTown_EventScript_RivalBattle_Text_8
	removefieldmugshot
	closemessage
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalBattle_Movement_5
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_6
	waitmovement 0
	removeobject LOCALID_NEWBARK_RIVAL
	removeobject LOCALID_NEWBARK_MARILL
	removeobject LOCALID_NEWBARK_MARILL2
	fadedefaultbgm
	setvar VAR_RIVAL_STATE, 3
	release
	end

NewBarkTown_EventScript_RivalBattle_2:
	trainerbattle_no_intro TRAINER_RIVALCRYSTAL1, NewBarkTown_EventScript_RivalBattle_Text_6
	goto NewBarkTown_EventScript_RivalBattle_1


RivalsMailbox::
	lock
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq RivalsMailbox_2
	msgbox RivalsMailbox_Text_1
RivalsMailbox_1:
	release
	end

RivalsMailbox_2:
	msgbox RivalsMailbox_Text_0
	goto RivalsMailbox_1


NewBarkTown_EventScript_ArcherArcadeCall::
	lock
	pokenavcall NewBarkTown_EventScript_ArcherArcadeCall_Text_0
	waitmessage
	delay 30
	setvar VAR_NEWBARK_TOWN_STATE, 12
	release
	end


NewBarkTown_EventScript_RivalIntro_Movement_0:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_1:
	jump_down
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_2:
	walk_up
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_3:
	jump_in_place_up
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_4:
	walk_right
	walk_right
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_5:
	face_left
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_6:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_7:
	jump_in_place_left
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_8:
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_9:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_0:
	jump_in_place_right
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_1:
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_down
	face_left
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_2:
	face_up
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_3:
	walk_down
	walk_down
	walk_down
	walk_right
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_4:
	walk_fast_left
	face_right
	exit_pokeball
	set_visible
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_5:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_6:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

NewBarkTown_EventScript_RivalBattle_Text_0:
	.string "{PLAYER}!$"

NewBarkTown_EventScript_RivalBattle_Text_1:
	.string "So you picked...\n"
	.string "a {STR_VAR_1}!$"

NewBarkTown_EventScript_RivalBattle_Text_2:
	.string "That's a cute Pokémon you have!\p"
	.string "I've got three Fidoughs of my own.\n"
	.string "Let's see which team is stronger!$"

NewBarkTown_EventScript_RivalBattle_Text_3:
	.string "When you walk with it, it'll become\n"
	.string "more friendly!$"

NewBarkTown_EventScript_RivalBattle_Text_4:
	.string "You should turn around and talk to it\n"
	.string "sometimes, too.$"

NewBarkTown_EventScript_RivalBattle_Text_5:
	.string "Hey, why don't we have a battle?\n"
	.string "That's what trainers usually do when\l"
	.string "they meet!$"

NewBarkTown_EventScript_RivalBattle_Text_6:
	.string "You did really well, {PLAYER}!$"

NewBarkTown_EventScript_RivalBattle_Text_7:
	.string "That was really fun, and both of our\n"
	.string "Pokémon did their best!$"

NewBarkTown_EventScript_RivalBattle_Text_8:
	.string "You got a task from Elm right?\n"
	.string "I'll leave you to it then.\l"
	.string "See ya!$"

RivalsMailbox_Text_0:
	.string "Crystal's house$"

RivalsMailbox_Text_1:
	.string "Gold's house$"

NewBarkTown_EventScript_ArcherArcadeCall_Text_0:
	.string "???: Greetings, {PLAYER}.\p"
	.string "This is Archer speaking.\p"
	.string "Archer: I've heard of your victory\n"
	.string "in the League and would like to \l"
	.string "offer you an invitation to our \l"
	.string "newly opened Rocket Arcade.\p"
	.string "If you are interested in gambling\n"
	.string "your way to the top, come visit us\l"
	.string "in the Goldenrod Underground.\p"
	.string "I assure you no tricks or traps are\n"
	.string "planned for you this time.$"

@ Repeatable pilot quiz. Update question text and YES/NO checks together.
NewBarkTown_EventScript_TrioTrivia::
	lock
	faceplayer
	msgbox NewBarkTown_Text_TrioTriviaOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NewBarkTown_EventScript_TrioTriviaDecline
	msgbox NewBarkTown_Text_TrioTriviaQuestion1, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, NewBarkTown_EventScript_TrioTriviaWrong
	msgbox NewBarkTown_Text_TrioTriviaQuestion2, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, NO, NewBarkTown_EventScript_TrioTriviaWrong
	msgbox NewBarkTown_Text_TrioTriviaQuestion3, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, NewBarkTown_EventScript_TrioTriviaWrong
	msgbox NewBarkTown_Text_TrioTriviaWin, MSGBOX_DEFAULT
	giveitem ITEM_POTION, 1
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_EventScript_TrioTriviaBagFull
	goto NewBarkTown_EventScript_TrioTriviaFinish

NewBarkTown_EventScript_TrioTriviaWrong::
	msgbox NewBarkTown_Text_TrioTriviaWrong, MSGBOX_DEFAULT
	goto NewBarkTown_EventScript_TrioTriviaFinish

NewBarkTown_EventScript_TrioTriviaDecline::
	msgbox NewBarkTown_Text_TrioTriviaDecline, MSGBOX_DEFAULT
	goto NewBarkTown_EventScript_TrioTriviaFinish

NewBarkTown_EventScript_TrioTriviaBagFull::
	msgbox NewBarkTown_Text_TrioTriviaBagFull, MSGBOX_DEFAULT

NewBarkTown_EventScript_TrioTriviaFinish::
	closemessage
	release
	end

NewBarkTown_Text_TrioTriviaOffer:
	.string "Hello! I host a little\n"
	.string "quiz about the girls.\p"
	.string "Three right answers earn\n"
	.string "one small Wawa!\p"
	.string "You can play again!\n"
	.string "Want to give it a try?$"

NewBarkTown_Text_TrioTriviaQuestion1:
	.string "Question one!\p"
	.string "Is Riko a Pomeranian?$"

NewBarkTown_Text_TrioTriviaQuestion2:
	.string "Question two!\p"
	.string "Is Bijuu a dachshund?$"

NewBarkTown_Text_TrioTriviaQuestion3:
	.string "Question three!\p"
	.string "Does Penny love chicken?$"

NewBarkTown_Text_TrioTriviaWin:
	.string "Three out of three!\n"
	.string "You know your girls!\p"
	.string "Here is a small Wawa\n"
	.string "for your clever team.$"

NewBarkTown_Text_TrioTriviaWrong:
	.string "Oops! That was not right.\n"
	.string "No worries, try again!\p"
	.string "Talk to me to start over.$"

NewBarkTown_Text_TrioTriviaDecline:
	.string "Another time, then!\n"
	.string "Give the girls my love.$"

NewBarkTown_Text_TrioTriviaBagFull:
	.string "Your Bag has no room!\p"
	.string "Make some space, then\n"
	.string "try my quiz again.$"
