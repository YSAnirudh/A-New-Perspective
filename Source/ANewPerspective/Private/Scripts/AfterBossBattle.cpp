// Fill out your copyright notice in the Description page of Project Settings.


#include "Scripts/AfterBossBattle.h"

AAfterBossBattle::AAfterBossBattle()
{
	PrimaryActorTick.bCanEverTick = true;

	BossBattleTiles = CreateDefaultSubobject<USceneComponent>(TEXT("BossBattleTiles"));
	if (BossBattleTiles)
	{
		SetRootComponent(BossBattleTiles);
	}
}

void AAfterBossBattle::GetTheTilesDownNow()
{
	TArray<USceneComponent*> BossTilesChildren;
	BossBattleTiles->GetChildrenComponents(true, BossTilesChildren);

	int CurrentIteration = 0;
	int CurrentBossTileIndex = 0;
	for (USceneComponent* BossTile : BossTilesChildren)
	{
		const FVector FinalLocation = BossTile->GetComponentLocation() + FVector::DownVector * (CurrentIteration + 1) * AmountIncrementPerIteration;
		BossTilesChildrenMap.Add(BossTile, FinalLocation.Z);

		++CurrentBossTileIndex;
		if (CurrentBossTileIndex >= BossTilesToGetDownPerIteration)
		{
			++CurrentIteration;
			CurrentBossTileIndex = 0;
		}
	}
	bTilesDown = true;
}

void AAfterBossBattle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTilesDown)
	{
		bool bAreAllFinished = true;
		for (auto& MapElem : BossTilesChildrenMap)
		{
			// MapElem -> Pair<Key, Value>
			// Key -> SceneComponent*
			// Value -> float
			if (MapElem.Key)
			{
				const FVector CurrentLoc = MapElem.Key->GetComponentLocation();
				float ZVal = FMath::FInterpConstantTo(CurrentLoc.Z, MapElem.Value, DeltaTime, ComeDownSpeed);
				MapElem.Key->SetWorldLocation(FVector(CurrentLoc.X, CurrentLoc.Y, ZVal));
				if (FMath::IsNearlyEqual(ZVal, MapElem.Value))
				{
					bAreAllFinished = true;
				}
				else
				{
					bAreAllFinished = false;
				}
			}
		}
		if (bAreAllFinished)
		{
			bTilesDown = false;
		}
	}
}

