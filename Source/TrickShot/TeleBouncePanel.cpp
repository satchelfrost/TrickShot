// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleBouncePanel.h"

ATeleBouncePanel::ATeleBouncePanel()
{
}

void ATeleBouncePanel::BeginPlay()
{
	Super::BeginPlay();

	// Location1 is the initial location
	Location1 = GetActorLocation();

	// Location2 is what the user chooses
	Location2.X = m_X;
	Location2.Y = m_Y;
	Location2.Z = m_Z;

	// Teleport to location 1 
	TeleLocationOne();
}

void ATeleBouncePanel::TeleLocationOne()
{
	SetActorLocation(Location1);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Teleport, this, &ATeleBouncePanel::TeleLocationTwo, WaitTime);
}

void ATeleBouncePanel::TeleLocationTwo()
{
	SetActorLocation(Location2);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Teleport, this, &ATeleBouncePanel::TeleLocationOne, WaitTime);
}
