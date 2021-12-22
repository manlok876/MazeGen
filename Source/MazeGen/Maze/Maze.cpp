// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze.h"
#include "Cell.h"
#include "Wall.h"

FCellCoordinates::FCellCoordinates()
{
	Maze = nullptr;
	CellColumn = CellRow = -1;
}

FCellCoordinates::FCellCoordinates(AMaze* Maze, int Column, int Row) : Maze(Maze)
{
	CellColumn = Column;
	CellRow = Row;
}

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

	Init(Width, Length);
}

void AMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMaze::Init_Implementation(int W, int L)
{
	Width = 0;
	Length = 0;

	UpdateMazeSize(W, L);

	bInitialized = true;
}

void AMaze::HandleCellAdded_Implementation(ACell* NewCell)
{
}

void AMaze::HandleWallAdded_Implementation(AWall* NewWall)
{
}

int AMaze::GetLength() const
{
	return Length;
}

void AMaze::SetLength(int NewLength)
{
	UpdateMazeSize(Width, NewLength);
}

int AMaze::GetWidth() const
{
	return Width;
}

void AMaze::SetWidth(int NewWidth)
{
	UpdateMazeSize(NewWidth, Length);
}

void AMaze::UpdateMazeSize(int NewWidth, int NewLength)
{
	int OldWidth = Width;
	int OldLength = Length;
	const TArray<ACell*> OldCells = Cells;
	const TArray<AWall*> OldWallsNS = WallsNS;
	const TArray<AWall*> OldWallsWE = WallsWE;

	Width = NewWidth;
	Length = NewLength;
	Cells.SetNumZeroed(NewWidth * NewLength);
	WallsNS.SetNumZeroed(NewWidth * (NewLength + 1));
	WallsWE.SetNumZeroed((NewWidth + 1) * NewLength);

	TArray<ACell*> NewCells;
	TArray<AWall*> NewWalls;

	for (int CellX = 0; CellX < NewWidth; ++CellX)
	{
		for (int CellY = 0; CellY < NewLength; ++CellY)
		{
			const int CellIdx = GetCellIndex1D(CellX, CellY);
			check(Cells.IsValidIndex(CellIdx));
			ACell* NewCell = nullptr;

			if (CellX < OldWidth && CellY < OldLength)
			{
				const int OldCellIdx =
					Index1DFromIndex2D(CellX, OldWidth, CellY, OldLength);
				check(OldCells.IsValidIndex(OldCellIdx));
				NewCell = OldCells[OldCellIdx];
			}
			else
			{
				NewCell = GetWorld()->SpawnActor<ACell>(ACell::StaticClass());
				NewCells.Add(NewCell);
			}

			Cells[CellIdx] = NewCell;
		}
	}

	// N-S walls
	for (int WallX = 0; WallX < NewWidth; ++WallX)
	{
		for (int WallY = 0; WallY < NewLength + 1; ++WallY)
		{
			const int WallIdx = GetNSWallIndex1D(WallX, WallY);
			check(WallsNS.IsValidIndex(WallIdx));
			AWall* NewWall = nullptr;

			if (WallX < OldWidth && WallY < OldLength + 1)
			{
				const int OldWallIdx =
					Index1DFromIndex2D(WallX, OldWidth, WallY, OldLength + 1);
				check(OldWallsNS.IsValidIndex(OldWallIdx));
				NewWall = OldWallsNS[OldWallIdx];
			}
			else
			{
				NewWall = GetWorld()->SpawnActor<AWall>(AWall::StaticClass());
				NewWalls.Add(NewWall);
			}

			WallsNS[WallIdx] = NewWall;
		}
	}
	// W-E walls
	for (int WallX = 0; WallX < NewWidth + 1; ++WallX)
	{
		for (int WallY = 0; WallY < NewLength; ++WallY)
		{
			const int WallIdx = GetWEWallIndex1D(WallX, WallY);
			check(WallsWE.IsValidIndex(WallIdx));

			AWall* NewWall = nullptr;
			if (WallX < OldWidth + 1 && WallY < OldLength)
			{
				const int OldWallIdx =
					Index1DFromIndex2D(WallX, OldWidth + 1, WallY, OldLength);
				check(OldWallsWE.IsValidIndex(OldWallIdx));
				NewWall = OldWallsWE[OldWallIdx];
			}
			else
			{
				NewWall = GetWorld()->SpawnActor<AWall>(AWall::StaticClass());
				NewWalls.Add(NewWall);
			}

			WallsWE[WallIdx] = NewWall;
		}
	}

	// Handle new elements being added
	for (ACell* NewCell : NewCells)
	{
		HandleCellAdded(NewCell);
	}
	for (AWall* NewWall: NewWalls)
	{
		HandleWallAdded(NewWall);
	}
}

