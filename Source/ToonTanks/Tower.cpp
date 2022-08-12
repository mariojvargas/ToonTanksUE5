// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(
        FireRateTimerHandle,
        this, 
        &ATower::CheckFireCondition, 
        FireRate, 
        true
    );
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (IsTankWithinFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

bool ATower::IsTankWithinFireRange() const
{
    return Tank != nullptr 
        && FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
}

void ATower::CheckFireCondition()
{
    if (IsTankWithinFireRange())
    {
        Fire();
    }
}