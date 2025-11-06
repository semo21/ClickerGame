// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Toast/ClickFloatingTextWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"


void UClickFloatingTextWidget::SetupToast(const FText& InText, const FVector2D& ScreenPos) {
	if (FloatingText) {
		FloatingText->SetText(InText);
	}
	if (auto* CanvasSlot = Cast<UCanvasPanelSlot>(Slot)) {
		CanvasSlot->SetPosition(ScreenPos);
	}
}
//void UClickFloatingTextWidget::PlayFade() {
//	bInUse = true;
//	SetVisibility(ESlateVisibility::Visible);
//	if (FloatUpFade) {
//		if (UUMGSequencePlayer* Player = PlayAnimation(FloatUpFade)) {
//			Player->OnSequenceFinishedPlaying().AddUObject(this, &UClickFloatingTextWidget::OnFloatPlayerFinished);
//		}			
//	}
//	else {
//		OnFloatPlayerFinished(*(UUMGSequencePlayer*)nullptr);
//	}
//}
//
//void UClickFloatingTextWidget::OnFloatPlayerFinished(UUMGSequencePlayer& Player) {
//	SetVisibility(ESlateVisibility::Collapsed);
//	bInUse = false;
//}