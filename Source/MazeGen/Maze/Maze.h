// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maze.generated.h"

class ACell;
class AWall;

USTRUCT()
class FArray2D
{
	GENERATED_BODY()

public:

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

	UFUNCTION()
	void AddCell(int X, int Y);
	UFUNCTION(BlueprintNativeEvent)
	void HandleCellAdded(ACell* NewCell);

	UFUNCTION()
	void AddWall(int X, int Y);
	UFUNCTION(BlueprintNativeEvent)
	void HandleWallAdded(AWall* NewWall);

private:
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
