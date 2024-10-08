// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagsClasses.h"
#include "ANPInputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

/**
* Input Data using Gameplay Tags
*/
USTRUCT(Blueprintable)
struct FANPInputData
{
	GENERATED_BODY();
	
	UPROPERTY(EditAnywhere, Category = "Input")
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InputAction;

};

/**
 * Input Config to have all the Input Actions in one place.
 */
UCLASS()
class ANEWPERSPECTIVE_API UANPInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UInputAction* GetInputActionByTag(const FGameplayTag& InputTag) const;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditAnywhere, Category = "Input")
	TArray<FANPInputData> InputActionMap;

};
