// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/UI/Widgets/ToastWidgetBase.h"
#include "Animation/UMGSequencePlayer.h"

void UToastWidgetBase::PlayToast(float PlayRate) {
	bInUse = true;
	SetVisibility(ESlateVisibility::Visible);

	if (ToastAnim) {
		if (UUMGSequencePlayer* Player = PlayAnimation(ToastAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, PlayRate)) {
			Player->OnSequenceFinishedPlaying().AddUObject(
				this, &UToastWidgetBase::OnToastFinished
			);
		}
	}
	else {
		OnToastFinished(*(UUMGSequencePlayer*)nullptr);
	}
}

void UToastWidgetBase::OnToastFinished(UUMGSequencePlayer& Player) {
	SetVisibility(ESlateVisibility::Collapsed);
	bInUse = false;	
}
