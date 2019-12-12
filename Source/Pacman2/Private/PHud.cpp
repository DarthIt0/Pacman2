// Fill out your copyright notice in the Description page of Project Settings.


#include "PHud.h"
#include "Pacman2.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "Pacman2GameModeBase.h"
#include "Pac.h"




APHud::APHud()
{
	static ConstructorHelpers::FObjectFinder<UFont> HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));

	if(HUDFontOb.Object != NULL)
	{
		HUDFont = HUDFontOb.Object;
	}
}

void APHud::DrawHUD()
{
	FVector2D ScreenDimension = FVector2D(Canvas->SizeX, Canvas->SizeY);

	Super::DrawHUD();

	class APacman2GameModeBase* GameMode = Cast<APacman2GameModeBase>(UGameplayStatics::GetGameMode(this));

	APac* Pacman = Cast<APac>(UGameplayStatics::GetPlayerPawn(this, 0));

	int Enemies = GameMode->GetEnemies();

	switch (GameMode->GetCurrentState())
	{
	case EGameState::EMenu:
		DrawText(TEXT(" Pacman Game!"), FColor::Orange, 50, 50, HUDFont);
		DrawText(TEXT(" Welcome!"), FColor::Orange, 50, 150, HUDFont);
		DrawText(TEXT(" New Game \n (Press N) \n\n"), FColor::Orange, 50, 250, HUDFont);
		DrawText(TEXT("(Left-click mouse first,)"), FColor::Orange, 50, 360, HUDFont, 0.75);
		DrawText(TEXT("(then start a new game)"), FColor::Orange, 50, 375, HUDFont, 0.75);
		
		
		
		
		

		break;
	case EGameState::EPlaying:
		
		

		if (Pacman)
		{
			FString Score = TEXT("Score:  ") + FString::FromInt(Pacman->Score);

			FString Life = TEXT("Health:  ") + FString::FromInt(Pacman->Health);

			//FString Droids = TEXT("Droids:  ") + FString::FromInt(Enemies);

			DrawText("Restart Game \n(Press R) \n\n", FColor::Orange, 50, 50, HUDFont);
			//DrawText("Pause Game \n(Press P) \n\n", FColor::Orange, 50, 150, HUDFont);
			DrawText(Score, FColor::Blue, 850, 50, HUDFont);
			DrawText(Life, FColor::Green, 850, 150, HUDFont);
			//DrawText(Droids, FColor::Red, 850, 250, HUDFont);


		}
		break;
	case EGameState::EGameOver:
		DrawText(TEXT("        Game Over!\n\n (Press R to restart)"), FColor::Magenta, 310, 200, HUDFont,2);
		break;
	case EGameState::EPause:
		DrawText(TEXT("         Game Paused!\n\n (Press R to restart)"), FColor::White, 310, 200, HUDFont, 2);
		break;
	case EGameState::EWin:
		DrawText(TEXT("         You Win!\n\n (Press R to restart)"), FColor::Yellow, 310, 200, HUDFont,2);
		break;
	default:
		break;
	}
}

