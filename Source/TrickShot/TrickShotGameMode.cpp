// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrickShotGameMode.h"
#include "TrickShotHUD.h"
#include "TrickShotCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Level %s"), *LevelCountString)
	int32 LevelCount = FCString::Atoi(*LevelCountString);
	LevelCount++; // increment to next level
	LevelCountString = FString::FromInt(LevelCount);

	// Check if next level exists
	
	// Load the next level
	FName LevelName = *LevelCountString;
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}
