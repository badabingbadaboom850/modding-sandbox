PalletTown_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PalletTown_OnLoad
	.byte 0

PalletTown_OnLoad::
	setrespawn HEAL_LOCATION_PALLET_TOWN
	end

PalletTown_EventScript_Woman::
	msgbox PalletTown_Text_Teacher, MSGBOX_NPC
	end
PalletTown_EventScript_Fatman::
	goto_if_set FLAG_BADGE16_GET, PalletTown_Text_Fisher_TrioWorld1_After
	msgbox PalletTown_Text_Fisher, MSGBOX_NPC
	goto PalletTown_Text_Fisher_TrioWorld1_Resume
PalletTown_Text_Fisher_TrioWorld1_After:
	msgbox PalletTown_Text_Fisher_TrioWorldAfter, MSGBOX_NPC
PalletTown_Text_Fisher_TrioWorld1_Resume:
	end
PalletTown_EventScript_TownSign::
	msgbox PalletTown_Text_Sign, MSGBOX_SIGN
	end	
PalletTown_EventScript_RedsHouseSign::
	msgbox PalletTown_Text_RedsHouseSign, MSGBOX_SIGN
	end
PalletTown_EventScript_BluesHouseSign::
	msgbox PalletTown_Text_BluesHouseSign, MSGBOX_SIGN
	end	
PalletTown_EventScript_OaksLabSign::
	msgbox PalletTown_Text_OaksLabSign, MSGBOX_SIGN
	end	

PalletTown_Text_Teacher:
	.string "I'm raising Pokémon too.\p"
	.string "They serve as my private\n"
	.string "guards.\p"

	.string "Penny is longer than the line\n"
	.string "at the mailbox.\p"
	.string "I like their trainer's way\n"
	.string "of letting the girls be\p"
	.string "themselves. Riko shines,\n"
	.string "Bijuu learns, and Penny\p"
	.string "never has to rush.$"

PalletTown_Text_Fisher:
	.string "Technology is incredible!\p"
	.string "You can now trade Pokémon\n"
	.string "across time like e-mail.\p"
	.string "A trainer from Johto\n"
	.string "arrived with the trio. Oak\p"
	.string "wants notes on their\n"
	.string "strength. I want to know\p"
	.string "who carries all the\n"
	.string "snacks.$"


PalletTown_Text_Fisher_TrioWorldAfter:
	.string "Technology is incredible!\p"
	.string "You can now trade Pokémon\n"
	.string "across time like e-mail.\p"
	.string "Word says Blue stood his\n"
	.string "ground against the trio!\p"
	.string "That trainer from Johto\n"
	.string "has given Kanto plenty to\p"
	.string "talk about.$"

PalletTown_Text_Sign:
	.string "Pallet Town\p"
	.string "A Tranquil Setting of Peace\n"
	.string "& Purity$"

PalletTown_Text_RedsHouseSign:
	.string "Red's House$"

PalletTown_Text_OaksLabSign:
	.string "Oak Pokémon\n"
	.string "Research Lab$"

PalletTown_Text_BluesHouseSign:
	.string "Blue's House$"
