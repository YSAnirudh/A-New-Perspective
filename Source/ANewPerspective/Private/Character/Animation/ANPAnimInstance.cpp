// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/ANPAnimInstance.h"
#include "Character/ANPCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UANPAnimInstance::UANPAnimInstance()
{
}

void UANPAnimInstance::NativeInitializeAnimation()
{
	CharacterReference = Cast<AANPCharacter>(TryGetPawnOwner());
}

void UANPAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (CharacterReference && CharacterReference->GetCharacterMovement())
	{
		bIsInAir = !CharacterReference->GetCharacterMovement()->IsMovingOnGround();
		Speed = CharacterReference->GetVelocity().Length();
	}
}
