// Fill out your copyright notice in the Description page of Project Settings.


#include "Pacman2GameModeBase.h"
#include "Pacman2.h"
#include "Foe.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "PHud.h"

// Initialize game mode base with Pacman's Blueprint and a Heads Up Display
APacman2GameModeBase::APacman2GameModeBase()
{
	// Instantiate the default pawn as Player Object from blueprint
	static ConstructorHelpers::FClassFinder<APawn> PlayerOb(TEXT("/Game/Blueprints/BP_Pac"));
	
	if(PlayerOb.Class != NULL)
	{
		DefaultPawnClass = PlayerOb.Class;
		
		HUDClass = APHud::StaticClass();
	}
	// Instantiate the HUD class as the custom APHud

}

// Setting the current game state with value 
void APacman2GameModeBase::SetCurrentState(EGameState value) 
{
	CurrentState = value;

	for (auto Iter(Enemies.CreateIterator()); Iter; Iter++)
	{
		switch (value)
		{
			case EGameState::EGameOver:
				
				(*Iter)->Destroy();
				
				break;
			
			case EGameState::EWin:
				
				(*Iter)->Destroy();
				
				break;
			
			default:
				
				break;
		}
	}
	// Iterate across the Droids Array and Destroy them depending on the Game mode
}

// Getting the current game state 
EGameState APacman2GameModeBase::GetCurrentState() const
{
	return CurrentState;
}

// Initializing game mode base on begin play
void APacman2GameModeBase::BeginPlay()
{
	// Construct begin play with super, set current game mode state to Menu
	Super::BeginPlay();

	SetCurrentState(EGameState::EMenu);

	PlayerController = GetWorld()->GetFirstPlayerController();

	for (TActorIterator<AFoe> enemyItr(GetWorld()); enemyItr ; ++enemyItr)
	{
		AFoe* enemy = Cast<AFoe>(*enemyItr);
		
		if (enemy)
		{ 
			Enemies.Add(enemy);
		}
	}
	// Get first player controller from World and add Droids to Droids' Array
}

// Setting each Droid of the array, harmless
void APacman2GameModeBase::SetEnemyVunerable()
{
	for(auto Iter(Enemies.CreateIterator()); Iter; Iter++)
	{
		(*Iter)->SetVulnerable();
	}
}

// Setting each Droid, destroyable
void APacman2GameModeBase::SetEnemyDestroyable()
{
	for (auto Iter(Enemies.CreateIterator()); Iter; Iter++)
	{
		(*Iter)->SetEnemyDestroyable();
	}
}

// Setting each one slower
void APacman2GameModeBase::SetEnemySlower()
{
	for (auto Iter(Enemies.CreateIterator()); Iter; Iter++)
	{
		(*Iter)->SetEnemySlower();
	}
}