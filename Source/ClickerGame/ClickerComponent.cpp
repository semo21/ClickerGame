// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickerComponent.h"
#include "Engine/Engine.h"	
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ClickerSaveGame.h"

// Sets default values for this component's properties
UClickerComponent::UClickerComponent() : UpgradeCostBase(10.0f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ClickCount = 0;
	Currency = 0.0f;
	CurrencyPerClick = 1.0f; // Default value for currency earned per click
	CurrencyPerSecond = 2.0f;
	AccumulatedTime = 0.0f;
}


// Called when the game starts
void UClickerComponent::BeginPlay()
{
	Super::BeginPlay();

	LoadProgress();
}


// Called every frame
void UClickerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AccumulatedTime += DeltaTime;
	if (AccumulatedTime >= 1.0f)
	{
		Currency += CurrencyPerSecond;
		AccumulatedTime = 0.0f;

		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Passive Income! Currency: %.2f"), Currency));

		if (!CachedMyPlayerController) {
			CachedMyPlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
		}
		if (CachedMyPlayerController) {
			CachedMyPlayerController->UpdateCurrencyUI();
		}
	}
}

void UClickerComponent::HandleClick() {

	ClickCount++;
	Currency += CurrencyPerClick;
}

void UClickerComponent::HandleUpgrade() {

	FString Message = TEXT("Click logic started");

	if (Currency >= GetUpgradeCost()) {
		RecalculateStats();
		SaveProgress();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("통화 부족!"));
	}
}

float UClickerComponent::GetCurrency() const {
	return Currency;
}

float UClickerComponent::GetCurrencyPerClick() const {
	return CurrencyPerClick;
}

float UClickerComponent::GetUpgradeCost() const {
	return FMath::Pow(1.5f, UpgradeLevel + 1) * UpgradeCostBase;
}

float UClickerComponent::GetCurrencyPerSecond() const {
	return CurrencyPerSecond;
}

void UClickerComponent::SaveProgress() {
	UClickerSaveGame* SaveGameInstance = Cast<UClickerSaveGame>(UGameplayStatics::CreateSaveGameObject(UClickerSaveGame::StaticClass()));

	if (SaveGameInstance) {
		SaveGameInstance->Currency = Currency;
		SaveGameInstance->CurrencyPerClick = CurrencyPerClick;
		SaveGameInstance->CurrencyPerSecond = CurrencyPerSecond;
		SaveGameInstance->UpgradeLevel = UpgradeLevel;

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("PlayerSaveSlot"), 0);
	}
}

void UClickerComponent::LoadProgress() {
	if (UGameplayStatics::DoesSaveGameExist(TEXT("PlayerSaveSlot"), 0)) {
		UClickerSaveGame* LoadedGame = Cast<UClickerSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSaveSlot"), 0));

		if (LoadedGame) {
			Currency = LoadedGame->Currency;
			CurrencyPerClick = LoadedGame->CurrencyPerClick;
			CurrencyPerSecond = LoadedGame->CurrencyPerSecond;
			UpgradeLevel = LoadedGame->UpgradeLevel;			
		}
	}
}

void UClickerComponent::RecalculateStats() {
	Currency -= GetUpgradeCost();
	CurrencyPerClick += 1.0f;
	UpgradeLevel++;
}