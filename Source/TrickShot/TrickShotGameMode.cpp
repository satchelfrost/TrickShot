// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrickShotGameMode.h"
#include "TrickShotHUD.h"
#include "TrickShotCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

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
		FName LevelName = "EndLevel";
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	} else {
		// Load the next level
		FName LevelName = *LevelCountString;
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	} 
}

UAudioComponent* ATrickShotGameMode::LoadLevelJingle(UAudioComponent* ac)
{
	// Get level by number
	FString LevelCountString = UGameplayStatics::GetCurrentLevelName(GetWorld());
	int32 LevelCount = FCString::Atoi(*LevelCountString);

	switch (LevelCount % 6) {
	case 0: ac->Sound = jingle_0; break;
	case 1: ac->Sound = jingle_1; break;
	case 2: ac->Sound = jingle_2; break;
	case 3: ac->Sound = jingle_3; break;
	case 4: ac->Sound = jingle_4; break;
	case 5: ac->Sound = jingle_5; break;
	}

	return ac;
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
