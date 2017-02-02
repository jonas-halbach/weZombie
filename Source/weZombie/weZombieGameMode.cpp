// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "weZombie.h"
#include "weZombieGameMode.h"
#include "weZombiePlayerController.h"
#include "weZombieCharacter.h"

AweZombieGameMode::AweZombieGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AweZombiePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}