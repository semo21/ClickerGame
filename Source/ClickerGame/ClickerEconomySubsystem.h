// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "ClickerEconomySubsystem.generated.h"

USTRUCT(BlueprintType)
struct FEconomySnapshot
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32  UpgradeLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double Currency = 0.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double CurrencyPerClick = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double CurrencyPerSecond = 2.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double UpgradeCostBase = 10.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double UpgradeGrowth = 1.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int64  LastSaveTime = 0;
};

// ==========================================================================================
// ==========================================================================================

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEconomyChanged, const FEconomySnapshot&, Snapshot);

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
	FEconomySnapshot MakeSnapshot() const;
	void ApplySnapshot(const FEconomySnapshot& In);
	double GetUpgradeCost() const;
	UPROPERTY(BlueprintAssignable)	FOnEconomyChanged OnEconomyChanged;

private:
	void Broadcast();
	void StartAutoSaveTimer();
	void StartTickTimer();
	void StopAutoSaveTimer();
	void StopTickTimer();

private:
	FEconomySnapshot EconomySnapshot;
	FTimerHandle AutoSaveHandle;
	FTimerHandle TickHandle;
	bool bWorldStarted = false;

};
