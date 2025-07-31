// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickerUIManager.h"
#include "ClickFloatingTextWidget.h"
#include "MyPlayerController.h"
#include "ClickerComponent.h"
#include "IdleRewardTextWidget.h"

#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "TimerManager.h"


void UClickerUIManager::Initialize(AMyPlayerController* InController) {
	//UE_LOG(LogTemp, Warning, TEXT("UIManager: Initialize called"));

	PlayerController = InController;
	FloatingTextWidgetClass = InController->FloatingTextWidgetClass;
	HUDWidgetClass = InController->HUDWidgetClass;
	ClickEffectAsset = InController->ClickEffectAsset;
	IdleRewardTextWidgetClass = InController->IdleRewardTextWidgetClass;
	ClickerComponent = InController->ClickerComponent;
	ClickerComponent->SetUIManager(this);
	GEngine->GameViewport->GetViewportSize(CachedViewportSize);

	int32 RewardTextPoolSize = 10;
	for (int32 i = 0; i < RewardTextPoolSize; i++) {
		UIdleRewardTextWidget* NewWidget = CreateWidget<UIdleRewardTextWidget>(GetWorld(), IdleRewardTextWidgetClass);

		if (NewWidget) {
			NewWidget->AddToViewport(10);
			NewWidget->SetVisibility(ESlateVisibility::Collapsed);
			RewardTextPool.Add(NewWidget);
		}
	}
	
	ShowHUD();
	UpdateScore();
}

void InitSoundSource() {
	
}

void UClickerUIManager::ShowFloatingText(const FString& Message, const FVector& WorldLocation) {
	//UE_LOG(LogTemp, Warning, TEXT("UIManager: ShowFloatingText called"));

	if (!FloatingTextWidgetClass || !PlayerController)	return;

	FVector2D ScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(PlayerController, WorldLocation, ScreenPosition);
	UClickFloatingTextWidget* Widget = GetFloatingTextWidgetFromPool();
	if (!Widget) {
		//UE_LOG(LogTemp, Error, TEXT("Failed to get/create a floating text widget!"));
	}

	if (!Widget) return;

	Widget->AddToViewport();

	if (UTextBlock* TextBlock = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("FloatingText")))) {
		TextBlock->SetText(FText::FromString(Message));
	}

	if (UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(Widget->Slot)) {
		Slot->SetPosition(ScreenPosition);
	}

	if (Widget->FloatUpFade) {
		Widget->PlayAnimation(Widget->FloatUpFade);
	}

	PlayerController->GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([Widget]() {
		Widget->RemoveFromParent();
		}), 1.0f, false);
}

UClickFloatingTextWidget* UClickerUIManager::GetFloatingTextWidgetFromPool() {
	for (UClickFloatingTextWidget* Widget : FloatingTextPool) {
		if (!Widget->IsInViewport()) {
			return Widget;
		}
	}

	if (FloatingTextWidgetClass && PlayerController) {
		UClickFloatingTextWidget* NewWidget = CreateWidget<UClickFloatingTextWidget>(PlayerController, FloatingTextWidgetClass);
		FloatingTextPool.Add(NewWidget);
		return NewWidget;
	}

	return nullptr;
}

UIdleRewardTextWidget* UClickerUIManager::GetRewardWidgetFromPool() {
	int i = 0;
	for (UIdleRewardTextWidget* Widget : RewardTextPool) {
		i++;
		if (!Widget->IsAnimationPlaying()) {
			UE_LOG(LogTemp, Warning, TEXT("IdleRewardTextWidget from Pool: %d"), i)
			return Widget;
		}
	}
	return nullptr;
}

void UClickerUIManager::ShowIdleReward(float Amount) {
	if (!IdleRewardTextWidgetClass)
		return;

	UIdleRewardTextWidget* RewardWidget = GetRewardWidgetFromPool();
	if (!RewardWidget) {
		UE_LOG(LogTemp, Warning, TEXT("No available reward widget in pool."));
		return;
	}
	//UIdleRewardTextWidget* RewardWidget = CreateWidget<UIdleRewardTextWidget>(GetWorld(), IdleRewardTextWidgetClass);
	FVector2D RandomOffset(FMath::RandRange(-200.0f, 200.0f), FMath::RandRange(-100.0f, 100.0f));
	FVector2D CenterScreen = CachedViewportSize / 2.0f;

	RewardWidget->SetPositionInViewport(CenterScreen + RandomOffset, false);
	RewardWidget->SetRewardAmount(Amount, false);
	RewardWidget->AddToViewport(10);
	RewardWidget->PlayFade(1, IdleRewardSound);
	
}

