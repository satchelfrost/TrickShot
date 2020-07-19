// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

class UBoxComponent;
class USphereComponent;

UCLASS()
class TRICKSHOT_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	AGoal();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
    void HandleOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
    bool AreAllPanelsSet();

	UFUNCTION(BlueprintImplementableEvent, Category = "Color")
	void ChangeColor();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* GoalComplete;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* GoalIncomplete;

	// Testing out rotation
	//UPROPERTY(EditDefaultsOnly, Category = "Movement")
	//float YawValue;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Goal")
	bool bGoalReady;


public:
	//virtual void Tick(float DeltaSeconds) override;
};
