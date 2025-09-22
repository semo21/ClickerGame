// Fill out your copyright notice in the Description page of Project Settings.


#include "IdleRewardTextWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"

void UIdleRewardTextWidget::SetRewardAmount(float Amount, bool bIsOfflineReward) {
	if (AmountText && !bIsOfflineReward) {
		AmountText->SetText(FText::FromString(FString::Printf(TEXT("+%.0f Gold"), Amount)));
		//UE_LOG(LogTemp, Warning, TEXT("IdleRewardTextWidget IdleReward"));
	}
	else if (AmountText && bIsOfflineReward) {
		AmountText->SetText(FText::FromString(FString::Printf(TEXT("Offline Reward: +%.0f Gold"), Amount)));

		//UE_LOG(LogTemp, Warning, TEXT("IdleRewardTextWidget OfflineReward"));
	}
}

void UIdleRewardTextWidget::PlayFade(float PlaybackSpeed, USoundBase* Sound) {
	if (FadeInOut && Sound) {
		UGameplayStatics::PlaySound2D(this, Sound);

		bIsPlaying = true;
		SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(FadeInOut, 0, 1, EUMGSequencePlayMode::Forward, PlaybackSpeed);

		FTimerHandle RemoveTimer;
		float Duration = FadeInOut->GetEndTime() / PlaybackSpeed;
		GetWorld()->GetTimerManager().SetTimer(
			RemoveTimer,
			[this]() {
				SetVisibility(ESlateVisibility::Collapsed);
				bIsPlaying = false;
			},
			Duration, false);
		//UE_LOG(LogTemp, Warning, TEXT("IdleRewardTextWidget PlayFade"));
	}
}