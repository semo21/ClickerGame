#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "MetaEconomySnapshot.generated.h"

USTRUCT(BlueprintType)
struct FMetaEconomySnapshot {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) double GlobalCurrency = 0.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTagContainer UnlockedLevels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTagContainer UnlockedGlobalUpgrades;
};