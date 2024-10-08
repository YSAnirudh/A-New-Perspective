// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ANPCharacter.h"
#include "ANPEnemyCharacter.generated.h"

class UBehaviorTree;

UCLASS()
class ANEWPERSPECTIVE_API AANPEnemyCharacter : public AANPCharacter
{
	GENERATED_BODY()

public:

	AANPEnemyCharacter(const FObjectInitializer& ObjectInitializer);

	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

protected:

	virtual void BeginPlay() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();

public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	TSubclassOf<AANPCharacter> PlayerCharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float KnockbackStrengthOnImpact = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float MoveRadius = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	float MoveSpeed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	bool bIsBoss = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
	bool bMakesTilesComeDown = false;

	bool bCanDamage = true;
	bool bMovingRight = true;
	FVector StartLocation;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTree = nullptr;

};
