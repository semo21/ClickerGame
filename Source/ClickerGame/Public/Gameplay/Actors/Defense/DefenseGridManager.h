// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DefenseGridManager.generated.h"

class ADefenseTowerBase;

USTRUCT()
struct FDefenseTileData {
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<ADefenseTowerBase> PlacedTower = nullptr;

	bool IsOccupied() const { return PlacedTower != nullptr; }
};

UCLASS()
class CLICKERGAME_API ADefenseGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefenseGridManager();
	int32 WorldToTileIndex(const FVector& WorldLocation) const;
	FVector TileIndexToWorld(int32 TileIndex) const;
	bool CanPlaceTower(int32 TileIndex) const;
	bool PlaceTower(int32 TileIndex, TSubclassOf<ADefenseTowerBase> TowerClass);
	TArray<int32> FindPath(int32 StartIndex, int32 GoalIndex) const;	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Grid")
	int32 GridWidth = 10;

	UPROPERTY(EditAnywhere, Category="Grid")
	int32 GridHeight = 10;

	UPROPERTY(EditAnywhere, Category="Grid")
	float TileSize = 100.0f;

	UPROPERTY(EditAnywhere, Category="Path")
	int32 SpawnTileIndex = 0;

	UPROPERTY(EditAnywhere, Category="Path")
	int32 GoalTileIndex = 99;

private:
	bool IsValidCoord(int32 X, int32 Y) const;

	UPROPERTY()
	TArray<FDefenseTileData> Tiles;

	UPROPERTY()
	TArray<int32> CurrentPath;

	void RecalculatePath();
	void DrawDebugPath() const;
};
