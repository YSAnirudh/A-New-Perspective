// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/Treasure.h"
#include "Character/ANPPlayerCharacter.h"
#include "UI/ANP_HUD.h"

void ATreasure::OnPickupItem(AANPPlayerCharacter* PlayerCharacter)
{
	// This bool is to ensure the player can't pickup the treasure before defeating the boss.
	if (!bCanTakeTreasure)
	{
		return;
	}
	if (PlayerCharacter)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController()))
		{
			if (AANP_HUD* HUD = Cast<AANP_HUD>(PlayerController->GetHUD()))
			{
				// This should play the Final Animation and Pause the game.
				HUD->FinalAnimation(true);
			}
		}
	}
}
