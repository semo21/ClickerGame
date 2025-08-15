// Fill out your copyright notice in the Description page of Project Settings.

#include "ClickerComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"	

#include "ClickerEconomySubsystem.h"
// Called every frame
void UClickerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AccumulatedTime += DeltaTime;
	if (AccumulatedTime >= 1.0f) {
		if (auto* Eco = GetWorld()->GetGameInstance()->GetSubsystem<UClickerEconomySubsystem>()) {
			Eco->OnTick1Second();
		}
		AccumulatedTime = 0.0f;
	}
}

void UClickerComponent::HandleClick() {
	if (auto* Eco = GetWorld()->GetGameInstance()->GetSubsystem<UClickerEconomySubsystem>()) {
		Eco->OnClicked();
	}
}

void UClickerComponent::HandleUpgrade() {
	if (auto* Eco = GetWorld()->GetGameInstance()->GetSubsystem<UClickerEconomySubsystem>()) {
		Eco->TryUpgrade();
	}
}