// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionButtonTypes.generated.h"
/**
 * 
 */

UENUM(BlueprintType)
enum class EActionButtonType : uint8 {
	IconOnly	UMETA(DisplayName = "IconOnly"),
	TextOnly	UMETA(DisplayName = "TextOnly"),
	IconText	UMETA(DisplayName = "IconText"),
	Auto		UMETA(DisplayName = "Auto")
};
