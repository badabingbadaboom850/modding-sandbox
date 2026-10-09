
.set LOCALID_ECRUTEAK_GRAMPS, 4
.set LOCALID_ECRUTEK_SILVER, 33

EcruteakCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_LOAD, EcruteakCity_OnLoad
	.byte 0

EcruteakCity_OnTransition::
	call Common_EventScript_SetupRivalGfxId
	call TrioStorySpirit_BijuuVisibility

EcruteakCity_OnTransition_SetTime::
	callnative SetTimeBasedEncounters
	end

EcruteakCity_OnLoad::
	setrespawn HEAL_LOCATION_ECRUTEAK_CITY
	end

EcruteakCity_Test_Lugia::
	setvar VAR_LUGIA_OR_HOOH, 1
	end
EcruteakCity_Test_League::
	setvar VAR_COMPLETED_HO_OH, 4
	setvar VAR_COMPLETED_LUGIA, 4
	end


EcruteakCity_EventScript_Trigger::
	@flagheap
	clearflag FLAG_RELEASED_BEASTS
	clearflag FLAG_AMPHAROS_HEALED
	clearflag FLAG_HIDE_ECRUTEAK_BILL
	clearflag FLAG_DEFEATED_HO_OH
	clearflag FLAG_CAUGHT_HO_OH
	clearflag FLAG_DEFEATED_LUGIA
	clearflag FLAG_CAUGHT_LUGIA
	clearflag FLAG_HIDE_ECRUTEAK_ROCKET
	clearflag FLAG_HIDE_BURNED_TOWER_NPCS  
	clearflag FLAG_HIDE_BURNED_TOWER_BEASTS
	clearflag FLAG_HIDE_BURNED_TOWER_B1F_EUSINE
	clearflag FLAG_HIDE_ECRUTEAK_CITY_SAGE
	clearflag FLAG_CAUGHT_ENTEI
	clearflag FLAG_CAUGHT_RAIKOU
	clearflag FLAG_GOT_TM_SNATCH
	clearflag FLAG_HIDE_ROUTE42_SUICUNE
	clearflag FLAG_GOT_TYROGUE
	clearflag FLAG_BEAT_KIYO
	clearflag FLAG_ENABLE_BAOBA_MATCH_CALL
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI
	clearflag FLAG_HIDE_TINTOWER_GUARD
	clearflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
	clearflag FLAG_HIDE_LUGIA
	clearflag FLAG_HIDE_HO_OH

	setflag FLAG_VISITED_ECRUTEAK_CITY
	setflag FLAG_HIDE_ROUTE42_EUSINE

	setflag FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	setflag FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	setflag FLAG_HIDE_ROUTE39_SHADOW
	setflag FLAG_HIDE_ECRUTEAK_SILVER
	setvar VAR_COMPLETED_HO_OH, 0
	setvar VAR_COMPLETED_LUGIA, 0
	setvar VAR_ECRUTEAK_CITY_THEATER, 0 
	setvar VAR_ECRUTEAK_CITY_STATE, 1
	end

EcruteakCity_Trigger_Silver::
	lockall
	opendoor 39, 40
	waitdooranim
	delay 10
	clearflag FLAG_HIDE_ECRUTEAK_SILVER
	addobject LOCALID_ECRUTEK_SILVER
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	playse SE_BANG
	applymovement LOCALID_ECRUTEK_SILVER, EcruteakCity_Movement_Silver1
	applymovement OBJ_EVENT_ID_PLAYER, EcruteakCity_Movement_Silver1
	message EcruteakCity_Text_Silver1
	
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement LOCALID_ECRUTEK_SILVER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	closedoor 39, 40
	waitdooranim
	createfieldmugshot MUGSHOT_SILVER
	msgbox EcruteakCity_Text_Silver2, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_ECRUTEK_SILVER, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_ECRUTEK_SILVER, DIR_SOUTH
	createfieldmugshot MUGSHOT_SILVER
	msgbox EcruteakCity_Text_Silver3, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_ECRUTEK_SILVER, EcruteakCity_Movement_Silver2
	waitmovement LOCALID_ECRUTEK_SILVER


	setflag FLAG_HIDE_ECRUTEAK_SILVER
	removeobject LOCALID_ECRUTEK_SILVER
	fadedefaultbgm

	setvar VAR_ECRUTEAK_CITY_THEATER, 5
	releaseall
	end

