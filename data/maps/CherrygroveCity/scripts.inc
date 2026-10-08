

CherrygroveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CherrygroveCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_LOAD, CherrygroveCity_OnLoad
	.byte 0

CherrygroveCity_OnTransition::
	callnative SetTimeBasedEncounters
	end

CherrygroveCity_OnLoad::
	setrespawn HEAL_LOCATION_CHERRYGROVE_CITY
	end

CherryGroveCity_EventScript_TriggerGent_Top::
	lock
	setflag FLAG_VISITED_CHERRYGROVE_CITY
	setflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	playse SE_PIN
	applymovement LOCALID_GUIDE_GENT, Common_Movement_ExclamationMark
	delay 60
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
	waitmessage
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Top
	waitmovement 0 
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
	waitmovement 0 
	goto CherryGroveCity_EventScript_GentTour
	release
	end

CherryGroveCity_EventScript_TriggerGent_Mid::
	lock
	setflag FLAG_VISITED_CHERRYGROVE_CITY
	setflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	playse SE_PIN
	applymovement LOCALID_GUIDE_GENT, Common_Movement_ExclamationMark
	delay 60
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
	waitmessage
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
	waitmovement 0 
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	goto CherryGroveCity_EventScript_GentTour
	release
	end

CherryGroveCity_EventScript_TriggerGent_Bottom::
	lock
	setflag FLAG_VISITED_CHERRYGROVE_CITY
	setflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	playse SE_PIN
	applymovement LOCALID_GUIDE_GENT, Common_Movement_ExclamationMark
	delay 60
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
	waitmessage
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
	waitmovement 0 
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Bottom
	waitmovement 0 
	goto CherryGroveCity_EventScript_GentTour
	release
	end

CherryGroveCity_EventScript_TriggerGent_Cancel::
	msgbox CherrygroveCity_Text_GuideGentDecline, MSGBOX_DEFAULT
	closemessage
	setvar VAR_CHERRYGROVE_CITY_STATE, 1 @ CHANGE THIS TO 1 LATER
	release
	end

CherryGroveCity_EventScript_GentTour::
	playbgm MUS_HG_FOLLOW_ME_1, FALSE
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Pokecenter
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Pokecenter
	waitmovement 0
	waitmovement 0
	msgbox CherrygroveCity_Text_GuideGentPokecenter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Pokemart
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Pokemart
	waitmovement 0
	waitmovement 0
	msgbox CherrygroveCity_Text_GuideGentMart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Route30
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Route30
	waitmovement 0
	waitmovement 0
	msgbox CherrygroveCity_Text_GuideGentRoute30, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Sea
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Sea
	waitmovement 0
	waitmovement 0
	msgbox CherrygroveCity_Text_GuideGentSea, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_House_Gent
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_House_Player
	waitmovement 0
	waitmovement 0
	delay 20
	msgbox CherrygroveCity_Text_GuideGentMap, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Gent_Leave
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 20
	opendoor 42, 14
	waitdooranim
	waitmovement 0
	removeobject LOCALID_GUIDE_GENT
	closedoor 42, 14
	waitdooranim
	
	clearflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	setflag FLAG_HIDE_GUIDE_GENT_CHERRYGROVE
	setvar VAR_CHERRYGROVE_CITY_STATE, 1
	fadedefaultbgm
	release
	end

CherryGroveCity_EventScript_Fisherman::
	lock
	faceplayer
	goto_if_set FLAG_GOT_MYSTICWATER, CherryGroveCity_EventScript_Fisherman2
	msgbox CherrygroveCity_Text_MysticWaterGuyBefore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_Fisherman2
	giveitem ITEM_MYSTIC_WATER
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull 
	closemessage
	setflag FLAG_GOT_MYSTICWATER
	release
	end

CherryGroveCity_EventScript_Fisherman2::
	msgbox CherrygroveCity_Text_MysticWaterGuyAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, CherrygroveCity_Text_TeacherHaveMapCard_TrioWorld1_After
	msgbox CherrygroveCity_Text_TeacherHaveMapCard, MSGBOX_DEFAULT
	goto CherrygroveCity_Text_TeacherHaveMapCard_TrioWorld1_Resume
CherrygroveCity_Text_TeacherHaveMapCard_TrioWorld1_After:
	msgbox CherrygroveCity_Text_TeacherHaveMapCard_TrioWorldAfter, MSGBOX_DEFAULT
CherrygroveCity_Text_TeacherHaveMapCard_TrioWorld1_Resume:
	closemessage
	release
	end

CherryGroveCity_EventScript_Boy::
	lock
	faceplayer
	goto_if_ge VAR_TRIO_RESEARCH_STATE, 3, CherryGroveCity_EventScript_ScrapbookVisit
	goto_if_eq VAR_TRIO_RESEARCH_STATE, 1, CherryGroveCity_EventScript_ResearchWaiting
	goto_if_eq VAR_TRIO_RESEARCH_STATE, 2, CherryGroveCity_EventScript_ResearchTurnIn
	goto_if_set FLAG_SYS_POKEDEX_GET, CherryGroveCity_EventScript_Boy2
	msgbox CherrygroveCity_Text_YoungsterNoPokedex, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_Boy2::
	msgbox CherrygroveCity_Text_YoungsterHavePokedex, MSGBOX_DEFAULT
	goto_if_eq VAR_TRIO_RESEARCH_STATE, 3, CherryGroveCity_EventScript_ResearchFinished
	call TrioParty_CheckAny
	goto_if_eq VAR_RESULT, FALSE, CherryGroveCity_EventScript_ResearchNoBuddy
	msgbox CherryGroveCity_Text_ResearchOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_Boy2_End
	call TrioParty_CheckAny
	goto_if_eq VAR_RESULT, FALSE, CherryGroveCity_EventScript_ResearchNoBuddy
	setvar VAR_TRIO_RESEARCH_STATE, 1
	msgbox CherryGroveCity_Text_ResearchAccepted, MSGBOX_DEFAULT
