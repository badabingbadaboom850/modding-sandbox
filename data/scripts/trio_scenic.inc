@ Optional photographers. No movement, item, weather or progression changes.
TrioScenic_Lighthouse::
	lockall
	faceplayer
	setvar VAR_0x8008, 0
	msgbox TrioScenic_LighthouseIntro, MSGBOX_DEFAULT
	goto TrioScenic_Offer
TrioScenic_Lake::
	lockall
	faceplayer
	setvar VAR_0x8008, 1
	msgbox TrioScenic_LakeIntro, MSGBOX_DEFAULT
	goto TrioScenic_Offer
TrioScenic_Ice::
	lockall
	faceplayer
	setvar VAR_0x8008, 2
	msgbox TrioScenic_IceIntro, MSGBOX_DEFAULT
TrioScenic_Offer:
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, ReadTrioScenicPhoto
	goto_if_eq VAR_RESULT, TRUE, TrioScenic_Retake
	msgbox TrioScenic_TakeQuestion, MSGBOX_YESNO
	goto TrioScenic_Answer
TrioScenic_Retake:
	msgbox TrioScenic_RetakeQuestion, MSGBOX_YESNO
TrioScenic_Answer:
	goto_if_ne VAR_RESULT, YES, TrioScenic_Close
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, TakeTrioScenicPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioScenic_Missing
	msgbox TrioScenic_Saved, MSGBOX_DEFAULT
	call TrioScenic_View
	goto TrioScenic_Close
TrioScenic_Missing:
	msgbox TrioScenic_MissingText, MSGBOX_DEFAULT
TrioScenic_Close:
	closemessage
	releaseall
	end

@ Returning submenu: the caller owns its lock. Cancel closes without writes.
TrioScenic_Album::
	msgbox TrioScenic_AlbumIntro, MSGBOX_DEFAULT
TrioScenic_AlbumMenu:
	closemessage
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TrioScenic_LighthouseName, TrioScenic_LakeName, TrioScenic_IceName, TrioScenic_BackName
	goto_if_ge VAR_RESULT, 3, TrioScenic_Return
	copyvar VAR_0x8008, VAR_RESULT
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, ReadTrioScenicPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioScenic_Locked
	call TrioScenic_View
	goto TrioScenic_AlbumMenu
TrioScenic_Locked:
	msgbox TrioScenic_LockedText, MSGBOX_DEFAULT
	goto TrioScenic_AlbumMenu
TrioScenic_View:
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, ReadTrioScenicPhoto
	goto_if_eq VAR_RESULT, FALSE, TrioScenic_Return
	call_if_eq VAR_0x8008, 0, TrioScenic_LighthouseCaption
	call_if_eq VAR_0x8008, 1, TrioScenic_LakeCaption
	call_if_eq VAR_0x8008, 2, TrioScenic_IceCaption
	showmonpic VAR_0x8005, 10, 3
	bufferspeciesname STR_VAR_1, VAR_0x8005
	msgbox TrioScenic_RikoCaption, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	showmonpic VAR_0x8006, 10, 3
	bufferspeciesname STR_VAR_1, VAR_0x8006
	msgbox TrioScenic_BijuuCaption, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	showmonpic VAR_0x8007, 10, 3
	bufferspeciesname STR_VAR_1, VAR_0x8007
	msgbox TrioScenic_PennyCaption, MSGBOX_DEFAULT
	closemessage
	hidemonpic
TrioScenic_Return:
	return
TrioScenic_LighthouseCaption:
	msgbox TrioScenic_LighthouseText, MSGBOX_DEFAULT
	return
TrioScenic_LakeCaption:
	msgbox TrioScenic_LakeText, MSGBOX_DEFAULT
	return
TrioScenic_IceCaption:
	msgbox TrioScenic_IceText, MSGBOX_DEFAULT
	return

TrioScenic_LighthouseIntro:
	.string "A family photo above\nOlivine's shining sea?\pI can save the girls'\nlooks in your scrapbook.$"
TrioScenic_LakeIntro:
	.string "A family photo beside\nthe Lake of Rage?\pI can save the girls'\nlooks in your scrapbook.$"
TrioScenic_IceIntro:
	.string "A family photo among\nthe Ice Path crystals?\pI can save the girls'\nlooks in your scrapbook.$"
TrioScenic_TakeQuestion:
	.string "Take a free family photo\nfor Mom's Scrapbook?$"
TrioScenic_RetakeQuestion:
	.string "Take a new photo here?\nIt replaces this spot's\ppicture in the scrapbook.\nKeep all other memories.$"
TrioScenic_MissingText:
	.string "Bring all three girls\nso everyone can be in it!\pAll their personal forms\nand costumes are welcome.$"
TrioScenic_Saved:
	.string "Click! Family photo saved.\nScott wrote the captions!\pRead in Mom's Scrapbook:\nScenic photos.$"
TrioScenic_AlbumIntro:
	.string "Three places. One family.\nSaved looks stay here.\pVisit a photographer for\na free picture or retake.$"
TrioScenic_LockedText:
	.string "No photo saved here yet.\nFind this photographer!\pLighthouse roof or lake,\nor the Ice Path entrance.$"
TrioScenic_LighthouseName:
	.string "Lighthouse$"
TrioScenic_LakeName:
	.string "Lake of Rage$"
TrioScenic_IceName:
	.string "Ice Path$"
TrioScenic_BackName:
	.string "Back$"
TrioScenic_LighthouseText:
	.string "Scott: The sea sparkles.\nYou still steal the view.\pThree girls. A lighthouse.\nMy whole world beside me.$"
TrioScenic_LakeText:
	.string "Scott: A lake called Rage,\na picture full of love.\pRiko supervised. Bijuu\navoided every puddle.\pPenny stayed close to you.\nI know how she feels.$"
TrioScenic_IceText:
	.string "Scott: All these crystals,\nand you're the brightest.\pThree girls huddled close.\nOur own little warm place.$"
TrioScenic_RikoCaption:
	.string "Riko: {STR_VAR_1}\pScott: Tiny queen.\nEnormous main-character\penergy. She approved\nthis picture herself.$"
TrioScenic_BijuuCaption:
	.string "Bijuu: {STR_VAR_1}\pScott: She found her angle\nbefore I found my camera.\pA perfect little cocoa.\nShe knows it, too.$"
TrioScenic_PennyCaption:
	.string "Penny: {STR_VAR_1}\pScott: Safe with sisters,\nloved right where she is.\pMy favorite little hot dog\nnever has to pose alone.$"
