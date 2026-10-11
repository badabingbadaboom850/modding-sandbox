@ Optional elemental keepsake gifts. Callers retain their original dialogue.

TrioElement_RikoDragon::
	checkitem ITEM_POM_DRAGON_PLUSH
	goto_if_eq VAR_RESULT, TRUE, TrioElement_RikoDragon_Owned
	call TrioParty_CheckRiko
	goto_if_ne VAR_RESULT, TRUE, TrioElement_RikoDragon_Missing
	msgbox TrioElement_RikoDragon_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioElement_RikoDragon_Return
	giveitem ITEM_POM_DRAGON_PLUSH
	goto_if_eq VAR_RESULT, FALSE, TrioElement_RikoDragon_Full
	msgbox TrioElement_RikoDragon_Taught, MSGBOX_DEFAULT
	return
TrioElement_RikoDragon_Owned::
	msgbox TrioElement_RikoDragon_Already, MSGBOX_DEFAULT
	return
TrioElement_RikoDragon_Missing::
	msgbox TrioElement_RikoDragon_Bring, MSGBOX_DEFAULT
	return
TrioElement_RikoDragon_Full::
	msgbox TrioElement_Text_Full, MSGBOX_DEFAULT
TrioElement_RikoDragon_Return::
	return
TrioElement_RikoDragon_Offer:
	.string "Riko says she's a dragon!\nI collect dragon plushies!\pThis one might wake her\ninner roar. Want it?$"
TrioElement_RikoDragon_Taught:
	.string "Use it on ordinary Riko.\nUse again to return!$"
TrioElement_RikoDragon_Already:
	.string "Riko has her keepsake.\nHer next adventure awaits!$"
TrioElement_RikoDragon_Bring:
	.string "Bring Riko along someday.\nI have a gift for her!$"

TrioElement_RikoBug::
	checkitem ITEM_RIKOS_HONEYCOMB
	goto_if_eq VAR_RESULT, TRUE, TrioElement_RikoBug_Owned
	call TrioParty_CheckRiko
	goto_if_ne VAR_RESULT, TRUE, TrioElement_RikoBug_Missing
	msgbox TrioElement_RikoBug_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioElement_RikoBug_Return
	giveitem ITEM_RIKOS_HONEYCOMB
	goto_if_eq VAR_RESULT, FALSE, TrioElement_RikoBug_Full
	msgbox TrioElement_RikoBug_Taught, MSGBOX_DEFAULT
	return
TrioElement_RikoBug_Owned::
	msgbox TrioElement_RikoBug_Already, MSGBOX_DEFAULT
	return
TrioElement_RikoBug_Missing::
	msgbox TrioElement_RikoBug_Bring, MSGBOX_DEFAULT
	return
TrioElement_RikoBug_Full::
	msgbox TrioElement_Text_Full, MSGBOX_DEFAULT
TrioElement_RikoBug_Return::
	return
TrioElement_RikoBug_Offer:
	.string "I keep a little beehive.\nRiko guards every snack!\pShe'd make a fine bee.\nWant this honeycomb?$"
TrioElement_RikoBug_Taught:
	.string "Use it on ordinary Riko.\nUse again to return!$"
TrioElement_RikoBug_Already:
	.string "Riko has her keepsake.\nHer next adventure awaits!$"
TrioElement_RikoBug_Bring:
	.string "Bring Riko along someday.\nI have a gift for her!$"

TrioElement_BijuuDark::
	checkitem ITEM_COCOAS_SNEAKY_CAPE
	goto_if_eq VAR_RESULT, TRUE, TrioElement_BijuuDark_Owned
	call TrioParty_CheckBijuu
	goto_if_ne VAR_RESULT, TRUE, TrioElement_BijuuDark_Missing
	msgbox TrioElement_BijuuDark_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioElement_BijuuDark_Return
	giveitem ITEM_COCOAS_SNEAKY_CAPE
	goto_if_eq VAR_RESULT, FALSE, TrioElement_BijuuDark_Full
	msgbox TrioElement_BijuuDark_Taught, MSGBOX_DEFAULT
	return
TrioElement_BijuuDark_Owned::
	msgbox TrioElement_BijuuDark_Already, MSGBOX_DEFAULT
	return
TrioElement_BijuuDark_Missing::
	msgbox TrioElement_BijuuDark_Bring, MSGBOX_DEFAULT
	return
TrioElement_BijuuDark_Full::
	msgbox TrioElement_Text_Full, MSGBOX_DEFAULT
TrioElement_BijuuDark_Return::
	return
TrioElement_BijuuDark_Offer:
	.string "I tell tales after dark.\nBijuu moves like a shadow!\pA cape for night walks.\nWould she like it?$"
TrioElement_BijuuDark_Taught:
	.string "Use it on ordinary Bijuu.\nUse again to return!$"
TrioElement_BijuuDark_Already:
	.string "Bijuu has her keepsake.\nHer next adventure awaits!$"
TrioElement_BijuuDark_Bring:
	.string "Bring Bijuu along someday.\nI have a gift for her!$"

