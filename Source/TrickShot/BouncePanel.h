// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BouncePanel.generated.h"

class UBoxComponent;
//class UMaterialInterface;

UCLASS()
class TRICKSHOT_API ABouncePanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABouncePanel();

	bool bPanelSetReset;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

//	UPROPERTY(EditDefaultsOnly, Category = "Materials")
//	UMaterialInterface* Material;



	UFUNCTION()
    void HandleOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
