// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/GlobalUISubsystem.h"
#include "Blueprint/UserWidget.h"

void UGlobalUISubsystem::ClearRootUI() {
	if (CurrentRootWidget) {
		CurrentRootWidget->RemoveFromParent();
		CurrentRootWidget = nullptr;
	}
}

void UGlobalUISubsystem::ShowRootUI(TSubclassOf<UUserWidget> RootWidgetClass) {
	ClearRootUI();

	if (!RootWidgetClass) {
		UE_LOG(LogTemp, Warning, TEXT("RootWidgetClass is null"));
		return;
	}

	UWorld* World = GetWorld();
	if (!World) return;

	CurrentRootWidget = CreateWidget<UUserWidget>(World, RootWidgetClass);

	if (CurrentRootWidget) {
		CurrentRootWidget->AddToViewport();
	}
}