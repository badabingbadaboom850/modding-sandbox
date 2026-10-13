
BlackthornCity_Mart_MapScripts::
	.byte 0

BlackthornMart_EventScript_CoolTrainerM::
	msgbox BlackthornMart_Text_CooltrainerM, MSGBOX_NPC
	end

BlackthornMart_EventScript_BlackBelt::
	msgbox BlackthornMart_Text_BlackBelt, MSGBOX_NPC
	end

BlackthornMart_Text_CooltrainerM:
	.string "You can't buy Max Revive, but it\n"
	.string "fully restores a fainted Pokémon.\p"
	.string "Beware--it won't restore PP, the\n"
	.string "Power Points needed for moves.$"

BlackthornMart_Text_BlackBelt:
	.string "Max Repel keeps weak Pokémon away\n"
	.string "from you.\p"
	.string "It's the longest lasting of the\n"
	.string "Repel sprays.$"

Blackthorn_Mart2::
	lock
	faceplayer
	message Blackthorn_Mart2_Text_0
	waitmessage
	call TrioPuffs_Shop
	msgbox Blackthorn_Mart2_Text_1
	release
	end


	.align 2
Blackthorn2:
	.2byte ITEM_TM_ACROBATICS
	.2byte ITEM_TM_DRAGON_TAIL
	.2byte ITEM_TM_SKY_DROP
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_PREMIER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_RETRO_MAIL
	.2byte ITEM_NONE

	.align 2
BlackthornPuffs:
	.2byte ITEM_RIKO_PUFFS
	.2byte ITEM_TM_ACROBATICS
	.2byte ITEM_TM_DRAGON_TAIL
	.2byte ITEM_TM_SKY_DROP
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_PREMIER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_RETRO_MAIL
	.2byte ITEM_NONE


TrioPuffs_Shop::
	goto_if_unset FLAG_BADGE01_GET, TrioPuffs_OriginalShop
	goto_if_unset FLAG_BADGE02_GET, TrioPuffs_OriginalShop
	goto_if_unset FLAG_BADGE03_GET, TrioPuffs_OriginalShop
	goto_if_unset FLAG_BADGE04_GET, TrioPuffs_OriginalShop
	goto_if_unset FLAG_BADGE05_GET, TrioPuffs_OriginalShop
	goto_if_unset FLAG_BADGE06_GET, TrioPuffs_OriginalShop
	goto_if_unset FLAG_BADGE07_GET, TrioPuffs_OriginalShop
	goto_if_unset FLAG_BADGE08_GET, TrioPuffs_OriginalShop
	msgbox TrioPuffs_ShopText, MSGBOX_DEFAULT
	pokemart BlackthornPuffs
	return
TrioPuffs_OriginalShop:
	pokemart Blackthorn2
	return
TrioPuffs_ShopText:
	.string "Eight Badges! Riko Puffs\nare now in stock.\pHelp your new friends\ncatch up with the team.$"

Blackthorn_Mart2_Text_0:
	.string "Welcome! How may I help you?$"

Blackthorn_Mart2_Text_1:
	.string "Come back soon!$"
