// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal.h"
#include "Components/BoxComponent.h"
#include "TrickShotProjectile.h"

// Sets default values
AGoal::AGoal()
{
	// Initialize the overlap component
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(200.0f, 200.0f, 50.0f));
	OverlapComp->SetHiddenInGame(false);
	//OverlapComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = OverlapComp;
	OverlapComp->OnComponentHit.AddDynamic(this, &AGoal::HandleOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(OverlapComp);
}

void AGoal::HandleOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ATrickShotProjectile* ball = Cast<ATrickShotProjectile>(OtherActor);
	if (ball) {
		UE_LOG(LogTemp, Warning, TEXT("Ball has landed"))
	}
}
