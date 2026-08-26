// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/UI/ClickerUISubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Engine/GameViewportClient.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TimerManager.h"

#include "Gameplay/Player/MyPlayerController.h"
#include "Systems/Economy/ClickerEconomySubsystem.h"
#include "Systems/UI/Widgets/Root/ClickerHUDRootWidgetBase.h"
#include "Systems/UI/Widgets/Toast/ToastWidgetBase.h"
#include "Systems/UI/Widgets/Toast/ClickFloatingTextWidget.h"
#include "Systems/UI/Widgets/Toast/IdleRewardTextWidget.h"
#include "Systems/UI/Settings/ClickerUISettings.h"
#include "Systems/UI/Data/ActionButton/ActionButtonRegistry.h"

// public field
void UClickerUISubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	EconomySubsystemRef = GetWorld()->GetSubsystem<UClickerEconomySubsystem>();
	checkf(EconomySubsystemRef, TEXT("UClickerUISubsystem::Initialize EconomySubsystemRef is null"));
	if (!EconomySubsystemRef)	return;

	EconomySubsystemRef->OnEconomyChanged.AddUniqueDynamic(this, &ThisClass::OnEconomyChanged);
	EconomySubsystemRef->OnPassiveIncome.AddUniqueDynamic(this, &ThisClass::OnPassiveIncome);
	EconomySubsystemRef->OnOfflineReward.AddUniqueDynamic(this, &ThisClass::OnOfflineReward);
	
	CachedEconomySnapshot = EconomySubsystemRef->GetSnapshot();
	OnEconomyChangedUI.Broadcast(CachedEconomySnapshot);	

	UE_LOG(LogTemp, Warning, TEXT("UISettingsAsset: %s, ActionButtonRegistryAsset: %s"), *UISettingsAsset.ToString(), *ActionButtonRegistryAsset.ToString());
	if (!UISettingsAsset.IsNull()) {
		UE_LOG(LogTemp, Warning, TEXT("UISubsystem::Initialize Found DA"));

		if (UClickerUISettings* Settings = UISettingsAsset.LoadSynchronous()) {
			UE_LOG(LogTemp, Warning, TEXT("UISubsystem::Initialize DA Load"));

			InGameRootWidgetClass = Settings->InGameRootWidgetClass;
			ClickEffectAsset = Settings->ClickEffectAsset.LoadSynchronous();
			RewardToastClass = Settings->IdleRewardTextWidgetClass;
			FloatingTextWidgetClass = Settings->FloatingTextWidgetClass;
			ClickRewardSound = Settings->ClickRewardSound.LoadSynchronous();
			OfflineRewardSound = Settings->OfflineRewardSound.LoadSynchronous();
		}
	}

	if (!ActionButtonRegistryAsset.IsNull()) {
		UE_LOG(LogTemp, Warning, TEXT("UISubsystem::Initialize Found ActionButtonRegistry"));
		ActionButtonRegistry = ActionButtonRegistryAsset.LoadSynchronous();
		UE_LOG(LogTemp, Warning, TEXT("UISubsystem::Initialize ActionButtonRegistry Load = %s"), ActionButtonRegistry ? TEXT("Success") : TEXT("Failed"));

	}
}

void UClickerUISubsystem::Deinitialize() {
	if (EconomySubsystemRef) {
		EconomySubsystemRef->OnEconomyChanged.RemoveDynamic(this, &UClickerUISubsystem::OnEconomyChanged);
		EconomySubsystemRef->OnPassiveIncome.RemoveDynamic(this, &UClickerUISubsystem::OnPassiveIncome);
		EconomySubsystemRef->OnOfflineReward.RemoveDynamic(this, &UClickerUISubsystem::OnOfflineReward);
	}
	if (auto* PC = PlayerController.Get()) {
		PC->GetWorldTimerManager().ClearTimer(UpgradeSuccessTimerHandle);
	}

	InGameRootWidget = nullptr;
	CurrencyText = ClickValueText = UpgradeCostText = PassiveIncomeText = UpgradeSuccessText = nullptr;
	UpgradeButton = SaveButton = LoadButton = nullptr;
	EconomySubsystemRef = nullptr;
	FloatingTextPool.Empty();
	RewardTextPool.Empty();
	PlayerController.Reset();

	Super::Deinitialize();
}

