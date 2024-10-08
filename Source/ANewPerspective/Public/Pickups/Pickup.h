// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class AANPPlayerCharacter;

UCLASS()
class ANEWPERSPECTIVE_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	virtual void OnPickupItem(AANPPlayerCharacter* PlayerCharacter);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	USphereComponent* PickupSphere = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	UStaticMeshComponent* PickupMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float TurnSpeed = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool bRotate = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
