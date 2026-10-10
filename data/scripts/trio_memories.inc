@ Keepsakes use separate delivered flags from victories: a full Bag never
@ forces another boss fight. Mom can deliver any pending Spirit memento.
TrioMemories_Mom::
	call TrioGang_TryReclaim
	call TrioKeepsakes_TryRiko
	goto_if_eq VAR_RESULT, FALSE, TrioMemories_Return
	call TrioKeepsakes_TryPenny
	goto_if_eq VAR_RESULT, FALSE, TrioMemories_Return
	call TrioKeepsakes_TryBijuu
	goto_if_eq VAR_RESULT, FALSE, TrioMemories_Return
	goto_if_set FLAG_TRIO_SCRAPBOOK_RECEIVED, TrioMemories_Return
	goto_if_set FLAG_BADGE01_GET, TrioMemories_BookGiftScript
	goto_if_set FLAG_TRIO_PENNY_HOME_WIN, TrioMemories_BookGiftScript
	goto_if_unset FLAG_TRIO_BIJUU_HOME_WIN, TrioMemories_Return
TrioMemories_BookGiftScript:
	msgbox TrioMemories_BookGift, MSGBOX_DEFAULT
	giveitem ITEM_MOMS_SCRAPBOOK, 1
	goto_if_eq VAR_RESULT, FALSE, TrioKeepsakes_BagFull
	setflag FLAG_TRIO_SCRAPBOOK_RECEIVED
	msgbox TrioMemories_BookHelp, MSGBOX_DEFAULT
TrioMemories_Return:
	return

TrioKeepsakes_TryRiko::
	goto_if_unset FLAG_DEFEATED_SUICUNE, TrioKeepsakes_Return
	goto_if_set FLAG_TRIO_RIKO_KEEPSAKE, TrioKeepsakes_Return
	msgbox TrioKeepsakes_RikoGift, MSGBOX_DEFAULT
	giveitem ITEM_RIKOS_SPARK, 1
	goto_if_eq VAR_RESULT, FALSE, TrioKeepsakes_BagFull
	setflag FLAG_TRIO_RIKO_KEEPSAKE
	msgbox TrioKeepsakes_Help, MSGBOX_DEFAULT
TrioKeepsakes_ReturnRiko:
	setvar VAR_RESULT, TRUE
	return

TrioKeepsakes_TryPenny::
	goto_if_set FLAG_TRIO_PENNY_SPIRIT_COMPLETE, TrioKeepsakes_EligiblePenny
	goto_if_unset FLAG_TRIO_PENNY_HOME_WIN, TrioKeepsakes_Return
TrioKeepsakes_EligiblePenny:
	goto_if_set FLAG_TRIO_PENNY_KEEPSAKE, TrioKeepsakes_Return
	msgbox TrioKeepsakes_PennyGift, MSGBOX_DEFAULT
	giveitem ITEM_PENNYS_SHIELD, 1
	goto_if_eq VAR_RESULT, FALSE, TrioKeepsakes_BagFull
	setflag FLAG_TRIO_PENNY_KEEPSAKE
	msgbox TrioKeepsakes_Help, MSGBOX_DEFAULT
TrioKeepsakes_ReturnPenny:
	setvar VAR_RESULT, TRUE
	return

TrioKeepsakes_TryBijuu::
	goto_if_set FLAG_TRIO_BIJUU_SPIRIT_COMPLETE, TrioKeepsakes_EligibleBijuu
	goto_if_unset FLAG_TRIO_BIJUU_HOME_WIN, TrioKeepsakes_Return
TrioKeepsakes_EligibleBijuu:
	goto_if_set FLAG_TRIO_BIJUU_KEEPSAKE, TrioKeepsakes_Return
	msgbox TrioKeepsakes_BijuuGift, MSGBOX_DEFAULT
	giveitem ITEM_BIJUUS_LIGHT, 1
	goto_if_eq VAR_RESULT, FALSE, TrioKeepsakes_BagFull
	setflag FLAG_TRIO_BIJUU_KEEPSAKE
	msgbox TrioKeepsakes_Help, MSGBOX_DEFAULT
TrioKeepsakes_ReturnBijuu:
	setvar VAR_RESULT, TRUE
	return

TrioKeepsakes_Return:
	setvar VAR_RESULT, TRUE
	return
TrioKeepsakes_BagFull:
	msgbox TrioMemories_BagFullText, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	return

@ Same script for Bag and registered-key-item use. Nothing is consumed.
EventScript_TrioMemoryItem::
	lockall
	goto_if_eq VAR_0x8004, ITEM_RIKOS_SPARK, TrioMemory_ReadRiko
	goto_if_eq VAR_0x8004, ITEM_PENNYS_SHIELD, TrioMemory_ReadPenny
	goto_if_eq VAR_0x8004, ITEM_BIJUUS_LIGHT, TrioMemory_ReadBijuu
	goto_if_ne VAR_0x8004, ITEM_MOMS_SCRAPBOOK, TrioMemory_Close
	call TrioScrapbook_Menu
	goto TrioMemory_Close
TrioMemory_ReadRiko:
	msgbox TrioMemories_RikoLetter, MSGBOX_DEFAULT
	goto TrioMemory_Close
TrioMemory_ReadPenny:
	msgbox TrioHomeSpirit_PennyVictory, MSGBOX_DEFAULT
	goto TrioMemory_Close
TrioMemory_ReadBijuu:
	msgbox TrioHomeSpirit_BijuuVictory, MSGBOX_DEFAULT
TrioMemory_Close:
	closemessage
	releaseall
	end

@ The research boy keeps his original scrapbook and offers Mom's companion pages.
TrioScrapbook_Offer::
	msgbox TrioScrapbook_OfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMemories_Return
	call TrioScrapbook_Menu
	return

