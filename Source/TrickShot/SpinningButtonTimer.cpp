// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningButtonTimer.h"

ASpinningButtonTimer::ASpinningButtonTimer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpinningButtonTimer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FQuat QuatRotation = FQuat(FRotator(PitchValue * DeltaSeconds, YawValue * DeltaSeconds, RollValue * DeltaSeconds));

	AddActorLocalRotation(QuatRotation);
}
