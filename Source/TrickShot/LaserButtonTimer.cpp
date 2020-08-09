// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserButtonTimer.h"
#include "LaserBeam.h"
#include "Kismet/GameplayStatics.h"
#include "TrickShotProjectile.h"
#include "Components/BoxComponent.h"

ALaserButtonTimer::ALaserButtonTimer()
{
	//OverlapComp->OnComponentHit.AddDynamic(this, &ALaserButtonTimer::TriggerLaser);
	//OverlapComp->SetHiddenInGame(true);
}

void ALaserButtonTimer::HandleOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	ATrickShotProjectile* ball = Cast<ATrickShotProjectile>(OtherActor);
	if (ball) {
		// Play sound when ball first hits button
		UGameplayStatics::PlaySound2D(this, ButtonSetSound);

		// specify behavior for the change of other actor 
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALaserBeam::StaticClass(), Actors);
		for (auto Actor : Actors) {
			ALaserBeam* Beam = Cast<ALaserBeam>(Actor);
			if (LaserName == Beam->LaserName)
				Beam->DisableLaser();
		}

		// Set button to green color (or not red)
		bButtonColorRed = false;

		//UE_LOG(LogTemp, Warning, TEXT("button color red %d"), bButtonColorRed)
		UE_LOG(LogTemp, Warning, TEXT("Only in overriden function"))
		

		// Update color of this object
		UpdateColor();

		// Set timer
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ButtonTimer, this, &ALaserButtonTimer::RevertChange, TimeForButtonReset);
	}
}

void ALaserButtonTimer::RevertChange()
{
	// Set button color back to red
	bButtonColorRed = true;

	UE_LOG(LogTemp, Warning, TEXT("button color change back red %d"), bButtonColorRed)

	// Update the color of this object
	UpdateColor();

	// specify behavior for the change of other actor 
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALaserBeam::StaticClass(), Actors);
	for (auto Actor : Actors) {
		ALaserBeam* Beam = Cast<ALaserBeam>(Actor);
		if (LaserName == Beam->LaserName)
			Beam->EnableLaser();
	}

	// Play sound for button reset 
	UGameplayStatics::PlaySound2D(this, ButtonResetSound);
}
