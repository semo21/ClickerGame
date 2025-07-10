// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TextBlock.h"
#include "IdleRewardTextWidget.h"

void UIdleRewardTextWidget::SetRewardAmount(float Amount) {
	if (AmountText) {
		AmountText->SetText(FText::FromString(FString::Printf(TEXT("+%.0f Gold"), Amount)));
	}
}

void UIdleRewardTextWidget::PlayFade() {
	if (FadeAnim) {
		PlayAnimation(FadeAnim);

		FTimerHandle RemoveTimer;
		GetWorld()->GetTimerManager().SetTimer(
			RemoveTimer, 
			[this]() {RemoveFromParent();}, 
			FadeAnim->GetEndTime(), 
			false
		);
	}
}