// Fill out your copyright notice in the Description page of Project Settings.

#include "weZombie.h"
#include "PlayerControllerStatus.h"

PlayerControllerStatus::~PlayerControllerStatus()
{
}

void PlayerControllerStatus::MouseDown(FVector2D &mousePos)
{
	this->mousePosition = mousePos;
	if (!mouseIsDown)
	{
		this->oldMousePosition = mousePos;
		mouseIsDown = true;
	}
}

void PlayerControllerStatus::MouseMove(FVector2D &mousePos)
{
	this->mousePosition = mousePos;
}

FVector2D PlayerControllerStatus::GetMousePos()
{
	return this->mousePosition;
}

void PlayerControllerStatus::GetMouseRect(FIntRect &selectionRect)
{
	int width = mousePosition.X - oldMousePosition.X;
	int height = mousePosition.Y - oldMousePosition.Y;

	mouseRect.Min.X = oldMousePosition.X;
	mouseRect.Min.Y = oldMousePosition.Y;
	mouseRect.Max.X = oldMousePosition.X + width;
	mouseRect.Max.Y= oldMousePosition.Y + height;

	selectionRect = mouseRect;
}

bool PlayerControllerStatus::IsMouseDown()
{
	return mouseIsDown;
}

void PlayerControllerStatus::SetMousePos(FVector2D &mousePos)
{
	this->mousePosition = mousePos;
}

void PlayerControllerStatus::MouseUp()
{
	mousePosition = FVector2D::ZeroVector;
	oldMousePosition = FVector2D::ZeroVector;
	mouseRect = FIntRect();
	mouseIsDown = false;
}


void PlayerControllerStatus::SetSelectionStatus(ACTION_PARTICIPATION membersWhoParticipate)
{
	this->whoParticipates = membersWhoParticipate;
}

ACTION_PARTICIPATION PlayerControllerStatus::WhoParticipates()
{
	return this->whoParticipates;
}

