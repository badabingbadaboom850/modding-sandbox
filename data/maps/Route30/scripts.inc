.set LOCALID_ROUTE_30_JOEY, 6

Route30_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route30_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route30_OnFrame
	.byte 0

Route30_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route30_OnFrame::
	map_script_2 VAR_CHERRYGROVE_CITY_STATE, 2, Route30_EventScript_ElmCall_Trigger
	.2byte 0
	
Route30_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Route30_EventScript_Boy2
	msgbox Route30_Text_YoungsterDirectionsToMrPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Boy2::
	lock
	faceplayer
	msgbox Route30_Text_YoungsterEveryoneIsBattling, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Girl::
	lock
	faceplayer
	msgbox Route30_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Youngster_Joey_Fighting::
	lock
	msgbox Route30_Text_UseTackle, 	MSGBOX_AUTOCLOSE
	waitmessage
	playse SE_PIN
	applymovement LOCALID_ROUTE_30_JOEY, Common_Movement_QuestionMark
	delay 30
	faceplayer
	msgbox Route30_Text_ThisIsABigBattle, MSGBOX_AUTOCLOSE
	waitmessage
	turnobject LOCALID_ROUTE_30_JOEY DIR_NORTH
	release
	end


Route30_EventScript_Youngster_Joey::
	trainerbattle_single TRAINER_JOEY, Route30_Text_YoungsterJoey1Seen, Route30_Text_YoungsterJoey1Beaten
	msgbox Route30_Text_YoungsterJoey1After, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_Youngster_Mikey::
	trainerbattle_single TRAINER_MIKEY, Route30_Text_YoungsterMikeySeen, Route30_Text_YoungsterMikeyBeaten
	msgbox Route30_Text_YoungsterMikeyAfter, MSGBOX_AUTOCLOSE
	end
	
Route30_EventScript_Bugcatcher_Don::
	trainerbattle_single TRAINER_DON, Route30_Text_BugCatcherDonSeen, Route30_Text_BugCatcherDonBeaten
	msgbox Route30_Text_BugCatcherDonAfter, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_ElmCall_Trigger::
	lock
	pokenavcall Route30_Text_Elm_Disaster
	waitmessage
	delay 30
	setvar VAR_CHERRYGROVE_CITY_STATE, 3
	release
	end

Route30_EventScript_Sign::
	lock
	msgbox Route30_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route30_EventScript_TrainerTips::
	lock
	msgbox Route30_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end	

Route30_EventScript_Poliwag::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWAG, CRY_MODE_NORMAL
	msgbox Route30_Text_Poliwag, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route30_EventScript_Mailbox::
	msgbox Route30_Text_Mailbox, MSGBOX_SIGN
	end

Route30_Text_Mailbox:
	.string "Mr.Pokémon's House$"

Route30_Text_UseTackle:
	.string "Go, Rattata!\p"
	.string "Tackle!$"

Route30_Text_ThisIsABigBattle:
	.string "What? This is a big battle!\n"
	.string "Leave me alone!$"

Route30_Text_YoungsterJoey1Seen:
	.string "I just lost, so I'm trying to\n"
	.string "find more Pokémon.\p"
	.string "Wait! You look weak! Come on,\n"
	.string "let's battle!$"

Route30_Text_YoungsterJoey1Beaten:
	.string "Ack! I lost again!\n"
	.string "Doggone it!$"

Route30_Text_YoungsterJoey1After:
	.string "Do I have to have more Pokémon\n"
	.string "in order to battle better?\p"
	.string "No! I'm sticking with this one\n"
	.string "no matter what!$"

Route30_Text_YoungsterMikeySeen:
	.string "You're a Pokémon trainer,\n"
	.string "right?\p"
	.string "Then you have to battle!$"

Route30_Text_YoungsterMikeyBeaten:
	.string "That's strange.\n"
	.string "I won before.$"

Route30_Text_YoungsterMikeyAfter:
	.string "Becoming a good trainer is\n"
	.string "really tough.\p"
	.string "I'm going to battle other\n"
	.string "people to get better.$"

Route30_Text_BugCatcherDonSeen:
	.string "Instead of a bug Pokémon,\n"
	.string "I found a trainer!$"

Route30_Text_BugCatcherDonBeaten:
	.string "Argh! You're too strong!$"

Route30_Text_BugCatcherDonAfter:
	.string "I ran out of Poké Balls while\n"
	.string "I was catching Pokémon.\p"
	.string "I should've bought some more…$"