EcruteakCity_Movement_Silver1:
	delay_16
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

EcruteakCity_Movement_Silver2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

EcruteakCity_Text_Silver1:
	.string "Thud!!$"

EcruteakCity_Text_Silver2:
	.string "Silver: How...? How is this\n"
	.string "possible? How can I lose to mere\l"
	.string "Kimono Girls...?$"

EcruteakCity_Text_Silver3:
	.string "Silver: You were watching me,\n"
	.string "{PLAYER}...\p"
	.string "Yeah, that's right!\p"
	.string "I never thought defeating five\n"
	.string "Kimono Girls would be so hard...\p"
	.string "I got beaten to a pulp...\p"
	.string "...\p"
	.string "You must have come here for the\n"
	.string "same reason, right?\p"
	.string "Don't get cocky just because you\n"
	.string "defeated Team Rocket!\p"
	.string "These Kimono Girls are insanely\n"
	.string "strong.\p"
	.string "See if you can defeat them.\p"
	.string "But I'm not going back, I don't\n"
	.string "want to see you win.$"

EcruteakCity_EventScript_Gramps::
	lock
	faceplayer
	goto_if_set FLAG_BADGE04_GET, EcruteakCity_Text_Gramps1_TrioWorld1_After
	msgbox EcruteakCity_Text_Gramps1, MSGBOX_DEFAULT
	goto EcruteakCity_Text_Gramps1_TrioWorld1_Resume
EcruteakCity_Text_Gramps1_TrioWorld1_After:
	msgbox EcruteakCity_Text_Gramps1_TrioWorldAfter, MSGBOX_DEFAULT
EcruteakCity_Text_Gramps1_TrioWorld1_Resume:
	call EcruteakCity_EventScript_CelestialSkeptic
	closemessage
	release
	end
		
EcruteakCity_EventScript_Lass::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Lass1, MSGBOX_DEFAULT
	call EcruteakCity_EventScript_CelestialHost
	closemessage
	release
	end

EcruteakCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RELEASED_BEASTS, EcruteakCity_EventScript_Girl2
	msgbox EcruteakCity_Text_Lass2, MSGBOX_DEFAULT
	call EcruteakCity_EventScript_CelestialTowerWitness
	closemessage
	release
	end

EcruteakCity_EventScript_Girl2::
	msgbox EcruteakCity_Text_Lass2_ReleasedBeasts, MSGBOX_DEFAULT
	call EcruteakCity_EventScript_CelestialTowerWitness
	closemessage
	release
	end

EcruteakCity_EventScrip_Man::
	lock
	faceplayer
	goto_if_set FLAG_AMPHAROS_HEALED, EcruteakCity_EventScrip_Man2
	msgbox EcruteakCity_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScrip_Man2::
	msgbox EcruteakCity_Text_Fisher_JasmineReturned, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Youngster, MSGBOX_DEFAULT
	call EcruteakCity_EventScript_CelestialMarketWitness
	closemessage
	release
	end

EcruteakCity_EventScript_SageRight::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps2, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageTower::
	lock
	faceplayer
	msgbox EcruteakCity_Text_Gramps3, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_SageGym::
	lock
	faceplayer
	msgbox EcruteakCity_Text_SageGym, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_EventScript_TheaterSign::
	lock
	msgbox EcruteakCity_Text_DanceTheaterSign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_OfficeSign::
	lock
	msgbox EcruteakCity_Text_OfficeSign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_BurnedSign::
	lock
	msgbox EcruteakCity_Text_BurnedTowerSign, MSGBOX_SIGN
	call EcruteakCity_EventScript_CelestialToySearch
	closemessage
	release
	end	

EcruteakCity_EventScript_CitySign::
	lock
	msgbox EcruteakCity_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end	

EcruteakCity_EventScript_GymSign::
	lock
	msgbox EcruteakCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

EcruteakCity_EventScript_Eevee::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_EEVEE, CRY_MODE_NORMAL
	msgbox EcruteakCity_Text_Eevee, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EcruteakCity_EventScript_Vulpix::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_VULPIX, CRY_MODE_NORMAL
	msgbox EcruteakCity_Text_Vulpix, MSGBOX_DEFAULT
	waitmoncry
	release
	end

EcruteakCity_Text_Eevee:
	.string "Eevee: Veee!$"

