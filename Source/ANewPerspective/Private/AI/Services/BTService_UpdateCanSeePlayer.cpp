// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_UpdateCanSeePlayer.h"
#include "Controllers/ANPEnemyAIController.h"
#include "Character/ANPPlayerCharacter.h"
#include "Enemy/ANPEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateCanSeePlayer::UBTService_UpdateCanSeePlayer()
{
	NodeName = TEXT("Update Can See Player");
}

void UBTService_UpdateCanSeePlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent())
	{
		if (AANPEnemyAIController* EnemyController = Cast<AANPEnemyAIController>(OwnerComp.GetAIOwner()))
		{
			AANPPlayerCharacter* PlayerActor = Cast<AANPPlayerCharacter>(Blackboard->GetValueAsObject(PlayerActorKey.SelectedKeyName));
			AANPEnemyCharacter* Enemy = Cast<AANPEnemyCharacter>(EnemyController->GetPawn());
			if (PlayerActor && Enemy)
			{
				const FVector EnemyLocation = Enemy->GetActorLocation();
				const FVector PlayerLocation = PlayerActor->GetActorLocation();
				const FVector EnemyToPlayerDirection = (PlayerLocation - EnemyLocation).GetSafeNormal();
				const FVector EnemyForward = Enemy->GetActorForwardVector();

				// Check if Player is within the sight radius of the enemy.
				if ((PlayerLocation - EnemyLocation).SquaredLength() < SearchSightRadius * SearchSightRadius)
				{
					// Check the direction in a cone. If Enemy forward and Enemy To Player dir's dot product is high, it means enemy is looking at the player.
					if (FVector::DotProduct(EnemyForward, EnemyToPlayerDirection) > FMath::Cos(FMath::DegreesToRadians(SearchConeRadiusDegrees)))
					{
						// Enemy can see player
						Blackboard->SetValueAsBool(GetSelectedBlackboardKey(), true);
						Blackboard->SetValueAsVector(MoveToKey.SelectedKeyName, PlayerLocation);
						return;
					}
				}

				// Enemy cannot see player
				Blackboard->SetValueAsBool(GetSelectedBlackboardKey(), false);
			}
		}
	}
}
