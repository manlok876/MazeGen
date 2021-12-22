// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.generated.h"

UCLASS()
class MAZEGEN_API ACell : public AActor
{
	GENERATED_BODY()

public:
	ACell();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCellSize(const FVector2D& NewSize);

protected:
	virtual void BeginPlay() override;

};
