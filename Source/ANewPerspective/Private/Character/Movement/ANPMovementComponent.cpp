// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Movement/ANPMovementComponent.h"
#include "Character/ANPPlayerCharacter.h"
#include "Enemy/ANPEnemyCharacter.h"
#include "GameModes/ANPGameModeBase.h"
#include "Components/CapsuleComponent.h"

UANPMovementComponent::UANPMovementComponent(const FObjectInitializer& ObjectInitializer)
{
}

float UANPMovementComponent::GetMaxSpeed() const
{
    if (MovementMode != MOVE_Custom)
    {
        return Super::GetMaxSpeed();
    }

    switch (CustomMovementMode)
    {
    case ANPMove_Dash:
        return DashMoveSpeed;
    default:
        return -1.f;
    }
}

void UANPMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
    Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);

    // Align Capsule's rotation to movement.
    if (!Velocity.IsNearlyZero())
    {
        const FVector CapsuleRotationDirection = Velocity.GetUnsafeNormal2D();
        if (CapsuleRotationDirection.IsNearlyZero(0.01f))
        {
            UpdatedComponent->SetWorldRotation(PrevRotation);
        }
        else
        {
            const FRotator MeshRotation = CapsuleRotationDirection.Rotation();
            UpdatedComponent->SetWorldRotation(MeshRotation);
            PrevRotation = MeshRotation;
        }
    }
    else
    {
        UpdatedComponent->SetWorldRotation(PrevRotation);
    }

    // If wants to dash and not in Cooldown, dash.
    if (bWantsToDash && bCanDash)
    {
        bWantsToDash = false;
        bCanDash = false;
        bInDashDamageBufferTime = true;

        SetMovementMode(MOVE_Custom, ANPMove_Dash);
    }
}

void UANPMovementComponent::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PrevCustomMode)
{
    Super::OnMovementModeChanged(PrevMovementMode, PrevCustomMode);

    if (MovementMode == MOVE_Custom)
    {
        if (CustomMovementMode == ANPMove_Dash)
        {
            // If we want to dash, more dash distance in air.
            CurrentDashDistance = 0.0f;
            if (PrevMovementMode == MOVE_Walking)
            {
                DashDistance = GroundDashDistance;
            }
            else if (PrevMovementMode == MOVE_Falling)
            {
                DashDistance = AirDashDistance;
            }
        }

        if (CustomMovementMode == ANPMove_Impact)
        {
            if (PrevMovementMode == MOVE_Custom && PrevCustomMode == ANPMove_Dash)
            {
                // Start the Dash cooldown timer, if there's an Impact.
                GetWorld()->GetTimerManager().SetTimer(CooldownHandle, this, &UANPMovementComponent::ResetDash, DashCooldownTime, false);
            }

            // Unsafe normal as the value will never be a zero vector as we check if UpDotNormal is zero.
            // Which means (Normal + Up) Vector cannot be zero as they are perpendicular.
            const float UpDotNormal = FVector::DotProduct(HitNormal, UpdatedComponent->GetUpVector());
            const FVector& LaunchDirection = FMath::Abs(UpDotNormal) < 0.1f ? (HitNormal + FVector::UpVector).GetUnsafeNormal() : HitNormal;
            const float HorizVelocity = 200.f;
            const float VertVelocity = 200.f;
            const float YVelocity = AANPGameModeBase::IsIn3D() ? LaunchDirection.Y * HorizVelocity : 0.0f;
            const FVector LaunchVelocity = FVector(LaunchDirection.X * HorizVelocity, YVelocity, LaunchDirection.Z * VertVelocity);
            
            // Disable Input on Impact to avoid unneccesary Movement on collision with enemy.
            if (bDisableInputOnImpact)
            {
                CharacterOwner->DisableInput(nullptr);
            }
            // Launch the character in opposite direction.
            CharacterOwner->LaunchCharacter(LaunchVelocity, false, false);
            SetMovementMode(MOVE_Falling);
        }
    }
}

void UANPMovementComponent::PhysCustom(float DeltaTime, int32 Iterations)
{
    Super::PhysCustom(DeltaTime, Iterations);

    switch (CustomMovementMode)
    {
    case ANPMove_Dash:
        PhysDash(DeltaTime, Iterations);
        break;
    case ANPMove_Impact:
        break;
    default:
        UE_LOG(LogTemp, Fatal, TEXT("Invalid Movement Mode"));
        return;
    }
}

void UANPMovementComponent::PhysDash(float DeltaTime, int32 Iterations)
{
    if (!CharacterOwner)
    {
        Acceleration = FVector::ZeroVector;
        Velocity = FVector::ZeroVector;
        return;
    }

    // dist = v * dt;
    // Track Dash distance and end dash after covering the distance.
    float DashDistanceThisFrame = DashMoveSpeed * DeltaTime;
    bool bDashFinished = false;
    if (DashDistanceThisFrame + CurrentDashDistance >= DashDistance)
    {
        DashDistanceThisFrame = DashDistance - CurrentDashDistance;
        bDashFinished = true;
    }
    CurrentDashDistance += DashDistanceThisFrame;

    FHitResult OutHit;
    const FRotator CurrentRotation = UpdatedComponent->GetComponentRotation();
    FVector CurrentRotationVector = CurrentRotation.Vector();
    // No Y Component in 3D.
    if (!AANPGameModeBase::IsIn3D())
    {
        CurrentRotationVector.Y = 0.0f;
        CurrentRotationVector.Normalize();
    }

    const FVector DeltaMove = CurrentRotationVector * DashDistanceThisFrame;
    SafeMoveUpdatedComponent(DeltaMove, CurrentRotationVector.Rotation(), true, OutHit);

    // If we hit anything on our way, stop dash then too.
    if (OutHit.bBlockingHit && OutHit.GetActor())
    {
        if (!OutHit.GetActor()->IsA<AANPEnemyCharacter>())
        {
            SetMovementMode(MOVE_Falling);
        }
        // Start Cooldown Timer and Dash End Damage Buffer Timer.
        GetWorld()->GetTimerManager().SetTimer(CooldownHandle, this, &UANPMovementComponent::ResetDash, DashCooldownTime, false);
        GetWorld()->GetTimerManager().SetTimer(DamageBufferHandle, this, &UANPMovementComponent::ResetDashDamageBuffer, DashDamageBufferTime, false);
        return;
    }

    if (bDashFinished)
    {
        SetMovementMode(MOVE_Falling);
        // Start Cooldown Timer and Dash End Damage Buffer Timer.
        GetWorld()->GetTimerManager().SetTimer(CooldownHandle, this, &UANPMovementComponent::ResetDash, DashCooldownTime, false);
        GetWorld()->GetTimerManager().SetTimer(DamageBufferHandle, this, &UANPMovementComponent::ResetDashDamageBuffer, DashDamageBufferTime, false);
        return;
    }
}

void UANPMovementComponent::ResetDash()
{
    GetWorld()->GetTimerManager().ClearTimer(CooldownHandle);
    bCanDash = true;
}

void UANPMovementComponent::ResetDashDamageBuffer()
{
    GetWorld()->GetTimerManager().ClearTimer(DamageBufferHandle);
    bInDashDamageBufferTime = false;
}

void UANPMovementComponent::SetImpactData(const FVector& InHitLocation, const FVector& InHitNormal, bool bDisableInput)
{
    // Handle Impact with enemy.
    HitLocation = InHitLocation;
    HitNormal = InHitNormal;
    bDisableInputOnImpact = bDisableInput;
}
