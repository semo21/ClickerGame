// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/DefenseUISubsystem.h"
#include "Systems/UI/Settings/DefenseUISettings.h"
#include "Systems/UI/Widgets/Result/DefenseResultWidget.h"
#include "Gameplay/GameMode/DefenseGameMode.h"



void UDefenseUISubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	UISettings = UISettingsAsset.LoadSynchronous();
	UE_LOG(LogTemp, Log, TEXT("UDefenseUISubsystem::Initialize / UISettings: %s"), UISettings ? TEXT("Loaded") : TEXT("Null"));
}

void UDefenseUISubsystem::ShowResult(APlayerController* PC, EDefenseMatchState Result) {
	if (!PC || !UISettings || !UISettings->ResultWidgetClass) return;

	if (!ResultWidget) {
		ResultWidget = CreateWidget<UDefenseResultWidget>(PC, UISettings->ResultWidgetClass);
	}
	if (!ResultWidget) return;

	ResultWidget->SetResult(Result);
	if (!ResultWidget->IsInViewport()) {
		ResultWidget->AddToViewport(10);
	}
}

TSubclassOf<AGameModeBase> UDefenseUISubsystem::GetRequiredGameModeClass() const {
	return ADefenseGameMode::StaticClass();
}