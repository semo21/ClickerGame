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
#include "Systems/UI/Widgets/ToastWidgetBase.h"
#include "Systems/UI/Widgets/Toast/ClickFloatingTextWidget.h"
#include "Systems/UI/Widgets/Toast/IdleRewardTextWidget.h"
#include "Systems/UI/Settings/ClickerUISettings.h"

// public field
void UClickerUISubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	Collection.InitializeDependency(UClickerEconomySubsystem::StaticClass());

	EconomySubsystemRef = GetGameInstance()->GetSubsystem<UClickerEconomySubsystem>();
	checkf(EconomySubsystemRef, TEXT("UClickerUISubsystem::Initialize EconomySubsystemRef is null"));

	EconomySubsystemRef->OnEconomyChanged.AddUniqueDynamic(this, &ThisClass::OnEconomyChanged);
	EconomySubsystemRef->OnPassiveIncome.AddUniqueDynamic(this, &ThisClass::OnPassiveIncome);
	EconomySubsystemRef->OnOfflineReward.AddUniqueDynamic(this, &ThisClass::OnOfflineReward);

	if (!UISettingsAsset.IsNull()) {
		UE_LOG(LogTemp, Warning, TEXT("UISubsystem::Initialize Found DA"));

		if (UClickerUISettings* Settings = UISettingsAsset.LoadSynchronous()) {
			UE_LOG(LogTemp, Warning, TEXT("UISubsystem::Initialize DA Load"));

			HUDWidgetClass = Settings->HUDWidgetClass;
			ClickEffectAsset = Settings->ClickEffectAsset.LoadSynchronous();
			RewardToastClass = Settings->IdleRewardTextWidgetClass;
			FloatingTextWidgetClass = Settings->FloatingTextWidgetClass;
			ClickRewardSound = Settings->ClickRewardSound.LoadSynchronous();
			OfflineRewardSound = Settings->OfflineRewardSound.LoadSynchronous();
		}
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

	HUDWidget = nullptr;
	CurrencyText = ClickValueText = UpgradeCostText = PassiveIncomeText = UpgradeSuccessText = nullptr;
	UpgradeButton = SaveButton = LoadButton = nullptr;
	EconomySubsystemRef = nullptr;
	FloatingTextPool.Empty();
	RewardTextPool.Empty();
	PlayerController.Reset();

	Super::Deinitialize();
}

void UClickerUISubsystem::ShowHUD(UWorld* World) {
	if (!World || HUDWidget || !HUDWidgetClass) return;

	if (!PlayerController.IsValid()) {
		if (auto* PC = World->GetFirstPlayerController()) {
			PlayerController = Cast<AMyPlayerController>(PC);
		}

		if (!PlayerController.IsValid()) return;
	}

	if (GEngine && GEngine->GameViewport) {
		GEngine->GameViewport->GetViewportSize(CachedViewportSize);
	}


	if (!ensureMsgf(HUDWidgetClass && HUDWidgetClass->IsChildOf(UUserWidget::StaticClass()), TEXT("HUDWidgetClass invalid: %s"), *GetNameSafe(HUDWidgetClass))) {
		return;
	}
	HUDWidget = CreateWidget<UUserWidget>(World, HUDWidgetClass);
	if (!HUDWidget) return;
	HUDWidget->AddToViewport();

	CurrencyText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("CurrencyText")));
	ClickValueText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("ClickValueText")));
	UpgradeCostText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("UpgradeCostText")));
	PassiveIncomeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("PassiveIncomeText")));
	UpgradeSuccessText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("UpgradeSuccessText")));
	UpgradeButton = Cast<UButton>(HUDWidget->GetWidgetFromName(TEXT("UpgradeButton")));
	SaveButton = Cast<UButton>(HUDWidget->GetWidgetFromName(TEXT("SaveButton")));
	LoadButton = Cast<UButton>(HUDWidget->GetWidgetFromName(TEXT("LoadButton")));

	if (UpgradeSuccessText)	UpgradeSuccessText->SetVisibility(ESlateVisibility::Collapsed);

	if (auto* PC = Cast<AMyPlayerController>(PlayerController.Get())) {
		if (UpgradeButton)
			UpgradeButton->OnClicked.AddDynamic(PC, &AMyPlayerController::OnUpgradeClicked);

		if (SaveButton)
			SaveButton->OnClicked.AddDynamic(PC, &AMyPlayerController::OnSaveClicked);

		if (LoadButton)
			LoadButton->OnClicked.AddDynamic(PC, &AMyPlayerController::OnLoadClicked);
	}

	//CreateIdleRewardTextWidgetPool(World, 10);
	//CreateFloatingTextWidgetPool(World, 10);

	if (EconomySubsystemRef) {
		OnEconomyChanged(EconomySubsystemRef->GetSnapshot());
		EconomySubsystemRef->TriggerOfflineReward();
	}
}

