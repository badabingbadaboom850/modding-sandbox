@ Eight optional repeatable jokes. No persistent writes, inventory or battles.
TrioSilly_ValetOffer::
	lockall
	faceplayer
	msgbox TrioSilly_ValetInviteText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSilly_Decline
	closemessage
	warp MAP_TRIO_SILLY_VALET, 4, 7
	waitstate
	releaseall
	end

TrioSilly_ValetInviteText:
	.string "A tiny valet service!\nThe attendant jingles\phis keys.\pSee who answers?$"

TrioSilly_ValetRun::
	lockall
	setvar VAR_TEMP_A, 0
	special PrepareTrioSillyActors
	goto_if_eq VAR_RESULT, FALSE, TrioSilly_ValetNotReady

	msgbox TrioSilly_ValetOpeningText, MSGBOX_DEFAULT
	playse SE_BALL
	waitse
	msgbox TrioSilly_ValetKeysText, MSGBOX_DEFAULT
	closemessage
	applymovement 3, TrioSilly_ValetFetch
	waitmovement 0
	playmoncry SPECIES_FIDOUGH, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSilly_ValetFinaleText, MSGBOX_DEFAULT
	goto TrioSilly_ValetReturn
TrioSilly_ValetReturn:
	closemessage
	clearflag FLAG_TEMP_HIDE_FOLLOWER
	warp MAP_OLIVINE_CITY_HOUSE1, 4, 7
	waitstate
	releaseall
	end
TrioSilly_ValetNotReady:
	msgbox TrioSilly_NotReadyText, MSGBOX_DEFAULT
	goto TrioSilly_ValetReturn

TrioSilly_BoxOffer::
	lockall
	faceplayer
	msgbox TrioSilly_BoxInviteText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSilly_Decline
	closemessage
	warp MAP_TRIO_SILLY_BOX, 4, 7
	waitstate
	releaseall
	end

TrioSilly_BoxInviteText:
	.string "A priceless artifact\nis being guarded here.\pWould you like to see\nthe forbidden box?$"

TrioSilly_BoxRun::
	lockall
	setvar VAR_TEMP_A, 0
	special PrepareTrioSillyActors
	goto_if_eq VAR_RESULT, FALSE, TrioSilly_BoxNotReady

	msgbox TrioSilly_BoxOpeningText, MSGBOX_DEFAULT
	closemessage
	applymovement 2, TrioSilly_BoxApproach
	waitmovement 0
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 6
	removeobject 2
	clearflag FLAG_TEMP_1
	addobject 7
	fadescreen FADE_FROM_BLACK
	playmoncry SPECIES_BIJUU, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSilly_BoxFinaleText, MSGBOX_DEFAULT
	goto TrioSilly_BoxReturn
TrioSilly_BoxReturn:
	closemessage
	clearflag FLAG_TEMP_HIDE_FOLLOWER
	clearflag FLAG_TEMP_1
	warp MAP_ECRUTEAK_CITY_HOUSE1, 4, 7
	waitstate
	releaseall
	end
TrioSilly_BoxNotReady:
	msgbox TrioSilly_NotReadyText, MSGBOX_DEFAULT
	goto TrioSilly_BoxReturn

TrioSilly_NoiseOffer::
	lockall
	faceplayer
	msgbox TrioSilly_NoiseInviteText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSilly_Decline
	closemessage
	warp MAP_TRIO_SILLY_NOISE, 4, 7
	waitstate
	releaseall
	end

TrioSilly_NoiseInviteText:
	.string "The town has a new\nbarking ordinance.\pRiko requested a hearing.\nWant to attend?$"

TrioSilly_NoiseRun::
	lockall
	setvar VAR_TEMP_A, 0
	special PrepareTrioSillyActors
	goto_if_eq VAR_RESULT, FALSE, TrioSilly_NoiseNotReady

	msgbox TrioSilly_NoiseOpeningText, MSGBOX_DEFAULT
	closemessage
	applymovement 1, TrioSilly_Bark
	waitmovement 0
	playmoncry SPECIES_RIKO, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSilly_NoiseFinaleText, MSGBOX_DEFAULT
	goto TrioSilly_NoiseReturn
TrioSilly_NoiseReturn:
	closemessage
	clearflag FLAG_TEMP_HIDE_FOLLOWER
	warp MAP_MAHOGANY_TOWN_HOUSE1, 4, 7
	waitstate
	releaseall
	end
TrioSilly_NoiseNotReady:
	msgbox TrioSilly_NotReadyText, MSGBOX_DEFAULT
	goto TrioSilly_NoiseReturn