CherryGroveCity_EventScript_Boy2_End::
	closemessage
	release
	end

CherryGroveCity_EventScript_ResearchNoBuddy::
	msgbox CherryGroveCity_Text_ResearchNeedBuddy, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_ResearchWaiting::
	msgbox CherryGroveCity_Text_ResearchWaiting, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_ResearchTurnIn::
	msgbox CherryGroveCity_Text_ResearchTurnIn, MSGBOX_DEFAULT
	giveitem ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, CherryGroveCity_EventScript_ResearchBagFull
	setvar VAR_TRIO_RESEARCH_STATE, 3
	msgbox CherryGroveCity_Text_ResearchThanks, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_ResearchBagFull::
	msgbox CherryGroveCity_Text_ResearchBagFull, MSGBOX_DEFAULT
	closemessage
	release
	end

CherryGroveCity_EventScript_ResearchFinished::
	msgbox CherryGroveCity_Text_ScrapbookAzaleaOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_ScrapbookEnd
	call TrioStory_CheckAll
	goto_if_eq VAR_RESULT, FALSE, CherryGroveCity_EventScript_ScrapbookNeedGirls
	setvar VAR_TRIO_RESEARCH_STATE, 4
	msgbox CherryGroveCity_Text_ScrapbookAzaleaAccepted, MSGBOX_DEFAULT
	goto CherryGroveCity_EventScript_ScrapbookEnd

CherryGroveCity_EventScript_Staryu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_STARYU, CRY_MODE_NORMAL
	msgbox CherryGroveCity_Text_Staryu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CherryGroveCity_EventScript_Corsola::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CORSOLA, CRY_MODE_NORMAL
	msgbox CherryGroveCity_Text_Corsola, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CherryGroveCity_EventScript_Krabby::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KRABBY, CRY_MODE_NORMAL
	msgbox CherryGroveCity_Text_Krabby, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CherryGroveCity_EventScript_Sign::
	lock
	msgbox CherrygroveCity_Text_CitySign, MSGBOX_SIGN
	closemessage
	release
	end	

CherryGroveCity_EventScript_TriggerSilver_Top::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Silver_Top
	waitmovement 0
	goto CherryGroveCity_EventScript_TriggerSilver
	end

CherryGroveCity_EventScript_TriggerSilver_Bottom::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Silver_Bottom
	waitmovement 0
	goto CherryGroveCity_EventScript_TriggerSilver
	end

CherryGroveCity_EventScript_TriggerSilver::
	lock
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Enter
	waitmovement 0
	createfieldmugshot MUGSHOT_SILVER
	msgbox CherrygroveCity_Text_RivalSeen, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_STARTER_MON, 0, CherryGroveCity_Silver_Battle_Cyndaquil
	goto_if_eq VAR_STARTER_MON, 1, CherryGroveCity_Silver_Battle_Totodile
	goto_if_eq VAR_STARTER_MON, 2, CherryGroveCity_Silver_Battle_Chikorita
	release
	end

CherryGroveCity_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_1, CherrygroveCity_Text_SilverWin
	goto CherryGroveCity_Silver_AfterBattle

CherryGroveCity_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_1, CherrygroveCity_Text_SilverWin
	goto CherryGroveCity_Silver_AfterBattle

CherryGroveCity_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_1, CherrygroveCity_Text_SilverWin
	goto CherryGroveCity_Silver_AfterBattle

CherryGroveCity_Silver_AfterBattle::
	playbgm MUS_HG_RIVAL_EXIT, TRUE
	createfieldmugshot MUGSHOT_SILVER
	msgbox CherrygroveCity_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Silver_Leave1Player
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Leave1
	waitmovement 0
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_CHERRYGROVE_SILVER, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_CHERRYGROVE_SILVER, DIR_EAST
	delay 60
	turnobject LOCALID_CHERRYGROVE_SILVER, DIR_SOUTH
	delay 30
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Return
	waitmovement 0
	createfieldmugshot MUGSHOT_SILVER
	msgbox CherrygroveCity_Text_RivalID, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Leave2
	waitmovement 0
	removeobject LOCALID_CHERRYGROVE_SILVER
	setflag FLAG_HIDE_SILVER_CHERRYGROVE
	setvar VAR_CHERRYGROVE_CITY_STATE, 4
	fadedefaultbgm
	release
	end

CherrygroveCity_Text_GuideGentIntro:
	.string "You're a rookie trainer,\n"
	.string "aren't you? I can tell!\p"
	.string "That's Ok! Everyone is a\n"
	.string "rookie at some point!\p"
	.string "If you'd like, I can teach\n"
	.string "you a few things.$"

CherrygroveCity_Text_GuideGentTourStart:
	.string "Ok, then!\n"
	.string "Follow me!$"

CherrygroveCity_Text_GuideGentPokecenter:
	.string "This is a Pokémon Center.\p"
	.string "They heal your Pokémon in no\n"
	.string "time at all.\p"
	.string "You'll be relying on them a lot,\n"
	.string "so you better learn about them.$"

CherrygroveCity_Text_GuideGentMart:
	.string "This is a Pokémon Mart.\p"
	.string "They sell Balls for catching wild\n"
	.string "Pokémon and other useful items.$"

CherrygroveCity_Text_GuideGentRoute30:
	.string "Route 30 is out this way.\p"
	.string "Trainers will battle their\n"
	.string "prized Pokemon there.\p"
	.string "One trainer saw three rare\n"
	.string "Pokemon on Route 31.\p"
	.string "A shy cat was with them.\n"
	.string "Then they all slipped away.$"



CherrygroveCity_Text_GuideGentSea:
	.string "This is the sea, as you can see.\p"
	.string "Some Pokémon are found only in\n"
	.string "in water.$"

