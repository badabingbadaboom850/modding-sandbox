@ Derive visual upgrades on load; no party, inventory or reward changes.
TrioCamp_DecorateRoom::
	setmetatile 1, 4, 0x109, FALSE
	setmetatile 2, 4, 0x109, FALSE
	setmetatile 3, 4, 0x109, FALSE
	setmetatile 1, 5, 0x109, FALSE
	setmetatile 2, 5, 0x109, FALSE
	setmetatile 3, 5, 0x109, FALSE
	setmetatile 1, 6, 0x109, FALSE
	setmetatile 2, 6, 0x109, FALSE
	setmetatile 3, 6, 0x109, FALSE
	setmetatile 0, 0, 0x108, TRUE
	setmetatile 1, 0, 0x108, TRUE
	setmetatile 0, 1, 0x110, TRUE
	setmetatile 1, 1, 0x110, TRUE
	setmetatile 6, 1, 0x110, TRUE
	setmetatile 8, 0, 0x108, TRUE
	call_if_set FLAG_BADGE03_GET, TrioCampKeepsakes_TravelPhotos
	call_if_set FLAG_BADGE04_GET, TrioCampKeepsakes_PlayMat
	call_if_set FLAG_BADGE08_GET, TrioCampKeepsakes_LeagueWall
	call_if_set FLAG_IS_CHAMPION, TrioCampKeepsakes_ChampionRoom
	end
TrioCampKeepsakes_TravelPhotos:
	setmetatile 0, 0, 0x150, TRUE
	setmetatile 1, 0, 0x151, TRUE
	setmetatile 0, 1, 0x158, TRUE
	setmetatile 1, 1, 0x159, TRUE
	return
TrioCampKeepsakes_PlayMat:
	setmetatile 1, 4, 0x123, FALSE
	setmetatile 2, 4, 0x124, FALSE
	setmetatile 3, 4, 0x125, FALSE
	setmetatile 1, 5, 0x12B, FALSE
	setmetatile 2, 5, METATILE_HouseLab_TrioPlayMat, FALSE
	setmetatile 3, 5, 0x12D, FALSE
	setmetatile 1, 6, 0x133, FALSE
	setmetatile 2, 6, 0x134, FALSE
	setmetatile 3, 6, 0x135, FALSE
	return
TrioCampKeepsakes_LeagueWall:
	setmetatile 6, 1, 0x105, TRUE
	return
TrioCampKeepsakes_ChampionRoom:
	setmetatile 8, 0, 0x105, TRUE
	return

TrioCampKeepsakes_PennyCorner::
	lockall
	faceplayer
	msgbox TrioCampKeepsakes_PennyCornerText, MSGBOX_DEFAULT
	releaseall
	end

TrioCampKeepsakes_RikoChicky::
	lockall
	faceplayer
	msgbox TrioCampKeepsakes_RikoChickyText, MSGBOX_DEFAULT
	releaseall
	end

TrioCampKeepsakes_BijuuToy::
	lockall
	faceplayer
	msgbox TrioCampKeepsakes_BijuuToyText, MSGBOX_DEFAULT
	releaseall
	end

TrioCampKeepsakes_Festival::
	lockall
	faceplayer
	msgbox TrioCampKeepsakes_FestivalText, MSGBOX_DEFAULT
	releaseall
	end

TrioCampKeepsakes_PennySpirit::
	lockall
	faceplayer
	msgbox TrioCampKeepsakes_PennySpiritText, MSGBOX_DEFAULT
	releaseall
	end

TrioCampKeepsakes_BijuuSpirit::
	lockall
	faceplayer
	msgbox TrioCampKeepsakes_BijuuSpiritText, MSGBOX_DEFAULT
	releaseall
	end

TrioCampKeepsakes_Photos::
	lockall
	goto_if_unset FLAG_BADGE03_GET, TrioCampKeepsakes_PhotosWaiting
	msgbox TrioCampKeepsakes_PhotosText, MSGBOX_DEFAULT
	releaseall
	end
TrioCampKeepsakes_PhotosWaiting:
	msgbox TrioCampKeepsakes_PhotosWaitingText, MSGBOX_DEFAULT
	releaseall
	end

TrioCampKeepsakes_LeagueDisplay::
	lockall
	goto_if_set FLAG_IS_CHAMPION, TrioCampKeepsakes_ChampionDisplay
	goto_if_unset FLAG_BADGE08_GET, TrioCampKeepsakes_LeagueWaiting
	msgbox TrioCampKeepsakes_LeagueText, MSGBOX_DEFAULT
	releaseall
	end
TrioCampKeepsakes_ChampionDisplay:
	msgbox TrioCampKeepsakes_ChampionText, MSGBOX_DEFAULT
	releaseall
	end
TrioCampKeepsakes_LeagueWaiting:
	msgbox TrioCampKeepsakes_LeagueWaitingText, MSGBOX_DEFAULT
	releaseall
	end

