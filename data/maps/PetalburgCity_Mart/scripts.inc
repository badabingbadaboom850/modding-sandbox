PetalburgCity_Mart_MapScripts::
	.byte 0

PetalburgCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_PETALBURG_MART_EXPANDED_ITEMS, PetalburgCity_Mart_EventScript_ExpandedItems
	pokemart PetalburgCity_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_Basic:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_ORANGE_MAIL
	pokemartlistend

PetalburgCity_Mart_EventScript_ExpandedItems::
	pokemart PetalburgCity_Mart_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_Expanded:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_ORANGE_MAIL
	pokemartlistend

PetalburgCity_Mart_EventScript_Woman::
	msgbox PetalburgCity_Mart_Text_WeakWillGrowStronger, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_Boy::
	msgbox PetalburgCity_Mart_Text_RepelIsUseful, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_Man::
	msgbox PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou, MSGBOX_NPC
	end

PetalburgCity_Mart_Text_WeakWillGrowStronger:
	.string "Even if a Pokémon is weak now,\n"
	.string "it will grow stronger.\p"
	.string "The most important thing is love!\n"
	.string "Love for your Pokémon!\p"
	.string "Riko agrees, although she also expects\n"
	.string "compliments and a snack.\p"
	.string "Penny says encouragement works better\n"
	.string "than shouting. Bijuu is taking notes.\pA clerk heard the trio helps\nsmall Pokemon grow strong.\nRiko, Penny, and Bijuu.$"

PetalburgCity_Mart_Text_RepelIsUseful:
	.string "Do you use Repel?\n"
	.string "It keeps Pokémon away, so it's\l"
	.string "useful when you're in a hurry.\p"
	.string "Penny would rather avoid the tall grass\n"
	.string "altogether, honestly.\p"
	.string "Riko would charge through it for a treat.\n"
	.string "Bijuu would copy whatever startled her.\pBijuu can copy a Pokemon cry.\nSome say it learned every sound\nfrom its legendary sisters.$"

PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou:
	.string "Do you have any Antidotes with\n"
	.string "you?\p"
	.string "If you walk around with a poisoned\n"
	.string "Pokémon, it will lose Hp until it faints.\l"
	.string "Take some Antidotes with you.\p"
	.string "Bijuu would probably copy the poison\n"
	.string "if nobody stopped it.\p"
	.string "Riko would demand a snack afterward,\n"
	.string "and Penny would check everyone twice.\pThe old tales say Riko walks\nthrough danger without fear.\nPenny watches every step.$"

