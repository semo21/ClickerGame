// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickerEconomySubsystem.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "SaveManagerSubsystem.h"
#include "IdleRewardTextWidget.h"
#include "ClickerUISubsystem.h"
#include "Kismet/KismetMathLibrary.h"

void UClickerEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

}

void UClickerEconomySubsystem::Deinitialize() {
	RequestSave();
	StopAutoSaveTimer();
	StopTickTimer();

	Super::Deinitialize();
}


void UClickerEconomySubsystem::StartWorld(UWorld* World) {
	if (!World || bWorldStarted) return;
	bWorldStarted = true;

	RequestLoad();
	StartAutoSaveTimer();
	StartTickTimer();

	UE_LOG(LogTemp, Warning, TEXT("EconomySubsyste::StartWorld Called"));
}

void UClickerEconomySubsystem::StartAutoSaveTimer() {
	if (UWorld* W = GetWorld()) {
		W->GetTimerManager().SetTimer(
			AutoSaveHandle,
			FTimerDelegate::CreateUObject(this, &UClickerEconomySubsystem::RequestSave),
			60.0f,
			true
		);
	}
}

void UClickerEconomySubsystem::StartTickTimer() {
	if (UWorld* W = GetWorld()) {
		W->GetTimerManager().SetTimer(
			TickHandle,
			this, &UClickerEconomySubsystem::OnTick1Second,
			1.0f,
			true
		);
	}
}

void UClickerEconomySubsystem::StopAutoSaveTimer() {
	if (UWorld* W = GetWorld()) {
		W->GetTimerManager().ClearTimer(AutoSaveHandle);
	}
}
void UClickerEconomySubsystem::StopTickTimer() {
	if (UWorld* W = GetWorld()) {
		W->GetTimerManager().ClearTimer(TickHandle);
	}
}
void UClickerEconomySubsystem::OnClicked() {
	EconomySnapshot.Currency += EconomySnapshot.CurrencyPerClick;
	Broadcast();
}

void UClickerEconomySubsystem::OnTick1Second() {
	EconomySnapshot.Currency += EconomySnapshot.CurrencyPerSecond;
	if (auto* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>()) {
		UI->ShowIdleReward(EconomySnapshot.CurrencyPerSecond);
	}
	Broadcast();
}

double UClickerEconomySubsystem::GetUpgradeCost() const {
	return FMath::Pow(EconomySnapshot.UpgradeGrowth, EconomySnapshot.UpgradeLevel + 1) * EconomySnapshot.UpgradeCostBase;
}

bool UClickerEconomySubsystem::TryUpgrade() {
	const double UpgradeCost = GetUpgradeCost();
	if (EconomySnapshot.Currency < UpgradeCost) return false;

	EconomySnapshot.Currency -= UpgradeCost;
	EconomySnapshot.UpgradeLevel++;
	EconomySnapshot.CurrencyPerClick += 1.0;
	EconomySnapshot.CurrencyPerSecond += 0.5;

	Broadcast();
	return true;
}

void UClickerEconomySubsystem::RequestSave() {
	if (USaveManagerSubsystem* Save = GetGameInstance()->GetSubsystem<USaveManagerSubsystem>()) {
		FEconomySnapshot Out = MakeSnapshot();
		Out.LastSaveTime = FDateTime::UtcNow().ToUnixTimestamp();

		Save->SaveProgress(Out);
	}
}

void UClickerEconomySubsystem::RequestLoad() {
	UE_LOG(LogTemp, Warning, TEXT("EconomySubsyste::Request Called"));

	if (USaveManagerSubsystem* Load = GetGameInstance()->GetSubsystem<USaveManagerSubsystem>()) {
		FEconomySnapshot In;
		UE_LOG(LogTemp, Warning, TEXT("EconomySubsyste::Request Load Instance Exists."));
		if (Load->LoadProgress(In)) {
			UE_LOG(LogTemp, Warning, TEXT("EconomySubsyste::Request LoadProgress Succeeded."));
			const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
			const int64 DeltaSec = Now - In.LastSaveTime;
			In.Currency += In.CurrencyPerSecond * DeltaSec / 30;

			ApplySnapshot(In);

			if (UClickerUISubsystem* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>()) {
				UI->ShowOfflineReward(In.CurrencyPerSecond * DeltaSec / 30);
			}
		}
		else {
			Broadcast();
		}
	}
}

FEconomySnapshot UClickerEconomySubsystem::MakeSnapshot() const {
	return EconomySnapshot;
}

void UClickerEconomySubsystem::ApplySnapshot(const FEconomySnapshot& In) {
	EconomySnapshot.UpgradeLevel = In.UpgradeLevel;
	EconomySnapshot.Currency = In.Currency;
	EconomySnapshot.CurrencyPerClick = In.CurrencyPerClick;
	EconomySnapshot.CurrencyPerSecond = In.CurrencyPerSecond;
	EconomySnapshot.UpgradeCostBase = In.UpgradeCostBase;
	EconomySnapshot.UpgradeGrowth = In.UpgradeGrowth;	
	Broadcast();
}

void UClickerEconomySubsystem::Broadcast() {
	OnEconomyChanged.Broadcast(EconomySnapshot);
}