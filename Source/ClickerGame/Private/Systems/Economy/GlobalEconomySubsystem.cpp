// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Economy/GlobalEconomySubsystem.h"
#include "Systems/Save/SaveManagerSubsystem.h"
#include "Engine/GameInstance.h"

void UGlobalEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
}

void UGlobalEconomySubsystem::StartGame() {
	if (bStarted) return;
	bStarted = true;

	if (UGameInstance* GI = GetGameInstance()) {
		SaveManagerRef = GI->GetSubsystem<USaveManagerSubsystem>();
	}
	if (SaveManagerRef) {
		SaveManagerRef->LoadProgress(MetaSnapshot);
	}
}

bool UGlobalEconomySubsystem::IsLevelUnlocked(const FGameplayTag& LevelTag) const {
	return MetaSnapshot.UnlockedLevels.HasTag(LevelTag);
}

void UGlobalEconomySubsystem::UnlockLevel(const FGameplayTag& LevelTag) {
	MetaSnapshot.UnlockedLevels.AddTag(LevelTag);
}

void UGlobalEconomySubsystem::AddGlobalCurrency(double Amount) {
	MetaSnapshot.GlobalCurrenty += Amount;
}