// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

UENUM(BlueprintType)
enum class EWallState : uint8
{
	EWS_Closed	UMETA(DisplayName = "Closed"),
	EWS_Open	UMETA(DisplayName = "Open")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWallUpdatedSignature, AWall*, Wall);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWallStateChangedSignature, AWall*, Wall, EWallState, NewState);

UCLASS()
class MAZEGEN_API AWall : public AActor
{
	GENERATED_BODY()

public:
	AWall();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetWallWidth(float NewWidth);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetWallThickness(float NewThickness);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetWallHeight(float NewHeight);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetWallFacingDirection(const FVector& NewFacingDir);

	UPROPERTY(BlueprintAssignable)
	FWallUpdatedSignature WallUpdatedDispatcher;

	EWallState GetWallState() const;
	UFUNCTION(BlueprintCallable)
	void SetWallState(EWallState NewState);
	UFUNCTION(BlueprintImplementableEvent)
	void OnWallStateChanged(EWallState NewState);
	UPROPERTY(BlueprintAssignable)
	FWallStateChangedSignature WallStateChangedDispatcher;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWallState State;
};
