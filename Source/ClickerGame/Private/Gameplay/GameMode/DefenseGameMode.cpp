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
	CurrentLives = StartLives;
	SpawnEnemy();
}

void ADefenseGameMode::SpawnEnemy() {
	if (!EnemyClass) return;

	ADefenseGridManager* GridManager = Cast< ADefenseGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ADefenseGridManager::StaticClass()));

	if (!GridManager) return;

	const FVector SpawnLocation = GridManager->GetSpawnLocation();

	ADefenseEnemyBase* Enemy = GetWorld()->SpawnActor<ADefenseEnemyBase>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
	
	if (Enemy) {
		Enemy->InitPath(GridManager);
		Enemy->OnReachedGoal.AddUObject(this, &ADefenseGameMode::HandleEnemyReachedGoal);
	}	
}

void ADefenseGameMode::HandleEnemyReachedGoal() {
	--CurrentLives;
	UE_LOG(LogTemp, Warning, TEXT("DefenseGameMode::CurrentLives: %d"), CurrentLives);
}