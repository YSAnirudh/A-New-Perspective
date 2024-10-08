// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hazard.generated.h"

class UBoxComponent;

UCLASS()
class ANEWPERSPECTIVE_API AHazard : public AActor
{
	GENERATED_BODY()
	
public:

	AHazard();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
	UBoxComponent* CollisionBox = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hazard")
	UStaticMeshComponent* HazardMesh = nullptr;

	UFUNCTION()
	void OnCollidedWithHazard(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
