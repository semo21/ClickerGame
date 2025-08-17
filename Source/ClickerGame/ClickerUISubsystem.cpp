// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickerUISubsystem.h"

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

#include "ClickerEconomySubsystem.h"
#include "MyPlayerController.h"
#include "ClickFloatingTextWidget.h"
#include "IdleRewardTextWidget.h"

void UClickerUISubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	if (auto* EconomySubsystem = Collection.InitializeDependency<UClickerEconomySubsystem>()) {
		EconomySubsystemRef = EconomySubsystem;
		EconomySubsystem->OnEconomyChanged.AddDynamic(this, &UClickerUISubsystem::OnEconomyChanged);
	}
}

void UClickerUISubsystem::Deinitialize() {
	if (auto* Eco = EconomySubsystemRef.Get()) {
		Eco->OnEconomyChanged.RemoveDynamic(this, &UClickerUISubsystem::OnEconomyChanged);
	}

	if (auto* PC = PlayerController.Get()) {
		PC->GetWorldTimerManager().ClearTimer(UpgradeSuccessTimerHandle);
	}

	HUDWidget = nullptr;
	CurrencyText = ClickValueText = UpgradeCostText = PassiveIncomeText = UpgradeSuccessText = nullptr;
	UpgradeButton = SaveButton = LoadButton = nullptr;
	FloatingTextPool.Empty();
	RewardTextPool.Empty();
	PlayerController.Reset();
	EconomySubsystemRef.Reset();

	Super::Deinitialize();
}

void UClickerUISubsystem::ShowHUD(UWorld* World) {
	if (!World || HUDWidget || !HUDWidgetClass) return;

	if (!PlayerController.IsValid())
		PlayerController = World->GetFirstPlayerController();

	if (GEngine && GEngine->GameViewport)
		GEngine->GameViewport->GetViewportSize(CachedViewportSize);

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

	const int32 PoolSize = 10;
	for (int32 i = 0; i < PoolSize; i++) {
		if (!IdleRewardTextWidgetClass) break;
		if (auto* W = CreateWidget<UIdleRewardTextWidget>(World, IdleRewardTextWidgetClass)) {
			W->AddToViewport(10);
			W->SetVisibility(ESlateVisibility::Collapsed);
			RewardTextPool.Add(W);
		}
	}

	if (auto* Eco = EconomySubsystemRef.Get()) {
		OnEconomyChanged(Eco->MakeSnapshot());
	}
}

void UClickerUISubsystem::OnEconomyChanged(const FEconomySnapshot& Snapshot) {
	UpdateScore(Snapshot);
}

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

void UClickerUISubsystem::ShowFloatingText(const FString& Message, const FVector& WorldLocation) {
	if (!FloatingTextWidgetClass || !PlayerController.IsValid())	return;

	FVector2D ScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(PlayerController.Get(), WorldLocation, ScreenPosition);

	if (auto* FloatingWidget = GetFloatingTextWidgetFromPool()) {
		FloatingWidget->AddToViewport();
		if (auto* TextBlock = Cast<UTextBlock>(FloatingWidget->GetWidgetFromName(TEXT("FloatingText"))))
			TextBlock->SetText(FText::FromString(Message));

		if (auto* Slot = Cast<UCanvasPanelSlot>(FloatingWidget->Slot))
			Slot->SetPosition(ScreenPosition);

		if (FloatingWidget->FloatUpFade)
			FloatingWidget->PlayAnimation(FloatingWidget->FloatUpFade);

		if (auto* Controller = PlayerController.Get()) {
			FTimerHandle Temp;
			Controller->GetWorldTimerManager().SetTimer(Temp, FTimerDelegate::CreateLambda(
				[FloatingWidget]() {FloatingWidget->RemoveFromParent(); }),
				1.0f,
				false
			);
		}
	}
}

UClickFloatingTextWidget* UClickerUISubsystem::GetFloatingTextWidgetFromPool() {
	for (auto* Widget : FloatingTextPool) {
		if (Widget && !Widget->IsInViewport()) {
			return Widget;
		}
	}

	if (FloatingTextWidgetClass && PlayerController.IsValid()) {
		auto* NewWidget = CreateWidget<UClickFloatingTextWidget>(PlayerController.Get(), FloatingTextWidgetClass);
		FloatingTextPool.Add(NewWidget);
		return NewWidget;
	}

	return nullptr;
}

UIdleRewardTextWidget* UClickerUISubsystem::GetRewardWidgetFromPool() {

	for (auto* Widget : RewardTextPool) {
		if (Widget && !Widget->IsAnimationPlaying()) {			
				return Widget;
		}
	}
	return nullptr;
}

void UClickerUISubsystem::ShowIdleReward(float Amount) {
	if (auto* Widget = GetRewardWidgetFromPool()) {
		const FVector2D Center = CachedViewportSize / 2.0f;
		FVector2D RandomOffset(FMath::RandRange(-200.0f, 200.0f), FMath::RandRange(-100.0f, 100.0f));

		Widget->SetPositionInViewport(Center + RandomOffset, false);
		Widget->SetRewardAmount(Amount, false);
		Widget->AddToViewport(10);
	}
}

void UClickerUISubsystem::ShowOfflineReward(float OfflineReward) {
	if (!IdleRewardTextWidgetClass || !PlayerController.IsValid())	return;
		
	if (auto* OfflineWidget = CreateWidget<UIdleRewardTextWidget>(PlayerController.Get(), IdleRewardTextWidgetClass)) {
		OfflineWidget->SetPositionInViewport(FVector2D(CachedViewportSize.X * 0.5f, CachedViewportSize.Y * 0.15f), false);
		OfflineWidget->SetRewardAmount(OfflineReward, true);
		OfflineWidget->AddToViewport(10);
	}
}

void UClickerUISubsystem::ShowClickEffect(const FVector& WorldLocation) {
	if (!PlayerController.IsValid() || !ClickEffectAsset) return;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(PlayerController->GetWorld(), ClickEffectAsset, Location, FRotator::ZeroRotator, FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);
}

void UClickerUISubsystem::ShowUpgradeSuccessText() {
	if (UpgradeSuccessText && PlayerController.IsValid()) {
		UpgradeSuccessText->SetVisibility(ESlateVisibility::Visible);

		PlayerController->GetWorldTimerManager().SetTimer(
			UpgradeSuccessTimerHandle,
			this,
			&UClickerUIManager::HideUpgradeSuccessText,
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