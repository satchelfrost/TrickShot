// Fill out your copyright notice in the Description page of Project Settings.

#include "ButtonTimer.h"
#include "Components/BoxComponent.h"
#include "TrickShotProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "ButtonBouncePanel.h"

// Sets default values
AButtonTimer::AButtonTimer()
{
	// Initialize the overlap component
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(200.0f, 200.0f, 50.0f));
	OverlapComp->SetHiddenInGame(true);
	RootComponent = OverlapComp;
	OverlapComp->OnComponentHit.AddDynamic(this, &AButtonTimer::HandleOverlap);

	// Our button timer consists of the button and the base of the button
	ButtonComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonComp"));
	ButtonComp->SetupAttachment(OverlapComp);
	BaseComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseComp"));
	BaseComp->SetupAttachment(OverlapComp);

	// true means button is red
	bButtonColorRed = true;

	// Amount of time before button changes color
	TimeForButtonReset = 2.0f;
}

// Called when the game starts or when spawned
void AButtonTimer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AButtonTimer::RevertChange()
{
	// Set button color back to red
	bButtonColorRed = true;

	UE_LOG(LogTemp, Warning, TEXT("button color change back red %d"), bButtonColorRed)

	// Update the color of this object
	UpdateColor();

	// Specify behavior for the change back to original state of the other actor 
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AButtonBouncePanel::StaticClass(), Actors);
	for (auto Actor : Actors) {
		AButtonBouncePanel* Panel = Cast<AButtonBouncePanel>(Actor);
		if (PanelName == Panel->PanelName)
			Panel->TeleLocationTwo();
	}
}

void AButtonTimer::HandleOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ATrickShotProjectile* ball = Cast<ATrickShotProjectile>(OtherActor);
	if (ball) {

		// specify behavior for the change of other actor 
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AButtonBouncePanel::StaticClass(), Actors);
		for (auto Actor : Actors) {
			AButtonBouncePanel* Panel = Cast<AButtonBouncePanel>(Actor);
			if (PanelName == Panel->PanelName)
				Panel->TeleLocationOne();
		}

		// Set button to green color (or not red)
		bButtonColorRed = false;

		UE_LOG(LogTemp, Warning, TEXT("button color red %d"), bButtonColorRed)

		// Update color of this object
		UpdateColor();

		// Set timer
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_ButtonTimer, this, &AButtonTimer::RevertChange, TimeForButtonReset);
	}
}
