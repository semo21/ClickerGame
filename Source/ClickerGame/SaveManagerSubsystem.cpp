// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "ClickerEconomySubsystem.h"
#include "ClickerSaveGame.h"
void USaveManagerSubsystem::SaveProgress(const FEconomySnapshot& S) {
	auto* SaveGameObj = Cast<UClickerSaveGame>(UGameplayStatics::CreateSaveGameObject(UClickerSaveGame::StaticClass()));
	SaveGameObj->Currency = S.Currency;
	SaveGameObj->CurrencyPerClick = S.CurrencyPerClick;
	SaveGameObj->CurrencyPerSecond = S.CurrencyPerSecond;
	SaveGameObj->UpgradeLevel = S.UpgradeLevel;
	SaveGameObj->LastSaveUnixTime = FDateTime::UtcNow().ToUnixTimestamp();
	UGameplayStatics::SaveGameToSlot(SaveGameObj, SaveSlotName, UserIndex);
}

bool USaveManagerSubsystem::LoadProgress(FEconomySnapshot& Out) {
	if (USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex)) {
		if (auto* SaveObj = Cast<UClickerSaveGame>(Loaded)){
			Out.Currency = SaveObj->Currency;
			Out.CurrencyPerClick = SaveObj->CurrencyPerClick;
			Out.CurrencyPerSecond = SaveObj->CurrencyPerSecond;
			Out.UpgradeLevel = SaveObj->UpgradeLevel;
			
			return true;
		}
	}
	return false;
}
