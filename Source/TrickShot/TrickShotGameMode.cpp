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
		//APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
		//if (PC) {
		//	UE_LOG(LogTemp, Warning, TEXT("PC is not nullptr"))
		//	APawn* MyPawn = PC->GetPawn();
		//	if (MyPawn)
		//		MyPawn->DisableInput(PC);
		//} else {
		//	UE_LOG(LogTemp, Warning, TEXT("PC is nullptr"))
		//}
	if (SpectatingViewpointClass) {
		TArray<AActor*> ReturnedActors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);
		if (ReturnedActors.Num() > 0) {
			AActor* NewViewTarget = ReturnedActors[0];
			APlayerController* PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
			if (PC) {
				UE_LOG(LogTemp, Warning, TEXT("PC is not nullptr"))
				PC->SetViewTargetWithBlend(NewViewTarget, 2.0f, EViewTargetBlendFunction::VTBlend_Cubic);
			} else {
				UE_LOG(LogTemp, Warning, TEXT("PC is nullptr"))
			}
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr"))
	}
}
