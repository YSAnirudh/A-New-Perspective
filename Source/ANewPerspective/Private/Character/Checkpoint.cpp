// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Checkpoint.h"
#include "Character/ANPPlayerCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckpointMesh"));
	if (CheckpointMesh)
	{
		SetRootComponent(CheckpointMesh);
	}

	CheckpointRegion = CreateDefaultSubobject<UBoxComponent>(TEXT("Checkpoint Region"));
	if (CheckpointRegion && CheckpointMesh)
	{
		CheckpointRegion->SetupAttachment(CheckpointMesh);
		CheckpointRegion->SetGenerateOverlapEvents(true);
		CheckpointRegion->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		CheckpointRegion->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		CheckpointRegion->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnCheckpointReached);
	}
}

void ACheckpoint::OnCheckpointReached(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AANPPlayerCharacter* PlayerCharacter = Cast<AANPPlayerCharacter>(OtherActor))
	{
		PlayerCharacter->SaveCheckpoint(this);
	}
}
