// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Toast/ClickFloatingTextWidget.h"

void UClickFloatingTextWidget::PlayFade() {
	bIsAvailable = false;
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(FloatUpFade);

	BindToAnimationFinished(FloatUpFade, FWidgetAnimationDynamicEvent::CreateWeakLambda(this, [this](UWidgetAnimation*) {
		SetVisibility(ESlateVisibility::Collapsed);
		bIsAvailable = true;
		}));
}