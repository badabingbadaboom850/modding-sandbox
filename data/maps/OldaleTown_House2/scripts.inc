OldaleTown_House2_MapScripts::
	.byte 0

OldaleTown_House2_EventScript_Woman::
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end

OldaleTown_House2_EventScript_Man::
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

OldaleTown_House2_Text_PokemonLevelUp:
	.string "When Pokémon battle, they eventually\n"
	.string "level up and become stronger.\p"
	.string "Penny calls this 'getting more powerful\n"
	.string "without losing your adorable face.'\p"
	.string "Riko says the best level-up reward is\n"
	.string "being told how fluffy she looks.$""

OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon:
	.string "If the Pokémon with you become\n"
	.string "stronger, you'll be able to go farther\l"
	.string "away from here.\p"
	.string "Bijuu says strong Pokémon are useful.\n"
	.string "It immediately tries to copy them.\p"
	.string "Nobody is sure whether it is learning\n"
	.string "or simply collecting secrets.$""

