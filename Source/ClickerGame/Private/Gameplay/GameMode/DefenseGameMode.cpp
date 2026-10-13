// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameMode/DefenseGameMode.h"
#include "Gameplay/Player/DefensePlayerController.h"

ADefenseGameMode::ADefenseGameMode() {
	PlayerControllerClass = ADefensePlayerController::StaticClass();
}