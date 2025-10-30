// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ClickFloatingTextWidget.generated.h"

/**
 *
 */
UCLASS()
class CLICKERGAME_API UClickFloatingTextWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* FloatingText;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* FloatUpFade;

    void PlayFade();
    bool IsAvailable() const { return bIsAvailable; }

private:
    bool bIsAvailable = false;
};
