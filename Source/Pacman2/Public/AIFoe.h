// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Foe.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "AI/Navigation/NavAgentInterface.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIFoe.generated.h"

/**
 *
 */
UCLASS()
class PACMAN2_API AAIFoe : public AAIController
{
    GENERATED_BODY()

public:

    AAIFoe();

    void OnPossess(class APawn* InPawn) override;

    virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

    void SearchNewPoint();

    void GoHome();

    void Rearm();

    void StopMove();

private:

    class AFoe* Bot;

    FVector HomeLocation;

    FTimerHandle TimerDead;

};
