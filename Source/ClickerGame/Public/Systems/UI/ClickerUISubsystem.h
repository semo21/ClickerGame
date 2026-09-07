// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "Systems/Economy/Data/EconomySnapshot.h"

#include "ClickerUISubsystem.generated.h"

class USoundBase;				class UUserWidget; 
class UButton;					class UTextBlock; 
class UNiagaraSystem;

class UClickerEconomySubsystem; class AMyPlayerController;
class UClickFloatingTextWidget; class UIdleRewardTextWidget;
class UClickerUISettings;		class UToastWidgetBase;			
class UActionButtonRegistry;	

struct FEconomySnapshot;		struct FActionButtonDefinition;

// Economy changed event for UI, passes the new snapshot to update displays
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEconomyChangedUI, const FEconomySnapshot&, Snapshot);

UCLASS(Config=Game, DefaultConfig)
class CLICKERGAME_API UClickerUISubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void BindEconomySubsystem(UClickerEconomySubsystem* Eco);
	void ShowHUD(UWorld* World);
	void ShowFloatingText(const FString& Message, const FVector& WorldLocation);
	void ShowReward(double Amount, bool bIsOffline);
	void ShowClickEffect(const FVector& WorldLocation);
	void ShowOfflineReward(float OfflineReward);
	void ShowUpgradeSuccessText();
	void HideUpgradeSuccessText();
	const FActionButtonDefinition* FindActionButtonDefinition(const FGameplayTag& Tag) const;
	UFUNCTION()	
	void OnEconomyChanged(const FEconomySnapshot& Snapshot);
	UFUNCTION() 
	void OnPassiveIncome(double AmountPerSec);
	UFUNCTION() 
	void OnOfflineReward(double Amount);
	UFUNCTION(BlueprintCallable, Category="UI|Economy")
	const FEconomySnapshot& GetCachedEconomySnapshot() const { return CachedEconomySnapshot; }

	UPROPERTY(BlueprintAssignable, Category="UI|Events")
	FOnEconomyChangedUI OnEconomyChangedUI;
	UPROPERTY(Config, EditAnywhere, Category="Settings")	
	TSoftObjectPtr<UClickerUISettings> UISettingsAsset;
	UPROPERTY(Config, EditAnywhere, Category="Settings")
	TSoftObjectPtr<UActionButtonRegistry> ActionButtonRegistryAsset = nullptr;
	UPROPERTY(Transient)
	TObjectPtr<UActionButtonRegistry> ActionButtonRegistry = nullptr;
	UPROPERTY() 
	TSubclassOf<UUserWidget> InGameRootWidgetClass;
	UPROPERTY() 
	UNiagaraSystem* ClickEffectAsset = nullptr;
	UPROPERTY()	
	USoundBase* ClickRewardSound = nullptr;
	UPROPERTY()	
	USoundBase* OfflineRewardSound = nullptr;
	

protected:
	UToastWidgetBase* GetWidgetFromPool(TArray<UToastWidgetBase*>& Pool, TSubclassOf<UToastWidgetBase> ToastWidgetClass);

	UPROPERTY() 
	TArray<UToastWidgetBase*> FloatingTextPool;
	UPROPERTY() 
	TArray<UToastWidgetBase*> RewardPool;
	UPROPERTY() 
	TSubclassOf<UToastWidgetBase> FloatingTextWidgetClass;
	UPROPERTY() 
	TSubclassOf<UToastWidgetBase> RewardToastClass;
	UPROPERTY() 
	TSubclassOf<UToastWidgetBase> ToastWidgetBaseClass;
	TWeakObjectPtr<APlayerController> PlayerController;

private:
	void UpdateScore(const FEconomySnapshot& S);
	void HandlePassiveIncome(double Amount);
	void HandleOfflineReward(double Amount);
	void TryFlushOfflineReward();

	UPROPERTY()	
	UUserWidget* InGameRootWidget;
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
	TArray<UIdleRewardTextWidget*> RewardTextPool;	
	UPROPERTY(Transient) 
	FEconomySnapshot CachedEconomySnapshot;
	
	double PendingOfflineReward = 0.0;
	bool bHUDReady = false;
	FTimerHandle UpgradeSuccessTimerHandle;

	UPROPERTY()
	TObjectPtr<UClickerEconomySubsystem> EconomySubsystemRef = nullptr;
	FVector2D CachedViewportSize = FVector2D::ZeroVector;
};
