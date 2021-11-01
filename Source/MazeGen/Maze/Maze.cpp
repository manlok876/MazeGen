// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze.h"
#include "Cell.h"
#include "Wall.h"

AMaze::AMaze()
{
	PrimaryActorTick.bCanEverTick = true;

	bInitialized = false;
	Width = 10;
	Length = 10;
}

void AMaze::BeginPlay()
{
	Super::BeginPlay();

}

void AMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMaze::Init_Implementation(int W, int L)
{
	Init_CreateCells();
	Init_CreateWalls();

	bInitialized = false;
}

void AMaze::Init_CreateCells()
{
	Cells.SetNum(Width * Length);
	for (int i = 0; i < Width * Length; ++i)
	{
		ACell* NewCell = GetWorld()->SpawnActor<ACell>();
		Cells[i] = NewCell;
	}
}

void AMaze::Init_CreateWalls()
{
	WallsNS.SetNum(Width * (Length + 1));
	for (int i = 0; i < Width * (Length + 1); ++i)
	{
		AWall* NewWall = GetWorld()->SpawnActor<AWall>();
		WallsNS[i] = NewWall;
	}
	WallsWE.SetNum((Width + 1) * Length);
	for (int i = 0; i < (Width + 1) * Length; ++i)
	{
		AWall* NewWall = GetWorld()->SpawnActor<AWall>();
		WallsWE[i] = NewWall;
	}
}

void AMaze::AddCell(int X, int Y)
{
}

void AMaze::HandleCellAdded_Implementation(ACell* NewCell)
{
}

void AMaze::AddWall(int X, int Y)
{
}

void AMaze::HandleWallAdded_Implementation(AWall* NewWall)
{
}

int AMaze::GetLength() const
{
	return 0;
}

void AMaze::SetLength(int NewLength)
{
}

int AMaze::GetWidth() const
{
	return 0;
}

void AMaze::SetWidth(int NewWidth)
{
}
