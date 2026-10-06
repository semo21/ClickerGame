// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/Defense/DefenseGridManager.h"
#include "Gameplay/Actors/Defense/DefenseTowerBase.h"

#include "Algo/Reverse.h"

#include "DrawDebugHelpers.h"
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
	TArray<int32> Path = FindPath(SpawnTileIndex, GoalTileIndex);

	for (int32 i = 0; i < Path.Num()-1; ++i) {
		FVector From = TileIndexToWorld(Path[i]) + FVector(0, 0, 50);
		FVector To = TileIndexToWorld(Path[i + 1]) + FVector(0, 0, 50);

		DrawDebugLine(GetWorld(), From, To, FColor::Green, true, -1.0f, 0, 5.0f);
	}
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
	if(!Tiles.IsValidIndex(StartIndex) || !Tiles.IsValidIndex(GoalIndex)) return {};
	if (StartIndex == GoalIndex) return { StartIndex };

	TQueue<int32> PathQueue;
	TArray<int32> CameFrom;
	TArray<bool> Visited;
	int32 Current = INDEX_NONE;

	CameFrom.Init(INDEX_NONE, Tiles.Num());
	Visited.SetNum(Tiles.Num());
	PathQueue.Enqueue(StartIndex);
	Visited[StartIndex] = true;
	
	const int32 Directions[4][2] = {
		{ 0, -1 }, // Up
		{ 0, 1 },  // Down
		{ -1, 0 }, // Left
		{ 1, 0 }   // Right
	};
	while (!PathQueue.IsEmpty()) {		
		PathQueue.Dequeue(Current);

		if (Current == GoalIndex) {
			TArray<int32> Path;
			while (Current != INDEX_NONE) {
				Path.Add(Current);
				Current = CameFrom[Current];
			}
			Algo::Reverse(Path);

			return Path;
		}
		
		int32 X = Current % GridWidth;
		int32 Y = Current / GridWidth;

		int32 NX, NY;
		for (int32 i = 0; i < 4; ++i) {
			NX = X + Directions[i][0];
			NY = Y + Directions[i][1];

			if (!IsValidCoord(NX, NY)) continue;

			int32 NeighborIndex = NY * GridWidth + NX;
			if (Visited[NeighborIndex] || Tiles[NeighborIndex].IsOccupied()) continue;

			Visited[NeighborIndex] = true;
			CameFrom[NeighborIndex] = Current;
			PathQueue.Enqueue(NeighborIndex);
		}
	}

	return {};
}


