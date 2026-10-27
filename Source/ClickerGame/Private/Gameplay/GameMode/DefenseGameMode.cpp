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
	StartWave();
}

void ADefenseGameMode::SpawnEnemy() {
	if (!EnemyClass) return;

	ADefenseGridManager* GridManager = Cast< ADefenseGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ADefenseGridManager::StaticClass()));

	if (!GridManager) return;

	const FVector SpawnLocation = GridManager->GetSpawnLocation();

	ADefenseEnemyBase* Enemy = GetWorld()->SpawnActor<ADefenseEnemyBase>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
	
	if (Enemy) {
		Enemy->InitPath(GridManager);
		AliveEnemies.Add(Enemy);

		Enemy->OnReachedGoal.AddUObject(this, &ADefenseGameMode::HandleEnemyReachedGoal);
		Enemy->OnDestroyed.AddDynamic(this, &ADefenseGameMode::HandleEnemyDestroyed);
	}	
}

void ADefenseGameMode::StartWave() {
	++CurrentWave;

	EnemiesLeftToSpawn = BaseEnemyCount + (CurrentWave - 1) * EnemyCountPerWave;
	UE_LOG(LogTemp, Warning, TEXT("ADefenseGameMode::StartWave / Wave: %d, Enemies: %d"), CurrentWave, EnemiesLeftToSpawn);

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ADefenseGameMode::HandleSpawnTick, SpawnInterval, true, 0.0f);
}

void ADefenseGameMode::HandleSpawnTick() {
	SpawnEnemy();
	--EnemiesLeftToSpawn;

	if (EnemiesLeftToSpawn <= 0) {
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

void ADefenseGameMode::HandleEnemyReachedGoal() {
	--CurrentLives;
	UE_LOG(LogTemp, Warning, TEXT("DefenseGameMode::CurrentLives: %d"), CurrentLives);
}

void ADefenseGameMode::HandleEnemyDestroyed(AActor* DestroyedActor) {
	ADefenseEnemyBase* Enemy = Cast<ADefenseEnemyBase>(DestroyedActor);
	if (!Enemy) return;

	AliveEnemies.Remove(Enemy);
	UE_LOG(LogTemp, Warning, TEXT("ADefenseGameMode::HandleEnemyDestroyed / Alive: %d"), AliveEnemies.Num());
	if (IsWaveCleared()) {
		HandleWaveCleared();
	}
}

void ADefenseGameMode::HandleWaveCleared() {
	if (CurrentWave >= MaxWaves) {
		UE_LOG(LogTemp, Warning, TEXT("ADefenseGameMode::HandleWaveCleared / All waves cleared"));
		return;
	}
	StartWave();
}

bool ADefenseGameMode::IsWaveCleared() const {
	return EnemiesLeftToSpawn <= 0 && AliveEnemies.IsEmpty();
}