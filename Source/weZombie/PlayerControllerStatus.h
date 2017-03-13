// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class WEZOMBIE_API PlayerControllerStatus
{
public:
	PlayerControllerStatus();
	~PlayerControllerStatus();

	void MouseDown(FVector2D &mousePos);
	FVector2D GetMousePos();
	void GetMouseRect(FIntRect &selectionRect);
	bool IsMouseDown();
	void SetMousePos(FVector2D &mousePos);
	void MouseUp();
	void MouseMove(FVector2D &mousePos);

private:
	bool mouseIsDown = false;
	FIntRect mouseRect;
	FVector2D mousePosition;
	FVector2D oldMousePosition;
};
