// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrickShotGameMode.h"
#include "TrickShotHUD.h"
#include "TrickShotCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "TrickShotGameInstance.h"

ATrickShotGameMode::ATrickShotGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATrickShotHUD::StaticClass();
}

void ATrickShotGameMode::CompleteLevel()
{
	if (SpectatingViewpointClass) {
		TArray<AActor*> ReturnedActors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);
		if (ReturnedActors.Num() > 0) {
			AActor* NewViewTarget = ReturnedActors[0];
			APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
			if (PC) {
				// Disable input
				APawn* MyPawn = PC->GetPawn();
				if (MyPawn)
					MyPawn->DisableInput(PC);
				// Change viewport to secondary camera (i.e. not first person)
				float ViewTargetTime = 2.0f;
				PC->SetViewTargetWithBlend(NewViewTarget, ViewTargetTime, EViewTargetBlendFunction::VTBlend_Cubic);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle_EndViewTarget, this, &ATrickShotGameMode::OnGoalCompleted, ViewTargetTime);
			} else {
				UE_LOG(LogTemp, Warning, TEXT("PC is nullptr"))
			}
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr."))
	}
}

void ATrickShotGameMode::OnGameOver()
{
	// Fade out current song
	UGameInstance* GI = GetGameInstance();
	UTrickShotGameInstance* TrickShotGI = Cast<UTrickShotGameInstance>(GI);
	if (TrickShotGI)
		TrickShotGI->FadeCurrentSong();

	// Open the game over level
	UGameplayStatics::OpenLevel(GetWorld(), "GameOverLevel");
}

void ATrickShotGameMode::LoadNextLevel()
{
	// Get level by number
	FString LevelCountString = UGameplayStatics::GetCurrentLevelName(GetWorld());
	//UE_LOG(LogTemp, Warning, TEXT("Level %s"), *LevelCountString)
	int32 LevelCount = FCString::Atoi(*LevelCountString);
	LevelCount++; // increment to next level
	LevelCountString = FString::FromInt(LevelCount);

	// Check if last level
	if (LevelCount == NumLevels) {
		FName LevelName = "EndLevel"; // TODO: This doesn't need to be a variable
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	} else {
		// Load the next level
		FName LevelName = *LevelCountString;
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	}

	// If we've reached a checkpoint then increment the checkpoint 
	if (CheckPointReached()) {
		UGameInstance* GI = GetGameInstance();
		UTrickShotGameInstance* TrickShotGI = Cast<UTrickShotGameInstance>(GI);
		if (TrickShotGI)
			TrickShotGI->IncrementCheckpoint();
	}
}

bool ATrickShotGameMode::CheckPointReached()
{
	FString LevelCountString = UGameplayStatics::GetCurrentLevelName(GetWorld());
	int32 LevelCount = FCString::Atoi(*LevelCountString);
	bool chkpnt = LevelCount % NUM_LEVELS_TO_GET_CCKPNT == 0; // This is not clean at ALL
	UE_LOG(LogTemp, Warning, TEXT("Level Count %d, Checkpoint %d"), LevelCount, chkpnt)
	if (LevelCount != 0)
		return chkpnt;
	else
		return 0;
}

void ATrickShotGameMode::PauseToReadMsg(float PauseTime)
{
	// Pause before enabling player input and loading the next level
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_PauseBeforeLevel, this, &ATrickShotGameMode::EnableInputAndLoadLevel, PauseTime);
}

void ATrickShotGameMode::LevelTransition()
{
	// If checkpoint reached, kill music, play checkpoint jingle, load next level
	if (CheckPointReached()) {
		// Kill music
		UGameInstance* GI = GetGameInstance();
		UTrickShotGameInstance* TrickShotGI = Cast<UTrickShotGameInstance>(GI);
		if (TrickShotGI)
			TrickShotGI->KillCurrentSong();

		// Play checkpoint jingle
		UGameplayStatics::PlaySound2D(this, CompletionJingle);

		// Pause to read message before loading next level
		PauseToReadMsg(CompletionJingle->Duration);
	} else {
		// Pause to read message before loading next level
		PauseToReadMsg(3.0);
	}
}

FString ATrickShotGameMode::GetEndOfLevelMessage()
{
	// Get current level by number
	FString LevelCountString = UGameplayStatics::GetCurrentLevelName(GetWorld());
	int32 LevelCount = FCString::Atoi(*LevelCountString);

	FString Msg = "";

	switch (LevelCount) {
	case 0: Msg = "Nice job... I guess.";                 break;
	case 1: Msg = "Please, you're still a noob.";         break;
	case 2: Msg = "Ready for something harder?";          break;
	case 3: Msg = "Fine, let's up the ante.";             break;
	case 4: Msg = "Alright, I'm tired of your malarkey."; break;
	case 5: Msg = "Checkpoint Reached.";                  break;
	case 6: Msg = "That was just a practice run.";        break;
	case 7: Msg = "Try this on for size!";                break;
	case 8: Msg = "Still... you know nothing.";           break;
	case 9: Msg = "Prepare to be powned.";                break;
	default: Msg = "Default Message";                     break;
	}

	return Msg;
}

void ATrickShotGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* GI = GetGameInstance();
	UTrickShotGameInstance* TrickShotGI = Cast<UTrickShotGameInstance>(GI);

	if (TrickShotGI) {
		if (TrickShotGI->StartMusicForFirstTime) {
			//TrickShotGI->LoadMusicFromCheckpoint();
			TrickShotGI->StartMusicForFirstTime = false;
			UAudioComponent* ac = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("m_Checkpoint = %d"), TrickShotGI->m_Checkpoint)
			switch (TrickShotGI->m_Checkpoint) {
			case 0: ac = UGameplayStatics::SpawnSound2D(this, Song1, 0.4f, 1.0f, 0.0f, nullptr, true, true);  break;
			case 1: ac = UGameplayStatics::SpawnSound2D(this, Song2, 0.4f, 1.0f, 0.0f, nullptr, true, true);  break;
			case 2: ac = UGameplayStatics::SpawnSound2D(this, Song3, 0.4f, 1.0f, 0.0f, nullptr, true, true);  break;
			case 3: ac = UGameplayStatics::SpawnSound2D(this, Song4, 0.4f, 1.0f, 0.0f, nullptr, true, true);  break;
			case 4: ac = UGameplayStatics::SpawnSound2D(this, Song5, 0.4f, 1.0f, 0.0f, nullptr, true, true);  break;
			}
			if (ac)
				ac->FadeIn(3.0f, 1.0, 0.0, EAudioFaderCurve::Linear);

			TrickShotGI->SaveCurrentSong(ac);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("Music not loaded a second time"))
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("TrickShot Game instance failed!"))
	}
}

void ATrickShotGameMode::EnableInputAndLoadLevel()
{
		APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
		if (PC) {
			// Enable input
			APawn* MyPawn = PC->GetPawn();
			if (MyPawn)
				MyPawn->EnableInput(PC);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("PC is nullptr."))
		}

		LoadNextLevel();
}