TrioScrapbook_Menu::
	msgbox TrioScrapbook_Title, MSGBOX_DEFAULT
	closemessage
	multichoice 0, 0, MULTI_TRIO_SCRAPBOOK, FALSE
	goto_if_eq VAR_RESULT, 0, TrioScrapbook_Journey
	goto_if_eq VAR_RESULT, 1, TrioScrapbook_Sisters
	goto_if_eq VAR_RESULT, 2, TrioScrapbook_Letters
	goto_if_eq VAR_RESULT, 3, TrioScrapbook_Checklist
	goto_if_eq VAR_RESULT, 4, TrioScott_Scrapbook
	return
TrioScrapbook_Journey:
	msgbox TrioScrapbook_OpeningPage, MSGBOX_DEFAULT
	call_if_set FLAG_BADGE01_GET, TrioScrapbook_FirstBadge
	call_if_set FLAG_BADGE03_GET, TrioScrapbook_GoldenrodBadge
	setvar VAR_0x8004, SPECIES_PENNY_SPIRIT
	specialvar VAR_RESULT, CheckTrioSpiritMilestone
	call_if_eq VAR_RESULT, TRUE, TrioScrapbook_EightBadges
	call_if_set FLAG_IS_CHAMPION, TrioScrapbook_Champion
	call_if_set FLAG_TRIO_CHAMPION_PICNIC, TrioScrapbook_PicnicLetter
	goto TrioScrapbook_Menu
TrioScrapbook_Sisters:
	msgbox TrioScrapbook_SistersIntro, MSGBOX_DEFAULT
	call_if_set FLAG_TRIO_SISTERS_AZALEA, TrioScrapbook_Azalea
	call_if_set FLAG_TRIO_SISTERS_GOLDENROD, TrioScrapbook_Goldenrod
	call_if_set FLAG_TRIO_SISTERS_OLIVINE, TrioScrapbook_Olivine
	call_if_set FLAG_TRIO_POM_PARTY_SEEN, TrioScrapbook_PomParty
	call_if_set FLAG_TRIO_SISTERS_CERULEAN, TrioScrapbook_Cerulean
	call_if_set FLAG_TRIO_SISTERS_VERMILION, TrioScrapbook_Vermilion
	call_if_set FLAG_TRIO_SISTERS_CELADON, TrioScrapbook_Celadon
	call_if_set FLAG_TRIO_CAMP_MEMORY, TrioCamp_ReadMemory
	call_if_set FLAG_TRIO_FESTIVAL_PICNIC, TrioFestival_ReadMemory
	call_if_eq VAR_TRIO_SNACK_CHASE_STATE, 4, TrioSnack_ReadMemory
	call_if_ge VAR_TRIO_RIFT_RIKO_STATE, 4, TrioRift_ReadMemory
	call_if_ge VAR_TRIO_RIFT_BIJUU_STATE, 4, TrioMirror_ReadMemory
	call_if_ge VAR_TRIO_RIFT_PENNY_STATE, 4, TrioLantern_ReadMemory
	call_if_eq VAR_TRIO_GANG_WINS, 6, TrioGang_ReadMemory
	goto TrioScrapbook_Menu
TrioScrapbook_Letters:
	msgbox TrioScrapbook_LettersIntro, MSGBOX_DEFAULT
	call_if_set FLAG_DEFEATED_SUICUNE, TrioScrapbook_RikoLetter
	call TrioScrapbook_CheckPennyLetter
	call TrioScrapbook_CheckBijuuLetter
	goto TrioScrapbook_Menu

TrioScrapbook_FirstBadge::
	msgbox TrioScrapbook_FirstBadgePage, MSGBOX_DEFAULT
	return

TrioScrapbook_GoldenrodBadge::
	msgbox TrioScrapbook_GoldenrodBadgePage, MSGBOX_DEFAULT
	return

TrioScrapbook_EightBadges::
	msgbox TrioScrapbook_EightBadgesPage, MSGBOX_DEFAULT
	return

TrioScrapbook_Champion::
	msgbox TrioScrapbook_ChampionPage, MSGBOX_DEFAULT
	return

TrioScrapbook_Azalea::
	msgbox TrioScrapbook_AzaleaPage, MSGBOX_DEFAULT
	return

TrioScrapbook_Goldenrod::
	msgbox TrioScrapbook_GoldenrodPage, MSGBOX_DEFAULT
	return

TrioScrapbook_Olivine::
	msgbox TrioScrapbook_OlivinePage, MSGBOX_DEFAULT
	return

TrioScrapbook_PomParty::
	msgbox TrioScrapbook_PomPartyPage, MSGBOX_DEFAULT
	return

TrioScrapbook_RikoLetter::
	msgbox TrioMemories_RikoLetter, MSGBOX_DEFAULT
	return

TrioScrapbook_PennyLetter::
	msgbox TrioHomeSpirit_PennyVictory, MSGBOX_DEFAULT
	return

TrioScrapbook_BijuuLetter::
	msgbox TrioHomeSpirit_BijuuVictory, MSGBOX_DEFAULT
	return

@ Optional sister scenes; recorded pages remain readable with the girls in the PC.
TrioSisters_CheckAll::
	call TrioParty_CheckRiko
	goto_if_eq VAR_RESULT, FALSE, TrioMemories_Return
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, FALSE, TrioMemories_Return
	call TrioParty_CheckPenny
	return

TrioSisters_Azalea::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE01_GET, TrioSisters_NotYet
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioSisters_BringGirls
	msgbox TrioSisters_AzaleaOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioSisters_End
	msgbox TrioSisters_AzaleaScene, MSGBOX_DEFAULT
	goto_if_set FLAG_TRIO_SISTERS_AZALEA, TrioSisters_End
	setflag FLAG_TRIO_SISTERS_AZALEA
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	goto TrioSisters_End