TrioElement_BijuuRock::
	checkitem ITEM_COCOAS_SHINY_PEBBLE
	goto_if_eq VAR_RESULT, TRUE, TrioElement_BijuuRock_Owned
	call TrioParty_CheckBijuu
	goto_if_ne VAR_RESULT, TRUE, TrioElement_BijuuRock_Missing
	msgbox TrioElement_BijuuRock_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioElement_BijuuRock_Return
	giveitem ITEM_COCOAS_SHINY_PEBBLE
	goto_if_eq VAR_RESULT, FALSE, TrioElement_BijuuRock_Full
	msgbox TrioElement_BijuuRock_Taught, MSGBOX_DEFAULT
	return
TrioElement_BijuuRock_Owned::
	msgbox TrioElement_BijuuRock_Already, MSGBOX_DEFAULT
	return
TrioElement_BijuuRock_Missing::
	msgbox TrioElement_BijuuRock_Bring, MSGBOX_DEFAULT
	return
TrioElement_BijuuRock_Full::
	msgbox TrioElement_Text_Full, MSGBOX_DEFAULT
TrioElement_BijuuRock_Return::
	return
TrioElement_BijuuRock_Offer:
	.string "I collect sparkling rocks.\nBijuu eyes my shiny rock.\pShe has excellent taste!\nWant this shiny pebble?$"
TrioElement_BijuuRock_Taught:
	.string "Use it on ordinary Bijuu.\nUse again to return!$"
TrioElement_BijuuRock_Already:
	.string "Bijuu has her keepsake.\nHer next adventure awaits!$"
TrioElement_BijuuRock_Bring:
	.string "Bring Bijuu along someday.\nI have a gift for her!$"

TrioElement_PennyGround::
	checkitem ITEM_PENNYS_GARDEN_TROWEL
	goto_if_eq VAR_RESULT, TRUE, TrioElement_PennyGround_Owned
	call TrioParty_CheckPenny
	goto_if_ne VAR_RESULT, TRUE, TrioElement_PennyGround_Missing
	msgbox TrioElement_PennyGround_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioElement_PennyGround_Return
	giveitem ITEM_PENNYS_GARDEN_TROWEL
	goto_if_eq VAR_RESULT, FALSE, TrioElement_PennyGround_Full
	msgbox TrioElement_PennyGround_Taught, MSGBOX_DEFAULT
	return
TrioElement_PennyGround_Owned::
	msgbox TrioElement_PennyGround_Already, MSGBOX_DEFAULT
	return
TrioElement_PennyGround_Missing::
	msgbox TrioElement_PennyGround_Bring, MSGBOX_DEFAULT
	return
TrioElement_PennyGround_Full::
	msgbox TrioElement_Text_Full, MSGBOX_DEFAULT
TrioElement_PennyGround_Return::
	return
TrioElement_PennyGround_Offer:
	.string "I tend the little gardens.\nPenny likes cozy hideouts!\pA trowel for our digger.\nWould she like it?$"
TrioElement_PennyGround_Taught:
	.string "Use it on Guardian Penny.\nUse again to return!$"
TrioElement_PennyGround_Already:
	.string "Penny has her keepsake.\nHer next adventure awaits!$"
TrioElement_PennyGround_Bring:
	.string "Bring Penny along someday.\nI have a gift for her!$"

TrioElement_PennySteel::
	checkitem ITEM_DADS_TOOLBOX
	goto_if_eq VAR_RESULT, TRUE, TrioElement_PennySteel_Owned
	call TrioParty_CheckPenny
	goto_if_ne VAR_RESULT, TRUE, TrioElement_PennySteel_Missing
	msgbox TrioElement_PennySteel_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioElement_PennySteel_Return
	giveitem ITEM_DADS_TOOLBOX
	goto_if_eq VAR_RESULT, FALSE, TrioElement_PennySteel_Full
	msgbox TrioElement_PennySteel_Taught, MSGBOX_DEFAULT
	return
TrioElement_PennySteel_Owned::
	msgbox TrioElement_PennySteel_Already, MSGBOX_DEFAULT
	return
TrioElement_PennySteel_Missing::
	msgbox TrioElement_PennySteel_Bring, MSGBOX_DEFAULT
	return
TrioElement_PennySteel_Full::
	msgbox TrioElement_Text_Full, MSGBOX_DEFAULT
TrioElement_PennySteel_Return::
	return
TrioElement_PennySteel_Offer:
	.string "I repair things on ships.\nPenny's a trusty helper!\pDad's toolbox suits her.\nWant it for Penny?$"
TrioElement_PennySteel_Taught:
	.string "Use it on Guardian Penny.\nUse again to return!$"
TrioElement_PennySteel_Already:
	.string "Penny has her keepsake.\nHer next adventure awaits!$"
TrioElement_PennySteel_Bring:
	.string "Bring Penny along someday.\nI have a gift for her!$"

TrioElement_Text_Full:
	.string "Your Bag is full. Come\nback for the keepsake!$"