EcruteakCity_Text_Vulpix:
	.string "Vulpix: Vullll Pix!$"


EcruteakCity_Text_UnusedMissingDaughter:
	.string "Oh, no. Oh, no…\p"
	.string "My daughter is missing.\p"
	.string "No… She couldn't have gone to the\n"
	.string "Burned Tower.\p"
	.string "I told her not to go near it…\p"
	.string "People seem to disappear there…\p"
	.string "Oh, what should I do…?$"

EcruteakCity_Text_Gramps1:
	.string "Ecruteak used to have two towers:\n"
	.string "one each in the east and west.\p"
	.string "Morty says the trio's bond\n"
	.string "feels older than any tale.\p"
	.string "I think the important part\n"
	.string "is who they chose to walk\p"
	.string "beside.\p"
	.string "Old tales tell of three\n"
	.string "little guardians wearing\p"
	.string "every element like a\n"
	.string "cloak. Could Riko, Penny\p"
	.string "and Bijuu be their\n"
	.string "descendants?$"


EcruteakCity_Text_Gramps1_TrioWorldAfter:
	.string "Ecruteak used to have two towers:\n"
	.string "one each in the east and west.\p"
	.string "Morty stood firm against\n"
	.string "the girls. He says their\p"
	.string "trainer gave them\n"
	.string "direction without dimming\p"
	.string "their spirit.\p"
	.string "Morty wonders if their\n"
	.string "forms are glimpses of\p"
	.string "something older. I wonder\n"
	.string "if those ancient guardians\p"
	.string "also loved chicken.$"

EcruteakCity_Text_Gramps2:
	.string "Ah, child. Have you learned to\n"
	.string "dance like the Kimono Girls?\p"
	.string "If you go to their Dance Theater,\n"
	.string "an odd old man will give you\l"
	.string "something nice, I hear.\p"
	.string "People ask whether the\n"
	.string "trio is a good omen. They\p"
	.string "brought a shy girl out\n"
	.string "into the world with her\p"
	.string "sisters. Good enough for\n"
	.string "me.$"

EcruteakCity_Text_Lass1:
	.string "I'm going to practice at the Dance\n"
	.string "Theater. Care to join me?\p"
	.string "Riko stopped to watch the\n"
	.string "dancers. Bijuu learned the\p"
	.string "steps. Penny leaned\n"
	.string "against her trainer and\p"
	.string "enjoyed the music.$"

EcruteakCity_Text_Lass2:
	.string "The tower that used to be here…\p"
	.string "My grandma told me it used to be\n"
	.string "much taller.\p"
	.string "I hear there are ghosts in it now.\p"
	.string "Grandma says they used to pray to\n"
	.string "Riko for fluff to make sweaters.\p"
	.string "She would help, but only if they\n"
	.string "saved her a cozy one!$"

EcruteakCity_Text_Lass2_ReleasedBeasts:
	.string "Three big Pokémon ran off in different\n"
	.string "directions. What were they?$"

EcruteakCity_Text_Fisher:
	.string "I heard a rumor about Olivine\n"
	.string "Lighthouse.\p"
	.string "The Pokémon that serves as the\n"
	.string "beacon fell ill. Sounds like they\l"
	.string "are in trouble.$"

EcruteakCity_Text_Fisher_JasmineReturned:
	.string "The Pokémon at Olivine Lighthouse\n"
	.string "has been cured.\p"
	.string "Boats can safely sail out to sea at\n"
	.string "night again.$"

EcruteakCity_Text_Youngster:
	.string "Pokemon ran wild at the lake.\p"
	.string "I would like to see them.\p"
	.string "The dancers whisper that Bijuu\n"
	.string "learns each routine from the shadows.\p"
	.string "Once she copied every step, then\n"
	.string "bowed before anyone saw her!$"



EcruteakCity_Text_Gramps3:
	.string "In the distant past…\p"
	.string "This tower burned in a fire. Three\n"
	.string "nameless Pokémon perished in it.\p"
	.string "A rainbow-colored Pokémon descended\n"
	.string "from the sky and resurrected them…\p"
	.string "It's a legend that has been passed\n"
	.string "down by Ecruteak Gym Leaders.\p"
	.string "Me?\p"
	.string "I was a trainer way back when.\n"
	.string "Hohoho!$"

