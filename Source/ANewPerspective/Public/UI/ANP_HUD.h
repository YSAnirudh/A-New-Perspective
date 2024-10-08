// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ANP_HUD.generated.h"

class UHUDWidget;
class UTexture2D;
/**
 * 
 */
UCLASS()
class ANEWPERSPECTIVE_API AANP_HUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AANP_HUD();
	virtual void BeginPlay() override;

	UFUNCTION()
	void SetHearts(int NumHearts);
	UFUNCTION()
	void SetStars(int NumStars);
	UFUNCTION()
	void SetCoins(int NumCoins);

	UFUNCTION()
	void FlashScreen();

	UFUNCTION()
	void StopFlash();

	UFUNCTION()
	void FinalAnimation(bool bWon);

	UFUNCTION()
	void OnFinalAnimFinished();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UHUDWidget* HUDWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UTexture2D* Heart = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UTexture2D* HalfHeart = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UTexture2D* NoHeart = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UTexture2D* NoStar = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UTexture2D* Star = nullptr;
};
