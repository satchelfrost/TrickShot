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
	bool CheckPointReached();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	UAudioComponent* LoadLevelJingle(UAudioComponent* ac);

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	FString GetEndOfLevelMessage();


protected:
	// Camera will be a secondary spectator to change viewport
	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	int32 NumLevels;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* jingle_0;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* jingle_1;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* jingle_2;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* jingle_3;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* jingle_4;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* jingle_5;
	
	//UPROPERTY(VisibleAnywhere, Category = "Anything")
	//UAudioComponent* CompletionJingle;
	

private:
	FTimerHandle TimerHandle_EndViewTarget;


	const int32 NUM_LEVELS_TO_GET_CCKPNT = 5;
};



