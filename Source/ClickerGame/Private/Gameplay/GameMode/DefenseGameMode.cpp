// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameMode/DefenseGameMode.h"
#include "Gameplay/Player/DefensePlayerController.h"
#include "Gameplay/Actors/Defense/DefenseGridManager.h"
#include "Gameplay/Actors/Defense/DefenseEnemyBase.h"
#include "Kismet/GameplayStatics.h"

ADefenseGameMode::ADefenseGameMode() {
	PlayerControllerClass = ADefensePlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}

void ADefenseGameMode::BeginPlay() {
	Super::BeginPlay();
	SpawnEnemy();
}

void ADefenseGameMode::SpawnEnemy() {
	if (!EnemyClass) return;

	ADefenseGridManager* GridManager = Cast< ADefenseGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ADefenseGridManager::StaticClass()));

	if (!GridManager) return;

	const FVector SpawnLocation = GridManager->GetSpawnLocation();

	GetWorld()->SpawnActor<ADefenseEnemyBase>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
}