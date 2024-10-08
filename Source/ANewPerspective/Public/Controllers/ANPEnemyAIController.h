// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ANPEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ANEWPERSPECTIVE_API AANPEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	AANPEnemyAIController(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
};
