// Fill out your copyright notice in the Description page of Project Settings.

#include "weZombie.h"
#include "StandardZombiePlayerController.h"
#include "StandardZombie.h"

AStandardZombiePlayerController::AStandardZombiePlayerController(class FObjectInitializer const & ObjInit) : Super(ObjInit)
{
	bWantsPlayerState = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AStandardZombiePlayerController::Possess(class APawn *inPawn)
{
	Super::Possess(inPawn);
	AStandardZombie *zombie = Cast<AStandardZombie>(inPawn);
}

void AStandardZombiePlayerController::BeginInactiveState()
{
	Super::BeginInactiveState();
}