TrioSisters_Goldenrod::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE02_GET, TrioSisters_NotYet
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioSisters_BringGirls
	msgbox TrioSisters_GoldenrodOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioSisters_End
	msgbox TrioSisters_GoldenrodScene, MSGBOX_DEFAULT
	goto_if_set FLAG_TRIO_SISTERS_GOLDENROD, TrioSisters_End
	setflag FLAG_TRIO_SISTERS_GOLDENROD
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	goto TrioSisters_End

TrioSisters_Olivine::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE04_GET, TrioSisters_NotYet
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioSisters_BringGirls
	msgbox TrioSisters_OlivineOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioSisters_End
	msgbox TrioSisters_OlivineScene, MSGBOX_DEFAULT
	goto_if_set FLAG_TRIO_SISTERS_OLIVINE, TrioSisters_End
	setflag FLAG_TRIO_SISTERS_OLIVINE
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	goto TrioSisters_End

TrioSisters_NotYet:
	msgbox TrioSisters_NotYetText, MSGBOX_DEFAULT
	goto TrioSisters_End
TrioSisters_BringGirls:
	msgbox TrioSisters_BringGirlsText, MSGBOX_DEFAULT
TrioSisters_End:
	closemessage
	release
	end

@ A repeatable party in an ordinary midgame house. No items or story gates.
TrioPomParty_OnTransition::
	setvar VAR_TEMP_A, FALSE
	goto_if_set FLAG_TRIO_POM_PARTY_SEEN, TrioPomParty_EntryEnd
	setvar VAR_TEMP_A, TRUE
TrioPomParty_EntryEnd:
	end
TrioPomParty_OnFrame::
	map_script_2 VAR_TEMP_A, TRUE, TrioPomParty_Welcome
	.2byte 0
TrioPomParty_Welcome::
	lockall
	setvar VAR_TEMP_A, FALSE
	msgbox TrioPomParty_HostText, MSGBOX_DEFAULT
	setflag FLAG_TRIO_POM_PARTY_SEEN
	closemessage
	releaseall
	end
TrioPomParty_Pom::
	lock
	faceplayer
	playmoncry SPECIES_RIKO, CRY_MODE_NORMAL
	msgbox TrioPomParty_PomText, MSGBOX_DEFAULT
	waitmoncry
	release
	end

TrioMemories_BookGift:
	.string "Mom: I made a little book\n"
	.string "for our girls.\p"
	.string "Not just the big\n"
	.string "victories. The little\p"
	.string "days, too.\p"
	.string "Some pages look like they\n"
	.string "were written with paws.$"

TrioMemories_BookHelp:
	.string "Use Mom's Scrapbook in KEY\n"
	.string "ITEMS to choose a chapter.\p"
	.string "Milestones add memories.\n"
	.string "Sister moments add pages.\p"
	.string "The research boy also\n"
	.string "keeps a copy of these\p"
	.string "pages.$"

TrioMemories_BagFullText:
	.string "There is no room for this\n"
	.string "memory in your Bag.\p"
	.string "Make space in KEY ITEMS,\n"
	.string "then visit Mom again.\p"
	.string "Penny and Bijuu can also\n"
	.string "keep their gifts for you.$"

TrioKeepsakes_RikoGift:
	.string "Mom: Riko left a tiny\n"
	.string "spark for you. It never\p"
	.string "burns.\p"
	.string "Her Spirit knows how much\n"
	.string "courage you gave her.$"

TrioKeepsakes_PennyGift:
	.string "A tiny shield settles into\n"
	.string "your hand.\p"
	.string "She learned what safety\n"
	.string "felt like. Now she carries\p"
	.string "it for you.$"

TrioKeepsakes_BijuuGift:
	.string "A blue light curls into a\n"
	.string "little charm.\p"
	.string "Warm as your little cocoa.\n"
	.string "Bright as her love for\p"
	.string "Mom.$"

TrioKeepsakes_Help:
	.string "Use this keepsake in KEY\n"
	.string "ITEMS to read her letter.\p"
	.string "It will always be there\n"
	.string "when you need it.$"

TrioMemories_RikoLetter:
	.string "The little spark trembles\n"
	.string "like an excited tail.\p"
	.string "Mom, I know I am little. I\n"
	.string "have checked.\p"
	.string "But you never made my love\n"
	.string "feel little.\p"
	.string "You listened to my biggest\n"
	.string "barks. You held my\p"
	.string "smallest paws.\p"
	.string "Every time you came home,\n"
	.string "I had to tell the whole\p"
	.string "world.\p"
	.string "My favorite person was\n"
	.string "here again.\p"
	.string "If being brave means\n"
	.string "loving with all you\p"
	.string "have...\p"
	.string "You taught me how before I\n"
	.string "ever became a Spirit.\p"
	.string "I will always be your\n"
	.string "little Pom.\p"
	.string "And you will always be my\n"
	.string "whole world.$"

TrioScrapbook_OfferText:
	.string "There are new pages\n"
	.string "written for Mom by the\p"
	.string "girls.\p"
	.string "Want to read their\n"
	.string "companion scrapbook?$"

TrioScrapbook_Title:
	.string "Mom's Scrapbook\p"
	.string "A journey in little\n"
	.string "pawprints. Choose some\p"
	.string "pages.$"

TrioScrapbook_OpeningPage:
	.string "Our journey - Riko\p"
	.string "Mom packed for an\n"
	.string "adventure. I packed my\p"
	.string "whole heart.\p"
	.string "Penny stayed close. Bijuu\n"
	.string "investigated absolutely\p"
	.string "everything.\p"
	.string "I made sure everyone knew\n"
	.string "we had arrived.\p"
	.string "We do not know how far we\n"
	.string "will go.\p"
	.string "We know who we want beside\n"
	.string "us.$"

TrioScrapbook_FirstBadgePage:
	.string "The first Badge - Penny\p"
	.string "Mom, I watched you try\n"
	.string "again when things were\p"
	.string "hard.\p"
	.string "You never looked at me\n"
	.string "like I was falling behind.\p"
	.string "I took one more step\n"
	.string "today.\p"
	.string "You smiled like I had won\n"
	.string "the whole League.$"

