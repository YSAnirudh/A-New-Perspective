// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/ANPPlayerController.h"
#include "Character/Movement/ANPMovementComponent.h"
#include "Character/ANPPlayerCharacter.h"
#include "GameModes/ANPGameModeBase.h"
#include "Input/ANPInputComponent.h"
#include "ANPGameplayTags.h"
#include "UI/ANP_HUD.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"

AANPPlayerController::AANPPlayerController()
{
}

void AANPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!IsValid(InputComponent) || !IsValid(BaseInputConfig))
	{
		return;
	}

	// Add Mapping Context
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GetLocalPlayer()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (BaseInputConfig->InputMappingContext)
			{
				InputSubsystem->AddMappingContext(BaseInputConfig->InputMappingContext, 0);
			}
		}
	}

	// Bind Input Actions
	if (UANPInputComponent* ANPInputComponent = Cast<UANPInputComponent>(InputComponent))
	{
		ANPInputComponent->BindInputActionByTag(BaseInputConfig, ANPGameplayTags::Input_Move, this, ETriggerEvent::Triggered, &AANPPlayerController::Move);
		ANPInputComponent->BindInputActionByTag(BaseInputConfig, ANPGameplayTags::Input_Jump, this, ETriggerEvent::Triggered, &AANPPlayerController::Jump);
		ANPInputComponent->BindInputActionByTag(BaseInputConfig, ANPGameplayTags::Input_Dash, this, ETriggerEvent::Triggered, &AANPPlayerController::Dash);
		ANPInputComponent->BindInputActionByTag(BaseInputConfig, ANPGameplayTags::Input_Switch, this, ETriggerEvent::Triggered, &AANPPlayerController::Switch);
	}
}

void AANPPlayerController::Move(const FInputActionValue& Value)
{
	APawn* InPawn = GetPawn();
	if (!InPawn || !InPawn->InputEnabled())
	{
		return;
	}

	FVector2D Value2D = Value.Get<FVector2D>();

	if (Value2D.X != 0.0f)
	{
		// Move Left, Right. (Forward and Back from the Character's Perspective)
		InPawn->AddMovementInput(FVector::XAxisVector, Value2D.X);
	}

	if (AANPGameModeBase::IsIn3D())
	{
		// Not used in 2D
		if (Value2D.Y != 0.0f)
		{
			// Move In and Out. (Left and Right from the Character's Perspective)
			InPawn->AddMovementInput(FVector::YAxisVector, Value2D.Y);
		}
	}
}

void AANPPlayerController::Jump(const FInputActionValue& Value)
{
	if (AANPCharacter* ANPCharacter = GetPawn<AANPCharacter>())
	{
		if (ANPCharacter->InputEnabled())
		{
			ANPCharacter->Jump();
		}
	}
}

void AANPPlayerController::Dash(const FInputActionValue& Value)
{
	if (AANPPlayerCharacter* ANPPlayerCharacter = GetPawn<AANPPlayerCharacter>())
	{
		if (ANPPlayerCharacter->InputEnabled())
		{
			ANPPlayerCharacter->Dash();
		}
	}
}

void AANPPlayerController::Switch(const FInputActionValue& Value)
{
	if (AANPPlayerCharacter* ANPPlayerCharacter = GetPawn<AANPPlayerCharacter>())
	{
		if (ANPPlayerCharacter->bCanSwitchTo3D)
		{
			AANPGameModeBase::SetIsIn3D(true);
			// Remove 2D Plane Constraint.
			if (UANPMovementComponent* MoveComp = ANPPlayerCharacter->GetANPMovementComponent())
			{
				MoveComp->bConstrainToPlane = false;
			}
			// Flash Screen and Switch when fully black. Call to Switch is called in WBP_HUD
			if (AANP_HUD* HUD = Cast<AANP_HUD>(GetHUD()))
			{
				HUD->FlashScreen();
			}
			// Cannot Switch back and forth.
			ANPPlayerCharacter->bCanSwitchTo3D = false;
		}
	}
}

void AANPPlayerController::SwitchView()
{
	// Called from WBP_HUD when screen is fully black.
	if (AANPPlayerCharacter* ANPPlayerCharacter = GetPawn<AANPPlayerCharacter>())
	{
		ANPPlayerCharacter->GetCamera()->SetProjectionMode(ECameraProjectionMode::Perspective);
		ANPPlayerCharacter->Set3DSpringArmRotation();
	}
}
