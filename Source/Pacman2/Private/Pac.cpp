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



// Sets default values
APac::APac()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APac::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<APacman2GameModeBase>(UGameplayStatics::GetGameMode(this));

	SetActorEnableCollision(true);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APac::OnCollision);

	for (TActorIterator<ACoin> CoinItr(GetWorld()); CoinItr; ++CoinItr)
	{
		Coins++;
	}

	Origin = GetActorLocation();

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
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &APac::MoveXAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &APac::MoveYAxis);
	PlayerInputComponent->BindAction("NewGame", IE_Pressed, this, &APac::NewGame);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APac::Pause);
	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &APac::RestartGame);


}

void APac::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue;
	AddMovementInput(CurrentVelocity);
}

void APac::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue;
	AddMovementInput(CurrentVelocity);
}

void APac::NewGame()
{
	if (GameMode->GetCurrentState() == EGameState::EMenu)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APac::Pause()
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		GameMode->SetCurrentState(EGameState::EPause);
	}
	else if (GameMode->GetCurrentState() == EGameState::EPause)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APac::RestartGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
}

void APac::OnCollision(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		if (OtherActor->IsA(ACoin::StaticClass()))
		{
			++Score;

			ACoin* Acoins = Cast<ACoin>(OtherActor);

			if (Acoins->bIsSuperCollectable)
			{
				++Health;
			}
			
			if (Acoins->bIsSuperCollectable2)
			{
				GameMode->SetEnemyVunerable();
			}

			//if (Acoins->bIsSuperCollectable3)
			//{
			//	Turbo = true;
			//}
			
			OtherActor->Destroy();
			
			if(--Coins == 0)
			{
				GameMode->SetCurrentState(EGameState::EWin);
			}
		}

	}
}

void APac::Dead()
{
	if(--Health == 0)
	{
		GameMode->SetCurrentState(EGameState::EGameOver);
	}
	else
	{
		SetActorLocation(Origin);
	}
}