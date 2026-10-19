TrioActionArena_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, TrioActionArena_Load
	.byte 0

TrioActionArena_Load:
	setvar VAR_TEMP_A, 1
	end

TrioActionArena_Offer::
	lockall
	faceplayer
	msgbox TrioActionArena_OfferText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioActionArena_Close
	closemessage
	warp MAP_TRIO_ACTION_ARENA, 12, 15
	waitstate
	releaseall
	end

TrioActionArena_Referee::
	lockall
	faceplayer
	msgbox TrioActionArena_Rules, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioActionArena_Close
	closemessage
	special StartTrioActionArena
	goto_if_eq VAR_RESULT, FALSE, TrioActionArena_Unavailable
	waitstate
	goto_if_eq VAR_RESULT, FALSE, TrioActionArena_Unavailable
	msgbox TrioActionArena_ReturnText, MSGBOX_DEFAULT
	goto TrioActionArena_Close

TrioActionArena_Unavailable:
	msgbox TrioActionArena_UnavailableText, MSGBOX_DEFAULT
	goto TrioActionArena_Close

TrioActionArena_Exit::
	lockall
	faceplayer
	msgbox TrioActionArena_ExitText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioActionArena_Close
	goto TrioActionArena_ReturnHome

TrioActionArena_WalkExit::
	lockall
TrioActionArena_ReturnHome:
	closemessage
	warp MAP_NEW_BARK_TOWN, 18, 12
	waitstate
	releaseall
	end

TrioActionArena_Riko::
	lockall
	msgbox TrioActionArena_RikoText, MSGBOX_DEFAULT
	goto TrioActionArena_Close
TrioActionArena_Bijuu::
	lockall
	msgbox TrioActionArena_BijuuText, MSGBOX_DEFAULT
	goto TrioActionArena_Close
TrioActionArena_Penny::
	lockall
	msgbox TrioActionArena_PennyText, MSGBOX_DEFAULT
TrioActionArena_Close:
	releaseall
	end

TrioActionArena_OfferText:
	.string "The girls have an arena!\nReal-time practice fights!\pMove, attack, and dodge.\nWant a free ride there?$"
TrioActionArena_Rules:
	.string "Scott: Ready for practice?\nChoose any of the girls!\pD-pad: move and aim.\nA: attack. B: special.\pR: dodge. Hold L to aim.\nSTART: pause or leave.\pThree rounds of Greedent!\nWatch the attack warnings!\pTraining HP is separate.\nYour party stays safe.\pNo items or money needed.\nShall we start?$"
TrioActionArena_ReturnText:
	.string "Scott: Nice moves, cutie!\nThe girls want an encore.\pTalk to me to play again.\nThe south guide goes home.$"
TrioActionArena_UnavailableText:
	.string "Please give us a moment.\nPlease ask me again.$"
TrioActionArena_ExitText:
	.string "Head back to New Bark?\nYou can return anytime!$"
TrioActionArena_RikoText:
	.string "Riko practices her bark.\nThe snacks look nervous.\pA sends a bark forward.\nB booms around her!$"
TrioActionArena_BijuuText:
	.string "Bijuu inspects the arena.\nShe requests more pillows.\pA sends a moon orb.\nB fans out slowing frost!$"
TrioActionArena_PennyText:
	.string "Penny has her sisters.\nShe is ready to be brave.\pA swipes close ahead.\nB charges with confidence!$"
