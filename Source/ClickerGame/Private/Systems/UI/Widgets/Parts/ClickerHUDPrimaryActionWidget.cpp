// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Parts/ClickerHUDPrimaryActionWidget.h"

#include "Components/Button.h"
#include "Systems/UI/ClickerUISubsystem.h"
#include "Gameplay/Player/MyPlayerControllerBase.h"
#include "Systems/UI/Widgets/ActionButton/ActionButtonWidgetBase.h"

void UClickerHUDPrimaryActionWidget::InitializePart_Implementation(UClickerUISubsystem* InUI, AMyPlayerControllerBase* InPC){
	Super::InitializePart_Implementation(InUI, InPC);
	UE_LOG(LogTemp, Warning, TEXT("UClickerHUDPrimaryActionWidget::InitializePart_Implementation - Initializing primary action buttons"));
	UE_LOG(LogTemp, Warning, TEXT("UpgradeActionTag: %s, BoostActionTag: %s, TestActionTag: %s"), *UpgradeActionTag.ToString(), *BoostActionTag.ToString(), *TestActionTag.ToString());
	if (Btn_Upgrade && UpgradeActionTag.IsValid()) {
		Btn_Upgrade->InitializeButton(InPC, InUI, UpgradeActionTag);
		UE_LOG(LogTemp, Warning, TEXT("UClickerHUDPrimaryActionWidget::InitializePart_Implementation - Initialized Upgrade button with tag: %s"), *UpgradeActionTag.ToString());
	}
	if (Btn_Boost && BoostActionTag.IsValid()) {
		Btn_Boost->InitializeButton(InPC, InUI, BoostActionTag);
		UE_LOG(LogTemp, Warning, TEXT("UClickerHUDPrimaryActionWidget::InitializePart_Implementation - Initialized Boost button with tag: %s"), *BoostActionTag.ToString());
	}
	if (Btn_Test && TestActionTag.IsValid()) {
		Btn_Test->InitializeButton(InPC, InUI, TestActionTag);
		UE_LOG(LogTemp, Warning, TEXT("UClickerHUDPrimaryActionWidget::InitializePart_Implementation - Initialized Test button with tag: %s"), *TestActionTag.ToString());
	}

}