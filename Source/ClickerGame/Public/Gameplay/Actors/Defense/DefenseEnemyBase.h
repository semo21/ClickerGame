// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefenseEnemyBase.generated.h"

class UStaticMeshComponent;
class ADefenseGridManager;

DECLARE_MULTICAST_DELEGATE(FOnDefenseEnemyReachedGoal);

UCLASS()
class CLICKERGAME_API ADefenseEnemyBase : public AActor
{
	GENERATED_BODY()

public:
	ADefenseEnemyBase();
	void InitPath(ADefenseGridManager* InGrid);
	int32 GetTargetTileIndex() const { return CurrentPath.IsValidIndex(PathStep) ? CurrentPath[PathStep] : INDEX_NONE; };
	virtual void Tick(float DeltaTime) override;

	FOnDefenseEnemyReachedGoal OnReachedGoal;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float MoveSpeed = 100.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Enemy")
	TArray<int32> CurrentPath;

	UPROPERTY(VisibleInstanceOnly, Category = "Enemy")
	TObjectPtr<ADefenseGridManager> GridManager;

	int32 PathStep = 1;

private:
	void HandlePathChanged();
};
