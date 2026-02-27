// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Root/ClickerHUDRootWidgetBase.h"
#include "Systems/UI/ClickerUISubsystem.h"
#include "Systems/UI/Widgets/Parts/ClickerHUDPartWidgetBase.h"
#include "Gameplay/Player/MyPlayerController.h"

void UClickerHUDRootWidgetBase::InitializeRoot(UClickerUISubsystem* UI, UClickerEconomySubsystem* Eco, AMyPlayerController* PC) {
	UIRef = UI;
	EcoRef = Eco;
	PCRef = PC;

	if (StatsPart)			StatsPart->InitializePart(UI, Eco, PC);
	if (PrimaryActionPart)	PrimaryActionPart->InitializePart(UI, Eco, PC);
	if (DevButtonsPart)		DevButtonsPart->InitializePart(UI, Eco, PC);

	if (UIRef) {
		UIRef->OnEconomyChanged.AddUniqueDynamic(this, &ThisClass::HandleEconomyChanged);
	}

	if (EcoRef) {
		HandleEconomyChanged(EcoRef->GetSnapshot());
	}
}

void UClickerHUDRootWidgetBase::HandleEconomyChanged(const FEconomySnapshot& Snapshot) {
	if (StatsPart)			StatsPart->OnEconomyChanged(Snapshot);
	if (PrimaryActionPart)	PrimaryActionPart->OnEconomyChanged(Snapshot);
	if (DevButtonsPart)		DevButtonsPart->OnEconomyChanged(Snapshot);
}
