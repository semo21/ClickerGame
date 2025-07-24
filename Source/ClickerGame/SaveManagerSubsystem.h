// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ClickerSaveGame.h"

#include "SaveManagerSubsystem.generated.h"

class UClickerComponent;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API USaveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void SaveProgress(const class UClickerComponent* ClickerComponent);
	void LoadProgress(class UClickerComponent* CLickerComponent);

private:
	const FString SaveSlotName = TEXT("ClickerSaveSlot");
	const int32 UserIndex = 0;
};
