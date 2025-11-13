// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ClickerUISettings.generated.h"

class UUserWidget;
class UIdleRewardTextWidget;
class UClickFloatingTextWidget;
class UNiagaraSystem;
class USoundBase;
class UToastWidgetBase;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API UClickerUISettings : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "UI") TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "FX") TSoftObjectPtr<UNiagaraSystem> ClickEffectAsset = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "UI") TSubclassOf<UToastWidgetBase> IdleRewardTextWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI") TSubclassOf<UToastWidgetBase> FloatingTextWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")	TSoftObjectPtr<USoundBase> ClickRewardSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")	TSoftObjectPtr<USoundBase> OfflineRewardSound;
};
