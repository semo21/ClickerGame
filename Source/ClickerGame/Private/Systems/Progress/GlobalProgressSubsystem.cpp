// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Progress/GlobalProgressSubsystem.h"
#include "Systems/Save/SaveManagerSubsystem.h"

void UGlobalProgressSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	SaveManagerRef = Collection.InitializeDependency<USaveManagerSubsystem>();
	if (SaveManagerRef) {
		SaveManagerRef->LoadProgress(GlobalProgressSnapshot);
	}

	if (GlobalProgressSnapshot.UnlockedLevels.IsEmpty()) {
		UnlockLevel(FGameplayTag::RequestGameplayTag("Level.Lobby"));
		UnlockLevel(FGameplayTag::RequestGameplayTag("Level.Clicker"));
		UnlockLevel(FGameplayTag::RequestGameplayTag("Level.Defense"));

	}
}

void UGlobalProgressSubsystem::Deinitialize()
{
	if (SaveManagerRef) {
		SaveManagerRef->SaveProgress(GlobalProgressSnapshot);
	}
	Super::Deinitialize();
}

bool UGlobalProgressSubsystem::IsLevelUnlocked(const FGameplayTag& LevelTag) const
{
	return GlobalProgressSnapshot.UnlockedLevels.HasTag(LevelTag);
}

void UGlobalProgressSubsystem::UnlockLevel(const FGameplayTag& LevelTag) {
	GlobalProgressSnapshot.UnlockedLevels.AddTag(LevelTag);
}