bool AMaze::IsValidCell(int X, int Y) const
{
	return Cells.IsValidIndex(GetCellIndex1D(X, Y));
}

ACell* AMaze::GetCell(int X, int Y) const
{
	int CellIdx1D = GetCellIndex1D(X, Y);
	if (!Cells.IsValidIndex(CellIdx1D))
	{
		return nullptr;
	}
	return Cells[CellIdx1D];
}

TArray<ACell*> AMaze::GetAllCells() const
{
	return TArray<ACell*>(Cells);
}

bool AMaze::IsValidWall(int CellX, int CellY, EMazeSide WallSide) const
{
	int WallX = CellX;
	int WallY = CellY;

	int WallIndex1D;
	switch (WallSide)
	{
	case EMazeSide::EMS_South:
		++WallY;
	case EMazeSide::EMS_North:
		WallIndex1D = GetNSWallIndex1D(WallX, WallY);
		if (WallsNS.IsValidIndex(WallIndex1D))
		{
			return true;
		}
		break;

	case EMazeSide::EMS_East:
		++WallX;
	case EMazeSide::EMS_West:
		WallIndex1D = GetWEWallIndex1D(WallX, WallY);
		if (WallsWE.IsValidIndex(WallIndex1D))
		{
			return true;
		}
		break;
	}

	return false;
}

AWall* AMaze::GetWall(int CellX, int CellY, EMazeSide WallSide) const
{
	int WallX = CellX;
	int WallY = CellY;
	AWall* Result = nullptr;

	int WallIndex1D;
	switch (WallSide)
	{
	case EMazeSide::EMS_South:
		++WallY;
	case EMazeSide::EMS_North:
		WallIndex1D = GetNSWallIndex1D(WallX, WallY);
		if (WallsNS.IsValidIndex(WallIndex1D))
		{
			Result = WallsNS[WallIndex1D];
		}
		break;

	case EMazeSide::EMS_East:
		++WallX;
	case EMazeSide::EMS_West:
		WallIndex1D = GetWEWallIndex1D(WallX, WallY);
		if (WallsWE.IsValidIndex(WallIndex1D))
		{
			Result = WallsWE[WallIndex1D];
		}
		break;
	}

	return Result;
}

TArray<AWall*> AMaze::GetAllWalls() const
{
	TArray<AWall*> Result(WallsNS);
	Result.Append(WallsWE);
	return Result;
}

int AMaze::GetNSWallIndex1D(int X, int Y) const
{
	return Index1DFromIndex2D(X, Width, Y, Length + 1);
}

int AMaze::GetWEWallIndex1D(int X, int Y) const
{
	return Index1DFromIndex2D(X, Width + 1, Y, Length);
}

int AMaze::GetCellIndex1D(int X, int Y) const
{
	return Index1DFromIndex2D(X, Width, Y, Length);
}

int AMaze::Index1DFromIndex2D(int X, int SizeX, int Y, int SizeY)
{
	if (X >= SizeX || Y >= SizeY)
	{
		return -1;
	}
	return X * SizeX + Y;
}

void AMaze::GetCellIndex2D(int Idx1D, int& X, int& Y) const
{
	Index2DFromIndex1D(Idx1D, Width, Length, X, Y);
}

void AMaze::Index2DFromIndex1D(int Idx1D, int SizeX, int SizeY, int& X, int& Y)
{
	if (SizeX < 1 || SizeY < 1 ||
		Idx1D < 0 || Idx1D > SizeX * SizeY)
	{
		X = Y = -1;
		return;
	}
	X = Idx1D % SizeX;
	Y = Idx1D / SizeX;
}
