// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maze.generated.h"

class ACell;
class AWall;
class AMaze;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMazeUpdatedSignature, AMaze*, Maze);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMazeSizeChangedSignature, AMaze*, Maze, FIntPoint, OldSize, FIntPoint, NewSize);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMazeCellsAddedSignature, AMaze*, Maze, const TArray<ACell*>&, AddedCells);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMazeCellsRemovedSignature, AMaze*, Maze, const TArray<ACell*>&, RemovedCells);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMazeWallsAddedSignature, AMaze*, Maze, const TArray<AWall*>&, AddedWalls);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMazeWallsRemovedSignature, AMaze*, Maze, const TArray<AWall*>&, RemovedWalls);

UENUM(BlueprintType)
enum class EMazeSide : uint8 {
	EMS_North	UMETA(DisplayName = "North"),
	EMS_East	UMETA(DisplayName = "East"),
	EMS_South	UMETA(DisplayName = "South"),
	EMS_West	UMETA(DisplayName = "West")
};

UENUM(BlueprintType)
enum class EWallDirection: uint8 {
	EWD_NS	UMETA(DisplayName = "Horizontal"),
	EWD_WE	UMETA(DisplayName = "Vertical")
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

USTRUCT(BlueprintType)
struct FWallCoordinates
{
	GENERATED_BODY()

public:
	FWallCoordinates();
	FWallCoordinates(AMaze* Maze, int Column, int Row, EWallDirection WallDirection);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMaze* Maze;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WallColumn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WallRow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWallDirection WallDirection;
};

UCLASS(BlueprintType, Blueprintable)
class MAZEGEN_API AMaze : public AActor
{
	GENERATED_BODY()
	
public:
	AMaze();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ACell> CellClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AWall> WallClass;

	int GetLength() const;
	UFUNCTION(BlueprintCallable)
	void SetLength(int NewLength);

	int GetWidth() const;
	UFUNCTION(BlueprintCallable)
	void SetWidth(int NewWidth);

	UFUNCTION(BlueprintCallable)
	void SetSize(int NewWidth, int NewLength);

	UFUNCTION(BlueprintPure)
	bool IsValidCell(int Column, int Row) const;
	UFUNCTION(BlueprintPure)
	ACell* GetCell(int Column, int Row) const;
	UFUNCTION(BlueprintCallable)
	TArray<ACell*> GetAllCells() const;
	UFUNCTION(BlueprintPure)
	FCellCoordinates GetCellCoordinates(ACell* Cell);

	UFUNCTION(BlueprintPure)
	bool IsValidWall(int CellX, int CellY, EMazeSide WallSide) const;
	UFUNCTION(BlueprintPure)
	AWall* GetWall(int CellX, int CellY, EMazeSide WallSide) const;
	UFUNCTION(BlueprintCallable)
	TArray<AWall*> GetAllWalls() const;
	UFUNCTION(BlueprintPure)
	FWallCoordinates GetWallCoordinates(AWall* Wall);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMazeUpdatedSignature OnMazeUpdatedDispatcher;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMazeSizeChangedSignature OnMazeSizeChangedDispatcher;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMazeCellsAddedSignature OnMazeCellsAddedDispatcher;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMazeCellsRemovedSignature OnMazeCellsRemovedDispatcher;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMazeWallsAddedSignature OnMazeWallsAddedDispatcher;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMazeWallsRemovedSignature OnMazeWallsRemovedDispatcher;

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
	UFUNCTION()
	void GetWallIndex2D(int Idx1D, EWallDirection WallDir, int& X, int& Y) const;

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
