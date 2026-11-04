// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DefenseTowerBase.generated.h"

class UStaticMeshComponent;
class ADefenseEnemyBase;

UCLASS()
class CLICKERGAME_API ADefenseTowerBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADefenseTowerBase();

protected:
	virtual void BeginPlay() override;
	virtual void Attack();
	virtual ADefenseEnemyBase* FindTarget() const;

	UPROPERTY(VisibleAnywhere, Category = "Tower")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "Tower")
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(EditAnywhere, Category = "Tower")
	float Range = 250.0f;

	UPROPERTY(EditAnywhere, Category = "Tower")
	float Damage = 25.0f;
	
	UPROPERTY(EditAnywhere, Category = "Tower")
	float AttackInterval = 1.0f;

private:
	FTimerHandle AttackTimerHandle;
};
