// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/DefenseUISubsystem.h"
#include "Gameplay/GameMode/DefenseGameMode.h"

TSubclassOf<AGameModeBase> UDefenseUISubsystem::GetRequiredGameModeClass() const {
	return ADefenseGameMode::StaticClass();
}