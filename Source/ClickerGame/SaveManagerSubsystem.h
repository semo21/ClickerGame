// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ClickerSaveGame.h"

#include "SaveManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CLICKERGAME_API USaveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	//void SaveProgress(const class UClickerComponent* ClickerComponent);
	void SaveProgress(const FEconomySnapshot& Snapshot);
	
	//void LoadProgress(class UClickerComponent* ClickerComponent);
	bool LoadProgress(FEconomySnapshot& OutSnapshot);

	
private:
	const FString SaveSlotName = TEXT("ClickerSaveSlot");
	const int32 UserIndex = 0;
};
