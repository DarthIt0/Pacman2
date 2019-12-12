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
		// Sets default values for this actor's properties
		ACoin();

		UPROPERTY(EditDefaultsOnly, Category = Coin)
		USphereComponent* BaseCollisionComponent;

		UPROPERTY(EditDefaultsOnly, Category = Coin)
		UStaticMeshComponent* CollectableMesh;

		UPROPERTY(EditAnywhere, Category = Coin)
		bool bIsSuperCollectable;

		UPROPERTY(EditAnywhere, Category = Coin)
		bool bIsSuperCollectable2;

		UPROPERTY(EditAnywhere, Category = Coin)
		bool bIsSuperCollectable3;


};