// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Save/SaveManagerSubsystem.h"
#include "Systems/Economy/Data/EconomySnapshot.h"
#include "Systems/Economy/Data/MetaEconomySnapshot.h"
#include "Systems/Save/Data/PlayerSaveGame.h"

#include "Kismet/GameplayStatics.h"

UPlayerSaveGame* USaveManagerSubsystem::LoadOrCreateSaveObject() const {
	if (auto* Existing = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex))) {
		return Existing;
	}
	return Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
}

void USaveManagerSubsystem::SaveProgress(const FEconomySnapshot& S) {
	auto* SaveGameObj = LoadOrCreateSaveObject();

	FEconomySnapshot Stamped = S;
	Stamped.LastSaveTime = FDateTime::UtcNow().ToUnixTimestamp();

	SaveGameObj->LevelSnapshots.Add(TEXT("Clicker"), FInstancedStruct::Make<FEconomySnapshot>(Stamped));
	UGameplayStatics::SaveGameToSlot(SaveGameObj, SaveSlotName, UserIndex);
}

bool USaveManagerSubsystem::LoadProgress(FEconomySnapshot& Out) {
	if (USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex)) {
		if (auto* SaveObj = Cast<UPlayerSaveGame>(Loaded)){
			if (const FInstancedStruct* Found = SaveObj->LevelSnapshots.Find(TEXT("Clicker"))) {
				if (const FEconomySnapshot* Snapshot = Found->GetPtr<FEconomySnapshot>()) {
					Out = *Snapshot;
					return true;
				}
			}
			
			return true;
		}
	}
	return false;
}

void USaveManagerSubsystem::SaveProgress(const FMetaEconomySnapshot& S) {
	auto* SaveGameObj = LoadOrCreateSaveObject();
	SaveGameObj->MetaSnapshot = S;
	UGameplayStatics::SaveGameToSlot(SaveGameObj, SaveSlotName, UserIndex);
}

bool USaveManagerSubsystem::LoadProgress(FMetaEconomySnapshot& Out) {
	if (USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex)) {
		if (auto* SaveObj = Cast<UPlayerSaveGame>(Loaded)) {
			Out = SaveObj->MetaSnapshot;
			return true;
		}
	}
	return false;
}