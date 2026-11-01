#pragma once

#include "CoreMinimal.h"
#include "DefenseTypes.generated.h"

UENUM()
enum class EDefenseMatchState : uint8 {
	InProgress,
	Victory,
	Defeat
};