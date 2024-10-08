// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagsClasses.h"
#include "ANPInputConfig.h"
#include "ANPInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ANEWPERSPECTIVE_API UANPInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:

	template<class UserClass, typename FunctionType>
	void BindInputActionByTag(const UANPInputConfig* InputConfig, const FGameplayTag& InputTag, UserClass* Object, ETriggerEvent TriggerEvent, FunctionType Function);
};

template<class UserClass, typename FunctionType>
inline void UANPInputComponent::BindInputActionByTag(const UANPInputConfig* InputConfig, const FGameplayTag& InputTag, UserClass* Object, ETriggerEvent TriggerEvent, FunctionType Function)
{
	if (!IsValid(Object) || !IsValid(InputConfig))
	{
		return;
	}

	if (UInputAction* InputAction = InputConfig->GetInputActionByTag(InputTag))
	{
		BindAction(InputAction, TriggerEvent, Object, Function);
	}
}
