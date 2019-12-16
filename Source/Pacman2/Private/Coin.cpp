// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Pacman2.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Enable collisions
	SetActorEnableCollision(true);

	// Base collision component
	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseCollisionComponent"));

	// Mesh component
	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));
	
	// Attaching mesh component to base collision component
	CollectableMesh->AttachTo(BaseCollisionComponent);

	// Setting the coin as a basic sphere
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	
	// If there is an sphere set it as the mesh component
	if (Sphere.Succeeded()) {
		CollectableMesh->SetStaticMesh(Sphere.Object);
	}

	// Set mesh size
	CollectableMesh->SetWorldScale3D(FVector(0.6, 0.6, 0.6));
	
	// Set collision component radius
	BaseCollisionComponent->SetSphereRadius(25);

}