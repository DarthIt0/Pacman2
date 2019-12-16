// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Pacman2GameModeBase.generated.h"

// Enumerator of the Game mode states
enum class EGameState : short
{
	EMenu,
	EPlaying,
	EWin,
	EGameOver
};

UCLASS()
class PACMAN2_API APacman2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	// Game mode constructor
	APacman2GameModeBase();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Getter method of current Game mode state
	EGameState GetCurrentState() const;

	// Setter of current Game mode state
	void SetCurrentState(EGameState value);

	// This method makes Pacman invulnerable to Droids
	void SetEnemyVunerable();

	// Method that makes Droids destroyable by Pacman
	void SetEnemyDestroyable();

	// Makes Droids slower
	void SetEnemySlower();

	// Variable to hold current game state
	EGameState CurrentState;

	// Array holding Droids
	TArray<class AFoe*> Enemies;

private:

	// Player controller variable
	class APlayerController* PlayerController;
	
};
