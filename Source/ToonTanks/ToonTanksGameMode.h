// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank = nullptr;

	class AToonTanksPlayerController* ToonTanksPlayerController = nullptr;

	float StartDelay = 3.f;

	int32 CurrentEnemyTowerCount = 0;

	void HandleGameStart();

	int32 GetEnemyTowerCount();

	void RestartCurrentLevel();

	void RestartLevelAfterDelay();

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float GameRestartDelay = 5.f;
};
