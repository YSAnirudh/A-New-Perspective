// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

class UBoxComponent;

UCLASS()
class ANEWPERSPECTIVE_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:

	ACheckpoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	UBoxComponent* CheckpointRegion = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	UStaticMeshComponent* CheckpointMesh = nullptr;

	UFUNCTION()
	void OnCheckpointReached(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
