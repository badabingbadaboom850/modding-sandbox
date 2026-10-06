Route102_MapScripts::
	.byte 0

Route102_EventScript_BijuuEncounter::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_FIRST_BALLS, Route102_EventScript_BijuuTooShy
	checkitem ITEM_POKE_BALL, 1
	goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_BijuuReadyToBattle
	msgbox Route102_Text_BijuuTooShy, MSGBOX_NPC
	release
	end

Route102_EventScript_BijuuReadyToBattle::
	msgbox Route102_Text_BijuuAppears, MSGBOX_DEFAULT
	playmoncry SPECIES_BIJUU, CRY_MODE_ENCOUNTER
	setwildbattle SPECIES_BIJUU, 8
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Route102_EventScript_BijuuCaught
	release
	end

Route102_EventScript_BijuuTooShy::
	msgbox Route102_Text_BijuuTooShy, MSGBOX_NPC
	release
	end

Route102_EventScript_BijuuCaught::
	removeobject LOCALID_ROUTE102_BIJUU
	setflag FLAG_CAUGHT_BIJUU
	msgbox Route102_Text_BijuuCaught, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_LittleBoy::
	msgbox Route102_Text_ImNotVeryTall, MSGBOX_NPC
	end

Route102_EventScript_RouteSignOldale::
	msgbox Route102_Text_RouteSignOldale, MSGBOX_SIGN
	end

Route102_EventScript_RouteSignPetalburg::
	msgbox Route102_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

Route102_EventScript_Boy::
	msgbox Route102_Text_CatchWholeBunchOfPokemon, MSGBOX_NPC
	end

Route102_EventScript_Calvin::
	trainerbattle_single TRAINER_NONE, Route102_Text_CalvinIntro, Route102_Text_CalvinDefeated, Route102_EventScript_CalvinRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_CalvinRematch
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route102_EventScript_CalvinTryRegister
	msgbox Route102_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_CalvinRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route102_EventScript_CalvinRegisterMatchCall
	release
	end

Route102_EventScript_CalvinRegisterMatchCall::
	msgbox Route102_Text_CalvinRegisterShort, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_CalvinTryRegister::
	goto_if_set FLAG_HAS_MATCH_CALL, Route102_EventScript_CalvinRegister
	msgbox Route102_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_CalvinRegister::
	msgbox Route102_Text_CalvinRegister, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_CalvinRematch::
	trainerbattle_rematch TRAINER_NONE, Route102_Text_CalvinRematchIntro, Route102_Text_CalvinRematchDefeated
	msgbox Route102_Text_CalvinRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Rick::
	trainerbattle_single TRAINER_RICK, Route102_Text_RickIntro, Route102_Text_RickDefeated
	msgbox Route102_Text_RickPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Tiana::
	trainerbattle_single TRAINER_TIANA, Route102_Text_TianaIntro, Route102_Text_TianaDefeated
	msgbox Route102_Text_TianaPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Allen::
	trainerbattle_single TRAINER_ALLEN, Route102_Text_AllenIntro, Route102_Text_AllenDefeated
	msgbox Route102_Text_AllenPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_Text_WatchMeCatchPokemon:
	.string "Wally: {PLAYER}…\n"
	.string "Pokémon hide in tall grass like this,\l"
	.string "don't they?\p"
	.string "Please watch me and see if I can\n"
	.string "catch one properly.\p"
	.string "…Whoa!$"

Route102_Text_WallyIDidIt:
	.string "Wally: I did it… It's my…\n"
	.string "My Pokémon!$"

Route102_Text_LetsGoBack:
	.string "{PLAYER}, thank you!\n"
	.string "Let's go back to the Gym!$"

Route102_Text_ImNotVeryTall:
	.string "I'm…not very tall, so I sink right\n"
	.string "into tall grass.\p"
	.string "Penny would disappear in here too…\n"
	.string "though she'd probably emerge covered\n"
	.string "in leaves and looking very proud!$"

Route102_Text_CatchWholeBunchOfPokemon:
	.string "I'm going to catch a whole bunch of\n"
	.string "Pokémon! Maybe one will be as\n"
	.string "dramatic as Riko!\p"
	.string "Maybe one will be as patient as Penny,\n"
	.string "or as mysterious as Bijuu.\p"
	.string "A shy cat watches by the berry trees.\n"
	.string "It copies every step, then hides.$"

Route102_Text_RouteSignOldale:
	.string "Route 102\n"
	.string "{RIGHT_ARROW} Oldale Town$"

Route102_Text_RouteSignPetalburg:
	.string "Route 102\n"
	.string "{LEFT_ARROW} Petalburg City$"

Route102_Text_BijuuAppears:
	.string "The shy cat copies your movements.\p"
	.string "She steps close, then watches you\n"
	.string "with bright, curious eyes.$"

Route102_Text_BijuuTooShy:
	.string "A shy cat watches from the grass.\n"
	.string "It copies your movements, then hides.\p"
	.string "You should come back with Poke Balls.$"

Route102_Text_BijuuCaught:
	.string "Bijuu trusts you enough to stay.\p"
	.string "She was sent to a PC Box if your\n"
	.string "party was full.$"
