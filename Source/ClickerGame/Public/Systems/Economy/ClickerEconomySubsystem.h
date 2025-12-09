// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/Economy/EconomySnapshot.h"

#include "ClickerEconomySubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEconomyChanged, const FEconomySnapshot&, Snapshot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOfflineReward, double, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPassiveIncome, double, AmountPerSec);

class UClickerUISubsystem;
class USaveManagerSubsystem;
/**
 * 
 */
UCLASS(BlueprintType)
class CLICKERGAME_API UClickerEconomySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void StartWorld(UWorld* World);
	void OnClicked();
	void OnTick1Second();
	bool TryUpgrade();
	void RequestSave();
	void RequestLoad();
	void TriggerOfflineReward();

	UFUNCTION(BlueprintPure, Category = "Economy") const FEconomySnapshot& GetSnapshot() const { return EconomySnapshot; }
	UFUNCTION(BlueprintPure) bool HasPendingOfflineReward() const { return LastOfflineReward > 0.0; }
	UFUNCTION(BlueprintPure) double GetLastOfflineReward() const { return LastOfflineReward; }

	// Delegate
	UPROPERTY(BlueprintAssignable, Category = "Economy|Events") FOnEconomyChanged OnEconomyChanged;
	UPROPERTY(BlueprintAssignable, Category = "Economy|Events") FOnOfflineReward OnOfflineReward;
	UPROPERTY(BlueprintAssignable, Category = "Economy|Events") FOnPassiveIncome OnPassiveIncome;

private:
	void Broadcast();
	void StartAutoSaveTimer();
	void StartTickTimer();
	void StopAutoSaveTimer();
	void StopTickTimer();
	double GetUpgradeCost() const;
	FEconomySnapshot MakeSnapshot() const;
	void ApplySnapshot(const FEconomySnapshot& In);
	void ApplyOfflineReward(double Amount);
	void UpdateLastOfflineReward(FEconomySnapshot& In);
	
private:
	FEconomySnapshot EconomySnapshot;
	FTimerHandle AutoSaveHandle;
	FTimerHandle TickHandle;
	bool bWorldStarted = false;
	double LastOfflineReward = 0.0;
};
