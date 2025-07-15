// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TextBlock.h"
#include "IdleRewardTextWidget.h"
#include "Animation/WidgetAnimation.h"

void UIdleRewardTextWidget::SetRewardAmount(float Amount) {
	if (AmountText) {
		AmountText->SetText(FText::FromString(FString::Printf(TEXT("+%.0f Gold"), Amount)));
	}
}

void UIdleRewardTextWidget::PlayFade() {
	if (FadeInOut) {
		PlayAnimation(FadeInOut);

		FTimerHandle RemoveTimer;
		GetWorld()->GetTimerManager().SetTimer(
			RemoveTimer, 
			[this]() {RemoveFromParent();}, 
			FadeInOut->GetEndTime(),
			false
		);
	}

	UE_LOG(LogTemp, Warning, TEXT("IdleRewardTextWidget PlayFade"));
}