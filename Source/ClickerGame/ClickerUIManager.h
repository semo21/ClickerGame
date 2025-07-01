// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ClickerComponent.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "ClickerUIManager.generated.h"

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
	void ShowClickEffect(const FVector& WorldLocation);
	void ShowHUD();
	void HideHUD();
	UUserWidget* GetHUDWidget() const;
	void UpdateScore();
	void ShowUpgradeSuccessText();
	void HideUpgradeSuccessText();
	void SetClickerComponent(ClickerComponent* Comp);

private:
	AMyPlayerController* PlayerController;

	TSubclassOf<UClickFloatingTextWidget> FloatingTextWidgetClass;
	TArray<UClickFloatingTextWidget*> FloatingTextPool;
	
	AActor* CurrentClickEffect = nullptr;
	UNiagaraSystem* ClickEffectAsset;

	FTimerHandle TimerHandle;

	TSubclassOf<UUserWidget> HUDWidgetClass;
	UUserWidget* HUDWidget;
	UTextBlock* CurrencyText;
	UTextBlock* ClickValueText;
	UTextBlock* UpgradeCostText;
	UTextBlock* PassiveIncomeText;
	UTextBlock* UpgradeSuccessText;
	UButton* UpgradeButton;
	FTimerHandle UpgradeSuccessTimerHandle;
	UClickerComponent* ClickerComponent;

	UClickFloatingTextWidget* GetFloatingTextWidgetFromPool();
	
};
