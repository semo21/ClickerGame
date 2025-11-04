// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/Toast/ClickFloatingTextWidget.h"
#include "Animation/UMGSequencePlayer.h"
#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"

void UClickFloatingTextWidget::PlayFade() {
	bInUse = true;
	SetVisibility(ESlateVisibility::Visible);
	if (FloatUpFade) {
		if (UUMGSequencePlayer* Player = PlayAnimation(FloatUpFade)) {
			Player->OnSequenceFinishedPlaying().AddUObject(this, &UClickFloatingTextWidget::OnFloatPlayerFinished);
		}			
	}
	else {
		OnFloatPlayerFinished(*(UUMGSequencePlayer*)nullptr);
	}
}

void UClickFloatingTextWidget::OnFloatPlayerFinished(UUMGSequencePlayer& Player) {
	SetVisibility(ESlateVisibility::Collapsed);
	bInUse = false;
}




