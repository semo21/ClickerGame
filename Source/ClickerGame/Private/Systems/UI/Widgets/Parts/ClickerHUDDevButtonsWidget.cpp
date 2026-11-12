// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Parts/ClickerHUDDevButtonsWidget.h"

#include "Systems/UI/ClickerUISubsystem.h"
#include "Gameplay/Player/ClickerPlayerController.h"
#include "Systems/UI/Widgets/ActionButton/ActionButtonWidget.h"

void UClickerHUDDevButtonsWidget::InitializePart_Implementation(UClickerUISubsystem* InUI, AClickerPlayerController* InPC) {
	Super::InitializePart_Implementation(InUI, InPC);
	if (Btn_Save && SaveActionTag.IsValid()) {
		Btn_Save->InitializeButton(InPC, InUI, SaveActionTag);
	}
	if (Btn_Load && LoadActionTag.IsValid()) {
		Btn_Load->InitializeButton(InPC, InUI, LoadActionTag);
	}	
}