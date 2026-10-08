FuchsiaCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FuchsiaCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_LOAD, FuchsiaCity_OnLoad
	.byte 0

FuchsiaCity_OnFrame::
	map_script_2 VAR_FUCHSIA_CITY_STATE, 0,  FuchsiaCity_EventScript_BaobaCall
	.2byte 0

FuchsiaCity_EventScript_CityEnter::
	end

FuchsiaCity_OnLoad::
	setrespawn HEAL_LOCATION_FUCHSIA_CITY
	end

FuchsiaCity_EventScript_BaobaCall::
	pokenavcall FuchsiaCity_Text_Baoba
	waitmessage
	delay 30
	setvar VAR_BAOBA_QUEST_STATE, 1
	setvar VAR_FUCHSIA_CITY_STATE, 1
	end

FuchsiaCity_Text_Baoba:
	.string "Warden Baoba: {PLAYER}!\p"
	.string "This is Warden Baoba.\p"
	.string "Something awful has happened!\n"
	.string "My old Safari Zone in Fuchsia City\l"
	.string "was bought out and reopened!\p"
	.string "And apparently it has exotic new\n"
	.string "Pokémon!\p"
	.string "It's hurting my business!\p"
	.string "{PLAYER}, you must venture into the\n"
	.string "new Safari Zone and catch a Pokémon\l"
	.string "to show me. I must know about these\l"
	.string "'exotic' Pokémon.\p"
	.string "Please {PLAYER}, my business depends\n"
	.string "on you!$"

FuchsiaCity_EventScript_Dratini::
	lock
	showmonpic SPECIES_DRATINI, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Kangaskhan::
	lock
	showmonpic SPECIES_KANGASKHAN, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Cubone::
	lock
	showmonpic SPECIES_CUBONE, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Omanyte::
	lock
	showmonpic SPECIES_OMANYTE, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Kabuto::
	lock
	showmonpic SPECIES_KABUTO, 10, 3
	delay 60
	hidemonpic
	release
	end

FuchsiaCity_EventScript_Youngster::
	msgbox FuchsiaCity_Text_Youngster, MSGBOX_NPC
	end

FuchsiaCity_EventScript_PokefanM::
	goto_if_set FLAG_BADGE14_GET, FuchsiaCity_Text_PokefanM_TrioWorld1_After
	msgbox FuchsiaCity_Text_PokefanM, MSGBOX_NPC
	goto FuchsiaCity_Text_PokefanM_TrioWorld1_Resume
FuchsiaCity_Text_PokefanM_TrioWorld1_After:
	msgbox FuchsiaCity_Text_PokefanM_TrioWorldAfter, MSGBOX_NPC
FuchsiaCity_Text_PokefanM_TrioWorld1_Resume:
	end

FuchsiaCity_EventScript_Teacher::
	msgbox FuchsiaCity_Text_Teacher, MSGBOX_NPC
	end

FuchsiaCity_EventScript_CitySign::
	msgbox FuchsiaCity_Text_Sign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_GymSign::
	msgbox FuchsiaCity_Text_GymSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_SafariZone::
	msgbox FuchsiaCity_Text_SafariZone, MSGBOX_NPC
	end

FuchsiaCity_Text_Youngster:
	.string "One of the Elite Four used to be\n"
	.string "the Leader of Fuchsia's Gym.\p"
	.string "Riko tried to look fierce\n"
	.string "beside a Kangaskhan. Penny\p"
	.string "said hello to the baby.\n"
	.string "Guess who got the most\p"
	.string "attention.$"

FuchsiaCity_Text_PokefanM:
	.string "Koga's daughter succeeded him as\n"
	.string "the Gym Leader after he joined the\l"
	.string "Elite Four.\p"
	.string "Janine wants a match with\n"
	.string "the trio. She says being\p"
	.string "famous does not help you\n"
	.string "spot a ninja. Bijuu may\p"
	.string "disagree.$"


FuchsiaCity_Text_PokefanM_TrioWorldAfter:
	.string "Koga's daughter succeeded him as\n"
	.string "the Gym Leader after he joined the\l"
	.string "Elite Four.\p"
	.string "Janine held her own\n"
	.string "against the girls! Their\p"
	.string "trainer had to watch\n"
	.string "carefully. Riko still\p"
	.string "cheered at every trick.$"

FuchsiaCity_Text_Teacher:
	.string "The Safari Zone is under new\n"
	.string "management.\p"
	.string "And it has tons of new Pokémon!\p"
	.string "I like the trio as a team.\n"
	.string "Riko gets them moving,\p"
	.string "Bijuu notices everything,\n"
	.string "and Penny makes sure\p"
	.string "nobody gets left behind.$"

FuchsiaCity_Text_Sign:
	.string "Fuchsia City\p"
	.string "Behold! It's Passion Pink!$"

FuchsiaCity_Text_GymSign:
	.string "Fuchsia City Pokémon Gym\n"
	.string "Leader: Janine\p"
	.string "The Poisonous Ninja Master$"

FuchsiaCity_Text_SafariZoneOfficeSign:
	.string "There's a notice here…\p"
	.string "Safari Zone Office is closed until\n"
	.string "further notice.$"

FuchsiaCity_Text_SafariZone:
	.string "Safari Zone\n"
	.string "Now Owned By\l"
	.string "Devon Corp.$"

FuchsiaCity_Text_SafariZoneClosedSign:
	.string "The Warden is traveling abroad.\p"
	.string "Therefore, the Safari Zone is\n"
	.string "closed.$"

FuchsiaCity_Text_NoLitteringSign:
	.string "No littering.\p"
	.string "Please take your waste with you.$"

