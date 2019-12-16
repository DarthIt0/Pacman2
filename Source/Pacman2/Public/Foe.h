// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pac.h"
#include "GameFramework/DefaultPawn.h"
#include "Foe.generated.h"

UCLASS()
class PACMAN2_API AFoe : public ACharacter
{
	GENERATED_BODY()

public:
	// Droid constructor
	AFoe();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when Droids collide with Pacman
	UFUNCTION()
		void OnCollision(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Droids mesh component field
	UPROPERTY(EditDefaultsOnly, Category = Body)
		UStaticMeshComponent* EnemyBody;

	// Method to set Droids harmless
	void SetVulnerable();

	// Method to set Droids not harmless anymore
	void SetInvulnerable();

	// Set Droids destroyable
	void SetEnemyDestroyable();

	// Set Droids undestroyable
	void SetEnemyNotDestroyable();

	// Droids set slower
	void SetEnemySlower();

	// Droids back to normal
	void SetEnemyNotSlower();

	// Droids are killed if harmless or destroyable
	void Kill();

private:

	// Harmless or not
	bool bIsVunerable;

	// The time harmless
	FTimerHandle TimerVunerable;

	// Droid's material when it is normal
	class UMaterialInterface* DefaultMaterial;

	// Material when it's harmless
	class UMaterialInterface* VulnerableMaterial;

	// Droid is destroyable or not
	bool bIsDestroyable;

	// Time destroyable
	FTimerHandle TimerDestroyable;

	// Destroyable mat
	class UMaterialInterface* DestroyableMaterial;

	// Slower or not
	bool bIsSlower;

	// Timer
	FTimerHandle TimerSlower;

	// Mat
	class UMaterialInterface* SlowerMaterial;
};
