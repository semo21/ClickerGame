// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Economy/GlobalEconomySubsystem.h"

void UGlobalEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
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