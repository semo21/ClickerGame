// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase() {
	// Set the player controller class to our custom player controller
	PlayerControllerClass = AMyPlayerController::StaticClass();

	// You can also set other properties here, such as the default pawn class, HUD class, etc.
	// DefaultPawnClass = AMyPawn::StaticClass(); // Example for setting a default pawn class
	// HUDClass = AMyHUD::StaticClass(); // Example for setting a custom HUD class
	// Set the default game state class if needed

}
