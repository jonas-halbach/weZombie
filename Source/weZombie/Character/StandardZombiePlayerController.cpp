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

void AStandardZombiePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	intelligence -= DeltaSeconds * intelligenceDrainPerSecond;

	intelligence = intelligence > 0 ? intelligence : 0;
}

void AStandardZombiePlayerController::MoveToLocation(const FVector destLocation, UNavigationSystem const *navSys)
{
	float maxBiasByIntelligence = MAX_BIAS * (MAX_INTELLIGENCE - intelligence) / MAX_INTELLIGENCE;
	float xBias = FMath::RandRange(0.0f, 1.0f) * maxBiasByIntelligence;
	float yBias = FMath::RandRange(0.0f, 1.0f) * maxBiasByIntelligence;
	FVector biasVector = FVector4(xBias, yBias, 1, 1);

	FVector biassedDestLocation = destLocation + biasVector;

	navSys->SimpleMoveToLocation(this, biassedDestLocation);
}
