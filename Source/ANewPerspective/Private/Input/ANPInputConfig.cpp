// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ANPInputConfig.h"
#include "InputAction.h"
#include "InputMappingContext.h"

UInputAction* UANPInputConfig::GetInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FANPInputData& InputData : InputActionMap)
	{
		if (InputTag.MatchesTagExact(InputData.InputTag))
		{
			return InputData.InputAction;
		}
	}

	return nullptr;
}