EcruteakCity_Text_SageGym:
	.string "Gym Leader Morty is not here right\n"
	.string "now. You may find him at the\l"
	.string "Burned Tower.$"

EcruteakCity_Text_Sign:
	.string "Ecruteak City\n"
	.string "A Historical City\p"
	.string "Where the Past Meets the Present$"

EcruteakCity_Text_TinTowerSign:
	.string "Tin Tower\p"
	.string "A legendary Pokémon is said to\n"
	.string "roost here.$"

EcruteakCity_Text_OfficeSign:
	.string "Barrier Station to Tin Tower\p"
	.string "No Trespassing by the Unworthy.$"

EcruteakCity_Text_GymSign:
	.string "Ecruteak City Pokémon Gym\n"
	.string "Leader: Morty\p"
	.string "The Mystic Seer of the Future$"

EcruteakCity_Text_DanceTheaterSign:
	.string "Ecruteak Dance Theater$"

EcruteakCity_Text_BurnedTowerSign:
	.string "Burned Tower\p"
	.string "It was destroyed by a mysterious\n"
	.string "fire.\p"
	.string "Please stay away, as it is unsafe.$"

EcruteakCity_RivalPostBattle::
	lock
	faceplayer
	createfieldmugshotrival
	msgbox EcruteakCity_RivalPostBattle_Text_0
	removefieldmugshot
	closemessage
	moveobjecttocoords LOCALID_ECRUTEAK_RIVAL, 8, 35, DIR_WEST
	waitmovement 0
	delay 60
	applymovement LOCALID_ECRUTEAK_RIVAL, EcruteakCity_RivalPostBattle_Movement_0
	delay 30
	createfieldmugshotrival
	msgbox EcruteakCity_RivalPostBattle_Text_1
	removefieldmugshot
	closemessage
	applymovement LOCALID_ECRUTEAK_RIVAL, EcruteakCity_RivalPostBattle_Movement_1
	waitmovement 0
	playse SE_EXIT
	delay 30
	setvar VAR_RIVAL_STATE, 8
	setflag FLAG_HIDE_ECRUTEAK_RIVAL
	clearflag FLAG_HIDE_OLIVINE_RIVAL
	removeobject LOCALID_ECRUTEAK_RIVAL
	release
	end


EcruteakCity_RivalPostBattle_Movement_0:
	face_right
	step_end

EcruteakCity_RivalPostBattle_Movement_1:
	face_left
	step_end

EcruteakCity_RivalPostBattle_Text_0:
	.string "What's up {PLAYER}?\p"
	.string "Mowing down more gyms left and right?\p"
	.string "Same as always. You're on a roll,\n"
	.string "woohoo.\p"
	.string "I can't even beat Morty yet...\p"
	.string "I'm going to train in Olivine for a while.\n"
	.string "Don't wait up.$"

EcruteakCity_RivalPostBattle_Text_1:
	.string "...You're doing really well.\n"
	.string "I mean that.$"


@ Independent optional mystery. VAR_ECRUTEAK_BIJUU_MYSTERY is persistent.
@ 0 offer; 1 investigating; 2 tower clue; 3 both clues; 4 toy found;
@ 5 actual Psychic form seen/reward pending; 6 reveal complete.
EcruteakCity_EventScript_CelestialHost::
	goto_if_ge VAR_ECRUTEAK_BIJUU_MYSTERY, 6, EcruteakCity_EventScript_CelestialHostFinished
	goto_if_eq VAR_ECRUTEAK_BIJUU_MYSTERY, 5, EcruteakCity_EventScript_CelestialReward
	goto_if_eq VAR_ECRUTEAK_BIJUU_MYSTERY, 4, EcruteakCity_EventScript_CelestialCheckReveal
	goto_if_eq VAR_ECRUTEAK_BIJUU_MYSTERY, 3, EcruteakCity_EventScript_CelestialSearchHint
	goto_if_eq VAR_ECRUTEAK_BIJUU_MYSTERY, 2, EcruteakCity_EventScript_CelestialMarketHint
	goto_if_eq VAR_ECRUTEAK_BIJUU_MYSTERY, 1, EcruteakCity_EventScript_CelestialTowerHint
	msgbox EcruteakCity_Text_CelestialOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EcruteakCity_EventScript_CelestialDecline
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, EcruteakCity_EventScript_CelestialNeedBijuu
	setvar VAR_ECRUTEAK_BIJUU_MYSTERY, 1
	msgbox EcruteakCity_Text_CelestialTowerHint, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialDecline::
	msgbox EcruteakCity_Text_CelestialDecline, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialNeedBijuu::
	msgbox EcruteakCity_Text_CelestialNeedBijuu, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialTowerHint::
	msgbox EcruteakCity_Text_CelestialTowerHint, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialMarketHint::
	msgbox EcruteakCity_Text_CelestialMarketHint, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialSearchHint::
	msgbox EcruteakCity_Text_CelestialSearchHint, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialCheckReveal::
	checkspecies SPECIES_BIJUU_PSYCHIC
	goto_if_eq VAR_RESULT, FALSE, EcruteakCity_EventScript_CelestialEvolutionHint
	msgbox EcruteakCity_Text_CelestialReveal, MSGBOX_DEFAULT
	setvar VAR_ECRUTEAK_BIJUU_MYSTERY, 5
	goto EcruteakCity_EventScript_CelestialReward

