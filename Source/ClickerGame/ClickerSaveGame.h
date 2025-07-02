// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ClickerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CLICKERGAME_API UClickerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float Currency;

	UPROPERTY()
	float CurrencyPerSecond;

	UPROPERTY()
	float CurrencyPerClick;

	UPROPERTY()
	int32 UpgradeLevel;
};
