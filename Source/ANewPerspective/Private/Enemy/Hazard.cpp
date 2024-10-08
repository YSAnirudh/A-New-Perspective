// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Hazard.h"
#include "Enemy/ANPEnemyCharacter.h"
#include "Character/ANPPlayerCharacter.h"
#include "Components/BoxComponent.h"

AHazard::AHazard()
{
	PrimaryActorTick.bCanEverTick = true;

	HazardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hazard Mesh"));
	if (HazardMesh)
	{
		SetRootComponent(HazardMesh);
	}

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	if (CollisionBox)
	{
		CollisionBox->SetupAttachment(HazardMesh);
		CollisionBox->SetGenerateOverlapEvents(true);
		CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AHazard::OnCollidedWithHazard);
	}
}

void AHazard::OnCollidedWithHazard(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Deal Damage to player
	if (AANPPlayerCharacter* PlayerCharacter = Cast<AANPPlayerCharacter>(OtherActor))
	{
		PlayerCharacter->DealDamage(this, true);
	}
	// If Enemy, just destroy the enemy.
	else if (OtherActor->IsA<AANPEnemyCharacter>())
	{
		OtherActor->Destroy();
	}
}
