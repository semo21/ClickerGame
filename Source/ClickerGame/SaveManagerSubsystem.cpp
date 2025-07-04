// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "ClickerComponent.h"

void USaveManagerSubsytem::SaveProgress(const UClickerComponent* ClickerComponent) {
	if (!ClickerComponent) return;
	
	//FString SaveDir = FPaths::ProjectSavedDir() + TEXT("SaveGames/");
	//UE_LOG(LogTemp, Warning, TEXT("Save directory: %s"), *SaveDir);

	UClickerSaveGame* SaveGameInstance = Cast<UClickerSaveGame>(UGameplayStatics::CreateSaveGameObject(UClickerSaveGame::StaticClass()));

	SaveGameInstance->Currency = ClickerComponent->GetCurrency();
	SaveGameInstance->CurrencyPerClick = ClickerComponent->GetCurrencyPerClick();
	SaveGameInstance->CurrencyPerSecond = ClickerComponent->GetCurrencyPerSecond();
	SaveGameInstance->UpgradeLevel = ClickerComponent->GetUpgradeLevel();

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);
}

void USaveManagerSubsystem::LoadProgress(UClickerComponent* ClickerComponent) {
	if (!ClickerComponent) return;

	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex)) {
		UClickerSaveGame* LoadedGame = Cast<UClickerSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));

		if (LoadedGame) {
			ClickerComponent->SetUpgradeLevel(LoadedGame->UpgradeLevel);
			ClickerComponent->SetCurrency(LoadedGame->Currency);
			ClickerComponent->SetCurrencyPerClick(LoadedGame->CurrencyPerClick);
			ClickerComponent->SetCurrencyPerSecond(LoadedGame->CurrencyPerSecond);
		}
	}
}