// Fill out your copyright notice in the Description page of Project Settings.


#include "Metrics/MazeMetricLocal.h"
#include "Maze/Cell.h"

UMazeMetricLocal::UMazeMetricLocal()
{

}

void UMazeMetricLocal::RunMetricForMaze_Implementation(AMaze* TargetMaze)
{
}

float UMazeMetricLocal::GetMetricForCell_Implementation(ACell* Cell)
{
	if (!CachedMetricValues.Find(Cell))
	{
		return 0.0f;
	}
	return CachedMetricValues[Cell];
}

void UMazeMetricLocal::CacheMetricValue(ACell* Cell, float MetricValue)
{
	if (!IsValid(Cell))
	{
		return;
	}
	CachedMetricValues[Cell] = MetricValue;
}
