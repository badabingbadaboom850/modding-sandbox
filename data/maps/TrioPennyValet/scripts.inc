TrioPennyValet_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TrioSilly_ValetTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrioSilly_ValetFrame
	.byte 0
TrioSilly_ValetTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	setvar VAR_TEMP_A, 1
	end
TrioSilly_ValetFrame:
	map_script_2 VAR_TEMP_A, 1, TrioSilly_ValetRun
	.2byte 0