CherrygroveCity_Text_GuideGentMap:
	.string "Here…\p"
	.string "It's my house! Thanks for\n"
	.string "your company.\p"
	.string "Oh, and if you're ever lost, check\n"
	.string "the Map on your Pokégear!\p"
	.string "I wish you luck on your journey!$"

CherrygroveCity_Text_GuideGentDecline:
	.string "Oh… It's something I enjoy\n"
	.string "doing…\p"
	.string "Fine. Come see me whenever\n"
	.string "you like.$"

CherrygroveCity_Text_RivalSeen:
	.string "… … … … … … … …\p"
	.string "You got a Pokémon at the Lab.\p"
	.string "What a waste.\n"
	.string "A wimp like you.\p"
	.string "… … … … … … … …\p"
	.string "Don't you get what I'm saying?\n"
	.string "Well, I too, have a good Pokémon.\p"
	.string "I'll show you what I mean!$"

CherrygroveCity_Text_SilverWin:
	.string "Humph. Are you happy you won?$"

CherrygroveCity_Text_RivalAfter:
	.string "… … … … … … … …\p"
	.string "Do you want to know who I am?\p"
	.string "I'm going to be the world's\n"
	.string "greatest Pokémon trainer.$"

CherrygroveCity_Text_RivalID:
	.string "Give it back!\n"
	.string "That's my Trainer Card!\p"
	.string "Oh no!\n"
	.string "You saw my name...$"

CherrygroveCity_Text_TeacherHaveMapCard:
	.string "When you are with Pokemon,\n"
	.string "going anywhere is fun.\p"
	.string "People returning from Route\n"
	.string "31 saw three rare Pokemon.\p"
	.string "One looked like a shy cat.\n"
	.string "No one could keep up.\p"
	.string "A traveler asked which\n"
	.string "road the trio took. I said\p"
	.string "to follow the snack\n"
	.string "crumbs. That was a joke.\p"
	.string "Mostly.$"


CherrygroveCity_Text_TeacherHaveMapCard_TrioWorldAfter:
	.string "When you are with Pokemon,\n"
	.string "going anywhere is fun.\p"
	.string "People returning from Route\n"
	.string "31 saw three rare Pokemon.\p"
	.string "One looked like a shy cat.\n"
	.string "No one could keep up.\p"
	.string "Word from Violet says\n"
	.string "Falkner made the trio work\p"
	.string "for that Badge. A legend\n"
	.string "still needs a good\p"
	.string "trainer.$"

CherrygroveCity_Text_YoungsterNoPokedex:
	.string "Mr. Pokémon's house is still\n"
	.string "farther up ahead.$"

CherrygroveCity_Text_YoungsterHavePokedex:
	.string "I battled the trainers on the\n"
	.string "road.\p"
	.string "My Pokémon lost. They're a\n"
	.string "mess! I must take them to a\l"
	.string "Pokémon Center.\p"
	.string "I heard Bijuu raced a Pidgey\n"
	.string "along Route 31.\p"
	.string "Pidgey took off first, but\n"
	.string "Bijuu was gone in a flash!$"

CherryGroveCity_Text_ResearchOffer:
	.string "I'm collecting stories about\n"
	.string "the trio from Route 31.\p"
	.string "Could you help me add a note?\n"
	.string "Ask the boy in Violet City?$"

CherryGroveCity_Text_ResearchAccepted:
	.string "Thanks! Ask the boy in Violet\n"
	.string "what the Academy has heard.\p"
	.string "Bring his note back here, and\n"
	.string "keep a trio friend with you.$"

CherryGroveCity_Text_ResearchNeedBuddy:
	.string "Come back with one of the trio\n"
	.string "traveling with you, and I'll\p"
	.string "tell you what I have so far.$"

CherryGroveCity_Text_ResearchWaiting:
	.string "The Violet City boy is near\n"
	.string "the Academy. Ask him about the\n"
	.string "trio, then bring his note\p"
	.string "back here.$"

CherryGroveCity_Text_ResearchTurnIn:
	.string "You brought the Academy's\n"
	.string "note! Thank you.\p"
	.string "Here is some Wawa for helping\n"
	.string "me finish my little research.$"

CherryGroveCity_Text_ResearchThanks:
	.string "Now we have stories from both\n"
	.string "cities. I'll keep them safe.$"

CherryGroveCity_Text_ResearchBagFull:
	.string "Your Bag is full. Make room,\n"
	.string "then come back for your small\p"
	.string "research thank-you.$"

CherryGroveCity_Text_ResearchFinished:
	.string "The trio's stories are safe in\n"
	.string "my notebook. Thanks again!$"

CherrygroveCity_Text_MysticWaterGuyBefore:
	.string "A Pokémon I caught had an\n"
	.string "item.\p"
	.string "I think it's Mystic Water.\p"
	.string "I don't need it, so do you\n"
	.string "want it?$"

CherrygroveCity_Text_MysticWaterGuyAfter:
	.string "Back to fishing for me, then.\p"
	.string "Bijuu copied my casting\n"
	.string "motion without a fishing\p"
	.string "rod. Riko watched the\n"
	.string "bait. Penny watched the\p"
	.string "horizon.$"

CherrygroveCity_Text_CitySign:
	.string "Cherrygrove City\p"
	.string "The City of Cute, Fragrant\n"
	.string "Flowers$"

CherrygroveCity_Text_GuideGentsHouseSign:
	.string "Guide Gent's House$"

CherryGroveCity_Text_Staryu:
	.string "Staryu: Yuuuuuuuu.$"

CherryGroveCity_Text_Corsola:
	.string "Corsola: Corsola! La!$"

CherryGroveCity_Text_Krabby:
	.string "Krabby: Kooookeee!$"

CherryGroveCity_Movement_Trigger_Gent:
	walk_down
	walk_left
	walk_down
	face_left
	step_end

CherryGroveCity_Movement_Trigger_Top:
	walk_down
	face_up
	step_end

CherryGroveCity_Movement_Trigger_Bottom:
	walk_up
	face_up
	step_end

