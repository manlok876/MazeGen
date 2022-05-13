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

	const FMazeSize MazeSize = TargetMaze->GetMazeSize();

	TArray<ACell*> CorridorCells;
	CorridorCells.Reserve(FMath::Max(MazeSize.Columns, MazeSize.Rows));

	// Get vertical corridors
	for (int ColIdx = 0; ColIdx < MazeSize.Columns; ++ColIdx)
	{
		CorridorCells.Empty();

		for (int RowIdx = 0; RowIdx < MazeSize.Rows; ++RowIdx)
		{
			ACell* CurrentCell = TargetMaze->GetCell(ColIdx, RowIdx);
			if (IsValid(CurrentCell))
			{
				CorridorCells.Add(CurrentCell);
			}

			const AWall* Wall = TargetMaze->GetWall(ColIdx, RowIdx, EMazeSide::EMS_South);
			if (IsValid(Wall) && Wall->IsBlocking())
			{
				int CorridorLength = CorridorCells.Num();
				for (ACell* Cell : CorridorCells)
				{
					CacheMetricValue(Cell, CorridorLength);
				}
				CorridorCells.Empty();
			}
		}

		int CorridorLength = CorridorCells.Num();
		for (ACell* Cell : CorridorCells)
		{
			CacheMetricValue(Cell, CorridorLength);
		}
	}

	// Get horizontal corridors
	for (int RowIdx = 0; RowIdx < MazeSize.Rows; ++RowIdx)
	{
		CorridorCells.Empty();

		for (int ColIdx = 0; ColIdx < MazeSize.Columns; ++ColIdx)
		{
			ACell* CurrentCell = TargetMaze->GetCell(ColIdx, RowIdx);
			if (IsValid(CurrentCell))
			{
				CorridorCells.Add(CurrentCell);
			}

			const AWall* Wall = TargetMaze->GetWall(ColIdx, RowIdx, EMazeSide::EMS_East);
			if (IsValid(Wall) && Wall->IsBlocking())
			{
				float CorridorLength = CorridorCells.Num();
				for (ACell* Cell : CorridorCells)
				{
					CacheMetricValue(Cell,
						FMath::Max(CorridorLength, GetMetricForCell_Implementation(Cell)));
				}
				CorridorCells.Empty();
			}
		}

		float CorridorLength = CorridorCells.Num();
		for (ACell* Cell : CorridorCells)
		{
			CacheMetricValue(Cell,
				FMath::Max(CorridorLength, GetMetricForCell_Implementation(Cell)));
		}
	}
}
