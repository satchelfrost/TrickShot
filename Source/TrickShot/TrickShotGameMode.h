// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TrickShotGameMode.generated.h"

UCLASS(minimalapi)
class ATrickShotGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATrickShotGameMode();

	void CompleteLevel();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;
};



