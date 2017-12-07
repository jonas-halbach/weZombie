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
	bool IsMouseDown();
	void GetSelectionRect(FIntRect &selectionRect);
	void SelectPawns(TArray<APawn *> &currentSelectedPawns);


protected:
	AweZombiePlayerController();
	void SetupInputComponent();
	void OnMouseDown();
	void OnMouseUp();
	void OnMouseMove();
	void OnRightMouseDown();
	void OnTouchDown(const ETouchIndex::Type FingerIndex, const FVector Location);

	void SetNewMoveDestination(const FVector DestLocation);
	void SetNewMoveDestinationForSelectedPawns(const FVector DestLocation);
	void SetNewMoveDestinationForMyPawn(const FVector DestLocation);
	void GetCurrentMousePosition(FVector2D &mousePos);
	void AddCurrentSelection(TArray<APawn *> &currentSelectedPawns, bool add);
	void SetPlayerSelectionState1();
	void UnsetPlayerSelectionState1();
	void SetPlayerSelectionState2();
	void UnsetPlayerSelectionState2();
	void SetPlayerSelectionState3();
	void UnsetPlayerSelectionState3();

	virtual void ProcessPlayerInput(float deltaTime, bool isPaused) override;

	PlayerControllerStatus playerControllerStatus;
	ULocalPlayer* LocalPlayer;

	TArray<APawn *> selectedPawns;
};

