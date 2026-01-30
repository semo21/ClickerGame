// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Systems/UI/ActionButtonTypes.h"

#include "ActionButtonStyleData.generated.h"


UCLASS(BlueprintType)
class CLICKERGAME_API UActionButtonStyleData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ActionButton")
	FText LabelText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ActionButton")
	TObjectPtr<UTexture2D> IconTexture = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ActionButton")
	EActionButtonType Type = EActionButtonType::Auto;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ActionButton")
	bool bEnabled = true;
};
