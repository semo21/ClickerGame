// Fill out your copyright notice in the Description page of Project Settings.

#include "ClickerComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"	

#include "GameManager.h"
#include "MyPlayerController.h"
#include "ClickerUIManager.h"
#include "SaveManagerSubsystem.h"

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

void UClickerComponent::Initialize(UGameManager* InGameManager) {
	UE_LOG(LogTemp, Warning, TEXT("ClickerComponent Initialize called"));
	UIManager = InGameManager->GetUIManager();

	LoadProgress();

	GetWorld()->GetTimerManager().SetTimer(
		AutoSaveHandle,
		this,
		&UClickerComponent::SaveProgress,
		60.0f,
		true
	);
}

// Called when the game starts
void UClickerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UClickerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	GetWorld()->GetTimerManager().ClearTimer(AutoSaveHandle);
	SaveProgress();

	Super::EndPlay(EndPlayReason);
}

void UClickerComponent::SetUIManager(UClickerUIManager* InUIManager) {
	if (InUIManager) {
		UIManager = InUIManager;
	}
}

void UClickerComponent::SaveProgress() {
	if (!GetWorld() || !GetWorld()->GetGameInstance()) return;
	
	EnsureSaveManager();

	if (SaveManager) {
		SaveManager->SaveProgress(this);
	}
}

void UClickerComponent::LoadProgress() {
	if (!GetWorld() || !GetWorld()->GetGameInstance()) return;

	EnsureSaveManager();

	if (SaveManager) {
		UE_LOG(LogTemp, Warning, TEXT("Load Progress"));
		SaveManager->LoadProgress(this);
	}	
}

void UClickerComponent::EnsureSaveManager() {
	if (!SaveManager) {
		SaveManager = GetWorld()->GetGameInstance()->GetSubsystem<USaveManagerSubsystem>();
	}
}

// Called every frame
void UClickerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (UIManager) {
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		AccumulatedTime += DeltaTime;
		if (AccumulatedTime >= 1.0f)
		{
			Currency += CurrencyPerSecond;
			if (UIManager) {
				UIManager->ShowIdleReward(CurrencyPerSecond);
				//UE_LOG(LogTemp, Warning, TEXT("ClickerComponent Tick"));
			}
			AccumulatedTime = 0.0f;

			if (!CachedMyPlayerController) {
				CachedMyPlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
			}
			if (CachedMyPlayerController) {
				CachedMyPlayerController->UpdateCurrencyUI();
			}
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

int32 UClickerComponent::GetUpgradeLevel() const {
	return UpgradeLevel;
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

void UClickerComponent::SetUpgradeLevel(int32 NewUpgradeLevel) {
	UpgradeLevel = NewUpgradeLevel;
}

void UClickerComponent::SetCurrency(float NewCurrency) {
	Currency = NewCurrency;
}

void UClickerComponent::SetOfflineReward(float OfflineReward) {	
	UE_LOG(LogTemp, Warning, TEXT("SetOfflineReward"));
	if (UIManager) {
		Currency += OfflineReward;
		UIManager->ShowOfflineReward(OfflineReward);
	}	
}

void UClickerComponent::SetCurrencyPerClick(float NewCurrencyPerClick) {
	CurrencyPerClick = NewCurrencyPerClick;
}

void UClickerComponent::SetCurrencyPerSecond(float NewCurrencyPerSecond) {
	CurrencyPerSecond = NewCurrencyPerSecond;
}

void UClickerComponent::RecalculateStats() {
	Currency -= GetUpgradeCost();
	CurrencyPerClick += 1.0f;
	UpgradeLevel++;
}