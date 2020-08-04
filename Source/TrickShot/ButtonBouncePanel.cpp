#include "ButtonBouncePanel.h"

void AButtonBouncePanel::BeginPlay()
{
	Super::BeginPlay();

	// Location1 is the initial location
	Location1 = GetActorLocation();

	// Location2 is what the user chooses
	Location2.X = m_X;
	Location2.Y = m_Y;
	Location2.Z = m_Z;

	// Teleport to location 2 
	TeleLocationTwo();
}

void AButtonBouncePanel::TeleLocationOne()
{
	SetActorLocation(Location1);
}

void AButtonBouncePanel::TeleLocationTwo()
{
	SetActorLocation(Location2);
}
