// Fill out your copyright notice in the Description page of Project Settings.


#include "TrickShotGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

UTrickShotGameInstance::UTrickShotGameInstance()
{
	StartMusicForFirstTime = true;
	m_Checkpoint = 0;
}

void UTrickShotGameInstance::IncrementCheckpoint()
{
	m_Checkpoint++;
	StartMusicForFirstTime = true;
}

void UTrickShotGameInstance::FadeCurrentSong()
{
	if (CurrentSong)
		CurrentSong->FadeOut(2.0f, 0.0f, EAudioFaderCurve::Linear);
	else
		UE_LOG(LogTemp, Warning, TEXT("Tried to fade song that doesn't exist"))

	StartMusicForFirstTime = true;
}

void UTrickShotGameInstance::KillCurrentSong()
{
	if (CurrentSong)
		CurrentSong->SetVolumeMultiplier(0.0f);
	else
		UE_LOG(LogTemp, Warning, TEXT("Tried to kill song that doesn't exist"))
}
