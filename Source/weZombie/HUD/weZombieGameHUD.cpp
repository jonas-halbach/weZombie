// Fill out your copyright notice in the Description page of Project Settings.

#include "weZombie.h"
#include "weZombieGameHUD.h"
#include "weZombiePlayerController.h"
#include "Kismet/GameplayStatics.h"

AweZombieGameHUD::AweZombieGameHUD()
{
	rectColor = FLinearColor();
	rectColor.R = 0.0f;
	rectColor.G = 1.0f;
	rectColor.B = 0.0f;
	rectColor.A = 0.5f;
}

void AweZombieGameHUD::DrawHUD()
{
	Super::DrawHUD();

	AweZombiePlayerController* playerController = Cast<AweZombiePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (playerController)
	{
		if (playerController->IsMouseDown())
		{
			FIntRect selectionRect;

			playerController->GetSelectionRect(selectionRect);
			

			TArray<APawn *> selectedPawns;

			GetActorsInSelectionRectangle(selectionRect.Min, selectionRect.Max, selectedPawns);
			playerController->AddCurrentSelection(selectedPawns);

			int width = selectionRect.Width();
			int height = selectionRect.Height();

			this->DrawRect(rectColor, selectionRect.Min.X, selectionRect.Min.Y, width, height);
		}
	}
}


