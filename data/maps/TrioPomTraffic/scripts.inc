TrioPomTraffic_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TrioSilly_JamTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrioSilly_JamFrame
	.byte 0
TrioSilly_JamTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	setvar VAR_TEMP_A, 1
	end
TrioSilly_JamFrame:
	map_script_2 VAR_TEMP_A, 1, TrioSilly_JamRun
	.2byte 0
