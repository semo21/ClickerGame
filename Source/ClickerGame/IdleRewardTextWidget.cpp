// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TextBlock.h"
#include "IdleRewardTextWidget.h"
#include "Animation/WidgetAnimation.h"

void UIdleRewardTextWidget::SetRewardAmount(float Amount, bool bIsOfflineReward) {
	if (AmountText && !bIsOfflineReward) {
		AmountText->SetText(FText::FromString(FString::Printf(TEXT("+%.0f Gold"), Amount)));
		UE_LOG(LogTemp, Warning, TEXT("IdleRewardTextWidget IdleReward"));
	}
	else if (AmountText && bIsOfflineReward) {
		AmountText->SetText(FText::FromString(FString::Printf(TEXT("Offline Reward: +%.0f Gold"), Amount)));
		
		UE_LOG(LogTemp, Warning, TEXT("IdleRewardTextWidget OfflineReward"));
	}
}

void UIdleRewardTextWidget::PlayFade(float PlaybackSpeed) {
	if (FadeInOut) {
		PlayAnimation(FadeInOut, 0, 1, EUMGSequencePlayMode::Forward, PlaybackSpeed);

		FTimerHandle RemoveTimer;
		GetWorld()->GetTimerManager().SetTimer(
			RemoveTimer, 
			[this]() {RemoveFromParent();}, 
			FadeInOut->GetEndTime()/PlaybackSpeed,
			false
		);
		//UE_LOG(LogTemp, Warning, TEXT("IdleRewardTextWidget PlayFade"));
	}
}