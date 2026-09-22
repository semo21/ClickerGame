#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "GlobalEconomySnapshot.generated.h"

USTRUCT(BlueprintType)
struct FGlobalEconomySnapshot {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) double GlobalCurrency = 0.0;

};