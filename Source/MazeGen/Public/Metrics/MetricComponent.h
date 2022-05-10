// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Metrics/LocalMetricInterface.h"
#include "MetricComponent.generated.h"

class AMaze;
class UMazeMetricLocal;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMetricClassChangedSignature, UMetricComponent*, MetricComponent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMetricRecalculatedSignature, UObject*, MetricObject, AMaze*, RelatedMaze);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAZEGEN_API UMetricComponent : public UActorComponent, public ILocalMetricInterface
{
	GENERATED_BODY()

public:
	UMetricComponent();

	UFUNCTION(BlueprintCallable, Category = "Metrics")
	void SetUsedMetric(TSubclassOf<UMazeMetricLocal> NewMetricClass);
	UFUNCTION(BlueprintCallable, Category = "Metrics")
	void RunMetric();

	virtual float GetMetricForCell_Implementation(ACell* Cell) override;

	AMaze* GetMaze() const;
	UFUNCTION(BlueprintCallable, Category = "Metrics")
	void SetMaze(AMaze* NewMaze);

	UPROPERTY(BlueprintAssignable)
	FMetricClassChangedSignature MetricClassChangedDespatcher;

	UPROPERTY(BlueprintAssignable)
	FMetricRecalculatedSignature MetricRecalculatedDispatcher;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<UMazeMetricLocal> MetricClass;

	UFUNCTION()
	void SetMetricObject(UMazeMetricLocal* NewMetricObject);
	UPROPERTY(BlueprintReadOnly)
	UMazeMetricLocal* MetricObject;

	UPROPERTY(BlueprintReadOnly)
	AMaze* Maze;
};
