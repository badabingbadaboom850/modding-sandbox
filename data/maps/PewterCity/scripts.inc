PewterCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PewterCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_LOAD, PewterCity_OnLoad
	.byte 0

PewterCity_EventScript_CityEnter::
	setflag FLAG_VISITED_BATTLE_TOWER
	end

PewterCity_OnLoad::
	setrespawn HEAL_LOCATION_PEWTER_CITY
	end

PewterCity_EventScript_CooltrainerF::
	msgbox PewterCity_Text_CooltrainerF, MSGBOX_NPC
	end

PewterCity_EventScript_BugCatcher::
	goto_if_set FLAG_BADGE09_GET, PewterCity_Text_BugCatcher_TrioWorld1_After
	goto_if_set FLAG_BADGE09_GET, PewterCity_Text_BugCatcher_TrioWorld2_After
	msgbox PewterCity_Text_BugCatcher, MSGBOX_NPC
	goto PewterCity_Text_BugCatcher_TrioWorld2_Resume
PewterCity_Text_BugCatcher_TrioWorld2_After:
	msgbox PewterCity_Text_BugCatcher_TrioWorldAfter, MSGBOX_NPC
PewterCity_Text_BugCatcher_TrioWorld2_Resume:
	goto PewterCity_Text_BugCatcher_TrioWorld1_Resume
PewterCity_Text_BugCatcher_TrioWorld1_After:
	msgbox PewterCity_Text_BugCatcher_TrioWorldAfter, MSGBOX_NPC
PewterCity_Text_BugCatcher_TrioWorld1_Resume:
	end

PewterCity_EventScript_Gramps::
	lock
	faceplayer
	goto_if_eq VAR_LUGIA_OR_HOOH, 1, PewterCity_EventScript_GrampsRainbowWing
	goto_if_eq VAR_LUGIA_OR_HOOH, 2, PewterCity_EventScript_GrampsSilverWing
	end

PewterCity_EventScript_GrampsRainbowWing::
	checkitem ITEM_RAINBOW_WING
	goto_if_eq VAR_RESULT, TRUE, PewterCity_EventScript_GrampsDone
	msgbox PewterCity_Text_Gramps, MSGBOX_DEFAULT
	setvar VAR_COMPLETED_HO_OH, 4
	giveitem ITEM_RAINBOW_WING
	setflag FLAG_HIDE_TINTOWER_GUARD
	closemessage
	release
	end

PewterCity_EventScript_GrampsSilverWing::
	checkitem ITEM_SILVER_WING
	goto_if_eq VAR_RESULT, TRUE, PewterCity_EventScript_GrampsDone
	msgbox PewterCity_Text_Gramps, MSGBOX_DEFAULT
	setvar VAR_COMPLETED_LUGIA, 4
	giveitem ITEM_SILVER_WING
	setflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
	closemessage
	release
	end

PewterCity_EventScript_GrampsDone::
	msgbox PewterCity_Text_Gramps_GotSilverWing, MSGBOX_DEFAULT
	closemessage
	release
	end

PewterCity_EventScript_Bugcatcher::
	goto PewterCity_EventScript_BugCatcher

PewterCity_EventScript_Cooltrainer::
	msgbox PewterCity_Text_CooltrainerF, MSGBOX_NPC
	end

PewterCity_Text_CooltrainerF:
	.string "Have you visited Pewter Gym?\p"
	.string "The Leader uses rock-type Pokémon.\p"
	.string "Riko stared at a fossil\n"
	.string "like it owed her a treat.\p"
	.string "Penny settled beside it.\n"
	.string "Bijuu copied the guide's\p"
	.string "voice.$"

PewterCity_Text_BugCatcher:
	.string "At night, Clefairy come out to play at\n"
	.string "Mt.Moon.\p"
	.string "But not every night.\p"
	.string "Brock says the trio's\n"
	.string "reputation does not change\p"
	.string "his training. I hope he\n"
	.string "knows Bijuu can copy his\p"
	.string "serious face.\p"
	.string "Museum visitors say the\n"
	.string "trio can awaken any\p"
	.string "element. Fossils cannot\n"
	.string "answer, so Bijuu supplied\p"
	.string "several opinions for them.$"


PewterCity_Text_BugCatcher_TrioWorldAfter:
	.string "At night, Clefairy come out to play at\n"
	.string "Mt.Moon.\p"
	.string "But not every night.\p"
	.string "Brock stood his ground\n"
	.string "against the trio! His\p"
	.string "defense made their trainer\n"
	.string "think. The museum kids\p"
	.string "keep reenacting the match.\p"
	.string "Brock's students think the\n"
	.string "girls' known forms are\p"
	.string "just the surface. They\n"
	.string "want to count every type.\p"
	.string "Bijuu keeps changing their\n"
	.string "answers.$"

PewterCity_Text_Gramps:
	.string "Ah, you came all the way out here from\n"
	.string "Johto?\p"
	.string "That brings back memories. When I was\n"
	.string "young, I went to Johto to train.\p"
	.string "You remind me so much of what I was like\n"
	.string "as a young man.\p"
	.string "Here. I want you to have this item I\n"
	.string "found in Johto.$"

PewterCity_Text_Gramps_GotSilverWing:
	.string "Going to new, unknown places and seeing\n"
	.string "new people…\p"
	.string "Those are the joys of travel.$"

PewterCity_EventScript_CitySign::
	msgbox PewterCity_Text_Sign, MSGBOX_NPC
	end

PewterCity_EventScript_GymSign::
	msgbox PewterCity_Text_GymSign, MSGBOX_NPC
	end

PewterCity_EventScript_MuseumSign::
	msgbox PewterCity_Text_MuseumSign, MSGBOX_NPC
	end

PewterCity_EventScript_MtMoonSign::
	msgbox PewterCity_Text_MtMoonGiftShopSign, MSGBOX_NPC
	end

PewterCity_EventScript_WelcomeSign::
	msgbox PewterCity_Text_WelcomeSign, MSGBOX_NPC
	end

PewterCity_Text_Sign:
	.string "Pewter City\n"
	.string "A Stone Gray City$"

PewterCity_Text_GymSign:
	.string "Pewter City Pokémon Gym\n"
	.string "Leader: Brock\p"
	.string "The Rock Solid Pokémon Trainer$"

PewterCity_Text_MuseumSign:
	.string "There's a notice here…\p"
	.string "Pewter Museum Of Science is closed for\n"
	.string "renovations…$"

PewterCity_Text_MtMoonGiftShopSign:
	.string "There's a notice here…\p"
	.string "Mt.Moon Gift Shop Now Open!$"

PewterCity_Text_WelcomeSign:
	.string "Welcome To Pewter City!$"