CherryGroveCity_Movement_Pokecenter:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

CherryGroveCity_Movement_Pokemart:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

CherryGroveCity_Movement_Route30:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

CherryGroveCity_Movement_Sea:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

CherryGroveCity_Movement_House_Gent:
	walk_down
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

CherryGroveCity_Movement_House_Player:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end

CherryGroveCity_Movement_Gent_Leave:
	walk_up
	step_end

CherryGroveCity_Movement_Trigger_Silver_Top:
	walk_down
	face_right
	step_end

CherryGroveCity_Movement_Trigger_Silver_Bottom:
	walk_up
	face_right
	step_end

CherryGroveCity_Movement_Silver_Enter:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

CherryGroveCity_Movement_Silver_Leave1:
	delay_16
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

CherryGroveCity_Movement_Silver_Leave1Player:
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	face_up
	step_end

CherryGroveCity_Movement_Silver_Return:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_down
	step_end


CherryGroveCity_Movement_Silver_Leave2:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

CherrygroveCity_EventScript_Caleb::
	lock
	faceplayer
	msgbox CherrygroveCity_Text_Caleb, MSGBOX_DEFAULT
	goto_if_set FLAG_IS_CHAMPION, CherrygroveCity_EventScript_Caleb_Family_Champion
	goto_if_set FLAG_BADGE08_GET, CherrygroveCity_EventScript_Caleb_Family_EightBadges
	goto_if_ge VAR_TRIO_RESEARCH_STATE, 9, CherrygroveCity_EventScript_Caleb_Family_Scrapbook
	goto_if_set FLAG_BADGE03_GET, CherrygroveCity_EventScript_Caleb_Family_Goldenrod
	goto_if_set FLAG_BADGE01_GET, CherrygroveCity_EventScript_Caleb_Family_Violet
	goto CherrygroveCity_EventScript_Caleb_Family_Early

CherrygroveCity_Text_Caleb:
	.string "Nothing beats this view.$"

CherrygroveCity_EventScript_Chelsea::
	lock
	faceplayer
	msgbox CherrygroveCity_Text_Chelsea, MSGBOX_DEFAULT
	goto_if_set FLAG_IS_CHAMPION, CherrygroveCity_EventScript_Chelsea_Family_Champion
	goto_if_set FLAG_BADGE08_GET, CherrygroveCity_EventScript_Chelsea_Family_EightBadges
	goto_if_ge VAR_TRIO_RESEARCH_STATE, 9, CherrygroveCity_EventScript_Chelsea_Family_Scrapbook
	goto_if_set FLAG_BADGE03_GET, CherrygroveCity_EventScript_Chelsea_Family_Goldenrod
	goto_if_set FLAG_BADGE01_GET, CherrygroveCity_EventScript_Chelsea_Family_Violet
	goto CherrygroveCity_EventScript_Chelsea_Family_Early

CherrygroveCity_Text_Chelsea:
	.string "This is the beach I hate.$"

CherrygroveCity_EventScript_Greg::
	trainerbattle_single TRAINER_GREG_CHERRYGROVE, CherrygroveCity_Text_GregSeen, CherrygroveCity_Text_GregBeaten
	goto_if_set FLAG_GREG_WAWA_REWARDED, CherrygroveCity_EventScript_Greg_AfterReward
	giveitem ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GREG_WAWA_REWARDED
	msgbox CherrygroveCity_Text_GregWawa, MSGBOX_DEFAULT
	end
CherrygroveCity_EventScript_Greg_AfterReward::
	goto_if_set FLAG_IS_CHAMPION, CherrygroveCity_EventScript_GregChampion
	goto_if_set FLAG_BADGE08_GET, CherrygroveCity_EventScript_GregLeague
	goto_if_set FLAG_BADGE03_GET, CherrygroveCity_EventScript_GregGoldenrod
	msgbox CherrygroveCity_Text_GregAlreadyPaid, MSGBOX_DEFAULT
	end

CherrygroveCity_Text_GregSeen:
	.string "Greg: Caleb says nothing\n"
	.string "beats this view. I say\p"
	.string "nothing beats my level 99\n"
	.string "team!$"

CherrygroveCity_Text_GregBeaten:
	.string "Greg: Chelsea laughed! I\n"
	.string "demand a rematch without\p"
	.string "an audience!$"

CherrygroveCity_Text_GregWawa:
	.string "Greg: Take your tiny Wawa.\n"
	.string "Chelsea is never hearing\p"
	.string "about this.$"

CherrygroveCity_Text_GregAlreadyPaid:
	.string "Greg: Chelsea already\n"
	.string "heard. Great.$"


Cherrygrove_FadedSign::
	msgbox Cherrygrove_FadedSign_Text_0, MSGBOX_SIGN
	return


Cherrygrove_DarkraiEventDoor::
	lock
	getcaughtmon SPECIES_DARKRAI
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 4
	goto_if_eq Cherrygrove_DarkraiEventDoor_2
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 5
	goto_if_ge Cherrygrove_DarkraiEventDoor_7
Cherrygrove_DarkraiEventDoor_3:
	msgbox Cherrygrove_DarkraiEventDoor_Text_7
	release
	end

Cherrygrove_DarkraiEventDoor_2:
	msgbox Cherrygrove_DarkraiEventDoor_Text_0
	checkspecies SPECIES_CRESSELIA
	compare VAR_RESULT, FALSE
	goto_if_eq Cherrygrove_DarkraiEventDoor_12
	msgbox Cherrygrove_DarkraiEventDoor_Text_2
	dynmultichoice 20, 8, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Cherrygrove_DarkraiEventDoor_Text_3, Cherrygrove_DarkraiEventDoor_Text_4
	compare VAR_RESULT, 1
	goto_if_eq Cherrygrove_DarkraiEventDoor_14
	msgbox Cherrygrove_DarkraiEventDoor_Text_6
	release
	end