@ Returning helper for the existing host menu.
TrioCampKeepsakes_ReadRoom::
	msgbox TrioCampKeepsakes_RoomIntro, MSGBOX_DEFAULT
	call_if_unset FLAG_HIDE_TRIO_CAMP_PENNY_CORNER, TrioCampKeepsakes_ReadPennyCorner
	call_if_unset FLAG_HIDE_TRIO_CAMP_RIKO_CHICKY, TrioCampKeepsakes_ReadRikoChicky
	call_if_unset FLAG_HIDE_TRIO_CAMP_BIJUU_TOY, TrioCampKeepsakes_ReadBijuuToy
	call_if_unset FLAG_HIDE_TRIO_CAMP_FESTIVAL, TrioCampKeepsakes_ReadFestival
	call_if_unset FLAG_HIDE_TRIO_CAMP_PENNY_SPIRIT, TrioCampKeepsakes_ReadPennySpirit
	call_if_unset FLAG_HIDE_TRIO_CAMP_BIJUU_SPIRIT, TrioCampKeepsakes_ReadBijuuSpirit
	call_if_set FLAG_BADGE03_GET, TrioCampKeepsakes_ReadPhotos
	call_if_set FLAG_BADGE04_GET, TrioCampKeepsakes_ReadMat
	call_if_set FLAG_BADGE08_GET, TrioCampKeepsakes_ReadLeague
	call_if_set FLAG_IS_CHAMPION, TrioCampKeepsakes_ReadChampion
	return
TrioCampKeepsakes_ReadPennyCorner:
	msgbox TrioCampKeepsakes_PennyCornerText, MSGBOX_DEFAULT
	return
TrioCampKeepsakes_ReadRikoChicky:
	msgbox TrioCampKeepsakes_RikoChickyText, MSGBOX_DEFAULT
	return
TrioCampKeepsakes_ReadBijuuToy:
	msgbox TrioCampKeepsakes_BijuuToyText, MSGBOX_DEFAULT
	return
TrioCampKeepsakes_ReadFestival:
	msgbox TrioCampKeepsakes_FestivalText, MSGBOX_DEFAULT
	return
TrioCampKeepsakes_ReadPennySpirit:
	msgbox TrioCampKeepsakes_PennySpiritText, MSGBOX_DEFAULT
	return
TrioCampKeepsakes_ReadBijuuSpirit:
	msgbox TrioCampKeepsakes_BijuuSpiritText, MSGBOX_DEFAULT
	return
TrioCampKeepsakes_ReadPhotos:
	msgbox TrioCampKeepsakes_PhotosText, MSGBOX_DEFAULT
	return
TrioCampKeepsakes_ReadLeague:
	msgbox TrioCampKeepsakes_LeagueText, MSGBOX_DEFAULT
	return
TrioCampKeepsakes_ReadChampion:
	msgbox TrioCampKeepsakes_ChampionText, MSGBOX_DEFAULT
	return
TrioCampKeepsakes_ReadMat:
	msgbox TrioCampKeepsakes_MatText, MSGBOX_DEFAULT
	return

TrioCampKeepsakes_PennyCornerText:
	.string "Penny's soft corner!\pScott sent this cushion\nafter your first Badge.\pPenny is allowed to take\nup space. Riko is asked to\ptake up less.$"

TrioCampKeepsakes_RikoChickyText:
	.string "Riko's chicky plush!\pThree Badges earned a toy\nthat cannot be eaten.\pRiko would like a second\nopinion on that.$"

TrioCampKeepsakes_BijuuToyText:
	.string "Bijuu's tiny cat toy!\pA fourth-Badge gift for\nyour very real cat.\pBijuu suspects it knows\nsomething. She has started\pan investigation.$"

TrioCampKeepsakes_FestivalText:
	.string "A cushion from the Girls'\nDay Out!\pScott wanted you to keep a\nlittle piece of that\pafternoon.\pIt smells faintly of\npicnic snacks. Greedent\phas no visiting rights.$"

TrioCampKeepsakes_PennySpiritText:
	.string "A guardian cushion, after\nPenny's Spirit encounter.\pBrave does not mean never\nbeing scared.\pIt means having a safe\nplace to come back to.$"

TrioCampKeepsakes_BijuuSpiritText:
	.string "A moon plush, after\nBijuu's Spirit encounter.\pTwo mysterious cats, one\nvery familiar attitude.\pBijuu has claimed the\nmoon. Please ask before\pmoving it.$"

TrioCampKeepsakes_PhotosText:
	.string "A framed travel photo from\nyour first three Badges.\pPenny sat still. Bijuu\nlooked away. Riko barked\pat the camera.\pScott calls it the perfect\nfamily picture.$"

TrioCampKeepsakes_PhotosWaitingText:
	.string "A little space for a\ntravel photo.\pScott says three Badges\nshould give the girls\penough time to pose.\pRiko has already declined.$"

TrioCampKeepsakes_LeagueText:
	.string "Eight Johto Badges, framed\nfor the girls!\pThe League is next. This\nroom will be here when you\pget back.$"

TrioCampKeepsakes_LeagueWaitingText:
	.string "Scott is saving this spot\nfor eight Johto Badges.\pUntil then, it is a very\nexpensive blank wall.$"

TrioCampKeepsakes_ChampionText:
	.string "CHAMPION AND HER GIRLS\pScott redecorated for your\nvictory: another proud\plittle wall display.\pThe League knows your\nnames. This room knows\pyour favorite snacks.$"

TrioCampKeepsakes_RoomIntro:
	.string "Scott sends little gifts\nas your adventure grows.\pThey stay here even while\nthe girls are away.\pThe room changes on your\nnext visit. Inspect each\pgift for its story.$"

TrioCampKeepsakes_MatText:
	.string "A soft play mat arrived\nwith your fourth Badge.\pBijuu says it is her\nstage. Riko says it is her\pstage.\pPenny says it is nice.$"
