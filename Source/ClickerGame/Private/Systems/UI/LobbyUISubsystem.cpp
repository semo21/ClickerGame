// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/LobbyUISubsystem.h"
#include "Gameplay/GameMode/LobbyGameMode.h"


void ULobbyUISubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("ULobbyUISubsystem::Initialize"));
}

TSubclassOf<AGameModeBase> ULobbyUISubsystem::GetRequiredGameModeClass() const {
	return ALobbyGameMode::StaticClass();
}