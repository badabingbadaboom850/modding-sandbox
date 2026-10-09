@ Temporary, repeatable test encounters outside Mom's house.
@ No quest flags, prizes, or party grants: the later story arenas stay separate.
NewBarkTown_EventScript_PennySpiritTrial::
	lock
	faceplayer
	msgbox TrioHomeSpirit_PennyOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioHomeSpirit_Decline
	setvar VAR_0x8004, SPECIES_PENNY_SPIRIT
	specialvar VAR_RESULT, PrepareTrioSpiritTrial
	goto_if_eq VAR_RESULT, FALSE, TrioHomeSpirit_NoParty
	msgbox TrioHomeSpirit_Ready, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_PENNY_SPIRIT, CRY_MODE_ENCOUNTER
	waitmoncry
	special BattleSetup_StartTrioSpiritTrial
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioHomeSpirit_Retry
	msgbox TrioHomeSpirit_PennyVictory, MSGBOX_DEFAULT
	release
	end

NewBarkTown_EventScript_BijuuSpiritTrial::
	lock
	faceplayer
	msgbox TrioHomeSpirit_BijuuOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioHomeSpirit_Decline
	setvar VAR_0x8004, SPECIES_BIJUU_SPIRIT
	specialvar VAR_RESULT, PrepareTrioSpiritTrial
	goto_if_eq VAR_RESULT, FALSE, TrioHomeSpirit_NoParty
	msgbox TrioHomeSpirit_Ready, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_BIJUU_SPIRIT, CRY_MODE_ENCOUNTER
	waitmoncry
	special BattleSetup_StartTrioSpiritTrial
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioHomeSpirit_Retry
	msgbox TrioHomeSpirit_BijuuVictory, MSGBOX_DEFAULT
	release
	end

TrioHomeSpirit_Decline::
	msgbox TrioHomeSpirit_DeclineText, MSGBOX_DEFAULT
	release
	end

TrioHomeSpirit_NoParty::
	msgbox TrioHomeSpirit_NoPartyText, MSGBOX_DEFAULT
	release
	end

TrioHomeSpirit_Retry::
	msgbox TrioHomeSpirit_RetryText, MSGBOX_DEFAULT
	release
	end

TrioHomeSpirit_PennyOffer:
	.string "Penny stands tall.\n"
	.string "Her armor shines softly.\p"
	.string "A friendly courage test?\n"
	.string "She will match your team.$"

TrioHomeSpirit_BijuuOffer:
	.string "Bijuu's blue tails dance.\n"
	.string "She gives a playful wink.\p"
	.string "A friendly test of spirit?\n"
	.string "She will match your team.$"

TrioHomeSpirit_Ready:
	.string "Your team feels refreshed.\n"
	.string "The spirit is ready!\p"
	.string "Win or lose, you are safe.\n"
	.string "You can always try again.$"

TrioHomeSpirit_DeclineText:
	.string "There is no rush.\n"
	.string "She is happy you came.$"

TrioHomeSpirit_NoPartyText:
	.string "Bring a Pokemon with you.\n"
	.string "She will wait right here.$"

TrioHomeSpirit_RetryText:
	.string "The spirit nuzzles you.\n"
	.string "Your team is healed.\p"
	.string "Love is not a test\n"
	.string "you can fail.\p"
	.string "Try again whenever\n"
	.string "you feel ready.$"

TrioHomeSpirit_PennyVictory:
	.string "Penny lowers her shield.\n"
	.string "Her voice feels familiar.\p"
	.string "Mom, I was not always\n"
	.string "this brave.\p"
	.string "You never asked me\n"
	.string "to stop being scared.\p"
	.string "You stayed beside me\n"
	.string "until I felt safe.\p"
	.string "Every piece of this armor\n"
	.string "is a time you chose me.\p"
	.string "A warm blanket. Your lap.\n"
	.string "A place I could belong.\p"
	.string "I guard my sisters now\n"
	.string "because you showed me how.\p"
	.string "If you ever wonder\n"
	.string "whether you were enough...\p"
	.string "Look at who I became.\p"
	.string "I am brave because\n"
	.string "I am your little girl.\p"
	.string "Thank you for being\n"
	.string "my mom.$"

TrioHomeSpirit_BijuuVictory:
	.string "Bijuu's flames grow quiet.\n"
	.string "She presses close to you.\p"
	.string "Mom, you call me\n"
	.string "your little cocoa.\p"
	.string "I act like the whole world\n"
	.string "belongs to me.\p"
	.string "But my favorite part of it\n"
	.string "has always been you.\p"
	.string "You loved all my quirks.\n"
	.string "Even on the noisy days.\p"
	.string "You made the backyard\n"
	.string "feel like a whole kingdom.\p"
	.string "And you made coming home\n"
	.string "feel even better.\p"
	.string "These flames can chase\n"
	.string "every shadow away.\p"
	.string "But you were my light\n"
	.string "before I had any of them.\p"
	.string "You did not have to make\n"
	.string "me legendary to love me.\p"
	.string "You loved me first.\n"
	.string "That is why I shine.\p"
	.string "In every world, Mom,\n"
	.string "I would choose you again.$"
