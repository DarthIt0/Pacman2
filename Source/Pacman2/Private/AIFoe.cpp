// Fill out your copyright notice in the Description page of Project Settings.


#include "AIFoe.h"
#include "Pacman2.h"
#include "TimerManager.h"
#include "NavigationSystem.h"
#include <Runtime/NavigationSystem/Public/NavigationSystem.h>
#include "NavMesh/RecastNavMeshGenerator.h"
#include "RecastNavMesh.h"
#include "Navmesh/Public/Recast/Recast.h"
#include "Pac.h"
#include "Kismet/GameplayStatics.h"
#include "Actor.h"
#include "ApexDefs.h"
#include "PhysXIncludes.h"
#include "GameFramework/Pawn.h"
#include "NavigationPath.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include <Runtime\AIModule\Classes\Blueprint\AIBlueprintHelperLibrary.h>
#include "NavigationData.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"



AAIFoe::AAIFoe()
{
	PrimaryActorTick.bCanEverTick = true;
	

}

void AAIFoe::OnPossess(class APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Bot = Cast<AFoe>(InPawn);

	HomeLocation = Bot->GetActorLocation();

	SearchNewPoint();

}

void AAIFoe::GoHome()
{
	MoveToLocation(HomeLocation);
	GetWorldTimerManager().SetTimer(TimerDead, this, &AAIFoe::Rearm, 5.0f, false);
}

void AAIFoe::Rearm()
{
	GetWorldTimerManager().ClearTimer(TimerDead);
	Bot->Rearm();
}

void AAIFoe::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	Bot->K2_UpdateCustomMovement(3.0f);

	//if (!Bot->bIsDead)
	//{
		SearchNewPoint();
	//}
}

void AAIFoe::StopMove()
{
	StopMovement();
}

void AAIFoe::SearchNewPoint()
{
	UNavigationSystemV1* NavMesh = UNavigationSystemV1::GetCurrent(this);
	if(NavMesh)
	{
		const float SearchRadius = 10000.0f;
		FNavLocation RandomPt;
		const bool bFound = NavMesh->K2_GetRandomReachablePointInRadius(Bot, Bot->GetActorLocation(), RandomPt.Location, SearchRadius);
		if(bFound)
		{
			MoveToLocation(RandomPt.Location);
		}
	}
}





