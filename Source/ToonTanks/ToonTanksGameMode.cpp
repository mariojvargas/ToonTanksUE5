// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    int32 MainPlayerIndex = 0;

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, MainPlayerIndex));
    
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(
        UGameplayStatics::GetPlayerController(this, MainPlayerIndex));

    CurrentEnemyTowerCount = GetEnemyTowerCount();

    HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }

        GameOver(false);
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        CurrentEnemyTowerCount--;

        if (CurrentEnemyTowerCount == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::HandleGameStart()
{
    StartGame();

    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
        );

        FTimerHandle PlayerEnableTimerHandle;
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
    }
}

int32 AToonTanksGameMode::GetEnemyTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);

    return Towers.Num();
}
