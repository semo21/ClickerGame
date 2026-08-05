// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "GameplayTagContainer.h"
#include "Systems/UI/Types/ActionButtonTypes.h"

#include "ActionButtonDefinition.generated.h"

USTRUCT(BlueprintType)
struct FActionButtonDefinition {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActionButton")
	FText LabelText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActionButton")
	TSoftObjectPtr<UTexture2D> IconTexture = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActionButton")
	EActionButtonMode Mode = EActionButtonMode::Auto;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActionButton")
	bool bDefaultEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActionButton")
	FText TooltipText;
};
