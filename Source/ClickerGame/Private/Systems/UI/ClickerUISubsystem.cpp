// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/UI/ClickerUISubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Engine/GameViewportClient.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

#include "Gameplay/Player/ClickerPlayerController.h"
#include "Gameplay/GameMode/ClickerGameMode.h"
#include "Systems/Economy/ClickerEconomySubsystem.h"
#include "Systems/UI/GlobalUISubsystem.h"
#include "Systems/UI/Widgets/Root/ClickerHUDRootWidget.h"
#include "Systems/UI/Widgets/Toast/ToastWidgetBase.h"
#include "Systems/UI/Widgets/Toast/ClickFloatingTextWidget.h"
#include "Systems/UI/Widgets/Toast/IdleRewardTextWidget.h"
#include "Systems/UI/Settings/ClickerUISettings.h"
#include "Systems/UI/Data/ActionButton/ActionButtonRegistry.h"

// public field
void UClickerUISubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	if (!UISettingsAsset.IsNull()) {
		if (UClickerUISettings* Settings = UISettingsAsset.LoadSynchronous()) {
			RewardToastClass = Settings->IdleRewardTextWidgetClass;
			FloatingTextWidgetClass = Settings->FloatingTextWidgetClass;
			OfflineRewardSound = Settings->OfflineRewardSound.LoadSynchronous();
		}
	}

	if (!ActionButtonRegistryAsset.IsNull()) {
		ActionButtonRegistry = ActionButtonRegistryAsset.LoadSynchronous();
	}}

void UClickerUISubsystem::Deinitialize() {
	if (EconomySubsystemRef) {
		EconomySubsystemRef->OnEconomyChanged.RemoveDynamic(this, &UClickerUISubsystem::OnEconomyChanged);
		EconomySubsystemRef->OnPassiveIncome.RemoveDynamic(this, &UClickerUISubsystem::OnPassiveIncome);
	}

	EconomySubsystemRef = nullptr;
	FloatingTextPool.Empty();
	RewardPool.Empty();
	PlayerController.Reset();

	Super::Deinitialize();
}

void UClickerUISubsystem::InitializeHUDRoot(AClickerPlayerController* PC) {
	if (!ensure(PC)) return;
	PlayerController = PC;

	auto* GlobalUI = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalUISubsystem>();
	if (!ensure(GlobalUI)) return;
	auto* RootWidget = Cast<UClickerHUDRootWidget>(GlobalUI->GetCurrentRootWidget());
	if (!ensure(RootWidget)) return;

	RootWidget->InitializeHUDRoot(this, PC);
	if (const double Reward = EconomySubsystemRef->GetLastOfflineReward(); Reward > 0.0) {
		ShowReward(Reward, true);
	}
}

void UClickerUISubsystem::BindEconomySubsystem(UClickerEconomySubsystem* Eco) {
	EconomySubsystemRef = Eco;

	if (!EconomySubsystemRef) return;

	EconomySubsystemRef->OnEconomyChanged.AddUniqueDynamic(this, &ThisClass::OnEconomyChanged);
	EconomySubsystemRef->OnPassiveIncome.AddUniqueDynamic(this, &ThisClass::OnPassiveIncome);

	CachedClickerEconomySnapshot = EconomySubsystemRef->GetSnapshot();
	OnEconomyChangedUI.Broadcast(CachedClickerEconomySnapshot);
}

const FActionButtonDefinition* UClickerUISubsystem::FindActionButtonDefinition(const FGameplayTag& Tag) const {
	if (!ActionButtonRegistry || !Tag.IsValid()) return nullptr;

	return ActionButtonRegistry->Find(Tag);
}

void UClickerUISubsystem::OnEconomyChanged(const FClickerEconomySnapshot& Snapshot) {
	CachedClickerEconomySnapshot = Snapshot;
	OnEconomyChangedUI.Broadcast(CachedClickerEconomySnapshot);
}

void UClickerUISubsystem::OnPassiveIncome(double AmountPerSec) {
	HandlePassiveIncome(AmountPerSec);
}

// private field
void UClickerUISubsystem::HandlePassiveIncome(double Amount) {
	ShowReward(Amount, false);
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
	const FVector2D ScreenPos(640.0f, 120.0f);

	if (UToastWidgetBase* Widget = GetWidgetFromPool(RewardPool, RewardToastClass)) {
		FString Text = bIsOffline
			? FString::Printf(TEXT("+%.0f (Offline)"), Amount)
			: FString::Printf(TEXT("+%.0f"), Amount);

		Widget->SetupToast(FText::FromString(Text), ScreenPos);
		Widget->PlayToast();
	}

	if (bIsOffline && OfflineRewardSound) {
		UGameplayStatics::PlaySound2D(this, OfflineRewardSound);
	}
}

TSubclassOf<AGameModeBase> UClickerUISubsystem::GetRequiredGameModeClass() const {
	return AClickerGameMode::StaticClass();
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