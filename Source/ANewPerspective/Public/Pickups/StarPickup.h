// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/Pickup.h"
#include "StarPickup.generated.h"

class AANPPlayerCharacter;

/**
 * 
 */
UCLASS()
class ANEWPERSPECTIVE_API AStarPickup : public APickup
{
	GENERATED_BODY()

public:

	virtual void OnPickupItem(AANPPlayerCharacter* PlayerCharacter) override;
	
};
