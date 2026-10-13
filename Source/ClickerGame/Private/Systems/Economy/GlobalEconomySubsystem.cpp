// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Economy/GlobalEconomySubsystem.h"
#include "Systems/Save/SaveManagerSubsystem.h"
#include "Engine/GameInstance.h"

void UGlobalEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
}

void UGlobalEconomySubsystem::Deinitialize() {
	if (SaveManagerRef) {
		SaveManagerRef->SaveProgress(GlobalEconomySnapshot);
	}	
	Super::Deinitialize();
}
void UGlobalEconomySubsystem::StartGame() {
	if (bStarted) return;
	bStarted = true;

	if (UGameInstance* GI = GetGameInstance()) {
		SaveManagerRef = GI->GetSubsystem<USaveManagerSubsystem>();
	}
	if (SaveManagerRef) {
		SaveManagerRef->LoadProgress(GlobalEconomySnapshot);
	}
}

void UGlobalEconomySubsystem::AddGlobalCurrency(double Amount) {
	GlobalEconomySnapshot.GlobalCurrency += Amount;
}