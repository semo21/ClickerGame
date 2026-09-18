// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameMode/MyGameModeBase.h"
#include "Gameplay/Player/MyPlayerControllerBase.h"
#include "Systems/Economy/GlobalEconomySubsystem.h"
#include "Systems/UI/GlobalUISUbsystem.h"
#include "Blueprint/UserWidget.h"

AMyGameModeBase::AMyGameModeBase() {
	// Set the player controller class to our custom player controller
	PlayerControllerClass = AMyPlayerControllerBase::StaticClass();
}

void AMyGameModeBase::BeginPlay() {
	Super::BeginPlay();

	if (UGlobalUISubsystem* GlobalUI = GetGameInstance()->GetSubsystem<UGlobalUISubsystem>()) {
		GlobalUI->ShowRootUI(RootWidgetClass);
	}

	if (UGlobalEconomySubsystem* GlobalEco = GetGameInstance()->GetSubsystem<UGlobalEconomySubsystem>()) {
		GlobalEco->StartGame();
	}
}