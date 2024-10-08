// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UHUDWidget::AddToDialogueQueue(FDialogueData DialogueData)
{
	DialogueQueue.Add(DialogueData);
}

bool UHUDWidget::GetNextDialogue(FDialogueData& OutData)
{
	if (DialogueQueue.Num() == 0)
	{
		return false;
	}

	OutData = DialogueQueue[0];
	DialogueQueue.RemoveAt(0);
	return true;
}
