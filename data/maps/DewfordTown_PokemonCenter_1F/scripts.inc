DewfordTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

DewfordTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_DEWFORD_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

DewfordTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_DEWFORD_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

DewfordTown_PokemonCenter_1F_EventScript_PokefanF::
	msgbox DewfordTown_PokemonCenter_1F_Text_StoneCavern, MSGBOX_NPC
	end

DewfordTown_PokemonCenter_1F_EventScript_Man::
	msgbox DewfordTown_PokemonCenter_1F_Text_FaintedMonCanUseHM, MSGBOX_NPC
	end

DewfordTown_PokemonCenter_1F_Text_StoneCavern:
	.string "There's a stone cavern at the edge\n"
	.string "of town.\p"
	.string "I've heard you can find rare stones\n"
	.string "there.\p"
	.string "Riko would charge in dramatically.\n"
	.string "Penny would bring a snack for the trip.\p"
	.string "Bijuu would pretend it already knew\n"
	.string "what was inside the cavern.\p"
	.string "Some island elders whisper that the\n"
	.string "caverns once guarded three sleeping\l"
	.string "legends. Riko wants to wake them up.$"

DewfordTown_PokemonCenter_1F_Text_FaintedMonCanUseHM:
	.string "Even if a Pokémon faints and can't\n"
	.string "battle, it can still use a move learned\l"
	.string "from a Hidden Machine (HM).\p"
	.string "Bijuu says fainting is no reason to stop\n"
	.string "copying useful tricks.\p"
	.string "Riko would cheer, Penny would supervise,\n"
	.string "and Bijuu would ask for a rematch.$"

