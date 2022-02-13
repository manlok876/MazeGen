// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWall::BeginPlay()
{
	Super::BeginPlay();
}

void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::SetWallSize_Implementation(float NewWidth, float NewHeight, float NewThickness)
{
	SetWallWidth(NewWidth);
	SetWallThickness(NewThickness);
	SetWallHeight(NewHeight);
}

EWallState AWall::GetWallState() const
{
	return State;
}

void AWall::SetWallState(EWallState NewState)
{
	if (State == NewState)
	{
		return;
	}

	State = NewState;

	OnWallStateChanged(NewState);
	if (WallStateChangedDispatcher.IsBound())
	{
		WallStateChangedDispatcher.Broadcast(this, NewState);
	}

	if (WallUpdatedDispatcher.IsBound())
	{
		WallUpdatedDispatcher.Broadcast(this);
	}
}
