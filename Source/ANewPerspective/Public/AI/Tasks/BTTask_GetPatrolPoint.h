// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetPatrolPoint.generated.h"

/**
 * Gets the new Random Patrol Point around a fixed start point for the enemy.
 */
UCLASS()
class ANEWPERSPECTIVE_API UBTTask_GetPatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UBTTask_GetPatrolPoint();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector StartPointKey;
};
