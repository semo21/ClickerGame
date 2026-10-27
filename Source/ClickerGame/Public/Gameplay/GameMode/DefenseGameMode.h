// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/GameMode/MyGameModeBase.h"

#include "DefenseGameMode.generated.h"

class ADefenseEnemyBase;
/**
 *
 */
UCLASS()
class CLICKERGAME_API ADefenseGameMode : public AMyGameModeBase
{
	GENERATED_BODY()
public:
	ADefenseGameMode();

protected:
	virtual void BeginPlay() override;


private:
	UFUNCTION()
	void HandleEnemyDestroyed(AActor* DestroyedActor);

	void StartWave();
	void HandleSpawnTick();
	void HandleEnemyReachedGoal();
	void HandleWaveCleared();
	void SpawnEnemy();
	bool IsWaveCleared() const;	

	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	TSubclassOf<ADefenseEnemyBase> EnemyClass;

	UPROPERTY(EditDefaultsOnly, Category = "Rules")
	int32 StartLives = 10;

	UPROPERTY(VisibleInstanceOnly, Category = "Rules")
	int32 CurrentLives = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	int32 BaseEnemyCount = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	int32 EnemyCountPerWave = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	float SpawnInterval = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	int32 MaxWaves = 3;

	UPROPERTY(VisibleInstanceOnly, Category = "Wave")
	int32 CurrentWave = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "Wave")
	int32 EnemiesLeftToSpawn = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "Wave")
	TArray<TObjectPtr<ADefenseEnemyBase>> AliveEnemies;

	FTimerHandle SpawnTimerHandle;
	
};
