TrioSquirrelApology_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TrioSilly_ApologyTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrioSilly_ApologyFrame
	.byte 0
TrioSilly_ApologyTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	setvar VAR_TEMP_A, 1
	end
TrioSilly_ApologyFrame:
	map_script_2 VAR_TEMP_A, 1, TrioSilly_ApologyRun
	.2byte 0