TrioScrapbook_GoldenrodBadgePage:
	.string "Goldenrod - Riko\p"
	.string "Three Badges! I celebrated\n"
	.string "with at least twelve\p"
	.string "barks.\p"
	.string "Bijuu says that is too\n"
	.string "many. Bijuu is wrong.\p"
	.string "Penny leaned against Mom.\n"
	.string "I leaned against Penny.\p"
	.string "We are very good at being\n"
	.string "a family.$"

TrioScrapbook_EightBadgesPage:
	.string "Eight Badges - Bijuu\p"
	.string "Mom has eight shiny\n"
	.string "things. I checked every\p"
	.string "one.\p"
	.string "She thinks this is the big\n"
	.string "achievement.\p"
	.string "I think it is the way\n"
	.string "Penny walks a little\p"
	.string "taller now.\p"
	.string "And how Riko still looks\n"
	.string "back to count us.\p"
	.string "We have grown. Mom has\n"
	.string "been loving us the whole\p"
	.string "time.$"

TrioScrapbook_ChampionPage:
	.string "Champion - Penny\p"
	.string "Everyone cheered for Mom.\n"
	.string "We were already doing\p"
	.string "that.\p"
	.string "They call her Champion\n"
	.string "now.\p"
	.string "We have another name for\n"
	.string "the person who makes us\p"
	.string "feel safe.\p"
	.string "Home.$"

TrioScrapbook_SistersIntro:
	.string "Little sister moments:\n"
	.string "Johto's Poke Center Lasses\p"
	.string "have stories to share.\n"
	.string "After the League, Kanto\p"
	.string "has new little adventures.\n"
	.string "The Memory checklist can\p"
	.string "help you find each page.$"

TrioScrapbook_LettersIntro:
	.string "Letters from the Spirits\p"
	.string "Their letters appear after\n"
	.string "you meet and overcome each\p"
	.string "Spirit.\p"
	.string "Love leaves something you\n"
	.string "can come back to.$"

TrioScrapbook_AzaleaPage:
	.string "Bijuu's note - Azalea\p"
	.string "I investigated a leaf.\n"
	.string "Riko declared a major\p"
	.string "emergency.\p"
	.string "Penny stood beside me.\n"
	.string "Very brave. Very serious.\p"
	.string "The leaf survived. So did\n"
	.string "my dignity. Mostly.$"

TrioScrapbook_GoldenrodPage:
	.string "Riko's note - Goldenrod\p"
	.string "Mom shared a quiet bench\n"
	.string "with us after the crowds.\p"
	.string "Penny got the closest\n"
	.string "spot. Bijuu got the\p"
	.string "sunbeam.\p"
	.string "I got to tell them how\n"
	.string "good a job I was doing.\p"
	.string "Nobody asked me to stop.$"

TrioScrapbook_OlivinePage:
	.string "Penny's note - Olivine\p"
	.string "The sea wind was loud.\n"
	.string "Bijuu tucked herself\p"
	.string "beside me.\p"
	.string "I thought I was the one\n"
	.string "who needed protecting.\p"
	.string "Then my sisters leaned on\n"
	.string "me.\p"
	.string "Mom, I think I can do\n"
	.string "this.$"

TrioScrapbook_PomPartyPage:
	.string "Riko's extremely official\n"
	.string "party report\p"
	.string "Four Poms. One circle.\n"
	.string "Unlimited enthusiasm.\p"
	.string "Ain't no party like a pom\n"
	.string "party!\p"
	.string "Mom laughed. Best party\n"
	.string "ever.$"

TrioSisters_NotYetText:
	.string "Your girls have a whole\n"
	.string "adventure ahead of them.\p"
	.string "Come back after your next\n"
	.string "big step together.$"

TrioSisters_BringGirlsText:
	.string "Bring Riko, Penny and\n"
	.string "Bijuu together.\p"
	.string "Little sister moments are\n"
	.string "best shared by all three.$"

TrioSisters_Recorded:
	.string "You save this little\n"
	.string "moment in Mom's Scrapbook.\p"
	.string "You can read it again\n"
	.string "anytime.$"

TrioSisters_AzaleaOffer:
	.string "I saw your girls near the\n"
	.string "trees. Quite a little\p"
	.string "team!\p"
	.string "Want to hear what they got\n"
	.string "up to?$"

TrioSisters_AzaleaScene:
	.string "Bijuu pounces on a leaf.\n"
	.string "It rustles back.\p"
	.string "Riko announces the threat\n"
	.string "with a very important\p"
	.string "bark.\p"
	.string "Penny hesitates... then\n"
	.string "stands beside Bijuu.\p"
	.string "Bijuu taps Penny's paw.\n"
	.string "One more pounce. Together.\p"
	.string "Riko looks at Mom as if to\n"
	.string "say: I handled that.\p"
	.string "Three sisters. One\n"
	.string "defeated leaf.$"

TrioSisters_GoldenrodOffer:
	.string "Your girls found a quiet\n"
	.string "bench away from the\p"
	.string "crowds.\p"
	.string "Want to hear their little\n"
	.string "moment?$"

TrioSisters_GoldenrodScene:
	.string "Penny leaves a spot beside\n"
	.string "Mom for each sister.\p"
	.string "Bijuu finds the sunniest\n"
	.string "bit and stretches right\p"
	.string "across it.\p"
	.string "Riko squeezes between\n"
	.string "them. Of course she fits.\p"
	.string "Penny gently scoots over.\n"
	.string "Nobody gets left out.\p"
	.string "For a minute, the big city\n"
	.string "is just your little\p"
	.string "family.$"

TrioSisters_OlivineOffer:
	.string "I saw your girls looking\n"
	.string "out toward the sea.\p"
	.string "Want to hear what\n"
	.string "happened?$"

