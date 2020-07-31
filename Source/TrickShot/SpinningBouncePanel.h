// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BouncePanel.h"
#include "SpinningBouncePanel.generated.h"

/**
 * 
 */
UCLASS()
class TRICKSHOT_API ASpinningBouncePanel : public ABouncePanel
{
	GENERATED_BODY()
public:
	ASpinningBouncePanel();

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
