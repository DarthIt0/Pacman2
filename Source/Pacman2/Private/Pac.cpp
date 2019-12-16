// Fill out your copyright notice in the Description page of Project Settings.


#include "Pac.h"
#include "Pacman2.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Coin.h"
#include "Components/CapsuleComponent.h"
#include "EngineUtils.h"
#include "Engine/EngineBaseTypes.h"
#include "ApexDefs.h"
#include "PhysXIncludes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"



// Sets default values
APac::APac()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APac::BeginPlay()
{
	// Super constructor of begin play
	Super::BeginPlay();

	// Initialize game mode variable
	GameMode = Cast<APacman2GameModeBase>(UGameplayStatics::GetGameMode(this));

	// Set collisions to true
	SetActorEnableCollision(true);

	// When Pacman collides add a dynamic
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APac::OnCollision);

	// Counting number of Coins in the World
	for (TActorIterator<ACoin> CoinItr(GetWorld()); CoinItr; ++CoinItr)
	{
		Coins++;
	}

	// Initialize Pacman's initial location
	Origin = GetActorLocation();

	// Set Pacman's initial health
	Health = 2;

}

// Called every frame
void APac::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APac::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Setting up player inputs
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binding input to move in X
	PlayerInputComponent->BindAxis("MoveX", this, &APac::MoveXAxis);
	
	// Binding input to move in Y
	PlayerInputComponent->BindAxis("MoveY", this, &APac::MoveYAxis);
	
	// Binding input to start a new game if player hit N
	PlayerInputComponent->BindAction("NewGame", IE_Pressed, this, &APac::NewGame);
	
	// Binding input to restart game with R pressed
	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &APac::RestartGame);

}

// Adding value to move in X
void APac::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue;
	
	AddMovementInput(CurrentVelocity);

}

// Adding value to move in Y
void APac::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue;
	
	AddMovementInput(CurrentVelocity);

}

// New game changes game mode from Menu to Playing 
void APac::NewGame()
{
	if (GameMode->GetCurrentState() == EGameState::EMenu)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

// Restarting game level 
void APac::RestartGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
}

// Handling Pacman collisions
void APac::OnCollision(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If Game mode is Playing
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		// If Pacman collided with a Coin
		if (OtherActor->IsA(ACoin::StaticClass()))
		{
			// Increase Pacman's score
			++Score;

			// Temporary variable where other actor is cast to coin
			ACoin* Acoins = Cast<ACoin>(OtherActor);

			// If the Coin is of special type 1 increase Pacman's health
			if (Acoins->bIsSuperCollectable)
			{
				++Health;
			}
			
			// If is of type 2, it makes Pacman invencible
			if (Acoins->bIsSuperCollectable2)
			{
				GameMode->SetEnemyVunerable();
			}

			// If 3, makes Pacman faster
			if (Acoins->bIsSuperCollectable3)
			{
				SetTurbo();
			}

			// If 4, Droids can be destroyed
			if (Acoins->bIsSuperCollectable4)
			{
				GameMode->SetEnemyDestroyable();
			}

			// If 5, Droids are slower
			if (Acoins->bIsSuperCollectable5)
			{
				GameMode->SetEnemySlower();
			}
			
			// After Pacman gets a Coin, the coin is destroyed
			OtherActor->Destroy();
			
			// If there are no more Coins to get, change game state to Win
			if(--Coins == 0)
			{
				GameMode->SetCurrentState(EGameState::EWin);
			}
		}
	}

}

// Called when Pacman gets hit by a Droid which is not vulnerable or destroyable
void APac::Dead()
{
	// If Pacman's health is depleted, change game state to Game Over
	if(--Health == 0)
	{
		GameMode->SetCurrentState(EGameState::EGameOver);
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed *= 10.0f;
		SetActorLocation(Origin);
		GetCharacterMovement()->MaxWalkSpeed *= 0.1f;
	}
	// If it's not, send him fast to his initial location 

}

// Called if Turbo Mode
void APac::SetTurbo()
{
	// Turbo time of 5 seconds
	GetWorldTimerManager().SetTimer(TimerTurbo, this, &APac::SetNotTurbo, 5.0f, false);

	// If already on Turbo mode, return
	if (bIsTurbo)
	{
		return;
	}

	// Turbo is on
	bIsTurbo = true;

	// Pacman's speed is doubled
	GetCharacterMovement()->MaxWalkSpeed *= 2.0f;

}

// Called if not Turbo
void APac::SetNotTurbo()
{
	// Clear Turbo time
	GetWorldTimerManager().ClearTimer(TimerTurbo);

	// Turbo is off
	bIsTurbo = false;

	// Pacman's speed is back to normal
	GetCharacterMovement()->MaxWalkSpeed *= 0.5f;

}