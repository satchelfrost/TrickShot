// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningLaserButtonTimer.h"

ASpinningLaserButtonTimer::ASpinningLaserButtonTimer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpinningLaserButtonTimer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FQuat QuatRotation = FQuat(FRotator(PitchValue * DeltaSeconds, YawValue * DeltaSeconds, RollValue * DeltaSeconds));

	AddActorLocalRotation(QuatRotation);
}