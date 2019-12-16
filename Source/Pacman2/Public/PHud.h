// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PHud.generated.h"

UCLASS()
class PACMAN2_API APHud : public AHUD
{
	GENERATED_BODY()

	// Hud constructor
	APHud();

	// Hud font field
	UPROPERTY()
	UFont* HUDFont;

	// Draw Hud method
	virtual void DrawHUD() override;
	
};
