OlivineCity_House2_MapScripts::
	.byte 0

OlivineCity_EventScript_Punisher::
	lock
	faceplayer
	msgbox OlivineCity_Text_PunishmentBro, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_PunisherBoy::
	lock
	faceplayer
	msgbox OlivineCity_Text_PunishmentBoy, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_PunishmentBro:
	.string "Along the way to Cianwood,\n"
	.string "there are four deserted islands.\p"
	.string "Bad kids are taken to those\n"
	.string "islands as punishment!$"

OlivineCity_Text_PunishmentBoy:
	.string "Whenever I get in trouble,\n"
	.string "big bro always scares me.$"

OlivinePomParty_Invite::
	lock
	faceplayer
	msgbox OlivinePomParty_InviteText, MSGBOX_YESNO
	goto_if_ne VAR_RESULT, YES, OlivinePomParty_Decline
	closemessage
	warp MAP_OLIVINE_POM_PARTY, 4, 7
	waitstate
	releaseall
	end
OlivinePomParty_Decline:
	release
	end
OlivinePomParty_InviteText:
	.string "Remember Goldenrod's\n"
	.string "pom party?\p"
	.string "We brought it to Olivine!\p"
	.string "'Cause a pom party\n"
	.string "don't stop!\p"
	.string "Want to join the encore?$"
