@ Independent optional NPC duels; never a sight-triggered trainer battle.

TrioArenaCircuit_EcruteakCity::
	lockall
	faceplayer
	specialvar VAR_RESULT, GetTrioArenaChallengeState
	goto_if_eq VAR_RESULT, 0, TrioArenaCircuit_Locked0
	goto_if_eq VAR_RESULT, 2, TrioArenaCircuit_Claim
	goto_if_eq VAR_RESULT, 3, TrioArenaCircuit_Replay
	goto_if_eq VAR_RESULT, 4, TrioArenaCircuit_Error
	msgbox TrioArenaCircuit_Intro0, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Offer
TrioArenaCircuit_Locked0:
	msgbox TrioArenaCircuit_Gate0, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Intro0:
	.string "Haunter dances in echoes.\nCan your girls keep up?$"
TrioArenaCircuit_Gate0:
	.string "Earn four Gym Badges.\nThen try my Echo Duel!$"

TrioArenaCircuit_CianwoodCity::
	lockall
	faceplayer
	specialvar VAR_RESULT, GetTrioArenaChallengeState
	goto_if_eq VAR_RESULT, 0, TrioArenaCircuit_Locked1
	goto_if_eq VAR_RESULT, 2, TrioArenaCircuit_Claim
	goto_if_eq VAR_RESULT, 3, TrioArenaCircuit_Replay
	goto_if_eq VAR_RESULT, 4, TrioArenaCircuit_Error
	msgbox TrioArenaCircuit_Intro1, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Offer
TrioArenaCircuit_Locked1:
	msgbox TrioArenaCircuit_Gate1, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Intro1:
	.string "Machoke knows Pom Fu!\nDodge, then strike back!$"
TrioArenaCircuit_Gate1:
	.string "Bring five Gym Badges.\nPom Fu takes practice!$"

TrioArenaCircuit_OlivineCity::
	lockall
	faceplayer
	specialvar VAR_RESULT, GetTrioArenaChallengeState
	goto_if_eq VAR_RESULT, 0, TrioArenaCircuit_Locked2
	goto_if_eq VAR_RESULT, 2, TrioArenaCircuit_Claim
	goto_if_eq VAR_RESULT, 3, TrioArenaCircuit_Replay
	goto_if_eq VAR_RESULT, 4, TrioArenaCircuit_Error
	msgbox TrioArenaCircuit_Intro2, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Offer
TrioArenaCircuit_Locked2:
	msgbox TrioArenaCircuit_Gate2, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Intro2:
	.string "Magneton guards the port.\nWatch those spread sparks!$"
TrioArenaCircuit_Gate2:
	.string "Bring six Gym Badges.\nThen brave these sparks!$"

TrioArenaCircuit_Mahoganytown::
	lockall
	faceplayer
	specialvar VAR_RESULT, GetTrioArenaChallengeState
	goto_if_eq VAR_RESULT, 0, TrioArenaCircuit_Locked3
	goto_if_eq VAR_RESULT, 2, TrioArenaCircuit_Claim
	goto_if_eq VAR_RESULT, 3, TrioArenaCircuit_Replay
	goto_if_eq VAR_RESULT, 4, TrioArenaCircuit_Error
	msgbox TrioArenaCircuit_Intro3, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Offer
TrioArenaCircuit_Locked3:
	msgbox TrioArenaCircuit_Gate3, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Intro3:
	.string "Piloswine shakes the snow.\nKeep clear of that stomp!$"
TrioArenaCircuit_Gate3:
	.string "Earn seven Badges first.\nThen test your footwork!$"

TrioArenaCircuit_BlackthornCity::
	lockall
	faceplayer
	specialvar VAR_RESULT, GetTrioArenaChallengeState
	goto_if_eq VAR_RESULT, 0, TrioArenaCircuit_Locked4
	goto_if_eq VAR_RESULT, 2, TrioArenaCircuit_Claim
	goto_if_eq VAR_RESULT, 3, TrioArenaCircuit_Replay
	goto_if_eq VAR_RESULT, 4, TrioArenaCircuit_Error
	msgbox TrioArenaCircuit_Intro4, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Offer
TrioArenaCircuit_Locked4:
	msgbox TrioArenaCircuit_Gate4, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Intro4:
	.string "Dragonair has a trial.\nDodge, then strike back!$"
TrioArenaCircuit_Gate4:
	.string "Bring eight Gym Badges.\nThen face the dragon!$"

TrioArenaCircuit_PewterCity::
	lockall
	faceplayer
	specialvar VAR_RESULT, GetTrioArenaChallengeState
	goto_if_eq VAR_RESULT, 0, TrioArenaCircuit_Locked5
	goto_if_eq VAR_RESULT, 2, TrioArenaCircuit_Claim
	goto_if_eq VAR_RESULT, 3, TrioArenaCircuit_Replay
	goto_if_eq VAR_RESULT, 4, TrioArenaCircuit_Error
	msgbox TrioArenaCircuit_Intro5, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Offer
