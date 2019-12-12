// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Pacman2GameModeBase.generated.h"


enum class EGameState : short
{
	EMenu,
	EPlaying,
	EPause,
	EWin,
	EGameOver
};

/**
 * 
 */
UCLASS()
class PACMAN2_API APacman2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	APacman2GameModeBase();

	EGameState GetCurrentState() const;

	void SetCurrentState(EGameState value);

	void SetEnemyVunerable();

	virtual void BeginPlay() override;

	int GetEnemies();

	EGameState CurrentState;

	TArray<class AFoe*> Enemies;

private:

	

	class APlayerController* PlayerController;
	
};
