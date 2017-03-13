// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "weZombie.h"
#include "weZombiePlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "weZombieCharacter.h"

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

	InputComponent->BindAction("SetDestination", EInputEvent::IE_Pressed, this, &AweZombiePlayerController::OnMouseDown);
	InputComponent->BindAction("SetDestination", EInputEvent::IE_Released, this, &AweZombiePlayerController::OnMouseUp);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AweZombiePlayerController::OnTouchDown);

}

void AweZombiePlayerController::OnMouseDown()
{
	/////
	///// Something like the following goes here:
	///// AHUD.GetActorsInSelectionRectangle
	/////
	///// maybe check:  https://www.youtube.com/watch?v=yCqsbXS9yRg
	///// and: https://wiki.unrealengine.com/HUD,_Canvas,_Code_Sample_of_800%2B_Lines,_Create_Buttons_%26_Draw_Materials
	/////
	
	//FVector MousePos;
	/*FVector MouseDir;

	float x;
	float y;

	bool success = this->DeprojectMousePositionToWorld(MousePos, MouseDir);

	if (success)
	{
		this->SetActorLocation(MousePos, false);
	}
	*/


	FVector2D mousePos;
	GetCurrentMousePosition(mousePos);
	playerControllerStatus.MouseDown(mousePos);

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		this->SetNewMoveDestination(Hit.ImpactPoint);
	}

	//UE_LOG("MyLog", Warning, TEXT("MyCharacter's Health is %f"), MyCharacter->Health);

	//ClientMessage("MousePos: " + FString::SanitizeFloat(MousePos.X) + ", " + FString::SanitizeFloat(MousePos.Y));
	//TCHAR[] message = TCHAR[1000];

	//UE_LOG(LogClass, Warning, TEXT("My Message"));
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

void AweZombiePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	for(int i = 0; i < selectedPawns.Num(); i++)
	{
		TArray<UActorComponent*> characterMovement;
		selectedPawns[i]->GetComponents(characterMovement);
		if (characterMovement.Num() > 0)
		{
			///!!!!Attention!!!! This will not work this way, because playercontroller just controls one pawn!!!!!!
			UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
			float const Distance = FVector::Dist(DestLocation, selectedPawns[i]->GetActorLocation());

			// We need to issue move command only if far enough in order for walk animation to play correctly
			if (NavSys && (Distance > 120.0f))
			{
				NavSys->SimpleMoveToLocation(this, DestLocation);
			}
		}
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

void AweZombiePlayerController::AddCurrentSelection(TArray<APawn *> &currentSelection)
{
	selectedPawns = currentSelection;
}