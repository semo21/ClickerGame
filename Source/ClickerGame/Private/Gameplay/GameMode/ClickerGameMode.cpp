// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameMode/ClickerGameMode.h"
#include "Gameplay/Player/ClickerPlayerController.h"
#include "Systems/UI/ClickerUISubsystem.h"
#include "Systems/UI/GlobalUISubsystem.h"
#include "Systems/UI/Widgets/Root/ClickerHUDRootWidgetBase.h"

AClickerGameMode::AClickerGameMode() {
	PlayerControllerClass = AClickerPlayerController::StaticClass();
}

void AClickerGameMode::BeginPlay() {
	Super::BeginPlay();

	auto* GlobalUI = GetGameInstance()->GetSubsystem<UGlobalUISubsystem>();
	if (!ensure(GlobalUI)) return;

	auto* Root = Cast<UClickerHUDRootWidgetBase>(GlobalUI->GetCurrentRootWidget());
	if (!ensure(Root)) return;

	auto* ClickerUI = GetWorld()->GetSubsystem<UClickerUISubsystem>();
	if (!ensure(ClickerUI)) return;

	auto* PC = Cast<AClickerPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!ensure(PC)) return;

	auto* Eco = GetWorld()->GetSubsystem<UClickerEconomySubsystem>();
	if (!ensure(Eco)) return;

	ClickerUI->BindEconomySubsystem(Eco);
	Root->InitializeHUDRoot(ClickerUI, PC);
	Eco->StartWorld(GetWorld());
}