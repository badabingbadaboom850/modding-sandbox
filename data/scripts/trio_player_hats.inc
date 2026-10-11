TrioPlayerHat_Wardrobe::
	lockall
	checkplayergender
	compare VAR_RESULT, FEMALE
	goto_if_ne TrioPlayerHat_Male
	msgbox TrioPlayerHat_Text_Shelf, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_TRIO_PLAYER_HATS, FALSE
	compare VAR_RESULT, 6
	goto_if_ge TrioPlayerHat_Exit
	special ApplyTrioPlayerHat
	compare VAR_TRIO_PLAYER_HAT, 1
	goto_if_eq TrioPlayerHat_Bow
	compare VAR_TRIO_PLAYER_HAT, 2
	goto_if_eq TrioPlayerHat_Sunhat
	compare VAR_TRIO_PLAYER_HAT, 3
	goto_if_eq TrioPlayerHat_Riko
	compare VAR_TRIO_PLAYER_HAT, 4
	goto_if_eq TrioPlayerHat_Penny
	compare VAR_TRIO_PLAYER_HAT, 5
	goto_if_eq TrioPlayerHat_Bijuu
	msgbox TrioPlayerHat_Text_Original, MSGBOX_DEFAULT
	goto TrioPlayerHat_Exit

TrioPlayerHat_Bow::
	msgbox TrioPlayerHat_Text_Bow, MSGBOX_DEFAULT
	goto TrioPlayerHat_Exit

TrioPlayerHat_Sunhat::
	msgbox TrioPlayerHat_Text_Sunhat, MSGBOX_DEFAULT
	goto TrioPlayerHat_Exit

TrioPlayerHat_Riko::
	msgbox TrioPlayerHat_Text_Riko, MSGBOX_DEFAULT
	goto TrioPlayerHat_Exit

TrioPlayerHat_Penny::
	msgbox TrioPlayerHat_Text_Penny, MSGBOX_DEFAULT
	goto TrioPlayerHat_Exit

TrioPlayerHat_Bijuu::
	msgbox TrioPlayerHat_Text_Bijuu, MSGBOX_DEFAULT
	goto TrioPlayerHat_Exit

TrioPlayerHat_Male::
	msgbox TrioPlayerHat_Text_Male, MSGBOX_DEFAULT

TrioPlayerHat_Exit::
	releaseall
	end

TrioPlayerHat_Text_Shelf:
	.string "Your hats have their own\nspot beside the books.\pPick a look for today's\nadventure!$"
TrioPlayerHat_Text_Original:
	.string "Your trusty original hat.\nReady for another day!$"
TrioPlayerHat_Text_Bow:
	.string "You try on the pink bow.\nRiko inspects it closely.\pShe approves. Naturally,\nshe wants one too.$"
TrioPlayerHat_Text_Sunhat:
	.string "A sunhat with a pink bow!\nBijuu claims the hatbox.\pPenny is ready for a walk.\nVacation starts with you.$"
TrioPlayerHat_Text_Male:
	.string "A shelf of pretty hats.\nThese are Mom's favorites.$"

TrioPlayerHat_Text_Riko:
	.string "Fluffy ears and a bow!\nRiko checks your posture.\pApparently, being a Pom\nis a full-time job.$"
TrioPlayerHat_Text_Penny:
	.string "You put on Penny's hat...\nIt's an entire hot dog.\pPenny looks very proud.\nScott cannot stop smiling.$"
TrioPlayerHat_Text_Bijuu:
	.string "Little Siamese ears!\nBijuu gives you a nod.\pYou may now supervise\nfrom the sunny window.$"
