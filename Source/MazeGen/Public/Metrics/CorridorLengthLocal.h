// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Metrics/MazeMetricLocal.h"
#include "CorridorLengthLocal.generated.h"

/**
 * 
 */
UCLASS()
class MAZEGEN_API UCorridorLengthLocal : public UMazeMetricLocal
{
	GENERATED_BODY()

public:
	virtual void RunMetricForMaze_Implementation(AMaze* TargetMaze) override;

};