Route30_Text_YoungsterDirectionsToMrPokemon:
	.string "Mr. Pokémon's house?\n"
	.string "It's a bit farther ahead.$"

Route30_Text_YoungsterEveryoneIsBattling:
	.string "Everyone's having fun\n"
	.string "battling!\p"
	.string "You should too!$"

Route30_Text_CooltrainerF:
	.string "I'm not a trainer.\p"
	.string "But if you look one in the\n"
	.string "eyes, prepare to battle.\p"
	.string "A local says Riko once charged\n"
	.string "through here chasing a snack.\p"
	.string "She left the grass flattened in a\n"
	.string "perfect little runway!$"

Route30_Text_Sign:
	.string "Route 30\p"
	.string "Violet City - Cherrygrove City$"

Route30_Text_MrPokemonsHouseDirectionsSign:
	.string "Mr. Pokémon's House\n"
	.string "Straight Ahead!$"

Route30_Text_MrPokemonsHouseSign:
	.string "Mr. Pokémon's House$"

Route30_Text_TrainerTips:
	.string "Trainer Tips\p"
	.string "No stealing other people's\n"
	.string "Pokémon!\p"
	.string "Poké Balls are to be thrown\n"
	.string "only at wild Pokémon!$"

Route30_Text_YoungsterJoeyGiveHPUp:
	.string "I lost again…\n"
	.string "Gee, you're tough!\p"
	.string "Oh yeah, I almost forgot that\n"
	.string "I had to give you this.\p"
	.string "Use it to get even tougher,\n"
	.string "Ok?\p"
	.string "I'm going to get tougher too.$"

Route30_Text_Elm_Disaster:
	.string "Prof Elm: H-hello? {PLAYER}? It's\n"
	.string "a disaster!\p"
	.string "Uh, um, it's just terrible!\p"
	.string "What should I do? It…\n"
	.string "Oh, no…\p"
	.string "Please get back here now!$"


Route30_Text_Poliwag:
	.string "Poliwag: Wag waag!$"

Route30_EventScript_Greg::
	trainerbattle_single TRAINER_GREG_ROUTE_30, Route30_Text_GregSeen, Route30_Text_GregBeaten
	goto_if_set FLAG_GREG_WAWA_REWARDED, Route30_EventScript_Greg_AfterReward
	giveitem ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GREG_WAWA_REWARDED
	msgbox Route30_Text_GregWawa, MSGBOX_DEFAULT
	end
Route30_EventScript_Greg_AfterReward::
	goto_if_set FLAG_IS_CHAMPION, Route30_EventScript_GregChampion
	goto_if_set FLAG_BADGE08_GET, Route30_EventScript_GregLeague
	goto_if_set FLAG_BADGE03_GET, Route30_EventScript_GregGoldenrod
	msgbox Route30_Text_GregAlreadyPaid, MSGBOX_DEFAULT
	end

Route30_Text_GregSeen:
	.string "Greg: Joey has a Rattata.\n"
	.string "I have a level 99 team.\p"
	.string "That makes me the better\n"
	.string "brother!$"

Route30_Text_GregBeaten:
	.string "Greg: Bijuu copied my\n"
	.string "strategy! That is\p"
	.string "cheating!$"

Route30_Text_GregWawa:
	.string "Greg: A tiny Wawa. Almost\n"
	.string "as tiny as my chances of\p"
	.string "admitting that was fair.$"

Route30_Text_GregAlreadyPaid:
	.string "Greg: No more Wawa. I am\n"
	.string "saving up for level 100.$"


Route30_EventScript_GregChampion::
	msgbox Route30_Text_GregChampion, MSGBOX_DEFAULT
	end

Route30_Text_GregChampion:
	.string "Greg: The League let you\n"
	.string "win. I am still the final\p"
	.string "boss of this family.$"

Route30_EventScript_GregLeague::
	msgbox Route30_Text_GregLeague, MSGBOX_DEFAULT
	end

Route30_Text_GregLeague:
	.string "Greg: Eight Badges? I have\n"
	.string "six level 99 Pokemon. Six\p"
	.string "is more than eight. Wait.$"

Route30_EventScript_GregGoldenrod::
	msgbox Route30_Text_GregGoldenrod, MSGBOX_DEFAULT
	end

Route30_Text_GregGoldenrod:
	.string "Greg: Whitney cried? I\n"
	.string "would never cry over a\p"
	.string "battle. My eyes are just\n"
	.string "sweating.$"


