// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maze.generated.h"

class ACell;
class AWall;

UENUM(BlueprintType)
enum class EMazeSide : uint8 {
	EMS_North	UMETA(DisplayName = "North"),
	EMS_East	UMETA(DisplayName = "East"),
	EMS_South	UMETA(DisplayName = "South"),
	EMS_West	UMETA(DisplayName = "West")
};

UCLASS(BlueprintType, Blueprintable)
class MAZEGEN_API AMaze : public AActor
{
	GENERATED_BODY()
	
public:
	AMaze();

	virtual void Tick(float DeltaTime) override;

	int GetLength() const;
	UFUNCTION(BlueprintCallable)
	void SetLength(int NewLength);

	int GetWidth() const;
	UFUNCTION(BlueprintCallable)
	void SetWidth(int NewWidth);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void Init(int W, int L);

	UFUNCTION()
	void AddCell(int X, int Y);
	UFUNCTION(BlueprintNativeEvent)
	void HandleCellAdded(ACell* NewCell);

	UFUNCTION()
	void AddWall(int X, int Y);
	UFUNCTION(BlueprintNativeEvent)
	void HandleWallAdded(AWall* NewWall);

private:
	UPROPERTY()
	bool bInitialized;
	UFUNCTION()
	void Init_CreateCells();
	UFUNCTION()
	void Init_CreateWalls();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int Length;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int Width;

	UPROPERTY()
	TArray<AWall*> WallsNS;
	UPROPERTY()
	TArray<AWall*> WallsWE;
	UPROPERTY()
	TArray<ACell*> Cells;
};
