// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AfterBossBattle.generated.h"

UCLASS()
class ANEWPERSPECTIVE_API AAfterBossBattle : public AActor
{
	GENERATED_BODY()
	
public:

	AAfterBossBattle();

	USceneComponent* BossBattleTiles = nullptr;

	UFUNCTION(BlueprintCallable)
	void GetTheTilesDownNow();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	int BossTilesToGetDownPerIteration = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	float AmountIncrementPerIteration = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	float ComeDownSpeed = 50.f;

	TMap<USceneComponent*, float> BossTilesChildrenMap;
	bool bTilesDown = false;

public:

	virtual void Tick(float DeltaTime) override;

};