Cherrygrove_DarkraiEventDoor_6:
	compare VAR_RESULT, FALSE
	goto_if_eq Cherrygrove_DarkraiEventDoor_2
	goto Cherrygrove_DarkraiEventDoor_3

Cherrygrove_DarkraiEventDoor_7:
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 10
	goto_if_le Cherrygrove_DarkraiEventDoor_6
	goto Cherrygrove_DarkraiEventDoor_3

Cherrygrove_DarkraiEventDoor_12:
	msgbox Cherrygrove_DarkraiEventDoor_Text_1
	release
	end

Cherrygrove_DarkraiEventDoor_14:
	msgbox Cherrygrove_DarkraiEventDoor_Text_5
	closemessage
	compare VAR_DARKRAI_INN_PROGRESS, 2
	goto_if_ge Cherrygrove_DarkraiEventDoor_18
	warpwhitefade MAP_DARKRAI_INN1, 1
Cherrygrove_DarkraiEventDoor_17:
	waitstate
	end

Cherrygrove_DarkraiEventDoor_18:
	warpwhitefade MAP_DARKRAI_INN1RUINED, 28, 18
	goto Cherrygrove_DarkraiEventDoor_17


Cherrygrove_Littlegirl::
	lock
	faceplayer
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 5
	goto_if_eq Cherrygrove_Littlegirl_2
	msgbox Cherrygrove_Littlegirl_Text_1
	release
	end

Cherrygrove_Littlegirl_2:
	msgbox Cherrygrove_Littlegirl_Text_0
	release
	end


Cherrygrove_Zigzagoon::
	lock
	faceplayer
	playmoncry SPECIES_ZIGZAGOON_GALAR, CRY_MODE_NORMAL
	msgbox Cherrygrove_Zigzagoon_Text_0
	release
	end


Cherrygrove_Rattata::
	lock
	faceplayer
	playmoncry SPECIES_RATTATA_ALOLA, CRY_MODE_NORMAL
	msgbox Cherrygrove_Rattata_Text_0
	release
	end


Cherrygrove_FriendlyTrader::
	lock
	faceplayer
	goto_if_set FLAG_PICKED_ZIGZAGOON, Cherrygrove_FriendlyTrader_2
	goto_if_set FLAG_PICKED_RATTATA, Cherrygrove_FriendlyTrader_2
	goto_if_set FLAG_RECEIVED_FIRST_BALLS, Cherrygrove_FriendlyTrader_7
	msgbox Cherrygrove_FriendlyTrader_Text_7
	release
	end

Cherrygrove_FriendlyTrader_2:
	msgbox Cherrygrove_FriendlyTrader_Text_0
	release
	end

	release
	end

Cherrygrove_FriendlyTrader_7:
	msgbox Cherrygrove_FriendlyTrader_Text_1
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Cherrygrove_FriendlyTrader_Text_2, Cherrygrove_FriendlyTrader_Text_3, Cherrygrove_FriendlyTrader_Text_4
	switch VAR_RESULT
	case 0, Cherrygrove_FriendlyTrader_11
	case 1, Cherrygrove_FriendlyTrader_12
	msgbox Cherrygrove_FriendlyTrader_Text_6
	release
	end

Cherrygrove_FriendlyTrader_11:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ZIGZAGOON_GALAR
	bufferspeciesname STR_VAR_1, SPECIES_ZIGZAGOON_GALAR
	givemon SPECIES_ZIGZAGOON_GALAR, 5
	showgivemonpic 10, 3
	removeobject LOCALID_CHERRY_ZIGZAGOON
	call Common_EventScript_GiftMon
	hidemonpic
	bufferspeciesname STR_VAR_1, SPECIES_ZIGZAGOON_GALAR
	msgbox Cherrygrove_FriendlyTrader_Text_5
	release
	end

Cherrygrove_FriendlyTrader_12:
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_RATTATA_ALOLA
	bufferspeciesname STR_VAR_1, SPECIES_RATTATA_ALOLA
	givemon SPECIES_RATTATA_ALOLA, 5
	showgivemonpic 10, 3
	removeobject LOCALID_CHERRY_RATTATA
	call Common_EventScript_GiftMon
	hidemonpic
	bufferspeciesname STR_VAR_1, SPECIES_RATTATA_ALOLA
	msgbox Cherrygrove_FriendlyTrader_Text_5
	release
	end


Cherrygrove_FadedSign_Text_0:
	.string "Cherrygrove inn...\n"
	.string "The text is too faded to read.$"

Cherrygrove_DarkraiEventDoor_Text_0:
	.string "Darkrai might be residing in this \n"
	.string "old inn.\p"
	.string "It would be best to prepare for\n"
	.string "anything.$"

Cherrygrove_DarkraiEventDoor_Text_1:
	.string "You should also bring Cresselia with \n"
	.string "you.$"

Cherrygrove_DarkraiEventDoor_Text_2:
	.string "Are you absolutely sure you are ready?$"

Cherrygrove_DarkraiEventDoor_Text_3:
	.string "Prepare first$"

Cherrygrove_DarkraiEventDoor_Text_4:
	.string "Go in$"

Cherrygrove_DarkraiEventDoor_Text_5:
	.string "You grab the door handle and-$"

Cherrygrove_DarkraiEventDoor_Text_6:
	.string "Best to prepare first.$"

Cherrygrove_DarkraiEventDoor_Text_7:
	.string "The door won't budge. It seems\n"
	.string "to be stuck.$"

Cherrygrove_Littlegirl_Text_0:
	.string "I saw you dozing off in front of the\n"
	.string "old inn's door. Are you okay?$"

Cherrygrove_Littlegirl_Text_1:
	.string "That inn... I don't think it\n"
	.string "has ever been open. My mom said it was\l"
	.string "abandoned even in her youth.$"

Cherrygrove_Zigzagoon_Text_0:
	.string "Zig!$"

