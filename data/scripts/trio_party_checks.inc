@ CheckPartyHasSpecies compares exact IDs. Riko Spirit is a separate species.
TrioParty_CheckRiko::
	checkspecies SPECIES_RIKO_BUG
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_FIGHTING
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_BUTTERFLY
	checkspecies SPECIES_RIKO_WITCH
	checkspecies SPECIES_RIKO_PARTY
	checkspecies SPECIES_RIKO_SANTA
	checkspecies SPECIES_RIKO_TURKEY
	checkspecies SPECIES_RIKO_LEAVES
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_RAINCOAT
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_PRINCESS
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_BALLOON
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_FLOWER
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_RIKO_ECHO
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
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
	checkspecies SPECIES_BIJUU_ASTRONAUT
	checkspecies SPECIES_BIJUU_VAMPIRE
	checkspecies SPECIES_BIJUU_GALA
	checkspecies SPECIES_BIJUU_PRESENT
	checkspecies SPECIES_BIJUU_CHEF
	checkspecies SPECIES_BIJUU_SWEATER
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_DETECTIVE
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_BREAD
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_BOX
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_EMBER
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_BIJUU_ICE
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
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
	checkspecies SPECIES_PENNY_GROUND
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_STEEL
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_BALLERINA
	checkspecies SPECIES_PENNY_PUMPKIN
	checkspecies SPECIES_PENNY_STARS
	checkspecies SPECIES_PENNY_REINDEER
	checkspecies SPECIES_PENNY_YAM
	checkspecies SPECIES_PENNY_SWEATER
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_LIFEGUARD
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_BALLERINA_DACHSBUN
	checkspecies SPECIES_PENNY_PUMPKIN_DACHSBUN
	checkspecies SPECIES_PENNY_STARS_DACHSBUN
	checkspecies SPECIES_PENNY_REINDEER_DACHSBUN
	checkspecies SPECIES_PENNY_YAM_DACHSBUN
	checkspecies SPECIES_PENNY_SWEATER_DACHSBUN
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_LIFEGUARD_DACHSBUN
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_BLANKET
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_BLANKET_DACHSBUN
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_HOTDOG_DACHSBUN
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_HOTDOG
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_BRAVE
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_WATER
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
	checkspecies SPECIES_PENNY_GRASS
	goto_if_eq VAR_RESULT, TRUE, TrioParty_SetResultTrue
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


