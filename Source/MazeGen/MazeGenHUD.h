// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MazeGenHUD.generated.h"

UCLASS()
class AMazeGenHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMazeGenHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

