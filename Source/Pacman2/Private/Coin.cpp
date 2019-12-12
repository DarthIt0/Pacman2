// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Pacman2.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetActorEnableCollision(true);

	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseCollisionComponent"));

	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));
	CollectableMesh->AttachTo(BaseCollisionComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if(Sphere.Succeeded())
		CollectableMesh->SetStaticMesh(Sphere.Object);

	CollectableMesh->SetWorldScale3D(FVector(0.6, 0.6, 0.6));
	BaseCollisionComponent->SetSphereRadius(25);
}

