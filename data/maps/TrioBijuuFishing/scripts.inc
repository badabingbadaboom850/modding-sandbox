TrioBijuuFishing_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TrioSilly_FishingTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrioSilly_FishingFrame
	.byte 0
TrioSilly_FishingTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	setvar VAR_TEMP_A, 1
	end
TrioSilly_FishingFrame:
	map_script_2 VAR_TEMP_A, 1, TrioSilly_FishingRun
	.2byte 0
