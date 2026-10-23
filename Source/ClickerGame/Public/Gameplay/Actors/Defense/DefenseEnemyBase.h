// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefenseEnemyBase.generated.h"

struct FDamageEvent;

class UStaticMeshComponent;
class ADefenseGridManager;

DECLARE_MULTICAST_DELEGATE(FOnDefenseEnemyReachedGoal);

UCLASS()
class CLICKERGAME_API ADefenseEnemyBase : public AActor
{
	GENERATED_BODY()

public:
	ADefenseEnemyBase();
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void InitPath(ADefenseGridManager* InGrid);
	int32 GetTargetTileIndex() const { return CurrentPath.IsValidIndex(PathStep) ? CurrentPath[PathStep] : INDEX_NONE; };


	FOnDefenseEnemyReachedGoal OnReachedGoal;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Enemy")	
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(VisibleAnywhere, Category = "Enemy")	
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleInstanceOnly, Category = "Enemy")	
	TArray<int32> CurrentPath;
	UPROPERTY(VisibleInstanceOnly, Category = "Enemy")	
	TObjectPtr<ADefenseGridManager> GridManager;
	int32 PathStep = 1;

	UPROPERTY(EditAnywhere, Category = "Enemy")	
	float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Enemy")	
	float MaxHP = 100.0f;
	UPROPERTY(VisibleInstanceOnly, Category = "Enemy")	
	float CurrentHP = 0.0f;

private:
	void HandlePathChanged();
};
