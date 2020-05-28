// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncePanel.h"
#include "Components/BoxComponent.h"
#include "TrickShotProjectile.h"

// Sets default values
ABouncePanel::ABouncePanel()
{
	// State of panel, hit or not 
	bPanelSetReset = false;

	// Initialize the overlap component
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(200.0f, 200.0f, 50.0f));
	OverlapComp->SetHiddenInGame(true);
	RootComponent = OverlapComp;
	OverlapComp->OnComponentHit.AddDynamic(this, &ABouncePanel::HandleOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(OverlapComp);

}


void ABouncePanel::HandleOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ATrickShotProjectile* ball = Cast<ATrickShotProjectile>(OtherActor);
	if (ball) {
		bPanelSetReset = !bPanelSetReset;
		FString set = "set";
		FString reset = "reset";
		UE_LOG(LogTemp, Warning, TEXT("Panel has been %s"), (bPanelSetReset) ? *set : *reset) 
	}
}