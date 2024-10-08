// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/Pickup.h"
#include "Treasure.generated.h"

class AANPPlayerCharacter;

/**
 * 
 */
UCLASS()
class ANEWPERSPECTIVE_API ATreasure : public APickup
{
	GENERATED_BODY()
	
public:

	virtual void OnPickupItem(AANPPlayerCharacter* PlayerCharacter) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Treasure")
	bool bCanTakeTreasure = false;

};
