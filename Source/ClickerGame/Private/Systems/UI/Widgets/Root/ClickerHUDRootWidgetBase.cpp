// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Root/ClickerHUDRootWidgetBase.h"
#include "Systems/UI/ClickerUISubsystem.h"
#include "Systems/UI/Widgets/Parts/ClickerHUDPartWidgetBase.h"
#include "Gameplay/Player/MyPlayerControllerBase.h"

void UClickerHUDRootWidgetBase::InitializeHUDRoot(UClickerUISubsystem* UI, AMyPlayerControllerBase* PC) {
	UIRef = UI;
	PCRef = PC;

	if (Part_Stats)			Part_Stats->InitializePart(UI, PC);
	if (Part_PrimaryActions)	Part_PrimaryActions->InitializePart(UI, PC);
	if (Part_DevButtons)		Part_DevButtons->InitializePart(UI, PC);

	UIRef->OnEconomyChangedUI.AddUniqueDynamic(this, &ThisClass::HandleEconomyChangedUI);
	HandleEconomyChangedUI(UIRef->GetCachedEconomySnapshot());
}

void UClickerHUDRootWidgetBase::HandleEconomyChangedUI(const FEconomySnapshot& Snapshot) {
	if (Part_Stats)			Part_Stats->OnEconomyChangedUI(Snapshot);
	if (Part_PrimaryActions)	Part_PrimaryActions->OnEconomyChangedUI(Snapshot);
	if (Part_DevButtons)		Part_DevButtons->OnEconomyChangedUI(Snapshot);
}
