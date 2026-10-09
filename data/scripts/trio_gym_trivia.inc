@ Each Gym-city quiz has one question and one successfully claimed reward.
TrioGymTrivia_VioletCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_VioletCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_VioletCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_VIOLET_CITY, TrioGymTrivia_VioletCity_Replay
	giveitem ITEM_EEL_SUSHI, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_VIOLET_CITY
TrioGymTrivia_VioletCity_Replay:
	msgbox TrioGymTrivia_VioletCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_VioletCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_VioletCity_Question:
	.string "Is Riko's favorite food\n"
	.string "chicky fil a?$"

TrioGymTrivia_VioletCity_Tip:
	.string "Electric Riko helps with\n"
	.string "Flying Pokemon. My prize\p"
	.string "is yours once, but you can\n"
	.string "play again!$"

TrioGymTrivia_AzaleaTown::
	lock
	faceplayer
	msgbox TrioGymTrivia_AzaleaTown_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_AzaleaTown_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_AZALEA_TOWN, TrioGymTrivia_AzaleaTown_Replay
	giveitem ITEM_GREEN_PEPPER, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_AZALEA_TOWN
TrioGymTrivia_AzaleaTown_Replay:
	msgbox TrioGymTrivia_AzaleaTown_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_AzaleaTown_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_AzaleaTown_Question:
	.string "Is Bijuu a cocoa?$"

TrioGymTrivia_AzaleaTown_Tip:
	.string "Fire Riko helps with Bug\n"
	.string "Pokemon. My prize is yours\p"
	.string "once, but you can play\n"
	.string "again!$"

TrioGymTrivia_GoldenrodCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_GoldenrodCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_GoldenrodCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, NO, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_GOLDENROD_CITY, TrioGymTrivia_GoldenrodCity_Replay
	giveitem ITEM_MOUSE_TOY, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_GOLDENROD_CITY
TrioGymTrivia_GoldenrodCity_Replay:
	msgbox TrioGymTrivia_GoldenrodCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_GoldenrodCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_GoldenrodCity_Question:
	.string "Is Scotts Favorite Food\n"
	.string "chicken?$"

TrioGymTrivia_GoldenrodCity_Tip:
	.string "Ghost Bijuu avoids Normal\n"
	.string "attacks. My prize is yours\p"
	.string "once, but you can play\n"
	.string "again!$"

TrioGymTrivia_EcruteakCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_EcruteakCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_EcruteakCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_ECRUTEAK_CITY, TrioGymTrivia_EcruteakCity_Replay
	giveitem ITEM_MOUSE_TOY, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_ECRUTEAK_CITY
TrioGymTrivia_EcruteakCity_Replay:
	msgbox TrioGymTrivia_EcruteakCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_EcruteakCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_EcruteakCity_Question:
	.string "Does Scott love you most?$"

TrioGymTrivia_EcruteakCity_Tip:
	.string "Ghost attacks hit Ghost\n"
	.string "Pokemon hard. Watch out\p"
	.string "for their attacks too! My\n"
	.string "prize is yours once, but\p"
	.string "you can play again!$"

TrioGymTrivia_CianwoodCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_CianwoodCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_CianwoodCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_CIANWOOD_CITY, TrioGymTrivia_CianwoodCity_Replay
	giveitem ITEM_MOUSE_TOY, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_CIANWOOD_CITY
TrioGymTrivia_CianwoodCity_Replay:
	msgbox TrioGymTrivia_CianwoodCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_CianwoodCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_CianwoodCity_Question:
	.string "Is Bijuu's favorite place\n"
	.string "the backyard?$"

TrioGymTrivia_CianwoodCity_Tip:
	.string "Ghost Bijuu avoids\n"
	.string "Fighting attacks. My prize\p"
	.string "is yours once, but you can\n"
	.string "play again!$"

TrioGymTrivia_OlivineCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_OlivineCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_OlivineCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_OLIVINE_CITY, TrioGymTrivia_OlivineCity_Replay
	giveitem ITEM_GREEN_PEPPER, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_OLIVINE_CITY
TrioGymTrivia_OlivineCity_Replay:
	msgbox TrioGymTrivia_OlivineCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_OlivineCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_OlivineCity_Question:
	.string "Is Penny's enemy a bun?$"

TrioGymTrivia_OlivineCity_Tip:
	.string "Fire Riko helps with Steel\n"
	.string "Pokemon. My prize is yours\p"
	.string "once, but you can play\n"
	.string "again!$"