TrioSilly_GregOffer::
	lockall
	faceplayer
	msgbox TrioSilly_GregInviteText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSilly_Decline
	closemessage
	warp MAP_TRIO_SILLY_GREG, 4, 7
	waitstate
	releaseall
	end

TrioSilly_GregInviteText:
	.string "The Greg Fan Club is\naccepting visitors.\pMembership: suspicious.\nAdmission: free.\pVisit the club?$"

TrioSilly_HotdogOffer::
	lockall
	faceplayer
	msgbox TrioSilly_HotdogInviteText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSilly_Decline
	closemessage
	warp MAP_TRIO_SILLY_HOTDOG, 4, 7
	waitstate
	releaseall
	end

TrioSilly_HotdogInviteText:
	.string "A hot-dog vendor has\na very strange question.\pScott looks concerned.\pGo hear him out?$"

TrioSilly_HotdogRun::
	lockall
	setvar VAR_TEMP_A, 0
	special PrepareTrioSillyActors
	goto_if_eq VAR_RESULT, FALSE, TrioSilly_HotdogNotReady

	msgbox TrioSilly_HotdogOpeningText, MSGBOX_DEFAULT
	closemessage
	applymovement 3, TrioSilly_HotdogApproach
	waitmovement 0
	playmoncry SPECIES_FIDOUGH, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSilly_HotdogFinaleText, MSGBOX_DEFAULT
	goto TrioSilly_HotdogReturn
TrioSilly_HotdogReturn:
	closemessage
	clearflag FLAG_TEMP_HIDE_FOLLOWER
	warp MAP_CIANWOOD_HOUSE2, 4, 7
	waitstate
	releaseall
	end
TrioSilly_HotdogNotReady:
	msgbox TrioSilly_NotReadyText, MSGBOX_DEFAULT
	goto TrioSilly_HotdogReturn

TrioSilly_JamOffer::
	lockall
	faceplayer
	msgbox TrioSilly_JamInviteText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSilly_Decline
	closemessage
	warp MAP_TRIO_SILLY_JAM, 26, 25
	waitstate
	releaseall
	end

TrioSilly_JamInviteText:
	.string "Three Poms have stopped\ntraffic over a snack.\pNegotiations have failed.\pHelp clear the road?$"

TrioSilly_JamRun::
	lockall
	setvar VAR_TEMP_A, 0
	special PrepareTrioSillyActors
	goto_if_eq VAR_RESULT, FALSE, TrioSilly_JamNotReady

	msgbox TrioSilly_JamOpeningText, MSGBOX_DEFAULT
	msgbox TrioSilly_JamDealText, MSGBOX_DEFAULT
	closemessage
	removeobject 10
	applymovement 6, TrioSilly_JamMarch
	applymovement 7, TrioSilly_JamMarch
	applymovement 8, TrioSilly_JamMarch
	waitmovementall
	removeobject 6
	removeobject 7
	removeobject 8
	msgbox TrioSilly_JamFinaleText, MSGBOX_DEFAULT
	goto TrioSilly_JamReturn
TrioSilly_JamReturn:
	closemessage
	clearflag FLAG_TEMP_HIDE_FOLLOWER
	warp MAP_PEWTER_CITY_HOUSE1, 4, 7
	waitstate
	releaseall
	end
TrioSilly_JamNotReady:
	msgbox TrioSilly_NotReadyText, MSGBOX_DEFAULT
	goto TrioSilly_JamReturn

TrioSilly_FishingOffer::
	lockall
	faceplayer
	msgbox TrioSilly_FishingInviteText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSilly_Decline
	closemessage
	warp MAP_TRIO_SILLY_FISHING, 40, 25
	waitstate
	releaseall
	end

TrioSilly_FishingInviteText:
	.string "A fisherman wants Bijuu\nto inspect his catch.\pThis seems unwise.\pWatch the inspection?$"

TrioSilly_FishingRun::
	lockall
	setvar VAR_TEMP_A, 0
	special PrepareTrioSillyActors
	goto_if_eq VAR_RESULT, FALSE, TrioSilly_FishingNotReady

	msgbox TrioSilly_FishingOpeningText, MSGBOX_DEFAULT
	closemessage
	applymovement 2, TrioSilly_FishInspect
	waitmovement 0
	closemessage
	fadescreen FADE_TO_BLACK
	playse SE_BALL
	waitse
	fadescreen FADE_FROM_BLACK
	playmoncry SPECIES_BIJUU, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSilly_FishingFinaleText, MSGBOX_DEFAULT
	goto TrioSilly_FishingReturn
