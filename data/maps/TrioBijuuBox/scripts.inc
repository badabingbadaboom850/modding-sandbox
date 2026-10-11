TrioBijuuBox_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TrioSilly_BoxTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrioSilly_BoxFrame
	.byte 0
TrioSilly_BoxTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	setvar VAR_TEMP_A, 1
	setflag FLAG_TEMP_1
	end
TrioSilly_BoxFrame:
	map_script_2 VAR_TEMP_A, 1, TrioSilly_BoxRun
	.2byte 0