TrioArenaCircuit_Locked5:
	msgbox TrioArenaCircuit_Gate5, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Intro5:
	.string "Umbreon stalks the night.\nKeep your paws moving!$"
TrioArenaCircuit_Gate5:
	.string "Become League Champion.\nThen seek the moonlight!$"

TrioArenaCircuit_CeladonCity::
	lockall
	faceplayer
	specialvar VAR_RESULT, GetTrioArenaChallengeState
	goto_if_eq VAR_RESULT, 0, TrioArenaCircuit_Locked6
	goto_if_eq VAR_RESULT, 2, TrioArenaCircuit_Claim
	goto_if_eq VAR_RESULT, 3, TrioArenaCircuit_Replay
	goto_if_eq VAR_RESULT, 4, TrioArenaCircuit_Error
	msgbox TrioArenaCircuit_Intro6, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Offer
TrioArenaCircuit_Locked6:
	msgbox TrioArenaCircuit_Gate6, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Intro6:
	.string "Alakazam reads your path.\nBreak that psychic rhythm!$"
TrioArenaCircuit_Gate6:
	.string "Champion plus 12 Badges.\nThat earns you entry!$"

TrioArenaCircuit_SaffronCity::
	lockall
	faceplayer
	specialvar VAR_RESULT, GetTrioArenaChallengeState
	goto_if_eq VAR_RESULT, 0, TrioArenaCircuit_Locked7
	goto_if_eq VAR_RESULT, 2, TrioArenaCircuit_Claim
	goto_if_eq VAR_RESULT, 3, TrioArenaCircuit_Replay
	goto_if_eq VAR_RESULT, 4, TrioArenaCircuit_Error
	msgbox TrioArenaCircuit_Intro7, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Offer
TrioArenaCircuit_Locked7:
	msgbox TrioArenaCircuit_Gate7, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Intro7:
	.string "Tyranitar awaits you.\nShow me the trio spirit!$"
TrioArenaCircuit_Gate7:
	.string "Champion and 16 Badges.\nThen face my final trial!$"

TrioArenaCircuit_Offer:
	msgbox TrioArenaCircuit_OfferText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, TrioArenaCircuit_Close
TrioArenaCircuit_Start:
	closemessage
	special StartTrioActionChallenge
	goto_if_eq VAR_RESULT, FALSE, TrioArenaCircuit_Error
	waitstate
	goto_if_eq VAR_RESULT, 2, TrioArenaCircuit_Won
	goto_if_eq VAR_RESULT, 1, TrioArenaCircuit_Lost
	goto_if_eq VAR_RESULT, 3, TrioArenaCircuit_Error
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Lost:
	msgbox TrioArenaCircuit_RetryText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TrioArenaCircuit_Start
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Won:
	special RecordTrioArenaChallengeWin
	goto_if_eq VAR_RESULT, FALSE, TrioArenaCircuit_Error
TrioArenaCircuit_Claim:
	specialvar VAR_RESULT, ClaimTrioArenaChallengeReward
	goto_if_eq VAR_RESULT, 0, TrioArenaCircuit_Full
	goto_if_eq VAR_RESULT, 2, TrioArenaCircuit_Replay
	goto_if_ne VAR_RESULT, 1, TrioArenaCircuit_Error
	playfanfare MUS_OBTAIN_ITEM
	msgbox TrioArenaCircuit_PrizeText, MSGBOX_DEFAULT
	waitfanfare
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Full:
	msgbox TrioArenaCircuit_FullText, MSGBOX_DEFAULT
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Replay:
	msgbox TrioArenaCircuit_ReplayText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TrioArenaCircuit_Start
	goto TrioArenaCircuit_Close
TrioArenaCircuit_Error:
	msgbox TrioArenaCircuit_ErrorText, MSGBOX_DEFAULT
TrioArenaCircuit_Close:
	releaseall
	end
TrioArenaCircuit_OfferText:
	.string "One tough real-time duel.\nFirst win: one Riko Puff!\pA attacks. B is a special.\nR dodges. Hold L to aim.\pSTART pauses the fight.\nTake the challenge?$"
TrioArenaCircuit_RetryText:
	.string "A brave try! No penalty.\nWant to try again?$"
TrioArenaCircuit_PrizeText:
	.string "You earned one Riko Puff!\nSome fancy footwork there!$"
TrioArenaCircuit_FullText:
	.string "I saved your winning Puff!\nMake space, then return.$"
TrioArenaCircuit_ReplayText:
	.string "Your Puff was earned.\nPractice another round?$"
TrioArenaCircuit_ErrorText:
	.string "Give us a moment, please.\nPlease ask me again.$"