Cherrygrove_Rattata_Text_0:
	.string "Rat!$"

Cherrygrove_FriendlyTrader_Text_0:
	.string "Hi! Has my Pokémon been helpful?$"

Cherrygrove_FriendlyTrader_Text_1:
	.string "Hello! Are you a new trainer per chance?\p"
	.string "Listen, I received two exotic Pokémon\n"
	.string "as a gift from my uncle in the Safari\l"
	.string "Zone, but I can't keep both. \p"
	.string "Would you be willing to take one of \n"
	.string "them with you?\p"
	.string "I'm sure either one would love to go on\n"
	.string "an adventure with you!$"

Cherrygrove_FriendlyTrader_Text_2:
	.string "Zigzagoon$"

Cherrygrove_FriendlyTrader_Text_3:
	.string "Rattata$"

Cherrygrove_FriendlyTrader_Text_4:
	.string "No thanks$"

Cherrygrove_FriendlyTrader_Text_5:
	.string "Take good care of my {STR_VAR_1}!\p"
	.string "Say hi to my uncle, Baoba if you are\n"
	.string "ever visiting the Safari Zone!$"

Cherrygrove_FriendlyTrader_Text_6:
	.string "Oh... That's a shame...$"

Cherrygrove_FriendlyTrader_Text_7:
	.string "Hey! Can I ask you a favour? \p"
	.string "Wait... You don't have any\n"
	.string "Poké Balls...\p"
	.string "Sorry,\n"
	.string "I thought you were a trainer.$"

CherrygroveCity_EventScript_Caleb_Family_Champion:
	msgbox CherrygroveCity_EventScript_Caleb_Family_Text_Champion, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_Caleb_Family_End

CherrygroveCity_EventScript_Caleb_Family_Text_Champion:
	.string "Caleb: The Champion and\n"
	.string "her babies! I told\p"
	.string "everyone I knew you before\n"
	.string "Riko needed an agent.$"

CherrygroveCity_EventScript_Caleb_Family_EightBadges:
	msgbox CherrygroveCity_EventScript_Caleb_Family_Text_EightBadges, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_Caleb_Family_End

CherrygroveCity_EventScript_Caleb_Family_Text_EightBadges:
	.string "Caleb: Taking the girls to\n"
	.string "the League? We will cheer\p"
	.string "from here. Chelsea says\n"
	.string "the view is better\p"
	.string "indoors.$"

CherrygroveCity_EventScript_Caleb_Family_Scrapbook:
	msgbox CherrygroveCity_EventScript_Caleb_Family_Text_Scrapbook, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_Caleb_Family_End

CherrygroveCity_EventScript_Caleb_Family_Text_Scrapbook:
	.string "Caleb: I read the girls'\n"
	.string "scrapbook. Saving a purse\p"
	.string "sounds much more useful\n"
	.string "than Greg's training plan.$"

CherrygroveCity_EventScript_Caleb_Family_Goldenrod:
	msgbox CherrygroveCity_EventScript_Caleb_Family_Text_Goldenrod, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_Caleb_Family_End

CherrygroveCity_EventScript_Caleb_Family_Text_Goldenrod:
	.string "Caleb: Chelsea heard there\n"
	.string "are shops in Goldenrod.\p"
	.string "Suddenly our next trip has\n"
	.string "an itinerary.$"

CherrygroveCity_EventScript_Caleb_Family_Violet:
	msgbox CherrygroveCity_EventScript_Caleb_Family_Text_Violet, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_Caleb_Family_End

CherrygroveCity_EventScript_Caleb_Family_Text_Violet:
	.string "Caleb: A Badge already! I\n"
	.string "tried giving Greg a lesson\p"
	.string "in manners. He said his\n"
	.string "manners are level 99.$"

CherrygroveCity_EventScript_Caleb_Family_Early:
	msgbox CherrygroveCity_EventScript_Caleb_Family_Text_Early, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_Caleb_Family_End

CherrygroveCity_EventScript_Caleb_Family_Text_Early:
	.string "Caleb: Riko agrees with\n"
	.string "me. Chelsea and Penny are\p"
	.string "voting for somewhere with\n"
	.string "a couch.$"

CherrygroveCity_EventScript_Caleb_Family_End:
	closemessage
	release
	end


CherrygroveCity_EventScript_Chelsea_Family_Champion:
	msgbox CherrygroveCity_EventScript_Chelsea_Family_Text_Champion, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_Chelsea_Family_End

CherrygroveCity_EventScript_Chelsea_Family_Text_Champion:
	.string "Chelsea: You beat the\n"
	.string "League! I am proud of all\p"
	.string "four of you. I still hate\n"
	.string "this beach.$"

CherrygroveCity_EventScript_Chelsea_Family_EightBadges:
	msgbox CherrygroveCity_EventScript_Chelsea_Family_Text_EightBadges, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_Chelsea_Family_End

CherrygroveCity_EventScript_Chelsea_Family_Text_EightBadges:
	.string "Chelsea: Eight Badges!\n"
	.string "Penny still deserves a nap\p"
	.string "before anything else. I\n"
	.string "will defend that in court.$"

CherrygroveCity_EventScript_Chelsea_Family_Scrapbook:
	msgbox CherrygroveCity_EventScript_Chelsea_Family_Text_Scrapbook, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_Chelsea_Family_End

CherrygroveCity_EventScript_Chelsea_Family_Text_Scrapbook:
	.string "Chelsea: Bijuu found a\n"
	.string "purse? Tell her to check\p"
	.string "inside for snacks. That is\n"
	.string "what Riko would do.$"

CherrygroveCity_EventScript_Chelsea_Family_Goldenrod:
	msgbox CherrygroveCity_EventScript_Chelsea_Family_Text_Goldenrod, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_Chelsea_Family_End

CherrygroveCity_EventScript_Chelsea_Family_Text_Goldenrod:
	.string "Chelsea: Riko and I are\n"
	.string "going shopping. Caleb can\p"
	.string "watch the view until we\n"
	.string "get back.$"

