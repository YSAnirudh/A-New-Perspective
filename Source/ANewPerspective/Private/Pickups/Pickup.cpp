// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/Pickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Character/ANPPlayerCharacter.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	if (PickupMesh)
	{
		SetRootComponent(PickupMesh);
	}

	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Sphere"));
	if (PickupSphere && PickupMesh)
	{
		PickupSphere->SetupAttachment(PickupMesh);
		PickupSphere->SetGenerateOverlapEvents(true);
		PickupSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		PickupSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPickup);
	}
}

void APickup::OnPickupItem(AANPPlayerCharacter* PlayerCharacter)
{
	// Child pickups like coins and stars will override.
	Destroy();
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Basic Rotation for pickups.
	if (PickupMesh && bRotate)
	{
		FRotator CurrentRotation = PickupMesh->GetComponentRotation();
		float DeltaRotationYaw = DeltaTime * TurnSpeed;
	
		CurrentRotation.Yaw += DeltaRotationYaw;
		PickupMesh->SetWorldRotation(CurrentRotation);
	}
}

void APickup::OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AANPPlayerCharacter* PlayerCharacter = Cast<AANPPlayerCharacter>(OtherActor))
	{
		// Call On Pickup Item, which is overriden in Child Pickup classes
		OnPickupItem(PlayerCharacter);
	}
}

