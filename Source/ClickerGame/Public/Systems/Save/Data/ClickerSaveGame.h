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
	UPROPERTY(SaveGame)	double Currency = 0.0;
	UPROPERTY(SaveGame)	double CurrencyPerClick = 0.0;
	UPROPERTY(SaveGame)	double CurrencyPerSecond = 0.0;
	UPROPERTY(SaveGame)	int32 UpgradeLevel = 0;
	UPROPERTY(SaveGame)	int64 LastSaveUnixTime = 0;
};
