// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LocalMetricInterface.generated.h"

class ACell;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULocalMetricInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAZEGEN_API ILocalMetricInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetMetricForCell(ACell* Cell);
};
