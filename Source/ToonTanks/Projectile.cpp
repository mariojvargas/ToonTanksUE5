// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = INITIAL_SPEED;
	ProjectileMovement->MaxSpeed = MAX_SPEED;

	TrailParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticleSystem->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(
	UPrimitiveComponent* HittingComponent,
	AActor* DamagedActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse,
	const FHitResult& HitResult)
{
	if (!DamagedActor || DamagedActor == this)
	{
		Destroy();
		return;
	}
	
	auto ProjectileOwner = GetOwner();
	if (ProjectileOwner && ProjectileOwner != DamagedActor)
	{
		auto OwnerInstigator = ProjectileOwner->GetInstigatorController();
		auto DamageTypeClass = UDamageType::StaticClass();
		UGameplayStatics::ApplyDamage(DamagedActor, Damage, OwnerInstigator, this, DamageTypeClass);

		if (ImpactParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticles, GetActorLocation(), GetActorRotation());
		}
	}

	Destroy();		
}
