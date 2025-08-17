// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "ClickerComponent.h"

//void USaveManagerSubsystem::SaveProgress(const UClickerComponent* ClickerComponent) {
//	if (!ClickerComponent) return;
//
//	//FString SaveDir = FPaths::ProjectSavedDir() + TEXT("SaveGames/");
//	//UE_LOG(LogTemp, Warning, TEXT("Save directory: %s"), *SaveDir);
//
//	UClickerSaveGame* SaveGameInstance = Cast<UClickerSaveGame>(UGameplayStatics::CreateSaveGameObject(UClickerSaveGame::StaticClass()));
//
//	SaveGameInstance->Currency = ClickerComponent->GetCurrency();
//	SaveGameInstance->CurrencyPerClick = ClickerComponent->GetCurrencyPerClick();
//	SaveGameInstance->CurrencyPerSecond = ClickerComponent->GetCurrencyPerSecond();
//	SaveGameInstance->UpgradeLevel = ClickerComponent->GetUpgradeLevel();
//	SaveGameInstance->LastSaveUnixTime = FDateTime::UtcNow().ToUnixTimestamp();
//
//	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);
//
//	if (GEngine) {
//		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan, TEXT("Saved!"));
//	}
//}

void USaveManagerSubsystem::SaveProgress(const FEconomySnapshot& S) {
	auto* SaveGameObj = Cast<UClickerSaveGame>(UGamePlayStatics::CreateSaveGameObject(UClickerSaveGame::StaticClass()));
	SaveGameObj.Currency = S.Currency;
	SaveGameObj.CurrencyPerClick = S.CurrencyPerClick;
	SaveGameObj.CurrencyPerSecond = S.CurrencyPerSecond;
	SaveGameObj.UpgradeLevel = S.UpgradeLevel;
	SaveGameObj.LastSaveUnixTime = FDateTime::UtcNow().ToUnixTimestamp();
	UGamePlayStatics::SaveGameToSlot(SaveGameObj, SaveSlotName, UserIndex);
}

//void USaveManagerSubsystem::LoadProgress(UClickerComponent* ClickerComponent) {
//	if (!ClickerComponent) return;
//
//	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex)) {
//		UClickerSaveGame* LoadedGame = Cast<UClickerSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
//
//		ClickerComponent->SetUpgradeLevel(LoadedGame->UpgradeLevel);		
//		ClickerComponent->SetCurrencyPerClick(LoadedGame->CurrencyPerClick);
//		ClickerComponent->SetCurrencyPerSecond(LoadedGame->CurrencyPerSecond);
//		ClickerComponent->SetCurrency(LoadedGame->Currency);
//
//		const int32 Now = FDateTime::UtcNow().ToUnixTimestamp();
//		int32 DeltaSec = Now - LoadedGame->LastSaveUnixTime;
//		DeltaSec = FMath::Clamp(DeltaSec, 0, 3600 * 24 * 7);
//		const float OfflineReward = LoadedGame->CurrencyPerSecond * DeltaSec;
//		ClickerComponent->SetOfflineReward(OfflineReward);
//		
//		
//	}
//}

bool USaveManagerSubsystem::LoadProgress(FEconomySnapshot& Out) {
	if (USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex)) {
		if (auto* SaveObj = Cast<UClickerSaveGame>(Loaded))){
			Out.Currency = SaveObj->Currency;
			Out.CurrencyPerClick = SaveObj->CurrencyPerClick;
			Out.CurrencyPerSecond = SaveObj->CurrencyPerSecond;
			Out.UpgradeLevel = SaveObj->UpgradeLevel;
			
			return true;
		}
	}
}