void UClickerUISubsystem::ShowHUD(UWorld* World) {
	if (!World || InGameRootWidget || !InGameRootWidgetClass) return;

	if (!PlayerController.IsValid()) {
		if (auto* PC = World->GetFirstPlayerController()) {
			PlayerController = Cast<AMyPlayerController>(PC);
		}

		if (!PlayerController.IsValid()) return;
	}

	InGameRootWidget = CreateWidget<UUserWidget>(World, InGameRootWidgetClass);
	if (!InGameRootWidget) return;
	InGameRootWidget->AddToViewport();

	if (auto* Root = Cast<UClickerHUDRootWidgetBase>(InGameRootWidget)) {
		Root->InitializeHUDRoot(this, Cast<AMyPlayerController>(PlayerController.Get()));
	}

	//if (UpgradeSuccessText)	UpgradeSuccessText->SetVisibility(ESlateVisibility::Collapsed);

	//if (auto* PC = Cast<AMyPlayerController>(PlayerController.Get())) {
	//	if (UpgradeButton)
	//		UpgradeButton->OnClicked.AddDynamic(PC, &AMyPlayerController::OnUpgradeClicked);

	//	if (SaveButton)
	//		SaveButton->OnClicked.AddDynamic(PC, &AMyPlayerController::OnSaveClicked);

	//	if (LoadButton)
	//		LoadButton->OnClicked.AddDynamic(PC, &AMyPlayerController::OnLoadClicked);
	//}
	//	
	//if (EconomySubsystemRef) {
	//	OnEconomyChanged(EconomySubsystemRef->GetSnapshot());
	//}
	bHUDReady = true;
	TryFlushOfflineReward();
}

void UClickerUISubsystem::ShowClickEffect(const FVector& WorldLocation) {
	if (!PlayerController.IsValid() || !ClickEffectAsset) return;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(PlayerController->GetWorld(), ClickEffectAsset, WorldLocation, FRotator::ZeroRotator, FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);
}

void UClickerUISubsystem::ShowOfflineReward(float OfflineReward) {
	ShowReward(OfflineReward, true);
}

void UClickerUISubsystem::ShowUpgradeSuccessText() {
	if (UpgradeSuccessText && PlayerController.IsValid()) {
		UpgradeSuccessText->SetVisibility(ESlateVisibility::Visible);

		PlayerController->GetWorldTimerManager().SetTimer(
			UpgradeSuccessTimerHandle,
			this,
			&UClickerUISubsystem::HideUpgradeSuccessText,
			2.0f,
			false
		);
	}
}

