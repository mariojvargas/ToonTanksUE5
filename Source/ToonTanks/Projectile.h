// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const float INITIAL_SPEED = 5000.f;
	const float MAX_SPEED = 10000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* ImpactParticles = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* TrailParticleSystem = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement = nullptr;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HittingComponent,	// component doing the hitting
		AActor* DamagedActor,					// actor that got hit
		UPrimitiveComponent* OtherComponent,	// static mesh component of component that was hit
		FVector NormalImpulse,					// if simulating physics, physics engine add impulse representing direction and magnitude
		const FHitResult& HitResult				// additional info about hit
	);
};