//void UClickerUISubsystem::ShowFloatingText(const FString& Message, const FVector& WorldLocation) {
//	if (!FloatingTextWidgetClass || !PlayerController.IsValid())	return;
//	//UE_LOG(LogTemp, Warning, TEXT("ShowFloatingText"));
//	FVector2D ScreenPosition;
//	UGameplayStatics::ProjectWorldToScreen(PlayerController.Get(), WorldLocation, ScreenPosition);
//
//	if (auto* W = GetFloatingTextWidgetFromPool()) {
//		W->PlayFade();
//		if (auto* TB = Cast<UTextBlock>(W->GetWidgetFromName(TEXT("FloatingText")))) {
//			TB->SetText(FText::FromString(Message));
//		}
//		if (auto* Slot = Cast<UCanvasPanelSlot>(W->Slot)) {
//			Slot->SetPosition(ScreenPosition);
//		}
//		//UE_LOG(LogTemp, Warning, TEXT("GetFloatingTextWidgetFromPool"));
//	}
//	
//}
//
//void UClickerUISubsystem::ShowIdleReward(float Amount) {
//	ShowReward(Amount, false);
//}

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

void UClickerUISubsystem::OnEconomyChanged(const FEconomySnapshot& Snapshot) {
	UpdateScore(Snapshot);
}

void UClickerUISubsystem::OnPassiveIncome(double AmountPerSec) {
	HandlePassiveIncome(AmountPerSec);
}

void UClickerUISubsystem::OnOfflineReward(double Amount) {
	HandleOfflineReward(Amount);
}

// private field
void UClickerUISubsystem::UpdateScore(const FEconomySnapshot& Snapshot) {
	if (CurrencyText)
		CurrencyText->SetText(FText::FromString(FString::Printf(TEXT("Currency: %.2f"), Snapshot.Currency)));

	if (ClickValueText)
		ClickValueText->SetText(FText::FromString(FString::Printf(TEXT("Click Value: %.2f"), Snapshot.CurrencyPerClick)));

	if (UpgradeCostText)
		UpgradeCostText->SetText(FText::FromString(FString::Printf(TEXT("Upgrade Cost: %.2f"), FMath::Pow(Snapshot.UpgradeGrowth, Snapshot.UpgradeLevel + 1) * Snapshot.UpgradeCostBase)));

	if (PassiveIncomeText)
		PassiveIncomeText->SetText(FText::FromString(FString::Printf(TEXT("Passive Income: %.2f / sec"), Snapshot.CurrencyPerSecond)));

}

void UClickerUISubsystem::HandlePassiveIncome(double Amount) {
	ShowReward(Amount, false);
}

void UClickerUISubsystem::HandleOfflineReward(double Amount) {
	ShowReward(Amount, true);
}

void UClickerUISubsystem::ShowReward(double Amount, bool bIsOffline) {
	if (!RewardToastClass || !PlayerController.IsValid())	return;

	const FVector2D ScreenPos(640.0f, 120.0f);

	if (UToastWidgetBase* Widget = GetWidgetFromPool(RewardPool, RewardToastClass)) {
		FString Text = bIsOffline
			? FString::Printf(TEXT("+%.0f (Offline)"), Amount)
			: FString::Printf(TEXT("+%.0f"), Amount);

		Widget->SetupToast(FText::FromString(Text), ScreenPos);
		Widget->PlayToast();
	}
	//if (auto* Widget = GetRewardWidgetFromPool()) {
	//	if (bIsOffline) {
	//		const FVector2D CenterTop(CachedViewportSize.X * 0.5f, CachedViewportSize.Y * 0.15f);
	//		Widget->SetPositionInViewport(CenterTop, false);
	//	}
	//	else {
	//		const FVector2D Center = CachedViewportSize / 2.0f;
	//		FVector2D RandomOffset(FMath::RandRange(-200.0f, 200.0f), FMath::RandRange(-100.0f, 100.0f));
	//		Widget->SetPositionInViewport(Center + RandomOffset, false);
	//	}

	//	//Widget->SetRewardAmount(Amount, bIsOffline);
	//	//Widget->SetVisibility(ESlateVisibility::Visible);
	//	//Widget->PlayFade(bIsOffline ? 0.5f : 1, bIsOffline ? OfflineRewardSound : ClickRewardSound);
	//}
}

