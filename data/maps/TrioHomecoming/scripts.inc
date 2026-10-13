TrioHomecoming_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, FamilyHome_Decor
    .byte 0
FamilyHome_Decor::
    setflag FLAG_TEMP_1
    setflag FLAG_TEMP_2
    setflag FLAG_TEMP_3
    call_if_ge VAR_TRIO_GARDEN_STATE, 5, FamilyHome_ShowGarden
    call_if_set FLAG_TRIO_FESTIVAL_PICNIC, FamilyHome_ShowFestival
    call_if_eq VAR_TRIO_ROAD_COMPLETE, 1, FamilyHome_ShowRoad
    end
FamilyHome_ShowGarden:
    clearflag FLAG_TEMP_1
    return
FamilyHome_ShowFestival:
    clearflag FLAG_TEMP_2
    return
FamilyHome_ShowRoad:
    clearflag FLAG_TEMP_3
    return
