TrioRikoNoise_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TrioSilly_NoiseTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrioSilly_NoiseFrame
	.byte 0
TrioSilly_NoiseTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	setvar VAR_TEMP_A, 1
	end
TrioSilly_NoiseFrame:
	map_script_2 VAR_TEMP_A, 1, TrioSilly_NoiseRun
	.2byte 0
