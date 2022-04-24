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

	UFUNCTION(BlueprintCallable, Category = "Maze|Serialization")
	static FMazeData SerializeMaze(const AMaze* Maze);
	UFUNCTION(BlueprintCallable, Category = "Maze|Serialization")
	static void RebuildMazeFromData(AMaze* Maze, const FMazeData& Data);

	UFUNCTION(BlueprintCallable, Category = "Maze|Serialization")
	static FString MazeDataToJSON(const FMazeData& Data);
	UFUNCTION(BlueprintCallable, Category = "Maze|Serialization")
	static bool MazeDataFromJSON(const FString& JsonString, FMazeData& Result);
};