TrioSilly_FishingReturn:
	closemessage
	clearflag FLAG_TEMP_HIDE_FOLLOWER
	warp MAP_CERULEAN_CITY_HOUSE1, 4, 7
	waitstate
	releaseall
	end
TrioSilly_FishingNotReady:
	msgbox TrioSilly_NotReadyText, MSGBOX_DEFAULT
	goto TrioSilly_FishingReturn

TrioSilly_ApologyOffer::
	lockall
	faceplayer
	msgbox TrioSilly_ApologyInviteText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioSilly_Decline
	closemessage
	warp MAP_TRIO_SILLY_APOLOGY, 4, 7
	waitstate
	releaseall
	end

TrioSilly_ApologyInviteText:
	.string "The Apology Department\nhas opened next door.\pNo actual belongings\nwill be taken.\pAttend the apology?$"

TrioSilly_ApologyRun::
	lockall
	setvar VAR_TEMP_A, 0
	special PrepareTrioSillyActors
	goto_if_eq VAR_RESULT, FALSE, TrioSilly_ApologyNotReady

	msgbox TrioSilly_ApologyOpeningText, MSGBOX_DEFAULT
	closemessage
	removeobject 7
	closemessage
	applymovement 6, TrioSilly_StealPaper
	waitmovement 0
	msgbox TrioSilly_ApologyTheftText, MSGBOX_DEFAULT
	closemessage
	removeobject 6
	msgbox TrioSilly_ApologyFinaleText, MSGBOX_DEFAULT
	goto TrioSilly_ApologyReturn
TrioSilly_ApologyReturn:
	closemessage
	clearflag FLAG_TEMP_HIDE_FOLLOWER
	warp MAP_TRIO_GREEDENT_CAFE, 3, 7
	waitstate
	releaseall
	end
TrioSilly_ApologyNotReady:
	msgbox TrioSilly_NotReadyText, MSGBOX_DEFAULT
	goto TrioSilly_ApologyReturn

TrioSilly_Decline:
	releaseall
	end
TrioSilly_Extra::
	msgbox TrioSilly_ExtraText, MSGBOX_NPC
	end

TrioSilly_NotReadyText:
	.string "The cast missed roll call.\pBack to the host.\nWe can try again!$"

TrioSilly_ExtraText:
	.string "Everyone is enjoying\na very silly afternoon.$"

TrioSilly_ValetOpeningText:
	.string "Attendant: Welcome to\nPenny's valet service!\pPlease present your keys.\pScott: I think I know\nwhere this is going.$"

TrioSilly_ValetKeysText:
	.string "The keys jingle.\pPenny's ears perk up.$"

TrioSilly_ValetFinaleText:
	.string "Attendant: Ma'am, your\nhot dog has arrived.\pScott: Five stars.\nExcellent service.\pPenny leans against you.\pRiko checks for snacks.\nBijuu refuses to tip.$"

TrioSilly_BoxOpeningText:
	.string "Curator: This box holds\na priceless artifact.\pNo touching. No chewing.\nAbsolutely no cats.$"

TrioSilly_BoxFinaleText:
	.string "Bijuu is sitting inside\nthe forbidden box.\pCurator: The artifact has\nrequested that we stop\ptouching her house.\pScott: That's fair.\nYou heard the artifact.\pRiko sniffs the corners.\nPenny guards the new home.$"

TrioSilly_NoiseOpeningText:
	.string "Official: Town ordinance\nnumber thirty-pom:\pNo barking after sunset.\nNo barking before sunset.\pNo barking DURING sunset.$"

TrioSilly_NoiseFinaleText:
	.string "The official pauses.\pOfficial: An exemption\nhas been granted.\pScott: Excellent ruling.\nVery reasonable citizen.\pBijuu files a complaint\nabout the complaint.\pPenny would like everyone\nto use their inside voice.$"

TrioSilly_HotdogOpeningText:
	.string "Vendor: That's the\nlongest hot dog I've seen.\pIs she on the menu?\pScott: That's my\nfavorite customer.$"

TrioSilly_HotdogFinaleText:
	.string "Vendor: My mistake!\nOne honorary pup cup.\pNothing goes in your Bag.\nPenny gets pretend cream.\pScott: Five stars for\nthe customer.\pRiko requests chicken.\nBijuu checks the receipt.$"

TrioSilly_JamOpeningText:
	.string "Official: Three Poms.\nOne dropped snack.\pWe tried negotiating.\nTheir demands are chicken.\pScott: Our finest minds\nare on the case.$"

