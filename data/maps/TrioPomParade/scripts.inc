TrioPomParade_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TrioParade_Transition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrioParade_Frame
	.byte 0
TrioParade_Transition:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	setvar VAR_TEMP_A, 1
	end
TrioParade_Frame:
	map_script_2 VAR_TEMP_A, 1, TrioParade_Run
	.2byte 0
