// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefenseEnemyBase.generated.h"

class UStaticMeshComponent;
class ADefenseGridManager;

UCLASS()
class CLICKERGAME_API ADefenseEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefenseEnemyBase();
	void InitPath(ADefenseGridManager* InGrid);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, Category="Enemy")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category="Enemy")
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(EditAnywhere, Category="Enemy")
	float MoveSpeed = 100.0f;

	UPROPERTY(VisibleInstanceOnly, Category="Enemy")
	TArray<int32> CurrentPath;

	UPROPERTY(VisibleInstanceOnly, Category="Enemy")
	TObjectPtr<ADefenseGridManager> GridManager;

	int32 PathStep = 1;
	

private:

};
