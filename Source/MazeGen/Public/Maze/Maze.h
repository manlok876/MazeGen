// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maze/MazeStructs.h"
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

UENUM(BlueprintType)
enum class EWallDirection: uint8 {
	EWD_NS	UMETA(DisplayName = "Horizontal"),
	EWD_WE	UMETA(DisplayName = "Vertical")
};

USTRUCT(BlueprintType)
struct FMazeSize
{
	GENERATED_BODY()

public:
	FMazeSize();
	FMazeSize(int NumColumns, int NumRows);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Columns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rows;
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMazeUpdatedSignature, AMaze*, Maze);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMazeSizeChangedSignature, AMaze*, Maze, FMazeSize, OldSize, FMazeSize, NewSize);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMazeCellsAddedSignature, AMaze*, Maze, const TArray<ACell*>&, AddedCells);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMazeCellsRemovedSignature, AMaze*, Maze, const TArray<ACell*>&, RemovedCells);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMazeWallsAddedSignature, AMaze*, Maze, const TArray<AWall*>&, AddedWalls);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMazeWallsRemovedSignature, AMaze*, Maze, const TArray<AWall*>&, RemovedWalls);

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

	UFUNCTION(BlueprintPure)
	FMazeSize GetMazeSize() const;
	UFUNCTION(BlueprintCallable)
	void SetSize(const FMazeSize& NewSize);

	UFUNCTION(BlueprintPure)
	bool IsValidCell(int Column, int Row) const;
	UFUNCTION(BlueprintPure)
	bool ContainsCell(ACell* Cell) const;
	UFUNCTION(BlueprintPure)
	ACell* GetCell(int Column, int Row) const;
	UFUNCTION(BlueprintPure)
	ACell* GetCellByCoords(const FCellCoordinates& Coordinates) const;
	UFUNCTION(BlueprintPure)
	FCellCoordinates GetCellCoordinates(ACell* Cell);
	UFUNCTION(BlueprintCallable)
	TArray<ACell*> GetAllCells() const;

	UFUNCTION(BlueprintCallable, BlueprintPure=false)
	bool GetNeighboringCells(
		ACell* TargetCell, TMap<EMazeSide, ACell*>& NeighborsMap, bool bOnlyReachable = false);

	UFUNCTION(BlueprintPure)
	bool IsValidWall(int CellX, int CellY, EMazeSide WallSide) const;
	UFUNCTION(BlueprintPure)
	bool ContainsWall(AWall* Wall) const;
	UFUNCTION(BlueprintPure)
	AWall* GetWall(int CellColumn, int CellRow, EMazeSide WallSide) const;
	UFUNCTION(BlueprintPure)
	AWall* GetWallByCoords(const FWallCoordinates& Coordinates) const;
	UFUNCTION(BlueprintPure)
	FWallCoordinates GetWallCoordinates(AWall* Wall);
	UFUNCTION(BlueprintCallable)
	TArray<AWall*> GetAllWalls() const;
	UFUNCTION(BlueprintCallable)
	TArray<AWall*> GetWallsNS() const;
	UFUNCTION(BlueprintCallable)
	TArray<AWall*> GetWallsWE() const;

	UFUNCTION(BlueprintCallable)
	bool GetCellWalls(ACell* TargetCell, FCellWalls& Walls);

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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateCell(ACell* CellToUpdate);

	UFUNCTION(BlueprintNativeEvent)
	void HandleWallAdded(AWall* NewWall);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateWall(AWall* WallToUpdate);

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
	int GetNSWallIndex1D(int Column, int Row) const;
	UFUNCTION()
	AWall* GetNSWall(int Column, int Row) const;
	UFUNCTION()
	int GetWEWallIndex1D(int Column, int Row) const;
	UFUNCTION()
	AWall* GetWEWall(int Column, int Row) const;
	UFUNCTION()
	void GetWallIndex2D(int Idx1D, EWallDirection WallDir, int& Column, int& Row) const;

	UPROPERTY()
	TArray<ACell*> Cells;
	UFUNCTION()
	int GetCellIndex1D(int Column, int Row) const;
	UFUNCTION()
	static int Index1DFromIndex2D(int X, int SizeX, int Y, int SizeY);
	UFUNCTION()
	void GetCellIndex2D(int Idx1D, int& Column, int& Row) const;
	UFUNCTION()
	static void Index2DFromIndex1D(int Idx1D, int SizeX, int SizeY, int& X, int& Y);

	UFUNCTION()
	void UpdateMazeSize(int NewWidth, int NewLength);
};
