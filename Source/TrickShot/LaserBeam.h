// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserBeam.generated.h"

class UParticleSystemComponent;
class UBoxComponent;

UCLASS()
class TRICKSHOT_API ALaserBeam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserBeam();
	
	UFUNCTION()
    void HandleOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Name")
	FString LaserName;

	void DisableLaser();

	void EnableLaser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp1;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp2;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USceneComponent* SceneComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UParticleSystemComponent* LaserBeam;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UBoxComponent* OverlapComp;


};
