// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Parts/ClickerHUDPrimaryActionWidget.h"

#include "Components/Button.h"
#include "Systems/UI/ClickerUISubsystem.h"
#include "Gameplay/Player/ClickerPlayerController.h"
#include "Systems/UI/Widgets/ActionButton/ActionButtonWidgetBase.h"

void UClickerHUDPrimaryActionWidget::InitializePart_Implementation(UClickerUISubsystem* InUI, AClickerPlayerController* InPC){
	Super::InitializePart_Implementation(InUI, InPC);
	if (Btn_Upgrade && UpgradeActionTag.IsValid()) {
		Btn_Upgrade->InitializeButton(InPC, InUI, UpgradeActionTag);
	}
	if (Btn_Boost && BoostActionTag.IsValid()) {
		Btn_Boost->InitializeButton(InPC, InUI, BoostActionTag);
	}
	if (Btn_Test && TestActionTag.IsValid()) {
		Btn_Test->InitializeButton(InPC, InUI, TestActionTag);
	}
}