TrioGymTrivia_Mahoganytown::
	lock
	faceplayer
	msgbox TrioGymTrivia_Mahoganytown_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_Mahoganytown_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, NO, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_MAHOGANYTOWN, TrioGymTrivia_Mahoganytown_Replay
	giveitem ITEM_GREEN_PEPPER, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_MAHOGANYTOWN
TrioGymTrivia_Mahoganytown_Replay:
	msgbox TrioGymTrivia_Mahoganytown_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_Mahoganytown_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_Mahoganytown_Question:
	.string "Does Riko Love Baths?$"

TrioGymTrivia_Mahoganytown_Tip:
	.string "Fire Riko helps with Ice\n"
	.string "Pokemon. My prize is yours\p"
	.string "once, but you can play\n"
	.string "again!$"

TrioGymTrivia_BlackthornCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_BlackthornCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_BlackthornCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_BLACKTHORN_CITY, TrioGymTrivia_BlackthornCity_Replay
	giveitem ITEM_FROZEN_FISH, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_BLACKTHORN_CITY
TrioGymTrivia_BlackthornCity_Replay:
	msgbox TrioGymTrivia_BlackthornCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_BlackthornCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_BlackthornCity_Question:
	.string "Are Ice attacks strong\n"
	.string "against Dragon Pokemon?$"

TrioGymTrivia_BlackthornCity_Tip:
	.string "Ice Bijuu helps with\n"
	.string "Dragon Pokemon. My prize\p"
	.string "is yours once, but you can\n"
	.string "play again!$"

TrioGymTrivia_PewterCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_PewterCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_PewterCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_PEWTER_CITY, TrioGymTrivia_PewterCity_Replay
	giveitem ITEM_DOG_BOWL, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_PEWTER_CITY
TrioGymTrivia_PewterCity_Replay:
	msgbox TrioGymTrivia_PewterCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_PewterCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_PewterCity_Question:
	.string "Are Water attacks strong\n"
	.string "against Rock Pokemon?$"

TrioGymTrivia_PewterCity_Tip:
	.string "Water Penny helps with\n"
	.string "Rock Pokemon. My prize is\p"
	.string "yours once, but you can\n"
	.string "play again!$"

TrioGymTrivia_CeruleanCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_CeruleanCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_CeruleanCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_CERULEAN_CITY, TrioGymTrivia_CeruleanCity_Replay
	giveitem ITEM_FETCHING_STICK, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_CERULEAN_CITY
TrioGymTrivia_CeruleanCity_Replay:
	msgbox TrioGymTrivia_CeruleanCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_CeruleanCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_CeruleanCity_Question:
	.string "Are Grass attacks strong\n"
	.string "against Water Pokemon?$"

TrioGymTrivia_CeruleanCity_Tip:
	.string "Grass Penny helps with\n"
	.string "Water Pokemon. My prize is\p"
	.string "yours once, but you can\n"
	.string "play again!$"

TrioGymTrivia_VermilionCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_VermilionCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_VermilionCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, NO, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_VERMILION_CITY, TrioGymTrivia_VermilionCity_Replay
	giveitem ITEM_FETCHING_STICK, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_VERMILION_CITY
TrioGymTrivia_VermilionCity_Replay:
	msgbox TrioGymTrivia_VermilionCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_VermilionCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_VermilionCity_Question:
	.string "Is Pikachu a Water type?$"

TrioGymTrivia_VermilionCity_Tip:
	.string "Grass Penny resists\n"
	.string "Electric attacks. My prize\p"
	.string "is yours once, but you can\n"
	.string "play again!$"

TrioGymTrivia_CeladonCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_CeladonCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_CeladonCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_CELADON_CITY, TrioGymTrivia_CeladonCity_Replay
	giveitem ITEM_GREEN_PEPPER, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_CELADON_CITY
TrioGymTrivia_CeladonCity_Replay:
	msgbox TrioGymTrivia_CeladonCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_CeladonCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_CeladonCity_Question:
	.string "Are Fire attacks strong\n"
	.string "against Grass Pokemon?$"

TrioGymTrivia_CeladonCity_Tip:
	.string "Fire Riko helps with Grass\n"
	.string "Pokemon. My prize is yours\p"
	.string "once, but you can play\n"
	.string "again!$"