CherrygroveCity_EventScript_Chelsea_Family_Violet:
	msgbox CherrygroveCity_EventScript_Chelsea_Family_Text_Violet, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_Chelsea_Family_End

CherrygroveCity_EventScript_Chelsea_Family_Text_Violet:
	.string "Chelsea: Greg brought six\n"
	.string "level 99 Pokemon. You\p"
	.string "brought the babies. Only\n"
	.string "one of you has taste.$"

CherrygroveCity_EventScript_Chelsea_Family_Early:
	msgbox CherrygroveCity_EventScript_Chelsea_Family_Text_Early, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_Chelsea_Family_End

CherrygroveCity_EventScript_Chelsea_Family_Text_Early:
	.string "Chelsea: Penny gets it.\n"
	.string "Look at her face. That is\p"
	.string "a girl who knows the value\n"
	.string "of a blanket.$"

CherrygroveCity_EventScript_Chelsea_Family_End:
	closemessage
	release
	end


CherrygroveCity_EventScript_GregChampion::
	msgbox CherrygroveCity_Text_GregChampion, MSGBOX_DEFAULT
	end

CherrygroveCity_Text_GregChampion:
	.string "Greg: The League let you\n"
	.string "win. I am still the final\p"
	.string "boss of this family.$"

CherrygroveCity_EventScript_GregLeague::
	msgbox CherrygroveCity_Text_GregLeague, MSGBOX_DEFAULT
	end

CherrygroveCity_Text_GregLeague:
	.string "Greg: Eight Badges? I have\n"
	.string "six level 99 Pokemon. Six\p"
	.string "is more than eight. Wait.$"

CherrygroveCity_EventScript_GregGoldenrod::
	msgbox CherrygroveCity_Text_GregGoldenrod, MSGBOX_DEFAULT
	end

CherrygroveCity_Text_GregGoldenrod:
	.string "Greg: Whitney cried? I\n"
	.string "would never cry over a\p"
	.string "battle. My eyes are just\n"
	.string "sweating.$"




@ States 0-3 keep the original Violet quest and its claimed reward intact.
@ 4/5/6 are Azalea accepted/report ready/reward claimed.
@ 7/8/9 are Goldenrod accepted/report ready/reward claimed.
CherryGroveCity_EventScript_ScrapbookVisit::
	msgbox CherryGroveCity_Text_ScrapbookReadOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_ScrapbookDispatch
	call CherryGroveCity_EventScript_ScrapbookRead
CherryGroveCity_EventScript_ScrapbookDispatch:
	goto_if_eq VAR_TRIO_RESEARCH_STATE, 3, CherryGroveCity_EventScript_ResearchFinished
	goto_if_eq VAR_TRIO_RESEARCH_STATE, 4, CherryGroveCity_EventScript_ScrapbookAzaleaWaiting
	goto_if_eq VAR_TRIO_RESEARCH_STATE, 5, CherryGroveCity_EventScript_ScrapbookAzaleaTurnIn
	goto_if_eq VAR_TRIO_RESEARCH_STATE, 6, CherryGroveCity_EventScript_ScrapbookGoldenrodOffer
	goto_if_eq VAR_TRIO_RESEARCH_STATE, 7, CherryGroveCity_EventScript_ScrapbookGoldenrodWaiting
	goto_if_eq VAR_TRIO_RESEARCH_STATE, 8, CherryGroveCity_EventScript_ScrapbookGoldenrodTurnIn
	msgbox CherryGroveCity_Text_ScrapbookFinished, MSGBOX_DEFAULT
	goto CherryGroveCity_EventScript_ScrapbookEnd

CherryGroveCity_EventScript_ScrapbookRead::
	msgbox CherryGroveCity_Text_ScrapbookVioletPage, MSGBOX_DEFAULT
	call_if_ge VAR_TRIO_RESEARCH_STATE, 5, CherryGroveCity_EventScript_ScrapbookReadAzalea
	call_if_ge VAR_TRIO_RESEARCH_STATE, 8, CherryGroveCity_EventScript_ScrapbookReadGoldenrod
	return

CherryGroveCity_EventScript_ScrapbookReadAzalea::
	msgbox CherryGroveCity_Text_ScrapbookAzaleaPage, MSGBOX_DEFAULT
	return

CherryGroveCity_EventScript_ScrapbookReadGoldenrod::
	msgbox CherryGroveCity_Text_ScrapbookGoldenrodPage, MSGBOX_DEFAULT
	return

CherryGroveCity_EventScript_ScrapbookAzaleaWaiting::
	msgbox CherryGroveCity_Text_ScrapbookAzaleaAccepted, MSGBOX_DEFAULT
	goto CherryGroveCity_EventScript_ScrapbookEnd

CherryGroveCity_EventScript_ScrapbookAzaleaTurnIn::
	msgbox CherryGroveCity_Text_ScrapbookAzaleaTurnIn, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_POTION
	goto_if_eq VAR_RESULT, FALSE, CherryGroveCity_EventScript_ScrapbookBagFull
	setvar VAR_TRIO_RESEARCH_STATE, 6
	msgbox CherryGroveCity_Text_ScrapbookAzaleaThanks, MSGBOX_DEFAULT
	goto CherryGroveCity_EventScript_ScrapbookEnd

CherryGroveCity_EventScript_ScrapbookGoldenrodOffer::
	msgbox CherryGroveCity_Text_ScrapbookGoldenrodOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_ScrapbookEnd
	call TrioStory_CheckAll
	goto_if_eq VAR_RESULT, FALSE, CherryGroveCity_EventScript_ScrapbookNeedGirls
	setvar VAR_TRIO_RESEARCH_STATE, 7
	msgbox CherryGroveCity_Text_ScrapbookGoldenrodAccepted, MSGBOX_DEFAULT
	goto CherryGroveCity_EventScript_ScrapbookEnd

