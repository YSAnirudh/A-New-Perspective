// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/StarPickup.h"
#include "Character/ANPPlayerCharacter.h"

void AStarPickup::OnPickupItem(AANPPlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->IncrementStars();
	}

	Super::OnPickupItem(PlayerCharacter);
}
