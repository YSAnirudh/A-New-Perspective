// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UTextBlock;
class UImage;
class UWidgetAnimation;

USTRUCT(BlueprintType)
struct FDialogueData
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString FullText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	float DelayPerFractionDisplay = 0.02f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	float DelayAfterDisplay = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bWaitAfterWords = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (EditCondition = "bWaitAfterWords", EditConditionHides))
	float WaitDelayAfterWords = 0.3f;
};

/**
 * 
 */
UCLASS()
class ANEWPERSPECTIVE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CoinCountText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Heart1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Heart2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Heart3 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Star1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Star2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Star3 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* FlashImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FlashAnim = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FinalAnim = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* FinalText = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	TArray<FDialogueData> DialogueQueue;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowDialogue(FDialogueData DialogueData);

	UFUNCTION(BlueprintCallable)
	void AddToDialogueQueue(FDialogueData DialogueData);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetNextDialogue(FDialogueData& OutData);

};
