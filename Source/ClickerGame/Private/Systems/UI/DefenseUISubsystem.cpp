// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/DefenseUISubsystem.h"
#include "Systems/UI/Settings/DefenseUISettings.h"
#include "Gameplay/GameMode/DefenseGameMode.h"


void UDefenseUISubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	UISettings = UISettingsAsset.LoadSynchronous();
	UE_LOG(LogTemp, Log, TEXT("UDefenseUISubsystem::Initialize / UISettings: %s"), UISettings ? TEXT("Loaded") : TEXT("Null"));
}

TSubclassOf<AGameModeBase> UDefenseUISubsystem::GetRequiredGameModeClass() const {
	return ADefenseGameMode::StaticClass();
}