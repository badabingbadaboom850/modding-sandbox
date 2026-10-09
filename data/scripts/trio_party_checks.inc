@ CheckPartyHasSpecies compares exact IDs. Riko Spirit is a separate species.
TrioParty_CheckRiko::
	checkspecies SPECIES_RIKO
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_FIRE
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_WATER
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_GRASS
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_ELECTRIC
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_ICE
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_PSYCHIC
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_FLYING
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_DRAGON
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_WING
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	setvar VAR_RESULT, FALSE
	return

TrioParty_CheckBijuu::
	checkspecies SPECIES_BIJUU
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_FIGHTING
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_POISON
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_GROUND
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_ROCK
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_BUG
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_GHOST
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_DARK
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_PSYCHIC
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_STEEL
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	setvar VAR_RESULT, FALSE
	return

TrioParty_CheckPenny::
	checkspecies SPECIES_FIDOUGH
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_DACHSBUN
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_GUARDIAN
	return

TrioParty_CheckAny::
	call TrioParty_CheckRiko
	goto_if_eq VAR_RESULT, TRUE, TrioParty_CheckAny_Return
	call TrioParty_CheckBijuu
	goto_if_eq VAR_RESULT, TRUE, TrioParty_CheckAny_Return
	call TrioParty_CheckPenny
TrioParty_CheckAny_Return::
	return

TrioParty_SetResultTrue::
	setvar VAR_RESULT, TRUE
	return

