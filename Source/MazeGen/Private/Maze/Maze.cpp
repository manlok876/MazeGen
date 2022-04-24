// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze/Maze.h"
#include "Maze/Cell.h"
#include "Maze/Wall.h"

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

FWallCoordinates::FWallCoordinates()
{
	Maze = nullptr;
	WallColumn = WallRow = -1;
	WallDirection = EWallDirection::EWD_NS;
}

FWallCoordinates::FWallCoordinates(AMaze* Maze, int Column, int Row, EWallDirection Direction) : Maze(Maze)
{
	WallColumn = Column;
	WallRow = Row;
	WallDirection = Direction;
}

AMaze::AMaze()
{
	PrimaryActorTick.bCanEverTick = true;

	CellClass = ACell::StaticClass();
	WallClass = AWall::StaticClass();

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

void AMaze::UpdateCell_Implementation(ACell* CellToUpdate)
{
}

void AMaze::HandleWallAdded_Implementation(AWall* NewWall)
{
}

void AMaze::UpdateWall_Implementation(AWall* WallToUpdate)
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

void AMaze::SetSize(int NewWidth, int NewLength)
{
	UpdateMazeSize(NewWidth, NewLength);
}

void AMaze::UpdateMazeSize(int NewWidth, int NewLength)
{
	if (NewWidth == Width && NewLength == Length)
	{
		return;
	}
	int OldWidth = Width;
	int OldLength = Length;
	TArray<ACell*> OldCells = Cells;
	TArray<AWall*> OldWallsNS = WallsNS;
	TArray<AWall*> OldWallsWE = WallsWE;

	Width = NewWidth;
	Length = NewLength;
	Cells.SetNumZeroed(NewWidth * NewLength);
	WallsNS.SetNumZeroed(NewWidth * (NewLength + 1));
	WallsWE.SetNumZeroed((NewWidth + 1) * NewLength);

	TArray<ACell*> NewCells;
	TArray<AWall*> NewWalls;

	TArray<ACell*> RemovedCells;
	TArray<AWall*> RemovedWalls;

	TArray<ACell*> RetainedCells;
	TArray<AWall*> RetainedWalls;

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
				OldCells[OldCellIdx] = nullptr;
				RetainedCells.Add(NewCell);
			}
			else
			{
				NewCell = GetWorld()->SpawnActor<ACell>(CellClass);
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
				OldWallsNS[OldWallIdx] = nullptr;
				RetainedWalls.Add(NewWall);
			}
			else
			{
				NewWall = GetWorld()->SpawnActor<AWall>(WallClass);
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
				OldWallsWE[OldWallIdx] = nullptr;
				RetainedWalls.Add(NewWall);
			}
			else
			{
				NewWall = GetWorld()->SpawnActor<AWall>(WallClass);
				NewWalls.Add(NewWall);
			}

			WallsWE[WallIdx] = NewWall;
		}
	}

	for (ACell* OldCell : OldCells)
	{
		if (OldCell != nullptr)
		{
			RemovedCells.Add(OldCell);
		}
	}

	for (AWall* OldWall : OldWallsNS)
	{
		if (OldWall != nullptr)
		{
			RemovedWalls.Add(OldWall);
		}
	}
	for (AWall* OldWall : OldWallsWE)
	{
		if (OldWall != nullptr)
		{
			RemovedWalls.Add(OldWall);
		}
	}

	// Update old cells/walls positions etc.
	for (ACell* RetainedCell : RetainedCells)
	{
		UpdateCell(RetainedCell);
	}
	for (AWall* RetainedWall : RetainedWalls)
	{
		UpdateWall(RetainedWall);
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

	if (NewCells.Num() > 0 && OnMazeCellsAddedDispatcher.IsBound())
	{
		OnMazeCellsAddedDispatcher.Broadcast(this, NewCells);
	}
	if (RemovedCells.Num() > 0 && OnMazeCellsRemovedDispatcher.IsBound())
	{
		OnMazeCellsRemovedDispatcher.Broadcast(this, RemovedCells);
	}
	if (NewWalls.Num() > 0 && OnMazeWallsAddedDispatcher.IsBound())
	{
		OnMazeWallsAddedDispatcher.Broadcast(this, NewWalls);
	}
	if (RemovedWalls.Num() > 0 && OnMazeWallsRemovedDispatcher.IsBound())
	{
		OnMazeWallsRemovedDispatcher.Broadcast(this, RemovedWalls);
	}
	if (OnMazeSizeChangedDispatcher.IsBound())
	{
		OnMazeSizeChangedDispatcher.Broadcast(this,
			FIntPoint(OldWidth, OldLength), FIntPoint(NewWidth, NewLength));
	}
	if (OnMazeUpdatedDispatcher.IsBound())
	{
		OnMazeUpdatedDispatcher.Broadcast(this);
	}

	for (AWall* OldWall : RemovedWalls)
	{
		if (IsValid(OldWall))
		{
			OldWall->Destroy();
		}
	}
	for (ACell* OldCell : RemovedCells)
	{
		if (IsValid(OldCell))
		{
			OldCell->Destroy();
		}
	}

}

bool AMaze::IsValidCell(int Column, int Row) const
{
	return Cells.IsValidIndex(GetCellIndex1D(Column, Row));
}

bool AMaze::ContainsCell(ACell* Cell) const
{
	if (!IsValid(Cell))
	{
		return nullptr;
	}

	return Cells.Contains(Cell);
}

