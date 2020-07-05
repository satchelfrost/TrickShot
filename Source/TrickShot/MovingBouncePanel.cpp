// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingBouncePanel.h"

AMovingBouncePanel::AMovingBouncePanel()
{

	PrimaryActorTick.bCanEverTick = true;
	
	bMoveFoward = true;
}

void AMovingBouncePanel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Location we will move actor
	FVector NewLocation = GetActorLocation();

	// We are either moving forward or backward
	if (bMoveFoward) {
		MoveForward(NewLocation);
	} else {
		MoveBackward(NewLocation);
	}

	// Euclidean distance between actor's initial position and newly moved
	float dist = FVector::Distance(InitialPosition, NewLocation);

	// If distance is greater than the reset distance move opposite direction
	bMoveFoward = (dist >= ResetDistance) ? !bMoveFoward : bMoveFoward;

	UE_LOG(LogTemp, Warning, TEXT("Euclidian distance: %.1f, Reset distance: %.1f"), dist, ResetDistance)

	SetActorLocation(NewLocation);
}

void AMovingBouncePanel::BeginPlay()
{
	Super::BeginPlay();
	InitialPosition = GetActorLocation();
}

void AMovingBouncePanel::MoveForward(FVector& v)
{
		if (bMoveXDirection)
			v.X += MoveXAmount;
		if (bMoveYDirection)
			v.Y += MoveYAmount;
		if (bMoveZDirection)
			v.Z += MoveZAmount;
}

void AMovingBouncePanel::MoveBackward(FVector& v)
{
		if (bMoveXDirection)
			v.X -= MoveXAmount;
		if (bMoveYDirection)
			v.Y -= MoveYAmount;
		if (bMoveZDirection)
			v.Z -= MoveZAmount;
}
