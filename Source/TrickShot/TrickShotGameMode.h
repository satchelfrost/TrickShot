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

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnGameOver();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void LoadNextLevel();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	UAudioComponent* LoadLevelJingle(UAudioComponent* ac);

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	FString GetEndOfLevelMessage();


protected:
	// Camera will be a secondary spectator to change viewport
	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* LevelOnejingle;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* LevelTwojingle;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* LevelThreejingle;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* LevelFourjingle;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* LevelFivejingle;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* LevelSixjingle;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* LevelSevenjingle;
	
	//UPROPERTY(VisibleAnywhere, Category = "Anything")
	//UAudioComponent* CompletionJingle;
	

private:
	FTimerHandle TimerHandle_EndViewTarget;

};



