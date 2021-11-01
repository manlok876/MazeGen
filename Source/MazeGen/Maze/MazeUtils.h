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
};
