// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DefenseEconomySettings.generated.h"

/**
 * 
 */
UCLASS()
class CLICKERGAME_API UDefenseEconomySettings : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category="Economy")
	double VictoryReward = 100.0;
	
	UPROPERTY(EditDefaultsOnly, Category = "Economy")
	double DefeatReward = 50.0;
};
