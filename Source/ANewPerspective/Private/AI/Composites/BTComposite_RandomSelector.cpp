// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Composites/BTComposite_RandomSelector.h"

UBTComposite_RandomSelector::UBTComposite_RandomSelector(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = TEXT("Random Selector");
}

int32 UBTComposite_RandomSelector::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	int32 NextChildIndex = BTSpecialChild::ReturnToParent;

	if (PrevChild == BTSpecialChild::NotInitialized)
	{
		NextChildIndex = FMath::RandRange(0, GetChildrenNum() - 1);
	}
	else if (LastResult == EBTNodeResult::Succeeded)
	{
		NextChildIndex = FMath::RandRange(0, GetChildrenNum() - 1);
	}

	return NextChildIndex;
}

void UBTComposite_RandomSelector::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	InitializeNodeMemory<FBTCompositeMemory>(NodeMemory, InitType);
}

void UBTComposite_RandomSelector::CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const
{
	CleanupNodeMemory<FBTCompositeMemory>(NodeMemory, CleanupType);
}
