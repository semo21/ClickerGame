// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Economy/DefenseEconomySubsystem.h"
#include "Gameplay/GameMode/DefenseGameMode.h"
#include "Systems/Economy/Settings/DefenseEconomySettings.h"

void UDefenseEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	
	EconomySettings = EconomySettingsAsset.LoadSynchronous();
	UE_LOG(LogTemp, Log, TEXT("UDefenseEconomySubsystem::Initialize / EconomySettings: %s"), EconomySettings ? TEXT("Loaded") : TEXT("Null"));
}

TSubclassOf<AGameModeBase> UDefenseEconomySubsystem::GetRequiredGameModeClass() const {
	return ADefenseGameMode::StaticClass();
}

double UDefenseEconomySubsystem::CalculateSettlementReward(EDefenseMatchState Result) const {
	switch (Result) {
	case EDefenseMatchState::Victory:
		return EconomySettings ? EconomySettings->VictoryReward : 0.0;
	case EDefenseMatchState::Defeat:
		return EconomySettings ? EconomySettings->DefeatReward : 0.0;
	default:
		return 0.0;
	}
}