TrioPennyHotdog_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TrioSilly_HotdogTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrioSilly_HotdogFrame
	.byte 0
TrioSilly_HotdogTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	setvar VAR_TEMP_A, 1
	end
TrioSilly_HotdogFrame:
	map_script_2 VAR_TEMP_A, 1, TrioSilly_HotdogRun
	.2byte 0
