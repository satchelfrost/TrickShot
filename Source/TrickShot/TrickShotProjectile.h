// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <chrono>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrickShotProjectile.generated.h"

UCLASS(config=Game)
class ATrickShotProjectile : public AActor
{

	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:
	ATrickShotProjectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* PingPongSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	float NoiseCancelTimeThreshold;

	std::chrono::steady_clock::time_point OnHitPreviousCall;
};

