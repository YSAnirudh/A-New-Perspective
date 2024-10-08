// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ANPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ANEWPERSPECTIVE_API AANPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	static bool IsIn3D() { return bIsIn3D; }
	static void SetIsIn3D(bool b3D) { bIsIn3D = !bIsIn3D ? b3D : true; }

private:

	static bool bIsIn3D;
};

typedef AANPGameModeBase ANP_GM;
