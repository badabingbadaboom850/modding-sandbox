@ Optional Scott moments: actual Badge gates, independent saved pages.
@ No party, time, reward, battle or movement requirement.
TrioScott_Azalea::
	lockall
	faceplayer
	goto_if_unset FLAG_BADGE02_GET, TrioScott_Azalea_Waiting
	goto_if_set FLAG_TRIO_SCOTT_AZALEA, TrioScott_Azalea_Replay
	msgbox TrioScott_Azalea_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioScott_Later
	call TrioScott_Azalea_Read
	setflag FLAG_TRIO_SCOTT_AZALEA
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	goto TrioScott_Close
TrioScott_Azalea_Waiting:
	msgbox TrioScott_Azalea_WaitText, MSGBOX_DEFAULT
	goto TrioScott_Close
TrioScott_Azalea_Replay:
	msgbox TrioScott_ReplayOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioScott_Later
	call TrioScott_Azalea_Read
	goto TrioScott_Close
TrioScott_Azalea_Read::
	msgbox TrioScott_Azalea_Memory, MSGBOX_DEFAULT
	return
TrioScott_Azalea_Page::
	goto_if_set FLAG_TRIO_SCOTT_AZALEA, TrioScott_Azalea_Read
	msgbox TrioScott_Azalea_Hint, MSGBOX_DEFAULT
	return
TrioScott_Azalea_Checklist::
	goto_if_set FLAG_TRIO_SCOTT_AZALEA, TrioScott_Azalea_Saved
	msgbox TrioScott_Azalea_Hint, MSGBOX_DEFAULT
	return
TrioScott_Azalea_Saved:
	msgbox TrioScott_Azalea_SavedText, MSGBOX_DEFAULT
	return

TrioScott_Ecruteak::
	lockall
	faceplayer
	goto_if_unset FLAG_BADGE04_GET, TrioScott_Ecruteak_Waiting
	goto_if_set FLAG_TRIO_SCOTT_ECRUTEAK, TrioScott_Ecruteak_Replay
	msgbox TrioScott_Ecruteak_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioScott_Later
	call TrioScott_Ecruteak_Read
	setflag FLAG_TRIO_SCOTT_ECRUTEAK
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	goto TrioScott_Close
TrioScott_Ecruteak_Waiting:
	msgbox TrioScott_Ecruteak_WaitText, MSGBOX_DEFAULT
	goto TrioScott_Close
TrioScott_Ecruteak_Replay:
	msgbox TrioScott_ReplayOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioScott_Later
	call TrioScott_Ecruteak_Read
	goto TrioScott_Close
TrioScott_Ecruteak_Read::
	msgbox TrioScott_Ecruteak_Memory, MSGBOX_DEFAULT
	return
TrioScott_Ecruteak_Page::
	goto_if_set FLAG_TRIO_SCOTT_ECRUTEAK, TrioScott_Ecruteak_Read
	msgbox TrioScott_Ecruteak_Hint, MSGBOX_DEFAULT
	return
TrioScott_Ecruteak_Checklist::
	goto_if_set FLAG_TRIO_SCOTT_ECRUTEAK, TrioScott_Ecruteak_Saved
	msgbox TrioScott_Ecruteak_Hint, MSGBOX_DEFAULT
	return
TrioScott_Ecruteak_Saved:
	msgbox TrioScott_Ecruteak_SavedText, MSGBOX_DEFAULT
	return

TrioScott_Olivine::
	lockall
	faceplayer
	goto_if_unset FLAG_BADGE06_GET, TrioScott_Olivine_Waiting
	goto_if_set FLAG_TRIO_SCOTT_OLIVINE, TrioScott_Olivine_Replay
	msgbox TrioScott_Olivine_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioScott_Later
	call TrioScott_Olivine_Read
	setflag FLAG_TRIO_SCOTT_OLIVINE
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	goto TrioScott_Close
TrioScott_Olivine_Waiting:
	msgbox TrioScott_Olivine_WaitText, MSGBOX_DEFAULT
	goto TrioScott_Close
TrioScott_Olivine_Replay:
	msgbox TrioScott_ReplayOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioScott_Later
	call TrioScott_Olivine_Read
	goto TrioScott_Close
TrioScott_Olivine_Read::
	msgbox TrioScott_Olivine_Memory, MSGBOX_DEFAULT
	return
