// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "StandardZombie.generated.h"

UCLASS()
class WEZOMBIE_API AStandardZombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStandardZombie();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
	
};
