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
	UE_LOG(LogClass, Warning, TEXT("Create PlayerController"));
}


void AweZombiePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", EInputEvent::IE_Pressed, this, &AweZombiePlayerController::OnMouseDown);
	InputComponent->BindAction("SetDestination", EInputEvent::IE_Released, this, &AweZombiePlayerController::OnMouseUp);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AweZombiePlayerController::OnTouchDown);

}

void AweZombiePlayerController::OnMouseDown()
{
	/*FVector MousePos;
	FVector2D MousePosition;
	FVector MouseDir;

	float x;
	float y;

	bool success = this->DeprojectMousePositionToWorld(MousePos, MouseDir);

	if (success)
	{
		this->SetActorLocation(MousePos, false);
	}
	*/
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

void AweZombiePlayerController::OnMouseUp()
{

}

void AweZombiePlayerController::OnTouchDown(const ETouchIndex::Type FingerIndex, const FVector Location)
{

}

void AweZombiePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}