EcruteakCity_EventScript_CelestialEvolutionHint::
	msgbox EcruteakCity_Text_CelestialEvolutionHint, MSGBOX_DEFAULT
	goto EcruteakCity_EventScript_CelestialSupplies

EcruteakCity_EventScript_CelestialReward::
	giveitem ITEM_BIJUUS_CAT_NIP
	goto_if_eq VAR_RESULT, FALSE, EcruteakCity_EventScript_CelestialBagFull
	setvar VAR_ECRUTEAK_BIJUU_MYSTERY, 6
	msgbox EcruteakCity_Text_CelestialReward, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialBagFull::
	msgbox EcruteakCity_Text_CelestialBagFull, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialHostFinished::
	msgbox EcruteakCity_Text_CelestialHostFinished, MSGBOX_DEFAULT
EcruteakCity_EventScript_CelestialSupplies::
	msgbox EcruteakCity_Text_CelestialSupplies, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EcruteakCity_EventScript_CelestialReturn
	pokemart EcruteakCity_CelestialSupplies
	return

EcruteakCity_EventScript_CelestialTowerWitness::
	goto_if_ge VAR_ECRUTEAK_BIJUU_MYSTERY, 5, EcruteakCity_EventScript_CelestialBelieverAfter
	goto_if_eq VAR_ECRUTEAK_BIJUU_MYSTERY, 0, EcruteakCity_EventScript_CelestialTowerRumor
	goto_if_ge VAR_ECRUTEAK_BIJUU_MYSTERY, 2, EcruteakCity_EventScript_CelestialTowerRepeat
	msgbox EcruteakCity_Text_CelestialTowerClue, MSGBOX_DEFAULT
	setvar VAR_ECRUTEAK_BIJUU_MYSTERY, 2
	msgbox EcruteakCity_Text_CelestialMarketHint, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialTowerRumor::
	msgbox EcruteakCity_Text_CelestialTowerRumor, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialTowerRepeat::
	msgbox EcruteakCity_Text_CelestialTowerClue, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialBelieverAfter::
	msgbox EcruteakCity_Text_CelestialBelieverAfter, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialMarketWitness::
	goto_if_ge VAR_ECRUTEAK_BIJUU_MYSTERY, 5, EcruteakCity_EventScript_CelestialMarketAfter
	goto_if_eq VAR_ECRUTEAK_BIJUU_MYSTERY, 2, EcruteakCity_EventScript_CelestialMarketClue
	goto_if_ge VAR_ECRUTEAK_BIJUU_MYSTERY, 3, EcruteakCity_EventScript_CelestialMarketRepeat
	msgbox EcruteakCity_Text_CelestialMarketRumor, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialMarketClue::
	msgbox EcruteakCity_Text_CelestialMarketClue, MSGBOX_DEFAULT
	setvar VAR_ECRUTEAK_BIJUU_MYSTERY, 3
	msgbox EcruteakCity_Text_CelestialSearchHint, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialMarketRepeat::
	msgbox EcruteakCity_Text_CelestialMarketClue, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialMarketAfter::
	msgbox EcruteakCity_Text_CelestialMarketAfter, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialToySearch::
	goto_if_eq VAR_ECRUTEAK_BIJUU_MYSTERY, 3, EcruteakCity_EventScript_CelestialFindToy
	goto_if_ge VAR_ECRUTEAK_BIJUU_MYSTERY, 4, EcruteakCity_EventScript_CelestialToyGone
	return