TrioGymTrivia_FuchsiaCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_FuchsiaCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_FuchsiaCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, NO, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_FUCHSIA_CITY, TrioGymTrivia_FuchsiaCity_Replay
	giveitem ITEM_PECHA_BERRY, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_FUCHSIA_CITY
TrioGymTrivia_FuchsiaCity_Replay:
	msgbox TrioGymTrivia_FuchsiaCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_FuchsiaCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_FuchsiaCity_Question:
	.string "Can Poison attacks hurt a\n"
	.string "pure Steel Pokemon?$"

TrioGymTrivia_FuchsiaCity_Tip:
	.string "A held Pecha Berry cures\n"
	.string "poison once. My prize is\p"
	.string "yours once, but you can\n"
	.string "play again!$"

TrioGymTrivia_SaffronCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_SaffronCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_SaffronCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_SAFFRON_CITY, TrioGymTrivia_SaffronCity_Replay
	giveitem ITEM_MOUSE_TOY, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_SAFFRON_CITY
TrioGymTrivia_SaffronCity_Replay:
	msgbox TrioGymTrivia_SaffronCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_SaffronCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_SaffronCity_Question:
	.string "Are Ghost attacks strong\n"
	.string "against Psychic Pokemon?$"

TrioGymTrivia_SaffronCity_Tip:
	.string "Ghost Bijuu helps with\n"
	.string "Psychic Pokemon. My prize\p"
	.string "is yours once, but you can\n"
	.string "play again!$"

TrioGymTrivia_CinnabarIsland::
	lock
	faceplayer
	msgbox TrioGymTrivia_CinnabarIsland_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_CinnabarIsland_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_CINNABAR_ISLAND, TrioGymTrivia_CinnabarIsland_Replay
	giveitem ITEM_DOG_BOWL, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_CINNABAR_ISLAND
TrioGymTrivia_CinnabarIsland_Replay:
	msgbox TrioGymTrivia_CinnabarIsland_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_CinnabarIsland_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_CinnabarIsland_Question:
	.string "Are Water attacks strong\n"
	.string "against Fire Pokemon?$"

TrioGymTrivia_CinnabarIsland_Tip:
	.string "Water Penny helps with\n"
	.string "Fire Pokemon. My prize is\p"
	.string "yours once, but you can\n"
	.string "play again!$"

TrioGymTrivia_ViridianCity::
	lock
	faceplayer
	msgbox TrioGymTrivia_ViridianCity_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioGymTrivia_Decline
	msgbox TrioGymTrivia_ViridianCity_Question, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioGymTrivia_Wrong
	goto_if_set FLAG_TRIO_QUIZ_VIRIDIAN_CITY, TrioGymTrivia_ViridianCity_Replay
	giveitem ITEM_FROZEN_FISH, 1
	goto_if_eq VAR_RESULT, FALSE, TrioGymTrivia_BagFull
	setflag FLAG_TRIO_QUIZ_VIRIDIAN_CITY
TrioGymTrivia_ViridianCity_Replay:
	msgbox TrioGymTrivia_ViridianCity_Tip, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish

TrioGymTrivia_ViridianCity_Offer:
	.string "One little quiz! A right\n"
	.string "answer earns a Gym helper.\p"
	.string "Want to play?$"

TrioGymTrivia_ViridianCity_Question:
	.string "Does Magikarp evolve into\n"
	.string "Gyarados?$"

TrioGymTrivia_ViridianCity_Tip:
	.string "Ice Bijuu helps against\n"
	.string "Flying and Ground Pokemon.\p"
	.string "Blue has a varied team! My\n"
	.string "prize is yours once, but\p"
	.string "you can play again!$"

TrioGymTrivia_Wrong::
	msgbox TrioGymTrivia_TextWrong, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish
TrioGymTrivia_Decline::
	msgbox TrioGymTrivia_TextDecline, MSGBOX_DEFAULT
	goto TrioGymTrivia_Finish
TrioGymTrivia_BagFull::
	msgbox TrioGymTrivia_TextBagFull, MSGBOX_DEFAULT
TrioGymTrivia_Finish::
	closemessage
	release
	end

TrioGymTrivia_TextWrong:
	.string "Not quite! There is no\n"
	.string "penalty. Talk to me and\p"
	.string "try again!$"

TrioGymTrivia_TextDecline:
	.string "Whenever you like! Give\n"
	.string "the girls my love.$"

TrioGymTrivia_TextBagFull:
	.string "Your Bag has no room! Make\n"
	.string "some space, then try my\p"
	.string "question again.$"

