// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonTimer.h"
#include "LaserButtonTimer.generated.h"

/**
 * 
 */
UCLASS()
class TRICKSHOT_API ALaserButtonTimer : public AButtonTimer
{
	GENERATED_BODY()
public:
	ALaserButtonTimer();

    virtual void HandleOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Name")
	FString LaserName;

	// Re-enstate lasers and change button color back
	virtual void RevertChange() override;

	
};
