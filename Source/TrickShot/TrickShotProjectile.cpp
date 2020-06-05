// Copyright Epic Games, Inc. All Rights Reserved.

//#include <chrono>
#include "TrickShotProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TrickShotCharacter.h"
#include "Goal.h"

ATrickShotProjectile::ATrickShotProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(150.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ATrickShotProjectile::OnHit);

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
	
	// capture the start time 
	OnHitPreviousCall = std::chrono::steady_clock::now();

	// Default time interval to cancel noise in between hits
	NoiseCancelTimeThreshold = 100.0f;
}

void ATrickShotProjectile::SetProjectileMovementSpeed(float speed)
{
	ProjectileMovement->InitialSpeed = speed;
	ProjectileMovement->MaxSpeed = speed;
}

void ATrickShotProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))// && OtherComp->IsSimulatingPhysics())
	{
		if (OtherComp->IsSimulatingPhysics())
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		// If projectile hits the player destroy
		ATrickShotCharacter* Player = Cast<ATrickShotCharacter>(OtherActor);
		if (Player) {
			Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Ball destroyed because of player overlap"))
			return;
		}

		// If projectile his the goal then destroy and return;	
		AGoal* Goal = Cast<AGoal>(OtherActor);
		if (Goal) {
			Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Ball destroyed because of goal overlap"))
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
			return;
		}

		// calculate elapsed time of last function call
		auto OnHitCurrentCall = std::chrono::steady_clock::now();
		auto diff = OnHitCurrentCall - OnHitPreviousCall;
		auto ElapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
		if (ElapsedTime > NoiseCancelTimeThreshold) // Prevents tons of bouncy noises
			UGameplayStatics::PlaySound2D(this, PingPongSound);
		OnHitPreviousCall = OnHitCurrentCall;
	}
}

void ATrickShotProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
