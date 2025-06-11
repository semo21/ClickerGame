// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "MyPlayerController.generated.h"

class UClickerComponent;

UCLASS()
class CLICKERGAME_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	// called when the button clicked
	UFUNCTION()
	void OnUpgradeClicked();
	void UpdateCurrencyUI();


protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


private:
	UPROPERTY()
	UClickerComponent* ClickerComponent;

	UPROPERTY()
	UUserWidget* ClickerUI;

	UPROPERTY()
	UTextBlock* CurrencyText;

	UPROPERTY()
	UTextBlock* ClickValueText;

	UPROPERTY()
	UTextBlock* UpgradeCostText;

	UPROPERTY()
	UTextBlock* PassiveIncomeText;

	UPROPERTY()
	UButton* UpgradeButton;

	UPROPERTY()
	TSubclassOf<UUserWidget> WidgetClassRef;

	void OnClick();
};
