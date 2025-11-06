// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Systems/UI/Widgets/ToastWidgetBase.h"

#include "ClickFloatingTextWidget.generated.h"

class UTextBlock;
/**
 *
 */
UCLASS()
class CLICKERGAME_API UClickFloatingTextWidget : public UToastWidgetBase
{
	GENERATED_BODY()
	

public:
    virtual void SetupToast(const FText& InText, const FVector2D& ScreenPos) override;
    //UPROPERTY(meta = (BindWidgetAnim), Transient)   UWidgetAnimation* FloatUpFade = nullptr;

    //void PlayFade();
    //bool IsAvailable() const { return !bInUse; }

protected:
    UPROPERTY(meta = (BindWidget))  class UTextBlock* FloatingText = nullptr;
private:
    //bool bInUse = false;

    //void OnFloatPlayerFinished(UUMGSequencePlayer& Player);
};
