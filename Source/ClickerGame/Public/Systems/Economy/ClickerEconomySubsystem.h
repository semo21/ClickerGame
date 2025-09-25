// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/Economy/EconomySnapshot.h"

#include "ClickerEconomySubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEconomyChanged, const FEconomySnapshot&, Snapshot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPassiveIncome, double, AmountPerSec);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOfflineReward, double, Amount);

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
	const FEconomySnapshot& GetSnapshot() const;		
	double GetUpgradeCost() const;

	// Delegate
	UPROPERTY(BlueprintAssignable) FOnEconomyChanged OnEconomyChanged;
	UPROPERTY(BlueprintAssignable) FOnPassiveIncome OnPassiveIncome;
	UPROPERTY(BlueprintAssignable) FOfflineReward OnOfflineReward;

private:
	void Broadcast();
	void StartAutoSaveTimer();
	void StartTickTimer();
	void StopAutoSaveTimer();
	void StopTickTimer();
	FEconomySnapshot MakeSnapshot() const;
	void ApplySnapshot(const FEconomySnapshot& In);
	
private:
	FEconomySnapshot EconomySnapshot;
	FTimerHandle AutoSaveHandle;
	FTimerHandle TickHandle;
	bool bWorldStarted = false;
};
