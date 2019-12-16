// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pacman2GameModeBase.h"
#include "Pac.generated.h"

UCLASS()
class PACMAN2_API APac : public ACharacter
{
	GENERATED_BODY()

public:
	
	// Pacman's constructor
	APac();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Sets default values for this character's properties

	// Pacman's velocity
	FVector CurrentVelocity;

	// Needed coins to win the game
	uint8 Coins;

	// Pacman's health
	uint8 Health;

	// Score after getting a coin
	uint8 Score;

	// Pacman's initial location
	FVector Origin;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Method called when Pacman is hit by Droids
	void Dead();

	// Called when Pacman gets a Silver coin, makes him faster
	void SetTurbo();

	// Called when Turbo mode is over
	void SetNotTurbo();

private:

	// Method to get X direction values
	void MoveXAxis(float AxisValue);
	
	// Function to get Y ones
	void MoveYAxis(float AxisValue);

	// Called to start a new game
	void NewGame();

	// Called to restart game
	void RestartGame();

	// This variable holds game mode
	APacman2GameModeBase* GameMode;

	// Turbo mode is on or off
	bool bIsTurbo;

	// Turbo mode timer
	FTimerHandle TimerTurbo;

	// Called when Pacman collides with a Coin or other actor
	UFUNCTION()
		void OnCollision(class UPrimitiveComponent* OverlappedComponent,class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};