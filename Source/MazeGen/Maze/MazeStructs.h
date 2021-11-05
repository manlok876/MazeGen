// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeStructs.generated.h"

class AWall;

USTRUCT(BlueprintType)
struct FCellWalls
{
	GENERATED_BODY()

public:
	FCellWalls();
	FCellWalls(AWall* NorthWall, AWall* EastWall, AWall* SouthWall, AWall* WestWall);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWall* North;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWall* East;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWall* South;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWall* West;
};
