// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Progress/GlobalProgressSubsystem.h"
#include "Systems/Save/SaveManagerSubsystem.h"
#include "Engine/GameInstance.h"

void UGlobalProgressSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGlobalProgressSubsystem::Deinitialize()
{
	if (SaveManagerRef) {
		SaveManagerRef->SaveProgress(GlobalProgressSnapshot);
	}
	Super::Deinitialize();
}

void UGlobalProgressSubsystem::StartGame()
{
	if (bStarted) return;
	bStarted = true;

	if (UGameInstance* GI = GetGameInstance()) {
		SaveManagerRef = GI->GetSubsystem<USaveManagerSubsystem>();
	}

	if (SaveManagerRef) {
		SaveManagerRef->LoadProgress(GlobalProgressSnapshot);
	}

	if (GlobalProgressSnapshot.UnlockedLevels.IsEmpty()) {
		UnlockLevel(FGameplayTag::RequestGameplayTag("Level.Clicker"));
	}
}

bool UGlobalProgressSubsystem::IsLevelUnlocked(const FGameplayTag& LevelTag) const
{
	return GlobalProgressSnapshot.UnlockedLevels.HasTag(LevelTag);
}

void UGlobalProgressSubsystem::UnlockLevel(const FGameplayTag& LevelTag) {
	GlobalProgressSnapshot.UnlockedLevels.AddTag(LevelTag);
}