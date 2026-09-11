// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Parts/ClickerHUDStatsWidget.h"

#include "Components/TextBlock.h"

void UClickerHUDStatsWidget::InitializePart_Implementation(UClickerUISubsystem* InUI, AMyPlayerControllerBase* InPC) {
	Super::InitializePart_Implementation(InUI, InPC);
	// Implement in Blueprint
}

void UClickerHUDStatsWidget::OnEconomyChangedUI_Implementation(const FEconomySnapshot& Snapshot) {
	//UE_LOG(LogTemp, Warning, TEXT("ClickerHUDStatsWidget::OnEconomyChangedUI_Implementation Currency: %f, CPC: %f, CPS: %f"), Snapshot.Currency, Snapshot.CurrencyPerClick, Snapshot.CurrencyPerSecond);
	Super::OnEconomyChangedUI_Implementation(Snapshot);
	Txt_Value_Currency->SetText(FText::AsNumber(Snapshot.Currency));
	Txt_Value_CPC->SetText(FText::AsNumber(Snapshot.CurrencyPerClick));
	Txt_Value_UpgradeCost->SetText(FText::AsNumber(FMath::Pow(Snapshot.UpgradeGrowth, Snapshot.UpgradeLevel + 1) * Snapshot.UpgradeCostBase));
	//UE_LOG(LogTemp, Warning, TEXT("ClickerHUDStatsWidget::UpgradeCost: %f"), Snapshot.UpgradeCostBase * FMath::Pow(Snapshot.UpgradeGrowth, Snapshot.UpgradeLevel + 1) * Snapshot.UpgradeCostBase);

	Txt_Value_CPS->SetText(FText::AsNumber(Snapshot.CurrencyPerSecond));
}