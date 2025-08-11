// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ClickerComponent.generated.h"

class UGameManager;
class AMyPlayerController;
class UClickerUIManager;
class USaveManagerSubsystem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLICKERGAME_API UClickerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClickerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	UFUNCTION()
	void SaveProgress();

	UFUNCTION()
	void LoadProgress();

	UFUNCTION()
	void Initialize(UGameManager* InGameManager);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HandleClick();
	void HandleUpgrade();
	int32 GetUpgradeLevel() const;
	float GetCurrency() const;
	float GetCurrencyPerClick() const;
	float GetUpgradeCost() const;
	float GetCurrencyPerSecond() const;

	void SetUpgradeLevel(int32 NewUpgradeLevel);
	void SetCurrency(float NewCurrency);
	void SetCurrencyPerClick(float NewCurrencyPerClick);
	void SetCurrencyPerSecond(float NewCurrencyPerSecond);
	void SetOfflineReward(float OfflineReward);

	void SetUIManager(UClickerUIManager* InUIManager);
			
private:
	UPROPERTY()
	UClickerUIManager* UIManager;

	UPROPERTY()
	AMyPlayerController* CachedMyPlayerController = nullptr;

	UPROPERTY()
	USaveManagerSubsystem* SaveManager;

	UFUNCTION()
	void RecalculateStats();

	UFUNCTION()
	void EnsureSaveManager();

	int32 ClickCount;
	float Currency = 0.0f;
	float Multiplier;	
	float CurrencyPerSecond;
	float OFflineReward;
	float AccumulatedTime;
	float CurrencyPerClick = 1.0f;
	float UpgradeCostBase;
	int32 UpgradeLevel = 0;
	FTimerHandle AutoSaveHandle;
};