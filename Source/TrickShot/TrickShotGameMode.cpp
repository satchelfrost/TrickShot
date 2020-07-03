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
	if (LevelCount == 7) {
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

	switch (LevelCount) {
	case 1: ac->Sound = LevelOnejingle; break;
	case 2: ac->Sound = LevelTwojingle; break;
	case 3: ac->Sound = LevelThreejingle; break;
	case 4: ac->Sound = LevelFourjingle; break;
	case 5: ac->Sound = LevelFivejingle; break;
	case 6: ac->Sound = LevelSixjingle; break;
	case 7: ac->Sound = LevelSevenjingle; break;
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
	case 1: Msg = "Nice job... I guess.";                 break;
	case 2: Msg = "Please, you're still a noob.";         break;
	case 3: Msg = "Ready for something harder?";          break;
	case 4: Msg = "Fine, let's up the ante.";             break;
	case 5: Msg = "Alright, I'm tired of your malarkey."; break;
	case 6: Msg = "Really b?";                            break;
	case 7: Msg = "Okay I have to hand it to you.";       break;
	}

	return Msg;
}
