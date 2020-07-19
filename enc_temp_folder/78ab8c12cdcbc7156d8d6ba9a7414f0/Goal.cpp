#include "Goal.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "TrickShotProjectile.h"
#include "BouncePanel.h"
#include "Kismet/GameplayStatics.h"
#include "TrickShotGameMode.h"

AGoal::AGoal()
{
	//PrimaryActorTick.bCanEverTick = true;

	// Initialize the overlap component
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(200.0f, 200.0f, 50.0f));
	OverlapComp->SetHiddenInGame(true);
	RootComponent = OverlapComp;
	OverlapComp->OnComponentHit.AddDynamic(this, &AGoal::HandleOverlap);

	// Setup mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(OverlapComp);
}

void AGoal::HandleOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if all panels are set
	if (AreAllPanelsSet()) {
		ATrickShotGameMode* GM = Cast<ATrickShotGameMode>(GetWorld()->GetAuthGameMode());
		if (GM) // if so then player has completed the level
			GM->CompleteLevel();
		else
			UE_LOG(LogTemp, Warning, TEXT("GM is nullptr"))
	} else {
		// if panels are not set make an error noise
		UGameplayStatics::PlaySound2D(this, GoalIncomplete);
	}
}

bool AGoal::AreAllPanelsSet()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABouncePanel::StaticClass(), Actors);
	int PanelReady = 0;

	for (auto Actor : Actors) {
		ABouncePanel* Panel = Cast<ABouncePanel>(Actor);
		if (Panel && Panel->bPanelSetReset)
			PanelReady++;
	}

	bool bAllPanelsSet = PanelReady == Actors.Num();

	if (bAllPanelsSet)
		ChangeColor();

	return bAllPanelsSet;
}

//void AGoal::Tick(float DeltaSeconds)
//{
//	Super::Tick(DeltaSeconds);
//
//	FQuat QuatRotation = FQuat(FRotator(0.f, YawValue * DeltaSeconds, 0.f));
//
//	AddActorLocalRotation(QuatRotation);
//}
