// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonTimer.h"
#include "SpinningButtonTimer.generated.h"

/**
 * 
 */
UCLASS()
class TRICKSHOT_API ASpinningButtonTimer : public AButtonTimer
{
	GENERATED_BODY()

public:
	ASpinningButtonTimer();
	
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
