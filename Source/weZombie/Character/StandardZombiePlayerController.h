// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "StandardZombiePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AStandardZombiePlayerController : public AAIController
{
	GENERATED_UCLASS_BODY()

	virtual void Possess(class APawn *InPawn) override;
	virtual void BeginInactiveState() override;
};
