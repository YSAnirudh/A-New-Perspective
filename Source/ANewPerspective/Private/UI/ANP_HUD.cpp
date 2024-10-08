// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ANP_HUD.h"
#include "Engine/Texture2D.h"
#include "UI/HUDWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Controllers/ANPPlayerController.h"
#include "Kismet/GameplayStatics.h"

AANP_HUD::AANP_HUD()
{
}

void AANP_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UHUDWidget>(GetOwningPlayerController(), HUDWidgetClass, FName("HUD Display"));
		HUDWidget->AddToViewport();
		SetHearts(6);
		SetCoins(0);
		SetStars(0);
	}
}

void AANP_HUD::SetHearts(int NumHearts)
{
	if (HUDWidget && HUDWidget->Heart1 && HUDWidget->Heart2 && HUDWidget->Heart3)
	{
		if (NumHearts == 0)
		{
			FinalAnimation(false);
		}
		switch (NumHearts)
		{
		case 0:
			HUDWidget->Heart1->SetBrushFromTexture(NoHeart);
			HUDWidget->Heart2->SetBrushFromTexture(NoHeart);
			HUDWidget->Heart3->SetBrushFromTexture(NoHeart);
			break;
		case 1:
			HUDWidget->Heart1->SetBrushFromTexture(HalfHeart);
			HUDWidget->Heart2->SetBrushFromTexture(NoHeart);
			HUDWidget->Heart3->SetBrushFromTexture(NoHeart);
			break;
		case 2:
			HUDWidget->Heart1->SetBrushFromTexture(Heart);
			HUDWidget->Heart2->SetBrushFromTexture(NoHeart);
			HUDWidget->Heart3->SetBrushFromTexture(NoHeart);
			break;
		case 3:
			HUDWidget->Heart1->SetBrushFromTexture(Heart);
			HUDWidget->Heart2->SetBrushFromTexture(HalfHeart);
			HUDWidget->Heart3->SetBrushFromTexture(NoHeart);
			break;
		case 4:
			HUDWidget->Heart1->SetBrushFromTexture(Heart);
			HUDWidget->Heart1->SetBrushFromTexture(Heart);
			HUDWidget->Heart3->SetBrushFromTexture(NoHeart);
			break;
		case 5:
			HUDWidget->Heart1->SetBrushFromTexture(Heart);
			HUDWidget->Heart1->SetBrushFromTexture(Heart);
			HUDWidget->Heart3->SetBrushFromTexture(HalfHeart);
			break;
		case 6:
			HUDWidget->Heart1->SetBrushFromTexture(Heart);
			HUDWidget->Heart2->SetBrushFromTexture(Heart);
			HUDWidget->Heart3->SetBrushFromTexture(Heart);
			break;
		}
	}
}

void AANP_HUD::SetStars(int NumStars)
{
	if (HUDWidget && HUDWidget->Star1 && HUDWidget->Star2 && HUDWidget->Star3)
	{
		switch (NumStars)
		{
		case 0:
			HUDWidget->Star1->SetBrushFromTexture(NoStar);
			HUDWidget->Star2->SetBrushFromTexture(NoStar);
			HUDWidget->Star3->SetBrushFromTexture(NoStar);
			break;
		case 1:
			HUDWidget->Star1->SetBrushFromTexture(Star);
			HUDWidget->Star2->SetBrushFromTexture(NoStar);
			HUDWidget->Star3->SetBrushFromTexture(NoStar);
			break;
		case 2:
			HUDWidget->Star1->SetBrushFromTexture(Star);
			HUDWidget->Star2->SetBrushFromTexture(Star);
			HUDWidget->Star3->SetBrushFromTexture(NoStar);
			break;
		case 3:
			HUDWidget->Star1->SetBrushFromTexture(Star);
			HUDWidget->Star2->SetBrushFromTexture(Star);
			HUDWidget->Star3->SetBrushFromTexture(Star);
			break;
		default:
			break;
		}
	}
}

void AANP_HUD::SetCoins(int NumCoins)
{
	if (HUDWidget && HUDWidget->CoinCountText)
	{
		HUDWidget->CoinCountText->SetText(FText::FromString(FString::FromInt(NumCoins)));
	}
}

void AANP_HUD::FlashScreen()
{
	if (HUDWidget && HUDWidget->FlashImage && HUDWidget->FlashAnim)
	{
		FWidgetAnimationDynamicEvent Event;
		Event.BindUFunction(this, FName(TEXT("StopFlash")));
		HUDWidget->BindToAnimationFinished(HUDWidget->FlashAnim, Event);
		HUDWidget->PlayAnimationForward(HUDWidget->FlashAnim);
	}
}

void AANP_HUD::StopFlash()
{
	if (HUDWidget && HUDWidget->FlashImage && HUDWidget->FlashAnim)
	{
		HUDWidget->UnbindAllFromAnimationFinished(HUDWidget->FlashAnim);
		HUDWidget->PlayAnimationReverse(HUDWidget->FlashAnim);
		if (AANPPlayerController* PlayerController = Cast<AANPPlayerController>(GetOwningPlayerController()))
		{
			PlayerController->SwitchView();
		}
	}
}

void AANP_HUD::FinalAnimation(bool bWon)
{
	if (HUDWidget && HUDWidget->FinalAnim && HUDWidget->FinalText)
	{
		if (bWon)
		{
			HUDWidget->FinalText->SetText(FText::FromString(TEXT("You Won! Congrats!")));
		}
		else
		{
			HUDWidget->FinalText->SetText(FText::FromString(TEXT("You Died! Try Restarting!")));
		}
		FWidgetAnimationDynamicEvent Event;
		Event.BindUFunction(this, FName(TEXT("OnFinalAnimFinished")));
		HUDWidget->BindToAnimationFinished(HUDWidget->FinalAnim, Event);
		HUDWidget->PlayAnimationForward(HUDWidget->FinalAnim);
	}
}

void AANP_HUD::OnFinalAnimFinished()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
