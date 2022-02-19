// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MazeStructs.h"
#include "MazeUtils.generated.h"

class AMaze;
class ACell;
class AWall;

UCLASS()
class MAZEGEN_API UMazeUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static AWall* GetWall(const FCellWalls& Walls, EMazeSide Side);

	UFUNCTION(BlueprintCallable)
	static FMazeData SerializeMaze(const AMaze* Maze);
	UFUNCTION(BlueprintCallable)
	static void RebuildMazeFromData(AMaze* Maze, const FMazeData& Data);

	UFUNCTION(BlueprintCallable)
	static FString MazeDataToJSON(const FMazeData& Data);
	UFUNCTION(BlueprintCallable)
	static bool MazeDataFromJSON(const FString& JsonString, FMazeData& Result);
};
