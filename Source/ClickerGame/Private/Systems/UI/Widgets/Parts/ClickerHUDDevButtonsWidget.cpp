// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Parts/ClickerHUDDevButtonsWidget.h"

#include "Systems/UI/ClickerUISubsystem.h"
#include "Gameplay/Player/MyPlayerController.h"
#include "Systems/UI/Widgets/ActionButton/ActionButtonWidgetBase.h"

void UClickerHUDDevButtonsWidget::InitializePart_Implementation(UClickerUISubsystem* InUI, AMyPlayerControllerBase* InPC) {
	Super::InitializePart_Implementation(InUI, InPC);
	UE_LOG(LogTemp, Warning, TEXT("UClickerHUDDevButtonsWidget::InitializePart_Implementation - Initializing dev buttons"));
	if (Btn_Save && SaveActionTag.IsValid()) {
		Btn_Save->InitializeButton(InPC, InUI, SaveActionTag);
		UE_LOG(LogTemp, Warning, TEXT("UClickerHUDDevButtonsWidget::InitializePart_Implementation - Initialized Save button with tag: %s"), *SaveActionTag.ToString());
	}
	if (Btn_Load && LoadActionTag.IsValid()) {
		Btn_Load->InitializeButton(InPC, InUI, LoadActionTag);
		UE_LOG(LogTemp, Warning, TEXT("UClickerHUDDevButtonsWidget::InitializePart_Implementation - Initialized Load button with tag %s"), *LoadActionTag.ToString());
	}
	
}