EcruteakCity_EventScript_CelestialFindToy::
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, EcruteakCity_EventScript_CelestialNeedBijuu
	msgbox EcruteakCity_Text_CelestialFindToy, MSGBOX_DEFAULT
	giveitem ITEM_BIJUUS_FISH_TOY
	goto_if_eq VAR_RESULT, FALSE, EcruteakCity_EventScript_CelestialToyBagFull
	setvar VAR_ECRUTEAK_BIJUU_MYSTERY, 4
	msgbox EcruteakCity_Text_CelestialToyInstructions, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialToyBagFull::
	msgbox EcruteakCity_Text_CelestialToyBagFull, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialToyGone::
	msgbox EcruteakCity_Text_CelestialToyGone, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialSkeptic::
	goto_if_ge VAR_ECRUTEAK_BIJUU_MYSTERY, 5, EcruteakCity_EventScript_CelestialSkepticAfter
	msgbox EcruteakCity_Text_CelestialSkepticBefore, MSGBOX_DEFAULT
	return

EcruteakCity_EventScript_CelestialSkepticAfter::
	msgbox EcruteakCity_Text_CelestialSkepticAfter, MSGBOX_DEFAULT
EcruteakCity_EventScript_CelestialReturn::
	return

	.align 2
EcruteakCity_CelestialSupplies:
	.2byte ITEM_BIJUUS_FISH_TOY
	.2byte ITEM_BIJUUS_CAT_NIP
	pokemartlistend

EcruteakCity_Text_CelestialOffer:
	.string "People keep seeing a\n"
	.string "celestial visitor around\p"
	.string "Ecruteak.\p"
	.string "Glowing eyes. Floating\n"
	.string "stones. A silver shape\p"
	.string "that vanishes when someone\n"
	.string "calls.\p"
	.string "Will you help me find out\n"
	.string "who she is?$"

EcruteakCity_Text_CelestialDecline:
	.string "Another time, then. If the\n"
	.string "heavens ask for snacks, I\p"
	.string "will let you know.$"

EcruteakCity_Text_CelestialNeedBijuu:
	.string "Bring Bijuu along. A\n"
	.string "curious cat might notice\p"
	.string "things people miss.$"

EcruteakCity_Text_CelestialTowerHint:
	.string "Start with the woman south\n"
	.string "of Burned Tower. She saw\p"
	.string "the visitor up close.\p"
	.string "Then tell me what you\n"
	.string "find. I am beside the\p"
	.string "Eevee, south of the Dance\n"
	.string "Theater.$"

EcruteakCity_Text_CelestialTowerClue:
	.string "I saw pebbles hovering\n"
	.string "beside a cat-shaped glow.\p"
	.string "Then a treat bag rustled.\n"
	.string "The glow turned its head\p"
	.string "before I even opened it!\p"
	.string "Bijuu looks very\n"
	.string "interested in that part of\p"
	.string "my story.$"

EcruteakCity_Text_CelestialMarketHint:
	.string "Ask the boy east of the\n"
	.string "Gym, near the city's\p"
	.string "southern edge. He saw her\n"
	.string "leave.$"

EcruteakCity_Text_CelestialMarketClue:
	.string "The visitor was dragging a\n"
	.string "little fish-shaped toy.\p"
	.string "She left paw prints all\n"
	.string "the way to the Burned\p"
	.string "Tower notice board.\p"
	.string "A celestial being with a\n"
	.string "favorite toy? That is my\p"
	.string "kind of legend.$"

EcruteakCity_Text_CelestialSearchHint:
	.string "Inspect the Burned Tower\n"
	.string "sign, just beside its\p"
	.string "entrance. Look behind the\n"
	.string "notice board.\p"
	.string "Take Bijuu. She seems to\n"
	.string "know exactly what we are\p"
	.string "looking for.$"

EcruteakCity_Text_CelestialTowerRumor:
	.string "A celestial visitor keeps\n"
	.string "appearing near the tower.\p"
	.string "The woman beside the Eevee\n"
	.string "is collecting sightings.\p"
	.string "She might want your help.$"

EcruteakCity_Text_CelestialMarketRumor:
	.string "A glowing shape dragged a\n"
	.string "toy through town. It made\p"
	.string "a very ordinary squeak.\p"
	.string "Ask the woman beside the\n"
	.string "Eevee about her\p"
	.string "investigation.$"

