// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Toast/IdleRewardTextWidget.h"

#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"

void UIdleRewardTextWidget::SetupToast(const FText& InText, const FVector2D& ScreenPos) {
	if (RewardText) {
		RewardText->SetText(InText);
	}
	if (auto* CanvasSlot = Cast<UCanvasPanelSlot>(Slot)) {
		CanvasSlot->SetPosition(ScreenPos);
	}
}
