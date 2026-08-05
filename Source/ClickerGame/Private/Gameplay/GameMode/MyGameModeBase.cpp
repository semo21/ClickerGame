// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameMode/MyGameModeBase.h"
#include "Gameplay/Player/MyPlayerController.h"
#include "Systems/UI/GlobalUISUbsystem.h"
#include "Blueprint/UserWidget.h"

AMyGameModeBase::AMyGameModeBase() {
	// Set the player controller class to our custom player controller
	PlayerControllerClass = AMyPlayerController::StaticClass();

	// You can also set other properties here, such as the default pawn class, HUD class, etc.
	// DefaultPawnClass = AMyPawn::StaticClass(); // Example for setting a default pawn class
	// HUDClass = AMyHUD::StaticClass(); // Example for setting a custom HUD class
	// Set the default game state class if needed

}

void AMyGameModeBase::BeginPlay() {
	Super::BeginPlay();

	if (UGlobalUISubsystem* UISubsystem = GetGameInstance()->GetSubsystem<UGlobalUISubsystem>()) {
		UISubsystem->ShowRootUI(RootWidgetClass);
	}
}