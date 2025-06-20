// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickerUIManager.h"
#include "ClickFloatingTextWidget.h"
#include "MyPlayerController.h"

#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "TimerManager.h"

void UClickerUIManager::Initialize(AMyPlayerController* InController, TSubclassOf<UClickFloatingTextWidget> InFloatingTextWidgetClass, TSubclassOf<UUserWidget> InHUDWidgetClass) {
	UE_LOG(LogTemp, Warning, TEXT("UIManager: Initialize called"));

	PlayerController = InController;
	FloatingTextWidgetClass = InController->FloatingTextWidgetClass;
	HUDWidgetClass = InHUDWidgetClass;
	

}

void UClickerUIManager::ShowFloatingText(const FString& Message, const FVector& WorldLocation) {
	UE_LOG(LogTemp, Warning, TEXT("UIManager: ShowFloatingText called"));

	if (!FloatingTextWidgetClass || !PlayerController)	return;

	FVector2D ScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(PlayerController, WorldLocation, ScreenPosition);
	UClickFloatingTextWidget* Widget = GetFloatingTextWidgetFromPool();
	if (!Widget) {
		UE_LOG(LogTemp, Error, TEXT("Failed to get/create a floating text widget!"));
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