TrioSilly_JamDealText:
	.string "Scott produces a pretend\npicnic chicken.\pRiko negotiates three\nequal imaginary portions.\pThe Poms accept the deal.$"

TrioSilly_JamFinaleText:
	.string "The road is clear!\pOfficial: Historic treaty.\nNo crumbs left behind.\pPenny approves the order.\nBijuu owns the paperwork.\pScott: Nice work, cute\ngirl. Traffic whisperer.$"

TrioSilly_FishingOpeningText:
	.string "Fisherman: My finest\ncatch all week!\pBijuu, have a look.\nStrictly an inspection.\pScott: Famous last words.$"

TrioSilly_FishingFinaleText:
	.string "The bucket is empty.\pFisherman: An unusually\nlocalized fishing\pshortage.\pBijuu looks innocent.\nShe has rehearsed this.\pRiko checks the bucket.\nPenny looks at Scott.\pScott: No witnesses.\nI was looking at you.$"

TrioSilly_ApologyOpeningText:
	.string "Clerk: On behalf of the\nsquirrel organization,\pplease accept our formal\nwritten apology.\pThis box contains\nall the apology forms.$"

TrioSilly_ApologyTheftText:
	.string "Another Greedent grabs\nthe entire box of forms!$"

TrioSilly_ApologyFinaleText:
	.string "Clerk: We apologize for\nstealing the apology.\pOur second apology will\narrive in six weeks.\pScott: Great turnaround.\nVery professional crime.\pBijuu takes the minutes.\nRiko demands chicken.\pPenny would prefer\na sincere pup cup.\pOnly their paper was\ntaken. Your Bag is safe.$"

TrioSilly_GregFan1Text:
	.string "Fan: Greg is incredible!\pYou: Greg?\pGreg: No. Independent\nsource number one.\pNothing beats the view.\nExcept my Garchomp.$"

TrioSilly_GregFan2Text:
	.string "Fan: Six level-99 Pokemon.\nVery modest. Very humble.\pYou: That's Greg in\na fishing hat.\pGreg: This is research.\nA different department.$"

TrioSilly_GregFan3Text:
	.string "Fan: I climbed a mountain\nto appreciate Greg.\pYou: Greg in a hiking hat?\pGreg: Independent sources\nagree I am incredible.$"

TrioSilly_GregFan4Text:
	.string "Fan: His Garchomp has\nexcellent cheekbones.\pYou: Another hat, Greg?\pGreg: A rigorous study\nneeds a large sample.$"

TrioSilly_GregFan5Text:
	.string "Fan: I am the chairman.\nAlso the entire committee.\pYou: Greg in a ninja hood.\pGreg: Scott booked dinner?\nI booked five\pendorsements.\pMembership fee: admitting\nmy Garchomp is incredible.$"

TrioSilly_GregScottText:
	.string "Scott: Five members.\nFive Gregs.\pI'm starting to question\nthe peer review.\pPenny wants to leave.\nBijuu stole the guestbook.\pRiko has voted chicken.\nUnanimous. Let's go.$"

TrioSilly_GregFan1::
	lock
	faceplayer
	msgbox TrioSilly_GregFan1Text, MSGBOX_DEFAULT
	release
	end

TrioSilly_GregFan2::
	lock
	faceplayer
	msgbox TrioSilly_GregFan2Text, MSGBOX_DEFAULT
	release
	end

TrioSilly_GregFan3::
	lock
	faceplayer
	msgbox TrioSilly_GregFan3Text, MSGBOX_DEFAULT
	release
	end

TrioSilly_GregFan4::
	lock
	faceplayer
	msgbox TrioSilly_GregFan4Text, MSGBOX_DEFAULT
	release
	end

TrioSilly_GregFan5::
	lock
	faceplayer
	msgbox TrioSilly_GregFan5Text, MSGBOX_DEFAULT
	release
	end

TrioSilly_GregScott::
	lock
	faceplayer
	msgbox TrioSilly_GregScottText, MSGBOX_DEFAULT
	release
	end

TrioSilly_ValetFetch:
	walk_down
	walk_right
	walk_right
	step_end

TrioSilly_BoxApproach:
	walk_up
	step_end

TrioSilly_Bark:
	face_right
	jump_in_place_down
	step_end

TrioSilly_HotdogApproach:
	walk_down
	walk_right
	step_end

TrioSilly_JamMarch:
	walk_down
	walk_down
	step_end

TrioSilly_FishInspect:
	walk_right
	walk_right
	step_end

TrioSilly_StealPaper:
	walk_down
	walk_right
	step_end

