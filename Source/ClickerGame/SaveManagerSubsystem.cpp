// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "ClickerComponent.h"

void USaveManagerSubsystem::SaveProgress(const UClickerComponent* ClickerComponent) {
	if (!ClickerComponent) return;

	//FString SaveDir = FPaths::ProjectSavedDir() + TEXT("SaveGames/");
	//UE_LOG(LogTemp, Warning, TEXT("Save directory: %s"), *SaveDir);

	UClickerSaveGame* SaveGameInstance = Cast<UClickerSaveGame>(UGameplayStatics::CreateSaveGameObject(UClickerSaveGame::StaticClass()));

	SaveGameInstance->Currency = ClickerComponent->GetCurrency();
	SaveGameInstance->CurrencyPerClick = ClickerComponent->GetCurrencyPerClick();
	SaveGameInstance->CurrencyPerSecond = ClickerComponent->GetCurrencyPerSecond();
	SaveGameInstance->UpgradeLevel = ClickerComponent->GetUpgradeLevel();
	SaveGameInstance->LastSaveUnixTime = FDateTime::UtcNow().ToUnixTimestamp();

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan, TEXT("Saved!"));
	}
}

void USaveManagerSubsystem::LoadProgress(UClickerComponent* ClickerComponent) {
	if (!ClickerComponent) return;

	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex)) {
		UClickerSaveGame* LoadedGame = Cast<UClickerSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));

		const int32 Now = FDateTime::UtcNow().ToUnixTimestamp();
		int32 DeltaSec = Now - LoadedGame->LastSaveUnixTime;
		DeltaSec = FMath::Clamp(DeltaSec, 0, 3600 * 24 * 7);
		
		ClickerComponent->SetUpgradeLevel(LoadedGame->UpgradeLevel);		
		ClickerComponent->SetCurrencyPerClick(LoadedGame->CurrencyPerClick);
		ClickerComponent->SetCurrencyPerSecond(LoadedGame->CurrencyPerSecond);
				
		const float Reward = LoadedGame->CurrencyPerSecond * DeltaSec;
		ClickerComponent->SetCurrency(LoadedGame->Currency + Reward);
	}
}