TrioSisters_OlivineScene:
	.string "A sea breeze catches\n"
	.string "Bijuu's whiskers. She\p"
	.string "leans into Penny.\p"
	.string "Penny plants her paws and\n"
	.string "stands a little taller.\p"
	.string "Riko marches around them,\n"
	.string "supervising the entire\p"
	.string "ocean.\p"
	.string "Penny glances back at Mom.\p"
	.string "Then she stays right\n"
	.string "there, sheltering her\p"
	.string "sisters.\p"
	.string "Sometimes courage looks\n"
	.string "like being somebody's safe\p"
	.string "place.$"

TrioPomParty_HostText:
	.string "Host: Ain't no party like\n"
	.string "a pom party!\p"
	.string "Round and round they go.\n"
	.string "Nobody knows who started\p"
	.string "it.\p"
	.string "Nobody wants to stop!$"

TrioPomParty_PomText:
	.string "Pom: Pom! Pom!\p"
	.string "One happy bark, then right\n"
	.string "back to the party.$"


TrioScrapbook_CheckPennyLetter::
	goto_if_set FLAG_TRIO_PENNY_SPIRIT_COMPLETE, TrioScrapbook_PennyLetter
	goto_if_set FLAG_TRIO_PENNY_HOME_WIN, TrioScrapbook_PennyLetter
	return

TrioScrapbook_CheckBijuuLetter::
	goto_if_set FLAG_TRIO_BIJUU_SPIRIT_COMPLETE, TrioScrapbook_BijuuLetter
	goto_if_set FLAG_TRIO_BIJUU_HOME_WIN, TrioScrapbook_BijuuLetter
	return

@ Kanto sister memories and Champion family picnic.

TrioKanto_PrepareCerulean::
	setvar VAR_TEMP_A, FALSE
	goto_if_set FLAG_TRIO_SISTERS_CERULEAN, TrioMemories_Return
	goto_if_unset FLAG_IS_CHAMPION, TrioMemories_Return
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioMemories_Return
	setvar VAR_TEMP_A, TRUE
	return
TrioKanto_CeruleanOnFrame::
	map_script_2 VAR_TEMP_A, TRUE, TrioKanto_CeruleanArrival
	.2byte 0
TrioKanto_CeruleanArrival::
	lockall
	setvar VAR_TEMP_A, FALSE
	call TrioKanto_PlayCerulean
	closemessage
	releaseall
	end

TrioKanto_CeruleanOffer::
	lockall
	goto_if_unset FLAG_IS_CHAMPION, TrioKanto_NotYet
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioKanto_BringGirls
	msgbox TrioKanto_CeruleanOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioKanto_OfferEnd
	call TrioKanto_PlayCerulean
	goto TrioKanto_OfferEnd
TrioKanto_PlayCerulean::
	msgbox TrioKanto_CeruleanScene, MSGBOX_DEFAULT
	goto_if_set FLAG_TRIO_SISTERS_CERULEAN, TrioMemories_Return
	setflag FLAG_TRIO_SISTERS_CERULEAN
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	return
TrioScrapbook_Cerulean::
	msgbox TrioKanto_CeruleanScene, MSGBOX_DEFAULT
	return

TrioKanto_PrepareVermilion::
	setvar VAR_TEMP_A, FALSE
	goto_if_set FLAG_TRIO_SISTERS_VERMILION, TrioMemories_Return
	goto_if_unset FLAG_IS_CHAMPION, TrioMemories_Return
	goto_if_eq VAR_SUICUNE_ENCOUNTERS, 3, TrioMemories_Return
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioMemories_Return
	setvar VAR_TEMP_A, TRUE
	return
TrioKanto_VermilionOnFrame::
	map_script_2 VAR_TEMP_A, TRUE, TrioKanto_VermilionArrival
	.2byte 0
TrioKanto_VermilionArrival::
	lockall
	setvar VAR_TEMP_A, FALSE
	call TrioKanto_PlayVermilion
	closemessage
	releaseall
	end

TrioKanto_VermilionOffer::
	lockall
	goto_if_unset FLAG_IS_CHAMPION, TrioKanto_NotYet
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioKanto_BringGirls
	msgbox TrioKanto_VermilionOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioKanto_OfferEnd
	call TrioKanto_PlayVermilion
	goto TrioKanto_OfferEnd
TrioKanto_PlayVermilion::
	msgbox TrioKanto_VermilionScene, MSGBOX_DEFAULT
	goto_if_set FLAG_TRIO_SISTERS_VERMILION, TrioMemories_Return
	setflag FLAG_TRIO_SISTERS_VERMILION
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	return
TrioScrapbook_Vermilion::
	msgbox TrioKanto_VermilionScene, MSGBOX_DEFAULT
	return

TrioKanto_CeladonOffer::
	lockall
	goto_if_unset FLAG_IS_CHAMPION, TrioKanto_NotYet
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioKanto_BringGirls
	msgbox TrioKanto_CeladonOfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioKanto_OfferEnd
	call TrioKanto_PlayCeladon
	goto TrioKanto_OfferEnd
TrioKanto_PlayCeladon::
	msgbox TrioKanto_CeladonScene, MSGBOX_DEFAULT
	goto_if_set FLAG_TRIO_SISTERS_CELADON, TrioMemories_Return
	setflag FLAG_TRIO_SISTERS_CELADON
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	return
TrioScrapbook_Celadon::
	msgbox TrioKanto_CeladonScene, MSGBOX_DEFAULT
	return

TrioKanto_NotYet:
	msgbox TrioKanto_NotYetText, MSGBOX_DEFAULT
	goto TrioKanto_OfferEnd
TrioKanto_BringGirls:
	msgbox TrioSisters_BringGirlsText, MSGBOX_DEFAULT
TrioKanto_OfferEnd:
	closemessage
	releaseall
	return
