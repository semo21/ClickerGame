// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Parts/ClickerHUDPartWidgetBase.h"

void UClickerHUDPartWidgetBase::InitializePart_Implementation(UClickerUISubsystem* InUI, AMyPlayerController* InPC) {
	
	UIRef = InUI;
	PCRef = InPC;
	// Implement in Blueprint
}

void UClickerHUDPartWidgetBase::OnEconomyChangedUI_Implementation(const FEconomySnapshot& Snapshot) {
	// Implement in Blueprint
}