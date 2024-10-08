// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_GetPatrolPoint.h"
#include "Controllers/ANPEnemyAIController.h"
#include "Enemy/ANPEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_GetPatrolPoint::UBTTask_GetPatrolPoint()
{
	NodeName = TEXT("Get Patrol Point");
}

EBTNodeResult::Type UBTTask_GetPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AANPEnemyAIController* EnemyAIController = Cast<AANPEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		if (AANPEnemyCharacter* Enemy = Cast<AANPEnemyCharacter>(EnemyAIController->GetPawn()))
		{
			if (UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent())
			{
				const FVector StartLocation = Blackboard->GetValueAsVector(StartPointKey.SelectedKeyName);
				FVector MoveToLocation;

				// Patrol around the start location, in a random path.
				if (UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld()))
				{
					FNavLocation Location;
					if (NavSystem->GetRandomPointInNavigableRadius(StartLocation, Enemy->MoveRadius, Location))
					{
						MoveToLocation = Location.Location;
					}
				}

				// Set the Move to Location.
				Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), MoveToLocation);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
