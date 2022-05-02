// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cell.h"
#include "Wall.h"
#include "MazeStructs.generated.h"

class AMaze;

USTRUCT(BlueprintType)
struct FCellWalls
{
	GENERATED_BODY()

public:
	FCellWalls();
	FCellWalls(ACell* InCell, AWall* NorthWall, AWall* EastWall, AWall* SouthWall, AWall* WestWall);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACell* Cell;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWall* North;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWall* East;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWall* South;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWall* West;
};


USTRUCT(BlueprintType)
struct FMazeData
{
	GENERATED_BODY()

public:
	FMazeData();
	FMazeData(const AMaze* Maze);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Length;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ECellState> CellsInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EWallState> NSWallsInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EWallState> WEWallsInfo;
};
