// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "SaveManagerSubsystem.generated.h"

struct FEconomySnapshot;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API USaveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void SaveProgress(const FEconomySnapshot& Snapshot);	
	bool LoadProgress(FEconomySnapshot& OutSnapshot);
	
private:
	const FString SaveSlotName = TEXT("ClickerSaveSlot");
	const int32 UserIndex = 0;
};