TrioScott_Olivine_Page::
	goto_if_set FLAG_TRIO_SCOTT_OLIVINE, TrioScott_Olivine_Read
	msgbox TrioScott_Olivine_Hint, MSGBOX_DEFAULT
	return
TrioScott_Olivine_Checklist::
	goto_if_set FLAG_TRIO_SCOTT_OLIVINE, TrioScott_Olivine_Saved
	msgbox TrioScott_Olivine_Hint, MSGBOX_DEFAULT
	return
TrioScott_Olivine_Saved:
	msgbox TrioScott_Olivine_SavedText, MSGBOX_DEFAULT
	return

TrioScott_Blackthorn::
	lockall
	faceplayer
	goto_if_unset FLAG_BADGE08_GET, TrioScott_Blackthorn_Waiting
	goto_if_set FLAG_TRIO_SCOTT_BLACKTHORN, TrioScott_Blackthorn_Replay
	msgbox TrioScott_Blackthorn_Offer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioScott_Later
	call TrioScott_Blackthorn_Read
	setflag FLAG_TRIO_SCOTT_BLACKTHORN
	msgbox TrioSisters_Recorded, MSGBOX_DEFAULT
	goto TrioScott_Close
TrioScott_Blackthorn_Waiting:
	msgbox TrioScott_Blackthorn_WaitText, MSGBOX_DEFAULT
	goto TrioScott_Close
TrioScott_Blackthorn_Replay:
	msgbox TrioScott_ReplayOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrioScott_Later
	call TrioScott_Blackthorn_Read
	goto TrioScott_Close
TrioScott_Blackthorn_Read::
	msgbox TrioScott_Blackthorn_Memory, MSGBOX_DEFAULT
	return
TrioScott_Blackthorn_Page::
	goto_if_set FLAG_TRIO_SCOTT_BLACKTHORN, TrioScott_Blackthorn_Read
	msgbox TrioScott_Blackthorn_Hint, MSGBOX_DEFAULT
	return
TrioScott_Blackthorn_Checklist::
	goto_if_set FLAG_TRIO_SCOTT_BLACKTHORN, TrioScott_Blackthorn_Saved
	msgbox TrioScott_Blackthorn_Hint, MSGBOX_DEFAULT
	return
TrioScott_Blackthorn_Saved:
	msgbox TrioScott_Blackthorn_SavedText, MSGBOX_DEFAULT
	return

TrioScott_Later:
	msgbox TrioScott_LaterText, MSGBOX_DEFAULT
TrioScott_Close:
	closemessage
	releaseall
	end

TrioScott_Scrapbook::
	msgbox TrioScott_BookIntro, MSGBOX_DEFAULT
	call TrioScott_Azalea_Page
	call TrioScott_Ecruteak_Page
	call TrioScott_Olivine_Page
	call TrioScott_Blackthorn_Page
	goto TrioScrapbook_Menu

TrioScott_Checklist::
	call TrioScott_Azalea_Checklist
	call TrioScott_Ecruteak_Checklist
	call TrioScott_Olivine_Checklist
	call TrioScott_Blackthorn_Checklist
	return

TrioScott_Azalea_Offer:
	.string "Scott: There you are! I\nheard you beat Bugsy.\pWant to stop for a minute?\nI have something to tell\pyou.$"

TrioScott_Azalea_Memory:
	.string "Scott: Two Badges already.\nI am so proud of you.\pNot just for winning. You\nkeep trying, and you take\psuch good care of our\ngirls.\pPenny leans into your leg.\nScott crouches to tell her\pshe did a good job too.\pRiko demands the same\nspeech. Bijuu acts like\pshe coached the whole\nmatch.\pScott: I love seeing you\nhappy. Come find me again\pin Ecruteak after Morty.$"

TrioScott_Azalea_Hint:
	.string "Scott is in east Azalea,\non the path south of the\pSlowpoke Well.\pBeat Bugsy, then talk to\nhim for a proud check-in.$"

TrioScott_Azalea_SavedText:
	.string "Azalea: A proud check-in.\pSaved in Scott moments.$"

TrioScott_Azalea_WaitText:
	.string "Scott: I came to cheer you\non. Good luck with Bugsy!\pCome see me after you earn\nthe Badge. I will be right\phere.$"

