// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LaserButtonTimer.h"
#include "SpinningLaserButtonTimer.generated.h"

/**
 * 
 */
UCLASS()
class TRICKSHOT_API ASpinningLaserButtonTimer : public ALaserButtonTimer
{
	GENERATED_BODY()

public:
	ASpinningLaserButtonTimer();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float PitchValue;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float YawValue;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RollValue;

public:
	virtual void Tick(float DeltaSeconds) override;
	
};
