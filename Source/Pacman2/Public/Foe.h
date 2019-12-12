// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pac.h"
#include "Foe.generated.h"

UCLASS()
class PACMAN2_API AFoe : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFoe();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;//

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;//

	//virtual void BeginPlay() override;

	UFUNCTION()
		void OnCollision(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = Body)
		UStaticMeshComponent* EnemyBody;

	void SetVulnerable();

	void SetInvulnerable();

	void SetMove(bool MoveIt);

	void Kill();

	void Rearm();

	bool bIsDead;

private:

	bool bIsVunerable;

	FTimerHandle TimerVunerable;

	class UMaterialInterface* DefaultMaterial;

	class UMaterialInterface* VulnerableMaterial;


};
