// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "GameFramework/PlayerController.h"
#include "StandardZombiePlayerController.generated.h"


/**
 * 
 */
UCLASS()
class AStandardZombiePlayerController : public AAIController
{
	GENERATED_BODY()
	float MAX_BIAS = 500;
	float MAX_INTELLIGENCE = 100;

public:
	virtual void Possess(class APawn *InPawn) override;
	virtual void BeginInactiveState() override;

	void MoveToLocation(const FVector destLocation, UNavigationSystem const *navSys);

protected:
	float intelligence = 100;
};
