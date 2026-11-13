// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameMode/DefenseGameMode.h"
#include "Systems/Economy/GlobalEconomySubsystem.h"
#include "Systems/Economy/DefenseEconomySubsystem.h"
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
	if (MatchState != EDefenseMatchState::InProgress)	return;

	--CurrentLives;
	UE_LOG(LogTemp, Warning, TEXT("DefenseGameMode::CurrentLives: %d"), CurrentLives);

	if (CurrentLives <= 0) {
		EndMatch(EDefenseMatchState::Defeat);
	}
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
	if (MatchState != EDefenseMatchState::InProgress) return;

	if (CurrentWave >= MaxWaves) {
		UE_LOG(LogTemp, Warning, TEXT("ADefenseGameMode::HandleWaveCleared / All waves cleared"));
		EndMatch(EDefenseMatchState::Victory);
		return;
	}
	StartWave();
}

bool ADefenseGameMode::IsWaveCleared() const {
	return EnemiesLeftToSpawn <= 0 && AliveEnemies.IsEmpty();
}

void ADefenseGameMode::EndMatch(EDefenseMatchState Result) {
	if (MatchState != EDefenseMatchState::InProgress) return;

	MatchState = Result;
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	UE_LOG(LogTemp, Warning, TEXT("ADefenseGameMode::EndMatch, MatchState: %s"), *UEnum::GetValueAsString(Result));

	UDefenseEconomySubsystem* DefenseEco = GetWorld()->GetSubsystem<UDefenseEconomySubsystem>();
	UGlobalEconomySubsystem* GlobalEco = GetGameInstance()->GetSubsystem<UGlobalEconomySubsystem>();
	if (DefenseEco && GlobalEco) {
		const double GlobalReward = DefenseEco->CalculateSettlementReward(Result);
		GlobalEco->AddGlobalCurrency(GlobalReward);
		UE_LOG(LogTemp, Warning, TEXT("ADefenseGameMode::EndMatch / GlobalReward: %f"), GlobalReward);
	}

	if (ADefensePlayerController* PC = Cast<ADefensePlayerController>(GetWorld()->GetFirstPlayerController())) {
		PC->HandleMatchEnded(Result);
	}
}