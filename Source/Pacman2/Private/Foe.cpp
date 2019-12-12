// Fill out your copyright notice in the Description page of Project Settings.

#include "Foe.h"
#include "Pacman2.h"
#include "AIFoe.h"
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
#include "GameFramework/Pawn.h"


// Sets default values
AFoe::AFoe()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetActorEnableCollision(true);

	GetCapsuleComponent()->SetCapsuleRadius(10.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(25.0f);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Pyramid(TEXT("/Game/StarterContent/Shapes/Shape_TriPyramid"));
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	if (Pyramid.Succeeded())
	{
		EnemyBody->SetStaticMesh(Pyramid.Object);
		EnemyBody->SetRelativeScale3D(FVector(0.7f, 0.7f, 1.0f));
		EnemyBody->AttachTo(RootComponent);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> VulnerableMat(TEXT("/Game/Materials/NewMaterial3"));
	VulnerableMaterial = VulnerableMat.Object;

	AIControllerClass = AAIFoe::StaticClass();

}

// Called when the game starts or when spawned
void AFoe::BeginPlay()
{
	Super::BeginPlay();

	DefaultMaterial = EnemyBody->GetMaterial(0);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AFoe::OnCollision);

}

void AFoe::SetMove(bool  moveIt)
{
	AAIFoe* AI = Cast<AAIFoe>(AIControllerClass);

	if (moveIt)
	{
		AI->SearchNewPoint();
	}
	else
	{
		AI->StopMove();
	}
}

void AFoe::Kill()
{

	if (bIsDead)
	{
		return;
	}

	bIsDead = true;

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	//Enemies.Remove(this);

	//this->Destroy();

}

void AFoe::Rearm()
{
	bIsDead = false;

	GetCharacterMovement()->MaxWalkSpeed = 150.0f;

	if (bIsVunerable)
	{
		SetInvulnerable();
	}
}

void AFoe::SetVulnerable()
{
	GetWorldTimerManager().SetTimer(TimerVunerable, this, &AFoe::SetInvulnerable, 10.0f, false);

	if (bIsVunerable)
	{
		return;
	}

	bIsVunerable = true;

	EnemyBody->SetMaterial(0, VulnerableMaterial);

	GetCharacterMovement()->MaxWalkSpeed = 50.0f;

}

void AFoe::SetInvulnerable()
{
	GetWorldTimerManager().ClearTimer(TimerVunerable);

	bIsVunerable = false;

	EnemyBody->SetMaterial(0, DefaultMaterial);

	GetCharacterMovement()->MaxWalkSpeed = 150.0f;

}

void AFoe::OnCollision(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APac::StaticClass()))
	{
		if (bIsVunerable)
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

// Called to bind functionality to input
void AFoe::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

