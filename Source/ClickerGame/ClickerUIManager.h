// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "ClickerUIManager.generated.h"

class UClickerComponent;
class AMyPlayerController;
class UClickFloatingTextWidget;
class UIdleRewardTextWidget;
class USoundBase;
class UGameManager;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API UClickerUIManager : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	UUserWidget* GetHUDWidget() const;

	void Initialize(UGmaeManager* InGameManager);
	void InitializeWidgetPool();
	void ShowFloatingText(const FString& Message, const FVector& WorldLocation);
	void ShowClickEffect(const FVector& WorldLocation);
	void ShowHUD();
	void HideHUD();	
	void UpdateScore();
	void ShowUpgradeSuccessText();
	void HideUpgradeSuccessText();
	void SetClickerComponent(UClickerComponent* Comp);
	void ShowIdleReward(float Amount);
	void ShowOfflineReward(float OfflineReward);
	UIdleRewardTextWidget* GetRewardWidgetFromPool();

private:
	UPROPERTY()
	UGameManager* GameManager;

	UPROPERTY()
	AMyPlayerController* PlayerController;

	UPROPERTY()
	AActor* CurrentClickEffect = nullptr;

	UPROPERTY()
	UNiagaraSystem* ClickEffectAsset;

	UPROPERTY()
	UUserWidget* HUDWidget;

	UPROPERTY()
	UTextBlock* CurrencyText;

	UPROPERTY()
	UTextBlock* ClickValueText;

	UPROPERTY()
	UTextBlock* UpgradeCostText;

	UPROPERTY()
	UTextBlock* PassiveIncomeText;

	UPROPERTY()
	UTextBlock* UpgradeSuccessText;

	UPROPERTY()
	UButton* UpgradeButton;

	UPROPERTY()
	UButton* SaveButton;

	UPROPERTY()
	UButton* LoadButton;

	UPROPERTY()
	FTimerHandle UpgradeSuccessTimerHandle;

	UPROPERTY()
	UClickerComponent* ClickerComponent;

	UPROPERTY()
	TArray<UIdleRewardTextWidget*> RewardTextPool;

	UFUNCTION()
	UClickFloatingTextWidget* GetFloatingTextWidgetFromPool();

	FVector2D CachedViewportSize;
	TSubclassOf<UClickFloatingTextWidget> FloatingTextWidgetClass;
	TArray<UClickFloatingTextWidget*> FloatingTextPool;
	TSubclassOf<UIdleRewardTextWidget> IdleRewardTextWidgetClass;
	FTimerHandle TimerHandle;
	TSubclassOf<UUserWidget> HUDWidgetClass;

	void InitSoundSource();
};
