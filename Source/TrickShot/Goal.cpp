// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal.h"
#include "Components/BoxComponent.h"
#include "TrickShotProjectile.h"
#include "BouncePanel.h"
#include "Kismet/GameplayStatics.h"
#include "TrickShotGameMode.h"

// Sets default values
AGoal::AGoal()
{
	// Initialize the overlap component
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(200.0f, 200.0f, 50.0f));
	OverlapComp->SetHiddenInGame(true);
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

	// Get all of the bounce panels
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABouncePanel::StaticClass(), Actors);
	int PanelReady = 0;

	for (auto Actor : Actors) {
		ABouncePanel* Panel = Cast<ABouncePanel>(Actor);
		if (Panel && Panel->bPanelSetReset)
			PanelReady++;
	}

	if (PanelReady == Actors.Num()) {
		UGameplayStatics::PlaySound2D(this, GoalComplete);
		ATrickShotGameMode* GM = Cast<ATrickShotGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
			GM->CompleteLevel();
		else
			UE_LOG(LogTemp, Warning, TEXT("GM is nullptr"))
	} else {
		UGameplayStatics::PlaySound2D(this, GoalIncomplete);
	}
}
