// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "weZombiePlayerController.generated.h"

UCLASS()
class AweZombiePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AweZombiePlayerController();

protected:
	void SetupInputComponent();
	void OnMouseDown();
	void OnMouseUp();
	void OnTouchDown(const ETouchIndex::Type FingerIndex, const FVector Location);
	void SetNewMoveDestination(const FVector DestLocation);

};



