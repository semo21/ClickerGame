// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ClickFloatingTextWidget.generated.h"

/**
 *
 */
class UUMGSequencePlayer;
UCLASS()
class CLICKERGAME_API UClickFloatingTextWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
    UPROPERTY(meta = (BindWidget))  class UTextBlock* FloatingText = nullptr;
    UPROPERTY(meta = (BindWidgetAnim), Transient)   UWidgetAnimation* FloatUpFade = nullptr;

    void PlayFade();
    bool IsAvailable() const { return !bInUse; }

private:
    bool bInUse = false;

    void OnFloatPlayerFinished(UUMGSequencePlayer& Player);
};
