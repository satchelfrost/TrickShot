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

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnGoalCompleted();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void LoadNextLevel();


protected:
	// Camera will be a secondary spectator to change viewport
	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;
private:
	FTimerHandle TimerHandle_EndViewTarget;

};



