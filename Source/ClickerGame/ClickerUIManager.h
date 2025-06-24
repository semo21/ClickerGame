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
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<AActor> ClickEffectClass;

	void Initialize(AMyPlayerController* InController);
	void ShowFloatingText(const FString& Message, const FVector& WorldLocation);
	void ShowClickEffect(const FVector& WorldLocation);
	void ShowHUD();
	void HideHUD();
	void UpdateScore(int32 NewScore);

private:
	AMyPlayerController* PlayerController;
	TSubclassOf<UClickFloatingTextWidget> FloatingTextWidgetClass;
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UUserWidget* HUDWidget;
	TArray<UClickFloatingTextWidget*> FloatingTextPool;
	FTimerHandle TimerHandle;
	AActor* CurrentClickEffect = nullptr;

	UClickFloatingTextWidget* GetFloatingTextWidgetFromPool();

	
};
