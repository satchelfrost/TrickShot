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
	void OnGameOver();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnGoalCompleted();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void LoadNextLevel();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	bool CheckPointReached();

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	int32 GetCurrentCheckpoint();

	void LoadMusic();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void PauseToReadMsg(float PauseTime);

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void LevelTransition();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	FString GetEndOfLevelMessage();

protected:
	virtual void BeginPlay() override;

	// Camera will be a secondary spectator to change viewport
	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	int32 NumLevels;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* CompletionJingle;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* Song1;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* Song2;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* Song3;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* Song4;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* Song5;
	
private:
	FTimerHandle TimerHandle_EndViewTarget;

	FTimerHandle TimerHandle_PauseBeforeLevel;

	const int32 NUM_LVLS_FOR_CHKPNT = 6;

	void EnableInputAndLoadLevel();
};



