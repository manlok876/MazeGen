// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cell.generated.h"

UENUM(BlueprintType)
enum class ECellState : uint8
{
	ECS_Blank	UMETA(DisplayName = "Blank")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCellUpdatedSignature, ACell*, Cell);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCellStateChangedSignature, ACell*, Cell, ECellState, NewState);

UCLASS()
class MAZEGEN_API ACell : public AActor
{
	GENERATED_BODY()

public:
	ACell();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCellSize(const FVector2D& NewSize);

	UPROPERTY(BlueprintAssignable)
	FCellUpdatedSignature CellUpdatedDispatcher;

	ECellState GetCellState() const;
	UFUNCTION(BlueprintCallable)
	void SetCellState(ECellState NewState);
	UFUNCTION(BlueprintImplementableEvent)
	void OnCellStateChanged(ECellState NewState);
	UPROPERTY(BlueprintAssignable)
	FCellStateChangedSignature CellStateChangedDispatcher;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECellState State;
};
