// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ANPMovementComponent.generated.h"

class AANPPlayerCharacter;

UENUM(BlueprintType)
enum ECustomMovementMode : int
{
	ANPMove_None		UMETA(DisplayName = "None"),
	ANPMove_Impact		UMETA(DisplayName = "Impact"),
	ANPMove_Dash		UMETA(DisplayName = "Dash"),
	ANPMove_MAX			UMETA(Hidden)
};

/**
 * Character Movement Component that handles Impacts and also Dash.
 */
UCLASS()
class ANEWPERSPECTIVE_API UANPMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UANPMovementComponent(const FObjectInitializer& ObjectInitializer);
	
protected:
	
	virtual float GetMaxSpeed() const override;
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PrevCustomMode) override;

public:

	virtual void PhysCustom(float DeltaTime, int32 Iterations) override;
	virtual bool IsCustomMovementMode(ECustomMovementMode CheckCustomMovementMode) const { return MovementMode == MOVE_Custom && CustomMovementMode == CheckCustomMovementMode; }

	virtual void PhysDash(float DeltaTime, int32 Iterations);
	virtual void ResetDash();
	virtual void ResetDashDamageBuffer();

	void SetImpactData(const FVector& HitLocation, const FVector& HitNormal, bool bDisableInputOnImpact);

public:

	FRotator PrevRotation;

	bool bDisableInputOnImpact = false;
	FVector HitLocation;
	FVector HitNormal;

	FTimerHandle CooldownHandle;
	FTimerHandle DamageBufferHandle;

	// Player Character declares intent to Dash.
	bool bWantsToDash = false;
	
	// Can Dash, when not in cooldown.
	bool bCanDash = true;

	// Buffer Timer Handle when ending dash, to avoid taking damage when dashing into an enemy while ending our dash.
	bool bInDashDamageBufferTime = false;

	// To Track Dash Distance.
	float DashDistance = 0.0f;
	float CurrentDashDistance = 0.0f;

	// Buffer time after the Dash when the player cannot take damage.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement|Dash")
	float DashDamageBufferTime = 0.25f;

	// Cooldown for Dash.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement|Dash")
	float DashCooldownTime = 0.5f;

	// Dash Distance on Ground
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement|Dash")
	float GroundDashDistance = 200.f;

	// Dash Distance in Air
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement|Dash")
	float AirDashDistance = 300.f;

	// Dash Speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement|Dash")
	float DashMoveSpeed = 600.f;

};
