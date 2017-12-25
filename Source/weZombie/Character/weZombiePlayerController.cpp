// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "weZombie.h"
#include "weZombiePlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "weZombieCharacter.h"
#include "Character/StandardZombiePlayerController.h"

//UPROPERTY(Category = "Visuals")
//AActor mouseSelectionBox;

AweZombiePlayerController::AweZombiePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	playerControllerStatus = PlayerControllerStatus();
	selectedPawns = TArray<APawn *>();

	UE_LOG(LogClass, Warning, TEXT("Create PlayerController"));
}

void AweZombiePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	LocalPlayer = Cast<ULocalPlayer>(Player);

	InputComponent->BindAction("SelectActors", EInputEvent::IE_Pressed, this, &AweZombiePlayerController::OnMouseDown);
	InputComponent->BindAction("SelectActors", EInputEvent::IE_Released, this, &AweZombiePlayerController::OnMouseUp);

	InputComponent->BindAction("SetDestination", EInputEvent::IE_Pressed, this, &AweZombiePlayerController::OnRightMouseDown);

	InputComponent->BindAction("SelectionState1", EInputEvent::IE_Pressed, this, &AweZombiePlayerController::SetPlayerSelectionState1);
	InputComponent->BindAction("SelectionState1", EInputEvent::IE_Released, this, &AweZombiePlayerController::UnsetPlayerSelectionState1);

	InputComponent->BindAction("SelectionState2", EInputEvent::IE_Pressed, this, &AweZombiePlayerController::SetPlayerSelectionState2);
	InputComponent->BindAction("SelectionState2", EInputEvent::IE_Released, this, &AweZombiePlayerController::UnsetPlayerSelectionState2);

	InputComponent->BindAction("SelectionState3", EInputEvent::IE_Pressed, this, &AweZombiePlayerController::SetPlayerSelectionState3);
	InputComponent->BindAction("SelectionState3", EInputEvent::IE_Released, this, &AweZombiePlayerController::UnsetPlayerSelectionState3);
	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AweZombiePlayerController::OnTouchDown);
}

void AweZombiePlayerController::OnMouseDown()
{
	FVector2D mousePos;
	GetCurrentMousePosition(mousePos);
	playerControllerStatus.MouseDown(mousePos);

	UE_LOG(LogClass, Warning, TEXT("My message from new Mouse_PlayerController"));
}

void AweZombiePlayerController::OnMouseMove()
{
	FVector2D mousePos;
	GetCurrentMousePosition(mousePos);
	playerControllerStatus.MouseMove(mousePos);
}

void AweZombiePlayerController::OnMouseUp()
{
	playerControllerStatus.MouseUp();
}

void AweZombiePlayerController::OnTouchDown(const ETouchIndex::Type FingerIndex, const FVector Location)
{

}

void AweZombiePlayerController::OnRightMouseDown()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		this->SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AweZombiePlayerController::SetNewMoveDestination(const FVector destLocation)
{
	if (playerControllerStatus.WhoParticipates() == ACTION_PARTICIPATION::ME)
	{
		SetNewMoveDestinationForMyPawn(destLocation);
	}
	else if (playerControllerStatus.WhoParticipates() == ACTION_PARTICIPATION::SELECTION)
	{
		SetNewMoveDestinationForSelectedPawns(destLocation);
	}
	else
	{
		SetNewMoveDestinationForMyPawn(destLocation);
		SetNewMoveDestinationForSelectedPawns(destLocation);
	}
}

void AweZombiePlayerController::SetNewMoveDestinationForSelectedPawns(const FVector destLocation)
{
	UNavigationSystem const *navSys = GetWorld()->GetNavigationSystem();
	for (int i = 0; i < selectedPawns.Num(); i++)
	{
		float const Distance = FVector::Dist(destLocation, selectedPawns[i]->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (navSys && (Distance > 120.0f))
		{
			AStandardZombiePlayerController* controller = Cast<AStandardZombiePlayerController>(selectedPawns[i]->GetController());
			if (controller != NULL)
			{
				controller->MoveToLocation(destLocation, navSys);
				//navSys->SimpleMoveToLocation(controller, destLocation);
			}
		}
	}
}


void AweZombiePlayerController::SetNewMoveDestinationForMyPawn(const FVector destLocation)
{
	UNavigationSystem const*navSys = GetWorld()->GetNavigationSystem();
	APawn *const pawn = GetPawn();
	float const distance = FVector::Dist(destLocation, pawn->GetActorLocation());

	// We need to issue move command only if far enough in order for walk animation to play correctly
	if (navSys && (distance > 120.0f))
	{
		navSys->SimpleMoveToLocation(this, destLocation);
	}
}

bool AweZombiePlayerController::IsMouseDown()
{
	return playerControllerStatus.IsMouseDown();
}

void AweZombiePlayerController::ProcessPlayerInput(float deltaTime, bool gamePaused)
{
	Super::ProcessPlayerInput(deltaTime, gamePaused);
	if (!gamePaused)
	{
		OnMouseMove();
	}
}

void AweZombiePlayerController::GetSelectionRect(FIntRect &selectionRect)
{
	playerControllerStatus.GetMouseRect(selectionRect);
}

void AweZombiePlayerController::GetCurrentMousePosition(FVector2D &mousePos)
{
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FVector2D MousePosition;
		if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
		{
			mousePos = MousePosition;
		}
	}
}

void AweZombiePlayerController::AddCurrentSelection(TArray<APawn *> &currentSelection, bool add)
{
	if (add)
	{
		selectedPawns.Append(currentSelection);
	}
	else
	{
		selectedPawns = currentSelection;
	}
}

void AweZombiePlayerController::SelectPawns(TArray<APawn *> &currentSelection)
{
	this->AddCurrentSelection(currentSelection, playerControllerStatus.GetShallAddToSelection());
}

void AweZombiePlayerController::SetPlayerSelectionState1()
{
	playerControllerStatus.SetSelectionStatus(ACTION_PARTICIPATION::ME);
}

void AweZombiePlayerController::UnsetPlayerSelectionState1()
{
	//playerControllerStatus.SetShallAddPawnsToSelectionStatus(false);
}

void AweZombiePlayerController::SetPlayerSelectionState2()
{
	playerControllerStatus.SetSelectionStatus(ACTION_PARTICIPATION::SELECTION);
}

void AweZombiePlayerController::UnsetPlayerSelectionState2()
{
	//playerControllerStatus.SetShallAddPawnsToSelectionStatus(false);
}

void AweZombiePlayerController::SetPlayerSelectionState3()
{
	playerControllerStatus.SetSelectionStatus(ACTION_PARTICIPATION::BOTH);
}

void AweZombiePlayerController::UnsetPlayerSelectionState3()
{
	//playerControllerStatus.SetShallAddPawnsToSelectionStatus(false);
}