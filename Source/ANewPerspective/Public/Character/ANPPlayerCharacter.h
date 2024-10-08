// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ANPCharacter.h"
#include "ANPPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AANPPlayerController;
class AANPEnemyCharacter;
class UANPMovementComponent;
class ACheckpoint;
class AActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FANPEvent, int, Count);

/**
 * 
 */
UCLASS()
class ANEWPERSPECTIVE_API AANPPlayerCharacter : public AANPCharacter
{
	GENERATED_BODY()

public:
	AANPPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	// Declares intent to Dash to the Movement Component
	UFUNCTION()
	void Dash();

	// Increment and Call Coin/Star Pickup Event
	void IncrementCoins();
	void IncrementStars();

	// Set Spring Arm stuff for 3D
	void Set3DSpringArmRotation();

	UANPMovementComponent* const GetANPMovementComponent() const { return ANPMovementComponent; }
	UCameraComponent* const GetCamera() const { return Camera; }

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* CameraSpringArm = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	UANPMovementComponent* ANPMovementComponent = nullptr;

	// Pickups
	int CoinsCollected = 0;
	int StarsCollected = 0;

	// Damage and invincibility

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float InvincibilityTimeOnDamage = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float FlashOnInvincibilityInterval = 0.3f;

	FTimerHandle InvincibilityHandle;
	FTimerHandle FlashHandle;

	bool bDamagePossible = true;

	UFUNCTION()
	void DamageReset();

	UFUNCTION()
	void FlashMesh();

	// Delegates

	UPROPERTY(BlueprintAssignable)
	FANPEvent OnTakeDamage;

	UPROPERTY(BlueprintAssignable)
	FANPEvent OnCollectStar;

	UPROPERTY(BlueprintAssignable)
	FANPEvent OnCollectCoin;

	ACheckpoint* CurrentCheckpoint = nullptr;

public:

	void HandleDamage(AANPEnemyCharacter* Enemy, const FVector& HitLocation, const FVector& HitNormal);
	void DealDamage(AActor* InInstigator, bool bGoToLastCheckpoint);

	void GoToLastCheckpoint();
	void SaveCheckpoint(ACheckpoint* Checkpoint);

	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION()
	void OnCharacterCollided(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	bool bCanSwitchTo3D = false;
};
