// Fill out your copyright notice in the Description page of Project Settings.


#include "RadialBouncePanel.h"
#include "Math/UnrealMathUtility.h"

ARadialBouncePanel::ARadialBouncePanel()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARadialBouncePanel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Orbit();
}

void ARadialBouncePanel::BeginPlay()
{
	Super::BeginPlay();
	Center = GetActorLocation();
	CurrPosition = GetActorLocation();
}

void ARadialBouncePanel::Orbit()
{
	float s; // sine
	float c; // cosine
	float time = GetWorld()->GetRealTimeSeconds();
	FMath::SinCos(&s, &c, time * Speed);
	float xAmt = Radius * s;
	float yAmt = Radius * c;
	CurrPosition.X = Center.X + xAmt;
	CurrPosition.Y = Center.Y + yAmt;
	SetActorLocation(CurrPosition);
}