TrioChampionPicnic_Offer::
	goto_if_unset FLAG_IS_CHAMPION, TrioMemories_Return
	goto_if_set FLAG_TRIO_CHAMPION_PICNIC, TrioMemories_Return
	call TrioSisters_CheckAll
	goto_if_eq VAR_RESULT, FALSE, TrioChampionPicnic_MissingGirls
	msgbox TrioChampionPicnic_OfferText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioMemories_Return
	msgbox TrioChampionPicnic_Scene, MSGBOX_DEFAULT
	msgbox TrioChampionPicnic_ScottLetter, MSGBOX_DEFAULT
	setflag FLAG_TRIO_CHAMPION_PICNIC
	msgbox TrioChampionPicnic_Recorded, MSGBOX_DEFAULT
	return
TrioChampionPicnic_MissingGirls:
	msgbox TrioChampionPicnic_BringGirls, MSGBOX_DEFAULT
	return
TrioScrapbook_PicnicLetter::
	msgbox TrioChampionPicnic_ScottLetter, MSGBOX_DEFAULT
	return
TrioScrapbook_Checklist::
	msgbox TrioChecklist_Intro, MSGBOX_DEFAULT
	call TrioChecklist_FirstBadge
	call TrioChecklist_GoldenrodBadge
	call TrioChecklist_Champion
	call TrioChecklist_Azalea
	call TrioChecklist_Goldenrod
	call TrioChecklist_Olivine
	call TrioChecklist_Pom
	call TrioChecklist_Cerulean
	call TrioChecklist_Vermilion
	call TrioChecklist_Celadon
	call TrioChecklist_RikoLetter
	call TrioChecklist_PennyLetter
	call TrioChecklist_BijuuLetter
	call TrioChecklist_Picnic
	call TrioCamp_Checklist
	call TrioFestival_Checklist
	call TrioScott_Checklist
	call TrioSnack_Checklist
	call TrioRift_Checklist
	call TrioGang_Checklist
	call TrioChecklist_EightBadges
	goto TrioScrapbook_Menu

TrioChecklist_FirstBadge::
	goto_if_set FLAG_BADGE01_GET, TrioChecklist_FirstBadgeDone
	msgbox TrioChecklist_FirstBadgeHint, MSGBOX_DEFAULT
	return
TrioChecklist_FirstBadgeDone:
	msgbox TrioChecklist_FirstBadgeSaved, MSGBOX_DEFAULT
	return

TrioChecklist_GoldenrodBadge::
	goto_if_set FLAG_BADGE03_GET, TrioChecklist_GoldenrodBadgeDone
	msgbox TrioChecklist_GoldenrodBadgeHint, MSGBOX_DEFAULT
	return
TrioChecklist_GoldenrodBadgeDone:
	msgbox TrioChecklist_GoldenrodBadgeSaved, MSGBOX_DEFAULT
	return

TrioChecklist_Champion::
	goto_if_set FLAG_IS_CHAMPION, TrioChecklist_ChampionDone
	msgbox TrioChecklist_ChampionHint, MSGBOX_DEFAULT
	return
TrioChecklist_ChampionDone:
	msgbox TrioChecklist_ChampionSaved, MSGBOX_DEFAULT
	return

TrioChecklist_Azalea::
	goto_if_set FLAG_TRIO_SISTERS_AZALEA, TrioChecklist_AzaleaDone
	msgbox TrioChecklist_AzaleaHint, MSGBOX_DEFAULT
	return
TrioChecklist_AzaleaDone:
	msgbox TrioChecklist_AzaleaSaved, MSGBOX_DEFAULT
	return

TrioChecklist_Goldenrod::
	goto_if_set FLAG_TRIO_SISTERS_GOLDENROD, TrioChecklist_GoldenrodDone
	msgbox TrioChecklist_GoldenrodHint, MSGBOX_DEFAULT
	return
TrioChecklist_GoldenrodDone:
	msgbox TrioChecklist_GoldenrodSaved, MSGBOX_DEFAULT
	return

TrioChecklist_Olivine::
	goto_if_set FLAG_TRIO_SISTERS_OLIVINE, TrioChecklist_OlivineDone
	msgbox TrioChecklist_OlivineHint, MSGBOX_DEFAULT
	return
TrioChecklist_OlivineDone:
	msgbox TrioChecklist_OlivineSaved, MSGBOX_DEFAULT
	return

TrioChecklist_Pom::
	goto_if_set FLAG_TRIO_POM_PARTY_SEEN, TrioChecklist_PomDone
	msgbox TrioChecklist_PomHint, MSGBOX_DEFAULT
	return
TrioChecklist_PomDone:
	msgbox TrioChecklist_PomSaved, MSGBOX_DEFAULT
	return

TrioChecklist_Cerulean::
	goto_if_set FLAG_TRIO_SISTERS_CERULEAN, TrioChecklist_CeruleanDone
	msgbox TrioChecklist_CeruleanHint, MSGBOX_DEFAULT
	return
TrioChecklist_CeruleanDone:
	msgbox TrioChecklist_CeruleanSaved, MSGBOX_DEFAULT
	return

TrioChecklist_Vermilion::
	goto_if_set FLAG_TRIO_SISTERS_VERMILION, TrioChecklist_VermilionDone
	msgbox TrioChecklist_VermilionHint, MSGBOX_DEFAULT
	return
TrioChecklist_VermilionDone:
	msgbox TrioChecklist_VermilionSaved, MSGBOX_DEFAULT
	return

TrioChecklist_Celadon::
	goto_if_set FLAG_TRIO_SISTERS_CELADON, TrioChecklist_CeladonDone
	msgbox TrioChecklist_CeladonHint, MSGBOX_DEFAULT
	return
TrioChecklist_CeladonDone:
	msgbox TrioChecklist_CeladonSaved, MSGBOX_DEFAULT
	return

TrioChecklist_RikoLetter::
	goto_if_set FLAG_DEFEATED_SUICUNE, TrioChecklist_RikoLetterDone
	msgbox TrioChecklist_RikoLetterHint, MSGBOX_DEFAULT
	return
