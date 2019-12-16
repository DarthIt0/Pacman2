// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Coin.generated.h"


UCLASS()
class PACMAN2_API ACoin : public AActor
{
	GENERATED_BODY()

public:	
	
	// Coins's constructor
	ACoin();

public:
	// Sets default values for this actor's properties

	// Creating collision component of the Coin
	UPROPERTY(EditDefaultsOnly, Category = Coin)
		USphereComponent* BaseCollisionComponent;
	
	// Creating mesh component of the Coin
	UPROPERTY(EditDefaultsOnly, Category = Coin)
		UStaticMeshComponent* CollectableMesh;
	
	// Creating fields for each special Coin
	UPROPERTY(EditAnywhere, Category = Coin)
		bool bIsSuperCollectable;
	
	// First one increase Pacman's health, 2nd is for invulnerability
	UPROPERTY(EditAnywhere, Category = Coin)
		bool bIsSuperCollectable2;
	
	// 3rd field is for making Pacman faster
	UPROPERTY(EditAnywhere, Category = Coin)
		bool bIsSuperCollectable3;
	
	// With the 4th field of the coin, Droids are destroyable 
	UPROPERTY(EditAnywhere, Category = Coin)
		bool bIsSuperCollectable4;
	
	// If Pacman gets a coin with 5th field active, Droids get slower 
	UPROPERTY(EditAnywhere, Category = Coin)
		bool bIsSuperCollectable5;

};