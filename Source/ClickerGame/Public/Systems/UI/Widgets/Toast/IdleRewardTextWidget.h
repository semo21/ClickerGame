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

protected:
	UPROPERTY(meta = (BindWidget))	class UTextBlock* RewardText = nullptr;
};
