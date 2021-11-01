// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeStructs.h"

FCellWalls::FCellWalls()
{
	North = East = South = West = nullptr;
}

FCellWalls::FCellWalls(AWall* NorthWall, AWall* EastWall, AWall* SouthWall, AWall* WestWall)
{
	North = NorthWall;
	East = EastWall;
	South = SouthWall;
	West = WestWall;
}
