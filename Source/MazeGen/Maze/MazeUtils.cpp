// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeUtils.h"
#include "Maze.h"

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
