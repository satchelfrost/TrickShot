// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingBouncePanel.h"
#include <chrono> 

AMovingBouncePanel::AMovingBouncePanel()
{

	PrimaryActorTick.bCanEverTick = true;
	
	bMoveFoward = true;

	DistanceTravelTimeX = 1;
	DistanceTravelTimeY = 1;
	DistanceTravelTimeZ = 1;
}

void AMovingBouncePanel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Location we will move actor
	FVector NewLocation = GetActorLocation();
	FVector SavedLocation = GetActorLocation();

	// We are either moving forward or backward
	if (bMoveFoward)
		MoveForward(NewLocation, DeltaSeconds);
	else
		MoveBackward(NewLocation, DeltaSeconds);

	// Euclidean distance between actor's initial position and newly moved
	float dist = FVector::Distance(InitialPosition, NewLocation);

	// If distance is greater than the reset distance move opposite direction
	bMoveFoward = (dist >= ResetDistance) ? !bMoveFoward : bMoveFoward;

	// If distance is greater than the reset distance set to previous position 
	NewLocation = (dist >= ResetDistance) ? SavedLocation : NewLocation;

	//if (dist >= ResetDistance) {
	//	UE_LOG(LogTemp, Warning, TEXT("Euclidean distance before: %.1f"), dist)
	//	dist = FVector::Distance(InitialPosition, NewLocation);
	//	UE_LOG(LogTemp, Warning, TEXT("Euclidean distance after: %.1f"), dist)
	//}

	SetActorLocation(NewLocation);
}

void AMovingBouncePanel::BeginPlay()
{
	Super::BeginPlay();
	InitialPosition = GetActorLocation();
}

void AMovingBouncePanel::MoveForward(FVector& v, float DeltaSeconds)
{
		if (bMoveXDirection)
			v.X += ((ResetDistance / DistanceTravelTimeX) * DeltaSeconds);
		if (bMoveYDirection)
			v.Y += ((ResetDistance / DistanceTravelTimeY) * DeltaSeconds);
		if (bMoveZDirection)
			v.Z += ((ResetDistance / DistanceTravelTimeZ) * DeltaSeconds);
}

void AMovingBouncePanel::MoveBackward(FVector& v, float DeltaSeconds)
{
		if (bMoveXDirection)
			v.X -= ((ResetDistance / DistanceTravelTimeX) * DeltaSeconds);
		if (bMoveYDirection)
			v.Y -= ((ResetDistance / DistanceTravelTimeY) * DeltaSeconds);
		if (bMoveZDirection)
			v.Z -= ((ResetDistance / DistanceTravelTimeZ) * DeltaSeconds);
}
