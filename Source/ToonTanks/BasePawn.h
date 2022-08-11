// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// UPROPERTY(VisibleInstanceOnly)
	// int32 VisibleInstanceOnly = 1792;

	// UPROPERTY(VisibleDefaultsOnly)
	// int32 VisibleDefaultsOnlyInt = 85;

	// UPROPERTY(EditDefaultsOnly)
	// int32 EditDefaultsOnlyInt = 50;

	// UPROPERTY(EditInstanceOnly)
	// int32 EditInstanceOnlyInt = 32;

	// UPROPERTY(EditAnywhere)
	// float Mana = 100.f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Super Duper", meta = (AllowPrivateAccess = "true"))
	// int32 VisibleAnywhereInt = 12;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Super Duper", meta = (AllowPrivateAccess = "true"))
	// int32 EditAnywhereInt = 42;
};