void UClickerUIManager::ShowOfflineReward(float OfflineReward) {
	if (!IdleRewardTextWidgetClass)
		return;

	UIdleRewardTextWidget* OfflineWidget = CreateWidget<UIdleRewardTextWidget>(GetWorld(), IdleRewardTextWidgetClass);
	
	if (OfflineWidget) {
		OfflineWidget->SetPositionInViewport(FVector2D(CachedViewportSize.X * 0.5f, CachedViewportSize.Y *0.15f), false);
		OfflineWidget->SetRewardAmount(OfflineReward, true);
		OfflineWidget->AddToViewport(10);
		OfflineWidget->PlayFade(0.5f, OfflineRewardSound);
	}
}

void UClickerUIManager::ShowClickEffect(const FVector& Location) {
	if (!PlayerController || !ClickEffectAsset) {
		return;
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(PlayerController->GetWorld(), ClickEffectAsset, Location, FRotator::ZeroRotator, FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);
}

void UClickerUIManager::ShowHUD() {
	//UE_LOG(LogTemp, Warning, TEXT("UIManager: ShowHUD called"));
	if (!HUDWidgetClass || !PlayerController) return;

	HUDWidget = CreateWidget<UUserWidget>(PlayerController, HUDWidgetClass);
	if (HUDWidget) {
		HUDWidget->AddToViewport();

		// Bind Textblock by name
		UWidget* CurrencyW = HUDWidget->GetWidgetFromName(TEXT("CurrencyText"));
		CurrencyText = Cast<UTextBlock>(CurrencyW);

		UWidget* ClickValueW = HUDWidget->GetWidgetFromName(TEXT("ClickValueText"));
		ClickValueText = Cast<UTextBlock>(ClickValueW);

		UWidget* UpgradeCostW = HUDWidget->GetWidgetFromName(TEXT("UpgradeCostText"));
		UpgradeCostText = Cast<UTextBlock>(UpgradeCostW);

		UWidget* PassiveIncomeW = HUDWidget->GetWidgetFromName(TEXT("PassiveIncomeText"));
		PassiveIncomeText = Cast<UTextBlock>(PassiveIncomeW);

		UWidget* UpgradeSuccessW = HUDWidget->GetWidgetFromName(TEXT("UpgradeSuccessText"));
		UpgradeSuccessText = Cast<UTextBlock>(UpgradeSuccessW);

		UWidget* UpgradeButtonW = HUDWidget->GetWidgetFromName(TEXT("UpgradeButton"));
		UpgradeButton = Cast<UButton>(UpgradeButtonW);

		UWidget* SaveButtonW = HUDWidget->GetWidgetFromName(TEXT("SaveButton"));
		SaveButton = Cast<UButton>(SaveButtonW);

		UWidget* LoadButtonW = HUDWidget->GetWidgetFromName(TEXT("LoadButton"));
		LoadButton = Cast<UButton>(LoadButtonW);

		if (UpgradeButton)
			UpgradeButton->OnClicked.AddDynamic(PlayerController, &AMyPlayerController::OnUpgradeClicked);

		if (SaveButton)
			SaveButton->OnClicked.AddDynamic(PlayerController, &AMyPlayerController::OnSaveClicked);

		if (LoadButton)
			LoadButton->OnClicked.AddDynamic(PlayerController, &AMyPlayerController::OnLoadClicked);

		if (UpgradeSuccessText) {
			UpgradeSuccessText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UClickerUIManager::UpdateScore() {
	if (CurrencyText)
		CurrencyText->SetText(FText::FromString(FString::Printf(TEXT("Currency: %.2f"), ClickerComponent->GetCurrency())));

	if (ClickValueText)
		ClickValueText->SetText(FText::FromString(FString::Printf(TEXT("Click Value: %.2f"), ClickerComponent->GetCurrencyPerClick())));

	if (UpgradeCostText)
		UpgradeCostText->SetText(FText::FromString(FString::Printf(TEXT("Upgrade Cost: %.2f"), ClickerComponent->GetUpgradeCost())));

	if (PassiveIncomeText)
		PassiveIncomeText->SetText(FText::FromString(FString::Printf(TEXT("Passive Income: %.2f / sec"), ClickerComponent->GetCurrencyPerSecond())));

}

UUserWidget* UClickerUIManager::GetHUDWidget() const {
	//UE_LOG(LogTemp, Warning, TEXT("UIManager: GetHUDWidget called"));
	return HUDWidget;
}

void UClickerUIManager::ShowUpgradeSuccessText() {
	if (UpgradeSuccessText) {
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

void UClickerUIManager::HideUpgradeSuccessText() {
	if (UpgradeSuccessText) {
		UpgradeSuccessText->SetVisibility(ESlateVisibility::Collapsed);
	}
}


