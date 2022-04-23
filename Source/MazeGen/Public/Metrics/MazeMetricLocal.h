// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Metrics/LocalMetricInterface.h"
#include "MazeMetricLocal.generated.h"

class AMaze;
class ACell;

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMetricRecalculatedSignature, UObject*, MetricObject, AMaze*, RelatedMaze);

/**
 * This is the base class for per-cell metrics
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class MAZEGEN_API UMazeMetricLocal : public UObject, public ILocalMetricInterface
{
	GENERATED_BODY()

public:
	UMazeMetricLocal();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RunMetricForMaze(AMaze* TargetMaze);

	//UPROPERTY(BlueprintAssignable)
	//FMetricRecalculatedSignature MetricRelalculatedDispatcher;

	virtual float GetMetricForCell_Implementation(ACell* Cell) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TMap<ACell*, float> CachedMetricValues;

	UFUNCTION(BlueprintCallable)
	void CacheMetricValue(ACell* Cell, float MetricValue);

};
