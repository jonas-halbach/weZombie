// Fill out your copyright notice in the Description page of Project Settings.

#include "weZombie.h"
#include "StandardZombie.h"
#include "StandardZombiePlayerController.h"


// Sets default values
AStandardZombie::AStandardZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AStandardZombiePlayerController::StaticClass();
}

// Called when the game starts or when spawned
void AStandardZombie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStandardZombie::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AStandardZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

