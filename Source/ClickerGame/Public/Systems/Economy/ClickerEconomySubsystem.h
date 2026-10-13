// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/WorldSubsystem.h"
#include "Systems/Economy/Data/ClickerEconomySnapshot.h"

#include "ClickerEconomySubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEconomyChanged, const FClickerEconomySnapshot&, Snapshot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOfflineReward, double, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPassiveIncome, double, AmountPerSec);

class UClickerUISubsystem;
class USaveManagerSubsystem;
/**
 * 
 */
UCLASS(BlueprintType)
class CLICKERGAME_API UClickerEconomySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void StartWorld(UWorld* World);
	void OnClicked();
	bool TryUpgrade();
	void RequestSave();
	void RequestLoad();

	UFUNCTION(BlueprintPure, Category = "Economy") const FClickerEconomySnapshot& GetSnapshot() const { return ClickerEconomySnapshot; }
	UFUNCTION(BlueprintPure) double GetLastOfflineReward() const { return LastOfflineReward; }

	// Delegate
	UPROPERTY(BlueprintAssignable, Category = "Economy|Events") FOnEconomyChanged OnEconomyChanged;
	UPROPERTY(BlueprintAssignable, Category = "Economy|Events") FOnOfflineReward OnOfflineReward;
	UPROPERTY(BlueprintAssignable, Category = "Economy|Events") FOnPassiveIncome OnPassiveIncome;

private:
	void Broadcast();
	void StartAutoSaveTimer();
	void StartTickTimer();
	void OnTick1Second();
	void StopAutoSaveTimer();
	void StopTickTimer();
	double GetUpgradeCost() const;
	FClickerEconomySnapshot MakeSnapshot() const;
	void TriggerOfflineReward();
	void ApplySnapshot(const FClickerEconomySnapshot& In);
	void ApplyOfflineReward(double Amount);
	void UpdateLastOfflineReward(FClickerEconomySnapshot& In);
	
private:
	UPROPERTY()
	TObjectPtr<USaveManagerSubsystem> SaveManagerSubsystemRef;
	FClickerEconomySnapshot ClickerEconomySnapshot;
	FTimerHandle AutoSaveHandle;
	FTimerHandle TickHandle;
	bool bWorldStarted = false;
	double LastOfflineReward = 0.0;
};
