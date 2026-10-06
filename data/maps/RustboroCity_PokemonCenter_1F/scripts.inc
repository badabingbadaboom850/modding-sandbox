RustboroCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

RustboroCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_RUSTBORO_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

RustboroCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_RUSTBORO_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

RustboroCity_PokemonCenter_1F_EventScript_Man::
	msgbox RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Boy::
	msgbox RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Girl::
	msgbox RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities:
	.string "My Pokémon has a Naive nature, and my\n"
	.string "friend's has a Jolly nature.\p"
	.string "It's fascinating how Pokémon have\n"
	.string "personalities!\p"
	.string "Riko is bold, Penny is cautious,\n"
	.string "and Bijuu is always observing.$"

RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon:
	.string "Just like people, there are male and\n"
	.string "female Pokémon.\p"
	.string "But no one seems to have any idea how\n"
	.string "they're different.\p"
	.string "Riko is bold, Penny is careful, and\n"
	.string "Bijuu is always studying everyone.\p"
	.string "They make a very strange research team.$"

RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor:
	.string "The man next door gave me an HM!\p"
	.string "I used it to teach my Pokémon how to\n"
	.string "Cut down skinny trees.\p"
	.string "Riko calls it making an entrance.\n"
	.string "Penny calls it clearing the path.\p"
	.string "Bijuu just copies the technique.\p"
	.string "Have you heard the old Rustboro rumor?\n"
	.string "Three legendary girls wander the region.\p"
	.string "One demands snacks, one avoids attention,\l"
	.string "and one copies anything interesting.\p"
	.string "Nobody knows where they came from - or\n"
	.string "why they always seem to be nearby.$"

