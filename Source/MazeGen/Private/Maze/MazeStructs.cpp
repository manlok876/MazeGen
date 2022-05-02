// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze/MazeStructs.h"
#include "Maze/Maze.h"

FCellWalls::FCellWalls()
{
	Cell = nullptr;
	North = East = South = West = nullptr;
}

FCellWalls::FCellWalls(ACell* InCell, AWall* NorthWall, AWall* EastWall, AWall* SouthWall, AWall* WestWall)
{
	Cell = InCell;
	North = NorthWall;
	East = EastWall;
	South = SouthWall;
	West = WestWall;
}

FMazeData::FMazeData()
{
	Width = Length = 0;
}

FMazeData::FMazeData(const AMaze* Maze)
{
	Width = Maze->GetWidth();
	Length = Maze->GetLength();

	CellsInfo.Reserve(Width * Length);
	for (const ACell* Cell : Maze->GetAllCells())
	{
		CellsInfo.Add(Cell->GetCellState());
	}

	NSWallsInfo.Reserve(Width * (Length + 1));
	for (const AWall* Wall : Maze->GetWallsNS())
	{
		NSWallsInfo.Add(Wall->GetWallState());
	}

	WEWallsInfo.Reserve((Width + 1) * Length);
	for (const AWall* Wall : Maze->GetWallsWE())
	{
		WEWallsInfo.Add(Wall->GetWallState());
	}
}
