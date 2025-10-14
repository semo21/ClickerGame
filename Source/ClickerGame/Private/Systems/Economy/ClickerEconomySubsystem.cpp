// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Economy/ClickerEconomySubsystem.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

#include "Systems/Save/SaveManagerSubsystem.h"
#include "Systems/UI/Widgets/Toast/IdleRewardTextWidget.h"
//#include "Systems/UI/ClickerUISubsystem.h"


// public field

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

	//UE_LOG(LogTemp, Warning, TEXT("EconomySubsystem::StartWorld Called"));
}

void UClickerEconomySubsystem::OnClicked() {
	EconomySnapshot.Currency += EconomySnapshot.CurrencyPerClick;
	Broadcast();
}

void UClickerEconomySubsystem::OnTick1Second() {
	EconomySnapshot.Currency += EconomySnapshot.CurrencyPerSecond;
	//if (auto* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>()) {
	//	UI->ShowIdleReward(EconomySnapshot.CurrencyPerSecond);
	//}
	OnPassiveIncome.Broadcast(EconomySnapshot.CurrencyPerSecond);
	Broadcast();
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
		//Out.LastSaveTime = FDateTime::UtcNow().ToUnixTimestamp();

		Save->SaveProgress(Out);
	}
}

void UClickerEconomySubsystem::RequestLoad() {
	//UE_LOG(LogTemp, Warning, TEXT("EconomySubsystem::Request Called"));

	if (USaveManagerSubsystem* Load = GetGameInstance()->GetSubsystem<USaveManagerSubsystem>()) {
		FEconomySnapshot In;
		if (Load->LoadProgress(In)) {
			const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
			const int64 DeltaSec = Now - In.LastSaveTime;
			In.Currency += In.CurrencyPerSecond * DeltaSec / 2;
			In.LastSaveTime = Now;
			LastOfflineReward = In.CurrencyPerSecond * DeltaSec / 30;

			ApplySnapshot(In);			
			RequestSave();
			ApplyOfflineReward(LastOfflineReward);
			//if (UClickerUISubsystem* UI = GetGameInstance()->GetSubsystem<UClickerUISubsystem>()) {
			//	//UE_LOG(LogTemp, Warning, TEXT("EconomySubsyste::Request LoadProgress ShowOfflineReward."));
			//	UI->ShowOfflineReward(In.CurrencyPerSecond * DeltaSec / 30);
			//}
		}
		else {
			Broadcast();
		}
	}
}

double UClickerEconomySubsystem::GetUpgradeCost() const {
	return FMath::Pow(EconomySnapshot.UpgradeGrowth, EconomySnapshot.UpgradeLevel + 1) * EconomySnapshot.UpgradeCostBase;
}

//  private field
void UClickerEconomySubsystem::Broadcast() {
	OnEconomyChanged.Broadcast(EconomySnapshot);
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

FEconomySnapshot UClickerEconomySubsystem::MakeSnapshot() const {
	return EconomySnapshot;
}

void UClickerEconomySubsystem::ApplySnapshot(const FEconomySnapshot& In) {

	EconomySnapshot = In;
	Broadcast();
}

void UClickerEconomySubsystem::ApplyOfflineReward(double Amount) {
	if (Amount <= 0.0) return;	
	OnOfflineReward.Broadcast(Amount);
	Broadcast();
}

void UClickerEconomySubsystem::UpdateLastOfflineReward(FEconomySnapshot& In) {
	const int64 Now = FDateTime::UtcNow().ToUnixTimestamp();
	const int64 DeltaSec = Now - In.LastSaveTime;
	LastOfflineReward = In.CurrencyPerSecond * DeltaSec / 30;
	In.LastSaveTime = Now;

}