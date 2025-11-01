// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Toast/ClickFloatingTextWidget.h"

void UClickFloatingTextWidget::PlayFade() {
	bIsAvailable = false;
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(FloatUpFade);

	BindToAnimationFinished(FloatUpFade, FWidgetAnimationDynamicEvent::CreateUObject(this, &UClickFloatingTextWidget::OnFloatAnimationFinished);
}

void UClickFloatingTextWidget::OnFloatAnimationFinished() {
	bIsAvailable = true;
	SetVisibility(ESlateVisibility::Collapsed);
}