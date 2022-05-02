// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinding/MazeWalker.h"

AMaze* UMazeWalker::GetCurrentMaze() const
{
	return CurrentMaze;
}

ACell* UMazeWalker::GetCurrentCell() const
{
	return CurrentCell;
}

bool UMazeWalker::TryStep(EMazeSide Direction)
{
	return false;
}

ACell* UMazeWalker::TryStepBack()
{
	if (PreviousSteps.Num() < 1)
	{
		return nullptr;
	}

	CurrentCell = PreviousSteps.Pop();
	return CurrentCell;
}

bool UMazeWalker::TryGoTo(ACell* Destination)
{
	return false;
}

bool UMazeWalker::TryGoToCoords(const FCellCoordinates& Destination)
{
	return false;
}

bool UMazeWalker::TeleportToMaze(AMaze* NewMaze, ACell* StartingCell)
{
	if (!IsValid(NewMaze))
	{
		return false;
	}

	if (!IsValid(StartingCell))
	{
		return false;
	}

	if (!NewMaze->ContainsCell(StartingCell))
	{
		return false;
	}

	DropSavedPath();
	CurrentMaze = NewMaze;
	CurrentCell = StartingCell;

	return true;
}

bool UMazeWalker::TeleportTo(ACell* Destination)
{
	if (!IsValid(Destination))
	{
		return false;
	}

	if (!IsValid(CurrentMaze))
	{
		return false;
	}

	if (!CurrentMaze->ContainsCell(Destination))
	{
		return false;
	}

	DropSavedPath();
	CurrentCell = Destination;

	return true;
}

bool UMazeWalker::TeleportToCoords(const FCellCoordinates& Destination)
{
	if (!IsValid(Destination.Maze))
	{
		return false;
	}

	ACell* DestinationCell;
	if (Destination.Maze == CurrentMaze)
	{
		DestinationCell = CurrentMaze->GetCell(Destination.CellColumn, Destination.CellRow);
		if (!IsValid(DestinationCell))
		{
			return false;
		}

		return TeleportTo(DestinationCell);
	}
	// else
	DestinationCell = Destination.Maze->GetCell(Destination.CellColumn, Destination.CellRow);
	if (!IsValid(DestinationCell))
	{
		return false;
	}

	return TeleportToMaze(Destination.Maze, DestinationCell);
}

void UMazeWalker::DropSavedPath()
{
	PreviousSteps.Empty();
}

TArray<ACell*> UMazeWalker::GetSavedPath() const
{
	TArray<ACell*> Result = PreviousSteps;
	Result.Add(CurrentCell);
	return Result;
}
