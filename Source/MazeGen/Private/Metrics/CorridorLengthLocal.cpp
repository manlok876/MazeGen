// Fill out your copyright notice in the Description page of Project Settings.


#include "Metrics/CorridorLengthLocal.h"
#include "Maze/Maze.h"
#include "Maze/Cell.h"

void UCorridorLengthLocal::RunMetricForMaze_Implementation(AMaze* TargetMaze)
{
	if (!IsValid(TargetMaze))
	{
		return;
	}

	for (ACell* Cell : TargetMaze->GetAllCells())
	{
		CachedMetricValues.Remove(Cell);
	}

	for (ACell* Cell : TargetMaze->GetAllCells())
	{
		// TODO: check cell state

		FCellCoordinates CellCoordinates = TargetMaze->GetCellCoordinates(Cell);
		check(CellCoordinates.CellRow >= 0 && CellCoordinates.CellColumn >= 0);

		int VerticalCorridorLength = 1;

		int TmpCellRow = CellCoordinates.CellRow;
		int TmpCellColumn = CellCoordinates.CellColumn;
		

		int HorizontalCorridorLength = 1;


		// Get vertical corridor
		
		// Get horizontal corridor
	}
}
