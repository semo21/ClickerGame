// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ToastWidgetBase.generated.h"

class UUMGSequencePlayer;
/**
 * 
 */
UCLASS(Abstract)
class CLICKERGAME_API UToastWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	bool IsAvailable() const { return !bInUse; }
	void PlayToast(float PlayRate = 1.0f);
	virtual void SetupToast(const FText& InText, const FVector2D& ScreenPos);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* ToastAnim = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bInUse = false;

	void OnToastFinished(UUMGSequencePlayer& Player);
};
