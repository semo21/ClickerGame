#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "GlobalProgressSnapshot.generated.h"

USTRUCT(BlueprintType)
struct FGlobalProgressSnapshot {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTagContainer UnlockedLevels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTagContainer UnlockedGlobalUpgrades;
};
