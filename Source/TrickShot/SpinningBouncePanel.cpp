// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningBouncePanel.h"

ASpinningBouncePanel::ASpinningBouncePanel()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpinningBouncePanel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FQuat QuatRotation = FQuat(FRotator(PitchValue * DeltaSeconds, YawValue * DeltaSeconds, RollValue * DeltaSeconds));

	AddActorLocalRotation(QuatRotation);
}
