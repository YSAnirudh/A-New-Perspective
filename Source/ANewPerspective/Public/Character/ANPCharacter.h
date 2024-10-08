// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ANPCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FANPDeathEvent);

UCLASS()
class ANEWPERSPECTIVE_API AANPCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AANPCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable)
	FANPDeathEvent OnDeathEvent;

public:

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	int HitPoints = 3;

};
