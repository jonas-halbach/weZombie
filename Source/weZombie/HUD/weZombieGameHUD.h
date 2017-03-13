// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "weZombieGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class WEZOMBIE_API AweZombieGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AweZombieGameHUD();
	virtual void DrawHUD() override;

	
private:
	FLinearColor rectColor;
	
};
