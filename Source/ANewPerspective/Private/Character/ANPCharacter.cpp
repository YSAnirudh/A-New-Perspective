// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ANPCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enemy/Hazard.h"

AANPCharacter::AANPCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bConstrainToPlane = true;
		GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
	}
}

float AANPCharacter::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageCauser->IsA<AANPCharacter>() || DamageCauser->IsA<AHazard>())
	{
		if (Damage > UE_KINDA_SMALL_NUMBER)
		{
			// Take one damage
			--HitPoints;
			if (HitPoints <= 0)
			{
				HitPoints = 0;
				OnDeathEvent.Broadcast();
				return Damage;
			}
			return Damage;
		}
	}
	return Damage;
}

