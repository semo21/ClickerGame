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
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	TSubclassOf<ADefenseEnemyBase> EnemyClass;
	void SpawnEnemy();

private:
	void HandleEnemyReachedGoal();

	UPROPERTY(EditDefaultsOnly, Category = "Rules")
	int32 StartLives = 10;

	UPROPERTY(VisibleInstanceOnly, Category = "Rules")
	int32 CurrentLives = 0;
};
