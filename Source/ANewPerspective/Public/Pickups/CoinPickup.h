// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/Pickup.h"
#include "CoinPickup.generated.h"

class AANPPlayerCharacter;

/**
 * 
 */
UCLASS()
class ANEWPERSPECTIVE_API ACoinPickup : public APickup
{
	GENERATED_BODY()
	
public:

	virtual void OnPickupItem(AANPPlayerCharacter* PlayerCharacter) override;
};
