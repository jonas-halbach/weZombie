// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
UENUM(BlueprintType)
enum class ACTION_PARTICIPATION : uint8
{
	ME,
	SELECTION,
	BOTH
};

/**
 * 
 */
class WEZOMBIE_API PlayerControllerStatus
{
public:
	~PlayerControllerStatus();

	void MouseDown(FVector2D &mousePos);
	FVector2D GetMousePos();
	void GetMouseRect(FIntRect &selectionRect);
	bool IsMouseDown();
	void SetMousePos(FVector2D &mousePos);
	void MouseUp();
	void MouseMove(FVector2D &mousePos);
	void SetSelectionStatus(ACTION_PARTICIPATION whoParticipates);
	ACTION_PARTICIPATION WhoParticipates();
	bool GetShallAddToSelection() { return shallAdd; }
	void SetShallAddToSelection(bool add) { this->shallAdd = add; }

private:

	bool mouseIsDown = false;
	bool shallAdd = false;
	ACTION_PARTICIPATION whoParticipates = ACTION_PARTICIPATION::ME;
	
	FIntRect mouseRect;
	FVector2D mousePosition;
	FVector2D oldMousePosition;
	
};

