// Fill out your copyright notice in the Description page of Project Settings.


#include "Pacman2GameModeBase.h"
#include "Pacman2.h"
#include "Foe.h"
#include "UObject/ConstructorHelpers.h"
//#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "PHud.h"



APacman2GameModeBase::APacman2GameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerOb(TEXT("/Game/Blueprints/BP_Pac"));
	if(PlayerOb.Class != NULL)
	{
		DefaultPawnClass = PlayerOb.Class;
		HUDClass = APHud::StaticClass();
	}
}

void APacman2GameModeBase::SetCurrentState(EGameState value) 
{
	CurrentState = value;

	for (auto Iter(Enemies.CreateIterator()); Iter; Iter++)
	{
		switch (value)
		{
		case EGameState::EMenu:
			(*Iter)->SetMove(false);
			break;
		case EGameState::EPlaying:
			(*Iter)->SetMove(true);
			break;
		case EGameState::EGameOver:
			(*Iter)->Destroy();
			break;
		case EGameState::EWin:
			(*Iter)->Destroy();
			break;
		case EGameState::EPause:
			(*Iter)->SetMove(false);
			break;
		default:
			break;
		}
	}

}

EGameState APacman2GameModeBase::GetCurrentState() const
{
	return CurrentState;
}

void APacman2GameModeBase::BeginPlay()
{
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
}

void APacman2GameModeBase::SetEnemyVunerable()
{

	for(auto Iter(Enemies.CreateIterator()); Iter; Iter++)
	{
		(*Iter)->SetVulnerable();
	}
}

int APacman2GameModeBase::GetEnemies()
{
	return Enemies.Num();
}
