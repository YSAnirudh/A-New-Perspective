// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/CoinPickup.h"
#include "Character/ANPPlayerCharacter.h"

void ACoinPickup::OnPickupItem(AANPPlayerCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->IncrementCoins();
	}

	Super::OnPickupItem(PlayerCharacter);
}
