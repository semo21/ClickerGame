// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IdleRewardTextWidget.generated.h"

/**
 *
 */
UCLASS()
class CLICKERGAME_API UIdleRewardTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetRewardAmount(float Amount, bool bIsOfflineReward);

	UFUNCTION(BlueprintCallable)
	void PlayFade(float PlaybackSpeed = 1.0f);

	bool IsAnimationPlaying() const { return bIsPlaying; }

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmountText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeInOut;

	UPROPERTY()
	bool bIsPlaying = false;
};
