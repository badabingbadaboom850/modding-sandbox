.set LOCALID_NURSE, 1

CinnabarIsland_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CinnabarIsland_PokemonCenter_OnTransition
	.byte 0

CinnabarIsland_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_CINNABAR_ISLAND
	end

CinnabarIsland_PokemonCenter_EventScript_Cooltrainer::
	goto_if_set FLAG_BADGE15_GET, CinnabarIsland_PokemonCenter1F_Text_CooltrainerF_TrioWorld1_After
	msgbox CinnabarIsland_PokemonCenter1F_Text_CooltrainerF, MSGBOX_NPC
	goto CinnabarIsland_PokemonCenter1F_Text_CooltrainerF_TrioWorld1_Resume
CinnabarIsland_PokemonCenter1F_Text_CooltrainerF_TrioWorld1_After:
	msgbox CinnabarIsland_PokemonCenter1F_Text_CooltrainerF_TrioWorldAfter, MSGBOX_NPC
CinnabarIsland_PokemonCenter1F_Text_CooltrainerF_TrioWorld1_Resume:
	end

CinnabarIsland_PokemonCenter_EventScript_Fisher::
	msgbox CinnabarIsland_PokemonCenter1F_Text_Fisher, MSGBOX_NPC
	end

CinnabarIsland_PokemonCenter1F_Text_CooltrainerF:
	.string "Cinnabar Gym's Blaine apparently\n"
	.string "lives alone in the Seafoam Islands\n"
	.string "cave…\p"
	.string "Blaine wants to face the\n"
	.string "trio. A trainer brought\p"
	.string "them across the sea, and\n"
	.string "the old man has been\p"
	.string "grinning ever since.\p"
	.string "A traveler claims the\n"
	.string "girls hold every element,\p"
	.string "even unseen ones. Blaine\n"
	.string "calls it a theory worth\p"
	.string "losing his eyebrows over.$"


CinnabarIsland_PokemonCenter1F_Text_CooltrainerF_TrioWorldAfter:
	.string "Cinnabar Gym's Blaine apparently\n"
	.string "lives alone in the Seafoam Islands\n"
	.string "cave…\p"
	.string "Blaine held his own\n"
	.string "against the girls! It gave\p"
	.string "him a new story after\n"
	.string "losing his old Gym. Their\p"
	.string "trainer brought quite a\n"
	.string "spark.\p"
	.string "Blaine thinks their\n"
	.string "familiar forms are the\p"
	.string "first sparks of a bigger\n"
	.string "mystery. I think the girls\p"
	.string "would enjoy less homework.$"

CinnabarIsland_PokemonCenter1F_Text_Fisher:
	.string "It's been a year since the volcano\n"
	.string "erupted.\p"
	.string "Penny sat beside someone\n"
	.string "who lost their home here.\p"
	.string "No grand entrance, no\n"
	.string "tricks. Just company. I\p"
	.string "will remember that.$"

