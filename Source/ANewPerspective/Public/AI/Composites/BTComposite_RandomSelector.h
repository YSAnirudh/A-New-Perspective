// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BTComposite_RandomSelector.generated.h"

/**
 * Random BT Node Selector
 */
UCLASS()
class ANEWPERSPECTIVE_API UBTComposite_RandomSelector : public UBTCompositeNode
{
	GENERATED_BODY()
	
public:

	UBTComposite_RandomSelector(const FObjectInitializer& ObjectInitializer);

	virtual int32 GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;
	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;
	virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;
};
