// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TrickShotHUD.generated.h"

UCLASS()
class ATrickShotHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATrickShotHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

