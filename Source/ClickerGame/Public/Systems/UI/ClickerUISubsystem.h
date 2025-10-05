// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "ClickerUISubsystem.generated.h"

class USoundBase; class UUserWidget; class UButton;
class UTextBlock; class UNiagaraSystem;

class UClickerEconomySubsystem; class AMyPlayerController;
class UClickFloatingTextWidget; class UIdleRewardTextWidget;
struct FEconomySnapshot;		class UClickerUISettings;
/**
 *
 */
UCLASS(Config=Game, DefaultConfig)
class CLICKERGAME_API UClickerUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void ShowHUD(UWorld* World);
	void ShowFloatingText(const FString& Message, const FVector& WorldLocation);
	void ShowIdleReward(float Amount);
	void ShowClickEffect(const FVector& WorldLocation);
	void ShowOfflineReward(float OfflineReward);
	void ShowUpgradeSuccessText();
	void HideUpgradeSuccessText();

	UFUNCTION()	void OnEconomyChanged(const FEconomySnapshot& Snapshot);
	UFUNCTION() void OnPassiveIncome(double AmountPerSec);
	UFUNCTION() void OnOfflineReward(double Amount);

	UPROPERTY(Config, EditAnywhere, Category = "Settings")	TSoftObjectPtr<UClickerUISettings> UISettingsAsset;
	UPROPERTY() TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY() UNiagaraSystem* ClickEffectAsset = nullptr;
	UPROPERTY() TSubclassOf<UIdleRewardTextWidget> IdleRewardTextWidgetClass;
	UPROPERTY() TSubclassOf<UClickFloatingTextWidget> FloatingTextWidgetClass;
	UPROPERTY()	USoundBase* ClickRewardSound = nullptr;
	UPROPERTY()	USoundBase* OfflineRewardSound = nullptr;

private:
	void UpdateScore(const FEconomySnapshot& S);
	UClickFloatingTextWidget* GetFloatingTextWidgetFromPool();
	UIdleRewardTextWidget* GetRewardWidgetFromPool();

	UPROPERTY()	UUserWidget* HUDWidget;
	UPROPERTY()	UTextBlock* CurrencyText;
	UPROPERTY()	UTextBlock* ClickValueText;
	UPROPERTY()	UTextBlock* UpgradeCostText;
	UPROPERTY()	UTextBlock* PassiveIncomeText;
	UPROPERTY()	UTextBlock* UpgradeSuccessText;
	UPROPERTY()	UButton* UpgradeButton;
	UPROPERTY()	UButton* SaveButton;
	UPROPERTY()	UButton* LoadButton;
	UPROPERTY() TArray<UClickFloatingTextWidget*> FloatingTextPool;
	UPROPERTY()	TArray<UIdleRewardTextWidget*> RewardTextPool;	
	FTimerHandle UpgradeSuccessTimerHandle;
	TWeakObjectPtr<APlayerController> PlayerController;
	TObjectPtr<UClickerEconomySubsystem> EconomySubsystemRef = nullptr;
	FVector2D CachedViewportSize = FVector2D::ZeroVector;
};