EcruteakCity_Text_CelestialFindToy:
	.string "Behind the notice board,\n"
	.string "you find a soft fish toy.\p"
	.string "Bijuu presses her nose to\n"
	.string "it. A pebble lifts, then\p"
	.string "drops. Riko jumps. Penny\n"
	.string "blinks.$"

EcruteakCity_Text_CelestialToyInstructions:
	.string "You found Bijuu's Fish\n"
	.string "Toy!\p"
	.string "Open the Bag's Items\n"
	.string "pocket and use it on Bijuu\p"
	.string "in her original form.\p"
	.string "Bring her back to the\n"
	.string "woman beside the Eevee.\p"
	.string "The toy may help her\n"
	.string "focus.$"

EcruteakCity_Text_CelestialToyBagFull:
	.string "There is no room in your\n"
	.string "Bag. The fish toy stays\p"
	.string "behind the sign until you\n"
	.string "return.$"

EcruteakCity_Text_CelestialToyGone:
	.string "Only paw prints remain\n"
	.string "behind the notice board.\p"
	.string "Bijuu seems very pleased\n"
	.string "with her little secret.$"

EcruteakCity_Text_CelestialEvolutionHint:
	.string "Try using the Fish Toy on\n"
	.string "Bijuu from the Bag. It\p"
	.string "works on her original\n"
	.string "form.\p"
	.string "Return with her in Psychic\n"
	.string "form. I want to see what\p"
	.string "she has been hiding.$"

EcruteakCity_Text_CelestialReveal:
	.string "Those eyes! The floating\n"
	.string "stones! Bijuu, it was you\p"
	.string "all along!\p"
	.string "The fish toy helps her\n"
	.string "focus the power she had\p"
	.string "been showing in little\n"
	.string "bursts.\p"
	.string "Bijuu lifts the toy. Then\n"
	.string "she looks straight at the\p"
	.string "woman's treat bag.\p"
	.string "Riko sits up for a snack.\n"
	.string "Penny stays beside her.\p"
	.string "The celestial being wants\n"
	.string "lunch.$"

EcruteakCity_Text_CelestialReward:
	.string "This catnip can return\n"
	.string "Bijuu to her original\p"
	.string "form.\p"
	.string "Either way, she is still\n"
	.string "your girl. The power was\p"
	.string "hers. The choice is yours.$"

EcruteakCity_Text_CelestialBagFull:
	.string "Your Bag is full. I will\n"
	.string "keep Bijuu's catnip here.\p"
	.string "Come back when there is\n"
	.string "room.$"

EcruteakCity_Text_CelestialHostFinished:
	.string "Ecruteak's celestial\n"
	.string "visitor was Bijuu all\p"
	.string "along.\p"
	.string "I asked her for a\n"
	.string "prophecy. She predicted I\p"
	.string "would open the treat bag.$"

EcruteakCity_Text_CelestialSupplies:
	.string "Want to buy a spare Fish\n"
	.string "Toy or some catnip? Each\p"
	.string "costs 500.\p"
	.string "You can change her form\n"
	.string "again whenever you like.$"

EcruteakCity_Text_CelestialBelieverAfter:
	.string "So the visitor was Bijuu!\n"
	.string "That makes her more\p"
	.string "magical to me.\p"
	.string "A celestial being who\n"
	.string "still loves her sisters\p"
	.string "and a squeaky fish.$"

EcruteakCity_Text_CelestialMarketAfter:
	.string "I knew it was a cat. The\n"
	.string "toy gave her away.\p"
	.string "Nobody believed me until\n"
	.string "Bijuu started making\p"
	.string "things float in front of\n"
	.string "them.$"

EcruteakCity_Text_CelestialSkepticBefore:
	.string "Glowing eyes and a taste\n"
	.string "for snacks? That sounds\p"
	.string "like a cat, not a\n"
	.string "prophecy.\p"
	.string "I would ask the woman\n"
	.string "beside the Eevee before\p"
	.string "building a shrine.$"

EcruteakCity_Text_CelestialSkepticAfter:
	.string "A psychic cat. I was half\n"
	.string "right.\p"
	.string "She can move stones with\n"
	.string "her mind, but still asks\p"
	.string "someone else to open her\n"
	.string "food.$"

