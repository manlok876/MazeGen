// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maze.generated.h"

class ACell;
class AWall;
class AMaze;

UENUM(BlueprintType)
enum class EMazeSide : uint8 {
	EMS_North	UMETA(DisplayName = "North"),
	EMS_East	UMETA(DisplayName = "East"),
	EMS_South	UMETA(DisplayName = "South"),
	EMS_West	UMETA(DisplayName = "West")
};

USTRUCT(BlueprintType)
struct FCellCoordinates
{
	GENERATED_BODY()

public:
	FCellCoordinates();
	FCellCoordinates(AMaze* Maze, int Column, int Row);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMaze* Maze;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CellColumn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CellRow;
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

	UFUNCTION(BlueprintPure)
	bool IsValidCell(int X, int Y) const;
	UFUNCTION(BlueprintPure)
	ACell* GetCell(int X, int Y) const;
	UFUNCTION(BlueprintCallable)
	TArray<ACell*> GetAllCells() const;

	UFUNCTION(BlueprintPure)
	bool IsValidWall(int CellX, int CellY, EMazeSide WallSide) const;
	UFUNCTION(BlueprintPure)
	AWall* GetWall(int CellX, int CellY, EMazeSide WallSide) const;
	UFUNCTION(BlueprintCallable)
	TArray<AWall*> GetAllWalls() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void Init(int W, int L);

	UFUNCTION(BlueprintNativeEvent)
	void HandleCellAdded(ACell* NewCell);

	UFUNCTION(BlueprintNativeEvent)
	void HandleWallAdded(AWall* NewWall);

private:
	UPROPERTY()
	bool bInitialized;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int Length;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int Width;

	UPROPERTY()
	TArray<AWall*> WallsNS;
	UPROPERTY()
	TArray<AWall*> WallsWE;
	UFUNCTION()
	int GetNSWallIndex1D(int X, int Y) const;
	UFUNCTION()
	int GetWEWallIndex1D(int X, int Y) const;

	UPROPERTY()
	TArray<ACell*> Cells;
	UFUNCTION()
	int GetCellIndex1D(int X, int Y) const;
	UFUNCTION()
	static int Index1DFromIndex2D(int X, int SizeX, int Y, int SizeY);
	UFUNCTION()
	void GetCellIndex2D(int Idx1D, int& X, int& Y) const;
	UFUNCTION()
	static void Index2DFromIndex1D(int Idx1D, int SizeX, int SizeY, int& X, int& Y);

	UFUNCTION()
	void UpdateMazeSize(int NewWidth, int NewLength);
};
