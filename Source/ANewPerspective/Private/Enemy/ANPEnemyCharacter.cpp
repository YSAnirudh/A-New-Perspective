// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ANPEnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"

// Sets default values
AANPEnemyCharacter::AANPEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnDeathEvent.AddDynamic(this, &AANPEnemyCharacter::OnDeath);
}

// Called when the game starts or when spawned
void AANPEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

void AANPEnemyCharacter::Landed(const FHitResult& Hit)
{
	Super::OnLanded(Hit);

	if (HitPoints == 0)
	{
		Destroy();
	}
}

float AANPEnemyCharacter::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ParentDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (HitPoints <= 0)
	{
		bCanDamage = false;
	}
	return ParentDamage;
}

// Called every frame
void AANPEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If no Behavior Tree, run basic 2D Movement.
	// Behavior Tree only used for Boss.
	if (BehaviorTree == nullptr)
	{
		if (bMovingRight)
		{
			if (GetActorLocation().X > StartLocation.X + MoveRadius)
			{
				bMovingRight = false;
				const FVector LookDirection = FVector(-1.0f, 0.0f, 0.0f);
				SetActorRotation(LookDirection.Rotation());
				return;
			}

			SetActorLocation(GetActorLocation() + FVector::XAxisVector * MoveSpeed * DeltaTime, true);
		}
		else
		{
			if (GetActorLocation().X < StartLocation.X - MoveRadius)
			{
				bMovingRight = true;
				const FVector LookDirection = FVector(1.0f, 0.0f, 0.0f);
				SetActorRotation(LookDirection.Rotation());
				return;
			}

			SetActorLocation(GetActorLocation() - FVector::XAxisVector * MoveSpeed * DeltaTime, true);
		}
	}
}
