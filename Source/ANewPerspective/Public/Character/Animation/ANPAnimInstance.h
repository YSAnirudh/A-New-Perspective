// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ANPAnimInstance.generated.h"

class AANPCharacter;

/**
 * Anim Instance for Characters.
 */
UCLASS()
class ANEWPERSPECTIVE_API UANPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UANPAnimInstance();

protected:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	AANPCharacter* CharacterReference = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	float Speed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bIsInAir = false;
};
