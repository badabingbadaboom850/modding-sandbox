@ Route 37: one Bag Berry in persistent escrow, two physical hiding spots.
TrioSnack_Entry::
	goto_if_unset FLAG_BADGE03_GET, TrioSnack_End
	setvar VAR_FACING, DIR_NORTH
	lockall
	goto TrioSnack_Steal
TrioSnack_Start::
	lockall
	faceplayer
	goto_if_unset FLAG_BADGE03_GET, TrioSnack_Close
	goto_if_ne VAR_TRIO_SNACK_CHASE_STATE, 0, TrioSnack_Close
TrioSnack_Steal:
	special TrioSnack_BeginTheft
	goto_if_eq VAR_RESULT, FALSE, TrioSnack_Close
	special TrioSnack_BufferItem
	playmoncry SPECIES_GREEDENT, CRY_MODE_NORMAL
	waitmoncry
	msgbox TrioSnack_StolenText, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	goto_if_eq VAR_FACING, DIR_SOUTH, TrioSnack_StartEscapeDown
	applymovement 13, TrioSnack_RunUp
	goto TrioSnack_StartEscapeWait
TrioSnack_StartEscapeDown:
	applymovement 13, TrioSnack_RunDown
TrioSnack_StartEscapeWait:
	waitmovement 0
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	setflag FLAG_HIDE_TRIO_SNACK_START
	removeobject 13
	clearflag FLAG_HIDE_TRIO_SNACK_GRASS
	addobject 14
	msgbox TrioSnack_GrassHintText, MSGBOX_DEFAULT
	goto TrioSnack_Close

TrioSnack_Grass::
	lockall
	faceplayer
	goto_if_ne VAR_TRIO_SNACK_CHASE_STATE, 1, TrioSnack_Close
	msgbox TrioSnack_GrassText, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	goto_if_eq VAR_FACING, DIR_SOUTH, TrioSnack_GrassEscapeRight
	applymovement 14, TrioSnack_RunUp
	goto TrioSnack_GrassEscapeWait
TrioSnack_GrassEscapeRight:
	applymovement 14, TrioSnack_RunRight
TrioSnack_GrassEscapeWait:
	waitmovement 0
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	setvar VAR_TRIO_SNACK_CHASE_STATE, 2
	setflag FLAG_HIDE_TRIO_SNACK_GRASS
	removeobject 14
	clearflag FLAG_HIDE_TRIO_SNACK_GROVE
	addobject 15
	msgbox TrioSnack_GroveHintText, MSGBOX_DEFAULT
	goto TrioSnack_Close

TrioSnack_Grove::
	lockall
	faceplayer
	goto_if_eq VAR_TRIO_SNACK_CHASE_STATE, 3, TrioSnack_Reclaim
	goto_if_ne VAR_TRIO_SNACK_CHASE_STATE, 2, TrioSnack_Close
	msgbox TrioSnack_BattleOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioSnack_Close
	trainerbattle_no_intro TRAINER_ROUTE37_SNACK_THIEF, TrioSnack_DefeatText
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TrioSnack_Retry
	setvar VAR_TRIO_SNACK_CHASE_STATE, 3
TrioSnack_Reclaim:
	special TrioSnack_BufferItem
	special TrioSnack_ReturnItem
	goto_if_eq VAR_RESULT, FALSE, TrioSnack_FullBag
	msgbox TrioSnack_ReturnedText, MSGBOX_DEFAULT
	msgbox TrioSnack_MemoryText, MSGBOX_DEFAULT
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	setflag FLAG_HIDE_TRIO_SNACK_GROVE
	removeobject 15
	goto TrioSnack_Close
TrioSnack_FullBag:
	msgbox TrioSnack_FullBagText, MSGBOX_DEFAULT
	goto TrioSnack_Close
TrioSnack_Retry:
	msgbox TrioSnack_RetryText, MSGBOX_DEFAULT
	goto TrioSnack_Close

TrioSnack_Hint::
	goto_if_eq VAR_TRIO_SNACK_CHASE_STATE, 1, TrioSnack_GrassHint
	goto_if_eq VAR_TRIO_SNACK_CHASE_STATE, 2, TrioSnack_GroveHint
	goto_if_eq VAR_TRIO_SNACK_CHASE_STATE, 3, TrioSnack_PendingHint
	return
TrioSnack_GrassHint:
	msgbox TrioSnack_GrassHintText, MSGBOX_DEFAULT
	return
TrioSnack_GroveHint:
	msgbox TrioSnack_GroveHintText, MSGBOX_DEFAULT
	return
TrioSnack_PendingHint:
	msgbox TrioSnack_FullBagText, MSGBOX_DEFAULT
	return
TrioSnack_Checklist::
	goto_if_eq VAR_TRIO_SNACK_CHASE_STATE, 4, TrioSnack_SavedHint
	goto_if_ne VAR_TRIO_SNACK_CHASE_STATE, 0, TrioSnack_Hint
	msgbox TrioSnack_StartHintText, MSGBOX_DEFAULT
	return
TrioSnack_SavedHint:
	msgbox TrioSnack_SavedText, MSGBOX_DEFAULT
	return
TrioSnack_ReadMemory::
	msgbox TrioSnack_MemoryText, MSGBOX_DEFAULT
	return
TrioSnack_Close:
	closemessage
	releaseall
TrioSnack_End:
	end

TrioSnack_RunUp:
	walk_fast_up
	walk_fast_up
	step_end
TrioSnack_RunDown:
	walk_fast_down
	walk_fast_down
	step_end
TrioSnack_RunRight:
	walk_fast_right
	walk_fast_right
	step_end

TrioSnack_StolenText:
	.string "A Greedent grabs your\n{STR_VAR_1}!\pRiko looks outraged.\nThat was FAMILY food!$"
TrioSnack_GrassHintText:
	.string "Bijuu spots a bushy tail\nin the northern grass.\pLook just north of the\nledge, below Ecruteak.$"
TrioSnack_GrassText:
	.string "Caught you!\pGreedent freezes with its\npaws full of evidence.\pThen it bolts again.\nPenny sniffs the trail.$"
TrioSnack_GroveHintText:
	.string "Penny points east. Follow\nthe trail to the Berry\ptree in the eastern grove.\nThe snack thief is there!$"
TrioSnack_BattleOffer:
	.string "Greedent hugs the snack.\nNo more hiding spots!\pFight the level-22 thief\nto get it back? You heal\pafter either outcome.$"
TrioSnack_DefeatText:
	.string "The snack is surrendered!$"
TrioSnack_RetryText:
	.string "Everyone is healed.\nGreedent keeps the snack\pbeside the Berry tree.\nTry again when ready.$"
TrioSnack_ReturnedText:
	.string "You get your snack back:\n{STR_VAR_1}!$"
TrioSnack_FullBagText:
	.string "The thief gave up, but\nyour Bag cannot fit it.\pMake room, then return to\nGreedent by the tree.\pNo second battle needed.$"
TrioSnack_MemoryText:
	.string "The Great Snack Chase:\pBijuu tracked the thief.\nPenny found its hideout.\pRiko supervised lunch.\nVery loudly.\pYou got the snack back.\nGreedent got a lecture.$"
TrioSnack_StartHintText:
	.string "After Whitney, explore\nRoute 37's southern path.\pA greedy visitor has its\neye on the girls' snacks.$"
TrioSnack_SavedText:
	.string "Route 37: Snack rescued.\nSaved in Sister moments.$"
