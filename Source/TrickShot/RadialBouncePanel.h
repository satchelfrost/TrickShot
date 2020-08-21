// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BouncePanel.h"
#include "RadialBouncePanel.generated.h"

/**
 * 
 */
UCLASS()
class TRICKSHOT_API ARadialBouncePanel : public ABouncePanel
{
	GENERATED_BODY()

public:
	ARadialBouncePanel();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	FVector Center;
	FVector CurrPosition;


	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float Speed;

	UPROPERTY(EditDefaultsOnly, Category = "Geometry")
	float Radius;

public:
	void Orbit();
	
};
