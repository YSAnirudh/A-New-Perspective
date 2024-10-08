// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateCanSeePlayer.generated.h"

/**
 * Updates whether the enemy can see player
 */
UCLASS()
class ANEWPERSPECTIVE_API UBTService_UpdateCanSeePlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UBTService_UpdateCanSeePlayer();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PlayerActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector MoveToKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float SearchConeRadiusDegrees = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float SearchSightRadius = 200.f;
};
