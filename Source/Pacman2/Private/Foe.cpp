// Fill out your copyright notice in the Description page of Project Settings.

#include "Foe.h"
#include "Pacman2.h"
#include "Pac.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"
#include "Materials/Material.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "ApexDefs.h"
#include "PhysXIncludes.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Pacman2GameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Pawn.h"


// Sets default values
AFoe::AFoe()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collisions to true
	SetActorEnableCollision(true);

	// Set capsule radius of component with value of 10
	GetCapsuleComponent()->SetCapsuleRadius(10.0f);
	
	// Set capsule half height component with 25
	GetCapsuleComponent()->SetCapsuleHalfHeight(25.0f);

	// Initialize shape as a pyramid
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Pyramid(TEXT("/Game/StarterContent/Shapes/Shape_TriPyramid"));
	
	// Create mesh component body of sentry droid
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	
	// If there is a pyramid set it as droid's body
	if (Pyramid.Succeeded())
	{
		EnemyBody->SetStaticMesh(Pyramid.Object);

		EnemyBody->SetRelativeScale3D(FVector(0.7f, 0.7f, 1.0f));

		EnemyBody->AttachTo(RootComponent);
	}
	// Scale it and attach to root component

	// Find a material from Materials to be used when Droids are harmless
	static ConstructorHelpers::FObjectFinder<UMaterial> VulnerableMat(TEXT("/Game/Materials/NewMaterial3"));
	
	// Initialize harmless material with the object found 
	VulnerableMaterial = VulnerableMat.Object;

	// Same as above for destroyable material 
	static ConstructorHelpers::FObjectFinder<UMaterial> DestroyableMat(TEXT("/Game/Materials/NewMaterial4"));
	
	DestroyableMaterial = DestroyableMat.Object;

	// The same for slower mat 
	static ConstructorHelpers::FObjectFinder<UMaterial> SlowerMat(TEXT("/Game/Materials/NewMaterial5"));
	
	SlowerMaterial = SlowerMat.Object;

}

// Called when the game starts or when spawned
void AFoe::BeginPlay()
{
	// Calls begin play super
	Super::BeginPlay();

	// Initialize normal droids with default mat
	DefaultMaterial = EnemyBody->GetMaterial(0);

	// Add dynamics when colliding
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AFoe::OnCollision);

}

// Called when harmless or destroyable
void AFoe::Kill()
{
	// If the Droid is destroyable remove from Droids' array 
	if (bIsDestroyable)
	{
		class APacman2GameModeBase* GameMode = Cast<APacman2GameModeBase>(UGameplayStatics::GetGameMode(this));

		GameMode->Enemies.Remove(this);

		this->Destroy();
	}
	// And destroy this droid, but if it just harmless don't 
}

// Called when droids are harmless
void AFoe::SetVulnerable()
{
	// They are for 7 seconds
	GetWorldTimerManager().SetTimer(TimerVunerable, this, &AFoe::SetInvulnerable, 7.0f, false);

	// If already harmless, return
	if (bIsVunerable)
	{
		return;
	}

	// Harmless is on
	bIsVunerable = true;

	// Change droids color to white
	EnemyBody->SetMaterial(0, VulnerableMaterial);
}

// Called when they aren't harmless
void AFoe::SetInvulnerable()
{
	// Clear time harmless
	GetWorldTimerManager().ClearTimer(TimerVunerable);

	// Harmless is off
	bIsVunerable = false;

	// Droids back to normal
	EnemyBody->SetMaterial(0, DefaultMaterial);
}

// When destroyable
void AFoe::SetEnemyDestroyable()
{
	// Destroyable for 6 sec
	GetWorldTimerManager().SetTimer(TimerDestroyable, this, &AFoe::SetEnemyNotDestroyable, 6.0f, false);

	// If already, return
	if (bIsDestroyable)
	{
		return;
	}

	// Destroyable is on
	bIsDestroyable = true;

	// Change to black mat
	EnemyBody->SetMaterial(0, DestroyableMaterial);

}

// When not destroyable
void AFoe::SetEnemyNotDestroyable()
{
	// Clear timer
	GetWorldTimerManager().ClearTimer(TimerDestroyable);

	// Destroyable is off
	bIsDestroyable = false;

	// Back to normal
	EnemyBody->SetMaterial(0, DefaultMaterial);

}

// The same steps of above, but decreasing Droids' speed
void AFoe::SetEnemySlower()
{
	GetWorldTimerManager().SetTimer(TimerSlower, this, &AFoe::SetEnemyNotSlower, 5.0f, false);

	if (bIsSlower)
	{
		return;
	}

	bIsSlower = true;

	EnemyBody->SetMaterial(0, SlowerMaterial);

	GetCharacterMovement()->MaxWalkSpeed = 50.0f;
}

// Same idea, but changing Droids' speed back to normal, and less than chase speed
void AFoe::SetEnemyNotSlower()
{
	GetWorldTimerManager().ClearTimer(TimerSlower);

	bIsSlower = false;

	EnemyBody->SetMaterial(0, DefaultMaterial);

	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

// Droids collisions with Pacman
void AFoe::OnCollision(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If the Droid is harmless or destroyable call Kill, else kill Pacman
	if (OtherActor->IsA(APac::StaticClass()))
	{
		if (bIsVunerable || bIsDestroyable)
		{
			Kill();
		}
		else
		{
			APac* PacMan = Cast<APac>(OtherActor);

			PacMan->Dead();
		}
	}
}

// Called every frame
void AFoe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

