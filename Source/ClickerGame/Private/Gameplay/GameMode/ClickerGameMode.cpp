// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameMode/ClickerGameMode.h"
#include "Systems/UI/ClickerUISubsystem.h"
#include "Systems/UI/GlobalUISubsystem.h"
#include "Systems/UI/Widgets/Root/ClickerHUDRootWidgetBase.h"
#include "Gameplay/Player/MyPlayerController.h"

void AClickerGameMode::BeginPlay() {
	Super::BeginPlay();

	auto* GlobalUI = GetGameInstance()->GetSubsystem<UGlobalUISubsystem>();
	auto* Root = Cast<UClickerHUDRootWidgetBase>(GlobalUI->GetCurrentRootWidget());
	auto* ClickerUI = GetWorld()->GetSubsystem<UClickerUISubsystem>();
	auto* PC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	auto* Eco = GetWorld()->GetSubsystem<UClickerEconomySubsystem>();

	if (Root && ClickerUI && PC && Eco) {
		ClickerUI->BindEconomySubsystem(Eco);
		Root->InitializeHUDRoot(ClickerUI, PC);
	}
}