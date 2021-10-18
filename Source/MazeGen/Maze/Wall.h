// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

UCLASS()
class MAZEGEN_API AWall : public AActor
{
	GENERATED_BODY()
	
public:
	AWall();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};
