// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonTimer.generated.h"

class UBoxComponent;

UCLASS()
class TRICKSHOT_API AButtonTimer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonTimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BaseComp;

	UPROPERTY(EditDefaultsOnly, Category = "Time")
	float TimeForButtonReset;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ButtonSetSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ButtonResetSound;

	UPROPERTY(EditDefaultsOnly, Category = "Name")
	FString PanelName;

	// Change panel back to original location and reset button color
	virtual void RevertChange();

	// Timer for button reset
	FTimerHandle TimerHandle_ButtonTimer;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* ButtonComp;

	UFUNCTION()
    virtual void HandleOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// button is either red or green
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	bool bButtonColorRed;

	UFUNCTION(BlueprintImplementableEvent, Category = "Color")
	void UpdateColor();

private:
};
