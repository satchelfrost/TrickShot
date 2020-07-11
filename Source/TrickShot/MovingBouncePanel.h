// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BouncePanel.h"
#include "MovingBouncePanel.generated.h"

/**
 * 
 */
UCLASS()
class TRICKSHOT_API AMovingBouncePanel : public ABouncePanel
{
	GENERATED_BODY()


public:
	AMovingBouncePanel();

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float ResetDistance;

	// X, Y, and Z directions movement enabled
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bMoveXDirection;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bMoveYDirection;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bMoveZDirection;

	// Time spent traveling in a direction
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float DistanceTravelTimeX;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float DistanceTravelTimeY;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float DistanceTravelTimeZ;

	virtual void BeginPlay() override;
private:
	FVector InitialPosition;

	bool bMoveFoward; // Note: "Forward" relatively speaking

	void MoveForward(FVector& v, float DeltaSeconds);  // Note: "Forward" relatively speaking
	void MoveBackward(FVector& v, float DeltaSeconds); // Note: "Backward" relatively speaking
};