UToastWidgetBase* UClickerUISubsystem::GetWidgetFromPool(TArray<UToastWidgetBase*>& Pool, TSubclassOf<UToastWidgetBase> ToastClass) {
	for (auto* W : Pool) {
		if (W && W->IsAvailable()) {
			return W;
		}
	}

	if (ToastClass && PlayerController.IsValid()) {
		UToastWidgetBase* NewWidget = CreateWidget<UToastWidgetBase>(PlayerController.Get(), ToastClass);
		if (NewWidget) {
			NewWidget->AddToViewport(11);
			NewWidget->SetVisibility(ESlateVisibility::Collapsed);
			Pool.Add(NewWidget);
			return NewWidget;
		}
	}

}

//UClickFloatingTextWidget* UClickerUISubsystem::GetFloatingTextWidgetFromPool() {
//	for (auto* W : FloatingTextPool) {
//		if (W && W->IsAvailable()) {
//			return W;
//		}
//	}
//
//	if (FloatingTextWidgetClass && PlayerController.IsValid()) {
//		ensureMsgf(FloatingTextWidgetClass->IsChildOf(UClickFloatingTextWidget::StaticClass()),
//			TEXT("FloatingTextWidgetClass invalid: %s"), *GetNameSafe(FloatingTextWidgetClass));
//
//		if (auto* NewWidget = CreateWidget<UClickFloatingTextWidget>(PlayerController.Get(), FloatingTextWidgetClass)) {
//			NewWidget->AddToViewport(11);
//			NewWidget->SetVisibility(ESlateVisibility::Collapsed);
//			FloatingTextPool.Add(NewWidget);
//			UE_LOG(LogTemp, Warning, TEXT("Created new FloatingTextWidget, pool size: %d"), FloatingTextPool.Num());
//			return NewWidget;
//		}
//	}
//
//	return nullptr;
//}

//UIdleRewardTextWidget* UClickerUISubsystem::GetRewardWidgetFromPool() {
//	for (auto* Widget : RewardTextPool) {
//		if (Widget && !Widget->IsAnimationPlaying()) {
//			return Widget;
//		}
//	}
//
//	// If there is no available widget in the pool, create a new one
//	if (IdleRewardTextWidgetClass && PlayerController.IsValid()) {
//		if (auto* W = CreateWidget<UIdleRewardTextWidget>(PlayerController.Get(), IdleRewardTextWidgetClass)) {
//			W->AddToViewport(10);
//			W->SetVisibility(ESlateVisibility::Collapsed);
//			RewardTextPool.Add(W);
//			return W;
//		}
//	}
//	return nullptr;
//}

//void UClickerUISubsystem::CreateIdleRewardTextWidgetPool(UWorld* World, const int32 PoolSize) {
//	for (int32 i = 0; i < PoolSize; i++) {
//		if (!IdleRewardTextWidgetClass) break;
//		if (!ensureMsgf(IdleRewardTextWidgetClass && IdleRewardTextWidgetClass->IsChildOf(UIdleRewardTextWidget::StaticClass()), TEXT("IdleRewardTextWidgetClass invalid: %s"), *GetNameSafe(IdleRewardTextWidgetClass))) {
//			return;
//		}
//
//		if (auto* W = CreateWidget<UIdleRewardTextWidget>(World, IdleRewardTextWidgetClass)) {
//			W->AddToViewport(10);
//			W->SetVisibility(ESlateVisibility::Collapsed);
//			RewardTextPool.Add(W);
//		}
//	}
//
//}

//void UClickerUISubsystem::CreateFloatingTextWidgetPool(UWorld* World, const int32 PoolSize) {		
//	for (int32 i = 0; i < PoolSize; i++) {
//		if (!FloatingTextWidgetClass) break;
//		ensureMsgf(FloatingTextWidgetClass->IsChildOf(UClickFloatingTextWidget::StaticClass()), TEXT("FloatingTextWidgetClass invalid: %s"), *GetNameSafe(FloatingTextWidgetClass));
//		if (auto* W = CreateWidget<UClickFloatingTextWidget>(World, FloatingTextWidgetClass)) {
//			W->AddToViewport(11);
//			W->SetVisibility(ESlateVisibility::Collapsed);
//			FloatingTextPool.Add(W);
//		}
//	}
//}