#pragma once

#include "CoreMinimal.h"

#include "EconomySnapshot.generated.h"

USTRUCT(BlueprintType)
struct FEconomySnapshot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32  UpgradeLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double Currency = 0.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double CurrencyPerClick = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double CurrencyPerSecond = 2.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double UpgradeCostBase = 10.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double UpgradeGrowth = 1.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int64  LastSaveTime = 0;

};
