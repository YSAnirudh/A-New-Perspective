// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/ANPEnemyAIController.h"
#include "Enemy/ANPEnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

AANPEnemyAIController::AANPEnemyAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AANPEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AANPEnemyCharacter* Enemy = Cast<AANPEnemyCharacter>(InPawn))
	{
		if (UBehaviorTree* BehaviorTree = Enemy->GetBehaviorTree())
		{
			UBlackboardComponent* OutBlackboard = nullptr;
			UseBlackboard(BehaviorTree->GetBlackboardAsset(), OutBlackboard);
			Blackboard = OutBlackboard;
			RunBehaviorTree(BehaviorTree);
		}
	}
}

void AANPEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	AANPEnemyCharacter* Enemy = Cast<AANPEnemyCharacter>(GetPawn());
	if (Blackboard && Enemy)
	{
		FVector ActorLocation = Enemy->GetActorLocation();
		Blackboard->SetValueAsVector(FName(TEXT("StartLocation")), ActorLocation);

		if (Enemy->PlayerCharacterClass)
		{
			if (AANPCharacter* PlayerCharacter = Cast<AANPCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), Enemy->PlayerCharacterClass)))
			{
				Blackboard->SetValueAsObject(FName(TEXT("PlayerCharacter")), PlayerCharacter);
			}
		}
	}
}