void UClickerUISubsystem::HideUpgradeSuccessText() {
	if (UpgradeSuccessText) {
		UpgradeSuccessText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

const FActionButtonDefinition* UClickerUISubsystem::FindActionButtonDefinition(const FGameplayTag& Tag) const {
	UE_LOG(LogTemp, Warning, TEXT("UISubsystem::FindActionButtonDefinition Tag: %s"), *Tag.ToString());
	if (!ActionButtonRegistry || !Tag.IsValid()) return nullptr;

	return ActionButtonRegistry->Find(Tag);
}

void UClickerUISubsystem::OnEconomyChanged(const FEconomySnapshot& Snapshot) {
	CachedEconomySnapshot = Snapshot;
	OnEconomyChangedUI.Broadcast(CachedEconomySnapshot);
	UpdateScore(Snapshot);	// HUDRoot 리팩터 후 이 부분은 HUDRoot에서 처리하도록 변경 예정
}

void UClickerUISubsystem::OnPassiveIncome(double AmountPerSec) {
	HandlePassiveIncome(AmountPerSec);
}

void UClickerUISubsystem::OnOfflineReward(double Amount) {
	if (Amount <= 0.0) return;

	PendingOfflineReward += Amount;
	TryFlushOfflineReward();
}

// private field
void UClickerUISubsystem::UpdateScore(const FEconomySnapshot& Snapshot) {
	UE_LOG(LogTemp, Warning, TEXT("UISubsystem::UpdateScore Currency: %.2f, ClickValue: %.2f, UpgradeCost: %.2f, PassiveIncome: %.2f"), Snapshot.Currency, Snapshot.CurrencyPerClick, FMath::Pow(Snapshot.UpgradeGrowth, Snapshot.UpgradeLevel + 1) * Snapshot.UpgradeCostBase, Snapshot.CurrencyPerSecond);

	if (CurrencyText)
		CurrencyText->SetText(FText::FromString(FString::Printf(TEXT("Currency: %.2f"), Snapshot.Currency)));

	if (ClickValueText)
		ClickValueText->SetText(FText::FromString(FString::Printf(TEXT("Click Value: %.2f"), Snapshot.CurrencyPerClick)));

	if (UpgradeCostText)
		UpgradeCostText->SetText(FText::FromString(FString::Printf(TEXT("Upgrade Cost: %.2f"), FMath::Pow(Snapshot.UpgradeGrowth, Snapshot.UpgradeLevel + 1) * Snapshot.UpgradeCostBase)));

	UE_LOG(LogTemp, Warning, TEXT("UISubsystem::UpgradeCost: %.2f"), FMath::Pow(Snapshot.UpgradeGrowth, Snapshot.UpgradeLevel + 1) * Snapshot.UpgradeCostBase);

	if (PassiveIncomeText)
		PassiveIncomeText->SetText(FText::FromString(FString::Printf(TEXT("Passive Income: %.2f / sec"), Snapshot.CurrencyPerSecond)));

}

void UClickerUISubsystem::HandlePassiveIncome(double Amount) {
	ShowReward(Amount, false);
}

void UClickerUISubsystem::HandleOfflineReward(double Amount) {
	ShowReward(Amount, true);
}

void UClickerUISubsystem::ShowFloatingText(const FString& Message, const FVector& WorldLocation) {
	if (!FloatingTextWidgetClass || !PlayerController.IsValid())	return;

	FVector2D ScreenPos;
	if (UGameplayStatics::ProjectWorldToScreen(PlayerController.Get(), WorldLocation, ScreenPos)) {
		if (UToastWidgetBase* Widget = GetWidgetFromPool(FloatingTextPool, FloatingTextWidgetClass)) {
			Widget->SetupToast(FText::FromString(Message), ScreenPos);
			Widget->PlayToast();
		}
	}
}

void UClickerUISubsystem::ShowReward(double Amount, bool bIsOffline) {
	if (!RewardToastClass)	return;
	UE_LOG(LogTemp, Warning, TEXT("UISubsystem::ShowReward Amount: %.2f, bIsOffline: %d"), Amount, bIsOffline);
	const FVector2D ScreenPos(640.0f, 120.0f);

	if (UToastWidgetBase* Widget = GetWidgetFromPool(RewardPool, RewardToastClass)) {
		FString Text = bIsOffline
			? FString::Printf(TEXT("+%.0f (Offline)"), Amount)
			: FString::Printf(TEXT("+%.0f"), Amount);

		Widget->SetupToast(FText::FromString(Text), ScreenPos);
		Widget->PlayToast();
	}
}

UToastWidgetBase* UClickerUISubsystem::GetWidgetFromPool(TArray<UToastWidgetBase*>& Pool, TSubclassOf<UToastWidgetBase> ToastWidgetClass) {
	for (auto* W : Pool) {
		if (W && W->IsAvailable()) {
			return W;
		}
	}

	if (ToastWidgetClass && PlayerController.IsValid()) {
		UToastWidgetBase* NewWidget = CreateWidget<UToastWidgetBase>(PlayerController.Get(), ToastWidgetClass);
		if (NewWidget) {
			NewWidget->AddToViewport(11);
			NewWidget->SetVisibility(ESlateVisibility::Collapsed);
			Pool.Add(NewWidget);
			return NewWidget;
		}
	}

	return nullptr;
}

void UClickerUISubsystem::TryFlushOfflineReward() {
	if (!bHUDReady || PendingOfflineReward <= 0.0)	return;

	const double amount = PendingOfflineReward;
	PendingOfflineReward = 0.0;

	ShowReward(amount, true);
}