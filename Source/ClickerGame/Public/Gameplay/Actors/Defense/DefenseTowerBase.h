// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DefenseTowerBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class CLICKERGAME_API ADefenseTowerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefenseTowerBase();

protected:
	UPROPERTY(VisibleAnywhere, Category="Tower")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category="Tower")
	TObjectPtr<UStaticMeshComponent> Body;
};
