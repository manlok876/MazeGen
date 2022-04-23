// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze/Cell.h"

ACell::ACell()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACell::BeginPlay()
{
	Super::BeginPlay();

}

void ACell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ECellState ACell::GetCellState() const
{
	return State;
}

void ACell::SetCellState(ECellState NewState)
{
	if (State == NewState)
	{
		return;
	}

	State = NewState;

	OnCellStateChanged(NewState);
	if (CellStateChangedDispatcher.IsBound())
	{
		CellStateChangedDispatcher.Broadcast(this, NewState);
	}

	if (CellUpdatedDispatcher.IsBound())
	{
		CellUpdatedDispatcher.Broadcast(this);
	}
}
