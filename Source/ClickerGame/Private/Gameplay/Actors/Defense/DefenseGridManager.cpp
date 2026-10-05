// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/Defense/DefenseGridManager.h"
#include "Gameplay/Actors/Defense/DefenseTowerBase.h"

// Sets default values
ADefenseGridManager::ADefenseGridManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADefenseGridManager::BeginPlay()
{
	Super::BeginPlay();	

	Tiles.SetNum(GridWidth * GridHeight);
}

bool ADefenseGridManager::IsValidCoord(int32 X, int32 Y) const {
	return X >= 0 && X < GridWidth && Y >= 0 && Y < GridHeight;
}

int32 ADefenseGridManager::WorldToTileIndex(const FVector& WorldLocation) const {
	const FVector Local = WorldLocation - GetActorLocation();

	const int32 X = FMath::FloorToInt(Local.X / TileSize);
	const int32 Y = FMath::FloorToInt(Local.Y / TileSize);

	if (!IsValidCoord(X, Y)) return INDEX_NONE;

	return Y * GridWidth + X;
}

FVector ADefenseGridManager::TileIndexToWorld(int32 TileIndex) const {
	if (!Tiles.IsValidIndex(TileIndex)) return GetActorLocation();

	const int32 X = TileIndex % GridWidth;
	const int32 Y = TileIndex / GridWidth;

	// Offset by half a tile so the tower lands on the tile's center.
	const FVector Offset(
		(X + 0.5f) * TileSize,
		(Y + 0.5f) * TileSize,
		0.0f
	);

	return GetActorLocation() + Offset;
}

bool ADefenseGridManager::CanPlaceTower(int32 TileIndex) const {
	if (!Tiles.IsValidIndex(TileIndex)) return false;

	return !Tiles[TileIndex].IsOccupied();
}

bool ADefenseGridManager::PlaceTower(int32 TileIndex, TSubclassOf<ADefenseTowerBase> TowerClass) {
	if (!TowerClass || !CanPlaceTower(TileIndex)) return false;

	UWorld* World = GetWorld();
	if (!World) return false;

	const FVector SpawnLocation = TileIndexToWorld(TileIndex);

	ADefenseTowerBase* Tower = World->SpawnActor<ADefenseTowerBase>(TowerClass, SpawnLocation, FRotator::ZeroRotator);
	if (!Tower) return false;

	Tiles[TileIndex].PlacedTower = Tower;
	return true;
}

TArray<int32> ADefenseGridManager::FindPath(int32 StartIndex, int32 GoalIndex) const {
	TQueue<int32> PathQueue;
	TArray<int32> CameFrom;
	TArray<bool> Visited;
	int32 OutIndex;
	CameFrom.Init(-1, Tiles.Num());
	Visited.SetNum(Tiles.Num());
	PathQueue.Enqueue(StartIndex);
		
	
	while (!PathQueue.IsEmpty()) {		
		PathQueue.Dequeue(OutIndex);
		Visited[OutIndex] = true;
		
		if (OutIndex == GoalIndex) {
			
			break;
		}

	}

	return {};
}


