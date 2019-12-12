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
	// Sets default values for this character's properties
	APac();

	FVector CurrentVelocity;

	uint8 Coins;
	uint8 Health;
	uint8 Score;

	FVector Origin;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Dead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:

	void MoveXAxis(float AxisValue);
	void MoveYAxis(float AxisValue);

	void NewGame();
	void Pause();
	void RestartGame();

	APacman2GameModeBase* GameMode;

	//bool Turbo;

	

	//void DelegateFuntion(class AActor* otherActor, class UPrimitiveComponent* otherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollision(class UPrimitiveComponent* OverlappedComponent,class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
