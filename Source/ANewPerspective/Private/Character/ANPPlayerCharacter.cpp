// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ANPPlayerCharacter.h"
#include "Character/Movement/ANPMovementComponent.h"
#include "Character/Checkpoint.h"
#include "Controllers/ANPPlayerController.h"
#include "GameModes/ANPGameModeBase.h"
#include "Enemy/ANPEnemyCharacter.h"
#include "UI/ANP_HUD.h"

#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AANPPlayerCharacter::AANPPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UANPMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	ANPMovementComponent = Cast<UANPMovementComponent>(GetCharacterMovement());

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	if (CameraSpringArm)
	{
		// Attach Camera to Capsule and setup default settings.
		CameraSpringArm->SetupAttachment(RootComponent);
		CameraSpringArm->SetUsingAbsoluteRotation(true);
		CameraSpringArm->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (Camera)
	{
		// Attach Camera to Spring Arm and setup default settings.
		Camera->SetupAttachment(CameraSpringArm);
		Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
		Camera->SetOrthoWidth(3000.f);
		Camera->bAutoCalculateOrthoPlanes = true;
	}

	if (UCapsuleComponent* CharacterCapsule = GetCapsuleComponent())
	{
		CharacterCapsule->OnComponentHit.AddUniqueDynamic(this, &AANPPlayerCharacter::OnCharacterCollided);
	}

	HitPoints = 6;
}

void AANPPlayerCharacter::Dash()
{
	if (ANPMovementComponent)
	{
		ANPMovementComponent->bWantsToDash = true;
	}
}

void AANPPlayerCharacter::IncrementCoins()
{
	++CoinsCollected;
	OnCollectCoin.Broadcast(CoinsCollected);
}

void AANPPlayerCharacter::IncrementStars()
{
	++StarsCollected;
	OnCollectStar.Broadcast(StarsCollected);
}

void AANPPlayerCharacter::Set3DSpringArmRotation()
{
	if (CameraSpringArm)
	{
		CameraSpringArm->TargetArmLength = 1000.f;
		CameraSpringArm->SetWorldRotation(FRotator(-30.0f, -90.0f, 0.0f));
	}
}

void AANPPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AANPPlayerController* PlayerController = Cast<AANPPlayerController>(GetController()))
	{
		if (AANP_HUD* HUD = Cast<AANP_HUD>(PlayerController->GetHUD()))
		{
			OnTakeDamage.AddUniqueDynamic(HUD, &AANP_HUD::SetHearts);
			OnCollectCoin.AddUniqueDynamic(HUD, &AANP_HUD::SetCoins);
			OnCollectStar.AddUniqueDynamic(HUD, &AANP_HUD::SetStars);
		}
	}
}

void AANPPlayerCharacter::DamageReset()
{
	GetWorld()->GetTimerManager().ClearTimer(InvincibilityHandle);
	GetWorld()->GetTimerManager().ClearTimer(FlashHandle);
	if (GetMesh())
	{
		GetMesh()->SetVisibility(true);
	}
	bDamagePossible = true;
}

void AANPPlayerCharacter::FlashMesh()
{
	if (GetMesh())
	{
		GetMesh()->SetVisibility(!GetMesh()->GetVisibleFlag());
	}
}

void AANPPlayerCharacter::HandleDamage(AANPEnemyCharacter* Enemy, const FVector& HitLocation, const FVector& HitNormal)
{
	if (ANPMovementComponent)
	{
		// When Invincible, can't hurt enemies too.
		if (bDamagePossible)
		{
			// When Dashing don't take damage.
			if (ANPMovementComponent->IsCustomMovementMode(ANPMove_Dash))
			{
				// Damage Onto Enemy
				UGameplayStatics::ApplyDamage(Enemy, 1.0f, GetInstigatorController(), this, UDamageType::StaticClass());
			}
			else
			{
				// Seeing if Hit Normal is aligned to Actor Up vector
				const float UpDotNormal = FVector::DotProduct(HitNormal, GetActorUpVector());
				if (UpDotNormal > 0.5f)
				{
					// Damage Onto Enemy
					UGameplayStatics::ApplyDamage(Enemy, 1.0f, GetInstigatorController(), this, UDamageType::StaticClass());
				}
				else
				{
					if (!ANPMovementComponent->bInDashDamageBufferTime)
					{
						if (Enemy->bCanDamage)
						{
							// Us Taking Damage
							UGameplayStatics::ApplyDamage(this, 1.0f, Enemy->GetInstigatorController(), Enemy, UDamageType::StaticClass());

							// Give invincibility for some time when taking damage.
							GetWorld()->GetTimerManager().SetTimer(InvincibilityHandle, this, &AANPPlayerCharacter::DamageReset, InvincibilityTimeOnDamage, false);
							GetWorld()->GetTimerManager().SetTimer(FlashHandle, this, &AANPPlayerCharacter::FlashMesh, FlashOnInvincibilityInterval, true);
							bDamagePossible = false;
						
							OnTakeDamage.Broadcast(HitPoints);
						}
					}
				}
			}
		}
		// Also Apply Knockback to enemy.
		FVector KnockbackDirection = -HitNormal;
		KnockbackDirection.Z = 1.0f;
		if (!AANPGameModeBase::IsIn3D())
		{
			// No Y in 2D
			KnockbackDirection.Y = 0.0f;
		}
		KnockbackDirection.Normalize();

		Enemy->LaunchCharacter(KnockbackDirection * Enemy->KnockbackStrengthOnImpact, false, false);

		ANPMovementComponent->SetImpactData(HitLocation, HitNormal, !bDamagePossible);
		ANPMovementComponent->SetMovementMode(MOVE_Custom, ANPMove_Impact);
	}
}

void AANPPlayerCharacter::DealDamage(AActor* InInstigator, bool bGoToLastCheckpoint)
{
	// This is for Damage from Spikes
	if (InInstigator && bDamagePossible)
	{
		UGameplayStatics::ApplyDamage(this, 1.0f, InInstigator->GetInstigatorController(), InInstigator, UDamageType::StaticClass());

		// Give invincibility for some time when taking damage.
		GetWorld()->GetTimerManager().SetTimer(InvincibilityHandle, this, &AANPPlayerCharacter::DamageReset, InvincibilityTimeOnDamage, false);
		GetWorld()->GetTimerManager().SetTimer(FlashHandle, this, &AANPPlayerCharacter::FlashMesh, FlashOnInvincibilityInterval, true);
		bDamagePossible = false;

		OnTakeDamage.Broadcast(HitPoints);

		if (bGoToLastCheckpoint)
		{
			GoToLastCheckpoint();
		}
	}
}

void AANPPlayerCharacter::GoToLastCheckpoint()
{
	if (CurrentCheckpoint)
	{
		// Spawn slightly above the checkpoint location to avoid collision errors.
		FVector CheckpointLocation = CurrentCheckpoint->GetActorLocation() + FVector::UpVector * 100.f;
		CheckpointLocation.Y = 0.0f;
		SetActorLocation(CheckpointLocation);
	}
}

void AANPPlayerCharacter::SaveCheckpoint(ACheckpoint* Checkpoint)
{
	CurrentCheckpoint = Checkpoint;
}

void AANPPlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	// Re-enable Input after landing when taking damage.
	EnableInput(nullptr);
}

void AANPPlayerCharacter::OnCharacterCollided(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AANPEnemyCharacter* Enemy = Cast<AANPEnemyCharacter>(OtherActor))
	{
		HandleDamage(Enemy, Hit.ImpactPoint, Hit.ImpactNormal);
	}
}
