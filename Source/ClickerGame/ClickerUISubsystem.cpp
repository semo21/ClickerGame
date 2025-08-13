// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickerUISubsystem.h"

void UClickerUIManager::ShowHUD() {
	//UE_LOG(LogTemp, Warning, TEXT("UIManager: ShowHUD called"));
	if (!HUDWidget || !PlayerController) return;

	if (HUDWidget) {
		//HUDWidget->AddToViewport();

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