// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "PlayerControllerStatus.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "weZombiePlayerController.generated.h"

UCLASS()
class AweZombiePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AweZombiePlayerController();
	bool IsMouseDown();
	void GetSelectionRect(FIntRect &selectionRect);

	void AddCurrentSelection(TArray<APawn *> &currentSelectedPawns);

protected:
	void SetupInputComponent();
	void OnMouseDown();
	void OnMouseUp();
	void OnMouseMove();
	void OnTouchDown(const ETouchIndex::Type FingerIndex, const FVector Location);
	void SetNewMoveDestination(const FVector DestLocation);
	void GetCurrentMousePosition(FVector2D &mousePos);
	virtual void ProcessPlayerInput(float deltaTime, bool isPaused) override;

	PlayerControllerStatus playerControllerStatus;
	ULocalPlayer* LocalPlayer;

	TArray<APawn *> selectedPawns;
};



