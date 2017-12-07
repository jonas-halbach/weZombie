// Fill out your copyright notice in the Description page of Project Settings.

#include "weZombie.h"
#include "StandardZombiePlayerController.h"
#include "StandardZombie.h"

void AStandardZombiePlayerController::Possess(class APawn *inPawn)
{
	Super::Possess(inPawn);
	AStandardZombie *zombie = Cast<AStandardZombie>(inPawn);
}

void AStandardZombiePlayerController::BeginInactiveState()
{
	Super::BeginInactiveState();
}

void AStandardZombiePlayerController::MoveToLocation(const FVector destLocation, UNavigationSystem const *navSys)
{
	FVector biasVector = FVector4(1, 1, 1, 1);
	biasVector *= MAX_BIAS * (MAX_INTELLIGENCE - intelligence);

	FVector biassedDestLocation = destLocation + biasVector;

	navSys->SimpleMoveToLocation(this, biassedDestLocation);
}