TrioScott_Ecruteak_Offer:
	.string "Scott: You beat Morty!\nFour Badges looks good on\pyou.\pI brought tea. Want a\nquiet garden date?$"

TrioScott_Ecruteak_Memory:
	.string "Scott finds a sunny patch\nbeside the pond and pours\ptwo cups of warm tea.\pRiko tries to book a solo\nconcert. Bijuu studies a\pleaf like it owes her\nmoney.\pPenny settles between you.\nFor once, nobody needs to\pbe anywhere else.\pScott: My favorite part of\nthis adventure is still\pyou.\pYou sit shoulder to\nshoulder until the tea\pgoes cold. It is worth it.\pScott: Next stop, Olivine.\nAfter Jasmine, I owe you a\pseaside break.$"

TrioScott_Ecruteak_Hint:
	.string "Scott waits by the pond in\nnorth Ecruteak, west of\pthe Tin Tower entrance.\pBeat Morty, then ask him\nfor a garden tea date.$"

TrioScott_Ecruteak_SavedText:
	.string "Ecruteak: Tea together.\pSaved in Scott moments.$"

TrioScott_Ecruteak_WaitText:
	.string "Scott: I came to cheer you\non. Good luck with Morty!\pCome see me after you earn\nthe Badge. I will be right\phere.$"

TrioScott_Olivine_Offer:
	.string "Scott: Jasmine told me you\nearned her Badge. I knew\pyou could.\pWant a little seaside\ndate? The view is pretty\pgood.$"

TrioScott_Olivine_Memory:
	.string "You share a snack below\nthe lighthouse. The sea\pbreeze does its best to\nfix your hair.\pScott: Okay, the view is\nvery good. I meant you.\pRiko campaigns for\nseconds. Bijuu watches the\pboats. Penny rests against\nyour knee.\pScott offers his hand. You\nstay together while the\pwaves roll in.\pScott: I love our little\nfamily. Even when Riko\psteals my entire snack.\pNo big plans. Just salt\nair, happy girls, and a\pfew extra minutes\ntogether.\pScott: Find me outside the\nBlackthorn Center once you\pearn Clair's Badge.$"

TrioScott_Olivine_Hint:
	.string "Scott waits on the grass\njust south of Olivine's\plighthouse entrance.\pBeat Jasmine, then join\nhim for a seaside snack.$"

TrioScott_Olivine_SavedText:
	.string "Olivine: A seaside break.\pSaved in Scott moments.$"

TrioScott_Olivine_WaitText:
	.string "Scott: I came to cheer you\non. Good luck with\pJasmine!\pCome see me after you earn\nthe Badge. I will be right\phere.$"

TrioScott_Blackthorn_Offer:
	.string "Scott: Clair's Badge! Look\nat you, love. All eight.\pBefore the League, can I\nhave a minute with you?$"

TrioScott_Blackthorn_Memory:
	.string "Scott: I am so proud of\nyou. Every city, every\phard battle, you kept\ngoing.\pAnd our girls have had you\nin their corner all the\pway.\pPenny stands a little\ntaller. Bijuu brushes your\phand. Riko loudly accepts\nthe praise.\pScott: Whatever happens at\nthe League, I hope you\pknow how loved you are.\pNow go show them what you\ncan do. We will be\pcheering for you.\pHe squeezes your hand.\nThere is one last kiss\pbefore the road ahead.$"

TrioScott_Blackthorn_Hint:
	.string "Scott waits outside the\nPokemon Center in\pBlackthorn.\pEarn Clair's Badge in the\nDragon's Den, then hear\phis League send-off.$"

TrioScott_Blackthorn_SavedText:
	.string "Blackthorn: Cheering for\nyou.\pSaved in Scott moments.$"

TrioScott_Blackthorn_WaitText:
	.string "Scott: I came to cheer you\non. Good luck with Clair!\pCome see me after you earn\nthe Badge. I will be right\phere.$"

TrioScott_ReplayOffer:
	.string "Scott: I kept this little\nmoment for us. Want to\premember it together?$"

TrioScott_LaterText:
	.string "Scott: Of course. No rush.\nI will save your spot.$"

TrioScott_BookIntro:
	.string "Scott moments.\pThe little breaks between\nthe big adventures.\pSaved pages can be read\nagain. Waiting pages show\pwhere to find Scott.$"
