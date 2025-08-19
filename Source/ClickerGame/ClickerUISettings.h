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
/**
 * 
 */
UCLASS()
class CLICKERGAME_API UClickerUISettings : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "UI") TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI") TSoftObjectPtr<UNiagaraSystem> ClickEffectAsset = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "UI") TSubclassOf<UIdleRewardTextWidget> IdleRewardTextWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "FX") TSubclassOf<UClickFloatingTextWidget> FloatingTextWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")	TSoftObjectPtr<USoundBase> ClickRewardSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound")	TSoftObjectPtr<USoundBase> OfflineRewardSound;
};
