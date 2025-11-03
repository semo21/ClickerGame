// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Toast/ClickFloatingTextWidget.h"
#include "Animation/UMGSequencePlayer.h"
#include "Animation/WidgetAnimation.h"

void UClickFloatingTextWidget::PlayFade() {
	bInUse = true;
	SetVisibility(ESlateVisibility::Visible);
	if(FloatUpFade)	PlayAnimation(FloatUpFade);
}

void UClickFloatingTextWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (FloatUpFade) {
		UnbindAllFromAnimationFinished(FloatUpFade);

		FWidgetAnimationDynamicEvent Finished;
		Finished.BindDynamic(this, &UClickFloatingTextWidget::OnFloatAnimationFinished);
		BindToAnimationFinished(FloatUpFade, Finished);
	}	
}

void UClickFloatingTextWidget::OnFloatAnimationFinished(UWidgetAnimation* Player) {
	SetVisibility(ESlateVisibility::Collapsed);
	bInUse = false;
}

