// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DefenseUISettings.generated.h"


class UDefenseResultWidget;
/**
 *
 */
UCLASS()
class CLICKERGAME_API UDefenseUISettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UDefenseResultWidget> ResultWidgetClass;
};