ACell* AMaze::GetCell(int Column, int Row) const
{
	int CellIdx1D = GetCellIndex1D(Column, Row);
	if (!Cells.IsValidIndex(CellIdx1D))
	{
		return nullptr;
	}
	return Cells[CellIdx1D];
}

ACell* AMaze::GetCellByCoords(const FCellCoordinates& Coordinates) const
{
	if (Coordinates.Maze != this)
	{
		return nullptr;
	}

	return GetCell(Coordinates.CellColumn, Coordinates.CellRow);
}

TArray<ACell*> AMaze::GetAllCells() const
{
	return Cells;
}

FCellCoordinates AMaze::GetCellCoordinates(ACell* Cell)
{
	int CellIdx1D = Cells.Find(Cell);
	if (!Cells.IsValidIndex(CellIdx1D))
	{
		return FCellCoordinates();
	}

	int CellRow, CellColumn;
	GetCellIndex2D(CellIdx1D, CellColumn, CellRow);
	check(CellColumn >= 0 && CellRow >= 0);

	return FCellCoordinates(this, CellColumn, CellRow);
}

bool AMaze::IsValidWall(int CellColumn, int CellRow, EMazeSide WallSide) const
{
	int WallColumn = CellColumn;
	int WallRow = CellRow;

	int WallIndex1D;
	switch (WallSide)
	{
	case EMazeSide::EMS_South:
		++WallRow;
	case EMazeSide::EMS_North:
		WallIndex1D = GetNSWallIndex1D(WallColumn, WallRow);
		if (WallsNS.IsValidIndex(WallIndex1D))
		{
			return true;
		}
		break;

	case EMazeSide::EMS_East:
		++WallColumn;
	case EMazeSide::EMS_West:
		WallIndex1D = GetWEWallIndex1D(WallColumn, WallRow);
		if (WallsWE.IsValidIndex(WallIndex1D))
		{
			return true;
		}
		break;
	}

	return false;
}

bool AMaze::ContainsWall(AWall* Wall) const
{
	if (!IsValid(Wall))
	{
		return nullptr;
	}

	return WallsNS.Contains(Wall) || WallsWE.Contains(Wall);
}

AWall* AMaze::GetWall(int CellColumn, int CellRow, EMazeSide WallSide) const
{
	int WallX = CellColumn;
	int WallY = CellRow;
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

AWall* AMaze::GetWallByCoords(const FWallCoordinates& Coordinates) const
{
	if (Coordinates.Maze != this)
	{
		return nullptr;
	}

	AWall* Result = nullptr;
	int WallIndex1D;
	switch (Coordinates.WallDirection)
	{
	case EWallDirection::EWD_NS:
		WallIndex1D = GetNSWallIndex1D(Coordinates.WallColumn, Coordinates.WallRow);
		if (WallsNS.IsValidIndex(WallIndex1D))
		{
			Result = WallsNS[WallIndex1D];
		}
		break;

	case EWallDirection::EWD_WE:
		WallIndex1D = GetWEWallIndex1D(Coordinates.WallColumn, Coordinates.WallRow);
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

TArray<AWall*> AMaze::GetWallsNS() const
{
	return WallsNS;
}

TArray<AWall*> AMaze::GetWallsWE() const
{
	return WallsWE;
}

FWallCoordinates AMaze::GetWallCoordinates(AWall* Wall)
{
	int NSWallIdx1D = WallsNS.Find(Wall);
	int WEWallIdx1D = WallsWE.Find(Wall);

	int WallRow, WallColumn;
	EWallDirection WallDirection;
	if (WallsNS.IsValidIndex(NSWallIdx1D))
	{
		WallDirection = EWallDirection::EWD_NS;
		GetWallIndex2D(NSWallIdx1D, WallDirection, WallColumn, WallRow);
		check(WallColumn >= 0 && WallRow >= 0);
	}
	else if (WallsWE.IsValidIndex(WEWallIdx1D))
	{
		WallDirection = EWallDirection::EWD_WE;
		GetWallIndex2D(WEWallIdx1D, WallDirection, WallColumn, WallRow);
		check(WallColumn >= 0 && WallRow >= 0);
	}
	else
	{
		return FWallCoordinates();
	}

	return FWallCoordinates(this, WallColumn, WallRow, WallDirection);
}

int AMaze::GetNSWallIndex1D(int Column, int Row) const
{
	return Index1DFromIndex2D(Column, Width, Row, Length + 1);
}

int AMaze::GetWEWallIndex1D(int Column, int Row) const
{
	return Index1DFromIndex2D(Column, Width + 1, Row, Length);
}

void AMaze::GetWallIndex2D(int Idx1D, EWallDirection WallDir, int& Column, int& Row) const
{
	switch (WallDir)
	{
	case EWallDirection::EWD_NS:
		Index2DFromIndex1D(Idx1D, Width, Length + 1, Column, Row);
		break;
	case EWallDirection::EWD_WE:
		Index2DFromIndex1D(Idx1D, Width + 1, Length, Column, Row);
		break;
	}
}

int AMaze::GetCellIndex1D(int Column, int Row) const
{
	return Index1DFromIndex2D(Column, Width, Row, Length);
}

int AMaze::Index1DFromIndex2D(int X, int SizeX, int Y, int SizeY)
{
	if (X < 0      || Y < 0     ||
		X >= SizeX || Y >= SizeY)
	{
		return -1;
	}
	return Y * SizeX + X;
}

void AMaze::GetCellIndex2D(int Idx1D, int& Column, int& Row) const
{
	Index2DFromIndex1D(Idx1D, Width, Length, Column, Row);
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
