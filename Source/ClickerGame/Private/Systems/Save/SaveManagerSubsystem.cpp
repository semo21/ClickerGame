// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Save/SaveManagerSubsystem.h"
#include "Systems/Economy/Data/ClickerEconomySnapshot.h"
#include "Systems/Economy/Data/GlobalEconomySnapshot.h"
#include "Systems/Progress/Data/GlobalProgressSnapshot.h"
#include "Systems/Save/Data/PlayerSaveGame.h"

#include "Kismet/GameplayStatics.h"

UPlayerSaveGame* USaveManagerSubsystem::LoadOrCreateSaveObject() const {
	if (auto* Existing = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex))) {
		return Existing;
	}
	return Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
}

void USaveManagerSubsystem::SaveProgress(const FClickerEconomySnapshot& S) {
	auto* SaveGameObj = LoadOrCreateSaveObject();

	FClickerEconomySnapshot Stamped = S;
	Stamped.LastSaveTime = FDateTime::UtcNow().ToUnixTimestamp();

	SaveGameObj->LevelSnapshots.Add(TEXT("Clicker"), FInstancedStruct::Make<FClickerEconomySnapshot>(Stamped));
	UGameplayStatics::SaveGameToSlot(SaveGameObj, SaveSlotName, UserIndex);
}

bool USaveManagerSubsystem::LoadProgress(FClickerEconomySnapshot& Out) {
	if (USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex)) {
		if (auto* SaveObj = Cast<UPlayerSaveGame>(Loaded)){
			if (const FInstancedStruct* Found = SaveObj->LevelSnapshots.Find(TEXT("Clicker"))) {
				if (const FClickerEconomySnapshot* Snapshot = Found->GetPtr<FClickerEconomySnapshot>()) {
					Out = *Snapshot;
					return true;
				}
			}
			
			return true;
		}
	}
	return false;
}

void USaveManagerSubsystem::SaveProgress(const FGlobalEconomySnapshot& S) {
	auto* SaveGameObj = LoadOrCreateSaveObject();
	SaveGameObj->GlobalEconomySnapshot = S;
	UGameplayStatics::SaveGameToSlot(SaveGameObj, SaveSlotName, UserIndex);
}

bool USaveManagerSubsystem::LoadProgress(FGlobalEconomySnapshot& Out) {
	if (USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex)) {
		if (auto* SaveObj = Cast<UPlayerSaveGame>(Loaded)) {
			Out = SaveObj->GlobalEconomySnapshot;
			return true;
		}
	}
	return false;
}

void USaveManagerSubsystem::SaveProgress(const FGlobalProgressSnapshot& S) {
	auto* SaveGameObj = LoadOrCreateSaveObject();
	SaveGameObj->GlobalProgressSnapshot = S;
	UGameplayStatics::SaveGameToSlot(SaveGameObj, SaveSlotName, UserIndex);
}

bool USaveManagerSubsystem::LoadProgress(FGlobalProgressSnapshot& Out) {
	if (USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex)) {
		if (auto* SaveObj = Cast<UPlayerSaveGame>(Loaded)) {
			Out = SaveObj->GlobalProgressSnapshot;
			return true;
		}
	}
	return false;
}