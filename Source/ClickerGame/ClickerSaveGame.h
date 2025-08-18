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
	UPROPERTY()	double Currency;
	UPROPERTY()	double CurrencyPerClick;
	UPROPERTY()	double CurrencyPerSecond;
	UPROPERTY()	int32 UpgradeLevel;
	UPROPERTY()	int64 LastSaveUnixTime = 0;
};
