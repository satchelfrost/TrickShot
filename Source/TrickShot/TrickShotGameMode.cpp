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

	// Save current checkpoint
	TrickShotGI->m_Checkpoint = GetCurrentCheckpoint();

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
	if (LevelCount > NumLevels) {
		FName LevelName = "EndLevel"; // TODO: This doesn't need to be a variable
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	} else {
		// Load the next level
		FName LevelName = *LevelCountString;
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	}
}

bool ATrickShotGameMode::CheckPointReached()
{
	// Checks if we are on the level to get check point, not necessarily saying we have beat the level.
	FString LevelCountString = UGameplayStatics::GetCurrentLevelName(GetWorld());
	int32 LevelCount = FCString::Atoi(*LevelCountString);
	return LevelCount % NUM_LVLS_FOR_CHKPNT == 0;
}

int32 ATrickShotGameMode::GetCurrentCheckpoint()
{
	// Calculate current checkpoint: so levels can be loaded out of order and have music match.
	FString LevelCountString = UGameplayStatics::GetCurrentLevelName(GetWorld());
	int32 LevelCount = FCString::Atoi(*LevelCountString);
	int32 Chkpnt = (LevelCount % NUM_LVLS_FOR_CHKPNT != 0) ? LevelCount / NUM_LVLS_FOR_CHKPNT : LevelCount / (NUM_LVLS_FOR_CHKPNT + 1);
	return Chkpnt;
}

void ATrickShotGameMode::LoadMusic()
{
	// Get static variable container for music and set/reset music boolean.
	UGameInstance* GI = GetGameInstance();
	UTrickShotGameInstance* TrickShotGI = Cast<UTrickShotGameInstance>(GI);

	// Get current checkpoint
	int32 Chkpnt = GetCurrentCheckpoint();

	// Load music or continue playing music 
	if (TrickShotGI) {
		if (TrickShotGI->StartMusicForFirstTime) {
			TrickShotGI->StartMusicForFirstTime = false;
			UAudioComponent* ac = nullptr;
			switch (Chkpnt) {
			case 0: ac = UGameplayStatics::SpawnSound2D(this, Song1, 0.4f, 1.0f, 0.0f, nullptr, true, true);  break;
			case 1: ac = UGameplayStatics::SpawnSound2D(this, Song2, 0.4f, 1.0f, 0.0f, nullptr, true, true);  break;
			case 2: ac = UGameplayStatics::SpawnSound2D(this, Song3, 0.4f, 1.0f, 0.0f, nullptr, true, true);  break;
			case 3: ac = UGameplayStatics::SpawnSound2D(this, Song4, 0.4f, 1.0f, 0.0f, nullptr, true, true);  break;
			case 4: ac = UGameplayStatics::SpawnSound2D(this, Song5, 0.4f, 1.0f, 0.0f, nullptr, true, true);  break;
			}

			// Fade in music
			if (ac)
				ac->FadeIn(3.0f, 1.0, 0.0, EAudioFaderCurve::Linear);

			// We need to statically save current song address so that later we can fade out
			TrickShotGI->SaveCurrentSong(ac);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("Music not loaded a second time"))
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("TrickShot Game instance failed!"))
	}

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
	case  1: Msg = "Nice job... I guess.";                 break;
	case  2: Msg = "Please, you're still a noob.";         break;
	case  3: Msg = "Ready for something harder?";          break;
	case  4: Msg = "Fine, let's up the ante.";             break;
	case  5: Msg = "Alright, I'm tired of your malarkey."; break;
	case  6: Msg = "Checkpoint Reached.";                  break;
	case  7: Msg = "That was just a practice run.";        break;
	case  8: Msg = "Try this next one on for size!";       break;
	case  9: Msg = "Still... you know nothing.";           break;
	case 10: Msg = "Prepare to be owned.";                 break;
	case 11: Msg = "Well well well... Try This!";          break;
	case 12: Msg = "Checkpoint Reached.";                  break;
	case 13: Msg = "I mean you need practice.";            break;
	case 14: Msg = "You think you're so smart!";           break;
	case 15: Msg = "You still don't have my respect.";     break;
	case 16: Msg = "And you persist why?";                 break;
	case 17: Msg = "I'm tired of messing around.";         break;
	case 18: Msg = "Checkpoint Reached...";                break;
	case 19: Msg = "Trendy..";                             break;
	case 20: Msg = "Figure this next one out.";            break;
	case 21: Msg = "Okay you're smarter than you look.";   break;
	case 22: Msg = "Why are you still here?";              break;
	case 23: Msg = "So you've got tenacity.";              break;
	case 24: Msg = "Checkpoint Reached.";                  break;
	case 25: Msg = "They can't all be hard.";              break;
	case 26: Msg = "Tricky eh?";                           break;
	case 27: Msg = "Okay you make the levels then!";       break;
	case 28: Msg = "Simple yet difficult.";                break;
	case 29: Msg = "Gaining my respect.";                  break;
	case 30: Msg = "That was for funzies.";                break;
	default: Msg = "Default Message";                      break;
	}

	return Msg;
}

void ATrickShotGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Load new music or continue playing current music
	LoadMusic();
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
