// Fill out your copyright notice in the Description page of Project Settings.


#include "PHud.h"
#include "Pacman2.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "Pacman2GameModeBase.h"
#include "Pac.h"

// Initializing the Heads-Up Display with a font object
APHud::APHud()
{
	static ConstructorHelpers::FObjectFinder<UFont> HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));

	if(HUDFontOb.Object != NULL)
	{
		HUDFont = HUDFontOb.Object;
	}
}

// Called to draw the Hud
void APHud::DrawHUD()
{
	// Hud canvas dimensions on the screen
	FVector2D ScreenDimension = FVector2D(Canvas->SizeX, Canvas->SizeY);

	// Hud super constructor
	Super::DrawHUD();

	// Variable to hold the game mode
	class APacman2GameModeBase* GameMode = Cast<APacman2GameModeBase>(UGameplayStatics::GetGameMode(this));

	// Variable to hold Pacman
	APac* Pacman = Cast<APac>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Depending on the Game mode show different UI
	switch (GameMode->GetCurrentState())
	{

	case EGameState::EMenu:
		
		// Greetings menu
		DrawText(TEXT(" Pacman Game!"), FColor::Orange, 50, 50, HUDFont);
		
		DrawText(TEXT(" Welcome!"), FColor::Orange, 50, 150, HUDFont);
		
		// Starting a new game
		DrawText(TEXT(" New Game \n (Press N) \n\n"), FColor::Orange, 50, 250, HUDFont);
		
		DrawText(TEXT("(Left-click mouse)"), FColor::Orange, 50, 360, HUDFont, 0.75);
		
		DrawText(TEXT("(start a new game)"), FColor::Orange, 50, 375, HUDFont, 0.75);
		
		// Objectives
		DrawText(TEXT("  Finish the game"), FColor::Orange, 800, 50, HUDFont);
		
		DrawText(TEXT("  by collecting coins."), FColor::Orange, 800, 100, HUDFont);
		
		DrawText(TEXT(" Get special Coins!"), FColor::Orange, 800, 250, HUDFont);
		
		DrawText(TEXT(" Avoid sentry droids!"), FColor::Orange, 800, 350, HUDFont);
		
		break;

	case EGameState::EPlaying:

		if (Pacman)
		{
			FString Score = TEXT("Score:  ") + FString::FromInt(Pacman->Score);

			FString Life = TEXT("Health:  ") + FString::FromInt(Pacman->Health);

			// Restarting the game
			DrawText("Restart Game \n(Press R) \n\n", FColor::Orange, 30, 50, HUDFont);
			
			// Describing special coins
			DrawText(TEXT("Blue coins make"), FColor::Orange, 25, 150, HUDFont, 0.85);
			
			DrawText(TEXT("Enemies slower!"), FColor::Orange, 25, 175, HUDFont, 0.85);
			
			DrawText(TEXT("Green coins make"), FColor::Orange, 25, 225, HUDFont, 0.85);
			
			DrawText(TEXT("Enemies destroyable!"), FColor::Orange, 25, 250, HUDFont, 0.85);

			// Showing player stats
			DrawText(Score, FColor::Orange, 850, 50, HUDFont);
			
			DrawText(Life, FColor::Orange, 850, 100, HUDFont);
			
			DrawText(TEXT(" Gold coins give"), FColor::Orange, 825, 200, HUDFont, 0.85);
			
			DrawText(TEXT(" Pacman health!"), FColor::Orange, 825, 225, HUDFont, 0.85);
			
			DrawText(TEXT(" Silver coins make"), FColor::Orange, 825, 275, HUDFont, 0.85);
			
			DrawText(TEXT(" Pacman faster!"), FColor::Orange, 825, 300, HUDFont, 0.85);
			
			DrawText(TEXT(" Bronze coins make"), FColor::Orange, 825, 350, HUDFont, 0.85);
			
			DrawText(TEXT(" Pacman invencible!"), FColor::Orange, 825, 375, HUDFont, 0.85);
		}
		break;

	case EGameState::EGameOver:
		
		// Showing after losing condition is met
		DrawText(TEXT("        Game Over!\n\n (Press R to restart)"), FColor::Magenta, 310, 200, HUDFont,2);
		
		break;

	case EGameState::EWin:
		
		// Show it after winning
		DrawText(TEXT("         You Win!\n\n (Press R to restart)"), FColor::Yellow, 310, 200, HUDFont,2);
		
		break;

	default:

		break;
	}
}

