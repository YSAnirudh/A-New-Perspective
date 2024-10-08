// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ANPPlayerController.generated.h"

class UANPInputConfig;

struct FInputActionValue;

/**
 * Player Controller Class Handling all input
 */
UCLASS()
class ANEWPERSPECTIVE_API AANPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AANPPlayerController();

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Jump(const FInputActionValue& Value);

	UFUNCTION()
	void Dash(const FInputActionValue& Value);

	UFUNCTION()
	void Switch(const FInputActionValue& Value);

	void SwitchView();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UANPInputConfig* BaseInputConfig;
};
