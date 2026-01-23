// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ActionButtonStyleData.generated.h"


UENUM(BlueprintType)
enum class EActionButtonMode : uint8 {	
	IconOnly	UMETA(DisplayName = "IconOnly"),
	TextOnly	UMETA(DisplayName = "TextOnly"),
	IconText	UMETA(DisplayName = "IconText"),
	Auto		UMETA(DisplayName = "Auto")
};

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
	EActionButtonMode Mode = EActionButtonMode::Auto;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ActionButton")
	bool bEnabled = true;
};
