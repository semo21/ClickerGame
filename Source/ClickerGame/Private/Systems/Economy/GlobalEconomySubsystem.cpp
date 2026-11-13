// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Economy/GlobalEconomySubsystem.h"
#include "Systems/Save/SaveManagerSubsystem.h"

void UGlobalEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	SaveManagerRef = Collection.InitializeDependency<USaveManagerSubsystem>();
	if (SaveManagerRef) {
		SaveManagerRef->LoadProgress(GlobalEconomySnapshot);
	}	
}

void UGlobalEconomySubsystem::Deinitialize() {
	if (SaveManagerRef) {
		SaveManagerRef->SaveProgress(GlobalEconomySnapshot);
	}	
	Super::Deinitialize();
}

void UGlobalEconomySubsystem::AddGlobalCurrency(double Amount) {
	if (SaveManagerRef) {
		GlobalEconomySnapshot.GlobalCurrency += Amount;
		SaveManagerRef->SaveProgress(GlobalEconomySnapshot);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("UGlobalEconomySubsystem::AddGlobalCurrency / SaveManagerRef is null"));
	}
}