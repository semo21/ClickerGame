// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ClickerUIManager.generated.h"


class UUserWidget;
class AMyPlayerController;
class UClickFloatingTextWidget;
/**
 * 
 */
UCLASS()
class CLICKERGAME_API UClickerUIManager : public UObject
{
	GENERATED_BODY()
	

public:
	void Initialize(AMyPlayerController* InController);

	void ShowFloatingText(const FString& Message, const FVector& WorldLocation);

private:
	AMyPlayerController* PlayerController;

	TSubclassOf<UClickFloatingTextWidget> FloatingTextWidgetClass;

	TArray<UClickFloatingTextWidget*> FloatingTextPool;

	UClickFloatingTextWidget* GetFloatingTextWidgetFromPool();

	FTimerHandle TimerHandle;
};
