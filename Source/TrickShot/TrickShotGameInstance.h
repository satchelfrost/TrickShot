// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TrickShotGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TRICKSHOT_API UTrickShotGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTrickShotGameInstance();

	bool StartMusicForFirstTime;

	// Current Song playing, used to fade in and out
	UPROPERTY(BlueprintReadWrite, Category = "Sounds")
	UAudioComponent* CurrentSong;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Checkpoint")
	int32 m_Checkpoint;

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void IncrementCheckpoint();

	UFUNCTION(BlueprintCallable, Category = "Music")
	void FadeCurrentSong();

	UFUNCTION(BlueprintCallable, Category = "Music")
	void KillCurrentSong();

	// Used to store audio component across level transitions
	void SaveCurrentSong(UAudioComponent* ac) { CurrentSong = ac; }

private:
	
};