CherryGroveCity_EventScript_ScrapbookGoldenrodWaiting::
	msgbox CherryGroveCity_Text_ScrapbookGoldenrodAccepted, MSGBOX_DEFAULT
	goto CherryGroveCity_EventScript_ScrapbookEnd

CherryGroveCity_EventScript_ScrapbookGoldenrodTurnIn::
	msgbox CherryGroveCity_Text_ScrapbookGoldenrodTurnIn, MSGBOX_DEFAULT
	giveitem ITEM_BIJUUS_POM_POMS
	goto_if_eq VAR_RESULT, FALSE, CherryGroveCity_EventScript_ScrapbookBagFull
	setvar VAR_TRIO_RESEARCH_STATE, 9
	msgbox CherryGroveCity_Text_ScrapbookGoldenrodThanks, MSGBOX_DEFAULT
	goto CherryGroveCity_EventScript_ScrapbookEnd

CherryGroveCity_EventScript_ScrapbookNeedGirls::
	msgbox CherryGroveCity_Text_ScrapbookNeedGirls, MSGBOX_DEFAULT
	goto CherryGroveCity_EventScript_ScrapbookEnd

CherryGroveCity_EventScript_ScrapbookBagFull::
	msgbox CherryGroveCity_Text_ScrapbookBagFull, MSGBOX_DEFAULT
CherryGroveCity_EventScript_ScrapbookEnd::
	closemessage
	release
	end

@ Party checks cover permanent forms. No new save variable is allocated.
TrioStory_CheckAll::
	call TrioParty_CheckRiko
	goto_if_eq VAR_RESULT, FALSE, TrioStory_CheckAll_Return
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, TrioStory_CheckAll_Return
	call TrioParty_CheckPenny
TrioStory_CheckAll_Return::
	return

CherryGroveCity_Text_ScrapbookReadOffer:
	.string "I made our notes into a\n"
	.string "little scrapbook. Want to\p"
	.string "read the pages we have?$"

CherryGroveCity_Text_ScrapbookVioletPage:
	.string "Page 1. Violet City.\p"
	.string "The Academy studied the\n"
	.string "trio. Our first notes were\p"
	.string "about their journeys and\n"
	.string "their different strengths.$"

CherryGroveCity_Text_ScrapbookAzaleaPage:
	.string "Page 2. A quiet afternoon.\p"
	.string "Penny waited beside a shy\n"
	.string "Hoothoot. Riko gave them\p"
	.string "room. Bijuu copied a\n"
	.string "gentle greeting.\p"
	.string "No battle. No cheering.\n"
	.string "Just a new friend who\p"
	.string "chose to come closer.$"

CherryGroveCity_Text_ScrapbookGoldenrodPage:
	.string "Page 3. The missing purse.\p"
	.string "Riko found the right\n"
	.string "trail. Bijuu spotted a\p"
	.string "hidden purse. Penny\n"
	.string "reached it under a hedge.\p"
	.string "Its owner was happier to\n"
	.string "get her family photo back\p"
	.string "than her money.$"

CherryGroveCity_Text_ScrapbookAzaleaOffer:
	.string "The Violet page is safe.\n"
	.string "Shall we add a quieter\p"
	.string "story from Azalea?$"

CherryGroveCity_Text_ScrapbookAzaleaAccepted:
	.string "Talk to the youngster near\n"
	.string "Azalea's southern exit\p"
	.string "after earning Bugsy's\n"
	.string "Badge.\p"
	.string "Bring all three girls. He\n"
	.string "knows a shy Pokemon who\p"
	.string "could use some company.\p"
	.string "Then come back and tell me\n"
	.string "how your visit went.$"

CherryGroveCity_Text_ScrapbookAzaleaTurnIn:
	.string "Penny made a friend? Let\n"
	.string "me write down how all\p"
	.string "three girls helped.\p"
	.string "Here is a medium Wawa for\n"
	.string "your next walk together.$"

CherryGroveCity_Text_ScrapbookAzaleaThanks:
	.string "That is our second page!\n"
	.string "Talk to me again when you\p"
	.string "want a Goldenrod story.$"

CherryGroveCity_Text_ScrapbookGoldenrodOffer:
	.string "Our next page could be a\n"
	.string "city adventure. Want to\p"
	.string "help someone in Goldenrod?$"

CherryGroveCity_Text_ScrapbookGoldenrodAccepted:
	.string "Ask the woman outside\n"
	.string "Goldenrod's Name Rater\p"
	.string "after earning Whitney's\n"
	.string "Badge.\p"
	.string "Bring the girls. She has\n"
	.string "lost something important.\p"
	.string "Return here with your\n"
	.string "story.$"

CherryGroveCity_Text_ScrapbookGoldenrodTurnIn:
	.string "The purse had a family\n"
	.string "photo inside? That belongs\p"
	.string "in our scrapbook.\p"
	.string "I found a little gift for\n"
	.string "Bijuu. She earned these\p"
	.string "Pom Poms!$"

CherryGroveCity_Text_ScrapbookGoldenrodThanks:
	.string "Three pages, three girls.\n"
	.string "Come back whenever you\p"
	.string "want to read them.\p"
	.string "There is more to a legend\n"
	.string "than winning battles.$"

CherryGroveCity_Text_ScrapbookNeedGirls:
	.string "Bring Riko, Penny, and\n"
	.string "Bijuu together for this\p"
	.string "chapter. This is their\n"
	.string "shared story.$"

CherryGroveCity_Text_ScrapbookBagFull:
	.string "Your Bag is full. Your\n"
	.string "gift is safe with me. Make\p"
	.string "room and come back.$"

CherryGroveCity_Text_ScrapbookFinished:
	.string "I still read our\n"
	.string "scrapbook. Nobody wrote\p"
	.string "down a level. They wrote\n"
	.string "down who helped.\p"
	.string "That is how I want people\n"
	.string "to remember the girls.$"