TrioChecklist_RikoLetterDone:
	msgbox TrioChecklist_RikoLetterSaved, MSGBOX_DEFAULT
	return

TrioChecklist_PennyLetter::
	goto_if_set FLAG_TRIO_PENNY_SPIRIT_COMPLETE, TrioChecklist_PennyLetterDone
	goto_if_set FLAG_TRIO_PENNY_HOME_WIN, TrioChecklist_PennyLetterDone
	msgbox TrioChecklist_PennyLetterHint, MSGBOX_DEFAULT
	return
TrioChecklist_PennyLetterDone:
	msgbox TrioChecklist_PennyLetterSaved, MSGBOX_DEFAULT
	return

TrioChecklist_BijuuLetter::
	goto_if_set FLAG_TRIO_BIJUU_SPIRIT_COMPLETE, TrioChecklist_BijuuLetterDone
	goto_if_set FLAG_TRIO_BIJUU_HOME_WIN, TrioChecklist_BijuuLetterDone
	msgbox TrioChecklist_BijuuLetterHint, MSGBOX_DEFAULT
	return
TrioChecklist_BijuuLetterDone:
	msgbox TrioChecklist_BijuuLetterSaved, MSGBOX_DEFAULT
	return

TrioChecklist_Picnic::
	goto_if_set FLAG_TRIO_CHAMPION_PICNIC, TrioChecklist_PicnicDone
	msgbox TrioChecklist_PicnicHint, MSGBOX_DEFAULT
	return
TrioChecklist_PicnicDone:
	msgbox TrioChecklist_PicnicSaved, MSGBOX_DEFAULT
	return

TrioChecklist_EightBadges::
	setvar VAR_0x8004, SPECIES_PENNY_SPIRIT
	specialvar VAR_RESULT, CheckTrioSpiritMilestone
	goto_if_eq VAR_RESULT, TRUE, TrioChecklist_EightBadgesDone
	msgbox TrioChecklist_EightBadgesHint, MSGBOX_DEFAULT
	return
TrioChecklist_EightBadgesDone:
	msgbox TrioChecklist_EightBadgesSaved, MSGBOX_DEFAULT
	return

TrioKanto_NotYetText:
	.string "There are little\n"
	.string "adventures waiting for\p"
	.string "your girls in Kanto. Come\n"
	.string "back after the League.$"

TrioKanto_CeruleanOfferText:
	.string "Your girls had quite a\n"
	.string "discovery here. Want to\p"
	.string "share their little moment?$"

TrioKanto_VermilionOfferText:
	.string "I saw your girls watching\n"
	.string "the harbor. Want to share\p"
	.string "their little moment?$"

TrioKanto_CeladonOfferText:
	.string "Your girls found a quiet\n"
	.string "spot by the fountain. Want\p"
	.string "to hear about it?$"

TrioKanto_CeruleanScene:
	.string "Bijuu finds her reflection\n"
	.string "in a little puddle. A\p"
	.string "suspicious cocoa. She taps\n"
	.string "it. The cocoa taps back.\p"
	.string "Riko gives a very serious\n"
	.string "warning bark. Penny puts\p"
	.string "one paw beside Bijuu's.\n"
	.string "Two sisters in the water\p"
	.string "now. Bijuu looks up at\n"
	.string "Mom. The mystery can wait.\p"
	.string "She has her real family\n"
	.string "right here.$"

TrioKanto_VermilionScene:
	.string "A ship sounds its horn.\n"
	.string "Riko answers immediately.\p"
	.string "Someone must welcome it.\n"
	.string "Bijuu watches a loose\p"
	.string "ribbon flutter in the\n"
	.string "harbor breeze. Penny stays\p"
	.string "close, but this time she\n"
	.string "looks out at the water\p"
	.string "before looking back at\n"
	.string "Mom. Then she leans\p"
	.string "against her sisters. Brave\n"
	.string "does not have to mean\p"
	.string "standing alone.$"

TrioKanto_CeladonScene:
	.string "The fountain splashes.\n"
	.string "Bijuu decides every drop\p"
	.string "is personally interesting.\n"
	.string "Riko supervises from the\p"
	.string "sunny spot. A very\n"
	.string "important job. Penny\p"
	.string "settles beside Mom. When\n"
	.string "Bijuu finally returns,\p"
	.string "Penny shifts just enough\n"
	.string "to make room. Riko rests\p"
	.string "her chin on Penny. Three\n"
	.string "little girls. One quiet\p"
	.string "afternoon. Nobody needs to\n"
	.string "win anything to belong\p"
	.string "here.$"

TrioChampionPicnic_OfferText:
	.string "Mom: Scott left a picnic\n"
	.string "ready for our Champion and\p"
	.string "her girls. Want a quiet\n"
	.string "celebration together?$"

TrioChampionPicnic_BringGirls:
	.string "Mom: Scott packed a picnic\n"
	.string "for all of you. Bring\p"
	.string "Riko, Penny and Bijuu home\n"
	.string "when you are ready.$"

TrioChampionPicnic_Scene:
	.string "You spread a blanket for a\n"
	.string "little family picnic.\p"
	.string "Scott packed chicken, cold\n"
	.string "Wawa, and room for every\p"
	.string "girl. Penny checks the\n"
	.string "chicken. Bijuu\p"
	.string "investigates the bag. Riko\n"
	.string "announces that the picnic\p"
	.string "is officially open. For\n"
	.string "once, there is nowhere you\p"
	.string "need to hurry. The girls\n"
	.string "curl beside you. Mom tucks\p"
	.string "a note into your\n"
	.string "scrapbook.$"

