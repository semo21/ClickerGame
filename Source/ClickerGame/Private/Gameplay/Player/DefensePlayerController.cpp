// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Player/DefensePlayerController.h"
#include "Gameplay/Actors/Defense/DefenseGridManager.h"
#include "Kismet/GameplayStatics.h"

void ADefensePlayerController::BeginPlay() {
	Super::BeginPlay();

	GridRef = Cast< ADefenseGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ADefenseGridManager::StaticClass()));
}

void ADefensePlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	if (IsLocalController())
		InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &ADefensePlayerController::OnClick);
}

void ADefensePlayerController::OnClick() {
	if (!GridRef) return;

	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (!HitResult.bBlockingHit) return;

	const int32 TileIndex = GridRef->WorldToTileIndex(HitResult.Location);
	if (TileIndex == INDEX_NONE) return;

	GridRef->PlaceTower(TileIndex, TowerClass);
}
