// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameMode/MyGameModeBase.h"
#include "Gameplay/Player/MyPlayerController.h"
#include "Systems/UI/GlobalUISUbsystem.h"
#include "Blueprint/UserWidget.h"

AMyGameModeBase::AMyGameModeBase() {
	// Set the player controller class to our custom player controller
	PlayerControllerClass = AMyPlayerControllerBase::StaticClass();
}

void AMyGameModeBase::BeginPlay() {
	Super::BeginPlay();

	if (UGlobalUISubsystem* UISubsystem = GetGameInstance()->GetSubsystem<UGlobalUISubsystem>()) {
		UISubsystem->ShowRootUI(RootWidgetClass);
	}
}