TrioChampionPicnic_ScottLetter:
	.string "A note from Scott: You\n"
	.string "looked cute becoming\p"
	.string "Champion. You looked cute\n"
	.string "at the first Gym, too. I\p"
	.string "loved watching you give\n"
	.string "our girls a whole world to\p"
	.string "explore. Riko brought the\n"
	.string "barks. Bijuu brought the\p"
	.string "chaos. Penny brought the\n"
	.string "heart. You made every\p"
	.string "place feel like home.\n"
	.string "Whatever adventure comes\p"
	.string "next, I choose you and our\n"
	.string "little family. Every time.\p"
	.string "I love you most. Love,\n"
	.string "Scott.$"

TrioChampionPicnic_Recorded:
	.string "Scott's letter is saved in\n"
	.string "Our journey. The picnic is\p"
	.string "a memory you can keep.$"

TrioChecklist_Intro:
	.string "Pages still waiting: These\n"
	.string "little moments will wait\p"
	.string "for you. Bring all three\n"
	.string "girls for sister scenes\p"
	.string "and the family picnic.$"

TrioChecklist_EightBadgesHint:
	.string "Eight Johto Badges: Still\n"
	.string "waiting. Earn every Johto\p"
	.string "Badge.$"

TrioChecklist_EightBadgesSaved:
	.string "Eight Johto Badges: Saved\n"
	.string "in your scrapbook.$"

TrioChecklist_FirstBadgeHint:
	.string "First Badge: Still\n"
	.string "waiting. Earn Violet's\p"
	.string "Badge.$"

TrioChecklist_FirstBadgeSaved:
	.string "First Badge: Saved in your\n"
	.string "scrapbook.$"

TrioChecklist_GoldenrodBadgeHint:
	.string "Goldenrod Badge: Still\n"
	.string "waiting. Earn Goldenrod's\p"
	.string "Badge.$"

TrioChecklist_GoldenrodBadgeSaved:
	.string "Goldenrod Badge: Saved in\n"
	.string "your scrapbook.$"

TrioChecklist_ChampionHint:
	.string "Champion: Still waiting.\n"
	.string "Become League Champion.$"

TrioChecklist_ChampionSaved:
	.string "Champion: Saved in your\n"
	.string "scrapbook.$"

TrioChecklist_AzaleaHint:
	.string "Azalea sisters: Still\n"
	.string "waiting. After Violet's\p"
	.string "Badge, bring the girls to\n"
	.string "Azalea's Poke Center Lass.$"

TrioChecklist_AzaleaSaved:
	.string "Azalea sisters: Saved in\n"
	.string "your scrapbook.$"

TrioChecklist_GoldenrodHint:
	.string "Goldenrod sisters: Still\n"
	.string "waiting. After Azalea's\p"
	.string "Badge, bring the girls to\n"
	.string "Goldenrod's Poke Center\p"
	.string "Lass.$"

TrioChecklist_GoldenrodSaved:
	.string "Goldenrod sisters: Saved\n"
	.string "in your scrapbook.$"

TrioChecklist_OlivineHint:
	.string "Olivine sisters: Still\n"
	.string "waiting. After Ecruteak's\p"
	.string "Badge, bring the girls to\n"
	.string "Olivine's Poke Center\p"
	.string "Lass.$"

TrioChecklist_OlivineSaved:
	.string "Olivine sisters: Saved in\n"
	.string "your scrapbook.$"

TrioChecklist_PomHint:
	.string "Pom party: Still waiting.\n"
	.string "Visit Goldenrod's PP\p"
	.string "house. Follow the happy\n"
	.string "barks!$"

TrioChecklist_PomSaved:
	.string "Pom party: Saved in your\n"
	.string "scrapbook.$"

TrioChecklist_CeruleanHint:
	.string "Cerulean sisters: Still\n"
	.string "waiting. After the League,\p"
	.string "enter Cerulean with the\n"
	.string "girls. The Bug Catcher can\p"
	.string "help.$"

TrioChecklist_CeruleanSaved:
	.string "Cerulean sisters: Saved in\n"
	.string "your scrapbook.$"

TrioChecklist_VermilionHint:
	.string "Vermilion sisters: Still\n"
	.string "waiting. After the League,\p"
	.string "enter Vermilion with the\n"
	.string "girls. Ask the Battle\p"
	.string "Girl, too.$"

TrioChecklist_VermilionSaved:
	.string "Vermilion sisters: Saved\n"
	.string "in your scrapbook.$"

TrioChecklist_CeladonHint:
	.string "Celadon sisters: Still\n"
	.string "waiting. After the League,\p"
	.string "talk to Celadon's Lass\n"
	.string "with the girls.$"

TrioChecklist_CeladonSaved:
	.string "Celadon sisters: Saved in\n"
	.string "your scrapbook.$"

TrioChecklist_RikoLetterHint:
	.string "Riko's letter: Still\n"
	.string "waiting. Meet the Spirit\p"
	.string "of Riko in her cave.$"

TrioChecklist_RikoLetterSaved:
	.string "Riko's letter: Saved in\n"
	.string "your scrapbook.$"

TrioChecklist_PennyLetterHint:
	.string "Penny's letter: Still\n"
	.string "waiting. After all eight\p"
	.string "Johto Badges, look north\n"
	.string "of Blackthorn's Poke\p"
	.string "Center.$"

TrioChecklist_PennyLetterSaved:
	.string "Penny's letter: Saved in\n"
	.string "your scrapbook.$"

TrioChecklist_BijuuLetterHint:
	.string "Bijuu's letter: Still\n"
	.string "waiting. After the League,\p"
	.string "look beside Ecruteak's\n"
	.string "Burned Tower.$"

TrioChecklist_BijuuLetterSaved:
	.string "Bijuu's letter: Saved in\n"
	.string "your scrapbook.$"

TrioChecklist_PicnicHint:
	.string "Family picnic: Still\n"
	.string "waiting. After the League,\p"
	.string "visit Mom at home with all\n"
	.string "three girls.$"

TrioChecklist_PicnicSaved:
	.string "Family picnic: Saved in\n"
	.string "your scrapbook.$"

