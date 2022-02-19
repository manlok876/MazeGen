// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeUtils.h"
#include "Maze.h"
#include "JsonObjectConverter.h"

AWall* UMazeUtils::GetWall(const FCellWalls& Walls, EMazeSide Side)
{
	if (Side == EMazeSide::EMS_North)
	{
		return Walls.North;
	}
	else if (Side == EMazeSide::EMS_East)
	{
		return Walls.East;
	}
	else if (Side == EMazeSide::EMS_South)
	{
		return Walls.South;
	}
	else if (Side == EMazeSide::EMS_West)
	{
		return Walls.West;
	}
	return nullptr;
}

FMazeData UMazeUtils::SerializeMaze(const AMaze* Maze)
{
	return FMazeData(Maze);
}

void UMazeUtils::RebuildMazeFromData(AMaze* Maze, const FMazeData& Data)
{
	if (Data.Width < 1 || Data.Length < 1)
	{
		return;
	}
	check(Data.CellsInfo.Num() == Data.Width * Data.Length);
	check(Data.NSWallsInfo.Num() == Data.Width * (Data.Length + 1));
	check(Data.WEWallsInfo.Num() == (Data.Width + 1) * Data.Length);

	Maze->SetSize(Data.Width, Data.Length);
	check(Maze->GetAllCells().Num() == Data.CellsInfo.Num());
	check(Maze->GetWallsNS().Num() == Data.NSWallsInfo.Num());
	check(Maze->GetWallsWE().Num() == Data.WEWallsInfo.Num());

	int CellIdx = 0;
	const TArray<ECellState>& CellsInfo = Data.CellsInfo;
	for (ACell* Cell : Maze->GetAllCells())
	{
		Cell->SetCellState(CellsInfo[CellIdx]);
		++CellIdx;
	}

	int NSWallIdx = 0;
	const TArray<EWallState>& NSWallsInfo = Data.NSWallsInfo;
	for (AWall* Wall : Maze->GetWallsNS())
	{
		Wall->SetWallState(NSWallsInfo[NSWallIdx]);
		++NSWallIdx;
	}

	int WEWallIdx = 0;
	const TArray<EWallState>& WEWallsInfo = Data.WEWallsInfo;
	for (AWall* Wall : Maze->GetWallsWE())
	{
		Wall->SetWallState(WEWallsInfo[WEWallIdx]);
		++WEWallIdx;
	}
}

FString UMazeUtils::MazeDataToJSON(const FMazeData& Data)
{
	FString Result;
	FJsonObjectConverter::UStructToJsonObjectString(Data, Result);
	return Result;
}

bool UMazeUtils::MazeDataFromJSON(const FString& JsonString, FMazeData& Result)
{
	return FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &Result, 0, 0);
}
