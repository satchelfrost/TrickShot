// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBeam.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TrickShotProjectile.h"

// Sets default values
ALaserBeam::ALaserBeam()
{

	// Set up scene component
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	// Set up the mesh components (i.e. where laser emits from)
	MeshComp1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp1"));
	MeshComp1->SetupAttachment(SceneComp);
	//MeshComp1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp2"));
	MeshComp2->SetupAttachment(SceneComp);
	//MeshComp2->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Set up the box trigger
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(200.0f, 50.0f, 50.0f));
	OverlapComp->SetHiddenInGame(true);
	OverlapComp->SetupAttachment(SceneComp);
	OverlapComp->OnComponentHit.AddDynamic(this, &ALaserBeam::HandleOverlap);

	// Particle system
	LaserBeam = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	LaserBeam->SetupAttachment(SceneComp);
	LaserBeam->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ALaserBeam::HandleOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ATrickShotProjectile* ball = Cast<ATrickShotProjectile>(OtherActor);

	if (ball) {
		ball->DestroyWithFlames();
	}
}

void ALaserBeam::DisableLaser()
{
	LaserBeam->SetBeamTargetPoint(0, MeshComp1->GetComponentLocation(), 0);
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ALaserBeam::EnableLaser()
{

	LaserBeam->SetBeamTargetPoint(0, MeshComp2->GetComponentLocation(), 0);
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void ALaserBeam::BeginPlay()
{
	Super::BeginPlay();
	LaserBeam->SetBeamSourcePoint(0, MeshComp1->GetComponentLocation(), 0);
	LaserBeam->SetBeamTargetPoint(0, MeshComp2->GetComponentLocation(), 0);
}

//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaserBeam, GetActorLocation());
//UGameplayStatics::PlaySound2D(this, ExplosionSound);
