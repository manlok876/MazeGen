// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Maze/Maze.h"
#include "Maze/MazeStructs.h"
#include "MazeWalker.generated.h"

class ACell;

/**
 * 
 */
UCLASS()
class MAZEGEN_API UMazeWalker : public UObject
{
	GENERATED_BODY()

public:
	AMaze* GetCurrentMaze() const;
	ACell* GetCurrentCell() const;

	UFUNCTION(BlueprintCallable, Category = "Maze|Pathfinding")
	bool TryStep(EMazeSide Direction);
	UFUNCTION(BlueprintCallable, Category = "Maze|Pathfinding")
	ACell* TryStepBack();

	UFUNCTION(BlueprintCallable, Category = "Maze|Pathfinding")
	bool TryGoTo(ACell* Destination);
	UFUNCTION(BlueprintCallable, Category = "Maze|Pathfinding")
	bool TryGoToCoords(const FCellCoordinates& Destination);

	UFUNCTION(BlueprintCallable, Category = "Maze|Pathfinding")
	bool TeleportToMaze(AMaze* NewMaze, ACell* StartingCell);
	UFUNCTION(BlueprintCallable, Category = "Maze|Pathfinding")
	bool TeleportTo(ACell* Destination);
	UFUNCTION(BlueprintCallable, Category = "Maze|Pathfinding")
	bool TeleportToCoords(const FCellCoordinates& Destination);

	UFUNCTION(BlueprintCallable, Category = "Maze|Pathfinding")
	void DropSavedPath();
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Maze|Pathfinding")
	TArray<ACell*> GetSavedPath() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	AMaze* CurrentMaze;
	UPROPERTY(BlueprintReadOnly)
	ACell* CurrentCell;

	UPROPERTY()
	TArray<ACell*> PreviousSteps;
};
