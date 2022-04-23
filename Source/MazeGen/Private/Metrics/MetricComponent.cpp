// Fill out your copyright notice in the Description page of Project Settings.


#include "Metrics/MetricComponent.h"
#include "Maze/Maze.h"

UMetricComponent::UMetricComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MetricClass = nullptr;
	MetricObject = nullptr;
}

void UMetricComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UMetricComponent::SetMetricObject(UObject* NewMetricObject)
{
	if (NewMetricObject == MetricObject)
	{
		return;
	}

	if (IsValid(MetricObject))
	{
		// Unbind
	}

	if (!IsValid(NewMetricObject))
	{
		MetricClass = nullptr;
		MetricObject = nullptr;
		return;
	}

	MetricObject = NewMetricObject;
	MetricClass = MetricObject->GetClass();

	if (IsValid(MetricObject))
	{
		// Bind
	}

	if (MetricClassChangedDespatcher.IsBound())
	{
		MetricClassChangedDespatcher.Broadcast(this);
	}
}

void UMetricComponent::SetUsedMetric(TSubclassOf<UObject> NewMetricClass)
{
	if (NewMetricClass == MetricClass)
	{
		return;
	}

	if (!IsValid(NewMetricClass))
	{
		SetMetricObject(nullptr);
		return;
	}

	if (!MetricClass->Implements<ULocalMetricInterface>())
	{
		UE_LOG(LogTemp, Error, TEXT("UMetricComponent::SetUsedMetric: Provided class does not implement LocalMetricInterface, aborting"));
	}

	SetMetricObject(NewObject<UObject>(this, MetricClass));
}

float UMetricComponent::GetMetricForCell_Implementation(ACell* Cell)
{
	if (!IsValid(MetricObject))
	{
		return 0.0f;
	}
	return ILocalMetricInterface::Execute_GetMetricForCell(MetricObject, Cell);
}

AMaze* UMetricComponent::GetMaze() const
{
	return Maze;
}

void UMetricComponent::SetMaze(AMaze* NewMaze)
{
	if (NewMaze == Maze)
	{
		return;
	}

	if (IsValid(Maze))
	{
		// Unbind
	}

	Maze = IsValid(NewMaze) ? NewMaze : nullptr;

	if (IsValid(Maze))
	{
		// Bind
	}

	if (IsValid(MetricObject))
	{

	}
}
