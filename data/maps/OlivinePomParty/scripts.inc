OlivinePomParty_MapScripts::
	.byte 0

OlivinePomParty_Host::
	lock
	faceplayer
	msgbox OlivinePomParty_HostText, MSGBOX_DEFAULT
	release
	end

OlivinePomParty_Woman::
	lock
	faceplayer
	msgbox OlivinePomParty_WomanText, MSGBOX_DEFAULT
	release
	end

OlivinePomParty_HostText:
	.string "Host: 'Cause a pom party\n"
	.string "don't stop!\p"
	.string "Goldenrod was only the\n"
	.string "first lap.\p"
	.string "Ain't no party like a\n"
	.string "pom party, 'cause a pom\p"
	.string "party don't stop!$"

OlivinePomParty_WomanText:
	.string "The party followed us\n"
	.string "all the way to Olivine.\p"
	.string "Penny found a soft seat.\n"
	.string "Bijuu judged the music.\p"
	.string "Riko requested another\n"
	.string "lap. Of course she did.$"
