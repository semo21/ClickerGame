// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Root/ClickerHUDRootWidgetBase.h"
#include "Systems/UI/ClickerUISubsystem.h"
#include "Systems/UI/Widgets/Parts/ClickerHUDPartWidgetBase.h"
#include "Gameplay/Player/MyPlayerController.h"

void UClickerHUDRootWidgetBase::InitializeHUDRoot(UClickerUISubsystem* UI, AMyPlayerController* PC) {
	UIRef = UI;
	PCRef = PC;

	if (StatsPart)			StatsPart->InitializePart(UI, PC);
	if (PrimaryActionPart)	PrimaryActionPart->InitializePart(UI, PC);
	if (DevButtonsPart)		DevButtonsPart->InitializePart(UI, PC);
		
	UIRef->OnEconomyChangedUI.AddUniqueDynamic(this, &ThisClass::HandleEconomyChangedUI);
	HandleEconomyChangedUI(UIRef->GetCachedEconomySnapshot());	
}

void UClickerHUDRootWidgetBase::HandleEconomyChangedUI(const FEconomySnapshot& Snapshot) {
	if (StatsPart)			StatsPart->OnEconomyChangedUI(Snapshot);
	if (PrimaryActionPart)	PrimaryActionPart->OnEconomyChangedUI(Snapshot);
	if (DevButtonsPart)		DevButtonsPart->OnEconomyChangedUI(Snapshot);
}
