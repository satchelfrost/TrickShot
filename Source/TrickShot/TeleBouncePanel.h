// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BouncePanel.h"
#include "TeleBouncePanel.generated.h"

/**
 * 
 */
UCLASS()
class TRICKSHOT_API ATeleBouncePanel : public ABouncePanel
{
	GENERATED_BODY()

public:
	ATeleBouncePanel();

protected:
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle_Teleport;

	void TeleLocationOne();
	void TeleLocationTwo();

	FVector Location1;
	FVector Location2;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float m_X;
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float m_Y;
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float m_Z;

	// Time to wait in between teleportations
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float WaitTime;
};
