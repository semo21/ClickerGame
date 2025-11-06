// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Systems/UI/Widgets/ToastWidgetBase.h"

#include "IdleRewardTextWidget.generated.h"

class UTextBlock;
/**
 *
 */
UCLASS()
class CLICKERGAME_API UIdleRewardTextWidget : public UToastWidgetBase
{
	GENERATED_BODY()

public:
	virtual void SetupToast(const FText& InText, const FVector2D& ScreenPos) override;

	//UFUNCTION(BlueprintCallable)
	//void SetRewardAmount(float Amount, bool bIsOfflineReward);

	//UFUNCTION(BlueprintCallable)
	//void PlayFade(float PlaybackSpeed, USoundBase* Sound);

	//bool IsAnimationPlaying() const { return bIsPlaying; }

protected:
	UPROPERTY(meta = (BindWidget))	class UTextBlock* RewardText;

	//UPROPERTY(meta = (BindWidgetAnim), Transient)
	//class UWidgetAnimation* FadeInOut;

	//UPROPERTY()
	//bool bIsPlaying = false;
};
